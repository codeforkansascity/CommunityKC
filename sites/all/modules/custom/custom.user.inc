<?php 
/**
 * @file
 *  custom.user.inc
 *
 *  User related custom module functions go here.
 */

/** 
 * implements hook_form_user_profile_form_alter()
 * Used to add the similar project preferences to the user preferences form.
 * notifications
 */
function custom_form_user_profile_form_alter(&$form, &$form_state) {
	# watchdog('custom', 'user profile form !form', array('!form' => var_export($form,TRUE)), WATCHDOG_DEBUG);
	# $account = new stdClass;
	$account = user_load($form_state['build_info']['args'][0]->uid);
	# $account->uid = $form_state['build_info']['args'][0]->uid;
	
	# this is a prettier version of the default widget, which we will hide.
	# otherwise admin would still see it.
	unset($form['field_project_notification_prefs']);
	$prefs_bit_value = 0;
	if (!empty($account->field_project_notification_prefs) ) {
		$prefs_bit_value = $account->field_project_notification_prefs[LANGUAGE_NONE][0]['value'];
	}
	$notify_prefs = _custom_project_notify_field_default_value($prefs_bit_value);

	$form['notification'] = array(
		'#type' => 'fieldset',
		'#title' => t('Notification settings'),
		'#weight' => '6',
		'#collapsible' => TRUE,
		'#access' => _custom_user_is_author($account, 'project'),
		'applies_when' => array(
			'#prefix' => '<p>',
			'#markup' => t('After you have entered one or more projects you can choose to be notified about similar projects'),
			'#suffix' => '</p>',
			'#weight' => 0,
		),
		'similar' => array(
			'#prefix' => '<h2>',
			'#markup' => t('Notify me about new projects that are:'),
			'#suffix' => '</h2>',
			'#weight' => 5,
		),
		'project_notification_prefs' => array(
  			'#type' => 'checkboxes',
  			'#title' => t(''),
  			'#options' => array(
  				1 => t('In the same neighborhood as one of my projects'),
  				2 => t('The same type as one of my projects'),
  				4 => t('Both in the same neighborhood and of the same type as one of my projects'),  				
  			),
			'#weight' => 10,
			'#default_value' => $notify_prefs, // array(1=>1,2=>2),
		),
		'email_notice' => array(
			'#prefix' => '<p>',
			'#markup' => t('You will receive notification emails from this website when projects that match your preferences are added.'),
			'#suffix' => '</p>',
			'#weight' => 20,
		),
	);	
}


/**
 * Determines if user has authored at least one content node or is admin
 * @param int $uid - user id of user in question
 * @param string $type - node type, leave NULL for any
 * @return bool TRUE if user has authored a content node, FALSE if not.
 * notifications
 */
function _custom_user_is_author($account, $type = NULL) {
	$rid = user_role_load_by_name('admin')->rid;
	# admin users always treated as authors
	if (user_has_role($rid, $account)) {
		return true;
	}
	# else check for authorship	
	$node_count_q = db_select('node', 'n')
	->fields('n', array('nid')) 
	->condition('uid', $account->uid, '=');
	# add condition if the type param is specified.
	if (!empty($type)) {
		$node_count_q->condition('type', $type, '=');
	}
	# continue defining and executing the query
	$node_count = $node_count_q
	->countQuery()
	->execute()->fetchField();	
	# count query should return a numeric number of nodes with the user as the author
	# result is true if they have more than 0 nodes authored
	return $node_count > 0;
}


/**
 * implements hook_user_presave()
 * Saves the user preferences data added to the user profile form
 * notifications
 */
function custom_user_presave(&$edit, $account, $category) {
	# reset field
	//$account->field_project_notify_prefs = array(LANGUAGE_NONE => array());
	# adjust based on form
	# we can express the selection of preferences in one number by summing all the non zero values in the array from the form.
	$prefs_sum = 0;
	if (!empty($edit['project_notification_prefs'])) {
		foreach($edit['project_notification_prefs'] as $key=>$value) {
			$prefs_sum += $value;
		}
	}
	$account->field_project_notification_prefs[LANGUAGE_NONE][0]['value'] = $prefs_sum;

}
/**
 * field stores a bit total like 7 - this splits it to 3 things and then to an assoc array the form alter can use for a default value.
 * Data format is set up specifically for the form.
 * $bit_array is 3 0 or 1 digits representing highest to lowest - left side is highest to array[0] is the 4 digit position.
 * @param int $bit_total value stored in field
 * notifications
 */
function _custom_project_notify_field_default_value($bit_total) {
	$bit_array = _custom_decimal_prefs_to_bit_array($bit_total);
	
	$result = array(
		1 => $bit_array[2] ? 1 : 0,  // same neighborhood
		2 => $bit_array[1] ? 2 : 0,  // same type
		4 => $bit_array[0] ? 4 : 0   // same type and neighborhood
	);
	return $result;
}



/**
* Used for one-time mapping users to projects
*/
function custom_map_user_to_project($nid, $full_name, $email) {
 	# load project node
 	echo "updating $nid..."; 	
	$node = node_load($nid);
	echo "with user $email\n";	
	$user = user_load_by_mail($email);
	if ($user) {		
		$uid = $user->uid;
		echo "\tfound user $uid\n";
	}	
	else {
		$user = user_load_by_name($email);
		if ($user) {
			echo "\tfound by name..";
			if (empty($user->mail)) {
				$user->mail = $email;
				user_save($user);
				echo "updated email.\n";
			}
			$uid = $user->uid;			
		}
		else {
		# create user
		$account = new stdClass;
		$account->is_new = true;
		$account->name = $email;
		$account->mail = $email;
		$account->status = 1;
		$account->field_full_name = array(LANGUAGE_NONE=>array(0=>array('value'=>$full_name)));
		$account->pass = $node->title . $full_name;
		user_save($account);
		$uid = $account->uid;
		echo "\tcreated user $uid\n";
		}
	}
	$node->uid = $uid;
	node_save($node);
	watchdog('custom', 'custom user map to project !nid, !fn, !email', array('!nid'=>$nid, '!fn'=>$full_name, '!email' => $email), WATCHDOG_INFO);
}

function _custom_page_map_users() {
	echo "<h1>User Mapping</h1>\n";
	echo "<pre>\n";
// add custom user map calls here if needed again
	echo "</pre>\n";
}
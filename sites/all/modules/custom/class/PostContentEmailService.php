<?php


// CCF_Node - holds all projects. Use changed field for criteria
class PostContentEmailService
{
  public function __construct()
  {

  }

  public function run()
  {
    variable_set('mail_system', array('html_mail_system' => 'HTMLMailSystem'));
    $sql_query = "SELECT
                    n.nid,
                    n.uid
                  FROM ccf_node n
                  WHERE
                    n.type = 'project' AND
                    n.status = 1 AND
                    n.changed <= UNIX_TIMESTAMP( DATE_ADD(DATE_ADD(CURDATE(), INTERVAL -6 MONTH), INTERVAL -1 SECOND) );
                  ";

    $queryResults = db_query($sql_query)->fetchAll();
    if (empty($queryResults))
      return;

    $length = count($queryResults);
    $projectNodeIds = array_fill(0, $queryResults, null);
    $projectUserIds = array_fill(0, $queryResults, null);

    for ($i = 0; $i < $length; $i++) {
      $projectId = intval($queryResults[$i]->nid);
      $projectNodeIds[$i] = $projectId;
      $projectUserIds[$projectId] = intval($queryResults[$i]->uid);
    }

    $users = user_load_multiple($projectUserIds);
    $projects = node_load_multiple($projectNodeIds);


    foreach ($projects as $project) {
      //_custom_sage_get_field
      $user = $users[(int)$project->uid];
      $email = $user->mail;
      $fullname = $user->field_full_name['und'][0]['value'];
      $project_name = $project->title;
      $last_rev = $project->revision_timestamp;

      $token_array = array(
        'user' => $user,
        'email' => $email,
        'fullname' => $fullname,
        'project_nid' => $project->nid,
        'project_name' => $project_name,
        'last_rev' => $last_rev,
      );

      //Queue up items

      $queue = new stdClass();
      $queue->uid = (int)$project->uid;
      $queue->mail_type = 'custom_project_notification_email';
      $queue->tokens = json_encode($token_array);
      $queue->created = REQUEST_TIME;
      $queue->sent = null;
      drupal_write_record( 'custom_notify_email_queue', $queue); // Move this out of the day
    }

    $email_query = "SELECT * FROM {custom_notify_email_queue} WHERE sent IS NULL LIMIT 10";
    $records = db_query($email_query)->fetchAll();

    foreach($records as $record){
      //send email...
      $tokens = json_decode($record->tokens);
      //$content = "Hi, ".$tokens->fullname.", your project, ".$tokens->project_name.", was last updated ".date("m/d/Y", $tokens->last_rev);

      $subject = "Custom Drupal Mail";
      $to = "test@localhost.com";
      // $to = $tokens->email
      $from = "CommunityKC";

      $root_dir = DRUPAL_ROOT;
      $template_path = $root_dir."/sites/all/modules/custom/email_templates/SixMonthProjectEmail.html";

      $template = file_get_contents($template_path);
      $content = t($template, array('!project_name' => $tokens->project_name));

      custom_drupal_mail($from, $to, $subject, $content);

      //enque table
      update_node_enque($record->queue_id);
      //update ccf_node's rev date to today
      //update_node_ccf_node($tokens->project_nid);

    }
  }
}




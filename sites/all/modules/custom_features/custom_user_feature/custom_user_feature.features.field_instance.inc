<?php
/**
 * @file
 * custom_user_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function custom_user_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_full_name'.
  $field_instances['user-user-field_full_name'] = array(
    'bundle' => 'user',
    'custom_add_another' => '',
    'custom_remove' => '',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Enter your full name in the way you wish it to be displayed on the site.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'display_label' => 'Full name',
    'entity_type' => 'user',
    'field_name' => 'field_full_name',
    'label' => 'Full Name',
    'required' => 0,
    'settings' => array(
      'custom_add_another' => '',
      'custom_remove' => '',
      'text_processing' => 0,
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'user-user-field_project_notification_prefs'.
  $field_instances['user-user-field_project_notification_prefs'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Stores checkbox prefs in bit form - 0 is no notification, 1 neighborhood, 2 is same type, 4 is same type and neighborhood. Checked boxes are populated from sum of choices - each corresponds to a bit in a binary number - 001 011 111 010 etc',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_project_notification_prefs',
    'label' => 'Project Notification Prefs',
    'required' => FALSE,
    'settings' => array(
      'custom_add_another' => '',
      'custom_remove' => '',
      'max' => 7,
      'min' => 0,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 5,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Enter your full name in the way you wish it to be displayed on the site.');
  t('Full Name');
  t('Project Notification Prefs');
  t('Stores checkbox prefs in bit form - 0 is no notification, 1 neighborhood, 2 is same type, 4 is same type and neighborhood. Checked boxes are populated from sum of choices - each corresponds to a bit in a binary number - 001 011 111 010 etc');

  return $field_instances;
}

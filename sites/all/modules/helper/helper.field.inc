<?php

/**
 * @file
 * Field integration for the Helper module.
 */

/**
 * Implements hook_field_create_instance().
 */
function helper_field_create_instance($instance) {
  // Clear the menu cache whenever a field instances is created.
  variable_set('menu_rebuild_needed', TRUE);
}

/**
 * Implements hook_field_delete_instance().
 */
function helper_field_delete_instance($instance) {
  // Clear the menu cache whenever a field instances is deleted.
  variable_set('menu_rebuild_needed', TRUE);
}

/**
 * A clone of field_delete_field() that works for inactive fields.
 */
function _helper_field_delete_field($field) {
  FieldHelper::deleteField($field, FALSE);
}

/**
 * A clone of field_delete_instance() that works for inactive fields.
 */
function _helper_field_delete_instance($instance) {
  FieldHelper::deleteInstance($instance, FALSE);
}

function _helper_purge_inactive_deleted_fields() {
  $instances = field_read_instances(array('deleted' => 1), array('include_deleted' => 1, 'include_inactive' => 1));
  foreach ($instances as $instance) {
    watchdog('helper', 'Purging inactive and deleted field instance @field_name:@entity_type:@bundle.', array('@field_name' => $instance['field_name'], '@entity_type' => $instance['entity_type'], '@bundle' => $instance['bundle']));
    FieldHelper::deleteInstance($instance);
  }
  $fields = field_read_fields(array('deleted' => 1), array('include_deleted' => 1, 'include_inactive' => 1));
  foreach ($fields as $field) {
    watchdog('helper', 'Purging inactive and deleted field @field_name.', array('@field_name' => $field['field_name']));
    FieldHelper::deleteField($field);
  }
}

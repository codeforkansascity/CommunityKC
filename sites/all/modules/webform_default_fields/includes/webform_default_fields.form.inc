<?php

/**
 * @file
 * Building forms
 */

/**
 * An additional form submit handler for webform settings.
 * Make sure to create default fields nodes for all content type that are webform-enabled.
 */
function webform_default_fields_form_webform_admin_settings_submit($form, $form_state) {
  $type = $form_state['input']['type'];
  if (isset($form_state['input']['webform_node']) && isset($form_state['input']['webform_default_fields'])) {
    variable_set('webform_default_fields_allow_node_' . $form['#node_type']->type, TRUE);
    _webform_default_fields_container_node($type, FALSE);
  }
  else {
    variable_set('webform_default_fields_allow_node_' . $form['#node_type']->type, FALSE);
    _webform_default_fields_delete_container_node($type, TRUE);
  }
  menu_rebuild(); 
}
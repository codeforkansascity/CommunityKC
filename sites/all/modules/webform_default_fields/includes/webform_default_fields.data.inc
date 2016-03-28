<?php

/**
 * @file
 * Information management 
 */

/**
 * Get node types which are webform-enabled
 *
 * @return array Content types list
 */
function _webform_default_fields_webform_node_types() {
  $webform_enabled_types = webform_variable_get('webform_node_types');
  $types = array();

  foreach (node_type_get_types() as $type) {
    $type_name = $type->type;

    // Ensure content type is webform-enabled
    if (!in_array($type_name, $webform_enabled_types)) {
      continue;
    }

    $type_url_str = str_replace('_', '-', $type_name);

    $types[] = array('url' => $type_url_str, 'name' => $type_name);
  }
  return $types;
}

/**
 * Create "master-node" for content type
 *
 * Master node contains all the data about webform
 *   fields for linked content type
 *
 * @param string $content_type
 */
function _webform_default_fields_create_container_node($content_type) {
  $node = new stdClass();
  $node->title = 'Webform Default Fields Master Node';
  $node->type = $content_type;
  $node->status = 0;
  $node->webform = array(
    'confirmation' => '',
    'roles' => array_keys(user_roles())
  );
  node_save($node);
  webform_ensure_record($node);
  return $node->nid;
}

/**
 * Update "master-node" for content type
 * 
 * @param string $content_type 
 */
function _webform_default_fields_update_container_node($content_type, $old_content_type) {
  if (variable_get('webform_default_fields_nid_' . $old_content_type, 0)) {
    variable_del('webform_default_fields_nid_' . $old_content_type);
    variable_set('webform_default_fields_nid_' . $content_type, $nid);
  }
}

/**
 * Delete "master-node" for content type
 * 
 * @param string $content_type 
 */
function _webform_default_fields_delete_container_node($content_type, $rebuild = TRUE) {
  if ($nid = variable_get('webform_default_fields_nid_' . $content_type, 0)) {
    node_delete($nid);      
    if ($rebuild) {
      menu_rebuild();
    }  
  }
}

/**
 * Get Master node by content type
 *
 * @param string $content_type Target content type
 * @return int Master node NID
 */
function _webform_default_fields_container_node($content_type, $rebuild = TRUE) {
  if (!($nid = variable_get('webform_default_fields_nid_' . $content_type, 0))) {
    // Cancel menu_rebuild() during node_save()
    // Please @see https://www.drupal.org/node/2088485
    variable_set('menu_rebuild_needed', FALSE);
    $nid = _webform_default_fields_create_container_node($content_type);
    variable_set('webform_default_fields_nid_' . $content_type, $nid);
    if ($rebuild) {
      menu_rebuild();
    }
  }
  return $nid;
}
<?php

/**
 * @file
 * Administration pages
 */

/**
 * Page callback
 */
function webform_default_fields_list($content_type) {
  module_load_include('inc', 'webform', 'includes/webform.components');
  
  $content_type = str_replace('-', '_', $content_type);

  $nid = _webform_default_fields_container_node($content_type);
    
  $node = node_load($nid);
  
  // Create a new container node if the expected one is missing.
  if (!$node) {
    $nid = _webform_default_fields_create_container_node($content_type);
    variable_set('webform_default_fields_nid_' . $content_type, $nid);
    $node = node_load(array("nid" => $nid));
  }
  return webform_components_page($node);
}

/**
 * Redirect webform fields page to content type fields callback
 */
function webform_default_fields_redirect_master($nid) {
  $node = node_load($nid);
  $content_type = str_replace('_', '-', $node->type);
  drupal_goto('admin/structure/types/manage/' . $content_type . '/webform-fields');
}
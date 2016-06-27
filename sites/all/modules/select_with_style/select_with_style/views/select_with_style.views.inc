<?php

/**
 * @file
 * select_with_style.views.inc
 *
 * Alterations to Views filter handlers.
 */

/**
 * Implements hook_views_data_alter().
 *
 * Temporarily swap out the taxonomy term filter handlers used in Views.
 *
 * This gets called when:
 * o the widget type is changed on the Manage Fields tab of the content type
 * o a View is saved
 * o the caches get cleared
 *
 * We could implement this in hook_field_views_data_alter().
 * However all hook_field_views_data_alter() implementations are called prior
 * to any hook_views_data_alter() implementations, which means that we cannot
 * place ourselves last via the module weight when competing with other
 * modules implementing that hook.
 */
function select_with_style_views_data_alter(&$data) {
  if (!variable_get('select_with_style_use_in_views', TRUE)) {
    return;
  }
  foreach ($data as $table_name => $table_data) {
    foreach ($table_data as $field_name => $field_data) {
      if (isset($field_data['filter']['handler']) && isset($field_data['filter']['field_name'])) {
        if ($field = field_info_field($field_data['filter']['field_name'])) {
          // Note: we get here for both the field and its revision counterpart.

          // If the View has a taxonomy term filter then swap it out for ours.
          // We don't want to interfere with other modules that introduce
          // subclasses of 'views_handler_filter_term_node_tid', so we only
          // swap out known Views classes, not subclasses thereof.
          $handler = &$data[$table_name][$field_name]['filter']['handler'];
          if ($handler == 'views_handler_filter_term_node_tid' || $handler == 'views_handler_filter_term_node_tid_depth') {
            // We're only interested in handlers that belong to Fields that have
            // a Select with Style widget attached.
            $instances = select_with_style_get_field_instances($field['field_name']);
            foreach ($instances as $instance) {
              if ($instance['widget']['module'] == 'select_with_style') {
                $handler = 'select_with_style_handler_filter_term_node_tid';
                break;
              }
            }
          }
        }
      }
    }
  }
}

<?php

/**
 * @file
 * select_with_style_handle_filter_term_node_tid.inc
 *
 * Views filter override to style exposed term filters.
 * Also covers the case where exposed filter forms are in blocks.
 */

class select_with_style_handler_filter_term_node_tid extends views_handler_filter_term_node_tid {

  function value_form(&$form, &$form_state) {

    if (empty($this->options['expose']['identifier'])) {
      parent::value_form($form, $form_state);
      return;
    }
    $field_name = $name = $this->options['expose']['identifier'];

    // See if the filter name has '_tid' or '_tid_N' appended. If it does, chop
    // it to find the associated field name.
    if ($_tid = strrpos($name, '_tid')) {
      $field_name = drupal_substr($name, 0, $_tid);
    }
    if ($field = field_info_field($field_name)) {
      // A field may be attached to multiple node types and users. Each will
      // return an instance. Not sure how to reliable identify the right
      // $instance and thus the widget settings.
      // The important thing is to retrieve the right terms (select options).
      // These depend on the $field only, not the $instance.
      foreach (select_with_style_get_field_instances($field_name) as $instance) {
        if ($instance['widget']['module'] == 'select_with_style') {
          break;
        }
        $instance = NULL;
      }
      if (empty($instance['widget']['settings']['select_with_style'])) {
        // This Views field does not have a Select with Style counterpart field
        // widget on the Manage Fields Edit form. Fall back on global defaults.
        $settings = array(
          'hierarchy_depth_prefix' => variable_get('select_with_style_def_hierarchy_depth_prefix'),
          'term_transform_callback' => variable_get('select_with_style_def_term_transform_callback'),
          'multi_select_height' => variable_get('select_with_style_def_multi_select_height'),
          'css file' => variable_get('select_with_style_def_css_files', array()),
        );
      }
      else {
        $settings = $instance['widget']['settings']['select_with_style'];
      }
      // Suppress hierarchy prefix if "Show hierarchy in dropdown" isn't ticked
      // on the filter's Settings panel.
      if (empty($this->options['hierarchy'])) {
        $settings['hierarchy_depth_prefix'] = NULL;
      }
      $widget_type = isset($instance['widget']['type']) ? $instance['widget']['type'] : 'select_tree';
      // Load options (w/wout hierarchy prefixes) and get attributes too.
      list($options, $option_attributes) = _select_with_style_options_and_attributes_lists($field, $widget_type, $settings);
    }
    if (empty($options)) {
      // If any of the above failed, then default to what Views does normally.
      parent::value_form($form, $form_state);
      return;
    }

    if (!empty($this->options['expose']['reduce'])) {
      $options = $this->reduce_value_options($options);
      // For optgroups, remove parents that have no children ...
      foreach ($options as $parent => $children) {
        if (is_array($children) && empty($children)) {
          unset($options[$parent]);
        }
      }
    }
    if (!empty($settings['multi_select_height'])) {
      if ($field['cardinality'] > 1 || $field['cardinality'] == FIELD_CARDINALITY_UNLIMITED) {
        $form[$name]['#size'] = $settings['multi_select_height'];
      }
    }
    $max_size = empty($form[$name]['#size']) ? 9 : $form[$name]['#size'];
    $form[$name]['#size'] = min($max_size, $this->count_entries($options));

    $form[$name]['#type'] = 'select';
    $form[$name]['#multiple'] = TRUE;
    $form[$name]['#options'] = $options;
    $form[$name]['#option_attributes'] = $option_attributes;
    // Add basic and optional CSS
    $form[$name]['#attached']['css'][] = drupal_get_path('module', 'select_with_style') . '/select_with_style.css';
    if (!empty($settings['css file'])) {
      if (!is_array($settings['css file'])) {
        $settings['css file'] = array($settings['css file']);
      }
      $css_files = select_with_style_css_files();
      foreach ($settings['css file'] as $css_file) {
        if (!empty($css_files[$css_file])) {
          $form[$name]['#attached']['css'][] = $css_files[$css_file];
        }
      }
    }
    // The caller, exposed_form(), wants to receive the element in 'value'.
    $form['value'] = $form[$name];
  }

  // Recursively calculates length of select list, including parent headings.
  function count_entries($array) {
    $count = 0;
    foreach ($array as $value) {
      $count += is_array($value) ? 1 + $this->count_entries($value) : 1;
    }
    return $count;
  }
}

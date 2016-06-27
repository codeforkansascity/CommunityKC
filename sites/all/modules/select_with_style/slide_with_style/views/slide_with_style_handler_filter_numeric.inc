<?php

/**
 * @file
 * slide_with_style_handle_filter_numeric.inc
 *
 * Views filter override to style exposed numeric filters as slider widgers.
 */
class slide_with_style_handler_filter_numeric extends views_handler_filter_numeric {

  function value_form(&$form, &$form_state) {

    if (!empty($this->definition['field_name'])) {
      $field_name = $this->definition['field_name'];
      if ($field = field_info_field($field_name)) {
        // A field may be attached to multiple node types and users. Each will
        // return an instance. Not sure how to reliable identify the right
        // $instance and thus the widget settings. Using the first we find.
        $instances = slide_with_style_get_field_instances($field_name);
        foreach ($instances as $instance) {
          if ($instance['widget']['module'] == 'slide_with_style') {
            break;
          }
          $instance = NULL;
        }
      }
    }
    if (empty($instance)) {
      // Perform the default behaviour
      parent::value_form($form, $form_state);
      return;
    }
    $min = isset($instance['settings']['min']) ? $instance['settings']['min'] : 0;
    $max = isset($instance['settings']['max']) ? $instance['settings']['max'] : 100;
    if ($field['type'] == 'list_integer' && !empty($field['settings']['allowed_values'])) {
      $keys = array_keys($field['settings']['allowed_values']);
      $min = reset($keys);
      $max = end($keys);
    }
    $default = $min;

    $field_id = $this->options['id'];
    $form_state['slider_id'] = 'edit-' . trim($field_id, '_ ');
    if (isset($form_state['input'][$field_id])) {
      $default = $form_state['input'][$field_id];
    }
    $element = array();
    if ($this->operator == 'between' || $this->operator == 'not between') {
      // Set up a double-handled slider with min and max handles.
      $element['#default_values'] = explode('--', $default);
      if (count($element['#default_values']) < 2) {
        $element['#default_values'][] = $max;
        $form_state['input'][$field_id] = implode('--', $element['#default_values']);
      }
    }
    $element['#autosubmit'] = !empty($form_state['exposed_form_plugin']->options['autosubmit']);
    $items[$delta = 0]['value'] = (float)$default;
    $element = slide_with_style_field_widget_form($form, $form_state, $field, $instance, LANGUAGE_NONE, $items, $delta, $element);
    unset($element['value']['#element_validate']);
    unset($element['#default_values']);

    $form += $element;
  }

  function accept_exposed_input($input) {
    if (($this->operator == 'between' || $this->operator == 'not between') && !empty($this->options['id'])) {
      $field_id = $this->options['id'];
      $min_max = explode('--', is_array($input[$field_id]) ? reset($input[$field_id]) : $input[$field_id]);
      $min = reset($min_max);
      $max = next($min_max);
      $input[$field_id] = array('min' => $min, 'max' => $max === FALSE ? $min : $max);
    }
    return parent::accept_exposed_input($input);
  }

}
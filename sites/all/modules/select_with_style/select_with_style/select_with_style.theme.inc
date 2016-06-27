<?php

/**
 * @file
 * select_with_style.theme.inc
 */

/**
 * Returns HTML for a select form element.
 *
 * It is possible to group options together as "optgroups" sub-elements of
 * the select. To do this, change the format of $options to an associative
 * array in which the keys are group labels, and the values are associative
 * arrays in the normal #options format.
 * Note that while you can nest optgroups through this function, your browser
 * may not honour deep nesting and flatten the optgroups hierarchy to one level.
 * For fine-grained styling of the HTML select options, $variables may include
 * $variables['element']['#option_attributes'], an array indexed by the same
 * keys as variables['element']['#options'], but containing CSS attributes, in
 * the manner of #attributes.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #options, #option_attributes,
 *     #description, #extra, #multiple, #required, #name, #attributes, #size.
 *
 * @ingroup themeable
 */
function theme_select_with_style_select($variables) {
  $element = $variables['element'];
  if (!isset($element['#option_attributes'])) {
    // Fall back to the original.
    return theme_select($variables);
  }
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select', 'with-style'));
  return '<select ' . drupal_attributes($element['#attributes']) . '>' . select_with_style_select_options($element) . '</select>';
}

/**
 * Returns HTML for the inner part of the select form element, i.e. its options.
 *
 * The $element['#options'] may be a linear or nested list.
 *
 * $element['#option_attributes'] is to pass attributes like 'style' and 'class'
 * to each option. Must has the same keys as $element['#options'], but is
 * always a linear array.
 *
 * @param $element
 *   An associative array containing the properties of the element. For
 *   fine-grained styling of the HTML select options, $element may include
 *   $element['#option_attributes'], a linear array indexed by the same keys as
 *   the $element['$options'] property, but containing CSS attributes.
 * @param $choices
 *   Mixed: Either an associative array of items to list as choices, or an
 *   object with an 'option' member that is an associative array. This
 *   parameter should not be passed when calling this function. It is used for
 *   recursion purposes.
 * @return
 *   An HTML string of options for the select form element, with CSS attributes.
 */
function select_with_style_select_options($element, $choices = NULL) {

  if (!isset($choices)) {
    $choices = $element['#options'];
  }

  $value_valid = isset($element['#value']) || array_key_exists('#value', $element);
  $value_is_array = $value_valid && is_array($element['#value']);
  $options = '';
  foreach ($choices as $key => $choice) {
    $option_attributes = isset($element['#option_attributes'][$key]) ? drupal_attributes($element['#option_attributes'][$key]) : '';
    if (is_array($choice)) {
      $options .= '<optgroup label="' . $key . '"' . $option_attributes . '>';
      $options .= select_with_style_select_options($element, $choice);
      $options .= '</optgroup>';
    }
    elseif (is_object($choice)) {
      $options .= select_with_style_select_options($element, $choice->option);
    }
    else {
      $key = (string) $key;
      if ($value_valid && (!$value_is_array && (string) $element['#value'] === $key || ($value_is_array && in_array($key, $element['#value'])))) {
        $selected = ' selected="selected"';
      }
      else {
        $selected = '';
      }
      $options .= '<option value="' . check_plain($key) . '"' . $selected . $option_attributes . '>' . check_plain($choice) . '</option>';
    }
  }
  return $options;
}

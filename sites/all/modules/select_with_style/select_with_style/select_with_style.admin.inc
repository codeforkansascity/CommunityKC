<?php

/**
 * @file
 * select_with_style.admin.inc
 *
 * Configuration options for Select with Style module.
 */

/**
 * Menu callback for admin configuration settings.
 */
function select_with_style_admin_configure() {
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );
  if (module_exists('views')) {
    $form['general']['select_with_style_use_in_views'] = array(
      '#type' => 'checkbox',
      '#title' => t('Also employ Select with Style widgets in Views exposed filters.'),
      '#default_value' => variable_get('select_with_style_use_in_views', TRUE),
      '#description' => t('If not ticked, then the widget will be available only as an input widget to edit entities with taxonomy term fields.')
    );
  }
  $form['general']['select_with_style_show_widgets_in_field_list'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show widget names in <a href="!url">Field list</a> overview (Reports page).', array('!url' => url('admin/reports/fields'))),
    '#default_value' => variable_get('select_with_style_show_widgets_in_field_list', TRUE),
    '#description' => t('')
  );
  $form['widget_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default widget settings'),
    '#description' => t("You can override these for each instance of the Select with Style widget on the entity's <strong>Manage Field</strong> page.<br/>Views: if the exposed filter does not have a counterpart on the entity's Manage Field page, then the below configuration will be used."),
  );
  $form['widget_defaults']['select_with_style_def_hierarchy_depth_prefix'] = array(
    '#type' => 'textfield',
    '#size' => 12,
    '#title' => t('Default hierarchy depth indicator prefix'),
    '#description' => t("You may enter any sequence of characters. Core default for taxonomies is a single hyphen. Copy and paste from these if you like them: <br/><strong>► ⇒ » ↘ ⁲ ◆ ❤ ❥ ❖ ✈ ♫ ♛ ♟ ★ ✱ ☺ ✔ ☯ ✉ </strong>.<br/>If you don't want a prefix, untick <strong>Show in hierarchy in dropdown</strong> on the View's filter. Or enter a space."),
    '#default_value' => variable_get('select_with_style_def_hierarchy_depth_prefix', '-'),
    '#element_validate' => array('_select_with_style_validate_hierarchy_depth_prefix'),
    '#required' => FALSE,
  );
  $form['widget_defaults']['select_with_style_def_term_transform_callback'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#title' => t('Optionally invoke a callback to apply a transformation of option labels into CSS class names'),
    '#description' => t('Enter <code>select_with_style_country_name_to_code</code> to transform localised country names into ISO two-letter codes.'),
    '#default_value' => variable_get('select_with_style_def_term_transform_callback'),
    '#element_validate' => array('_select_with_style_validate_callback'),
    '#required' => FALSE,
  );
  $form['widget_defaults']['select_with_style_def_multi_select_height'] = array(
    '#type' => 'textfield',
    '#size' => 4,
    '#title' => t('Height of term select box (in rows)'),
    '#description' => t('Applies only to multi-select boxes. If left blank the browser default will be used.'),
    '#default_value' => variable_get('select_with_style_def_multi_select_height'),
    '#element_validate' => array('element_validate_integer_positive'),
    '#required' => FALSE,
  );
  $path = drupal_get_path('module', 'select_with_style') . '/css';
  $form['widget_defaults']['select_with_style_css_directory'] = array(
    '#type' => 'textfield',
    '#title' => t('Directory containing CSS styling files'),
    '#default_value' => variable_get('select_with_style_css_directory', $path),
    '#description' => t('')
  );
  $options = array();
  foreach (select_with_style_css_files() as $name => $filespec) {
    $options[$name] = $name;
  }
  $form['widget_defaults']['select_with_style_def_css_files'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#size' => 3,
    '#title' => t('CSS styling files'),
    '#default_value' => variable_get('select_with_style_def_css_files', array()),
    '#options' => $options,
    '#description' => t('Select one or more. The directory where these files are looked up may be changed above.'),
    '#required' => FALSE,
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['#submit'][] = 'select_with_style_admin_configure_form_submit';
  $form['#theme'] = 'system_settings_form';
  return $form;
}

function select_with_style_admin_configure_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  variable_set('select_with_style_use_in_views', $values['select_with_style_use_in_views']);
  variable_set('select_with_style_show_widgets_in_field_list', $values['select_with_style_show_widgets_in_field_list']);
  variable_set('select_with_style_def_hierarchy_depth_prefix', $values['select_with_style_def_hierarchy_depth_prefix']);
  variable_set('select_with_style_def_term_transform_callback', $values['select_with_style_def_term_transform_callback']);
  variable_set('select_with_style_def_multi_select_height', $values['select_with_style_def_multi_select_height']);
  variable_set('select_with_style_css_directory', $values['select_with_style_css_directory']);
  variable_set('select_with_style_def_css_files', $values['select_with_style_def_css_files']);

  drupal_set_message(t('Select with Style configuration has been saved.'));

  // Make sure Views exposed filters will be updated with the correct widgets.
  if (module_exists('views')) {
    views_invalidate_cache();
  }
}

/**
 * Menu callback; lists all defined fields with their widgets for quick reference.
 *
 * Code adapted from function field_ui_fields_list(), field_ui.admin.inc
 */
function select_with_style_fields_and_widgets_list() {
  $instances = field_info_instances();
  $field_types = field_info_field_types();
  $bundles = field_info_bundles();

  $modules = system_rebuild_module_data();

  $show_widget_column = variable_get('select_with_style_show_widgets_in_field_list', TRUE);

  $header = array(t('Field name'), t('Field type'), t('Used in'));
  if ($show_widget_column) {
    $header[] = t('Widget');
  }
  $rows = array();
  foreach ($instances as $entity_type => $type_bundles) {
    foreach ($type_bundles as $bundle => $bundle_instances) {
      foreach ($bundle_instances as $field_name => $instance) {
        $field = field_info_field($field_name);

        // Initialize the row if we encounter the field for the first time.
        if (!isset($rows[$field_name])) {
          $rows[$field_name]['class'] = $field['locked'] ? array('menu-disabled') : array('');
          $rows[$field_name]['data'][0] = $field['locked'] ? t('@field_name (Locked)', array('@field_name' => $field_name)) : $field_name;
          $module_name = $field_types[$field['type']]['module'];
          $rows[$field_name]['data'][1] = $field_types[$field['type']]['label'] . ' ' . t('(module: !module)', array('!module' => $modules[$module_name]->info['name']));
        }

        // Add the current instance.
        if (empty($bundles[$entity_type][$bundle])) {
          $rows[$field_name]['data'][2][] = '';
        }
        else {
          $admin_path = _field_ui_bundle_admin_path($entity_type, $bundle);
          $rows[$field_name]['data'][2][] = $admin_path ? l($bundles[$entity_type][$bundle]['label'], $admin_path . '/fields') : $bundles[$entity_type][$bundle]['label'];
        }
        if ($show_widget_column) {
          if (!isset($rows[$field_name]['data'][3])) {
            $rows[$field_name]['data'][3] = array();
          }
          // Add the field widget details (name + module)
          $module_name = $instance['widget']['module'];
          $widget_name = $instance['widget']['type'] . ' ' . t('(module: !module)', array('!module' => $modules[$module_name]->info['name']));
          if (!in_array($widget_name, $rows[$field_name]['data'][3])) {
            $rows[$field_name]['data'][3][] = $widget_name;
          }
        }
      }
    }
  }
  foreach ($rows as $field_name => $cell) {
    $rows[$field_name]['data'][2] = implode(', ', $cell['data'][2]);
    if ($show_widget_column) {
      $rows[$field_name]['data'][3] = implode(', ', $cell['data'][3]);
    }
  }
  if (empty($rows)) {
    $output = t('No fields have been defined yet.');
  }
  else {
    // Sort rows by field name.
    ksort($rows);
    $output = theme('table', array('header' => $header, 'rows' => $rows));
  }
  return $output;
}

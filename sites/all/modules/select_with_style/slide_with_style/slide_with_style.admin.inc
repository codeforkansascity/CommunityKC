<?php

/**
 * @file
 * slide_with_style.admin.inc
 *
 * Configuration options for Slide with Style module.
 */

/**
 * Menu callback for admin configuration settings.
 */
function slide_with_style_admin_configure() {
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );
  if (module_exists('views')) {
    $form['general']['slide_with_style_use_in_views'] = array(
      '#type' => 'checkbox',
      '#title' => t('Also employ Slide with Style widget in Views exposed filters.'),
      '#default_value' => variable_get('slide_with_style_use_in_views', TRUE),
      '#description' => t('If not ticked, then the widget will be available only as an input widget to edit entities.')
    );
  }

  $form['widget_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Widget settings'),
  );
  $path = drupal_get_path('module', 'slide_with_style') . '/css';
  $form['widget_defaults']['slide_with_style_css_directory'] = array(
    '#type' => 'textfield',
    '#title' => t('Directory containing CSS styling files for sliders'),
    '#default_value' => variable_get('slide_with_style_css_directory', $path),
    '#description' => t('')
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['#submit'][] = 'slide_with_style_admin_configure_form_submit';
  $form['#theme'] = 'system_settings_form';
  return $form;
}

/**
 * Handle the admin form submission.
 *
 * @param type $form
 * @param type $form_state
 */
function slide_with_style_admin_configure_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  variable_set('slide_with_style_use_in_views', $values['slide_with_style_use_in_views']);
  variable_set('slide_with_style_css_directory', $values['slide_with_style_css_directory']);

  drupal_set_message(t('Slide with Style configuration has been saved.'));

  // Make sure Views exposed filters will be updated with the correct widgets.
  if (module_exists('views')) {
    views_invalidate_cache();
  }
}
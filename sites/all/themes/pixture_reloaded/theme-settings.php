<?php

// Set this no matter what, we need this to happen
if (module_exists('noggin')) {
  variable_set('noggin:header_selector', '#header .header-inner');
}


/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function pixture_reloaded_form_system_theme_settings_alter(&$form, &$form_state) {

  // Include a hidden form field with the current release information
  $form['at-release'] = array(
    '#type' => 'hidden',
    '#default_value' => '7.x-3.x',
  );

  // Remove option to use full width wrappers
  $form['at']['modify-output']['design']['page_full_width_wrappers'] = array(
    '#access' => FALSE,
  );

  // Tell the submit function its safe to run the color inc generator
  // if running on AT Core 7.x-3.x
  $form['at-color'] = array(
    '#type' => 'hidden',
    '#default_value' => TRUE,
  );

  if (at_get_setting('enable_extensions') === 1) {
    $form['at']['corners'] = array(
      '#type' => 'fieldset',
      '#title' => t('Rounded corners'),
    );
    $form['at']['corners']['corner_radius'] = array(
      '#type' => 'select',
      '#title' => t('Corner radius'),
      '#default_value' => theme_get_setting('corner_radius'),
      '#description' => t('Change the corner radius for blocks, node teasers and comments.'),
      '#options' => array(
        'rc-0' => t('none'),
        'rc-4' => t('4px'),
        'rc-8' => t('8px'),
        'rc-12' => t('12px'),
      ),
    );
    $form['at']['pagestyles'] = array(
      '#type' => 'fieldset',
      '#title' => t('Box Shadows and Textures'),
      '#description' => t('<h3>Shadows and Textures</h3><p>The box shadows are implimented using CSS and only work in modern compliant browsers. The textures are small, semi-transparent images that tile to fill the entire background.</p>'),
    );
    $form['at']['pagestyles']['shadows'] = array(
      '#type' => 'fieldset',
      '#title' => t('Box Shadows'),
      '#description' => t('<h3>Box Shadows</h3><p>Box shadows (a drop shadow/glow effect) apply to the main content column and work only in CSS3 compliant browsers such as Firefox, Safari and Chrome.</p>'),
    );
    $form['at']['pagestyles']['shadows']['box_shadows'] = array(
      '#type' => 'radios',
      '#title' => t('<strong>Apply a box shadow to the main content column</strong>'),
      '#default_value' => theme_get_setting('box_shadows'),
      '#options' => array(
        'bs-n' => t('None'),
        'bs-l' => t('Box shadow - light'),
        'bs-d' => t('Box shadow - dark'),
      ),
    );
    $form['at']['pagestyles']['textures'] = array(
      '#type' => 'fieldset',
      '#title' => t('Textures'),
      '#description' => t('<h3>Body Textures</h3><p>This setting adds a texture over the main background color - the darker the background the more these stand out, on light backgrounds the effect is subtle.</p>'),
    );
    $form['at']['pagestyles']['textures']['body_background'] = array(
      '#type' => 'select',
      '#title' => t('Select texture'),
      '#default_value' => theme_get_setting('body_background'),
      '#options' => array(
        'bb-n'  => t('None'),
        'bb-h'  => t('Hatch'),
        'bb-vl' => t('Vertical lines'),
        'bb-hl' => t('Horizontal lines'),
        'bb-g'  => t('Grid'),
        'bb-d'  => t('Dots'),
      ),
    );
    $form['at']['menus'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu Settings'),
    );
    $form['at']['menus']['mbp'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu Bar Alignment'),
      '#description' => t('<h3>Menu Bar Alignment</h3><p>Position the Menu Bar left, center or right. This will position any menu (Superfish included) placed in the Menu Bar region.</p>'),
    );
    $form['at']['menus']['mbp']['menu_bar_position'] = array(
      '#type' => 'radios',
      '#title' => t('Set the position of the Menu bar'),
      '#default_value' => theme_get_setting('menu_bar_position'),
      '#options' => array(
        'mbp-l' => t('Left (default)'),
        'mbp-c' => t('Center'),
        'mbp-r' => t('Right'),
      ),
    );
    $form['at']['menus']['mb'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu Bullets'),
      '#description' => t('<h3>Menu Bullets</h3><p>This setting allows you to customize the bullet images used on menus items. Bullet images only show on normal vertical block menus.</p>'),
    );
    $form['at']['menus']['mb']['menu_bullets'] = array(
      '#type' => 'select',
      '#title' => t('Menu Bullets'),
      '#default_value' => theme_get_setting('menu_bullets'),
      '#options' => array(
        'mb-n' => t('None'),
        'mb-dd' => t('Drupal default'),
        'mb-ah' => t('Arrow head'),
        'mb-ad' => t('Double arrow head'),
        'mb-ca' => t('Circle arrow'),
        'mb-fa' => t('Fat arrow'),
        'mb-sa' => t('Skinny arrow'),
      ),
    );
  }
}

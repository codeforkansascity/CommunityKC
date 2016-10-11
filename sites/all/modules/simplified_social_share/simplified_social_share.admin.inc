<?php
/**
 * @file
 * Admin page callback file for the simplified_open_social_share module.
 */
/**
 * Function that build an abstract representation of a HTML form for Social Sharing settings.
 *
 * @global string $base_url URL to home page.
 * @param array $form Nested array of form elements that comprise the form.
 * @param array $form_state A keyed array containing the current state of the form.
 * @return array A renderable form array for the respective request.
 */
function simplified_open_social_sharebar_settings_form($form, &$form_state) {
 
  global $base_url;
  drupal_add_library('system', 'ui.sortable');
  drupal_add_js(drupal_get_path('module', 'simplified_social_share') . '/js/simplified_open_social_share.js', array(
      'type' => 'file',
      'scope' => 'footer',
      'weight' => 5,
    ));
 
  drupal_add_css(drupal_get_path('module', 'simplified_social_share') . '/css/simplified_open_social_share.css');   
  drupal_add_css('https://sharecdn.social9.com/v2/css/os-share-widget-style.css', array('type' => 'external'));   
  drupal_add_js('jQuery(document).ready(function() {
var horizontal_image="' . variable_get("simplified_open_social_share_horizontal_images") . '";
var vertical_image="' . variable_get("simplified_open_social_share_vertical_images") . '";
if (horizontal_image == 8 || horizontal_image == 9) {
counter_horizontal_show();
}
else {
sharing_horizontal_show();
if (horizontal_image == 2 || horizontal_image == 3) {
sharing_simplehorizontal_show();
}
}
if (vertical_image == 6 || vertical_image == 7) {
counter_vertical_show();
}
else {
sharing_vertical_show();
}
var selected_theme = "' . variable_get("simplified_open_social_share_selected_share_interface") . '";
if (selected_theme == "vertical"){
hidden_horizontal_widget();
}
else {
display_horizontal_widget();
}
});', array('type' => 'inline', 'scope' => 'header', 'weight' => 5));
  $my_path = drupal_get_path('module', 'simplified_social_share');

    // Add thanks text to show at admin page.
    $thanks_text = t('Social9 provides Social Sharing solutions to your drupal website. We also offer Social Plugins for <a href="@wordpress" target="_blank">Wordpress</a>,
<a href="@joomla" target="_blank">Joomla</a>,
<a href="@magento" target="_blank">Magento</a>,
<a href="@zencart" target="_blank">Zen-Cart</a>,
<a href="@ee" target="_blank">Expression Engine</a>,
<a href="@prestashop" target="_blank">Prestashop</a> and
<a href="@typo3" target="_blank">Typo3</a>!
Please visit <a href="@social9" target="_blank">www.social9.com</a> for more info.',
      array(
        '@social9' => 'http://www.social9.com',
        '@joomla' => 'http://www.social9.com/docs/joomla-social-share?utm_source=Drupal&utm_medium=Refferal&utm_campaign=Plugin',
        '@magento' => 'http://www.social9.com/docs/magento-social-share?utm_source=Drupal&utm_medium=Refferal&utm_campaign=Plugin',
        '@ee' => 'http://www.social9.com/docs/expression-engine-social-share?utm_source=Drupal&utm_medium=Refferal&utm_campaign=Plugin',
        '@prestashop' => 'http://www.social9.com/docs/prestashop-social-share?utm_source=Drupal&utm_medium=Refferal&utm_campaign=Plugin',
        '@typo3' => 'http://www.social9.com/docs/typo3-social-share?utm_source=Drupal&utm_medium=Refferal&utm_campaign=Plugin',
        '@wordpress' => 'http://www.social9.com/docs/wordpress-social-share?utm_source=Drupal&utm_medium=Refferal&utm_campaign=Plugin',
        '@zencart' => 'http://www.social9.com/docs/zencart-social-share?utm_source=Drupal&utm_medium=Refferal&utm_campaign=Plugin',
      ));
    // Show module details.
    $update_text = t('<a href="@installation" target="_blank">Plugin Installation, Configuration and Troubleshooting</a> <br/>  <a href="@features" target="_blank">Social9 Features</a>',
      array(
        '@installation' => 'http://www.social9.com/docs/drupal-social-share?utm_source=Drupal&utm_medium=Refferal&utm_campaign=Plugin',
        '@features' => 'http://www.social9.com/features?utm_source=Drupal&utm_medium=Refferal&utm_campaign=Plugin',

      ));
    $form['thanks_block'] = array(
      '#type' => 'fieldset',
      '#title' => t('Thank you for installing Social9.com social sharing Module!<br/><br/>'),
      '#description' => $thanks_text,
      '#attributes' => array('style' => 'float:left;'),
    );
    $form['update_block'] = array(
      '#type' => 'fieldset',
      '#title' => t('Help'),
      '#description' => $update_text,
    );
  
  $share_group = 'share';
  $form[$share_group] = array(
    '#type' => 'fieldset',
    '#title' => t('Simplified Open Social Share Settings'),
  );
  $form[$share_group]['simplified_open_social_share_horizontal'] = array(
    '#type' => 'item',
    '#prefix' => '<div><b>' . t('What open social sharing widget theme do you want to use across your website?<div class="description">Horizontal and Vertical themes can be enabled simultaneously</div>') . '</b></div>',
    '#markup' => ' <div id="oss_tabs"><ul><li><a id="simplified_open_social_share_horizontal" onclick="display_horizontal_widget();">Horizontal widget</a></li><li><a id="simplified_open_social_share_veritical" onclick="hidden_horizontal_widget();">Vertical widget</a></li><li><a id="simplified_open_social_share_advance_settings" onclick="display_advance_widget();">Advance Settings</a></li></ul>',
  );
  $form[$share_group]['simplified_open_social_share_selected_share_interface'] = array(
    '#type' => 'hidden',
    '#title' => t('selected share interface'),
    '#default_value' => variable_get('simplified_open_social_share_selected_share_interface'),
    '#suffix' => '<div id=oss_divwhite></div><div id=oss_divgrey></div><div id="show_horizontal_block">',
  );
  $form[$share_group]['simplified_open_social_share_enable_horizontal_share'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to enable horizontal open social sharing for your website?'),
    '#default_value' => variable_get('simplified_open_social_share_enable_horizontal_share', 1),
    '#options' => array(
      1 => t('Yes'),
      0 => t('No'),
    ),
  );
  $form[$share_group]['simplified_open_social_share_enable_vertical_share'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to enable vertical open social sharing for your website'),
    '#default_value' => variable_get('simplified_open_social_share_enable_vertical_share', 0),
    '#options' => array(
      1 => t('Yes'),
      0 => t('No'),
    ),
  );
  $form[$share_group]['opensocialshare_label_string'] = array(
    '#type' => 'textfield',
    '#title' => t('What text do you want to display above the open social sharing widget?'),
    '#default_value' => variable_get('opensocialshare_label_string', 'Share it now!'),
    '#description' => t('Leave empty for no text.'),
  );
  $form[$share_group]['simplified_open_social_share_horizontal_images'] = array(
    '#type' => 'radios',
    '#id' => 'simplified_open_social_share_horizontal_images',
    '#default_value' => variable_get('simplified_open_social_share_horizontal_images', 0),
    '#options' => array(
      0 => '<img src="' . $base_url . '/' . $my_path . '/images/horizonSharing32.png"></img>',
      1 => '<img src="' . $base_url . '/' . $my_path . '/images/horizonSharing16.png"></img>',
      10 => '<img src="' . $base_url . '/' . $my_path . '/images/responsive-icons.png"></img>',
      2 => '<img src="' . $base_url . '/' . $my_path . '/images/single-image-theme-large.png"></img>',
      3 => '<img src="' . $base_url . '/' . $my_path . '/images/single-image-theme-small.png"></img>',
      8 => '<img src="' . $base_url . '/' . $my_path . '/images/horizontalvertical.png"></img>',
      9 => '<img src="' . $base_url . '/' . $my_path . '/images/horizontal.png"></img>',
    ),   
  );
  
  $form[$share_group]['simplified_open_social_share_vertical_images'] = array(
    '#type' => 'radios',
    '#id' => 'simplified_open_social_share_vertical_images',
    '#default_value' => variable_get('simplified_open_social_share_vertical_images', 4),
    '#options' => array(
      4 => '<img id= "32VerticlewithBox" src="' . $base_url . '/' . $my_path . '/images/32VerticlewithBox.png"></img>',
      5 => '<img id="VerticlewithBox" src="' . $base_url . '/' . $my_path . '/images/16VerticlewithBox.png"></img>',
      6 => '<img id="hybrid-verticle-vertical" src="' . $base_url . '/' . $my_path . '/images/hybrid-verticle-vertical.png"></img>',
      7 => '<img id="hybrid-verticle-horizontal"  src="' . $base_url . '/' . $my_path . '/images/hybrid-verticle-horizontal.png"></img>',
    ),    
  );
  
  $form[$share_group]['simplified_open_social_share_show_horizotal'] = array(
    '#type' => 'hidden',
    '#suffix' => '<div id="simplified_open_social_share_show_horizotal_widget">',
  );
  $counter_providers = variable_get('socialcounter_rearrange_providers_list');

  if (empty($counter_providers)) {
    variable_set('socialcounter_rearrange_providers_list', simplified_open_social_share_default_sharing_networks('socialcounter_rearrange_providers_list'));
  }

  $form[$share_group]['opensocialshare_counter_show_providers_list'] = array(
    '#type' => 'item',
    '#id' => 'socialcounter_show_providers_list',
    '#class' => 'form-item form-type-checkboxes form-item-opensocialshare-counter-show-providers-list',
    '#title' => t('What sharing networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of Social9 sharing icon)'),
    '#default_value' => variable_get('socialcounter_rearrange_providers_list'),
    '#suffix' => '<div id="socialcounter_hidden_field" style="display:none;">',
  );

  foreach (variable_get("socialcounter_rearrange_providers_list") as $provider) {
    if (!empty($provider)) {
      $raw = $provider;
      $provider = str_replace(array(
        ' ',
        '++',
        '+',
      ), array(
        '',
        'plusplus',
        'plus',
      ), $provider);
      $form[$share_group][$provider] = array(
        '#type' => 'item',
        '#attributes' => array('class' => array('osshare_' . $provider)),
        '#markup' => '<input type = "hidden" id = "input-oscounter-' . $provider . '" name = "socialcounter_rearrange_providers_list[]" value = "' . $raw . '" />',
      );
    }
  }
  $share_providers = variable_get("simplified_open_social_share_rearrange_providers_list"); 
  
  if (empty($share_providers)) {
    variable_set('simplified_open_social_share_rearrange_providers_list', simplified_open_social_share_default_sharing_networks('simplified_open_social_share_rearrange_providers_list'));
  }

  $form[$share_group]['opensocialshare_show_providers_list'] = array(
    '#type' => 'item',
    '#id' => 'opensocialshare_providers_list',
    '#title' => t('What sharing networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of Social9 sharing icon)'),
    '#default_value' => variable_get('simplified_open_social_share_rearrange_providers_list'),
    '#prefix' => '</div><div id="loginRadiusSharingLimit" style="color:red; display:none; margin-bottom: 5px;">' . t('You can select only 9 providers.') . '</div>',
    '#suffix' => '<div id="rearrange_sharing_text"><b>' . t('What sharing network order do you prefer for your sharing widget?(Drag around to set the order)') . '</b></div><ul id="simplified_open_social_share_rearrange_providers" class="simplified_open_social_share_rearrange_providers">',
  );

  foreach (variable_get("simplified_open_social_share_rearrange_providers_list") as $provider) {
    if (!empty($provider)) {
      $form[$share_group]['osshare_iconsprite32' . $provider] = array(
        '#type' => 'item',        
        '#attributes' => array('class' => array('osshare_' . $provider)),
        '#markup' => '<li id = "edit-osshare-iconsprite32' . $provider . '" class = "share-provider ' . $provider . ' flat square size-32 horizontal" title = "' . $provider . '" >
      <input type = "hidden" id = "input-osshare-' . $provider . '" name = "simplified_open_social_share_rearrange_providers_list[]" value = "' . $provider . '" /></li>',
      );     
    }
  }

  $form[$share_group]['simplified_open_social_share_rearran_providers_list'] = array(
    '#type' => 'hidden',
    '#prefix' => '</ul>',
    '#suffix' => '</div>',
  );
  $form[$share_group]['simplified_open_social_share_show_veritical'] = array(
    '#type' => 'hidden',
    '#suffix' => '<div id="simplified_open_social_share_show_veritcal_widget">',
  );
  $vertical_counter_providers = variable_get('socialcounter_vertical_rearrange_providers_list');

  if (empty($vertical_counter_providers)) {
    variable_set('socialcounter_vertical_rearrange_providers_list', simplified_open_social_share_default_sharing_networks('socialcounter_vertical_rearrange_providers_list'));
  }

  $form[$share_group]['opensocialshare_counter_vertical_show_providers_list'] = array(
    '#type' => 'item',
    '#id' => 'socialcounter_vertical_show_providers_list',
    '#title' => t('What sharing networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of Social9 sharing icon)'),
    '#default_value' => variable_get('socialcounter_vertical_rearrange_providers_list'),
    '#suffix' => '<div id="socialcounter_vertical_hidden_field" style="display:none;">',
  );

  foreach (variable_get("socialcounter_vertical_rearrange_providers_list") as $provider) {
    if (!empty($provider)) {
      $raw = $provider;
      $provider = str_replace(array(
        ' ',
        '++',
        '+',
      ), array(
        '',
        'plusplus',
        'plus',
      ), $provider);
      $form[$share_group]['osshare_vertical_' . $provider] = array(
        '#type' => 'item',
        '#attributes' => array('class' => array('osshare_vertical_' . $provider)),
        '#markup' => '<input type = "hidden" id = "input-oscounter-vertical-' . $provider . '" name = "socialcounter_vertical_rearrange_providers_list[]" value = "' . $raw . '" />',
      );
    }
  }

  $vertical_share_providers = variable_get("opensocialshare_vertical_rearrange_providers_list");

  if (empty($vertical_share_providers)) {
    variable_set('opensocialshare_vertical_rearrange_providers_list', simplified_open_social_share_default_sharing_networks('opensocialshare_vertical_rearrange_providers_list'));
  }

  $form[$share_group]['opensocialshare_vetical_show_providers_list'] = array(
    '#type' => 'item',
    '#id' => 'opensocialshare_vetical_show_providers_list',
    '#title' => t('What sharing networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of Social9 sharing icon)'),
    '#default_value' => variable_get('opensocialshare_vertical_rearrange_providers_list'),
    '#prefix' => '</div><div id="loginRadiusSharingLimit_vertical" style="color:red; display:none; margin-bottom: 5px;">' . t('You can select only 9 providers.') . '</div>',
    '#suffix' => '<div id="rearrange_sharing_text_vertical"><b>' . t('What sharing network order do you prefer for your sharing widget?(Drag around to set the order)') . '</b></div><ul id="opensocialshare_vertical_rearrange_providers" class="opensocialshare_vertical_rearrange_providers">',
  );

  foreach (variable_get("opensocialshare_vertical_rearrange_providers_list") as $provider) {
    if (!empty($provider)) {
      $form[$share_group]['osshare_iconsprite32_vertical' . $provider] = array(
        '#type' => 'item',
        '#attributes' => array('class' => array('osshare_' . $provider)),
        '#markup' => '<li id = "edit-osshare-iconsprite32_vertical' . $provider . '" class = "share-provider ' . $provider . ' flat square size-32 horizontal" title = "' . $provider . '" >
      <input type = "hidden" id = "input-osshare-vertical-' . $provider . '" name = "opensocialshare_vertical_rearrange_providers_list[]" value = "' . $provider . '" /></li>',
      );
    }
  }

  $form[$share_group]['opensocialshare_vertical_rearrange_providers_list_div'] = array(
    '#type' => 'hidden',
    '#prefix' => '</ul>',
    '#suffix' => '</div>',
  );
  
  $form[$share_group]['simplified_open_social_share_vertical_images']['opensocialshare_vertical_position'] = array(
    '#type' => 'radios',
    '#title' => t('Select the position of social sharing widget'),
    '#weight' => 50,
    '#default_value' => variable_get('opensocialshare_vertical_position', 0),
    '#options' => array(
      0 => t('Top Left'),
      1 => t('Top Right'),
      2 => t('Bottom Left'),
      3 => t('Bottom Right'),
    ),
    '#attributes' => array('style' => 'clear:both'),
  );
  $form[$share_group]['opensocialshare_position_top'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show at the top of content.'),
    '#default_value' => variable_get('opensocialshare_position_top', 1) ? 1 : 0,
    '#prefix' => '<div id="horizontal_sharing_show" style="clear:both;"> <b>Select the position of Social sharing interface</b>',
  );
  $form[$share_group]['opensocialshare_position_bottom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show at the bottom of content.'),
    '#default_value' => variable_get('opensocialshare_position_bottom', 1) ? 1 : 0,
    '#suffix' => '</div>',
  );
  $form[$share_group]['opensocialshare_show_pages'] = array(
    '#type' => 'radios',
    '#title' => t('Show social share on specific pages'),
    '#default_value' => variable_get('opensocialshare_show_pages', 0),
    '#options' => array(
      0 => t('All pages except those listed'),
      1 => t('Only the listed pages'),
    ),
  );
  $form[$share_group]['opensocialshare_show_exceptpages'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('opensocialshare_show_exceptpages', ''),
    '#description' => t('Enter a page title(you give on page creation) or node id (if url is http://example.com/node/1 then enter 1(node id)) with comma sepreted'),
    '#rows' => 5,
  );
  $form[$share_group]['opensocialshare_vertical_show_pages'] = array(
    '#type' => 'radios',
    '#title' => t('Show social share on specific pages'),
    '#default_value' => variable_get('opensocialshare_vertical_show_pages', 0),
    '#options' => array(
      0 => t('All pages except those listed'),
      1 => t('Only the listed pages'),
    ),
  );
  $form[$share_group]['opensocialshare_vertical_show_exceptpages'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('opensocialshare_vertical_show_exceptpages', ''),
    '#description' => t('Enter a page title(you give on page creation) or node id (if url is http://example.com/node/1 then enter 1(node id)) with comma sepreted'),
    '#rows' => 5,    
  );    
  
   
  $form[$share_group]['opensocialshare_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Please enter your desired email subject'),
    '#default_value' => variable_get('opensocialshare_email_subject'),    
  );
  $form[$share_group]['opensocialshare_email_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Please enter your desired email message'),
    '#default_value' => variable_get('opensocialshare_email_message')  
  ); 
  $form[$share_group]['opensocialshare_is_email_content_read_only'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to make the email content read only<a title="Your readers wont be able to change the Email Content if its read only."  style="text-decoration:none"> (<span style="color:#3CF;">?</span>)</a>'),
    '#default_value' => variable_get('opensocialshare_is_email_content_read_only', 'false'),
    '#options' => array(
      'true' => t('Yes (read only)'),
      'false' => t('No'),
    ),
  ); 
  
  $form[$share_group]['opensocialshare_is_shorten_url'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to use short URL during sharing<a title="Enable this if you want the URL to be shortened using Ish.re"  style="text-decoration:none"> (<span style="color:#3CF;">?</span>)</a>'),
    '#default_value' => variable_get('opensocialshare_is_shorten_url', 'false'),
    '#options' => array(
      'true' => t('Yes'),
      'false' => t('No'),
    ),
  );
 
  $form[$share_group]['opensocialshare_facebook_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter your Facebook App ID<a title="Enter the Facebook App Id if you want to track social sharing on your Facebook app"  style="text-decoration:none"> (<span style="color:#3CF;">?</span>)</a>'),
    '#default_value' => variable_get('opensocialshare_facebook_app_id'),    
  );      
  $form[$share_group]['opensocialshare_is_total_share'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to enable Total Share to display the total share count on your website<a title="Display the total shares URL got from all social providers"  style="text-decoration:none"> (<span style="color:#3CF;">?</span>)</a>'),
    '#default_value' => variable_get('opensocialshare_is_total_share', 'false'),
    '#options' => array(
      'true' => t('Yes'),
      'false' => t('No'),
    ),
  );     
  $form[$share_group]['opensocialshare_is_open_single_window'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to open all providers in a single window<a title="Disabling this opens all sharing providers in a new Popup"  style="text-decoration:none"> (<span style="color:#3CF;">?</span>)</a>'),
    '#default_value' => variable_get('opensocialshare_is_open_single_window', 'false'),
    '#options' => array(
      'true' => t('Yes'),
      'false' => t('No'),
    ),
  ); 
   
  $form[$share_group]['opensocialshare_popup_window'] = array(
    '#type' => 'checkbox',
    '#title' => t('Check this if you want to change default Popup Window Size. [Default Size 530*530 Px]'),
    '#default_value' => variable_get('opensocialshare_popup_window', 0) ? 1 : 0,  
    '#attributes' => array(
    'onchange' => "showAndHidePopupWindow();",
    ),
    '#prefix' => '<div id="popup_window_size" style="clear:both;"> <b>Do you want to enable custom popup window size<a title="Check this if you want to change default Popup Window Size. [Default Size 530*530 Px]"  style="text-decoration:none"> (<span style="color:#3CF;">?</span>)</a></b>' 
  );
   
  $form[$share_group]['opensocialshare_popup_window_size_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Popup window height'),
    '#default_value' => variable_get('opensocialshare_popup_window_size_height', ''),
    '#element_validate' => array('element_validate_number'),
  );
  $form[$share_group]['opensocialshare_popup_window_size_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Popup window width'),
    '#default_value' => variable_get('opensocialshare_popup_window_size_width', ''),
    '#description' => t('If you want to change popup window size, Make sure to fill both height and width(Ex.400,450).'),
    '#element_validate' => array('element_validate_number'),
    '#suffix' => '</div>',
  );  
   
  $form[$share_group]['opensocialshare_twitter_mention'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter your desired Twitter handle to mention during a Twitter share<a title="Handle will be mentioned as suffix as via @twitterhandle"  style="text-decoration:none"> (<span style="color:#3CF;">?</span>)</a>'),
    '#default_value' => variable_get('opensocialshare_twitter_mention', ''),    
  );    
  $form[$share_group]['opensocialshare_twitter_hash_tags'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter your desired Twitter hash tag to be used during a Twitter share<a title="Hashtag will be added to all tweets"  style="text-decoration:none"> (<span style="color:#3CF;">?</span>)</a>'),
    '#default_value' => variable_get('opensocialshare_twitter_hash_tags', ''),    
  );      
   $form[$share_group]['opensocialshare_is_mobile_friendly'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to enable mobile friendly sharing widget<a title="Enable this option to show a mobile sharing interface to mobile users"  style="text-decoration:none"> (<span style="color:#3CF;">?</span>)</a> '),
    '#default_value' => variable_get('opensocialshare_is_mobile_friendly', 'false'),
    '#options' => array(
      'true' => t('Yes'),
      'false' => t('No'),
    ),
  ); 
  
  $form[$share_group]['opensocialshare_custom_options'] = array(
    '#type' => 'textarea',
    '#title' => t('Please enter custom options for open social sharing'),
    '#id' => 'add_custom_options',
    '#rows' => 4,
    '#default_value' => variable_get('opensocialshare_custom_options', ''),    
    '#description' => t('<p style="color:black;">Choose form the list of options you want to customize from the <a target="_blank" href="http://www.social9.com/docs/custom-option-list">link</a></p>'),
    '#attributes' => array(
    'onchange' => "openSocialShareCheckValidJson();",
    ),
   ); 
  
  
  $form['#submit'][] = 'simplified_open_social_sharebar_settings_submit';
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Submit Social Sharing settings.
 *
 * @param $form Nested array of form elements that comprise the form.
 * @param $form_state array A keyed array containing the current state of the form
 * @return bool
 */
function simplified_open_social_sharebar_settings_submit($form, &$form_state) {

  foreach ($form_state['values'] as $key => $value) {
    if (is_array($value) && isset($form_state['values']['array_filter'])) {
      $value = array_keys(array_filter($value));
    }
    variable_set($key, $value);
  }
 
  simplified_open_social_share_save_network_providers($form_state);
  // Clean all values and save into database.
  foreach ($form_state['input'] as $key => $value) {
    if (is_array($value)) {
      variable_set($key, array_filter($value));
    }
  }
  drupal_set_message(t('The configuration options have been saved.'));
  // Clear the cached pages and blocks.
  cache_clear_all();
  menu_rebuild();
  return TRUE;
}

/**
 * Get sharing/Counter providers into database.
 *
 * @param array $form_state A keyed array containing the current state of the form
 */
function simplified_open_social_share_save_network_providers(&$form_state) {
  // Set default value of sharing networks.
  $settings = array(
    'simplified_open_social_share_rearrange_providers_list',
    'socialcounter_rearrange_providers_list',
    'opensocialshare_vertical_rearrange_providers_list',
    'socialcounter_vertical_rearrange_providers_list',  
  );

  foreach ($settings as $value) {
    simplified_open_social_share_save_network_providers_submit($form_state, $value);
  }
}

/**
 * Save the sharing/counter networks.
 *
 * @param array $form_state A keyed array containing the current state of the form
 * @param string $network Key of sharing/counter to get default networks.
 */
function simplified_open_social_share_save_network_providers_submit(&$form_state, $network) {

  if (isset($form_state['input'][$network])) { 
    //print_r($form_state['input'][])
    $form_state['input'][$network] = array_filter($form_state['input'][$network]);
  }
  else {
    $form_state['input'][$network] = simplified_open_social_share_default_sharing_networks($network);
  }
}

/**
 * Get default values of sharing/counter networks.
 *
 * @param string $key sharing/counter key
 * @return array default sharing/counter networks
 */
function simplified_open_social_share_default_sharing_networks($key) {
  if ($key == 'simplified_open_social_share_rearrange_providers_list' || $key == 'opensocialshare_vertical_rearrange_providers_list') {
    return array("facebook", "googleplus", "google", "pinterest", "twitter");
  }
  return array(
    "Facebook Like",
    "Google+ +1",
    "Pinterest Pin it",
    "LinkedIn Share",
  );
}

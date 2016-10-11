var selected_sharing_theme = jQuery('[name="simplified_open_social_share_selected_share_interface"]');
var script = document.createElement('script');
script.type = 'text/javascript';
script.text = 'var islrsharing = true; var islrsocialcounter = true;';
document.body.appendChild(script);

jQuery(document).ready(function () {  
    showAndHidePopupWindow();
 });  
 
window.onload = function () {
        
    jQuery("#edit-simplified-open-social-share-horizontal-images-0,#edit-simplified-open-social-share-horizontal-images-1, #edit-simplified-open-social-share-horizontal-images-10").click(function () {
        sharing_horizontal_show();
    });
    jQuery("#edit-simplified-open-social-share-horizontal-images-2,#edit-simplified-open-social-share-horizontal-images-3").click(function () {
        sharing_horizontal_show();
        sharing_simplehorizontal_show();
    });
    jQuery("#edit-simplified-open-social-share-horizontal-images-8,#edit-simplified-open-social-share-horizontal-images-9").click(function () {
        counter_horizontal_show();
    });
    jQuery("#edit-simplified-open-social-share-vertical-images-4,#edit-simplified-open-social-share-vertical-images-5").click(function () {
        sharing_vertical_show();
    });
    jQuery("#edit-simplified-open-social-share-vertical-images-6,#edit-simplified-open-social-share-vertical-images-7").click(function () {
        counter_vertical_show();
    });
  
    var sharing = ["Facebook","GooglePlus","Linkedin","Twitter","Pinterest","Email","Google","Digg","Reddit","Vkontakte","Tumblr","MySpace","Delicious","Print"];    
    sharingproviderlist(sharing);
    var counter = ["Facebook Like","Facebook Recommend","Facebook Send","Twitter Tweet","Pinterest Pin it","LinkedIn Share","StumbleUpon Badge","Reddit","Google+ +1","Google+ Share"];    
    counterproviderlist(counter);
    jQuery(".simplified_open_social_share_rearrange_providers, #opensocialshare_vertical_rearrange_providers").sortable({
        revert: true
    });
    if (selected_sharing_theme)
        loginRadiusToggleShareTheme(selected_sharing_theme.val());
    jQuery(".simplified_open_social_share_rearrange_providers, .opensocialshare_vertical_rearrange_providers").find("li").unwrap();   
    jQuery("#simplified_open_social_share_veritical").click(function () {
        loginRadiusToggleShareTheme("vertical");
    });
    jQuery("#simplified_open_social_share_horizontal").click(function () {
        loginRadiusToggleShareTheme("horizontal");
    });
    jQuery("#simplified_open_social_share_advance_settings").click(function () {
        loginRadiusToggleShareTheme("advance");
    });  

}
/*
 * Show and hide popup window ui
 */
function showAndHidePopupWindow() { 
        var value = jQuery('input[name=opensocialshare_popup_window]:checked').val();            
            if (value != 1) {                
                  jQuery('.form-item.form-type-textfield.form-item-opensocialshare-popup-window-size-height,.form-item.form-type-textfield.form-item-opensocialshare-popup-window-size-width').hide();      
            } else {                  
                   jQuery('.form-item.form-type-textfield.form-item-opensocialshare-popup-window-size-height,.form-item.form-type-textfield.form-item-opensocialshare-popup-window-size-width').show();     
            }       
}
/*
 * Check Json is valid or not.
 */
 function openSocialShareCheckValidJson() {    
      jQuery('#add_custom_options').change(function(){
      var profile = jQuery('#add_custom_options').val();      
      var response = '';
      try
      {
          response = jQuery.parseJSON(profile);
          if(response != true && response != false){
              var validjson = JSON.stringify(response, null, '\t').replace(/</g, '&lt;');
              if(validjson != 'null'){
                  jQuery('#add_custom_options').val(validjson);
                  jQuery('#add_custom_options').css("border","1px solid green");
              }else{                  
                  jQuery('#add_custom_options').css("border","1px solid red");
              }
          }
          else{
              jQuery('#add_custom_options').css("border","1px solid green");
          }
      } catch (e)
      {
          jQuery('#add_custom_options').css("border","1px solid green");
      }
  });
}
/*
 * Sharing Theme selected.
 */
function loginRadiusToggleShareTheme(theme) {
    
    var verticalDisplay = 'none';
    var horizontalDisplay = 'block';
    var simplified_open_social_share_horizontal = jQuery("#simplified_open_social_share_horizontal");
    var simplified_open_social_share_veritical = jQuery("#simplified_open_social_share_veritical");
    var simplified_open_social_share_advance = jQuery("#simplified_open_social_share_advance_settings");
    var vertical_position = jQuery(".form-item.form-type-radios.form-item-opensocialshare-vertical-position");
    if (theme == "vertical") {
        verticalDisplay = 'block';
        horizontalDisplay = 'none';
        simplified_open_social_share_horizontal.removeClass("active");
        simplified_open_social_share_advance.removeClass("active");
        simplified_open_social_share_veritical.addClass("active");
        vertical_position.removeClass("element-invisible");
    } else if(theme == "advance"){  
        simplified_open_social_share_advance.addClass("active");
        simplified_open_social_share_veritical.removeClass("active");
        simplified_open_social_share_horizontal.removeClass("active");
        vertical_position.addClass("element-invisible");
    }    
    else {     
        simplified_open_social_share_horizontal.addClass("active");
        simplified_open_social_share_veritical.removeClass("active");
        simplified_open_social_share_advance.removeClass("active");
        vertical_position.addClass("element-invisible");      
    }
    jQuery("#simplified_open_social_share_horizontal_images").css("display", horizontalDisplay);
    jQuery("#simplified_open_social_share_vertical_images").css("display", verticalDisplay);
}
/*
 * Get sharing provider list
 */
function sharingproviderlist(sharing) {
   // var sharing = $SS.Providers.More;
    var div = jQuery('#opensocialshare_providers_list');
    var div_vertical = jQuery('#opensocialshare_vetical_show_providers_list');
    if (div && div_vertical) {
       
        for (var i = 0; i < sharing.length; i++) {
            var listItem = jQuery("<div class= 'form-item form-type-checkbox form-item-opensocialshare-show-providers-list-" + sharing[i].toLowerCase() + "'><input type='checkbox' id='edit-opensocialshare-show-providers-list-" + sharing[i].toLowerCase() + "' onChange='loginRadiusSharingLimit(this),loginRadiusRearrangeProviderList(this)' name='opensocialshare_show_providers_list[" + sharing[i].toLowerCase() + "]' value='" + sharing[i].toLowerCase() + "' class='form-checkbox' /><label for='edit-opensocialshare-show-providers-list-" + sharing[i].toLowerCase() + "' class='option'>" + sharing[i] + "</label></div>");
            div.append(listItem);
            var listItem = jQuery("<div class= 'form-item form-type-checkbox form-item-opensocialshare-vertical-show-providers-list-" + sharing[i].toLowerCase() + "'><input type='checkbox' id='edit-opensocialshare-vertical-show-providers-list-" + sharing[i].toLowerCase() + "' onChange='loginRadiusverticalSharingLimit(this),loginRadiusverticalRearrangeProviderList(this)' name='opensocialshare_vertical_show_providers_list[" + sharing[i].toLowerCase() + "]' value='" + sharing[i].toLowerCase() + "' class='form-checkbox' /><label for='edit-opensocialshare-vertical-show-providers-list-" + sharing[i].toLowerCase() + "' class='option'>" + sharing[i] + "</label></div>");
            div_vertical.append(listItem);
        }
        jQuery('input[name^="simplified_open_social_share_rearrange_providers_list"]').each(function () {
            var elem = jQuery(this);
            if (!elem.checked) {
                jQuery('#edit-opensocialshare-show-providers-list-' + elem.val()).attr('checked', 'checked');
            }
        });
        jQuery('input[name^="opensocialshare_vertical_rearrange_providers_list"]').each(function () {
            var elem = jQuery(this);
            if (!elem.checked) {
                jQuery('#edit-opensocialshare-vertical-show-providers-list-' + elem.val()).attr('checked', 'checked');
            }
        });
    }
}
/*
 * Show sharing Rearrange Providers.
 */
function loginRadiusRearrangeProviderList(elem) {
    var ul = jQuery('#simplified_open_social_share_rearrange_providers');   
    var input = jQuery('#simplified_open_social_share_chnage_name');
    if (elem.checked) {
        var provider = jQuery("<li id='edit-osshare-iconsprite32" + elem.value + "' title='" + elem.value + "' class='share-provider " + elem.value + " flat square size-32 horizontal'><input type='hidden' value='" + elem.value + "' name='simplified_open_social_share_rearrange_providers_list[]' id='input-osshare-" + elem.value + "'></li>");
        ul.append(provider);
       
    } else {
        if (jQuery('#edit-osshare-iconsprite32' + elem.value)) {          
            jQuery('#edit-osshare-iconsprite32' + elem.value).remove();
        }
    }
}
/*
 * vertical Sharing Rearrange counter
 */
function loginRadiusverticalRearrangeProviderList(elem) {
    var ul = jQuery('#opensocialshare_vertical_rearrange_providers');    
    var input = jQuery('#opensocialshare_chnage_name');
    if (elem.checked) {
        var provider = jQuery("<li id='edit-osshare-iconsprite32_vertical" + elem.value + "' title='" + elem.value + "' class='share-provider " + elem.value + " flat square size-32 horizontal'><input type='hidden' value='" + elem.value + "' name='opensocialshare_vertical_rearrange_providers_list[]' id='input-osshare-vertical-" + elem.value + "'></li>");
        ul.append(provider);       
    } else {
        if (jQuery('#edit-osshare-iconsprite32_vertical' + elem.value)) {
          
            jQuery('#edit-osshare-iconsprite32_vertical' + elem.value).remove();
        }
    }
}
/*
 * Check limit for horizontal Social sharing.
 */
function loginRadiusSharingLimit(elem) {
    var checkCount = jQuery('input[name^="simplified_open_social_share_rearrange_providers_list"]').length;
    if (elem.checked) {
        // count checked providers
        checkCount++;
        if (checkCount >= 10) {           
            elem.checked = false;
            jQuery("#loginRadiusSharingLimit").show('slow');
            setTimeout(function () {
                jQuery("#loginRadiusSharingLimit").hide('slow');
            }, 2000);
            return;
        }
    }
}
/*
 * check limit for vertical Social sharing.
 */
function loginRadiusverticalSharingLimit(elem) {
    var checkCount = jQuery('input[name^="opensocialshare_vertical_rearrange_providers_list"]').length;
    if (elem.checked) {
        // count checked providers
       
        if (checkCount >= 10) {      
            elem.checked = false;
            jQuery("#loginRadiusSharingLimit_vertical").show('slow');
            setTimeout(function () {
                jQuery("#loginRadiusSharingLimit_vertical").hide('slow');
            }, 2000);
            return;
        } checkCount++;
    }
}
/*
 * Show Provider List for horizontal Social counter.
 */
function counterproviderlist(counter) {
    var div = jQuery('#socialcounter_show_providers_list');
    var div_vertical = jQuery('#socialcounter_vertical_show_providers_list');
    if (div && div_vertical) {
        for (var i = 0; i < counter.length; i++) {
            var value = counter[i].split(' ').join('');
            value = value.replace("++", "plusplus");
            value = value.replace("+", "plus");
            var listItem = jQuery("<div class= 'form-item form-type-checkbox form-item-opensocialshare_counter_show_providers_list-" + counter[i] + "'><input type='checkbox' id='edit-opensocialshare-counter-show-providers-list-" + value + "' onChange='loginRadiuscounterProviderList(this)' name='socialcounter_providers_list[]' value='" + counter[i] + "' class='form-checkbox' /><label for='edit-opensocialshare-counter-show-providers-list-" + value + "' class='option'>" + counter[i] + "</label></div>");
            div.append(listItem);
            var listItem = jQuery("<div class= 'form-item form-type-checkbox form-item-opensocialshare_counter_vertical_show_providers_list-" + counter[i] + "'><input type='checkbox' id='edit-opensocialshare-counter-vertical-show-providers-list-" + value + "' onChange='loginRadiuscounterverticalProviderList(this)' name='socialcounter_new_vertical_providers_list[]' value='" + counter[i] + "' class='form-checkbox' /><label for='edit-opensocialshare-counter-vertical-show-providers-list-" + value + "' class='option'>" + counter[i] + "</label></div>");
            div_vertical.append(listItem);
        }
        jQuery('input[name^="socialcounter_rearrange_providers_list"]').each(function () {
            var elem = jQuery(this);
            if (!elem.checked) {
                var value = elem.val().split(' ').join('');
                value = value.replace("++", "plusplus");
                value = value.replace("+", "plus");
                jQuery('#edit-opensocialshare-counter-show-providers-list-' + value).attr('checked', 'checked');
            }
        });
        jQuery('input[name^="socialcounter_vertical_rearrange_providers_list"]').each(function () {
            var elem = jQuery(this);
            if (!elem.checked) {
                var value = elem.val().split(' ').join('');
                value = value.replace("++", "plusplus");
                value = value.replace("+", "plus");
                jQuery('#edit-opensocialshare-counter-vertical-show-providers-list-' + value).attr('checked', 'checked');
            }
        });
    }
}
/*
 * Show Counter Providers selected.
 */
function loginRadiuscounterProviderList(elem) {
    var ul = jQuery('#socialcounter_show_providers_list');
    var raw = elem.value;
    var value = elem.value.split(' ').join('');
    value = value.replace("++", "plusplus");
    value = value.replace("+", "plus");
    if (elem.checked) {
        var provider = jQuery("<input type='hidden' value='" + raw + "' name='socialcounter_rearrange_providers_list[]' id='input-oscounter-" + elem.value + "'>");
        ul.append(provider);
    } else {
        jQuery('#input-oscounter-' + value).remove();
        jQuery('#edit-' + value).remove();
    }
}
/*
 * Provider list selcted in vertical counter.
 */
function loginRadiuscounterverticalProviderList(elem) {
    var ul = jQuery('#socialcounter_vertical_show_providers_list');
    var raw = elem.value;
    var value = elem.value.split(' ').join('');
    value = value.replace("++", "plusplus");
    value = value.replace("+", "plus");
    if (elem.checked) {
        var provider = jQuery("<input type='hidden' value='" + raw + "' name='socialcounter_vertical_rearrange_providers_list[]' id='input-oscounter-vertical-" + value + "'>");
        ul.append(provider);
    } else {
        jQuery('#input-oscounter-vertical-' + value).remove();
        jQuery('#edit-osshare-vertical-' + value).remove();
    }
}
/*
 * show Sharing Horizontal
 */
function sharing_horizontal_show() {
    toggle_sharing_counter(true);
}
/*
 * show Counter Horizontal .
 */
function counter_horizontal_show() {
    toggle_sharing_counter(false);
}
/*
 * Show simple sharing widget.
 */
function sharing_simplehorizontal_show() {
    toggle_sharing_counter(true, true);
}
/*
 * Toggle shairing and counter fields.
 */
function toggle_sharing_counter(is_open_social_share, is_social_counter) {
    var simple_sharing = is_open_social_share ? "addClass" : "removeClass";
    var simple_counter = is_open_social_share ? "removeClass" : "addClass";
    if (is_social_counter) {
        simple_counter = "addClass";
    }
    jQuery("#opensocialshare_providers_list, #rearrange_sharing_text, .simplified_open_social_share_rearrange_providers")[simple_counter]("element-invisible");
    jQuery("#socialcounter_show_providers_list")[simple_sharing]("element-invisible");

}
/*
 * Show sharing vertical.
 */
function sharing_vertical_show() {
    toggle_sharing_vertical_show(true);
}
/*
 * show Counter Vertical.
 */
function counter_vertical_show() {
    toggle_sharing_vertical_show(false);
}
/*
 * Toggle Vertical sharing widget.
 */
function toggle_sharing_vertical_show(is_open_social_share) {
    var simple_vertical_sharing = is_open_social_share ? "addClass" : "removeClass";
    var simple_vertical_counter = is_open_social_share ? "removeClass" : "addClass";
    jQuery("#socialcounter_vertical_show_providers_list")[simple_vertical_sharing]("element-invisible");
    jQuery("#opensocialshare_vetical_show_providers_list, #rearrange_sharing_text_vertical, #opensocialshare_vertical_rearrange_providers")[simple_vertical_counter]("element-invisible");
}
/*
 * Toggle horizontal sharing widget.
 */
function toggle_horizontal_widget(is_horizontal) {    
    var horizontal_sharing = is_horizontal ? "addClass" : "removeClass";   
    var vertical_sharing = is_horizontal ? "removeClass" : "addClass"; 
    var advance_sharing =  "addClass";
    jQuery("#simplified_open_social_share_show_horizotal_widget, .form-item.form-type-radio.form-item-simplified-open-social-share-horizontal-images, .form-item.form-type-textarea.form-item-opensocialshare-show-exceptpages, .form-item.form-type-radios.form-item-opensocialshare-show-pages, #horizontal_sharing_show, .form-item.form-type-radios.form-item-simplified-open-social-share-enable-horizontal-share, .form-item.form-type-select.form-item-opensocialshare-top-weight, .form-item.form-type-select.form-item-opensocialshare-bottom-weight, .form-item.form-type-radios.form-item-opensocialshare-horizontal-location, .form-item.form-type-textfield.form-item-opensocialshare-label-string")[horizontal_sharing]("element-invisible");
    jQuery("#simplified_open_social_share_show_veritcal_widget, .form-item.form-type-radio.form-item-simplified-open-social-share-vertical-images, .form-item.form-type-radios.form-item-opensocialshare-vertical-position, .form-item.form-type-radios.form-item-opensocialshare-vertical-show-pages, .form-item.form-type-textarea.form-item-opensocialshare-vertical-show-exceptpages, .form-item.form-type-radios.form-item-simplified-open-social-share-enable-vertical-share, .form-item.form-type-radios.form-item-opensocialshare-vertical-location")[vertical_sharing]("element-invisible");
    jQuery("#popup_window_size,.form-item.form-type-textarea.form-item-opensocialshare-email-message, .form-item.form-type-radios.form-item-opensocialshare-is-mobile-friendly, .form-item.form-type-textfield.form-item-opensocialshare-email-subject, .form-item.form-type-radios.form-item-opensocialshare-is-email-content-read-only, .form-item.form-type-textfield.form-item-opensocialshare-facebook-app-id, .form-item.form-type-radios.form-item-opensocialshare-is-shorten-url, .form-item.form-type-radios.form-item-opensocialshare-is-total-share, .form-item.form-type-radios.form-item-opensocialshare-is-open-single-window, .form-item.form-type-textfield.form-item-opensocialshare-popup-window-size-height, .form-item.form-type-textfield.form-item-opensocialshare-popup-window-size-width, .form-item.form-type-textfield.form-item-opensocialshare-twitter-mention, .form-item.form-type-textfield.form-item-opensocialshare-twitter-hash-tags, .form-item.form-type-textarea.form-item-opensocialshare-custom-options")[advance_sharing]("element-invisible");
}
/*
 * Show only vertical widget options.
 */
function hidden_horizontal_widget() {
    toggle_horizontal_widget(true);
}
/*
 * Show only Horizontal widget options.
 */
function display_horizontal_widget() {
    toggle_horizontal_widget(false);
}
/*
 * Show only advance widget options.
 */
function display_advance_widget() {  
    var horizontal_sharing =  "addClass";   
    var vertical_sharing =  "addClass";
    var advance_sharing =  "removeClass";
    jQuery("#simplified_open_social_share_show_horizotal_widget, .form-item.form-type-radio.form-item-simplified-open-social-share-horizontal-images, .form-item.form-type-textarea.form-item-opensocialshare-show-exceptpages, .form-item.form-type-radios.form-item-opensocialshare-show-pages, #horizontal_sharing_show, .form-item.form-type-radios.form-item-simplified-open-social-share-enable-horizontal-share, .form-item.form-type-select.form-item-opensocialshare-top-weight, .form-item.form-type-select.form-item-opensocialshare-bottom-weight, .form-item.form-type-radios.form-item-opensocialshare-horizontal-location, .form-item.form-type-textfield.form-item-opensocialshare-label-string")[horizontal_sharing]("element-invisible");
    jQuery("#simplified_open_social_share_show_veritcal_widget, .form-item.form-type-radio.form-item-simplified-open-social-share-vertical-images, .form-item.form-type-radios.form-item-opensocialshare-vertical-position, .form-item.form-type-radios.form-item-opensocialshare-vertical-show-pages, .form-item.form-type-textarea.form-item-opensocialshare-vertical-show-exceptpages, .form-item.form-type-radios.form-item-simplified-open-social-share-enable-vertical-share, .form-item.form-type-radios.form-item-opensocialshare-vertical-location")[vertical_sharing]("element-invisible");
    jQuery("#popup_window_size,.form-item.form-type-textarea.form-item-opensocialshare-email-message, .form-item.form-type-radios.form-item-opensocialshare-is-mobile-friendly, .form-item.form-type-textfield.form-item-opensocialshare-email-subject, .form-item.form-type-radios.form-item-opensocialshare-is-email-content-read-only, .form-item.form-type-textfield.form-item-opensocialshare-facebook-app-id, .form-item.form-type-radios.form-item-opensocialshare-is-shorten-url, .form-item.form-type-radios.form-item-opensocialshare-is-total-share, .form-item.form-type-radios.form-item-opensocialshare-is-open-single-window, .form-item.form-type-textfield.form-item-opensocialshare-popup-window-size-height, .form-item.form-type-textfield.form-item-opensocialshare-popup-window-size-width, .form-item.form-type-textfield.form-item-opensocialshare-twitter-mention, .form-item.form-type-textfield.form-item-opensocialshare-twitter-hash-tags, .form-item.form-type-textarea.form-item-opensocialshare-custom-options")[advance_sharing]("element-invisible");
}
var script = document.createElement('script');
script.type = 'text/javascript';
script.text = 'var islrsharing = true; var islrsocialcounter = true;';
document.body.appendChild(script);


//window.onload = function(){
    if (Drupal.settings.advanceopensocialshare.horizontal != undefined && Drupal.settings.advanceopensocialshare.horizontal) {
        var string = Drupal.settings.advanceopensocialshare.providers;
        var providers = string.split(",");

        var str = Drupal.settings.advanceopensocialshare.widgets;
        var widgets = str.split(',');       
    
        var script = '{';
        
        if (Drupal.settings.advanceopensocialshare.emailMessage != '') {
            script = script + 'emailMessage:' + "'" + Drupal.settings.advanceopensocialshare.emailMessage + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.emailSubject != '') {
            script = script + 'emailSubject:' + "'" + Drupal.settings.advanceopensocialshare.emailSubject + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.isEmailContentReadOnly != '') {
            script = script + 'isEmailContentReadOnly:' + Drupal.settings.advanceopensocialshare.isEmailContentReadOnly + ',';
        }            
        script = script + "isCounterWidgetTheme:" + Drupal.settings.advanceopensocialshare.isCounterWidgetTheme + ',';
        script = script + "isHorizontalCounter:" + Drupal.settings.advanceopensocialshare.isHorizontalCounter + ',';
        script = script + "isHorizontalLayout:" + Drupal.settings.advanceopensocialshare.isHorizontalLayout + ',';

        if (Drupal.settings.advanceopensocialshare.widgetIconSize != '') {
            script = script + 'widgetIconSize:' + "'" + Drupal.settings.advanceopensocialshare.widgetIconSize + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.widgetStyle != '') {
            script = script + 'widgetStyle:' + "'" + Drupal.settings.advanceopensocialshare.widgetStyle + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.theme != '') {
            script = script + 'theme:' + "'" + Drupal.settings.advanceopensocialshare.theme + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.isShortenUrl != '') {
            script = script + 'isShortenUrl:' + Drupal.settings.advanceopensocialshare.isShortenUrl + ',';
        }
        if (Drupal.settings.advanceopensocialshare.facebookAppId != '') {
            script = script + 'facebookAppId:' + Drupal.settings.advanceopensocialshare.facebookAppId + ',';
        }
        script = script + 'providers: {top:' + JSON.stringify(providers) + '},';
        script = script + 'widgets: {top:' + JSON.stringify(widgets) + '},';

        if (Drupal.settings.advanceopensocialshare.isTotalShare != '') {
            script = script + 'isTotalShare:' + Drupal.settings.advanceopensocialshare.isTotalShare + ',';
        }
        if (Drupal.settings.advanceopensocialshare.isOpenSingleWindow != '') {
            script = script + 'isOpenSingleWindow:' + Drupal.settings.advanceopensocialshare.isOpenSingleWindow + ',';
        }        
        if (Drupal.settings.advanceopensocialshare.twittermention != '') {
            script = script + 'twittermention:' + "'" + Drupal.settings.advanceopensocialshare.twittermention + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.twitterhashtags != '') {
            script = script + 'twitterhashtag:' + "'" + Drupal.settings.advanceopensocialshare.twitterhashtags + "'" + ',';
        }       
        if (Drupal.settings.advanceopensocialshare.popupWindowSize != '') {
            script = script + 'popupWindowSize: ' + Drupal.settings.advanceopensocialshare.popupWindowSize + ',';
        } 
        if (Drupal.settings.advanceopensocialshare.isMobileFriendly != '') {
            script = script + 'isMobileFriendly:' + Drupal.settings.advanceopensocialshare.isMobileFriendly + ',';
        }
        if (Drupal.settings.advanceopensocialshare.customOption != '') {           
            script = script + Drupal.settings.advanceopensocialshare.customOption;
        }          
        script = script + '}';        

        var shareWidget = new OpenSocialShare();
        shareWidget.init((eval("(" + script + ")")));
        shareWidget.injectInterface("." + Drupal.settings.advanceopensocialshare.divwidget);
        shareWidget.setWidgetTheme("." + Drupal.settings.advanceopensocialshare.divwidget);
    }

    if (Drupal.settings.advanceopensocialshare.vertical != undefined && Drupal.settings.advanceopensocialshare.vertical) {
        var string = Drupal.settings.advanceopensocialshare.vericalProviders;
        var providers = string.split(",");

        var str = Drupal.settings.advanceopensocialshare.verticalWidgets;
        var widgets = str.split(',');     

        var vscript = '{';
        if (Drupal.settings.advanceopensocialshare.verticalEmailMessage != '') {
            vscript = vscript + 'emailMessage:' + "'" + Drupal.settings.advanceopensocialshare.verticalEmailMessage + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.verticalEmailSubject != '') {
            vscript = vscript + 'emailSubject:' + "'" + Drupal.settings.advanceopensocialshare.verticalEmailSubject + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.verticalIsEmailContentReadOnly != '') {
            vscript = vscript + 'isEmailContentReadOnly:' + Drupal.settings.advanceopensocialshare.verticalIsEmailContentReadOnly + ',';
        }              
        vscript = vscript + "isCounterWidgetTheme:" + Drupal.settings.advanceopensocialshare.verticalIsCounterWidgetTheme + ',';
        vscript = vscript + "isHorizontalCounter:" + Drupal.settings.advanceopensocialshare.verticalIsHorizontalCounter + ',';
        vscript = vscript + "isHorizontalLayout:" + Drupal.settings.advanceopensocialshare.verticalIsHorizontalLayout + ',';

        if (Drupal.settings.advanceopensocialshare.verticalWidgetIconSize != '') {
            vscript = vscript + 'widgetIconSize:' + "'" + Drupal.settings.advanceopensocialshare.verticalWidgetIconSize + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.verticalWidgetStyle != '') {
            vscript = vscript + 'widgetStyle:' + "'" + Drupal.settings.advanceopensocialshare.verticalWidgetStyle + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.verticalTheme != '') {
            vscript = vscript + 'theme:' + "'" + Drupal.settings.advanceopensocialshare.verticalTheme + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.verticalIsShortenUrl != '') {
            vscript = vscript + 'isShortenUrl:' + Drupal.settings.advanceopensocialshare.verticalIsShortenUrl + ',';
        }
        if (Drupal.settings.advanceopensocialshare.verticalFacebookAppId != '') {
            vscript = vscript + 'facebookAppId:' + "'" + Drupal.settings.advanceopensocialshare.verticalFacebookAppId + "'" + ',';
        }
        vscript = vscript + 'providers: {top:' + JSON.stringify(providers) + '},';
        vscript = vscript + 'widgets: {top:' + JSON.stringify(widgets) + '},';
        if (Drupal.settings.advanceopensocialshare.verticalIsTotalShare != '') {
            vscript = vscript + 'isTotalShare:' + Drupal.settings.advanceopensocialshare.verticalIsTotalShare + ',';
        }
        if (Drupal.settings.advanceopensocialshare.verticalIsOpenSingleWindow != '') {
            vscript = vscript + 'isOpenSingleWindow:' + Drupal.settings.advanceopensocialshare.verticalIsOpenSingleWindow + ',';
        }       
        if (Drupal.settings.advanceopensocialshare.verticalTwitterMention != '') {
            vscript = vscript + 'twittermention:' + "'" + Drupal.settings.advanceopensocialshare.verticalTwitterMention + "'" + ',';
        }
        if (Drupal.settings.advanceopensocialshare.verticalTwitterHashTags != '') {
            vscript = vscript + 'twitterhashtag:' + "'" + Drupal.settings.advanceopensocialshare.verticalTwitterHashTags + "'" + ',';
        }       
        if (Drupal.settings.advanceopensocialshare.verticalPopupWindowSize != '') {
            vscript = vscript + 'popupWindowSize: ' + Drupal.settings.advanceopensocialshare.verticalPopupWindowSize + ',';
        } 
        if (Drupal.settings.advanceopensocialshare.verticalIsMobileFriendly != '') {
            vscript = vscript + 'isMobileFriendly:' + Drupal.settings.advanceopensocialshare.verticalIsMobileFriendly + ',';
        }
        if (Drupal.settings.advanceopensocialshare.verticalCustomOption != '') {           
            vscript = vscript + Drupal.settings.advanceopensocialshare.verticalCustomOption;
        } 
        vscript = vscript + '}';

        var shareWidget = new OpenSocialShare();
        shareWidget.init((eval("(" + vscript + ")")));
        shareWidget.injectInterface("#" + Drupal.settings.advanceopensocialshare.verticalDivwidget);
        shareWidget.setWidgetTheme("#" + Drupal.settings.advanceopensocialshare.verticalDivwidget);
    }


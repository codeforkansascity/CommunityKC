CONTENTS OF THIS FILE
---------------------

 * Description
 * Requirements
 * Installation
 * Configuration
 * Support

DESCRIPTION
-----------
With this module you can easily create much of nodes with same webform
fields. It can be applicable in case of job vacancies with reply form,
kind of quality feedback control or whatever your mind suggests you.
Because you can create more than one webform-enabled content types, you
respectively can attach different default fields for each of them.

REQUIREMENTS
------------
This module requires the module:
 * Webform (https://drupal.org/project/webform) 7.x-4.1 or higher

INSTALLATION
------------
 * Install Webform module.
 * Copy the entire module directory the Drupal sites/all/modules directory.
 * Login as an administrator. Enable the module in the "Administration" »
  "Modules"

CONFIGURATION
-------------
 * Configure user permissions in Administration » People » Permissions:

   - Administer Webform Default Fields
     Grants access to the "Webform Default Fields" tab on content types
     management page. Generally an administrative permission.

   - Reset Webform components to Default
     Users with roles with the "Reset Webform components to Default"
     permission will see the "Reset" page on all webform content.

 * Create default fields for the webform content type:
   
   - Go to admin/structure/types/manage/%WEBFORM_ALLOWED_TYPE%/webform-fields
     where %WEBFORM_ALLOWED_TYPE% is content type which allow Webform module.
   
   - Add components to the Default Webform.

   - To set default Conditionals, E-mails and Form Settings for this content
     type use a tabs on webform sub-navigation

   - Create a new webform node and make sure it contains default fields
     you added before.

 * Configure exclusions for the Webform Default Fields

   - Go to /admin/structure/types/manage/%WEBFORM_ALLOWED_TYPE% in the tab
     "Webform" Webform default fields allowing for content type, to disable
     action when create a new node.

   - If you use hook_webform_node_defaults_alter() and don't want Webform
     Default Fields to overwrite the your defaults in $node->webform, you should
     add $defaults['webform_default_fields_ignore'] = TRUE in your implementing.

 * Reset existing webform to default:

   - Go to %YOUR_NODE%/webform/webform-reset where %WEBFORM_NODE% is ID of node
     which you want to reset

   - Reset components of webform implemented in "reset components" form. Check
     out a difference between components the curent webform and default webform.
     Select which components expose to reset actions (add / remove / restore).

   - Reset main webform parts implemented in "global reset" form.

SUPPORT
-------
Feel free to report bugs and propositions in our Issue Queue
http://drupal.org/project/issues/webform_default_fields

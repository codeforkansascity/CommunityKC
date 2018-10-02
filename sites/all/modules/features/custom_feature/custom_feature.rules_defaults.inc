<?php
/**
 * @file
 * custom_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function custom_feature_default_rules_configuration() {
  $items = array();
  $items['rules_map_oneall_user_to_custom_field'] = entity_import('rules_config', '{ "rules_map_oneall_user_to_custom_field" : {
      "LABEL" : "Map Oneall user to custom field",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "social_login_core" ],
      "ON" : { "social_login_core_user_insert" : [] },
      "DO" : []
    }
  }');
  $items['rules_new_account_notification'] = entity_import('rules_config', '{ "rules_new_account_notification" : {
      "LABEL" : "New Account Notification",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_insert" : [] },
      "IF" : [
        { "user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "2" : "2" } } } }
      ],
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "3" : "3", "4" : "4" } },
            "subject" : "A New User Has Registered at CommunityKC",
            "message" : "FYI A new user [account:name] registered at CommunityKC on [account:created]:\\r\\n\\r\\nYou can view and edit the account at [account:url]"
          }
        }
      ]
    }
  }');
  $items['rules_new_project_email'] = entity_import('rules_config', '{ "rules_new_project_email" : {
      "LABEL" : "New project email",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--project" : { "bundle" : "project" } },
      "DO" : [
        { "mail" : {
            "to" : "[node:author:mail]",
            "subject" : "Your CommunityKC Project Has Been Submitted for Review",
            "message" : "Thank you for submitting your project to CommunityKC, the map that connects people, projects, and resources in Kansas City.\\r\\n\\r\\nYour project has been sent to our team for review and approval. We work hard to quickly get new projects on CommunityKC, but this process may take 1-2 weeks if we have questions or need clarification on anything. We will contact you shortly if we need any additional information. \\r\\n\\r\\nHang tight and you\\u2019ll receive another notification once your project has been published or if we have questions. \\r\\n\\r\\nThanks!\\r\\nThe CommunityKC Team",
            "language" : [ "" ]
          }
        },
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "3" : "3" } },
            "subject" : "A new project has been submitted to CommunityKC!",
            "message" : "A new project has been submitted to CommuntyKC! To view the submission please visit \\r\\n\\r\\n[node:url]\\r\\n\\r\\nLogin and click \\u0022edit\\u0022 on the project page. There you can make any necessary changes. To publish the project scroll to the bottom, select the \\u0022publishing options\\u0022 link and check the \\u0022published\\u0022 box before saving."
          }
        }
      ]
    }
  }');
  $items['rules_send_6_month_followup_email'] = entity_import('rules_config', '{ "rules_send_6_month_followup_email" : {
      "LABEL" : "Send 6 month followup email",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_update--project" : { "bundle" : "project" } },
      "DO" : []
    }
  }');
  $items['rules_send_email_when_project_is_published'] = entity_import('rules_config', '{ "rules_send_email_when_project_is_published" : {
      "LABEL" : "Send email when project is published",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_update--project" : { "bundle" : "project" } },
      "IF" : [
        { "data_is" : { "data" : [ "node-unchanged:status" ], "value" : "0" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[node:author:mail],[node:field-lead-contact-email]",
            "subject" : "Your project has been published on CommunityKC!",
            "message" : "Congratulations! Your CommunityKC project has been approved and is now live! You can view your project page at [node:url]. Be sure to review your project information as we may have made some minor edits. Please let us know if any of our potential revisions do not accurately depict your project.\\r\\n\\r\\nKeep your project up to date! To update your project, login using your username ([node:author]) and password then select your project to edit. We\\u2019ll help you keep your project information up-to-date by sending you a reminder email in 6 months and again in 1 year. \\r\\n\\r\\nShare your project with others! You can share your project page via email or on Facebook, Twitter, Pinterest, LinkedIn, or Google+. Simply go to your project page and click on those icons in the right sidebar. \\r\\n\\r\\nLearn about other projects! You will receive notifications when other projects of the same category are added and when other projects are added in your area.\\r\\n\\r\\nLet us know if you have questions at any time! We can be reached at info@communitykc.org or 816-502-9584.\\r\\n\\r\\nThe Community KC Team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_volunteer_notification'] = entity_import('rules_config', '{ "rules_volunteer_notification" : {
      "LABEL" : "Volunteer Notification",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "entityform" ],
      "ON" : { "entityform_insert" : [] },
      "DO" : []
    }
  }');
  return $items;
}

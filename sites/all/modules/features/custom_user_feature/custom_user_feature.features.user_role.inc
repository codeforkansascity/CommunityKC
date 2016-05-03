<?php
/**
 * @file
 * custom_user_feature.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function custom_user_feature_user_default_roles() {
  $roles = array();

  // Exported role: admin.
  $roles['admin'] = array(
    'name' => 'admin',
    'weight' => 3,
  );

  // Exported role: communitykc.
  $roles['communitykc'] = array(
    'name' => 'communitykc',
    'weight' => 2,
  );

  return $roles;
}

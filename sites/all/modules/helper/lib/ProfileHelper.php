<?php

class ProfileHelper {
  public static function installVariables(array $variables) {
    foreach ($variables as $name => $value) {
      variable_set($name, $value);
    }
  }

  public static function installBlocks(array $blocks, $theme = NULL) {
    if (!isset($theme)) {
      $theme = variable_get('theme_default', 'bartik');
    }

    $query = db_insert('block');
    $query->fields(array('module', 'delta', 'theme', 'status', 'weight', 'region', 'visibility', 'pages', 'title', 'cache'));
    foreach ($blocks as $block) {
      $block += array(
        'theme' => $theme,
        'status' => 1,
        'weight' => 0,
        'visibility' => BLOCK_VISIBILITY_NOTLISTED,
        'pages' => '',
        'title' => '',
        'cache' => DRUPAL_NO_CACHE,
      );
      $query->values($block);
    }

    if (!empty($blocks)) {
      $query->execute();
    }
  }

  public static function installFields(array $fields) {
    foreach ($fields as $index => $field) {
      if (field_info_field($field['field_name'])) {
        continue;
      }
      $fields[$index] = field_create_field($field);
    }
    return $fields;
  }
}

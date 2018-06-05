<?php

class FeaturesHelper {

  /**
   * @deprecated
   *
   * Use features_revert_module($module) instead.
   */
  public static function revert(array $modules, $force = FALSE) {
    module_load_include('inc', 'features', 'features.export');
    features_include(TRUE);

    $items = array();
    $states = features_get_component_states($modules, TRUE, TRUE);
    $restore_states = array(FEATURES_OVERRIDDEN, FEATURES_REBUILDABLE, FEATURES_NEEDS_REVIEW);
    foreach ($states as $module_name => $components) {
      foreach ($components as $component => $state) {
        if ($force || in_array($state, $restore_states)) {
          if (!isset($items[$module_name])) {
            $items[$module_name] = array();
          }
          $items[$module_name][] = $component;
        }
      }
    }

    if (!empty($items)) {
      return features_revert($items);
    }
  }

  public static function revertAll($force = FALSE, array $features_to_exclude = array()) {
    module_load_include('inc', 'features', 'features.export');

    $modules = array();
    foreach (features_get_features(NULL, TRUE) as $module) {
      if ($module->status && !in_array($module->name, $features_to_exclude)) {
        // If forced, add module regardless of status.
        if ($force) {
          $modules[] = $module->name;
        }
        else {
          switch (features_get_storage($module->name)) {
            case FEATURES_OVERRIDDEN:
            case FEATURES_NEEDS_REVIEW:
            case FEATURES_REBUILDABLE:
              $modules[] = $module->name;
              break;
          }
        }
      }
    }

    if (!empty($modules)) {
      static::revert($modules, $force);
    }
  }
}

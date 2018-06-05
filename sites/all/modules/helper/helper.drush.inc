<?php

/**
 * @file
 * Drush integration for the Helper module.
 */

/**
 * Implements hook_drush_cache_clear().
 */
function helper_drush_cache_clear(&$types) {
  $types['bootstrap'] = 'helper_drush_cache_clear_bootstrap';
  // @todo Remove when http://drupal.org/node/1899468 is fixed.
  if (drush_has_boostrapped(DRUSH_BOOTSTRAP_DRUPAL_FULL)) {
    $types['entity'] = 'helper_drush_cache_clear_entity';
    $types['field'] = 'field_cache_clear';
    if (function_exists('module_exists') && module_exists('migrate')) {
      $types['migrate'] = 'helper_drush_cache_clear_migrate';
    }
    if (function_exists('module_exists') && module_exists('views')) {
      $types['views'] = 'views_invalidate_cache';
    }
  }
}

/**
 * Clears the bootstrap cache.
 */
function helper_drush_cache_clear_bootstrap() {
  cache_clear_all('*', 'cache_bootstrap', TRUE);
}

/**
 * Clears entity-related caches.
 */
function helper_drush_cache_clear_entity() {
  entity_info_cache_clear();

  if (module_exists('entitycache')) {
    $tables = module_invoke('entitycache', 'flush_caches');
    foreach ($tables as $table) {
      cache_clear_all('*', $table, TRUE);
    }
  }
}

/**
 * Clears the migrate cache (and the registry cache).
 */
function helper_drush_cache_clear_migrate() {
  registry_rebuild();
  migrate_static_registration();
  cache_clear_all('migrate', 'cache', TRUE);
}

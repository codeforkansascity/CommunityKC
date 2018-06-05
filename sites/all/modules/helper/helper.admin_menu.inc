<?php

/**
 * @file
 * Administration menu integration for the Helper module.
 */

/**
 * Implements hook_admin_menu_cache_info().
 */
function helper_admin_menu_cache_info() {
  $caches['bootstrap'] = array(
    'title' => t('Bootstrap'),
    'callback' => 'helper_admin_menu_cache_flush_bootstrap',
  );
  $caches['entity'] = array(
    'title' => t('Entity'),
    'callback' => 'helper_admin_menu_cache_flush_entity',
  );
  $caches['field'] = array(
    'title' => t('Field'),
    'callback' => 'field_cache_clear',
  );
  if (module_exists('migrate')) {
    $caches['migrate'] = array(
      'title' => t('Migrate'),
      'callback' => 'helper_admin_menu_cache_flush_migrate',
    );
  }
  if (module_exists('views')) {
    $caches['views'] = array(
      'title' => t('Views'),
      'callback' => 'views_invalidate_cache',
    );
  }
  return $caches;
}

/**
 * Cache callback to clear entity-related caches.
 */
function helper_admin_menu_cache_flush_entity() {
  entity_info_cache_clear();

  if (module_exists('entitycache')) {
    $tables = module_invoke('entitycache', 'flush_caches');
    foreach ($tables as $table) {
      cache_clear_all('*', $table, TRUE);
    }
  }
}

/**
 * Cache callback to clear the bootstrap cache.
 */
function helper_admin_menu_cache_flush_bootstrap() {
  cache_clear_all('*', 'cache_bootstrap', TRUE);
}

/**
 * Cache callback to clear the migrate cache.
 */
function helper_admin_menu_cache_flush_migrate() {
  registry_rebuild();
  migrate_static_registration();
  cache_clear_all('migrate', 'cache', TRUE);
}

/**
 * Implements hook_admin_menu_output_alter().
 */
function helper_admin_menu_output_alter(array &$content) {
  // For older 7.x-3.x versions of admin_menu, show the entire devel menu.
  // @see http://drupal.org/node/1899474 is fixed.
  if (isset($content['icon']['icon']['devel-variables'])) {
    unset($content['icon']['icon']['devel-variables']);
    if (module_exists('devel')) {
      $devel_tree = menu_tree_all_data('devel');
      if ($devel_tree = admin_menu_links_menu($devel_tree)) {
        $content['icon']['icon']['devel'] = array(
          '#title' => t('Devel'),
          '#href' => '#',
          '#options' => array(
            'external' => TRUE,
          ),
        ) + $devel_tree;
      }
    }
  }
}

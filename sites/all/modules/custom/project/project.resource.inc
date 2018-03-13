<?php

function custom_project_resource_index($neighborhood = 0, $project_type = 0) {
  /* // making sure we're getting params passed
    watchdog('custom', 'custom_project_resource_index called !neighborhood, !project_type ', array(
    '!neighborhood' => $neighborhood,
    '!project_type' => $project_type
  ), WATCHDOG_DEBUG); */
  $cacheId = custom_project_get_cache_key($neighborhood, $project_type);
	$geoData = cache_get($cacheId);
	if ($geoData === false) {
		$geoData = (new GeoJsonService())->getProjectsGeoJson(FALSE, $project_type, $neighborhood);
		cache_set($cacheId, $geoData, 'cache', CACHE_TEMPORARY);
	} else {
		$geoData = $geoData->data;
	}
	return $geoData;
}

/**
 * Makes a cache key for a neighborhood and project tpye combination.
 */
function custom_project_get_cache_key($nh, $pt) {
  $key = 'projects_geojson';
  if ($nh) {
    $key .= 'n'. $nh;
  }
  if ($pt) {
    $key .= 'p' . $pt;
  }
  return $key;
}

function custom_project_type_resource_index() {
  // this is bad
  define('PROJECT_TYPE_VOCABULARY_ID', 2);
  $project_types = array_map('_custom_project_type_simplify_taxonomy',
    taxonomy_get_tree(PROJECT_TYPE_VOCABULARY_ID));
  $root = array();
  foreach($project_types as $pt) {
    if ($pt['parent'] == 0) {
      $root[$pt['tid']] = array('tid'=>$pt['tid'], 'name' => $pt['name'], 'children' => array());
    }
  }
  foreach($project_types as $pt ) {
    if ($pt['parent'] != 0) {
      $root[$pt['parent']]['children'][] = array('tid'=>$pt['tid'], 'name' => $pt['name'], 'children' => array());
    }
  }
  $noids = array();
  foreach($root as $item) {
    $noids[] = $item;
  }

  return $noids;
}

function _custom_project_type_simplify_taxonomy($obj) {
  return array('tid' => $obj->tid, 'name' => $obj->name, 'parent' => $obj->parents[0]);
}

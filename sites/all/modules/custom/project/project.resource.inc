<?php

function custom_project_resource_index() {
  $cacheId = 'projects_geojson';
	$geoData = cache_get($cacheId);
	if ($geoData === false) {
		$geoData = (new GeoJsonService())->getProjectsGeoJson();
		cache_set($cacheId, $geoData, 'cache', CACHE_TEMPORARY);
	} else {
		$geoData = $geoData->data;
	}
	return $geoData;
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

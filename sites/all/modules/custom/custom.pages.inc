<?php


function _custom_page_geojson_map() {
	drupal_add_http_header('Content-Type', 'application/json', false);
	
	$cacheId = 'projects_geojson';
	$geoData = cache_get($cacheId);
	if ($geoData === false) {
		$geoData = (new GeoJsonService())->getProjectsGeoJson();
		cache_set($cacheId, $geoData, 'cache', CACHE_TEMPORARY);
	} else {
		$geoData = $geoData->data;
	}
	
	echo json_encode($geoData);
}
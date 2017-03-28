<?php


function _custom_page_geojson_map() {
	drupal_add_http_header('Content-Type', 'application/json', false);
	$geoData = (new GeoJsonService())->getProjectsGeoJson();
	echo json_encode($geoData);
}
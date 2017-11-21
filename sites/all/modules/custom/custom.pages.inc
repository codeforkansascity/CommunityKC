<?php


function _custom_page_geojson_map() {
	drupal_add_http_header('Content-Type', 'application/json', false);
	drupal_add_http_header('Access-Control-Allow-Origin', '*', false);

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

function _custom_page_newmap_js() {
/*<link rel="stylesheet" href="//api.tiles.mapbox.com/mapbox.js/v2.2.3/mapbox.css">
      <link rel="stylesheet" href="//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/MarkerCluster.css">
      <link rel="stylesheet" href="//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/MarkerCluster.Default.css">
      <link rel="stylesheet" href="//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-locatecontrol/v0.43.0/L.Control.Locate.mapbox.css">*/
  drupal_add_css(
    '//api.tiles.mapbox.com/mapbox.js/v2.2.3/mapbox.css',
    array('type' => 'external')
  );
  drupal_add_css(
    '//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/MarkerCluster.css',
    array('type' => 'external')
  );
  drupal_add_css(
    '//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-locatecontrol/v0.43.0/L.Control.Locate.mapbox.css',
    array('type' => 'external')
  );
  /*
  /*<script src="//api.tiles.mapbox.com/mapbox.js/v2.2.3/mapbox.js"></script>
<script src="//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-omnivore/v0.2.0/leaflet-omnivore.min.js"></script>
<script src="//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/leaflet.markercluster.js"></script>
<script src="//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-locatecontrol/v0.43.0/L.Control.Locate.min.js"></script>
*/
  drupal_add_js(
    '//api.tiles.mapbox.com/mapbox.js/v2.2.3/mapbox.js',
    array('type' => 'external')
  );
  drupal_add_js(
    '//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-omnivore/v0.2.0/leaflet-omnivore.min.js',
    array('type' => 'external')
  );
  drupal_add_js(
    '//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/leaflet.markercluster.js',
    array('type' => 'external')
  );
  drupal_add_js(
    '//api.tiles.mapbox.com/mapbox.js/plugins/leaflet-locatecontrol/v0.43.0/L.Control.Locate.min.js',
    array('type' => 'external')
  );
  drupal_add_js(
    '/sites/all/modules/custom/js/ckc-map.js',
    array('type' => 'file')
  );
  /*
  drupal_add_js(
    'custom_js_initializeMap();',
    array('type' => 'inline')
  );
*/
  $page = array();
  $page['markup'] = array(
    '#markup' => ' <div id="mapContainer" style="height: 600px; width: 100%; display: block"></div>
    <script type="text/javascript">custom_js_initializeMap();</script>'
  );
  return $page;
}

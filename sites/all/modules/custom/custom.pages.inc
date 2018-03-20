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
  drupal_add_css(
    '/sites/all/modules/custom/css/ckc-map.css',
    array('type' => 'file')
  );
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

  drupal_add_js("misc/autocomplete.js");
  drupal_add_js("misc/ahah.js");

  $page = array();
  $page['markup'] = array(
    '#markup' => '
    <div class="view-header">
      <div class="toggle"><a href="list">Go to List View</a></div>
    </div>
    <div class="view-filters">
      <div>
      <form id="custom_map_form" method="POST" action="" onsubmit="custom_js_initializeMap();return false;">
        <div class="views-exposed-form">
          <div class="views-exposed-widgets clearfix">
            <div class="views-exposed-widget" style="z-index:100">
              <label>Neighborhood Name</label> <input id="edit-field-neighborhood-tid" type="text" class="form-text form-autocomplete" autocomplete="OFF" size="60" maxlength="128" name="neighborhood">
              <input class="autocomplete" type="hidden" id="edit-field-neighborhood-tid-autocomplete"
              value="/admin/views/ajax/autocomplete/taxonomy/1" disabled="disabled" />
            </div>
            <div class="views-exposed-widget">
              <label>Project Type</label> <select id="project_type" name="project_type" ><option value="">- Any</select>
            </div>
            <div class="views-exposed-widget">
              <input type="button" onclick="custom_js_initializeMap(this);return false;" value="submit" class="form-submit" />
            </div>
          </div>
        </div>
        </form>
      </div>
    </div>
    <div id="mapContainer" class="view-content" style="height: 600px; width: 100%; display: block"></div>
    <script type="text/javascript">custom_js_loadProjectTypes(); custom_js_initializeMap();</script>'
  );
  return $page;
}

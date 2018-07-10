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

/**
 * Custom version of the event add page - allows us to show a login to anonymous users
 * todo: move to event module
 */
function _custom_event_add_page() {
  global $user;
  $page = array();
  drupal_set_title('Submit an Event');
  // terms & conditions disclaimer
  $page['terms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Terms &amp; Conditions'),
    'term_content' => array(
      '#prefix' => '<p>',
      '#markup' => t('Please read the following privacy statement and check the box below if you agree to its terms and conditions. *
      All event information submitted through this form will be entered into our database by CommunityKC facilitators.
      The data will be displayed on the public web site www.communitykc.org except for the name, email, and phone number of the person
       providing the information in this questionnaire. All other information will become public as of January 31, 2015 and may be linked
       to third-party websites for reference. In the next few weeks you will receive an email to verify the accuracy of the information
       submitted through this form. If you wish to update, edit, or delete any information for your event, please email communitykc@gmail.com
        with the name of the project and your request.'),
      '#suffix' => '</p>',
    )
  );

  if (!$user || $user->uid === 0) {
    $page['msg'] = array(
      '#prefix' => '<p>',
      '#markup' => t('You will need to login or register for an account to submit an event.'),
      '#suffic' => '</p>',
    );
    $login_form = drupal_get_form('user_login_block');
    $page['login'] = $login_form;
  }
  else {
    module_load_include('inc', 'node', 'node.pages');
    $node_form = new stdClass;
    $node_form->type = 'event';
    $node_form->language = LANGUAGE_NONE;
    $form = drupal_get_form('event_node_form', $node_form);
    $page['add_form'] = $form;
  }
  return $page;
}

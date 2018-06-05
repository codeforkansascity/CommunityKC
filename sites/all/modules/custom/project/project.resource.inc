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
 * Returns a cleaned up project data structure for json
 */
function custom_project_resource_retrieve($project_id) {

  if ($project_id && ctype_digit($project_id)) {
    $node = node_load($project_id);
    if ($node && $node->type == 'project' && $node->status == '1') {
      $p = entity_metadata_wrapper('node',$node); // wrapper for the node via entity api
      $proj = new stdClass;
      $proj->name = $p->label();
      $proj->id = $p->getIdentifier();
      $proj->description = $p->body->value->value(array('decode' => TRUE));
      $proj->author_name = $p->field_your_name->value() ?: '';
      $proj->website = $p->field_project_website->value() ?: '';
      $proj->year_established = $p->field_year_established->value() ?: '';
      $proj->phase = $p->field_phase->value() ?: '';
      $proj->partners = $p->field_partners->value() ?: array();
      // neighborhood format needs to be cleaned up
      $neighborhoods = $p->field_neighborhood->value() ?: array();
      $neighborhoods_simplified = array();
      foreach($neighborhoods as $n) {
        $simple = new stdClass();
        $simple->name = $n->name;
        $simple->id = $n->tid;
        $neighborhoods_simplified[] = $simple;
      }
      $proj->neighborhoods = $neighborhoods_simplified;
      $proj->organization = $p->field_organization_name->value() ?: '';
      $proj->organizaiton_url_or_phone = $p->field_organization_website_or_ph->value()['value'] ?: '';
      $proj->organization_type = $p->field_organization_type->value() ?: '';
      $proj->lead_contact_name = $p->field_lead_contact_person->value() ?: '';
      $proj->lead_contact_email = $p->field_lead_contact_email->value()['value'] ?: '';
      // address fields all need to be renamed and simplified.
      $address = $p->field_address->value() ?: '';
      $simplified_address = new stdClass();
      $simplified_address->street = $address['thoroughfare'] ?: '';
      $simplified_address->street2 = $address['premise'] ?: '';
      $simplified_address->city = $address['locality'] ?: '';
      $simplified_address->state = $address['administrative_area'] ?: '';
      $simplified_address->zip = $address['postal_code'] ?: '';
      $simplified_address->country = $address['country'] ?: '';
      $proj->address = $simplified_address;
      $proj_types = $p->field_project_type->value() ?: array();
      $proj_types_simplified = array();
      foreach ($proj_types as $pt) {
        $simple = new stdClass();
        $simple->name = $pt->name;
        $simple->id = $pt->tid;
        $proj_types_simplified[] = $simple;
      }
      $proj->project_types = $proj_types_simplified;
      $proj->photos = $p->field_photos->value() ?: array();
      $proj->funder = $p->field_funder->value() ?: '';
      $proj->needs = $p->field_project_needs->value() ?: '';
      $proj->area_wide_info = $p->field_if_your_project_is_area_wi->value() ?: '';
      // possibly add created and updated dates?
      return $proj;
    }
  }
  return array('error' => 'Not a valid project id');
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

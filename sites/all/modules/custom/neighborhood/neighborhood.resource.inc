<?php

/**
 * returns list of neighborhood with their TIDs
 *
 * @return void
 */
function custom_neighborhood_resource_index() {
  define('NEIGHBORHOOD_VOCABULARY_ID',1);
  $neighborhoods = array_map('_custom_neighborhood_simplify_taxonomy',
    taxonomy_get_tree(NEIGHBORHOOD_VOCABULARY_ID));
  return $neighborhoods;
}

/**
 * Returns just the tid and name of a neighborhood for data to be more json-friendly
 *
 * @param [stdClass] neighborhood returned from taxonomy_get_tree()
 * @return array with `tid` and `name` keys
 */
function _custom_neighborhood_simplify_taxonomy($obj) {
  return array('tid' => $obj->tid, 'name' => $obj->name, 'parent' => $obj->parents[0]);
}

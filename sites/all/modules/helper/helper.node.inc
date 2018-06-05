<?php

/**
 * @file
 * Node hooks implemented by the Helper module.
 */

/**
 * Implements hook_node_load().
 */
function helper_node_load(array $nodes) {
  // Add an unpublished comment count property to loaded nodes.
  if (module_exists('comment') && helper_is_tweak_enabled('node_comment_unpublished_count')) {
    $unpublished_counts = db_query('SELECT nid, COUNT(cid) FROM {comment} WHERE nid IN (:nids) AND status = :status GROUP BY nid', array(
      ':nids' => array_keys($nodes),
      ':status' => COMMENT_NOT_PUBLISHED,
    ))->fetchAllKeyed();
    $unpublished_counts += array_fill_keys(array_keys($nodes), 0);
    foreach ($nodes as $node) {
      $node->comment_unpublished_count = $unpublished_counts[$node->nid];
    }
  }
}

/**
 * Implements hook_node_view().
 */
function helper_node_view($node, $view_mode, $langcode) {
  // Add an unpublished comment summary link to the node.
  if (module_exists('comment') && helper_is_tweak_enabled('node_comment_unpublished_count') && $view_mode == 'teaser' && !empty($node->comment_unpublished_count)) {
    _helper_node_add_unpublished_comments_link($node, $langcode);
  }
}

/**
 * Add the number of unpublished comments as a link on a node.
 *
 * @param object $node
 *   A node object.
 * @param string $langcode
 *   The language code to use when displaying the link.
 */
function _helper_node_add_unpublished_comments_link($node, $langcode) {
  if ($node->comment != COMMENT_NODE_HIDDEN && user_access('administer comments') && !empty($node->comment_unpublished_count)) {
    $node->content['links']['comment']['#links']['comment-unpublished-comments'] = array(
      'title' => format_plural($node->comment_unpublished_count, '1 unpublished comment', '@count unpublished comments', array(), array('langcode' => $langcode)),
      'href' => "node/$node->nid",
      'fragment' => 'comments',
    );
  }
}

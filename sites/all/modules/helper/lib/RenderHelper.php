<?php

class RenderHelper {

  /**
   * Rewrite #states selectors.
   *
   * @param array $elements
   *   A renderable array element having a #states property.
   * @param string $search
   *   A partial or entire jQuery selector string to replace in #states.
   * @param string $replace
   *   The string to replace all instances of $search with.
   */
  public static function rewriteStatesSelector(array &$elements, $search, $replace) {
    if (!empty($elements['#states'])) {
      foreach ($elements['#states'] as $state => $ids) {
        foreach ($ids as $id => $value) {
          if (strpos($id, $search) !== FALSE) {
            $new_id = str_replace($search, $replace, $id);
            $elements['#states'][$state][$new_id] = $value;
            unset($elements['#states'][$state][$id]);
          }
        }
      }
    }
    foreach (element_children($elements) as $key) {
      static::rewriteStatesSelector($elements[$key], $search, $replace);
    }
  }

  public static function filterElementChildren(array $elements) {
    return array_intersect_key($elements, array_flip(element_children($elements)));
  }

  public static function filterVisibleElementChildren(array $elements) {
    return array_intersect_key($elements, array_flip(element_get_visible_children($elements)));
  }

  /**
   * Render a specific block.
   *
   * @param string $module
   *   The module machine name.
   * @param string $delta
   *   The block delta.
   *
   * @return array
   *   The render array of the block output.
   */
  public static function viewBlock($module, $delta) {
    $block = new stdClass();
    $block->module = $module;
    $block->delta = $delta;
    $block->enabled = TRUE;
    $block->page_match = TRUE;
    $blocks = array();
    $blocks[$module . "_" . $delta] = $block;
    $block_content = _block_render_blocks($blocks);
    return _block_get_renderable_array($block_content);
  }
}

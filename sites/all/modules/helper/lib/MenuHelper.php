<?php

class MenuHelper {

  /**
   * Create menu links.
   *
   * @param array $links
   *   An array of menu link arrays.
   * @param array $defaults
   *   An array of defaults to use for each link. This avoids having to repeat
   *   values in each menu link, like 'menu_name' for example.
   */
  public static function createLinks(array &$links, array $defaults = array()) {
    foreach ($links as &$link) {
      $link += $defaults;
      if (!url_is_external($link['link_path'])) {
        $link['link_path'] = drupal_get_normal_path($link['link_path']);
      }
      if ($mlid = menu_link_save($link)) {
        $link['mlid'] = $mlid;
        if (!empty($link['children'])) {
          static::createLinks($link['children'], array('plid' => $mlid) + $defaults);
        }
      }
      else {
        // Add error logging.
      }
    }
  }

}

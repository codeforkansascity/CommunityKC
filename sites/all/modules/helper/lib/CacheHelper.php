<?php

class CacheHelper {

  /**
   * A copy of cache_get() that respects expiration.
   *
   * @see http://drupal.org/node/534092
   */
  public static function get($cid, $bin = 'cache') {
    if ($cache = cache_get($cid, $bin)) {
      if (!static::isCacheUnexpired($cache)) {
        return FALSE;
      }
    }
    return $cache;
  }

  /**
   * A copy of cache_get_multiple() that respects expiration.
   *
   * @see http://drupal.org/node/534092
   */
  public static function getMultiple(array &$cids, $bin = 'cache') {
    $cache = cache_get_multiple($cids, $bin);
    return array_filter($cache, array(get_called_class(), 'isCacheUnexpired'));
  }

  /**
   * Check if a cache record is expired or not.
   *
   * Callback for array_filter() within CacheHelper::get() and
   * CacheHelper::getMultiple().
   *
   * @param object $cache
   *   A cache object from cache_get().
   *
   * @return bool
   *   TRUE if the cache record has not yet expired, or FALSE otherwise.
   */
  public static function isCacheUnexpired($cache) {
    if ($cache->expire > 0 && $cache->expire < REQUEST_TIME) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * A copy of cache_set() that allows multiple values to be set at once.
   *
   * @param array $data
   *   An array of values to cache, keyed by the cache ID of the data to store
   *   (cid).
   * @param string $bin
   *   The cache bin to store the data in.
   * @param int $expire
   *   The expiration value to pass to cache_set().
   */
  public static function setMultiple(array $data, $bin = 'cache', $expire = CACHE_PERMANENT) {
    foreach ($data as $cid => $value) {
      cache_set($cid, $value, $bin, $expire);
    }
  }

  /**
   * Deprecated.
   */
  public static function httpRequest($url, array $options = array()) {
    return HttpHelper::cachedRequest($url, $options);
  }
}

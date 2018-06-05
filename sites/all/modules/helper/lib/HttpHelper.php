<?php

class HttpHelper {

  public static function cachedRequest($url, array $options = array(), $cache_errors = FALSE) {
    $cid = static::cachedRequestGetCid($url, $options);
    $bin = isset($options['cache']['bin']) ? $options['cache']['bin'] : 'cache';

    if ($cid && $cache = CacheHelper::get($cid, $bin)) {
      return $cache->data;
    }
    else {
      $response = drupal_http_request($url, $options);
      $response->request_url = $url;
      $response->request_options = $options;

      if (!empty($response->error)) {
        trigger_error("Error on request to {$url}: {$response->code} {$response->error}.", E_USER_WARNING);
      }

      if (!$cache_errors && !empty($response->error)) {
        $cid = FALSE;
      }
      if ($cid) {
        $expire = static::cachedRequestGetExpire($response, $options);
        if ($expire !== FALSE) {
          cache_set($cid, $response, $bin, $expire);
        }
      }
      return $response;
    }
  }

  public static function cachedRequestGetCid($url, array $options) {
    if (isset($options['cache']) && $options['cache'] === FALSE) {
      return FALSE;
    }
    elseif (isset($options['method']) && !in_array($options['method'], array('GET', 'HEAD'))) {
      // Only cache GET and HEAD methods.
      return FALSE;
    }
    elseif (isset($options['cache']['cid'])) {
      return $options['cache']['cid'];
    }
    $cid_parts = array($url, serialize(array_diff_key($options, array('cache' => ''))));
    return 'http-request:' . drupal_hash_base64(serialize($cid_parts));
  }

  public static function cachedRequestGetExpire($response, $options) {
    if (isset($options['cache']['expire'])) {
      return $options['cache']['expire'];
    }
    elseif (!empty($response->headers['cache-control']) && strpos($response->headers['cache-control'], 'no-cache') !== FALSE) {
      // Respect the Cache-Control: no-cache header.
      return FALSE;
    }
    elseif (!empty($response->headers['cache-control']) && preg_match('/max-age=(\d+)/', $response->headers['cache-control'], $matches)) {
      // Respect the Cache-Control: max-age=SECONDS header.
      return REQUEST_TIME + $matches[1];
    }
    elseif (!empty($response->headers['expires']) && $expire = strtotime($response->headers['expires'])) {
      return $expire;
    }
    else {
      return CACHE_TEMPORARY;
    }
  }

  public static function getJson($url, array $options = array()) {
    $data = NULL;
    $response = static::cachedRequest($url, $options);
    if (empty($response->error)) {
      $data = drupal_json_decode($response->data);
      if ($data === FALSE) {
        trigger_error("Unable to decode JSON response from {$url}.", E_USER_WARNING);
      }
    }
    return $data;
  }
}

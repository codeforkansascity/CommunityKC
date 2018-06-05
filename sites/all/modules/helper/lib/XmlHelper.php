<?php

class XmlHelper {

  /**
   * Convert a string of XML to an associative array.
   *
   * The converse of format_xml_elements().
   *
   * @param string|SimpleXmlElement $data
   *   The XML data to parse.
   * @param array $options
   *
   * @return array|bool
   *   An array representing the XML data, or FALSE if there was a failure.
   */
  public static function parseElements($data, array $options = array()) {
    $xml = static::normalizeDataToSimpleXml($data);

    $options += array(
      'simplify' => TRUE,
      'namespaces' => $xml->getNamespaces(TRUE),
    );

    $results = array(static::parseElement($xml, $options));
    if (!empty($options['simplify'])) {
      static::simplifyElements($results);
    }

    return $results;
  }

  public static function parseElement(SimpleXMLElement $element, array $options = array()) {
    $options += array(
      'simplify' => TRUE,
      'namespaces' => $element->getNamespaces(TRUE),
    );

    $result = array();
    $result['key'] = $element->getName();
    if (!empty($options['prefix'])) {
      $result['key'] = $options['prefix'] . ':' . $result['key'];
    }

    foreach ($element->attributes() as $attribute_key => $attribute_value) {
      $result['attributes'][$attribute_key] = (string) $attribute_value;
    }

    if (!empty($options['namespaces'])) {
      foreach (array_keys($options['namespaces']) as $namespace) {
        foreach ($element->attributes($namespace, TRUE) as $attribute_key => $attribute_value) {
          $result['attributes'][$namespace . ':' . $attribute_key] = (string) $attribute_value;
        }
      }
    }

    $children = array();
    foreach ($element->children() as $child) {
      $children[] = static::parseElement($child, $options);
    }
    if (!empty($options['namespaces'])) {
      foreach (array_keys($options['namespaces']) as $namespace) {
        foreach ($element->children($namespace, TRUE) as $child) {
          $children[] = static::parseElement($child, array('prefix' => $namespace) + $options);
        }
      }
    }

    if (!empty($children)) {
      if (!empty($options['simplify'])) {
        static::simplifyElements($children);
      }
      $result['value'] = $children;
    }
    else {
      $result['value'] = (string) $element;
      if (!empty($options['simplify'])) {
        $result['value'] = trim($result['value']);
      }
    }

    return $result;
  }

  public static function simplifyElements(array &$elements) {
    $key_indexes = array();
    foreach ($elements as $index => $element) {
      $key_indexes[$element['key']][] = $index;
    }

    foreach ($elements as $index => $element) {
      if (!is_numeric($index) || !is_array($element) || !isset($element['key'])) {
        continue;
      }
      if (count($key_indexes[$element['key']]) > 1) {
        continue;
      }

      if (!empty($element['attributes'])) {
        continue;
      }

      // Replace it in the array.
      $elements = ArrayHelper::spliceAssociativeValues($elements, array($element['key'] => $element['value']), $index);
      unset($elements[$index]);
    }
  }

  public static function convertToSimpleArray($data) {
    $xml = static::normalizeDataToSimpleXml($data);
    $array = json_decode(json_encode((array) $xml), 1);
    return array($xml->getName() => $array);
  }

  public static function normalizeDataToSimpleXml($data, $class_name = NULL, $options = LIBXML_NOCDATA) {
    if (is_object($data) && is_a($data, 'SimpleXMLElement')) {
      return $data;
    }
    elseif (is_file($data) || valid_url($data, TRUE)) {
      $xml = simplexml_load_file($data, $class_name, $options);
      if ($xml === FALSE) {
        throw new Exception("Unable to parse XML from $data");
      }
      else {
        return $xml;
      }
    }
    else {
      $xml = simplexml_load_string((string) render($data), $class_name, $options);
      if ($xml === FALSE) {
        throw new Exception("Unable to parse XML");
      }
      else {
        return $xml;
      }
    }
  }

}

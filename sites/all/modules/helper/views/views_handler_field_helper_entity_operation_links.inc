<?php

class views_handler_field_helper_entity_operation_links extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['alter']['path'] = array('#access' => FALSE);
    $form['alter']['external'] = array('#access' => FALSE);
  }

  function render($values) {
    if ($entity = $this->get_value($values)) {
      $links = EntityHelper::getOperationLinks($this->entity_type, $entity);
      return drupal_render($links);
    }
  }
}

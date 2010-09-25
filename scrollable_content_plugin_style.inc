<?php
// $Id$
/**
 * @file
 *  Provide the views scrollable plugin object with default options and form.
 */

/**
  * Implementation of views_plugin_style().
  */
class scrollable_content_plugin_style extends views_plugin_style {
/*
  function option_definition() {
    $options = parent::option_definition();
dprint_r($options);
    //$this->get_form($options);

    return $options;
  }
*/
  function options(&$options) {
    $defaults = scrollable_content_fields_init();

    foreach ($defaults as $key => $value) {
      $options[$key] = $value;
    }
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $this->get_form($form);
  }

  function get_form(&$form) {
    $full_form = scrollable_content_form('view', $this);

    $fieldsets = array();
    $fieldsets[] = $full_form['scrollable_content_settings'];
    $fieldsets[] = $full_form['scrollable_content_theme'];

    foreach ($fieldsets as $fieldset) {
      foreach ($fieldset as $key => $val) {
        if (is_array($val)) {
          $form[$key] = $fieldset[$key];
        }
      }
    }

    return $form;
  }
}
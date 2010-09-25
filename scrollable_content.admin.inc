<?php
// $Id$

/**
 * @file
 * Admin page callbacks for the Scrollable Content module.
 */

/**
 * Builds and returns the Scrollable Content settings form.
 */
function scrollable_content_admin_settings() {
  // Scrollable source settings
  $form['scrollable_source'] = array(
    '#type' => 'fieldset',
    '#weight' => -40,
    '#title' => t('Scrollable source'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

    // Node types
    $types = array_map('check_plain', node_get_types('names'));
	  if (!empty($types)) {
      $form['scrollable_source']['scrollable_source_types'] = array(
        '#type' => 'select',
        '#title' => t('Only from type(s)'),
        '#options' => $types,
        '#multiple' => TRUE,
        '#default_value' => variable_get('scrollable_source_types', 'scrollable'),
        '#description' => t('The content type(s) that you want to display as sliding content.'),
      );
    }

    // Taxonomy box
    if (module_exists('taxonomy')) {
      $taxonomy = module_invoke('taxonomy', 'form_all', 1);
      if (!empty($taxonomy)) {
        $form['scrollable_source']['scrollable_source_terms'] = array(
          '#type' => 'select',
          '#title' => t('Only in category(s)'),
          '#size' => 10,
          '#options' => $taxonomy,
          '#multiple' => TRUE,
          '#default_value' => variable_get('scrollable_source_terms', 'scrollable'),
          '#description' => t('The term(s) that you want to display as sliding content.'),
        );
      }
    }

    // CCK fields names
    if (module_exists('content') && function_exists('content_fields')) {
      $cck_fields[] = '- None -';
      $fields = array_keys(content_fields());

      foreach ($fields as $key => $value) {
        $cck_fields[$value] = $value; 
      }

      $form['scrollable_source']['scrollable_image_source'] = array(
        '#type' => 'select',
        '#title' => t('Images field name'),
        '#options' => $cck_fields,
        '#default_value' => variable_get('scrollable_image_source', ''),
        '#description' => t('The name of CCK field that contains images, <em>leave it empty if you put the images inside body field</em>. Scrollable Content can detect and get images if they are in body field'),
      );
    }

  // Results settings
  $form['scrollable_results'] = array(
    '#type' => 'fieldset',
    '#weight' => -30,
    '#title' => t('Results settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

    $form['scrollable_results']['scrollable_nodes'] = array(
	    '#type' => 'select',
	    '#title' => t('Number of nodes'),
	    '#default_value' => variable_get('scrollable_nodes', 5),
	    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)),
	    '#description' => t('The number of nodes to get and display as scrolling content.'),
	  );

    $form['scrollable_results']['scrollable_default_image'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Default image'),
	    '#default_value' => variable_get('scrollable_default_image', ''),
	    '#description' => t('If Scrollable Content does not find any image in the node, it will use this default image.'),
	    '#maxlength' => 255,
	    '#field_prefix' => '<strong>'. file_directory_path() . '/' .'</strong>',
	  );

	  $form['scrollable_results']['scrollable_imagecache_preset'] = array(
	    '#type' => 'select',
	    '#title' => t('Imagecache Preset'),
	    '#description' => t('The Imagecache preset to use for scalling the images in Scrollable.'),
	    '#options' => drupal_map_assoc(_scrollable_content_image_presets()),
	    '#default_value' => variable_get('scrollable_imagecache_preset', ''),
	  );

  // Render settings
  $form['scrollable_settings'] = array(
    '#type' => 'fieldset',
    '#weight' => -20,
    '#title' => t('Render settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

	  $form['scrollable_settings']['scrollable_auto'] = array(
	    '#type' => 'checkbox',
	    '#title' => t('Automatic scrolling'),
	    '#default_value' => variable_get('scrollable_auto', 1),
	    '#description' => t('Automatic scrolling content.'),
	    '#maxlength' => '1',
	    '#size' => '1',
	  );
	
	  $directions = array('horizontal' => 'horizontal', 'vertical' => 'vertical');
	  $form['scrollable_settings']['scrollable_direction'] = array(
	    '#type' => 'select',
      '#title' => t('Sliding direction'),
	    '#options' => $directions,
	    '#default_value' => variable_get('scrollable_direction', 'horizontal'),
	  );

	  $form['scrollable_settings']['scrollable_items_number'] = array(
	    '#type' => 'select',
	    '#title' => t('Number of items scrolled at once'),
	    '#default_value' => variable_get('scrollable_items_number', 1),
	    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6)),
	    '#description' => t('The number of items that appear in each view at one scrolling step. <b>It\'s only useful for vertical scrolling with appropriate CSS.</b>'),
	  );
	
	  $form['scrollable_settings']['scrollable_interval'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Interval Speed'),
	    '#default_value' => variable_get('scrollable_interval', 3000),
	    '#description' => t('The time (in milliseconds) between autoscrolls.'),
	    '#maxlength' => '6',
	    '#size' => '6',
	    '#element_validate' => array('scrollable_content_integer_validate'),
	  );
	
	  $form['scrollable_settings']['scrollable_speed'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Sliding Speed'),
	    '#default_value' => variable_get('scrollable_speed', 400),
	    '#description' => t('The scrolling speed (in milliseconds) on each step.'),
	    '#maxlength' => '6',
	    '#size' => '6',
	    '#element_validate' => array('scrollable_content_integer_validate'),
	  );


  // Render settings
  $form['scrollable_theme'] = array(
    '#type' => 'fieldset',
    '#weight' => -10,
    '#title' => t('Theme'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

    $dirs = scandir(drupal_get_path('module', 'scrollable_content') . '/themes');
    $themes = array();
    foreach ($dirs as $key => $val) {
      if ($val[0] == '.') {
        unset($dirs[$key]);
      } else {
        $themes[$val] = ucwords($val);
      }
    }

	  $form['scrollable_theme']['scrollable_theme'] = array(
	    '#type' => 'select',
      '#title' => t('Theme name'),
	    '#options' => $themes,
	    '#default_value' => variable_get('scrollable_theme', 'blue'),
	  );

  return system_settings_form($form);
}

/**
 * Validate integers
 *
 * @param $element
 *  Type: array; The form element to validate.
 */
function scrollable_content_integer_validate($element) {

  if (preg_match('/\D/', $element['#value']) == 1) {
    form_set_error($element['#name'], t('%element_title may only contain numbers.', array('%element_title' => $element['#title'])));
  }

}

/**
 * Helper function for Imagecache presets
 * 
 * Based on the function _taxonomy_image_presets() in Taxonomy Image module
 */
function _scrollable_content_image_presets() {

  if (module_exists('imagecache')) {

    if (function_exists('_imagecache_get_presets')) {
      $presets = _imagecache_get_presets();

    } elseif (function_exists('imagecache_presets')) {

      $ic_presets = imagecache_presets();
      $presets = array();
      foreach ($ic_presets as $preset_id => $preset_info) {
        $presets[$preset_info['presetid']] = $preset_info['presetname'];
      }
    } else {
      drupal_set_message(t('Unrecognized Imagecache API.'), 'error');
      return FALSE;
    }

    $presets[0] = '';
    sort($presets);

    return $presets;
  } else {
    return FALSE;
  }

}
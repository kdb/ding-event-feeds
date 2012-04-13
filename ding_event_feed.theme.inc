<?php

/**
 * Preprocess an Atom feed
 */
function template_preprocess_ding_event_feed_atom(&$vars) {
  global $base_url;
  global $language;

  $view     = &$vars['view'];
  $options  = &$vars['options'];
  $items    = &$vars['rows'];

  $style    = &$view->style_plugin;

  $vars['author'] = $title = variable_get('site_name', 'Drupal');


  // Figure out which display which has a path we're using for this feed. If there isn't
  // one, use the global $base_url
  $link_display_id = $view->display_handler->get_link_display();
  if ($link_display_id && !empty($view->display[$link_display_id])) {
    $path = $view->display[$link_display_id]->handler->get_path();
  }

  if ($path) {
    $path = $view->get_url(NULL, $path);
    $url_options = array('absolute' => TRUE);
    if (!empty($view->exposed_raw_input)) {
      $url_options['query'] = $view->exposed_raw_input;
    }

    // Compare the link to the default home page; if it's the default home page, just use $base_url.
    if ($path == variable_get('site_frontpage', 'node')) {
      $path = '';
    }

    $vars['link'] = check_url(url($path, $url_options));
  }

  $vars['namespaces'] = drupal_attributes($style->namespaces);
  $vars['items'] = $items;
  $vars['id'] = !empty($style->id) ? $style->id : '';
  $vars['updated'] = !empty($style->updated) ? $style->updated : '';

  drupal_set_header('Content-Type: application/atom+xml; charset=utf-8');
}

/**
 * Default theme function for all RSS rows.
 */
function template_preprocess_ding_event_feed_row_atom(&$vars) {
  $view     = &$vars['view'];
  $options  = &$vars['options'];
  $item     = &$vars['row'];

  $vars['item_elements'] = empty($item->elements) ? '' : format_xml_elements($item->elements);
}


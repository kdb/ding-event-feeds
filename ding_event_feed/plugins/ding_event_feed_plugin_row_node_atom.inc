<?php
/**
 * @file
 * Contains the node RSS row style plugin.
 */

/**
 * Plugin which performs a node_view on the resulting object
 * and formats it as an RSS item.
 */
class ding_event_feed_plugin_row_node_atom extends views_plugin_row_node_rss {
  // Basic properties that let the row style follow relationships.
  var $base_table = 'node';
  var $base_field = 'nid';

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['item_length'] = array(
      '#type' => 'select',
      '#title' => t('Display type'),
      '#options' => array(
        'default' => t('Default'),
      ),
      '#default_value' => $this->options['item_length'],
    );

    $options = array();
    $vocabs = taxonomy_get_vocabularies();
    foreach ($vocabs as $vid => $vocab) {
      $options[$vid] = $vocab->name;
    }

    $form['ding_audience'] = array(
      '#type' => 'select',
      '#title' => t('Audience category'),
      '#description' => t('Select the catagory used as audience'),
      '#options' => $options,
      '#default_value' => $this->options['audience'],
    );

    $form['ding_keywords'] = array(
      '#type' => 'select',
      '#title' => t('Keywords category'),
      '#description' => t('Select the catagory used as audience'),
      '#options' => $options,
      '#default_value' => $this->options['ding_keywords'],
    );

    $form['ding_tags'] = array(
      '#type' => 'select',
      '#title' => t('Tags category'),
      '#description' => t('Select the catagory used as audience'),
      '#options' => $options,
      '#default_value' => $this->options['ding_tags'],
    );

    $fields = content_fields();
    $field_options = array('' => t('Default'));
    foreach ($fields as $field_name => $field) {
      $field_options[$field_name] = $field_name . ' (' . $field['type'] . ')';
    }

    $form['ding_teaser'] = array(
      '#type' => 'select',
      '#title' => t('Summary'),
      '#description' => t('Select field used for summary element.'),
      '#options' => $field_options,
      '#default_value' => $this->options['ding_teaser'],
    );

    $form['ding_image'] = array(
      '#type' => 'select',
      '#title' => t('Image'),
      '#description' => t('Select field used for dingevent:image element.'),
      '#options' => $field_options,
      '#default_value' => $this->options['ding_teaser'],
    );

    $form['ding_date'] = array(
      '#type' => 'select',
      '#title' => t('Date'),
      '#description' => t('Select field used for dingevent:startdate and dingevent:enddata element.'),
      '#options' => $field_options,
      '#default_value' => $this->options['ding_date'],
    );

    $form['ding_entry_price'] = array(
      '#type' => 'select',
      '#title' => t('Entry price'),
      '#description' => t('Select field used for dingevent:price element.'),
      '#options' => $field_options,
      '#default_value' => $this->options['ding_entry_price'],
    );

    $form['ding_library'] = array(
      '#type' => 'select',
      '#title' => t('Library'),
      '#description' => t('Select field used for dingevent:institution element.'),
      '#options' => $field_options,
      '#default_value' => $this->options['ding_library'],
    );
  }

  function render($row) {
    $teaser_field_name = empty($this->options['ding_teaser']) ? 'field_teaser' : $this->options['ding_teaser'];
    $image_field_name = empty($this->options['ding_image']) ? 'field_list_image' : $this->options['ding_image'];
    $date_field_name = empty($this->options['ding_image']) ? 'field_datetime' : $this->options['ding_date'];
    $entry_price_field_name = empty($this->options['ding_image']) ? 'field_entry_price' : $this->options['ding_entry_price'];
    $library_field_name = empty($this->options['ding_library']) ? 'field_library_ref' : $this->options['ding_library'];

    // For the most part, this code is taken from node_feed() in node.module
    global $base_url;

    $nid = $row->{$this->field_alias};
    if (!is_numeric($nid)) {
      return;
    }

    $item_length = $this->options['item_length'];
    if ($item_length == 'default') {
      $item_length = variable_get('feed_item_length', 'teaser');
    }

    // Load the specified node:
    $node = node_load($nid);
    if (empty($node)) {
      return;
    }

    $this->view->style_plugin->id = $base_url . '/node/' . $node->nid;
    $this->view->style_plugin->updated = gmdate('c', $node->changed);

    // Filter and prepare node teaser
    if (node_hook($node, 'view')) {
      $node = node_invoke($node, 'view', FALSE, FALSE);
    }
    else {
      $node = node_prepare($node, FALSE);
    }

    // Set the proper node part, then unset unused $node part so that a bad
    // theme can not open a security hole.
    $content = drupal_render($node->content);

    $item = new stdClass();
    $item->nid = $node->nid;

    // Allow modules to add additional item fields and/or modify $item
    $extra = node_invoke_nodeapi($node, 'rss item');
    $item->elements = array(
      array('key' => 'title', 'value' => check_plain($node->title)),
      array('key' => 'link', 'attributes' => array('href' => $base_url . '/node/' . $node->nid)),
      array('key' => 'link', 'attributes' => array('rel' => 'alternate', 'href' => url('node/' . $node->nid, array('absolute' => TRUE)))),
      array('key' => 'id', 'value' => $base_url . '/node/' . $node->nid),
      array('key' => 'published', 'value' => gmdate('c', $node->created)),
      array('key' => 'updated', 'value' => gmdate('c', $node->changed)),
      array('key' => 'content', 'value' => $content, 'attributes' => array('type' => 'html')),
    );

    // Add info about the library ref.
    if (!empty($node->{$library_field_name}) && !empty($node->{$library_field_name}[0]['nid'])) {
      $library = node_load($node->{$library_field_name}[0]['nid']);
      $item->elements[] = array(
        'key' => 'dingevent:institution',
        'value' => check_plain($library->title),
        'attributes' => array('id' => $library->nid),
      );
    }

    if (!empty($node->{$teaser_field_name}) && !empty($node->{$teaser_field_name}[0]['value'])) {
      $item->elements[] = array('key' => 'summary', 'value' => check_plain($node->{$teaser_field_name}[0]['value']));
    }

    foreach ($node->taxonomy as $term) {
      if ($term->vid == $this->options['ding_audience']) {
        $item->elements[] = array('key' => 'category', 'value' => check_plain($term->name), 'attributes' => array('scheme' => 'audience'));
      }
      elseif ($term->vid == $this->options['ding_keywords']) {
        $item->elements[] = array('key' => 'category', 'value' => check_plain($term->name), 'attributes' => array('scheme' => 'keywords'));
      }
      elseif ($term->vid == $this->options['ding_tags']) {
        $item->elements[] = array('key' => 'category', 'value' => check_plain($term->name), 'attributes' => array('scheme' => 'tags'));
      }
    }

    if (!empty($node->{$image_field_name}) && !empty($node->{$image_field_name}[0]['fid'])) {
      foreach ($node->{$image_field_name} as $file) {
        $item->elements[] = array(
          'key' => 'dingevent:image',
          'value' => url($file['filepath'], array('absolute' => TRUE)),
          'attributes' => array('title' => check_plain($file['data']['alt'])),
          'namespace' => array('xmlns:dingevent' => 'https://github.com/kdb/ding-event-feeds/blob/master/spec/index.md'),
        );
      }
    }

    if (!empty($node->{$date_field_name}) && !empty($node->{$date_field_name}[0]['value2'])) {
      $item->elements[] = array(
        'key' => 'dingevent:startdate',
        'value' => gmdate('c', strtotime($node->{$date_field_name}[0]['value'])),
        'namespace' => array('xmlns:dingevent' => 'https://github.com/kdb/ding-event-feeds/blob/master/spec/index.md'),
      );
      $item->elements[] = array(
        'key' => 'dingevent:enddate',
        'value' => gmdate('c', strtotime($node->{$date_field_name}[0]['value2'])),
        'namespace' => array('xmlns:dingevent' => 'https://github.com/kdb/ding-event-feeds/blob/master/spec/index.md'),
      );
    }

    if (!empty($node->{$entry_price_field_name}) && !empty($node->{$entry_price_field_name}[0]['value'])) {
      $item->elements[] = array(
        'key' => 'dingevent:price',
        'value' => check_plain($node->{$entry_price_field_name}[0]['value']),
        'attributes' => array('currency' => 'DKK'),
        'namespace' => array('xmlns:dingevent' => 'https://github.com/kdb/ding-event-feeds/blob/master/spec/index.md'),
      );
    }

    foreach ($item->elements as $element) {
      if (isset($element['namespace'])) {
        $this->view->style_plugin->namespaces = array_merge($this->view->style_plugin->namespaces, $element['namespace']);
      }
    }

    return theme($this->theme_functions(), $this->view, $this->options, $item);
  }
}


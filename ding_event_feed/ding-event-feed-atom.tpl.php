<?php
/**
 * @file views-view-row-rss.tpl.php
 * Default view template to display a item in an RSS feed.
 *
 * @ingroup views_templates
 */
?>
<?php print "<?xml"; ?> version="1.0" encoding="utf-8" <?php print "?>"; ?>
<feed xmlns="http://www.w3.org/2005/Atom" <?php print $namespaces; ?>>
  <title><?php print $title; ?></title>
  <link><?php print $link; ?></link>
  <updated><?php print $updated; ?></updated>
  <author>
    <name><?php print $author; ?></name>
  </author>
  <id><?php print $id; ?></id>

  <?php print $items; ?>
</feed>

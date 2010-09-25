<?php
// $Id$
/**
 * @file scrollable-content-view.tpl.php
 *  Display content in 'scrollable content' block using jQuery.
 *
 * - $rows: Array of rows (resulted rows from the view).
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @see template_preprocess_scrollable_content_view()
 * @ingroup views_templates
 */
?>

<ul id="scrollable_content_<?php print $options['items']; ?>_navi" class="main_navi">
<?php
foreach ($rows as $row) {
?>
  <li>
    <?php print $row; ?>
  </li>
<?php
}
?>
</ul>

<div id="scrollable_content_wrapper_<?php print $options['items']; ?>">
  <div class="navi"></div>

  <a class="prev scrollable_content_<?php print $options['items']; ?>_prev"></a>

  <div id="scrollable_content_<?php print $options['items']; ?>" class="scrollable_content <?php print $options['vertical'] == 1 ? 'vertical' : 'horizontal'; ?>">
    <div id="scrollable_content_thumbs_<?php print $options['items']; ?>" class="items" style="left: 0px;">
      <?php
      foreach ($rows as $row) {
      ?>
      <div class="slide">
        <?php print $row; ?>
      </div>
      <?php
      }
      ?>
    </div>
  </div>

  <a class="next scrollable_content_<?php print $options['items']; ?>_next"></a>

  <br clear="all"/>
</div>
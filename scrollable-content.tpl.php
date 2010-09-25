<?php
// $Id$

/**
 * @file scrollable-content.tpl.php
 * Default theme implementation for Scrollable Content block.
 *
 * Available variables:
 * - $slides
 * - $direction
 *
 * @see template_preprocess_scrollable_content()
 */
?>

<ul id="scrollable_content_items_navi" class="main_navi">
<?php
foreach ($slides as $slide) {
?>
  <li>
    <img title="<?php print $slide['title']; ?>" alt="<?php print $slide['title']; ?>" src="<?php print $slide['image']; ?>"/>
    <span><?php print $slide['title']; ?></span>
  </li>
<?php
}
?>
</ul>


<div id="scrollable_content_wrapper_items">
  <div class="navi"></div>

  <a class="prev scrollable_content_prev"></a>

  <div id="scrollable_content_items" class="scrollable_content <?php print $direction; ?>">
    <div id="scrollable_content_thumbs_items" class="items" style="left: 0px;">
      <?php
      foreach ($slides as $slide) {
      ?>
      <div class="slide">
        <a href="<?php print $slide['path']; ?>" title="<?php print $slide['path']; ?>">
          <img title="<?php print $slide['title']; ?>" alt="<?php print $slide['title']; ?>" src="<?php print $slide['image']; ?>"/>
          <h3><?php print $slide['title']; ?></h3>
        </a>
      </div>
      <?php
      }
      ?>
    </div>
  </div>

  <a class="next scrollable_content_next"></a>

  <br clear="all"/>
</div>
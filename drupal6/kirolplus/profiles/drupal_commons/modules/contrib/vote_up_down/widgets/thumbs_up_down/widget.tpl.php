<?php

/**
 * @file
 * widget.tpl.php
 *
 * thumbs_up_down widget theme for Vote Up/Down
 * @todo use $show_up_as_link and $show_down_as_link
 */
?>
<div class="vud-widget vud-widget-thumbs_up_down" id="<?php print $id; ?>">
  <div class="up-score clear-block">
    <?php if ($show_links): ?>
      <?php if ($show_up_as_link): ?>
        <a href="<?php print $link_up; ?>" rel="nofollow" class="<?php print "$link_class_up"; ?>" title="<?php print t('Vote up!'); ?>">
      <?php endif; ?>
          <div class="vote-thumb <?php print $class_up; ?>" title="<?php print t('Vote up!'); ?>"></div>
          <div class="element-invisible"><?php print t('Vote up!'); ?></div>
      <?php if ($show_up_as_link): ?>
        </a>
      <?php endif; ?>
    <?php endif; ?>
  </div>

  <div class="down-score clear-block">
    <?php if ($show_links): ?>
      <?php if ($show_down_as_link): ?>
        <a href="<?php print $link_down; ?>" rel="nofollow" class="<?php print "$link_class_down"; ?>" title="<?php print t('Vote down!'); ?>">
      <?php endif; ?>
          <div class="vote-thumb <?php print $class_down; ?>" title="<?php print t('Vote down!'); ?>"></div>
          <div class="element-invisible"><?php print t('Vote down!'); ?></div>
      <?php if ($show_down_as_link): ?>
        </a>
      <?php endif; ?>
    <?php endif; ?>
  </div>
  
  <a href="<?php print $link_reset; ?>" rel="nofollow" class="element-invisible <?php print $link_class_reset; ?>" title="<?php print $reset_long_text; ?>">
    <div class="<?php print $class_reset; ?>">
      <?php print $reset_short_text; ?>
    </div>
  </a>
    
  <p class="vote-current-score">Points: <strong><?php print $retVal = ($vote_sum) ? $vote_sum : '0' ; ?></strong></p>
  
  <?php if ($class_up == 'up-active'): ?>
  <p class="voted-how">You voted &lsquo;up&rsquo;</p>
  <?php endif; ?>
  
  <?php if ($class_down == 'down-active'): ?>
  <p class="voted-how">You voted &lsquo;down&rsquo;</p>
  <?php endif; ?>
  
</div>

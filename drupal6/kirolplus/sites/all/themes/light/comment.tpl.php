<div class="post comment<?php if ($comment->status == COMMENT_NOT_PUBLISHED) print ' comment-unpublished'; ?>">
  <?php if ($picture) : ?><?php print $picture ?><?php endif; ?>  
  <p><?php print $author; ?> on <?php print format_date($comment->timestamp, 'custom','F dS Y') ?></p>
  <div class="content"><?php print $content ?></div>
  <?php if ($links): ?><div class="comments"><?php print $links ?></div><?php endif; ?>
</div>
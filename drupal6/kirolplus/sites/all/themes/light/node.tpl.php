<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">
  <?php if ($page == 0): ?>
    <h3 class="title">
      <a href="<?php print $node_url ?>"><?php print $title; ?></a>
    </h3>
  <?php endif; ?>

  <?php 
  if ($picture):
    print $picture; 
  endif;
?>  
  
     <div class="submitted">
  <?php 
  if ($submitted): 
    print t('Published by ') . theme('username', $node) .' on ' .format_date($node->created, 'custom', "F jS, Y") ; 
    $pred = " in ";
  else:
    $pred = "Filed in ";
  endif;
  
  if (count($taxonomy)):
    print $pred.light_print_terms($node);
  endif; ?>
   </div> 
  
  <div class="content">
    <?php print $content; ?>
  </div>
  
  <?php if ($links): ?>
    <div class="links">
      <?php print $links; ?>
    </div>
  <?php endif; ?>
</div>
<?php
echo("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
?>
<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Strict//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd'>
<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='en-us' lang='en-us'>
<head>
    <title><?php print $head_title ?></title>
    <?php print $head ?>
    <?php print $styles ?>
    <?php print $scripts ?>
<!--[if lte IE 6]>
<style type="text/css"> 
/* CSS Fix for IE 6 and below. */
.page #header h1 {padding: 10px 0;}
</style>
<![endif]-->
</head>
<body class="page">
<div id="container">
  <!-- start #header -->
  <div id="header">
    <!-- start #logoandtitle -->
    <div id="logoandtitle">
      <div class="logo">
        <?php if ($logo) { ?><a href="<?php print check_url($base_path); ?>" title="<?php print t('Home') ?>"><img src="<?php print $logo ?>" alt="<?php print t('Home') ?>" /></a><?php } ?>
      </div>
      <div class="title">    
        <h1><?php print l($site_name, "<front>"); ?></h1>        
        <?php if ($site_slogan) { ?><h2><?php print $site_slogan ?></h2><?php } ?>
      </div>
    </div>
    <!-- end #logoandtitle -->
    <?php if (isset($primary_links)): ?>
    <div id="navigation">
      <?php 
      //see http://drupal.org/node/140491    
      print phptemplate_light_primarylinks($primary_links);
      ?>
    </div>
    <?php endif; ?>
  </div>
  <!-- end #header -->
    <!-- start #wrap -->
    <div id="wrap">
        <!-- start #content -->
        <div id="content"> 
      
            <?php if ($mission != ""): ?>
                <div id="mission"><?php print $mission ?></div>
            <?php endif; ?>
                    
            <?php print $header; ?>
            
            <?php if ($title != ""): ?>
                <h2><?php print $title ?></h2>
            <?php endif; ?>
            
            <?php if ($breadcrumb) { ?><div class="breadcrumb"><?php print $breadcrumb ?></div><?php } ?>
            
            <?php if ($tabs != ""): ?>
                <?php print $tabs ?>
            <?php endif; ?>
            <?php if ($help != ""): ?>
                <p id="help"><?php print $help ?></p>
            <?php endif; ?>
            <?php if ($messages != ""): ?>
                <?php print $messages ?>
            <?php endif; ?>
            <?php print($content) ?>
        </div>
        <!-- end #content -->
        <!-- start #sidebar -->
        <div id="sidebar">
            <?php if ($sidebar): ?>
                <?php print $sidebar; ?>
            <?php endif; ?>  
        </div>
        <!-- end #sidebar -->
    </div>
    <!-- end #wrap -->
    <div class="clear">&nbsp;</div>
  <!-- This clearing element should immediately follow the #mainContent div in order to force the #container div to contain all child floats --><br class="clearfloat" />
    <!-- start #footer -->
  <div id="footer">
    <p><?php print $footer_message ?> | Theme based on <a href="http://wpzone.net/">Light Theme</a>, ported by <a href="http://www.nickbits.co.uk">Nick Young</a></p>
  </div>
    <!-- end #footer -->
</div>
<!-- end #container -->
<?php
print $closure
?>
</body>
</html>
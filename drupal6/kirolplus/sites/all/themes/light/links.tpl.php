<ul class="links">
<?php
// to change the delimiter, just modify the $delimiter value
foreach ( $links as $lnk ) {
  // Print the link
  //see http://api.drupal.org/api/function/l/5
  $class_extra="";
  if ($lnk['href'] == $_GET['q']) 
      $class_extra = 'active';   
  if ($lnk['attributes']['title'])
    $title = $lnk['attributes']['title'];
  else
    $title = $lnk['title'];	
  //Added BASE_PATH to fix bug for: http://drupal.org/node/295898
  //Added strreplace to fix XML error: http://drupal.org/node/295137
  $options['html'] = TRUE;
  print("<li>");
  print l("<span>".$lnk['title']."</span>",$lnk['href'],$options);
  print("</li>");
}
?> 
</ul>

<?php
// split out taxonomy terms by vocabulary
//see http://drupal.org/node/133223
function light_print_terms($nid) {
  $vocabularies = taxonomy_get_vocabularies();
  $output = '';
  foreach($vocabularies as $vocabulary) 
  {
    if ($vocabularies) 
    {
      $terms = taxonomy_node_get_terms_by_vocabulary($nid, $vocabulary->vid);
      if ($terms) 
      {
        $links = array();
        //$output .= '' . $vocabulary->name . ': ';
        foreach ($terms as $term) 
        {
          $links[] = l($term->name, taxonomy_term_path($term), array('rel' => 'tag', 'title' => strip_tags($term->description)));
        }
        $output .= implode(', ', $links);
      }
    }
  }
  return $output;
}

//Hack to ensure primary menu (the active item) stays highlighted when a secondary item is selested
//see http://drupal.org/node/140491
// Thanks to David McIntosh (aka  neofactor) (http://drupal.org/user/15203) for supplying a work around to the span issue
function phptemplate_light_primarylinks($links, $attributes = array('class' => 'links')) {
  $output = '';

  if (count($links) > 0) 
  {
    //Only do this if we have links to display
    $output = '<ul'. drupal_attributes($attributes) .'>';
    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) 
    {
      $class = '';
//line missing.  Pointed out by ryan@irealms.co.uk on 31st July 2008
//$output .= "<li>\n";
      // Automatically add a class to each link and also to each LI
      if (isset($link['attributes']) && isset($link['attributes']['class'])) 
      {
        $link['attributes']['class'] .= ' ' . $key;
        $class = $key;
      }else{
        $link['attributes']['class'] = $key;
        $class = $key;
      }

      $explode_array = explode('-',$link['attributes']['class']);
      if(count($explode_array)== 5)
      {   
        array_push($explode_array,'active');
        $link['attributes']['class'] = implode('-',$explode_array);
        $pos = strrpos($link['attributes']['class'], "-");
        $link['attributes']['class'] = substr_replace($link['attributes']['class'], ' ', $pos, -6);
      }

      // Add first and last classes to the list of links to help out themers.
      $extra_class = '';
      if ($i == 1) 
      {
        $extra_class .= 'first ';
      }
      if ($i == $num_links) 
      {
        $extra_class .= 'last ';
      }
$output .= '<li class="'. $extra_class . $class .'">';
      // Is the title HTML?
      $html = isset($link['html']) && $link['html'];

      // Initialize fragment and query variables.
      $link['query'] = isset($link['query']) ? $link['query'] : NULL;
      $link['fragment'] = isset($link['fragment']) ? $link['fragment'] : NULL;

      if (isset($link['href'])) {
        // neofactor - Commented out Drupal5 funcion below
        // $output .= l($link['title'], $link['href'], $link['attributes'], $link['query'], $link['fragment'], FALSE, $html);       
        // $output .= l('<span>'.$link['title'].'</span>', $link['href'], $link['attributes'], $link['query'], $link['fragment'], FALSE, true);

        // neofactor - Added in new Drupal6 work around using the new function
        $link['html'] = TRUE;
        $output .= l('<span>'. check_plain($link['title']) .'</span>', $link['href'], $link, $link['query'], $link['fragment'], FALSE, true);
        // neofactor - // END custom change
      }
      else if ($link['title']) 
      {
        //Some links are actually not links, but we wrap these in <span> for adding title and class attributes
        if (!$html) 
        {
          $link['title'] = check_plain($link['title']);
        }
        $output .= '<span'. drupal_attributes($link['attributes']) .'>'. $link['title'] .'</span>';
      }
      $i++;
      $output .= "</li>\n";
    }
    $output .= '</ul>';
  }
  return $output;
}
?>
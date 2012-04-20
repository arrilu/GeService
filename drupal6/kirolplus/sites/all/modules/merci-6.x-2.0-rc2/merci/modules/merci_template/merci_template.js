if (Drupal.jsEnabled) {
  $(document).ready( function() {
      if($('#edit-update-draft-id').attr('value')){
      $('#edit-save-as-draft').attr('value','Update Template');
      } else {
      $('#edit-save-as-draft').attr('value','Save as Template');
      }
      
      $('#show-merci-choices').click(function() {
        $('#merci-choices').toggle('slow', function() {
        // Animation complete.
        });
        $('#edit-merci-more').toggle('slow', function() {
        // Animation complete.
        });
        
      });   
  });

}



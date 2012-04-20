Drupal.behaviors.userTermsBehavior = function (context) {
  function sync_registration() {
    input_enabled = $(this);
    input_registration = $(input_enabled).parents('tr').find('.registration');
    if (this.checked) {
      input_registration.removeAttr('disabled');
    }
    else {
      input_registration.attr('disabled', 'disabled');
      input_registration.removeAttr('checked');
    }
  }

  $('#user-terms-fields input.enabled').click(sync_registration);
  $('#user-terms-fields input.enabled').each(sync_registration);
};

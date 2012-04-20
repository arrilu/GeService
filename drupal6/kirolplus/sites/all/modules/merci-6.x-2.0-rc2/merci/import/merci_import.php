<?php


/**
 * @file
 * Administrative page for adding MERCI bucket/resource content types and
 * items.
 *
 * Place this file in the root of your Drupal installation (ie, the same
 * directory as index.php), point your browser to
 * "http://yoursite/merci_import.php" and follow the
 * instructions.
 *
 * If you are not logged in as administrator, you will need to modify the access
 * check statement below. Change the TRUE to a FALSE to disable the access
 * check. After finishing the import, be sure to open this file and change the
 * FALSE back to a TRUE!
 */

// Enforce access checking?
$access_check = TRUE;

/**
 * Add issue files.
 */
function merci_import_1() {

  // This determines how many content types will be created per page load.
  // A resonable default has been chosen, but feel free to tweak to suit your needs.
  $limit = 10;

  // No file uploaded, so skip the import.
  if (!$_SESSION['content_types_file']) {
    return array();
  }

  // Multi-part import.
  if (!isset($_SESSION['merci_import_1'])) {
    $csv_file_array = file($_SESSION['content_types_file']);
    $_SESSION['merci_import_file_position'] = 0;
    $_SESSION['merci_import_1'] = 0;
    $_SESSION['merci_import_1_max'] = count($csv_file_array) - 1;
  }

  // Open import file.
  $handle = fopen($_SESSION['content_types_file'], 'r');
  fseek($handle, $_SESSION['merci_import_file_position']);

  // Have to manually load the content types inc file.
  module_load_include('inc', 'node', 'content_types');

  $ret = array();

  $count = 0;
  while (($data = fgetcsv($handle)) !== FALSE) {
    $count++;
    $_SESSION['merci_import_1']++;

    // Only save if the row count for the data is right.
    if (count($data) == 13) {
      // Node type settings.
      $form_state['values']['orig_type'] = '';
      $form_state['values']['type'] = $data[0];
      $form_state['values']['name'] = $data[1];
      $form_state['values']['description'] = $data[2];
      $form_state['values']['help'] = $data[3];
      $form_state['values']['min_word_count'] = 0;
      $form_state['values']['title_label'] = t('Title');
      $form_state['values']['body_label'] = t('Body');
      $form_state['values']['custom'] = TRUE;
      $form_state['values']['locked'] = FALSE;
      $form_state['values']['node_options'] = array(
        'promote' => 0,
        'revision' => 1,
        'status' => 1,
        'sticky' => 0,
      );

      // MERCI settings.
      $form_state['values']['merci_type_setting'] = $data[4];
      $form_state['values']['merci_max_hours_per_reservation'] = $data[5];
      $form_state['values']['merci_allow_overnight'] = $data[6];
      $form_state['values']['merci_allow_weekends'] = $data[7];
      $form_state['values']['merci_late_fee_per_hour'] = $data[8];
      $form_state['values']['merci_rate_per_hour'] = $data[9];
      $form_state['values']{'merci_fee_free_hours'} = $data[10];
      $form_state['values']['merci_status'] = $data[11];
      $form_state['values']['merci_spare_items'] = $data[0] == 'bucket' ? $data[12] : 0;

      $form_state['clicked_button']['#value'] = t('Save content type');
      drupal_execute('node_type_form', $form_state);
    }

    // Jump out of the loop here and do another cycle.  Save
    // where we're at in the CSV file.
    if ($count >= $limit) {
      $_SESSION['merci_import_file_position'] = ftell($handle);
      break;
    }
  }

  // No more lines in the file, import is done.  Clean up.
  if (!fgets($handle)) {
    fclose($handle);
    unset($_SESSION['merci_import_file_position']);
    unset($_SESSION['merci_import_1']);
    unset($_SESSION['merci_import_1_max']);
    file_delete($_SESSION['content_types_file']);
    unset($_SESSION['content_types_file']);
    return $ret;
  }

  fclose($handle);
  $ret['#finished'] = $_SESSION['merci_import_1'] / $_SESSION['merci_import_1_max'];
  return $ret;
}

/**
 * Add followup files.
 */
function merci_import_2() {
  global $user;

  // This determines how many content types will be created per page load.
  // A resonable default has been chosen, but feel free to tweak to suit your needs.
  $limit = 10;

  // No file uploaded, so skip the import.
  if (!$_SESSION['items_file']) {
    return array();
  }

  // Multi-part import
  if (!isset($_SESSION['merci_import_2'])) {
    $csv_file_array = file($_SESSION['items_file']);
    $_SESSION['merci_import_file_position'] = 0;
    $_SESSION['merci_import_2'] = 0;
    $_SESSION['merci_import_2_max'] = count($csv_file_array) - 1;
  }

  // Open import file.
  $handle = fopen($_SESSION['items_file'], 'r');
  fseek($handle, $_SESSION['merci_import_file_position']);

  $ret = array();

  $count = 0;
  while (($data = fgetcsv($handle)) !== FALSE) {
    $count++;
    $_SESSION['merci_import_2']++;

    // Only save if the row count for the data is right.
    if (count($data) == 7) {

      // Node data.
      $item          = new stdClass();
      $item->type    = $data[0];
      $item->name    = $user->name;
      $item->uid     = $user->uid;
      $item->title   = $data[1];
      $item->body    = $data[2];
      $item->status  = 1;
      $item->promote = 0;
      $item->sticky  = 0;

      // MERCI specific data.
      //$merci_settings = merci_load_content_type_settings($item->type);
      $merci_settings = merci_load_item_settings(NULL,$item->type);
      $is_resource = $merci_settings->type_setting == 'resource' ? TRUE : FALSE;
      $item->merci_default_availability = $data[3];
      $item->merci_sub_type = MERCI_SUB_TYPE_ITEM;
      // Only resources get per item accounting data.
      $item->merci_late_fee_per_hour = $is_resource ? $data[4] : 0;
      $item->merci_rate_per_hour = $is_resource ? $data[5] : 0;
      $item->merci_fee_free_hours = $is_resource ? $data[6] : 0;

      $item = node_submit($item);
      node_save($item);
      if (isset($item->nid)) {
        drupal_set_message(t("The %type item %title has been added.", array('%type' => $item->type, '%title' => $item->title)));
      }
    }

    // Jump out of the loop here and do another cycle.  Save
    // where we're at in the CSV file.
    if ($count >= $limit) {
      $_SESSION['merci_import_file_position'] = ftell($handle);
      break;
    }
  }

  // No more lines in the file, import is done.  Clean up.
  if (!fgets($handle)) {
    fclose($handle);
    unset($_SESSION['merci_import_file_position']);
    unset($_SESSION['merci_import_2']);
    unset($_SESSION['merci_import_2_max']);
    file_delete($_SESSION['items_file']);
    unset($_SESSION['items_file']);
    return $ret;
  }

  fclose($handle);
  $ret['#finished'] = $_SESSION['merci_import_2'] / $_SESSION['merci_import_2_max'];
  return $ret;
}

/**
 * Perform one import and store the results which will later be displayed on
 * the finished page.
 *
 * @param $module
 *   The module whose import will be run.
 * @param $number
 *   The import number to run.
 *
 * @return
 *   TRUE if the import was finished. Otherwise, FALSE.
 */
function import_data($module, $number) {

  $function = "merci_import_$number";
  $ret = $function();

  // Assume the import finished unless the import results indicate otherwise.
  $finished = 1;
  if (isset($ret['#finished'])) {
    $finished = $ret['#finished'];
    unset($ret['#finished']);
  }

  // Save the query and results for display by import_finished_page().
  if (!isset($_SESSION['import_results'])) {
    $_SESSION['import_results'] = array();
  }
  if (!isset($_SESSION['import_results'][$module])) {
    $_SESSION['import_results'][$module] = array();
  }
  if (!isset($_SESSION['import_results'][$module][$number])) {
    $_SESSION['import_results'][$module][$number] = array();
  }
  $_SESSION['import_results'][$module][$number] = array_merge($_SESSION['import_results'][$module][$number], $ret);

  return $finished;
}

function import_selection_page() {
  $output = '';
  $output .= '<p>Click Import to start the import process.</p>';

  drupal_set_title('MERCI import');
  // Use custom import.js.
  drupal_add_js(import_js(), 'inline');
  $output .= drupal_get_form('import_script_selection_form');

  return $output;
}

function import_script_selection_form() {
  $form = array();

  $form['#attributes'] = array('enctype' => 'multipart/form-data');
  $form['content_types_file'] = array(
    '#type' => 'file',
    '#title' => t('CSV file for bucket/resource content types'),
    '#description' => t("Must be a comma separated file, double-quote text delimiters, backslash for escape character."),
  );
  $form['items_file'] = array(
    '#type' => 'file',
    '#title' => t('CSV file for bucket/resource items'),
    '#description' => t("Must be a comma separated file, double-quote text delimiters, backslash for escape character."),
  );

  $form['has_js'] = array(
    '#type' => 'hidden',
    '#default_value' => FALSE,
    '#attributes' => array('id' => 'edit-has_js'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Import',
  );
  return $form;
}

function import_import_page() {
  // Set the installed version so imports start at the correct place.
  $_SESSION['import_remaining'][] = array('module' => 'merci', 'version' => 1);
  $_SESSION['import_remaining'][] = array('module' => 'merci', 'version' => 2);

  // Upload the files.
  if ($content_types_file = file_save_upload('content_types_file', array(), FALSE, FILE_EXISTS_REPLACE)) {
    $_SESSION['content_types_file'] = $content_types_file->filepath;
  }
  else {
    $_SESSION['content_types_file'] = FALSE;
  }
  if ($items_file = file_save_upload('items_file', array(), FALSE, FILE_EXISTS_REPLACE)) {
    $_SESSION['items_file'] = $items_file->filepath;
  }
  else {
    $_SESSION['items_file'] = FALSE;
  }

  // Keep track of total number of imports
  if (isset($_SESSION['import_remaining'])) {
    $_SESSION['import_total'] = count($_SESSION['import_remaining']);
  }

  if ($_POST['has_js']) {
    return import_progress_page();
  }
  else {
    return import_progress_page_nojs();
  }
}

function import_progress_page() {
  // Prevent browser from using cached drupal.js or import.js
  drupal_add_js('misc/progress.js', 'core', 'header', FALSE, TRUE);
  drupal_add_js(import_js(), 'inline');

  drupal_set_title('Importing');
  $output = '<div id="progress"></div>';
  $output .= '<p id="wait">Please wait while the data is being imported.</p>';
  return $output;
}

/**
 * Custom import JS function.
 */
function import_js() {
  return "
  if (Drupal.jsEnabled) {
    $(document).ready(function() {
      $('#edit-has-js').each(function() { this.value = 1; });
      $('#progress').each(function () {
        var holder = this;

        // Success: redirect to the summary.
        var importCallback = function (progress, status, pb) {
          if (progress == 100) {
            pb.stopMonitoring();
            window.location = window.location.href.split('op=')[0] +'op=finished';
          }
        }

        // Failure: point out error message and provide link to the summary.
        var errorCallback = function (pb) {
          var div = document.createElement('p');
          div.className = 'error';
          $(div).html('An unrecoverable error has occured. You can find the error message below. It is advised to copy it to the clipboard for reference. Please continue to the <a href=\"merci_import.php?op=error\">import summary</a>');
          $(holder).prepend(div);
          $('#wait').hide();
        }

        var progress = new Drupal.progressBar('importprogress', importCallback, \"POST\", errorCallback);
        progress.setProgress(-1, 'Starting import');
        $(holder).append(progress.element);
        progress.startMonitoring('merci_import.php?op=do_import', 0);
      });
    });
  }
  ";
}

/**
 * Perform imports for one second or until finished.
 *
 * @return
 *   An array indicating the status after doing imports. The first element is
 *   the overall percentage finished. The second element is a status message.
 */
function import_do_imports() {
  while (isset($_SESSION['import_remaining']) && ($import = reset($_SESSION['import_remaining']))) {
    $import_finished = import_data($import['module'], $import['version']);
    if ($import_finished == 1) {
      // Dequeue the completed import.
      unset($_SESSION['import_remaining'][key($_SESSION['import_remaining'])]);
      // Make sure this step isn't counted double
      $import_finished = 0;
    }
    if (timer_read('page') > 1000) {
      break;
    }
  }

  if ($_SESSION['import_total']) {
    $percentage = floor(($_SESSION['import_total'] - count($_SESSION['import_remaining']) + $import_finished) / $_SESSION['import_total'] * 100);
  }
  else {
    $percentage = 100;
  }

  // When no imports remain, clear the caches in case the data has been imported.
  if (!isset($import['module'])) {
    cache_clear_all('*', 'cache', TRUE);
    cache_clear_all('*', 'cache_page', TRUE);
    cache_clear_all('*', 'cache_menu', TRUE);
    cache_clear_all('*', 'cache_filter', TRUE);
    drupal_clear_css_cache();
  }

  return array($percentage, isset($import['module']) ? 'Importing '. $import['module'] .' module' : 'Importing complete');
}

/**
 * Perform imports for the JS version and return progress.
 */
function import_do_import_page() {
  global $conf;

  // HTTP Post required
  if ($_SERVER['REQUEST_METHOD'] != 'POST') {
    drupal_set_message('HTTP Post is required.', 'error');
    drupal_set_title('Error');
    return '';
  }

  // Error handling: if PHP dies, the output will fail to parse as JSON, and
  // the Javascript will tell the user to continue to the op=error page.
  list($percentage, $message) = import_do_imports();
  print drupal_to_js(array('status' => TRUE, 'percentage' => $percentage, 'message' => $message));
}

/**
 * Perform imports for the non-JS version and return the status page.
 */
function import_progress_page_nojs() {
  drupal_set_title('Importing');

  $new_op = 'do_import_nojs';
  if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    // Error handling: if PHP dies, it will output whatever is in the output
    // buffer, followed by the error message.
    ob_start();
    $fallback = '<p class="error">An unrecoverable error has occurred. You can find the error message below. It is advised to copy it to the clipboard for reference. Please continue to the <a href="merci_import.php?op=error">import summary</a>.</p>';
    print theme('maintenance_page', $fallback, FALSE, TRUE);

    list($percentage, $message) = import_do_imports();
    if ($percentage == 100) {
      $new_op = 'finished';
    }

    // Imports successful; remove fallback
    ob_end_clean();
  }
  else {

    // This is the first page so return some output immediately.
    $percentage = 0;
    $message = 'Starting import';
  }

  drupal_set_html_head('<meta http-equiv="Refresh" content="0; URL=merci_import.php?op='. $new_op .'">');
  $output = theme('progress_bar', $percentage, $message);
  $output .= '<p>Importing the data will take a few seconds.</p>';

  // Note: do not output drupal_set_message()s until the summary page.
  print theme('maintenance_page', $output, FALSE);
  return NULL;
}

function import_finished_page($success) {
  drupal_set_title('MERCI import');

  $links[] = '<a href="'. base_path() .'">Main page</a>';
  $links[] = '<a href="'. base_path() .'?q=admin">Administration pages</a>';

  // Report end result
  if ($success) {
    $output = '<p>Importing data was attempted. If you see no errors listed, you should remove merci_import.php from your Drupal root directory. Otherwise, you may need to update your database manually. All errors have been <a href="index.php?q=admin/logs/watchdog">logged</a>.</p>';
  }
  else {
    $output = '<p class="error">The import process was aborted prematurely. All other errors have been <a href="index.php?q=admin/logs/watchdog">logged</a>. You may need to check the <code>watchdog</code> database table manually.</p>';
    $output .= '<p class="error">This has most likely occurred because the CSV files are not in the correct format.</p>';
  }

  $output .= theme('item_list', $links);

  if ($success) {
    $output .= "<h4>Some things to take care of now:</h4>\n";
    $output .= "<ul>\n";
    $output .= "<li>Follow the instructions in MERCI's INSTALL.txt for setting up proper permissions for the bucket/resource content types that you added.</li>\n";
    $output .= "</ul>\n";
  }

  return $output;
}

function import_info_page() {
  drupal_set_title('MERCI import');
  $output = "<ol>\n";
  $output .= "<li>Use this script to import MERCI bucket/resource content types and items.</li>";
  $output .= "<li>Before doing anything, backup your database. This process will change your database and its values.</li>\n";
  $output .= "<li>Check below for the format and data structure of the CSV files you'll need for the import.</li>\n";
  $output .= "<li>Use the example files <em>content_types.csv</em> and <em>items.csv</em> (found in the same location as this file) for reference when constructing custom CSV files for import. They can also be used to load in a small amount of test data to demo the module.</li>\n";
  $output .= "<li>Make sure this file is placed in the root of your Drupal installation (the same directory that index.php is in) and <a href=\"merci_import.php?op=selection\">run the import script</a>. <strong>Don't import your data twice as it will cause problems!</strong></li>\n";
  $output .= "</ol>\n";

  $output .= "<h3>CSV file data structure and format</h3>\n";
  $output .= "<p>There are two types of data that can be imported -- bucket/resource content types, and bucket/resource item nodes.  Each type uses it's own CSV file, with the data structures listed below.  The CSV file format is as follows:</p>\n";
  $output .= "<ul>\n";
  $output .= "<li>Commas as field delimiters.</li>\n";
  $output .= "<li>All text fields surrounded by double quotes.</li>\n";
  $output .= "<li>Backslash character used for escaping.</li>\n";
  $output .= "</ul>\n";
  $output .= "<h4>Data structure for bucket/resource content types</h4>\n";
  $output .= "<p>The following data fields must be ordered left to right exactly as they appear below. There should be no column labels in the final CSV file, only data:</p>\n";
  $output .= "<ul>\n";
  $output .= "<li>type (text): Machine-readable name of the content type -- letters, numbers, and underscores only.</li>\n";
  $output .= "<li>name (text): Human-readable name of the content type.</li>\n";
  $output .= "<li>description (text): Longer description for the content type.</li>\n";
  $output .= "<li>help (text): Text that will appear above the node creation form for this content type.</li>\n";
  $output .= "<li>type_setting (text): The MERCI type.  Valid values: resource|bucket</li>\n";
  $output .= "<li>max_hours_per_reservation (integer): The maximum hours that the content type can be reserved.</li>\n";
  $output .= "<li>allow_overnight (integer): Boolean indicating if reservations are allowed overnight.  Valid values: 0|1</li>\n";
  $output .= "<li>allow_weekends (integer): Boolean indicating if reservations are allowed on weekends.  Valid values: 0|1</li>\n";
  $output .= "<li>late_fee_per_hour (float): Per hour late fee -- should be a dollar amount with no $ sign.</li>\n";
  $output .= "<li>rate_per_hour (float): Per hour fee -- should be a dollar amount with no $ sign.</li>\n";
  $output .= "<li>fee_free_hours (integer): Number of hours the content type can be used at no cost.</li>\n";
  $output .= "<li>status (integer): The status of the content type.  Valid values: 1 (active) | 2 (inactive)</li>\n";
  $output .= "<li>spare_items (integer): Number of bucket items that should never be reserved -- valid only for bucket content types.</li>\n";
  $output .= "</ul>\n";
  $output .= "<h4>Data structure for bucket/resource item nodes</h4>\n";
  $output .= "<p>The following data fields must be ordered left to right exactly as they appear below. There should be no column labels in the final CSV file, only data:</p>\n";
  $output .= "<ul>\n";
  $output .= "<li>type (text): Machine-readable name of the content type this item should belong to.</li>\n";
  $output .= "<li>title (text): The name of the item.</li>\n";
  $output .= "<li>body (text): A longer description of the item.</li>\n";
  $output .= "<li>default_availability (integer): The reservatioin availability of the item.  Valid values: 1 (available) | 2 (unavailable) | 3 (strictly available) | 4 (strictly unavailable)</li>\n";
  $output .= "<li>late_fee_per_hour (float): Per hour late fee -- should be a dollar amount with no $ sign.</li>\n";
  $output .= "<li>rate_per_hour (float): Per hour fee -- should be a dollar amount with no $ sign.</li>\n";
  $output .= "<li>fee_free_hours (integer): Number of hours the content type can be used at no cost.</li>\n";
  $output .= "</ul>\n";

  return $output;
}

function import_access_denied_page() {
  drupal_set_title('Access denied');
  return '<p>Access denied. You are not authorized to access this page. Please log in as the admin user (the first user you created). If you cannot log in, you will have to edit <code>merci_import.php</code> to bypass this access check. To do this:</p>
<ol>
 <li>With a text editor find the merci_import.php file on your system. It should be in the main Drupal directory that you installed all the files into.</li>
 <li>There is a line near top of merci_import.php that says <code>$access_check = TRUE;</code>. Change it to <code>$access_check = FALSE;</code>.</li>
 <li>As soon as the import is done, you should remove merci_import.php from your main installation directory.</li>
</ol>';
}

/**
 * Helper function for determining module dependencies.
 *
 * @param $modules
 *   An associative array of modules to check. Key is module name,
 *   value is human-readable name.
 *
 * @return
 *   A string containing the error message, if any -- FALSE otherwise.
 */
function merci_check_dependencies($modules) {
  $message = FALSE;
  $messages = array();
  // Have to reset the module list here, as the maintenance theme wipes
  // out the full list.
  module_list(TRUE, FALSE);
  foreach ($modules as $module => $name) {
    if (!module_exists($module)) {
      $messages[] = t('The %module module is not enabled.', array('%module' => $name));
    }
  }
  if (!empty($messages)) {
    $message = t('The import was aborted for the following reasons: !messages', array('!messages' => theme('item_list', $messages))) . t("This has most likely occurred because the required modules are not <a href=\"index.php?q=admin/build/modules\">properly installed</a>.");
  }

  return $message;
}

include_once './includes/bootstrap.inc';

drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
drupal_maintenance_theme();

// Abort the import if the necessary modules aren't installed.
$dependencies = array(
  'merci' => t('MERCI'),
  'content' => t('Content'),
  'date' => t('Date'),
  'date_api' => t('Date API'),
  'date_popup' => t('Date popup'),
  'date_timezone' => t('Date timezone'),
  'views' => t('Views'),
  'taxonomy' => t('Taxonomy'),
);
if ($messages = merci_check_dependencies($dependencies)) {
  drupal_set_title(t("Import aborted"));
  print theme('maintenance_page', $messages);
  exit();
}

// Access check:
if (($access_check == FALSE) || ($user->uid == 1)) {

  $op = isset($_REQUEST['op']) ? $_REQUEST['op'] : '';
  switch ($op) {
    case 'Import':
      $output = import_import_page();
      break;

    case 'finished':
      $output = import_finished_page(TRUE);
      break;

    case 'error':
      $output = import_finished_page(FALSE);
      break;

    case 'do_import':
      $output = import_do_import_page();
      break;

    case 'do_import_nojs':
      $output = import_progress_page_nojs();
      break;

    case 'selection':
      $output = import_selection_page();
      break;

    default:
      $output = import_info_page();
      break;
  }
}
else {
  $output = import_access_denied_page();
}

if (isset($output)) {
  print theme('maintenance_page', $output);
}


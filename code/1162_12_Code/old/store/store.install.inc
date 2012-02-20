<?php

function store_configure_contact_form($form, &$form_state, &$install_state) {
  $form['recipients'] = array(
    '#type' => 'textarea',
    '#title' => t('Recipients'),
    '#default_value' => '',
    '#description' => t("Example: 'webmaster@example.com' or 'sales@example.com,support@example.com' . To specify multiple recipients, separate each e-mail address with a comma."),
    '#required' => TRUE,
  );
  $form['reply'] = array(
    '#type' => 'textarea',
    '#title' => t('Auto-reply'),
    '#default_value' => '',
    '#description' => t('Optional auto-reply. Leave empty if you do not want to send the user an auto-reply message.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

function store_configure_contact_form_validate($form, &$form_state) {
  drupal_set_title(t('Default site contact information'));

  // Validate and each e-mail recipient.
  $recipients = explode(',', $form_state['values']['recipients']);
  foreach ($recipients as &$recipient) {
    $recipient = trim($recipient);
    if (!valid_email_address($recipient)) {
      form_set_error('recipients', t('%recipient is an invalid e-mail address.', array('%recipient' => $recipient)));
    }
  }
  $form_state['values']['recipients'] = implode(',', $recipients);
}

function store_configure_contact_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $values += array(
    'cid' => 1,
  );
  drupal_write_record('contact', $values, array('cid'));
  watchdog('contact', 'The default category has been updated.', array(), WATCHDOG_NOTICE, l(t('Edit'), 'admin/structure/contact/edit/' . $values['cid']));
}

/**
 * Installation task; Override install_settings_form.
 * Define a form to configure and rewrite settings.php.
 */
function store_database_settings_form($form, &$form_state, &$install_state) {
  // Retrieve the default form.
  $default_form = install_settings_form($form, &$form_state, &$install_state);
  $default_form['database']['#description'] .= st(' If you choose use SQLite please provide an absolute path outside of the webroot directory.');
  return $default_form;
}

/**
 * Form API validate for store_database_settings_form form.
 */
function store_database_settings_form_validate($form, &$form_state) {
  install_settings_form_validate($form, &$form_state);
}

/**
 * Form API submit for store_database_settings_form form.
 */
function store_database_settings_form_submit($form, &$form_state) {
  install_settings_form_submit($form, &$form_state);
}

function store_create_content_types(&$install_state) {
  $types = array(
    array(
      'type' => 'page',
      'name' => st('Page'),
      'base' => 'node_content',
      'description' => st("Use <em>pages</em> for your static content, such as an 'About us' page."),
      'custom' => 1,
      'modified' => 1,
      'locked' => 0,
    ),
    array(
      'type' => 'product',
      'name' => st('Product'),
      'base' => 'node_content',
      'description' => st('Use <em>products</em> for items in the store.'),
      'custom' => 1,
      'modified' => 1,
      'locked' => 0,
    ),
  );

  foreach ($types as $type) {
    $type = node_type_set_defaults($type);
    node_type_save($type);
  }
}


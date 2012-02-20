<?php

/**
 * @file
 * Example Store profile.
 */

/**
 * Implements hook_install_tasks().
 */
function store_install_tasks() {
  $tasks = array();
  $tasks['store_create_content_types'] = array(
    'type' => 'normal',
  );
  $tasks['store_configure_contact_form'] = array(
    'display_name' => t('Default site contact information.'),
    'type' => 'form',
  );
  return $tasks;
}

/**
 * Implements hook_install_tasks_alter().
 */
function store_install_tasks_alter(&$tasks, &$install_state) {
  $tasks['install_settings_form']['function'] = 'store_database_settings_form';

  // Include store.install.inc containing the tasks and forms.
  include_once 'store.install.inc';
}

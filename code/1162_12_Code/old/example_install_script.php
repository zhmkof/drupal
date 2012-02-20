<?php

// The settings for the installer to use when installing Drupal.
$settings = array(
  // This overrides the PHP array $_SERVER so we can tell Drupal
  // the path to the site. This is important for multi-site support.
  'server' => array(
    'HTTP_HOST' => 'localhost',   // The domain name.
    'SCRIPT_NAME' => '',          // The path to the site on the domain.
  ),

  // Select the profile and the locale.
  'parameters' => array(
    'profile' => 'minimal',
    'locale' => 'en',
  ),

  // The values to use in each of the forms.
  'forms' => array(
    'install_settings_form' => array(
      'driver' => 'sqlite',
      'database' => 'test',
      'username' => '',
      'password' => '',
      'host' => 'localhost',
      'port' => '',
      'db_prefix' => '',
    ),

    // The site configuration form.
    'install_configure_form' => array(
      'site_name' => 'Drupal Site',
      'site_mail' => 'email@example.com',
      'account' => array(
        'name' => 'admin',
        'mail' => 'email@example.com',
        'pass' => array(
          // On the form there are two password fields. The installer is filling
          // out the form so we need to fill in both form fields.
          'pass1' => 'password',
          'pass2' => 'password',
        ),
      ),
 
      // The default country and timezone.
      'site_default_country' => 'US',
      'date_default_timezone' => 'America/Detroit',
 
      // Enable clearn URLs.
      'clean_url' => TRUE,
 
      // Check for updates using the Update manager.
      // Possible values are:
      //  - array() = off, 
      //  - array(1) = check for updates, 
      //  - array(1, 2) = check for updates and notify by email
      'update_status_module' => array(1, 2),
    ),
  ),
);
 
/**
* Root directory of Drupal installation.
*/
define('DRUPAL_ROOT', getcwd());

/**
* Global flag to indicate that site is in installation mode.
*/
define('MAINTENANCE_MODE', 'install');

// Load the installer and initiate the install process using $settings.
require_once DRUPAL_ROOT . '/includes/install.core.inc';
install_drupal($settings);

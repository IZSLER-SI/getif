<?php
/**
 * @file
 * Admin ui for the module.
 */

/**
 * Callback function for the admin settings form.
 *
 * @param array $form
 *   The form array.
 *
 * @return array
 *   The system settings form.
 */
function cmnc_settings_form($form) {
  $form['cmnc_delete_expired'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete old viewed notifications'),
    '#description' => t('When checked, will delete viewed notifications older than the specified maximum age.  Deletions occur during cron runs.'),
    '#default_value' => variable_get('cmnc_delete_expired', TRUE),
  );

  $options = array(
    0 => t('Immediately'),
    60 => t('1 hour'),
    86400 => t('1 day'),
    604800 => t('1 week'),
    1209600 => t('2 weeks'),
    2419200 => t('1 month (30 days)'),
  );

  $form['cmnc_max_message_age'] = array(
    '#type' => 'select',
    '#title' => t('Maximum notification age'),
    '#description' => t('The length of time that viewed notifications are retained.'),
    '#options' => $options,
    '#default_value' => variable_get('cmnc_max_message_age', 604800),
    '#states' => array(
      'disabled' => array(
        ':input[name="cmnc_delete_expired"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['cmnc_show_icon_in_utility_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Notification in Commons Utility Links'),
    '#description' => t('When checked, the Notification icon will display at the end of the Drupal Commons Utility Links block.'),
    '#default_value' => variable_get('cmnc_show_icon_in_utility_links', TRUE),
  );

  return system_settings_form($form);
}

<?php
/**
 * @file
 * Administration UI for the module.
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
function cmnc_ui_settings_form($form) {
  $users_have_default_settings = cmnc_ui_check_user_default_settings();
  if (!$users_have_default_settings) {
    drupal_set_message(t('Some user accounts are missing a default setting for notifications.  Use the "Initialize user default settings" button below to resolve this issue.'), 'warning');
  }
  else {
    drupal_set_message(t('All user accounts have default notification settings configured.'));
  }

  $form['init_users'] = array(
    '#type' => 'fieldset',
    '#title' => t('Initialize users'),
    '#tree' => TRUE,
  );
  $form['init_users']['info'] = array(
    '#type' => 'item',
    '#prefix' => '<div>',
    '#markup' => t('Clicking the "Initialize user default settings button will update all existing user accounts with the specified default setting for the notification center.'),
    '#suffix' => '</div>',
  );
  $form['init_users']['default_value'] = array(
    '#type' => 'select',
    '#title' => t('Enable Notification Center for all users'),
    '#description' => t('Should this routine enable the notification center by default for all users?'),
    '#options' => array(1 => t('Yes'), 0 => t('No')),
  );
  $form['init_users']['replace'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace existing defaults'),
    '#description' => t('Should we replace the default settings on user accounts that have already set them?') .
    '<br />' .
    t('Only applies to the global email and CMNC notifications.'),
  );
  $form['init_users']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Initialize user default settings'),
    '#submit' => array('cmnc_ui_init_users_submit'),
  );

  return $form;
}

/**
 * Submit handler for the Initialize Users button.
 */
function cmnc_ui_init_users_submit($form, &$form_state) {
  $replace_defaults = $form_state['values']['init_users']['replace'];
  $default_value = $form_state['values']['init_users']['default_value'];

  $batch = array(
    'title' => t('Setting user default notification settings'),
    'operations' => array(
      array(
        'cmnc_ui_batch_set_user_defaults',
        array(
          $default_value,
          $replace_defaults,
        ),
      ),
      array(
        'cmnc_ui_batch_set_flag_defaults',
        array(),
      ),
      array(
        'cmnc_ui_batch_set_notification_type_defaults',
        array(),
      ),
    ),
    'finished' => 'cmnc_ui_batch_init_defaults_finished',
    'file' => drupal_get_path('module', 'cmnc_ui') . '/includes/cmnc_ui.batch.inc',
  );
  batch_set($batch);
  batch_process('admin/config/system/cmnc/ui');
}

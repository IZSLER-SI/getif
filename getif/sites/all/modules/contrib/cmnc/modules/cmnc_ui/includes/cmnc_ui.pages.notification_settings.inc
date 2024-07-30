<?php
/**
 * @file
 * Handles the rendering of the notification-settings page.
 */

/**
 * Overrides the settings form commons_follow_ui_notification_settings_form().
 *
 * We need to override the default to replace the tab rendering call.
 *
 * @see commons_follow_ui_notification_settings_form()
 */
function cmnc_ui_notification_settings_form($form, &$form_state, $account) {
  if (empty($account)) {
    global $user;
    $account = $user;
  }
  drupal_set_title(t('Notification settings'));
  $form['#submit'][] = 'commons_follow_message_subscribe_email_setting_submit';
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );
  $form['explanation'] = array(
    '#markup' => t("Control how you are notified of new content and activity. When you follow a group, topic, user, or other content, you'll see updates in your content and activity streams, and you will automatically get email updates unlesss you disable emails or unfollow."),
    '#weight' => 0,
  );

  $form['message_subscribe_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send email notifications by default.'),
    '#description' => t("If checked, you'll automatically sign up for email notifications when you follow something. Leave unchecked to default to signing up only for activity stream notifications"),
    '#ajax' => array(
      'callback' => 'commons_follow_message_subscribe_email_setting_submit',
    ),
    '#default_value' => isset($account->message_subscribe_email[LANGUAGE_NONE][0]['value']) ? $account->message_subscribe_email[LANGUAGE_NONE][0]['value'] : FALSE,
    '#weight' => 1,
  );
  $form['cmnc_subscribe_message_center'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show notifications in notifications center by default.'),
    '#description' => t('If checked, notifications will be automatically displayed in the notification center.'),
    '#ajax' => array(
      'callback' => 'cmnc_ui_subscribe_message_center_submit',
    ),
    '#default_value' => isset($account->cmnc_subscribe_message_center[LANGUAGE_NONE][0]['value']) ? $account->cmnc_subscribe_message_center[LANGUAGE_NONE][0]['value'] : TRUE,
    '#weight' => 1,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save email notification settings'),
    '#attributes' => array(
      'class' => array('js-hide'),
    ),
    '#weight' => 2,
  );

  $module_path = drupal_get_path('module', 'cmnc_ui');
  $form['#attached']['css'][] = $module_path . '/css/cmnc_ui.css';
  $form['#attached']['js'][] = $module_path . '/js/cmnc_ui.js';

  $tabs = cmnc_ui_generate_tabs($account);
  $form['tabs'] = array(
    '#markup' => drupal_render($tabs),
    '#weight' => 3,
  );

  return $form;
}

/**
 * Overridden version of commons_follow_ui_generate_tabs().
 *
 * @param object $account
 *   The user account that the tabs are being generated for.
 *
 * @return array
 *   A render array for the tabs.
 */
function cmnc_ui_generate_tabs($account) {
  $tabs = array();
  foreach (array_keys(message_subscribe_flag_get_flags()) as $flag_name) {
    $tabs[$flag_name] = array(
      'title' => commons_follow_ui_tab_title($account, $flag_name),
      'contents' => array('#markup' => message_subscribe_ui_tab($account, $flag_name)),
    );
  }

  // Add Notification Types tab.
  $tabs['notification_types'] = array(
    'title' => t('Notification Types'),
    'contents' => array(
      '#markup' => cmnc_ui_notification_setting_types_tab($account),
    ),
    'weight' => 99,
  );

  $settings = array(
    'style' => 'Commons Tabs',
    'ajax' => FALSE,
    'html' => TRUE,
    'title' => 'test',
    'default_tab' => 'commons_follow_group',
  );
  $built_tabs = quicktabs_build_quicktabs('commons_follow_ui', $settings, $tabs);

  return $built_tabs;
}

/**
 * Renders the contents for the notification types tab.
 *
 * @param object $account
 *   The user object the tab is being rendered for.
 *
 * @return string
 *   The rendered tab content.
 */
function cmnc_ui_notification_setting_types_tab($account) {
  $rows = array();

  $notification_types = cmnc_ui_get_notification_type_flags();
  foreach ($notification_types as $type => $options) {
    $email_link = '';
    if (isset($options['notifiers']['email']) && !empty($options['notifiers']['email'])) {
      $email_link = flag_create_link($options['notifiers']['email'], $account->uid);
    }
    $cmnc_link = '';
    if (isset($options['notifiers']['cmnc']) && !empty($options['notifiers']['cmnc'])) {
      $cmnc_link = flag_create_link($options['notifiers']['cmnc'], $account->uid);
    }

    $rows[] = array(
      $options['title'],
      $email_link,
      $cmnc_link,
    );
  }

  $variables = array(
    'header' => array(
      t('Event'),
      t('Send email?'),
      t('Internal notification?'),
    ),
    'rows' => $rows,
  );

  return theme('table', $variables);
}


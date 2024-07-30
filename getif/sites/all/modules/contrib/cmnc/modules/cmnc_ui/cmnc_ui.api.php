<?php
/**
 * @file
 * Hooks provided by the cmnc_ui module.
 */

/**
 * Defines notification types that users can enable/disable notifications for.
 *
 * @return array
 *   An associative array keyed by the generic notification type key and
 *   containing the following sub keys:
 *   * title :  The translated title for the notification type.
 *              Displayed as the event on the Notification Types tab.
 *   * notifiers : An array mapping message_subscribe notifiers to flag
 *                 definitions.  This is the per-user flag that indicates
 *                 if the user wishes to receive a notification via the
 *                 specified notifier.
 *   * notifier_flags : An array of Flag names that can trigger this
 *                      notification type.
 *   * message_types : An array of message_type names that can trigger this
 *                     notification type.
 */
function hook_cmnc_ui_type_definitions() {
  $flags['cmnc_ui_notify_user'] = array(
    'title' => t('Notify me when a user follows me'),
    'notifiers' => array(
      'email' => 'cmnc_ui_notify_user_follow_email',
      'cmnc' => 'cmnc_ui_notify_user_follow_cmnc',
    ),
    'notifier_flags' => array(
      'commons_follow_user',
    ),
    'message_types' => array(
      'cmnc_user_followed',
    ),
  );

  return $flags;
}

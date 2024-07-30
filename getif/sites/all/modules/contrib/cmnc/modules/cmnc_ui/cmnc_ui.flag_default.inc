<?php
/**
 * @file
 * Defines default flags provided by this module.
 */

/**
 * Implements hook_flag_default_flags().
 */
function cmnc_ui_flag_default_flags() {
  $flags = array();
  // Exported flag: "Show in notification center (Node)".
  $flags['cmnc_node'] = array(
    'content_type' => 'node',
    'title' => 'Show in notification center (Node)',
    'global' => 0,
    'types' => array(
      0 => 'answer',
      1 => 'event',
      2 => 'group',
      3 => 'poll',
      4 => 'post',
      5 => 'question',
      6 => 'wiki',
    ),
    'flag_short' => 'Show in notification center',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Don\'t show in notification center',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_contextual_link' => FALSE,
    'i18n' => 0,
    'api_version' => 2,
  );
  // Exported flag: "Show in notification center (Topic)".
  $flags['cmnc_term'] = array(
    'content_type' => 'taxonomy_term',
    'title' => 'Show in notification center (Topic)',
    'global' => 0,
    'types' => array(
      0 => 'topics',
    ),
    'flag_short' => 'Show in notification center',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Don\'t show in notification center',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_entity' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'api_version' => 2,
  );
  // Exported flag: "Show in notification center (User)".
  $flags['cmnc_user'] = array(
    'content_type' => 'user',
    'title' => 'Show in notification center (User)',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Show in notification center',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Don\'t show in notification center',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_entity' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_profile' => 0,
    'access_uid' => '',
    'api_version' => 2,
  );
  // Exported flag: "Notify me when a user follows me (CMNC)".
  $flags['cmnc_ui_notify_user_follow_cmnc'] = array(
    'content_type' => 'user',
    'title' => 'Notify me when a user follows me (CMNC)',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Notify',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Do not notify',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_entity' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_profile' => 0,
    'access_uid' => '',
    'api_version' => 2,
  );
  // Exported flag: "Notify me when a user follows me (Email)".
  $flags['cmnc_ui_notify_user_follow_email'] = array(
    'content_type' => 'user',
    'title' => 'Notify me when a user follows me (Email)',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Notify',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Do not notify',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_entity' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_profile' => 0,
    'access_uid' => '',
    'api_version' => 2,
  );

  return $flags;
}

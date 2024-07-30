<?php
/**
 * @file
 * cmnc.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function cmnc_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.message-commons_follow_user_user_followed-field_target_users.display|cmnc_message"] = array(
    'label' => 'above',
    'settings' => array(),
    'type' => 'hidden',
    'weight' => 0,
  );
  $overrides["field_instance.message-commons_notify_comment_created-field_message_rendered_body.display|cmnc_message"] = array(
    'label' => 'above',
    'settings' => array(),
    'type' => 'hidden',
    'weight' => 3,
  );

  // Exported overrides for: message_type
  $overrides["message_type.commons_notify_comment_created.message_text|und|2"] = array(
    'value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> commented on <a href="[message:field-target-nodes:0:url]">[message:field-target-nodes:0:title]</a> [commons-groups:in-groups-text]',
    'format' => 'full_html',
    'safe_value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> commented on <a href="[message:field-target-nodes:0:url]">[message:field-target-nodes:0:title]</a> [commons-groups:in-groups-text]',
  );
  $overrides["message_type.commons_notify_node_created.message_text|und|2"] = array(
    'value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> created a new&nbsp;[message:field-target-nodes:0:content-type] <a href="[message:field-target-nodes:0:url]">[message:field-target-nodes:0:title]</a> [commons-groups:in-groups-text]',
    'format' => 'full_html',
    'safe_value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> created a new&nbsp;[message:field-target-nodes:0:content-type] <a href="[message:field-target-nodes:0:url]">[message:field-target-nodes:0:title]</a> [commons-groups:in-groups-text]',
  );
  $overrides["message_type.commons_notify_node_created_no_groups.message_text|und|2"] = array(
    'value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> created a new [message:field-target-nodes:0:content-type]: <a href="[message:field-target-nodes:0:url:absolute]">[message:field-target-nodes:0:title]</a>',
    'format' => 'full_html',
    'safe_value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> created a new [message:field-target-nodes:0:content-type]: <a href="[message:field-target-nodes:0:url:absolute]">[message:field-target-nodes:0:title]</a>',
  );

  // Exported overrides for: variable
  $overrides["variable.field_bundle_settings_message__commons_notify_comment_created.value|extra_fields|display|message__message_text__0|cmnc_message"] = array(
    'weight' => 1,
    'visible' => FALSE,
  );
  $overrides["variable.field_bundle_settings_message__commons_notify_comment_created.value|extra_fields|display|message__message_text__1|cmnc_message"] = array(
    'weight' => 6,
    'visible' => FALSE,
  );
  $overrides["variable.field_bundle_settings_message__commons_notify_comment_created.value|extra_fields|display|message__message_text__1|message_notify_email_body"] = array(
    'visible' => TRUE,
    'weight' => 0,
  );
  $overrides["variable.field_bundle_settings_message__commons_notify_comment_created.value|extra_fields|display|message__message_text__1|message_notify_email_subject"] = array(
    'weight' => 2,
    'visible' => FALSE,
  );
  $overrides["variable.field_bundle_settings_message__commons_notify_comment_created.value|extra_fields|display|message__message_text__2"] = array(
    'message_notify_email_body' => array(
      'weight' => 2,
      'visible' => FALSE,
    ),
  );
  $overrides["variable.field_bundle_settings_message__commons_notify_node_created_no_groups.value"] = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(
        'message__message_text__2' => array(),
        'message__message_text__0' => array(),
        'message__message_text__1' => array(),
      ),
    ),
  );

 return $overrides;
}

<?php
/**
 * @file
 * cmnc.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cmnc_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "message_notify" && $api == "notifier") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cmnc_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function cmnc_field_default_field_instances_alter(&$data) {
  if (isset($data['message-commons_follow_user_user_followed-field_target_users'])) {
    $data['message-commons_follow_user_user_followed-field_target_users']['display']['cmnc_message'] = array(
      'label' => 'above',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 0,
    ); /* WAS: '' */
  }
  if (isset($data['message-commons_notify_comment_created-field_message_rendered_body'])) {
    $data['message-commons_notify_comment_created-field_message_rendered_body']['display']['cmnc_message'] = array(
      'label' => 'above',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 3,
    ); /* WAS: '' */
  }
}

/**
 * Implements hook_default_message_type_alter().
 */
function cmnc_default_message_type_alter(&$data) {
  if (isset($data['commons_notify_comment_created'])) {
    $data['commons_notify_comment_created']->message_text['und']['2'] = array(
      'value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> commented on <a href="[message:field-target-nodes:0:url]">[message:field-target-nodes:0:title]</a> [commons-groups:in-groups-text]',
      'format' => 'full_html',
      'safe_value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> commented on <a href="[message:field-target-nodes:0:url]">[message:field-target-nodes:0:title]</a> [commons-groups:in-groups-text]',
    ); /* WAS: '' */
  }
  if (isset($data['commons_notify_node_created'])) {
    $data['commons_notify_node_created']->message_text['und']['2'] = array(
      'value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> created a new&nbsp;[message:field-target-nodes:0:content-type] <a href="[message:field-target-nodes:0:url]">[message:field-target-nodes:0:title]</a> [commons-groups:in-groups-text]',
      'format' => 'full_html',
      'safe_value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> created a new&nbsp;[message:field-target-nodes:0:content-type] <a href="[message:field-target-nodes:0:url]">[message:field-target-nodes:0:title]</a> [commons-groups:in-groups-text]',
    ); /* WAS: '' */
  }
  if (isset($data['commons_notify_node_created_no_groups'])) {
    $data['commons_notify_node_created_no_groups']->message_text['und']['2'] = array(
      'value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> created a new [message:field-target-nodes:0:content-type]: <a href="[message:field-target-nodes:0:url:absolute]">[message:field-target-nodes:0:title]</a>',
      'format' => 'full_html',
      'safe_value' => '[message:user:picture:35x35] <a href="[message:user:url:absolute]">[message:user:name]</a> created a new [message:field-target-nodes:0:content-type]: <a href="[message:field-target-nodes:0:url:absolute]">[message:field-target-nodes:0:title]</a>',
    ); /* WAS: '' */
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function cmnc_strongarm_alter(&$data) {
  if (isset($data['field_bundle_settings_message__commons_notify_comment_created'])) {
    $data['field_bundle_settings_message__commons_notify_comment_created']->value['extra_fields']['display']['message__message_text__0']['cmnc_message'] = array(
      'weight' => 1,
      'visible' => FALSE,
    ); /* WAS: '' */
    $data['field_bundle_settings_message__commons_notify_comment_created']->value['extra_fields']['display']['message__message_text__1']['cmnc_message'] = array(
      'weight' => 6,
      'visible' => FALSE,
    ); /* WAS: '' */
    $data['field_bundle_settings_message__commons_notify_comment_created']->value['extra_fields']['display']['message__message_text__1']['message_notify_email_body'] = array(
      'visible' => TRUE,
      'weight' => 0,
    ); /* WAS: '' */
    $data['field_bundle_settings_message__commons_notify_comment_created']->value['extra_fields']['display']['message__message_text__1']['message_notify_email_subject'] = array(
      'weight' => 2,
      'visible' => FALSE,
    ); /* WAS: '' */
    $data['field_bundle_settings_message__commons_notify_comment_created']->value['extra_fields']['display']['message__message_text__2'] = array(
      'message_notify_email_body' => array(
        'weight' => 2,
        'visible' => FALSE,
      ),
    ); /* WAS: '' */
  }
  if (isset($data['field_bundle_settings_message__commons_notify_node_created_no_groups'])) {
    $data['field_bundle_settings_message__commons_notify_node_created_no_groups']->value = array(
      'view_modes' => array(),
      'extra_fields' => array(
        'form' => array(),
        'display' => array(
          'message__message_text__2' => array(),
          'message__message_text__0' => array(),
          'message__message_text__1' => array(),
        ),
      ),
    ); /* WAS: '' */
  }
}

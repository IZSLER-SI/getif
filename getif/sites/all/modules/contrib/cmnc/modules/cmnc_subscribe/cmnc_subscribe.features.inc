<?php
/**
 * @file
 * cmnc_subscribe.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cmnc_subscribe_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cmnc_subscribe_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function cmnc_subscribe_default_message_type() {
  $items = array();
  $items['cmnc_group_membership_deleted'] = entity_import('message_type', '{
    "name" : "cmnc_group_membership_deleted",
    "description" : "Group membership deleted",
    "argument_keys" : [],
    "argument" : [],
    "category" : "commons_notify",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "@{message:user:name} removed you from group [message:field-target-nodes:0:title]\\r\\n",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E@{message:user:name} removed you from group [message:field-target-nodes:0:title]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "Hi [message:field-target-users:0:name],\\r\\n\\r\\n@{message:user:name} removed your account from group [message:field-target-nodes:0:title]\\r\\n\\r\\nChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003EHi [message:field-target-users:0:name],\\u003C\\/p\\u003E\\n\\u003Cp\\u003E@{message:user:name} removed your account from group [message:field-target-nodes:0:title]\\u003C\\/p\\u003E\\n\\u003Cp\\u003EChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E removed you from group \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E removed you from group \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['cmnc_group_membership_request_approved'] = entity_import('message_type', '{
    "name" : "cmnc_group_membership_request_approved",
    "description" : "Group membership request approved",
    "argument_keys" : [],
    "argument" : [],
    "category" : "commons_notify",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "@{message:user:name} approved your membership request in group [message:field-target-nodes:0:title]\\r\\n",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E@{message:user:name} approved your membership request in group [message:field-target-nodes:0:title]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "Hi [message:field-target-users:0:name],\\r\\n\\r\\n@{message:user:name} approved your membership request in group [message:field-target-nodes:0:title].\\r\\n\\r\\nChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003EHi [message:field-target-users:0:name],\\u003C\\/p\\u003E\\n\\u003Cp\\u003E@{message:user:name} approved your membership request in group [message:field-target-nodes:0:title].\\u003C\\/p\\u003E\\n\\u003Cp\\u003EChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E approved your membership request in group \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E approved your membership request in group \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['cmnc_group_membership_request_denied'] = entity_import('message_type', '{
    "name" : "cmnc_group_membership_request_denied",
    "description" : "Group membership request denied",
    "argument_keys" : [],
    "argument" : [],
    "category" : "commons_notify",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "@{message:user:name} denied your membership request in group [message:field-target-nodes:0:title]\\r\\n",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E@{message:user:name} denied your membership request in group [message:field-target-nodes:0:title]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "Hi [message:field-target-users:0:name],\\r\\n\\r\\n@{message:user:name} denied your membership request in group [message:field-target-nodes:0:title]\\r\\n\\r\\nChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003EHi [message:field-target-users:0:name],\\u003C\\/p\\u003E\\n\\u003Cp\\u003E@{message:user:name} denied your membership request in group [message:field-target-nodes:0:title]\\u003C\\/p\\u003E\\n\\u003Cp\\u003EChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E denied your membership request in group \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E denied your membership request in group \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['cmnc_member_invited_to_private_group'] = entity_import('message_type', '{
    "name" : "cmnc_member_invited_to_private_group",
    "description" : "Member invited to private group",
    "argument_keys" : [],
    "argument" : [],
    "category" : "commons_notify",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "@{message:user:name} has invited you to participate in private group [message:field-target-nodes:0:title]\\r\\n",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E@{message:user:name} has invited you to participate in private group [message:field-target-nodes:0:title]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "Hi [message:field-target-users:0:name],\\r\\n\\r\\n@{message:user:name} invited you to participate in private group [message:field-target-nodes:0:title].\\r\\n\\r\\nChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings\\r\\n",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003EHi [message:field-target-users:0:name],\\u003C\\/p\\u003E\\n\\u003Cp\\u003E@{message:user:name} invited you to participate in private group [message:field-target-nodes:0:title].\\u003C\\/p\\u003E\\n\\u003Cp\\u003EChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E has invited you to particpate in private group \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E has invited you to particpate in private group \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['cmnc_user_followed'] = entity_import('message_type', '{
    "name" : "cmnc_user_followed",
    "description" : "CMNC User Followed",
    "argument_keys" : [],
    "argument" : [],
    "category" : "commons_notify",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "@{message:user:name} is now following [message:field-target-users:0:name]\\r\\n",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E@{message:user:name} is now following [message:field-target-users:0:name]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "Hi [message:field-target-users:0:name],\\r\\n\\r\\n@{message:user:name} is now following you.\\r\\n\\r\\nChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003EHi [message:field-target-users:0:name],\\u003C\\/p\\u003E\\n\\u003Cp\\u003E@{message:user:name} is now following you.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E is now following \\u003Ca href=\\u0022[message:field-target-users:0:url]\\u0022\\u003E[message:field-target-users:0:name]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E is now following \\u003Ca href=\\u0022[message:field-target-users:0:url]\\u0022\\u003E[message:field-target-users:0:name]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['cmnc_user_requests_group_membership'] = entity_import('message_type', '{
    "name" : "cmnc_user_requests_group_membership",
    "description" : "User requests group membership",
    "argument_keys" : [],
    "argument" : [],
    "category" : "commons_notify",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "@{message:user:name} requests membership in group [message:field-target-nodes:0:title]\\r\\n",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E@{message:user:name} requests membership in group [message:field-target-nodes:0:title]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "Hi [message:user:name],\\r\\n\\r\\nThere is a new membership request in group [message:field-target-nodes:0:title] from @{message:user:name}.\\r\\n\\r\\nPermalink: [message:field-target-nodes:0:url]\\r\\n\\r\\nChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003EHi [message:user:name],\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThere is a new membership request in group [message:field-target-nodes:0:title] from @{message:user:name}.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EPermalink: [message:field-target-nodes:0:url]\\u003C\\/p\\u003E\\n\\u003Cp\\u003EChange email notifications at [site:url]user\\/[message:user:uid]\\/notification-settings\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E requests membership in group \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture:35x35] \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E requests membership in group \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}

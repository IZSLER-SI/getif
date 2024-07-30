<?php
/**
 * @file
 * cmnc_subscribe.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function cmnc_subscribe_default_rules_configuration() {
  $items = array();
  $items['rules_cmnc_og_member_invite_private'] = entity_import('rules_config', '{ "rules_cmnc_og_member_invite_private" : {
      "LABEL" : "OG member invited to private group",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "CMNC" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_user_insert" ],
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
        { "entity_has_field" : {
            "entity" : [ "og-membership:group" ],
            "field" : "field_og_subscribe_settings"
          }
        },
        { "data_is" : {
            "data" : [ "og-membership:group:field-og-subscribe-settings" ],
            "value" : "invitation"
          }
        },
        { "NOT data_is" : { "data" : [ "account" ], "value" : [ "site:current-user" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "cmnc_member_invited_to_private_group",
              "param_user" : [ "site:current-user" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-nodes:0" ],
            "value" : [ "og-membership:group" ]
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-users:0" ],
            "value" : [ "account" ]
          }
        }
      ]
    }
  }');
  $items['rules_cmnc_subscribe_cmnc_og_member_subscribe_denied'] = entity_import('rules_config', '{ "rules_cmnc_subscribe_cmnc_og_member_subscribe_denied" : {
      "LABEL" : "OG member subscribe (Denied)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "CMNC" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_user_blocked" ],
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "3" } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "cmnc_group_membership_request_denied",
              "param_user" : [ "site:current-user" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-nodes:0" ],
            "value" : [ "og-membership:group" ]
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-users:0" ],
            "value" : [ "account" ]
          }
        }
      ]
    }
  }');
  $items['rules_cmnc_subscribe_og_member_subscribe_approved'] = entity_import('rules_config', '{ "rules_cmnc_subscribe_og_member_subscribe_approved" : {
      "LABEL" : "OG member subscribe (Approved)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "CMNC" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_user_approved" ],
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "cmnc_group_membership_request_approved",
              "param_user" : [ "site:current-user" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-nodes:0" ],
            "value" : [ "og-membership:group" ]
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-users:0" ],
            "value" : [ "account" ]
          }
        }
      ]
    }
  }');
  $items['rules_cmnc_subscribe_og_member_subscribe_deleted'] = entity_import('rules_config', '{ "rules_cmnc_subscribe_og_member_subscribe_deleted" : {
      "LABEL" : "OG member subscribe (Deleted)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "CMNC" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_user_delete" ],
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
        { "NOT data_is" : { "data" : [ "account" ], "value" : [ "site:current-user" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "cmnc_group_membership_deleted",
              "param_user" : [ "site:current-user" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-nodes:0" ],
            "value" : [ "og-membership:group" ]
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-users:0" ],
            "value" : [ "account" ]
          }
        }
      ]
    }
  }');
  $items['rules_cmnc_subscribe_og_member_subscribe_pending'] = entity_import('rules_config', '{ "rules_cmnc_subscribe_og_member_subscribe_pending" : {
      "LABEL" : "OG member subscribe (Pending)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "CMNC" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_user_insert" ],
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "2" } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "cmnc_user_requests_group_membership",
              "param_user" : [ "site:current-user" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-nodes:0" ],
            "value" : [ "og-membership:group" ]
          }
        }
      ]
    }
  }');
  return $items;
}

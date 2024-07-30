This module adds a Facebook style message notification interface to Drupal
Commons.

Dependencies
============
* Drupal Commons 3.3 or later. (https://drupal.org/project/commons)
* qtips (https://drupal.org/project/qtip)
* Features Override (https://drupal.org/project/features_override)


Installation
============
* Download and enable the module as usual (and it's dependencies)
  * Make sure you review the install instructions for the qTips module.
* Due to an issue with features overrides, you will need to update the display
  settings of all of the commons_follow_* message types.

Submodules
==========
* cmnc_subscribe
  * Provides additional notifications for the following events:
    * When a user follows you.
    * When someone requests membership in a private group that you own.
    * When your membership request to a group is approved/denied.
* cmnc_ui
  * Updates the "Notification Settings" tab on the user profile page with
    additional subscription options so that users can choose which
    notifications appear in the notification center.

Configuration
=============
* Enable the notification center by:
  * Configuration -> System -> Message subscribe settings
    (admin/config/system/message-subscribe)
  * Select "Commons Message Notification Center" under "Default Message Notifiers".
    * NOTE: Do not do this if you are also enabling the cmnc_ui submodule.
  * Click Save
* Go to Structure => Features => Commons Message Notfication Center
  * Revert the CMNC Features.
* Grant users permission to use or administer the notification center.
  * By default, authenticated users are granted permission to use the module.
* Optional: Add the "Commons Message Notification Icon" block to your site layout.
  * By default, the notification icon is added to Commons Utility Links block.
* Additional configuration options are available at /admin/config/system/cmnc.
  * Option to delete old viewed notifications.
  * Enable the display of the notification icon in the Commons Utility Links
    block.
* Setting Message Displays
  * Go to /admin/structure/messages
  * Click "manage display" for each of the following message types:
    * commons_notify_comment_created
    * commons_notify_node_created
    * commons_notify_node_created_no_groups
  * Update the display settings on each of the above message types as follows:
    * Display: Notify - Email subject
      * Only "Message text 0 partial" marked as visible.  All others hidden.
    * Display: Notify - Email body
      * Only "Message text 1 partial" marked as visible.  All others hidden.
    * Display: Notify - CMNC
      * Only "Message text 2 partial" marked as visible.  All others hidden.


Upgrading from Alpha 1 to Alpha 2
=================================
You should completely uninstall the alpha1 version before
upgrading to the alpha2 release.


Notifications that appear in the notification center
====================================================
The following events will trigger notifications to be displayed in the
notification center.

* When anyone creates a node in a group that you are following.
* When anyone comments on a node that you are following.
* Anytime a user you are following creates a node or posts a comment.
* Anytime a user creates a node with a topic that you are following.


Additional notifications provided by the cmnc_subscribe submodule.

* When a user follows you.
* When someone requests membership in a private group that you own.
* When your membership request to a group is approved/denied.
* When your membership to a group is revoked (blocked).
* When your user account is removed from a group by a group administrator.
* When you are invited to join a private group.


Customizing the notification messages
=====================================
The notification messages that appear in the notification center can be
customized via the Message Types administration screen at
/admin/structure/messages.  The following message types are current used:

* commons_notify_comment_created
* commons_notify_node_created
* commons_notify_node_created_no_groups
* cmnc_group_membership_request_approved  (provided by cmnc_subscribe module)
* cmnc_group_membership_request_denied    (provided by cmnc_subscribe module)
* cmnc_user_requests_group_membership     (provided by cmnc_subscribe module)
* cmnc_member_invited_to_private_group    (provided by cmnc_subscribe module)
* cmnc_group_membership_deleted           (provided by cmnc_subscribe module)
* cmnc_user_followed                      (provided by cmnc_subscribe module)


In all of the above, message #2 is the default message that gets rendered.
The CMNC Display determines which message is rendered, so you can add custom
messages to the list and just update the settings of the CMNC display to
use your custom messages.

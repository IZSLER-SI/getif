<?php
/**
 * @file
 * Renders the Notifications Icon block.
 */
?>

<div class="cmnc-notification-icon-block <?php print $message_count_class; ?>">
  <div class="qtip-link">
    <span class="qtip-header">Notifications</span>
    <span class="qtip-tooltip"><?php print $notification_content; ?></span>
    <div class="cmnc-notification-icon">
      <span class="cmnc-message-count"><?php print $unread_message_count; ?></span>
    </div>
  </div>
</div>

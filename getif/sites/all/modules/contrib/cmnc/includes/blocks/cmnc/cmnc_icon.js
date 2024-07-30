/**
 * @file
 * JS for the CMNC Message Notification Icon block.
 */

(function ($) {
  Drupal.behaviors.cmnc_icon = {
    attach: function(context) {
      $('.qtip-link').bind('click', Drupal.behaviors.cmnc_icon.markRead);
    },
    /**
     * Triggers an AJAX call to flag the displayed messages as read.
     */
    markRead: function() {
      // Only do the callback if there is at least 1 new message.
      if ($('.view-display-id-block_notification_icon .cmnc-viewed-No').length > 0) {
        // Get IDs of unread messages.
        var re = /(cmnc-message-id--)(\d+)/;
        var message_ids = [];
        $('.view-display-id-block_notification_icon .cmnc-viewed-No').each(function() {
          var matches = re.exec($(this).attr('class'));
          var message_id = matches[2];
          message_ids.push(message_id);
        });

        var messages_param = message_ids.join(',');

        $.ajax({
          url: Drupal.settings.basePath + 'cmnc/ajax/flag_read',
          method: 'GET',
          data: { messages: messages_param }
        });
      }
    }
  };
})(jQuery);

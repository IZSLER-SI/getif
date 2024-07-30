/**
 * @file
 * JS for the CMNC My Notifications Page and icon.
 */

(function ($) {

  'use strict';

  Drupal.behaviors.cmnc_page = {
    attach: function(context) {
      // Make sure the user has viewed the page for at least 5 seconds.
      setTimeout(Drupal.behaviors.cmnc_page.markRead, 5000);
    },
    /**
     * Triggers an AJAX call to flag the displayed messages as read.
     */
    markRead: function() {
      // Only do the callback if there is at least 1 new message.
      if ($('.page-my-notifications .view-display-id-page .cmnc-viewed-No').length > 0) {
        // Get IDs of unread messages.
        var re = /(cmnc-message-id--)(\d+)/;
        var message_ids = [];
        $('.page-my-notifications .view-display-id-page .cmnc-viewed-No').each(function() {
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


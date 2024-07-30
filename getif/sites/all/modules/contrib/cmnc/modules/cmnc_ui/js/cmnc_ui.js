/**
 * @file
 * UI related handling for the cmnc_ui module.
 */

/**
 * Reformats the Notification settings flag displays to be checkboxes.
 *
 * Stolen from commons_origins.js.
 */
jQuery(document).ready(function($){
  'use strict';

  var cmnc_set_follow_checkboxes = function(){
    $('#quicktabs-commons_follow_ui .cmnc-flag-link a.flag, #quicktabs-tabpage-commons_follow_ui-notification_types a.flag').each(function(){
      var a_target = $(this).addClass('formatted-as-checkbox').removeClass('action-item-small action-item-small-active');

      if (a_target.children('span').length === 0) {
        a_target.wrapInner('<span></span>');
      }

      if (a_target.hasClass('flag-action') && a_target.children('input').length === 0) {
        a_target.prepend('<input type="checkbox">');
      } else if (a_target.children('input').length === 0) {
        a_target.prepend('<input type="checkbox" checked>');
      }
    });
  };

  cmnc_set_follow_checkboxes();

  $(document).ajaxComplete(function(){
    cmnc_set_follow_checkboxes();
  });
});

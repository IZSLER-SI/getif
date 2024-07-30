<?php
/**
 * @file
 * Defines the CMNC block.
 */

/**
 * Block info array for the CMNC block.
 *
 * @param array $blocks
 *   Set of all blocks defined for this module.
 */
function cmnc_block_cmnc_info(&$blocks) {
  $blocks[CMNC_BLOCK_CMNC] = array(
    'info' => t('Commons Message Notification Icon'),
    'cache' => DRUPAL_NO_CACHE,
  );
}

/**
 * Renders the Message Notification Icon block.
 *
 * @return array
 *   The render array for the block.
 */
function cmnc_block_cmnc_view() {
  if (!user_access(CMNC_PERM_USE)) {
    return array();
  }

  list($content, $count) = cmnc_block_cmnc_get_notifications();
  $module_path = drupal_get_path('module', 'cmnc');

  $block = array(
    'subject' => t('Commons Message Notification Icon'),
    'content' => array(
      '#theme' => 'cmnc_notification_icon',
      '#unread_message_count' => $count,
      '#notification_content' => $content,
      '#message_count_class' => $count > 0 ? 'cmnc-message-count-unread' : 'cmnc-message-count-none',
      '#title' => t('My Notifications'),
      '#attached' => array(
        'css' => array(
          $module_path . '/includes/blocks/cmnc/cmnc_icon.css',
        ),
        'js' => array(
          $module_path . '/includes/blocks/cmnc/cmnc_icon.js',
        ),
      ),
    ),
  );
  return $block;
}

/**
 * Renders the notifications for the notifications icon popup.
 *
 * @return string
 *   The rendered content.
 */
function cmnc_block_cmnc_get_notifications() {
  $view = views_get_view('my_notifications');
  $view->set_display('block_notification_icon');
  $view->execute('block_notification_icon');
  $count = count($view->result);
  $content = $view->preview('block_notification_icon');
  return array($content, $count);
}

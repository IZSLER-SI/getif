<?php
/**
 * @file
 * Enter file description.
 */

/**
 * Class description.
 */
class CommonsMessageCenterMessage extends MessageNotifierBase implements MessageNotifierInterface {

  /**
   * Overrides the default delivery method to write the message to a log.
   *
   * @param array $output
   *   Array keyed by the view mode, and the rendered entity in the
   *   specified view mode.
   *
   * @return bool|void
   *   TRUE or FALSE based on delivery status.
   */
  public function deliver(array $output = array()) {
    $message = $this->message;
    $plugin = $this->plugin;

    $message_digest = array(
      'receiver' => $message->uid,
      'gid' => !empty($message->gid) ? $message->gid : 0,
      'notifier' => $plugin['name'],
      'viewed' => FALSE,
      'timestamp' => $message->timestamp,
    );
    // This will only have a value if the message is not a message_subscribe message.
    $mid = NULL;
    if (isset($message->mid)) {
      $mid = $message->mid;
    }

    // Our $message is a cloned copy of the original $message with the mid field removed to
    // prevent overwriting (this happens in message_subscribe) so we need to fetch the mid manually.
    if (empty($mid)) {
      $mid = db_select('message', 'm')
        ->fields('m', array('mid'))
        ->condition('timestamp', $message->timestamp)
        ->condition('type', $message->type)
        ->execute()
        ->fetchField();
    }

    if (!empty($mid)) {
      $message_digest['mid'] = $mid;
    }

    $success = drupal_write_record('cmnc', $message_digest);
    return $success !== FALSE;
  }
}

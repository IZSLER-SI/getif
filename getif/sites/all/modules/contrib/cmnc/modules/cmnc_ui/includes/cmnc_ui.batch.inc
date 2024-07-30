<?php
/**
 * @file
 * Callbacks for batch api operations.
 */


//region Callbacks
/**
 * Batch API callback for updating user notification defaults.
 *
 * @param bool $default_value
 *   The default value to set for user notifications.
 *
 * @param bool $replace
 *   TRUE to update all users, even if they have an existing default setting.
 *
 * @param array $context
 *   The batch operation context.
 */
function cmnc_ui_batch_set_user_defaults($default_value, $replace, &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_user'] = 0;
    $query = _cmnc_ui_user_default_settings_query(!$replace, TRUE);
    $user_count = $query->execute()->fetchField();
    $context['sandbox']['max'] = $user_count;
  }

  $limit = variable_get('cmnc_ui_batch_update_size', 5);

  $query = _cmnc_ui_user_default_settings_query(!$replace, FALSE);
  $query->condition('u.uid', $context['sandbox']['current_user'], '>');
  $query->range(0, $limit);
  $users_to_update = $query->execute();
  $updated = FALSE;

  foreach ($users_to_update as $row) {
    $context['sandbox']['current_user'] = $row->uid;
    $context['sandbox']['progress']++;
    $updated = TRUE;

    $account = user_load($row->uid);
    $edit = array(
      'cmnc_subscribe_message_center' => array(
        LANGUAGE_NONE => array(
          0 => array(
            'value' => (bool) $default_value,
          ),
        ),
      ),
    );
    user_save($account, $edit);
  }

  if ($updated && $context['sandbox']['progress'] <= $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
  elseif (!$updated) {
    $context['finished'] = 1;
  }
}

/**
 * Batch API callback for defaulting all CMNC notification flags for users.
 *
 * @param array $context
 *   The batch operation context.
 */
function cmnc_ui_batch_set_flag_defaults(&$context) {
  $cmnc_flags = cmnc_flag_get_flags();
  $cmnc_fids = _cmnc_ui_batch_get_cmnc_flags($cmnc_flags);
  $subscription_flags = _cmnc_ui_batch_get_subscription_flags();
  $subscription_fids = $subscription_flags['subscription_fids'];
  $subscription_flags_by_id = $subscription_flags['subscription_flags_by_id'];

  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_fcid'] = 0;
    $query = _cmnc_ui_batch_get_flags_query($cmnc_fids, $subscription_fids, TRUE);
    $flag_count = $query->execute()->fetchField();
    $context['sandbox']['max'] = $flag_count;
  }
  $updated = FALSE;
  $limit = variable_get('cmnc_ui_batch_update_size', 5);

  $query = _cmnc_ui_batch_get_flags_query($cmnc_fids, $subscription_fids, FALSE);
  $query->condition('fc.fcid', $context['sandbox']['current_fcid'], '>');
  $query->range(0, $limit);
  $results = $query->execute();

  $prefix = variable_get('message_subscribe_flag_prefix', 'subscribe') . '_';
  foreach ($results as $row) {
    $context['sandbox']['current_fcid'] = $row->fcid;
    $context['sandbox']['progress']++;
    $updated = TRUE;

    if (!isset($subscription_flags_by_id[$row->fid])) {
      continue;
    }
    $subscription_flag = $subscription_flags_by_id[$row->fid];

    $cmnc_flag_name = 'cmnc_' . str_replace($prefix, '', $subscription_flag->name);
    if ($cmnc_flag_name == 'cmnc_group') {
      $cmnc_flag_name = 'cmnc_node';
    }
    if (!isset($cmnc_flags[$cmnc_flag_name])) {
      continue;
    }
    $cmnc_flag = $cmnc_flags[$cmnc_flag_name];

    $new_flag = array();
    $new_flag['fid'] = $cmnc_flag->fid;
    $new_flag['content_type'] = $row->content_type;
    $new_flag['content_id'] = $row->content_id;
    $new_flag['uid'] = $row->uid;
    $new_flag['sid'] = $row->sid;

    drupal_write_record('flag_content', $new_flag);
  }

  if ($updated && $context['sandbox']['progress'] <= $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
  elseif (!$updated) {
    $context['finished'] = 1;
  }
}

/**
 * Batch API callback for defaulting all CMNC notification type flags for users.
 *
 * @param array $context
 *   The batch operation context.
 */
function cmnc_ui_batch_set_notification_type_defaults(&$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_uid'] = 0;
    $user_count = db_query('SELECT COUNT(1) FROM {users} u WHERE u.status=1')->fetchField();
    $context['sandbox']['max'] = $user_count;
  }

  $updated = FALSE;
  $limit = variable_get('cmnc_ui_batch_update_size', 5);
  $query = db_select('users', 'u')
    ->fields('u', array('uid'));
  $query->condition('u.uid', $context['sandbox']['current_uid'], '>');
  $query->range(0, $limit);
  $results = $query->execute();

  $flags = flag_get_flags();
  $notification_types = cmnc_ui_get_notification_type_flags();
  foreach ($results as $row) {
    $context['sandbox']['current_uid'] = $row->uid;
    $context['sandbox']['progress']++;
    $updated = TRUE;
    $account = user_load($row->uid);

    foreach ($notification_types as $notification_type => $settings) {
      foreach ($settings['notifiers'] as $notifier => $flag_name) {
        if (!isset($flags[$flag_name])) {
          continue;
        }
        flag('flag', $flag_name, $account->uid, $account);
      }
    }
  }

  if ($updated && $context['sandbox']['progress'] <= $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
  elseif (!$updated) {
    $context['finished'] = 1;
  }
}
//endregion

/**
 * Batch API completion callback.
 *
 * @param bool $success
 *   If the batch operations completed successfully.
 *
 * @param array $results
 *   Collection of results from batch operations.
 *
 * @param array $operations
 *   The operations performed during the batch.
 */
function cmnc_ui_batch_init_defaults_finished($success, $results, $operations) {
  if ($success) {
    $message = t('Updates completed successfully.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}

/**
 * Retrieves a list of CMNC flags for use during the batch update.
 *
 * @param array $cmnc_flags
 *   An array of all CMNC flags.
 *
 * @return array
 *   An array of CMNC flag IDs.
 */
function _cmnc_ui_batch_get_cmnc_flags($cmnc_flags) {
  $cmnc_fids = &drupal_static(__FUNCTION__);

  if (!isset($cmnc_fids)) {
    $cmnc_fids = array();

    foreach ($cmnc_flags as $flag) {
      $cmnc_fids[] = $flag->fid;
    }
  }

  return $cmnc_fids;
}

/**
 * Retrieves a list of subscription flags for use during the batch update.
 *
 * @return array
 *   An associative array with keys 'subscription_fids'
 *   and 'subscription_flags_by_id'.
 */
function _cmnc_ui_batch_get_subscription_flags() {
  $flags = &drupal_static(__FUNCTION__);

  if (!isset($flags)) {
    $subscription_flags = message_subscribe_flag_get_flags();
    $subscription_fids = array();
    $subscription_flags_by_id = array();
    foreach ($subscription_flags as $flag) {
      $subscription_fids[] = $flag->fid;
      $subscription_flags_by_id[$flag->fid] = $flag;
    }

    $flags = array(
      'subscription_fids' => $subscription_fids,
      'subscription_flags_by_id' => $subscription_flags_by_id,
    );
  }

  return $flags;
}

/**
 * Generates a query for selecting flags to be updated during batch operations.
 *
 * @param array $cmnc_fids
 *   An array of CMNC Notification Flags.
 *
 * @param array $subscription_fids
 *   An array of message subscription flags.
 *
 * @param bool $count
 *   TRUE to return a count query, FALSE to return individual flags.
 *
 * @return SelectQuery
 *   The SelectQuery to be executed.
 */
function _cmnc_ui_batch_get_flags_query($cmnc_fids, $subscription_fids, $count = FALSE) {
  $subquery = db_select('flag_content', 'fc1');
  $subquery->fields('fc1', array('fcid'));
  $subquery->where('fc1.uid=fc.uid');
  $subquery->where('fc1.content_id=fc.content_id');
  $subquery->condition('fc1.fid', $cmnc_fids, 'IN');

  $select = db_select('flag_content', 'fc');
  if ($count) {
    $select->addExpression('COUNT(DISTINCT fc.fcid)', 'flag_count');
  }
  else {
    $select->fields('fc');
  }

  $select->condition('fc.fid', $subscription_fids, 'IN');
  $select->notExists($subquery);
  $select->orderBy('fc.fcid');

  return $select;
}

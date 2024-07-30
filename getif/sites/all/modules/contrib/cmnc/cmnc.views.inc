<?php
/**
 * @file
 * Views integration hooks.
 */

/**
 * Implements hook_views_data().
 */
function cmnc_views_data() {
  $data = array(
    'cmnc' => array(
      'table' => array(
        'group' => t('Commons Message Notification Center'),
        'base' => array(
          'field' => 'id',
          'title' => t('Commons Message Notification Center'),
          'help' => t('Contains a log of all message notifications for users.'),
          'weight' => 0,
        ),
        'join' => array(
          'message' => array(
            'left_field' => 'mid',
            'field' => 'mid',
          ),
          'users' => array(
            'left_field' => 'uid',
            'field' => 'receiver',
          ),
        ),
      ),
      'id' => array(
        'title' => t('Notification ID'),
        'help' => t('The ID of the notification.'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'mid' => array(
        'title' => t('Message ID'),
        'help' => t('The ID of the message.'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'relationship' => array(
          'base' => 'message',
          'base field' => 'mid',
          'handler' => 'views_handler_relationship',
          'label' => t('Message'),
          'title' => t('Message'),
          'help' => t('The message being sent to the user.'),
        ),
      ),
      'gid' => array(
        'title' => t('Group ID'),
        'help' => t('The ID of the group.'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'receiver' => array(
        'title' => t('User ID'),
        'help' => t('The ID of the user to be notified.'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'relationship' => array(
          'base' => 'users',
          'base field' => 'uid',
          'handler' => 'views_handler_relationship',
          'label' => t('Receiver'),
          'title' => t('User'),
          'help' => t('The user receiving the notification.'),
        ),
      ),
      'notifier' => array(
        'title' => t('Notifier'),
        'help' => t('The plugin that generated the notification.'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_string',
        ),
      ),
      'viewed' => array(
        'title' => t('Viewed'),
        'help' => t('Indicates if the message has been viewed.'),
        'field' => array(
          'handler' => 'views_handler_field_boolean',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_boolean_operator',
          'label' => t('Viewed'),
          'type' => 'yes-no',
          'use equal' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'timestamp' => array(
        'title' => t('Timestamp'),
        'help' => t('When the message was created.'),
        'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_date',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
      ),
    ),
  );

  return $data;
}

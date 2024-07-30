<?php
/**
 * @file
 * Defines the Commons Message Notification Center plugin.
 */

$plugin = array(
  'title' => t('Commons Message Notification Center'),
  'description' => t('Displays messages in the Commons Message Notification Center.'),
  'class' => 'CommonsMessageCenterMessage',
  'view_modes' => array(
    'cmnc_message' => array('label' => t('Notify - CMNC')),
  ),
);

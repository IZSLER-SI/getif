<?php
/**
 * @file
 * cmnc.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cmnc_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'my_notifications';
  $view->description = 'Provides the page and block displays for the My Notifications system.';
  $view->tag = 'CMNC';
  $view->base_table = 'cmnc';
  $view->human_name = 'My Notifications';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'My Notifications';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'use cmnc';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'cmnc-viewed-[viewed] cmnc-message-id--[id]';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No new notifications are available.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Receiver User Account */
  $handler->display->display_options['relationships']['receiver']['id'] = 'receiver';
  $handler->display->display_options['relationships']['receiver']['table'] = 'cmnc';
  $handler->display->display_options['relationships']['receiver']['field'] = 'receiver';
  $handler->display->display_options['relationships']['receiver']['ui_name'] = 'Receiver User Account';
  /* Relationship: Message Entity */
  $handler->display->display_options['relationships']['mid']['id'] = 'mid';
  $handler->display->display_options['relationships']['mid']['table'] = 'cmnc';
  $handler->display->display_options['relationships']['mid']['field'] = 'mid';
  $handler->display->display_options['relationships']['mid']['ui_name'] = 'Message Entity';
  /* Field: Commons Message Notification Center: Notification ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'cmnc';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: Commons Message Notification Center: Message ID */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'cmnc';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Commons Message Notification Center: User ID */
  $handler->display->display_options['fields']['receiver']['id'] = 'receiver';
  $handler->display->display_options['fields']['receiver']['table'] = 'cmnc';
  $handler->display->display_options['fields']['receiver']['field'] = 'receiver';
  $handler->display->display_options['fields']['receiver']['exclude'] = TRUE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'receiver';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  /* Field: Commons Message Notification Center: Viewed */
  $handler->display->display_options['fields']['viewed']['id'] = 'viewed';
  $handler->display->display_options['fields']['viewed']['table'] = 'cmnc';
  $handler->display->display_options['fields']['viewed']['field'] = 'viewed';
  $handler->display->display_options['fields']['viewed']['exclude'] = TRUE;
  $handler->display->display_options['fields']['viewed']['not'] = 0;
  /* Field: Message: Rendered Message */
  $handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_message';
  $handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['relationship'] = 'mid';
  $handler->display->display_options['fields']['rendered_entity']['label'] = '';
  $handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['display'] = 'view';
  $handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'cmnc_message';
  $handler->display->display_options['fields']['rendered_entity']['bypass_access'] = 0;
  /* Field: Commons Message Notification Center: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'cmnc';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'time ago';
  /* Sort criterion: Commons Message Notification Center: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'cmnc';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'receiver';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'user';
  /* Filter criterion: Message: Message category */
  $handler->display->display_options['filters']['type_category']['id'] = 'type_category';
  $handler->display->display_options['filters']['type_category']['table'] = 'message';
  $handler->display->display_options['filters']['type_category']['field'] = 'type_category';
  $handler->display->display_options['filters']['type_category']['relationship'] = 'mid';
  $handler->display->display_options['filters']['type_category']['value'] = array(
    'message_type' => 'message_type',
    'commons_notify' => 'commons_notify',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_notification_icon');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'cmnc-viewed-[viewed] cmnc-message-id--[id]';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['empty'] = TRUE;
  $handler->display->display_options['footer']['area']['content'] = '<div class="cmnc-view-all"><a href="/user/!1/my-notifications">View all notifications</a></div>';
  $handler->display->display_options['footer']['area']['format'] = 'full_html';
  $handler->display->display_options['footer']['area']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Commons Message Notification Center: Notification ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'cmnc';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: Commons Message Notification Center: Message ID */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'cmnc';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Commons Message Notification Center: User ID */
  $handler->display->display_options['fields']['receiver']['id'] = 'receiver';
  $handler->display->display_options['fields']['receiver']['table'] = 'cmnc';
  $handler->display->display_options['fields']['receiver']['field'] = 'receiver';
  $handler->display->display_options['fields']['receiver']['exclude'] = TRUE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'receiver';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  /* Field: Commons Message Notification Center: Viewed */
  $handler->display->display_options['fields']['viewed']['id'] = 'viewed';
  $handler->display->display_options['fields']['viewed']['table'] = 'cmnc';
  $handler->display->display_options['fields']['viewed']['field'] = 'viewed';
  $handler->display->display_options['fields']['viewed']['exclude'] = TRUE;
  $handler->display->display_options['fields']['viewed']['not'] = 0;
  /* Field: Message: Rendered Message */
  $handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_message';
  $handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['relationship'] = 'mid';
  $handler->display->display_options['fields']['rendered_entity']['label'] = '';
  $handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['display'] = 'view';
  $handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'cmnc_message';
  $handler->display->display_options['fields']['rendered_entity']['bypass_access'] = 0;
  /* Field: Commons Message Notification Center: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'cmnc';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'time ago';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Message: Message category */
  $handler->display->display_options['filters']['type_category']['id'] = 'type_category';
  $handler->display->display_options['filters']['type_category']['table'] = 'message';
  $handler->display->display_options['filters']['type_category']['field'] = 'type_category';
  $handler->display->display_options['filters']['type_category']['relationship'] = 'mid';
  $handler->display->display_options['filters']['type_category']['value'] = array(
    'message_type' => 'message_type',
    'commons_notify' => 'commons_notify',
  );
  /* Filter criterion: Commons Message Notification Center: Viewed */
  $handler->display->display_options['filters']['viewed']['id'] = 'viewed';
  $handler->display->display_options['filters']['viewed']['table'] = 'cmnc';
  $handler->display->display_options['filters']['viewed']['field'] = 'viewed';
  $handler->display->display_options['filters']['viewed']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'user/%/my-notifications';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'My Notifications';
  $handler->display->display_options['menu']['description'] = 'My Notifications';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['my_notifications'] = $view;

  return $export;
}

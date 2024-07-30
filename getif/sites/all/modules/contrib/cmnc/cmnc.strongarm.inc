<?php
/**
 * @file
 * cmnc.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cmnc_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qtip_hide_event_type';
  $strongarm->value = 'unfocus';
  $export['qtip_hide_event_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qtip_show_event_type';
  $strongarm->value = 'click';
  $export['qtip_show_event_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qtip_target_position';
  $strongarm->value = 'bottom_center';
  $export['qtip_target_position'] = $strongarm;

  return $export;
}

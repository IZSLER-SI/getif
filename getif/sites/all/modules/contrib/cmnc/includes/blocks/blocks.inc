<?php
/**
 * @file
 * Hook implementations for custom blocks.
 */

define('CMNC_BLOCK_CMNC', 'cmnc');

include_once "cmnc/cmnc.block.inc";

/**
 * Implements hook_block_info().
 */
function cmnc_block_info() {
  $blocks = array();

  cmnc_block_cmnc_info($blocks);

  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function cmnc_block_view($delta = '') {
  $block = array();

  switch ($delta) {
    case CMNC_BLOCK_CMNC:
      $block = cmnc_block_cmnc_view();
      break;
  }

  return $block;
}

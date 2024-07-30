<?php

/**
 * Inspired from the Menu Trail By Path module.
 *
 * Returns an array of parent candidates
 *
 * e.g. given the argument 'foo/bar/zee', this returns an array of
 * internal Drupal paths for 'foo', 'foo/bar', 'foo/bar/zee'.
 *
 * @param string $path
 *   A Drupal path alias.
 *
 * @return array
 *   An array of internal Drupal paths.
 */
function _link_trail_by_path_get_parent_candidates($path) {
  $path_exploded = explode('/', $path);

  do {
    $parent_path_temporary = implode('/', $path_exploded);
    $parent_path_candidates[] = drupal_get_normal_path($parent_path_temporary);
    $parent_path_candidates[] = drupal_get_path_alias($parent_path_temporary);
    array_pop($path_exploded);
  } while (!empty($path_exploded));

  $parent_path_candidates = array_values(array_unique(array_filter($parent_path_candidates)));

  // Allow other modules to alter the parent candidates.
  drupal_alter('link_trail_by_path_parent_candidates', $path, $parent_path_candidates);

  usort($parent_path_candidates, function($a, $b) {
    return strlen($a) - strlen($b);
  });

  return $parent_path_candidates;
}

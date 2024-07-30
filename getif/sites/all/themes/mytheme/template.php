<?php

/**
 * @file
 * The primary PHP file for this theme.
 */

function mytheme_theme() {
    return array(
        'user_profile_form' => array(
            // Forms always take the form argument.
            'arguments' => array('form' => NULL),
            'render element' => 'form',
            'template' => 'templates/user-profile-edit',
        ),
    );
}

function mytheme_preprocess_page(&$vars, $hook) {
    // Primary nav.
    $vars['primary_nav'] = FALSE;
    if ($vars['main_menu']) {
        // Build links.
        $vars['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
        // Provide default theme wrapper function.
        $vars['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
    }
    
}
/**
 * Theme wrapper function for the primary menu links
 */
function MYTHEME_menu_tree__primary(&$vars) {
    return '<ul class="flexnav" data-breakpoint="769">' . $vars['tree'] . '</ul>';
}



function mytheme_bootstrap_colorize_text_alter(array &$texts) {
    unset($texts['contains']);
}

function mytheme_bootstrap_iconize_text_alter(array &$texts) {
    $texts['contains'][t('download')] = 'download-alt';
    $texts['contains'][t('nuov')] = 'plus';
    $texts['contains'][t('salva')] = 'floppy-disk';
    $texts['contains'][t('filtra')] = 'filter';
    $texts['contains'][t('dashboard')] = 'dashboard';
    $texts['contains'][t('rimuovi')] = 'trash';
    $texts['contains'][t('elimina')] = 'trash';
    $texts['contains'][t('aggiungi')] = 'plus';
    $texts['contains'][t('anagrafica')] = 'glyphicon-edit';
    $texts['contains'][t('lista')] = 'list-alt';
    $texts['contains'][t('tirocini')] = 'list-alt';
    $texts['contains'][t('frequenze')] = 'list-alt';
    $texts['contains'][t('indietro')] = 'arrow-left';
    $texts['contains'][t('prosegui')] = 'arrow-right';
    $texts['contains'][t('genera')] = 'file';
    $texts['contains'][t('figure')] = 'list-alt';
    $texts['contains'][t('convenzioni')] = 'list-alt';
    $texts['contains'][t('soggetti')] = 'list-alt';
    $texts['contains'][t('gestione strutture')] = 'cog';
    $texts['contains'][t('gestione laboratori')] = 'cog';
    $texts['contains'][t('gestione segr')] = 'cog';
    $texts['contains'][t('budget')] = 'eur';
    $texts['contains'][t('completa')] = 'pencil';
    $texts['contains']['reset'] = 'erase';
    $texts['contains'][t('reset')] = 'erase';
    $texts['contains'][t('download')] = 'download-alt';
    $texts['contains'][t('chiudi registro')] = 'lock';
}


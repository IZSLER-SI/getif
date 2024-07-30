<?php

/**
 * @file
 * The primary PHP file for this theme.
 */

function helptheme_theme() {
    return array(

    );
}

function helptheme_preprocess_page(&$vars) {
    $vars['breadcrumb'] = '';

    unset($vars['page']['sidebar_first']);
}
/**
 * Theme wrapper function for the primary menu links
 */
function helptheme_menu_tree__primary(&$vars) {
    return '<ul class="flexnav" data-breakpoint="769">' . $vars['tree'] . '</ul>';
}



function helptheme_bootstrap_colorize_text_alter(array &$texts) {
    unset($texts['contains']);
}

function helptheme_bootstrap_iconize_text_alter(array &$texts) {
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
    $texts['contains'][t('gestione segr')] = 'cog';
    $texts['contains'][t('budget')] = 'eur';
    $texts['contains'][t('completa')] = 'pencil';
    $texts['contains'][t('reset')] = 'erase';
    $texts['contains'][t('download')] = 'download-alt';
    $texts['contains'][t('chiudi registro')] = 'lock';
}


<?php

/**
 * Theme budget manage
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_host_budget_manage_form($variables){
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    $form = $variables['form'];
    return getif_form_theme($form,'',false,false);
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function lperson_host_budget_manage_form($form, &$form_state) {
    global $base_url;
    $id_lperson = arg(2);
    $id_budget = arg(3);
    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Anagrafica Soggetto'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_back'),
        '#attributes' => array(
            'id_lperson' => $id_lperson
        )
    );
    $form['nav']['back']['#attributes']['id_lperson_parent'] = $id_lperson;
    $form['nav']['new'] = array(
        '#type' => 'button',
        '#value' => t('Nuovo').' '.t('Budget'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_new'),
        '#attributes' => array(
            'id_lperson' => $id_lperson
        )
    );
    // Content
    $header = array(
        t('Anno'),
        t('Budget'),
        t('Extra-Budget'),
        t('&nbsp;'),
    );
    db_set_active('getif_data');
    $query = db_select("budget", "b");
    $query->fields("b");
    $query->condition('b.id_lperson',$id_lperson);
    $query->condition('b.active',1);
    $query = $query->extend('TableSort')->orderByHeader($header)->extend('PagerDefault')->limit(10);
    $result = $query->execute();
    db_set_active();
    $rows = array();
    while($data = $result->fetchObject()) {
        $url = url($base_url . "/lperson_host/budget/" .$id_lperson. "/" .$data->id_budget, array('query' => drupal_get_query_parameters()));
        $rows[] = array(
            'data' => array(
                $data->year,
                !empty($data->a_amount)?money_format('%.2n',$data->a_amount):'-',
                !empty($data->a_extra_amount)?money_format('%.2n',$data->a_extra_amount):'-',
                t('<a href="@url"><span class="btn glyphicon glyphicon-pencil"></span>&nbsp;</a>', array(
                    '@url' => url($url),
                ))
            ),
            'class' => ($id_budget === $data->id_budget) ? array('success') : null,
        );
    }
    $form['fs_budget'] = array
    (
        '#type' => 'item',
        '#title' => t('Lista Budget Annuali'),
        '#prefix' => '<div id="fs-agreement-div">',
        '#suffix' => '</div>',
        '#title_display' => 'invisible',
        '#access' =>true
    );
    $form['fs_budget']['table'] = array
    (
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('Table has no row!'),
        '#attributes' => array(
            'id' => 'tabella'
        )
    );
    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function lperson_host_budget_manage_form_validate($form, &$form_state) {
    // empty
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_host_budget_manage_form_submit($form, &$form_state) {
    // empty
}

/**
 * @param $form
 * @param $form_state
 */
function remove_budget_submit($form, &$form_state) {
    $id_budget = $form_state['clicked_button']['#attributes']['id_budget'];
    setRecordState('budget', 'getif_data', 'id_budget', $id_budget,'active','0');
}


/**
 * @param $form
 * @param $form_state
 */
function goto_back($form, &$form_state) {
    getif_goto('lperson_host/edit/'.$form_state['clicked_button']['#attributes']['id_lperson'],array(),302,true);
}


/**
 * @param $form
 * @param $form_state
 */
function goto_new($form, &$form_state) {
    getif_goto('lperson_host/budget/'.$form_state['clicked_button']['#attributes']['id_lperson'],array(),302,true);
}

/* end */

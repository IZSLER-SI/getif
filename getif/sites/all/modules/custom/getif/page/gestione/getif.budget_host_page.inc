<?php

/**
 * @return string
 * @throws Exception
 */
function _tabella_budget() {
    global $base_url;
    $module_path = drupal_get_path('module', 'getif');
    $full_path = $module_path .'/css/getif.css';
    drupal_add_css($full_path);
    $id_lperson = arg(2);
    $id_budget = arg(3);
    $output = '';
    $link_lperson = $base_url.'/lperson_host/edit/'.$id_lperson;
    $output .= '<div class="col-md-12 form-container">';
    $output .= '
    <div class="bootstrap">
        <div class="page-head">
            <div class="wrapper clearfix">
                <h1 class="page-title">'.drupal_get_title().'</h1>
                    <div class="page-bar toolbarBox">
                        <div class="btn-toolbar">
                            <ul id="toolbar-nav" class="nav nav-pills pull-right collapse navbar-collapse">
                                <li>
                                    <button id="edit-goto-dashboard" onclick="location.href=\''.$base_url.'\';" value="Dashboard" class="btn btn-default form-submit icon-before">
                                    <span class="icon glyphicon glyphicon-dashboard" aria-hidden="true"></span>Dashboard</button>
                                </li>
                            </ul>
                                
                        </div>
                    </div>
                </div>
            </div>
        </div>';
    $output .= '<div class="row">';
    $output .= '<div class="col-md-12 form-container">';
    $output .= '<div class="panel panel-default">';
    $output .= '<div class="panel-body">';
    $output .= '<button id="edit-back" value="Anagrafica Soggetto" class="btn btn-default form-submit" onclick="location.href=\''.$link_lperson.'\';">Anagrafica Soggetto</button>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '<div class="row form-container"><div class="col-sm-12 col-xs-12">';

    $header = array(
        array(
            "data" => t('Anno'),
            "field" => "year",
            "sort" => "asc",
        ),
        array(
            "data" => t('Budget'),
            "field" => "a_amount"
        ),
        array(
            "data" => t('Extra-Budget'),
            "field" => "a_extra_amount"
        ),
        array(
            "data" => '&nbsp;',
        ),
    );
    db_set_active('getif_data');
    $query = db_select("budget", "b");
    $query->fields("b");
    $query->condition('b.id_lperson',$id_lperson);
    $query = $query->extend('TableSort')->orderByHeader($header)->extend('PagerDefault')->limit(10);
    $result = $query->execute();
    db_set_active();
    $rows = array();
    while($data = $result->fetchObject()) {
        $upd_url = url($base_url . "/lperson_host/budget/" .$id_lperson. "/" .$data->id_budget, array('query' => drupal_get_query_parameters()));
        //$del_url = url($base_url . "/delete_record/budget/" . $data->id_budget, array('query' => drupal_get_query_parameters()));
        $upd_btn = "<a href='" . $upd_url . "' class='btn btn-sm glyphicon glyphicon-pencil'></a>";
        $form['remove_budget_'.$data->id_budget]  = array (
            '#type' => 'submit',
            '#name' => 'remove_budget_'.$data->id_budget,
            '#value' => '',
            '#submit' => array('remove_budget_submit'),
            '#id' => 'edit-remove-budget-'.$data->id_budget,
            '#attributes' => array(
                'id_budget' => $data->id_budget,
                'class' => array('btn','glyphicon','glyphicon-trash'),
                'onclick' => 'if(!confirm("Sei sicuro di voler eliminare il Budget? I dati andranno persi definitivamente.")){return false;}'
            ),
        );
        //$del_btn = drupal_render(drupal_get_form($form['remove_budget_'.$data->id_budget]);
        $rows[] = array(
            'data' => array(
                $data->year,
                !empty($data->a_amount)?money_format('%.2n',$data->a_amount):'-',
                !empty($data->a_extra_amount)?money_format('%.2n',$data->a_extra_amount):'-',
                $upd_btn
            ),
            'class' => ($id_budget === $data->id_budget) ? array('success') : null,
        );
    }
    $output .= '<fieldset class="panel panel-default form-wrapper" id="edit-fs-budget">
                 <legend class="panel-heading">
                    <span class="panel-title fieldset-legend">Budget Annuali</span>
                </legend>
                <div class="panel-body" id="edit-fs-budget-body">
                    <div class="table-responsive">';
    $form = drupal_get_form('budget_page_form');
    $output .= drupal_render($form);

    $output .= '<br/>';
    $output .= theme_table(
        array(
            "header" => $header,
            "rows" => $rows,
            'attributes' => array('class' => array('table', 'table-striped', 'table-hover')),
            "sticky" => false, // Table header will be sticky
            "caption" => "",
            "colgroups" => array(),
            "empty" => t("La tabella è vuota!") // The message to be displayed if table is empty
        )
    ).theme("pager");


    $output .= '
                </div>
            </div>
    </fieldset>.</div></div></div>';
    return $output;
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function budget_page_form($form, &$form_state)
{

    $id_lperson = arg(2);
    $id_budget = arg(3);


    /* Budget */
    $form['fs_budget'] = array(
        '#type' => 'item',
    );
    $form['fs_budget']['budget_container'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="budget-ajax-wrapper">',
        '#suffix' => '</div>',
    );
    /* Budget */
    $form['fs_budget']['budget_container']['year'] = array(
        '#type' => 'date_select',
        '#title' => t('Anno di rif.'),
        '#date_timezone' => date_default_timezone(),
        '#date_format' => 'Y',
        '#date_year_range' => '-10:0',
        '#date_label_position' => 'within',
        '#required' => true,
        '#default_value' => '',
        '#prefix' => '<br>',
    );
    $form['fs_budget']['budget_container']['a_amount_protocol'] = array(
        '#type' => 'textfield',
        '#title' => t('Protocollo Budget'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => true,
    );
    $form['fs_budget']['budget_container']['a_amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Importo annuale Budget'),
        '#field_prefix' => '<div class = "input-group"><span class="input-group-addon">&euro;</span>',
        '#field_suffix' => '</div>',
        '#description' => t('Importo annuale in &euro;'),
        '#attributes' => array(
            ' type' => 'number',
            'step' => '0.01',
            'min' => 0,
            'max' => 1000000.00,
            'lang' => 'it',
            'placeholder'=>"0.00",
            'maxlength' => 9,
            ' data-number-to-fixed' => 2,
            ' data-number-stepfactor' => 100,
            'class' => array('currency','form-control'),
            'check_for_draft_save' => 'no',
        ),
        '#required' => true,
    );
    /* Extra Budget */
    $form['fs_budget']['budget_container']['a_extra_amount_protocol'] = array(
        '#type' => 'textfield',
        '#title' => t('Protocollo Extra Budget'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => false,
    );

    $form['fs_budget']['budget_container']['a_extra_amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Importo annuale Extra Budget'),
        '#field_prefix' => '<div class = "input-group"><span class="input-group-addon">&euro;</span>',
        '#field_suffix' => '</div>',
        '#description' => t('Importo annuale Extra Budget in &euro;'),
        '#attributes' => array(
            ' type' => 'number',
            'step' => '0.01',
            'min' => 0,
            'max' => 1000000.00,
            'lang' => 'it',
            'placeholder'=>"0.00",
            'check_for_draft_save' => 'no',
            'maxlength' => 9,
            ' data-number-to-fixed' => 2,
            ' data-number-stepfactor' => 100,
            'class' => array('currency','form-control')
        ),
        '#required' => false,
    );



    $form['fs_budget']['submit_line'] = array(
        '#type' => 'submit',
        '#description' => (empty($id_budget)) ? t('Aggiungi') : t('Modifica'),
        '#value' => (empty($id_budget)) ? t('Aggiungi') : t('Modifica'),
        '#name' => 'submit_line',
        '#validate' => array('budget_form_validate'),
        '#submit' => array('budget_form_submit'),
        '#attributes' => array(
            'save_type' => 'submit_line',
            'id_lperson' => $id_lperson
        ),
        '#prefix' => '<hr>'
    );
    //se non siamo nella fase di rebuild del form
    if ($form_state['rebuild'] == false) {
        //verifico se esiste il caso
        if (!empty($id_budget)) {
            $budget = getRecordById('budget', 'getif_data', $id_budget);
            $form['fs_budget']['budget_container']['year']['#default_value'] = $budget->year;
            $form['fs_budget']['budget_container']['year']['#disabled'] = true;
            $form['fs_budget']['budget_container']['a_amount']['#default_value'] = $budget->a_amount;
            $form['fs_budget']['budget_container']['a_amount_protocol']['#default_value'] = $budget->a_amount_protocol;
            $form['fs_budget']['budget_container']['a_extra_amount']['#default_value'] = $budget->a_extra_amount;
            $form['fs_budget']['budget_container']['a_extra_amount_protocol']['#default_value'] = $budget->a_extra_amount_protocol;
            $form['fs_budget']['undo'] = array(
                '#type' => 'button',
                '#description' => t('Annulla'),
                '#value' => t('Annulla'),
                '#limit_validation_errors' => array(),
                '#validate' => array('go_back_budget'),
                '#attributes' => array(
                    'id_lperson' => $id_lperson
                )
            );
        }
    }
    return $form;
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function budget_ajax_callback($form, $form_state) {
    return $form['ajax_wrapper'];
}

/**
 * @param $form
 * @param $form_state
 */
function budget_form_validate($form, &$form_state){

    if ((!empty($form_state['values']['budget_container']['a_extra_amount']) && empty($form_state['values']['budget_container']['a_extra_amount_protocol']))  ||
        (empty($form_state['values']['budget_container']['a_extra_amount']) && !empty($form_state['values']['budget_container']['a_extra_amount_protocol']))) {
        form_set_error('a_extra_amount', t('I campi Protocollo Extra Budget e Importo Annuale Extra Budget devono essere entrambi compilati'));
    }
}

/**
 * @param $form
 * @param $form_state
 */
function budget_form_submit($form, &$form_state){
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    $fields = array(
        'id_lperson' => $id_lperson,
        'year' => $form_state['values']['budget_container']['year'],
        'a_amount' => $form_state['values']['budget_container']['a_amount'],
        'a_amount_protocol' => $form_state['values']['budget_container']['a_amount_protocol'],
        'active' => 1,
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    $key = array(
        'id_lperson' => $id_lperson,
        'year' => $form_state['values']['budget_container']['year'],
    );
    if (!empty($form_state['values']['budget_container']['a_extra_amount']) && !empty($form_state['values']['budget_container']['a_extra_amount_protocol'])) {
        $fields['a_extra_amount'] = $form_state['values']['budget_container']['a_extra_amount'];
        $fields['a_extra_amount_protocol'] = $form_state['values']['budget_container']['a_extra_amount_protocol'];
    }


    try {
        db_set_active('getif_data');
        $query = db_merge('budget');
        $query->key($key)->fields($fields)->execute();
        db_set_active();
        drupal_set_message(t("Budget inserito con successo"));
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    go_back_budget($form,$form_state);
}

/**
 * @param $form
 * @param $form_state
 */
function go_back_budget($form, &$form_state) {
    global $base_url;
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    //drupal_goto(url($base_url . "/lperson_host/budget/".$id_lperson),array('query' => drupal_get_query_parameters()));
}

/**
 *
 */
function go_back() {
    drupal_goto("dashboard");
}

/**
 * @param $form
 * @param $form_state
 */
function remove_budget_submit($form, &$form_state) {
    $id_budget = $form_state['clicked_button']['#attributes']['id_budget'];
    $fields = array(
        'active' => 0
    );
    db_set_active('getif_data');
    db_update('budget')->fields($fields)->condition('id_budget',$id_budget)->execute();
    db_set_active();
}
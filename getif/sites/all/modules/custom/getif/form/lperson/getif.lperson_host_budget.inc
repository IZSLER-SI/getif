<?php

/**
 * Theme budget
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_host_budget_form($variables){
    $form = $variables['form'];
    if(empty(arg(3)))
        return getif_form_theme($form,'',false,false,'Soggetto Ospitante - Nuovo Budget');
    else {
        return getif_form_theme($form,'',false,false,'Soggetto Ospitante - '.$form['fs_budget']['#title']);
    }
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function lperson_host_budget_form($form, &$form_state) {
    $id_lperson = arg(2);
    $id_budget = arg(3);
    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Gestione Budget'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_back'),
        '#attributes' => array(
            'id_lperson' => $id_lperson
        )
    );
    /* Budget */
    $form['fs_budget'] = array(
        '#type' => 'container',
        '#title' => t('Budget annuale')
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
        '#title' => t('Anno di riferimento'),
        '#date_timezone' => date_default_timezone(),
        '#date_format' => 'Y',
        '#date_year_range' => '-10:0',
        '#date_label_position' => 'within',
        '#required' => true,
        '#default_value' => ''
    );
    $form['fs_budget']['budget_container']['a_amount_protocol'] = array(
        '#type' => 'textfield',
        '#title' => t('Protocollo Budget'),
        '#description' => t('inserire il numero di protocollo del budget annuale'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => true,
    );
    $form['fs_budget']['budget_container']['a_amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Importo annuale Budget'),
        '#description' => t('Inserire l\'importo in € del budget annuale'),
        '#field_prefix' => '<div class = "input-group"><span class="input-group-addon">&euro;</span>',
        '#field_suffix' => '</div>',
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
        '#description' => t('inserire il numero di protocollo dell\'extra budget annuale'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => false,
    );

    $form['fs_budget']['budget_container']['a_extra_amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Importo annuale Extra Budget'),
        '#description' => t('Inserire l\'importo in € dell\'extra budget annuale'),
        '#field_prefix' => '<div class = "input-group"><span class="input-group-addon">&euro;</span>',
        '#field_suffix' => '</div>',
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
            'class' => array('currency','form-control'),

        ),
        '#required' => false,
    );

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#description' => 'Salva',
        '#value' => t('Salva'),
        '#validate' => array('budget_form_validate'),
        '#submit' => array('budget_form_submit'),
        '#attributes' => array(
            'id_lperson' => $id_lperson
        ),
    );
    //se non siamo nella fase di rebuild del form
    if ($form_state['rebuild'] == false) {
        //verifico se esiste il caso
        if (!empty($id_budget)) {
            $budget = getRecordById('budget', 'getif_data', $id_budget);
            $form['fs_budget']['#title'] = 'Modifica Budget '.$budget->year;
            $form['fs_budget']['budget_container']['year']['#default_value'] = $budget->year;
            $form['fs_budget']['budget_container']['year']['#disabled'] = true;
            $form['fs_budget']['budget_container']['a_amount']['#default_value'] = $budget->a_amount;
            $form['fs_budget']['budget_container']['a_amount_protocol']['#default_value'] = $budget->a_amount_protocol;
            $form['fs_budget']['budget_container']['a_extra_amount']['#default_value'] = $budget->a_extra_amount;
            $form['fs_budget']['budget_container']['a_extra_amount_protocol']['#default_value'] = $budget->a_extra_amount_protocol;
        }
    }
    return $form;
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
function budget_form_submit($form, &$form_state)
{
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
        drupal_set_message('Errore: ' . $ex, 'error');
    }
    drupal_goto("lperson_host/budget_manage/".$id_lperson);
}

/**
 * @param $form
 * @param $form_state
 */
function goto_back($form, &$form_state) {
    getif_goto('lperson_host/budget_manage/'.$form_state['clicked_button']['#attributes']['id_lperson'],array(),302,true);
}


/* end */

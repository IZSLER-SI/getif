<?php

/**
 * Theme lperson_manage
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_budget_manage_form($variables){
    $form = $variables['form'];
    $buttons = drupal_render($form['actions']['submit']).drupal_render($form['actions']['goto_budgetes']);
    $back_submit = drupal_render($form['actions']['back']);
    $output = '';
    $output .= '<div class="col-md-12 form-container">';
    $output .= '
    <div class="bootstrap"><div class="page-head"><div class="wrapper clearfix"><h1 class="page-title">'.drupal_get_title().'</h1>
        <div class="page-bar toolbarBox">
            <div class="btn-toolbar">
                <ul id="toolbar-nav" class="nav nav-pills pull-right collapse navbar-collapse">
                    <li>
                        '.drupal_render($form['actions']['goto_dashboard']).'
                    </li>
                    <li>
                        '.drupal_render($form['actions']['goto_list']).'
                    </li>
                </ul>
                    
            </div>
        </div>
    </div></div></div>';
    $output .= '<div class="row">';
    $output .= '<div class="col-md-12 form-container">';
    $output .= '<div class="panel panel-default">';
    $output .= '<div class="panel-body">';
    $output .= $back_submit;
    $output .= $buttons;
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= drupal_render_children($form);
    $output .= '<div class="row">';
    $output .= '<div class="col-md-12 form-container">';
    $output .= '<div class="panel panel-default">';
    $output .= '<div class="panel-body">';
    $output .= $back_submit;
    $output .= $buttons;
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    return $output;
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function lperson_budget_manage_form($form, &$form_state) {
    $controller = $form_state["build_info"]["args"]["0"];
    $id_lperson = $form_state["build_info"]["args"]["1"];
    // Top Buttons
    $form['actions']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    $form['actions']['goto_list'] = array(
        '#type' => 'button',
        '#value' => t('Soggetti'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'lperson'
        )
    );
    $form['actions']['back'] = array(
        '#type' => 'button',
        '#value' => t('Anagrafica Soggetto'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_back'),
    );
    $required = true;

    /* Budget */
    $lperson = getLPersonById('getif_data',$id_lperson);
    $form['fs_budget'] = array(
        '#type' => 'fieldset',
        '#title' => t('Strutture').' '.t('di').' '.$lperson->name,
        '#prefix' => '<div id="fs-budget-div">',
        '#suffix' => '</div>',
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
        '#title' => t('Anno:'),
        '#date_timezone' => date_default_timezone(),
        '#date_format' => 'Y',
        '#date_year_range' => '-1:+10',
        '#date_label_position' => 'within',
        '#title_display' => 'invisible'
    );
    $form['fs_budget']['budget_container']['a_amount_protocol'] = array(
        '#type' => 'textfield',
        '#title' => t('Protocollo Budget'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required,
    );
    $form['fs_budget']['budget_container']['a_amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Importo annuale Budget'),
        '#field_suffix' => '<div class="field_suffix">&euro;</div>',
        '#description' => t('Indennità mensile in &euro;'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'class' => array('money_field'),
            'maxlength' => 9
        ),
        '#ajax' => array(
            'callback' => 'budget_ax_callback',
            'wrapper' => 'total_amount_div',
        ),
        '#required' => $required,
    );
    /* Extra Budget */
    $form['fs_budget']['budget_container']['a_extra_amount_protocol'] = array(
        '#type' => 'textfield',
        '#title' => t('Protocollo Extra Budget'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required,
    );
    $form['fs_budget']['budget_container']['a_extra_amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Importo annuale Extra Budget'),
        '#field_suffix' => '<div class="field_suffix">&euro;</div>',
        '#description' => t('Indennità mensile in &euro;'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'class' => array('money_field'),
            'maxlength' => 9
        ),
        '#ajax' => array(
            'callback' => 'budget_ax_callback',
            'wrapper' => 'total_amount_div',
        ),
        '#required' => $required,
    );

   
    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function my_custom_validation($form, &$form_state) {

}

/**
 * @param $form
 * @param $form_state
 */
function lperson_budget_manage_form_validate($form, &$form_state) {
    if ($form_state["build_info"]["args"]["0"] == 'new') {

        // controllo che esiste già il codice fiscale inserito
        if(!empty($form['fs_lperson']['tax_code'])) {
            db_set_active('getif_data');
            $query = db_select('lperson','lp');
            $id_lperson = $query->fields('lp',array('id_lperson'))->condition('tax_code',db_like($form_state['values']['tax_code']),'LIKE')->execute()->fetchAssoc();
            if (!empty($id_lperson)) {
                form_set_error('tax_code', t('Soggetto con questo codice fiscale esistente.'));
            }
            db_set_active();
        }
    }
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_budget_manage_form_submit($form, &$form_state) {
    // empty
}

/**
 * @param $form
 * @param $form_state
 */
function goto_back($form, &$form_state) {
    getif_goto('lperson/edit/'.$form_state["build_info"]["args"]["1"],array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function add_budget_submit($form, &$form_state) {
    $id_lperson_parent = $form_state['clicked_button']['#attributes']['id_lperson_parent'];
    $ids_lprole = $form_state['clicked_button']['#attributes']['ids_lprole'];
    $fields = array(
        'name' => _strformat($form_state['input']['budget_container']['name']),
        'seat' => _strformat($form_state['input']['budget_container']['seat']),
        'vat_number' => strtoupper($form_state['input']['budget_container']['tax_code']),
        'tax_code' => strtoupper($form_state['input']['budget_container']['tax_code']),
        'num_employers' => _strformat($form_state['input']['budget_container']['num_employers']),
    );
    $fields = array_merge($fields,array(
        'address' => !empty($form_state['input']['budget_container']['address'])?_strformat($form_state['input']['budget_container']['address']):null,
        'phone' => !empty($form_state['input']['budget_container']['phone'])?$form_state['input']['budget_container']['phone']:null,
        'email_address' => !empty($form_state['input']['budget_container']['email_address'])?strtolower($form_state['input']['budget_container']['email_address']):null,
        'id_lperson_parent' => $id_lperson_parent
    ));
    $key = array(
        'vat_number' => strtoupper($form_state['input']['budget_container']['tax_code']),
        'tax_code' => strtoupper($form_state['input']['budget_container']['tax_code']),
    );
    // insert to DB
    db_set_active('getif_data');
    try {
        $query = db_merge('lperson');
        $status = $query -> key($key) ->fields($fields)->execute();
        if( $status == MergeQuery::STATUS_INSERT ) {
            $id_lperson = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        }

        foreach ($ids_lprole AS $key_id_lprole => $id_lprole) {
            $fields = array(
                'id_lperson' => $id_lperson,
                'id_lprole' => $key_id_lprole
            );
            $key = array(
                'id_lperson' => $id_lperson,
                'id_lprole' => $key_id_lprole
            );
            try {
                $query = db_merge('lperson_lprole');
                $id_lperson_lprole = $query -> key($key) ->fields($fields)->execute();
            } catch (Exception $ex) {
                drupal_set_message('Errore: '.$ex,'error');
            }

        }


    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    // rebuild
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}

/**
 * @param $form
 * @param $form_state
 */
function remove_budgetes_submit($form, &$form_state) {
    $selected = array_filter($form_state['values']['budget_container']['table']);
    // per ogni stuttura associata
    foreach ($selected as $id_lperson => $item) {
        try {
            // disabilita la struttura
            setRecordState('lperson', 'getif_data', 'id_lperson', $id_lperson, 'active', 2);
            // disabilita i ruoli associati alla struttura
            $ids_lperson_lprole = getLPersonLProleIdsByLPersonId('getif_data', $id_lperson);
            foreach ($ids_lperson_lprole AS $id_lperson_lprole) {
                setRecordState('lperson_lprole', 'getif_data', 'id_lperson_lprole', $id_lperson_lprole, 'active', 2);
            }
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        };
    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}

/**
 * @param $form
 * @param $form_state
 */
function remove_budget_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    db_set_active('getif_data');
    try {
        // disabilita la struttura
        setRecordState('lperson', 'getif_data', 'id_lperson', $id_lperson, 'active', 2);
        // disabilita i ruoli associati alla struttura
        $ids_lperson_lprole = getLPersonLProleIdsByLPersonId('getif_data', $id_lperson);
        foreach ($ids_lperson_lprole AS $id_lperson_lprole) {
            setRecordState('lperson_lprole', 'getif_data', 'id_lperson_lprole', $id_lperson_lprole, 'active', 2);
        }
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}

/**
 * @param $form
 * @param $form_state
 */
function edit_budget_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    getif_goto('budget/edit/'.$id_lperson,array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_budget_callback($form, &$form_state) {
    return $form['fs_budget']['budget_container'];
}

/* end */

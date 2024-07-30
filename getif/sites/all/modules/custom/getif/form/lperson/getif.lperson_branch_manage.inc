<?php

/**
 * Theme branch_manage
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_branch_manage_form($variables){
    $form = $variables['form'];
    $buttons = drupal_render($form['actions']['submit']).drupal_render($form['actions']['goto_branches']);
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
function lperson_branch_manage_form($form, &$form_state) {
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

    /* STRUTTURE - BRANCH */
    $lperson_parent = getLPersonById('getif_data',$id_lperson);
    $form['fs_branches'] = array(
        '#type' => 'fieldset',
        '#title' => t('Strutture').' '.t('di').' '.$lperson_parent->name,
        '#prefix' => '<div id="fs-branch-div">',
        '#suffix' => '</div>',
    );
    $form['fs_branches']['branch_container'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="branch-ajax-wrapper">',
        '#suffix' => '</div>',
    );
    // recupera le strutture annidate
    $branches = getAllRecordByField('lperson', 'getif_data' , 'id_lperson_parent', $id_lperson, 'active');

    $rows = array();
    foreach ($branches as $branch) {
        $form['edit_branch_'.$branch->id_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'edit_branch_'.$branch->id_lperson,
            '#value' => '',
            '#submit' => array('edit_branch_submit'),
            '#id' => 'edit-edit-branch-'.$branch->id_lperson,
            '#attributes' => array(
                'id_lperson' => $branch->id_lperson,
                'class' => array('btn','glyphicon','glyphicon-pencil'),
            ),
            '#limit_validation_errors' => array(array('branch_container','table'))
        );
        // Button remove person_lperson
        $form['remove_branch_'.$branch->id_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'remove_branch_'.$branch->id_lperson,
            '#value' => '',
            '#submit' => array('remove_branch_submit'),
            '#id' => 'edit-remove-branch-'.$branch->id_lperson,
            '#ajax' => array(
                'callback' => 'add_branch_callback',
                'wrapper' => 'branch-ajax-wrapper',
            ),
            '#attributes' => array(
                'id_lperson' => $branch->id_lperson,
                'class' => array('btn','glyphicon','glyphicon-trash'),
                'onclick' => 'if(!confirm("Sei sicuro di voler eliminare la Struttura? I dati andranno persi definitivamente.")){return false;}'
            ),
            '#limit_validation_errors' => array(array('branch_container','table'))
        );
        // necessario per associare la funzione ajax
        $form['remove_branch_'.$branch->id_lperson] = ajax_pre_render_element($form['remove_branch_'.$branch->id_lperson]);
        $rows[$branch->id_lperson] = array(
            _strformat($branch->name),
            _strformat($branch->seat),
            strtoupper($branch->tax_code),
            ($branch->num_employers != 0)?$branch->num_employers:'-',
            drupal_render($form['edit_branch_'.$branch->id_lperson]).drupal_render($form['remove_branch_'.$branch->id_lperson])
        );
    }



    $header = array(t('Denominazione Struttura'),t('Sede'),t('N.identificativo'),t('Numero Dipendenti'),t('Azioni'));
    // Tabella delle strutture
    $form['fs_branches']['branch_container']['table'] = array
    (
        '#type' => 'tableselect',
        '#header' => $header,
        '#options' => $rows,
        '#empty' => t('Table has no row!'),
    );
    /* Nome della Struttura */
    $form['fs_branches']['branch_container']['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Denominazione Struttura'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required,

    );
    /* Sede della Struttura */
    $form['fs_branches']['branch_container']['seat'] = array(
        '#type' => 'textfield',
        '#title' => t('Sede della struttura'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required
    );

    /* Cod.Fiscale della Struttura */
    $form['fs_branches']['branch_container']['tax_code'] = array(
        '#type' => 'textfield',
        '#title' => t("Numero Identificativo"),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required
    );

    /* Numero di dipendenti */
    $form['fs_branches']['branch_container']['num_employers'] = array(
        '#type' => 'textfield',
        '#title' => t('Numero di dipendenti'),
        '#attributes' => array(
            'check_for_draft_save'=> 'no',
            ' type' => 'number', // insert space before attribute name :)
        ),
    );

    /* Indirizzo delle Struttura */
    $form['fs_branches']['branch_container']['address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo"),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    /* Email di rif. della Struttura */
    $form['fs_branches']['branch_container']['email_address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo Email"),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#default_value' => "",
        '#size' => 40,
        '#maxlength' => 40,
        '#element_validate' => array('getif_email_element_validate')
    );
    /* Pec di rif. della Struttura */
    $form['fs_branches']['branch_container']['certified_email_address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo di Posta Elettronica Certificata (PEC)"),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#default_value' => "",
        '#size' => 40,
        '#maxlength' => 40,
        '#element_validate' => array('getif_email_element_validate')
    );
    /* Telefono di rif. della Struttura */
    $form['fs_branches']['branch_container']['phone'] = array(
        '#type' => 'textfield',
        '#title' => t("Numero di telefono"),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#size' => 20,
        '#maxlength' => 20,
        '#element_validate' => array('getif_phone_element_validate')
    );
    /* Fax di rif. della Struttura */
    $form['fs_branches']['branch_container']['fax'] = array(
        '#type' => 'textfield',
        '#title' => t("Numero di fax"),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#size' => 20,
        '#maxlength' => 20,
        '#element_validate' => array('getif_phone_element_validate')
    );

    $form['fs_branches']['branch_container']['add_branch'] = array(
        '#type' => 'submit',
        '#name' => 'add_role',
        '#value' => t('Aggiungi'),
        '#submit' => array('add_branch_submit'),
        '#ajax' => array(
            'callback' => 'add_branch_callback',
            'wrapper' => 'branch-ajax-wrapper',
        ),
        '#attributes' => array(
            'id_lperson_parent' => $id_lperson,
            'ids_lprole' => getLPersonLProles('getif_data', $id_lperson),
        ),
        '#weight' => 100,
    );
    $form['fs_branches']['branch_container']['remove_role'] = array(
        '#type' => 'submit',
        '#value' => t('Rimuovi selezionati'),
        '#submit' => array('remove_branches_submit'),
        '#name' => 'remove_role',
        '#ajax' => array(
            'callback' => 'add_branch_callback',
            'wrapper' => 'branch-ajax-wrapper',
        ),
        '#weight' => -50,
        '#limit_validation_errors' => array(array('branch_container','table'))
    );

    $lperson = getRecordById('lperson', 'getif_data', $id_lperson);
    if ($controller == "host") {
        $form['fs_branches']['#title'] = t('Strutture associate a ').ucwords($lperson->name) . ' (' .strtoupper($lperson->tax_code).')';
    } elseif ($controller == "promoter") {
        $form['fs_branches']['#title'] = t('Dipartimenti/Segreterie associate a ').ucwords($lperson->name) . ' (' .strtoupper($lperson->tax_code).')';
        $form['fs_branches']['branch_container']['num_employers']['#access'] = FALSE;
    }

    if (!empty($form_state_values)) {
        $form['fs_lperson']['name']['#default_value'] = !empty($form_state_values['name'])?$form_state_values['name']."":'';
        $form['fs_lperson']['tax_code']['#default_value'] = !empty($form_state_values['tax_code'])?$form_state_values['tax_code']."":'';
        $form['fs_lperson']['address']['#default_value'] = !empty($form_state_values['address'])?$form_state_values['address']."":'';
        $form['fs_lperson']['phone']['#default_value'] = !empty($form_state_values['phone'])?$form_state_values['phone']."":'';
        $form['fs_lperson']['email_address']['#default_value'] = !empty($form_state_values['email_address'])?$form_state_values['email_address']."":'';
        $form['fs_lperson']['lprole']['#default_value'] = !empty($form_state_values['lprole'])?$form_state_values['lprole']:'';
    }
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
function lperson_branch_manage_form_validate($form, &$form_state) {
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
function lperson_branch_manage_form_submit($form, &$form_state) {
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
function add_branch_submit($form, &$form_state) {
    $id_lperson_parent = $form_state['clicked_button']['#attributes']['id_lperson_parent'];
    $ids_lprole = $form_state['clicked_button']['#attributes']['ids_lprole'];
    $fields = array(
        'name' => _strformat($form_state['input']['branch_container']['name']),
        'seat' => _strformat($form_state['input']['branch_container']['seat']),
        'vat_number' => strtoupper($form_state['input']['branch_container']['tax_code']),
        'tax_code' => strtoupper($form_state['input']['branch_container']['tax_code']),
        'num_employers' => !empty($form_state['input']['branch_container']['num_employers'])?$form_state['input']['branch_container']['num_employers']:0,
    );
    $fields = array_merge($fields,array(
        'address' => !empty($form_state['input']['branch_container']['address'])?_strformat($form_state['input']['branch_container']['address']):null,
        'phone' => !empty($form_state['input']['branch_container']['phone'])?$form_state['input']['branch_container']['phone']:null,
        'fax' => !empty($form_state['input']['branch_container']['fax'])?$form_state['input']['branch_container']['fax']:null,
        'email_address' => !empty($form_state['input']['branch_container']['email_address'])?strtolower($form_state['input']['branch_container']['email_address']):null,
        'certified_email_address' => !empty($form_state['input']['branch_container']['certified_email_address'])?strtolower($form_state['input']['branch_container']['certified_email_address']):null,
        'id_lperson_parent' => $id_lperson_parent
    ));
    $key = array(
        'vat_number' => strtoupper($form_state['input']['branch_container']['tax_code']),
        'tax_code' => strtoupper($form_state['input']['branch_container']['tax_code']),
    );
    // insert to DB
    db_set_active('getif_data');
    try {
        $query = db_merge('lperson');
        $status = $query -> key($key) ->fields($fields)->execute();
        if( $status == MergeQuery::STATUS_INSERT ) {
            $id_lperson = db_query("SELECT LAST_INSERT_ID()")->fetchField();
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
                    $query -> key($key) ->fields($fields)->execute();
                } catch (Exception $ex) {
                    drupal_set_message('Errore: '.$ex,'error');
                }

            }
            drupal_set_message('Struttura inserita con successo.', 'status');
        } else {
            drupal_set_message('Struttura gi&agrave; inserita.', 'warning');
        }
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    // rebuild
    $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 */
function remove_branches_submit($form, &$form_state) {
    $selected = array_filter($form_state['values']['branch_container']['table']);
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
function remove_branch_submit($form, &$form_state) {
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
function edit_branch_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    getif_goto('branch/edit/'.$id_lperson,array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_branch_callback($form, &$form_state) {
    return $form['fs_branches']['branch_container'];
}

/* end */

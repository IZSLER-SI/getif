<?php

/**
 * Theme lperson_promoter
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_promoter_form($variables){
    $form = $variables['form'];
    if (arg(1) == 'new') {
        $options['page_title'] = "Nuovo Soggetto Promotore";
    } elseif (arg(1) == 'edit') {
        $options['page_title'] = "Modifica Soggetto Promotore: ".$form['fs_lperson']['#title'];
    }

    return getif_form_theme($form,null,$options);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function lperson_promoter_form($form, &$form_state) {
    $controller = $form_state["build_info"]["args"]["0"];
    if ($controller == 'new') {
        $form_state_values = session_get("lperson");
    } elseif ($controller == "edit"){
        $id_lperson = $form_state["build_info"]["args"]["1"];
    } elseif($controller == "view") {
        $form_state_values = session_get('lperson');
        // se la variabile di sessione è vuota non fa il redirect
        if(empty($form_state_values)) {
            drupal_goto('lperson_promoter/new');
        }
        
    }
    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    $form['nav']['goto_list'] = array(
        '#type' => 'button',
        '#value' => t('Soggetti Promotore'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'lperson_promoter'
        )
    );
    // Contenuto
    $required = true;

    $form['fs_lperson'] = array(
        '#type' => 'container',
        '#title' => t('Anagrafica'),
        '#prefix' => '<div id="fs-intern-div">',
        '#suffix' => '</div>',
    );

    $form['fs_lperson']['id_lperson'] = array(
        '#type' => 'hidden'
    );

    $form['fs_lperson']['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Ragione Sociale'),
        '#description' => t('Inserire la ragione sociale'),
        '#required' => true,
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    $form['fs_lperson']['tax_code'] = array(
        '#type' => 'textfield',
        '#title' => t("P.IVA / Cod.Fisc."),
        '#description' => t('Inserire la P.IVA / Cod.Fisc.'),
        '#required' => true,
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    $form['fs_lperson']['address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo"),
        '#description' => t('Inserire l\'indirizzo'),
        '#required' => $required,
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    $form['fs_lperson']['email_address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo Email"),
        '#description' => t('Inserire l\'indirizzo email'),
        '#required' => $required,
        '#default_value' => "",
        '#size' => 40,
        '#maxlength' => 40,
        '#element_validate' => array('getif_email_element_validate'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    $form['fs_lperson']['certified_email_address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo di Posta Elettronica Certificata (PEC)"),
        '#description' => t('Inserire l\'indirizzo di Posta Elettronica Certificata (PEC)'),
        '#default_value' => "",
        '#size' => 40,
        '#maxlength' => 40,
        '#element_validate' => array('getif_email_element_validate'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    $form['fs_lperson']['phone'] = array(
        '#type' => 'textfield',
        '#title' => t("Numero di telefono"),
        '#description' => t('Inserire il numero di telefono'),
        '#required' => false,
        '#size' => 20,
        '#maxlength' => 20,
        '#element_validate' => array('getif_phone_element_validate'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    $form['fs_lperson']['fax'] = array(
        '#type' => 'textfield',
        '#title' => t("Fax"),
        '#description' => t('Inserire il numero di fax della struttura'),
        '#required' => false,
        '#size' => 20,
        '#maxlength' => 20,
        '#element_validate' => array('getif_phone_element_validate'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );

    $form['fs_lperson']['lproles'] = array(
        '#type' => 'checkboxes',
        '#title' => t("Tipo Soggetto"),
        '#options' => getLibOptions('lib_lprole', 'getif_data'),
        '#required' => $required,
        '#value' => array(1=>1),
        '#attributes' => array(
            'disabled' => true
        )
    );



    if ($controller == "new") {

        $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Salva'),
        );
    } elseif ($controller == "view") {
        // disabilita elementi
        _iterate_form($form, function(&$element, $form){
            if (!empty($element['#type']) && $element['#type'] == 'submit') {
                if (!empty($element['#submit']) && $element['#submit'] != array('back_submit')) {
                    $element['#access'] = false;
                }
            } else {
                $element['#disabled'] = true;
            }
        });
        $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Conferma salvataggio')
        );
    } elseif ($controller == "edit") {
        // get person record
        $lperson = getRecordById('lperson', 'getif_data', $id_lperson);
        // populate fields
        $form['fs_lperson']['id_lperson']['#value'] = $lperson->id_lperson;
        $form['fs_lperson']['name']['#default_value'] = ucwords($lperson->name);
        $form['fs_lperson']['tax_code']['#default_value'] = strtoupper($lperson->tax_code);
        $form['fs_lperson']['address']['#default_value'] = $lperson->address;
        $form['fs_lperson']['phone']['#default_value'] = $lperson->phone;
        $form['fs_lperson']['fax']['#default_value'] = $lperson->fax;
        $form['fs_lperson']['email_address']['#default_value'] = strtolower($lperson->email_address);
        $form['fs_lperson']['certified_email_address']['#default_value'] = strtolower($lperson->certified_email_address);
        $results = getAllRecordByField('lperson_lprole', 'getif_data', 'id_lperson', $id_lperson, 'active', 1);
        $form['fs_lperson']['#title'] = ucwords($lperson->name);
        $lprole_array = array();
        foreach($results as $result) {
            $lprole_array[$result->id_lprole] = $result->id_lprole;
        }
        $form['fs_lperson']['lproles']['#default_value'] = $lprole_array;
        $form['fs_lperson']['lproles']['#ajax'] = array(
            'callback' => 'update_branch_lproles_callback',
            'wrapper' => 'branch-ajax-wrapper',
            'event' => 'change',
        );

        $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Salva'),
            '#limit_validation_errors' => array(array('name'))
        );
        $form['nav']['goto_branches'] = array(
            '#type' => 'submit',
            '#value' => t('Gestione Segr./Dip.'),
            '#submit' => array('goto_branches_submit'),
            '#limit_validation_errors' => array(),
        );
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler applicare le modifiche?")){return false;}';
    }

    if (!empty($form_state_values)) {
        $form['fs_lperson']['name']['#default_value'] = !empty($form_state_values['name'])?$form_state_values['name']:'';
        $form['fs_lperson']['tax_code']['#default_value'] = !empty($form_state_values['tax_code'])?$form_state_values['tax_code']:'';
        $form['fs_lperson']['address']['#default_value'] = !empty($form_state_values['address'])?$form_state_values['address']:'';
        $form['fs_lperson']['phone']['#default_value'] = !empty($form_state_values['phone'])?$form_state_values['phone']:'';
        $form['fs_lperson']['fax']['#default_value'] = !empty($form_state_values['fax'])?$form_state_values['fax']:'';
        $form['fs_lperson']['email_address']['#default_value'] = !empty($form_state_values['email_address'])?$form_state_values['email_address']:'';
        $form['fs_lperson']['certified_email_address']['#default_value'] = !empty($form_state_values['certified_email_address'])?$form_state_values['certified_email_address']:'';
        $form['fs_lperson']['lproles']['#default_value'] = !empty($form_state_values['lproles'])?$form_state_values['lproles']:'';
    }
    return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_promoter_form_validate($form, &$form_state) {
    if ($form_state["build_info"]["args"]["0"] == 'new') {
        // controllo che esiste già il codice fiscale inserito
        if(!empty($form['fs_lperson']['tax_code'])) {
            db_set_active('getif_data');
            $query = db_select('lperson','lp');
            $id_lperson = $query->fields('lp',array('id_lperson'))->condition('tax_code',db_like($form_state['values']['tax_code']),'LIKE')->execute()->fetchAssoc();
            db_set_active();
            if (!empty($id_lperson)) {
                form_set_error('tax_code', t('Soggetto con questo codice fiscale esistente.'));
            }

        }
    }
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_promoter_form_submit($form, &$form_state) {
    if($form_state["build_info"]["args"][0] == "new") {
        unset($_SESSION['lperson']);
        save($form, $form_state);
        drupal_goto('lperson_promoter/list');
        drupal_set_message(t("Dati inseriti con successo"));
    } elseif ($form_state["build_info"]["args"][0] == "view") {
        unset($_SESSION['lperson']);
        $id_lperson = save($form, $form_state);
        drupal_goto('lperson_promoter/edit/'.$id_lperson);
    } elseif ($form_state["build_info"]["args"][0] == "edit") {
        edit($form, $form_state);
        drupal_goto('lperson_promoter/list');
        drupal_set_message(t("Dati modificati con successo"));
    }
}

/**
 * @param $form
 * @param $form_state
 */
function back_submit($form, &$form_state) {
    getif_goto('lperson_promoter/list',array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function goto_branches_submit($form, &$form_state) {
    getif_goto('lperson_promoter/branches/'.arg(2),array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function goto_budget_submit($form, &$form_state) {
    getif_goto('lperson_promoter/budget/'.arg(2),array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function save($form, &$form_state) {
    /* insert into lperson */
    $fields = array(
        'name' => _strformat($form_state['values']['name']),
        'vat_number' => strtoupper($form_state['values']['tax_code']),
        'tax_code' => strtoupper($form_state['values']['tax_code']),
        'address' => !empty($form_state['values']['address'])?_strformat($form_state['values']['address']):null,
        'phone' => !empty($form_state['values']['phone'])?$form_state['values']['phone']:null,
        'fax' => !empty($form_state['values']['fax'])?$form_state['values']['fax']:null,
        'email_address' => !empty($form_state['values']['email_address'])?strtolower($form_state['values']['email_address']):null,
        'certified_email_address' => !empty($form_state['values']['certified_email_address'])?strtolower($form_state['values']['certified_email_address']):null,
        'num_employers' => 0,
        'seat' => t('Sede legale'),
        'level' => 0,
    );
    db_set_active('getif_data');
    try {
        $query = db_insert('lperson');
        $id_lperson= $query -> fields($fields)->execute();

        $query = db_update('lperson');
        $query->fields(array('id_lperson_parent'=>$id_lperson));
        $query->condition('id_lperson',$id_lperson)->execute();
        if (!empty($form_state['values']['lproles'])) {
            foreach($form_state['values']['lproles'] as $key => $value) {
                if($value != 0) {
                    $fields = array(
                        'id_lperson'=> $id_lperson,
                        'id_lprole' => $key
                    );      
                    try {
                        $query = db_insert('lperson_lprole');
                        $query -> fields($fields) -> execute();
                    } catch (Exception $ex) {
                        drupal_set_message('Errore: '.$ex,'error');
                    }
                }
            }
        }
    } catch (Exception $ex) {    
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    return $id_lperson;
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function edit($form, &$form_state) {
    $id_lperson = $form_state["build_info"]["args"][1];
    $fields = array(
        'name' => _strformat($form_state['input']['name']),
        'vat_number' => strtoupper($form_state['input']['tax_code']),
        'tax_code' => strtoupper($form_state['input']['tax_code']),
        'address' => !empty(_strformat($form_state['input']['address']))?_strformat($form_state['input']['address']):null,
        'phone' => !empty($form_state['input']['phone'])?$form_state['input']['phone']:null,
        'fax' => !empty($form_state['input']['fax'])?$form_state['input']['fax']:null,
        'email_address' => !empty($form_state['input']['email_address'])?strtolower($form_state['input']['email_address']):null,
        'certified_email_address' => !empty($form_state['input']['certified_email_address'])?strtolower($form_state['input']['certified_email_address']):null,
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    db_set_active('getif_data');
    try {
        $query = db_update('lperson');
        $id_lperson_m = $query -> fields($fields) -> condition('id_lperson',$id_lperson)->execute();
        // insert ruoli soggetti
        if (!empty($form_state['values']['lproles'])) {
            foreach($form_state['values']['lproles'] as $key => $value) {             
                if($value != 0) {
                    $fields = array(
                        'id_lperson'=> $id_lperson,
                        'id_lprole' => $key,
                        'active'    => 1   
                    );
                    $key = array(
                        'id_lperson'=> $id_lperson,
                        'id_lprole' => $key,                       
                    );
                    try {
                        $query = db_merge('lperson_lprole');
                        $id_lperson_lprole = $query -> key($key) -> fields($fields) -> execute();
                    } catch (Exception $ex) {
                        drupal_set_message('Errore: '.$ex,'error');
                    }
                } else {
                    $fields = array(
                        'id_lperson'=> $id_lperson,
                        'id_lprole' => $key,
                        'active'    => 2
                    );
                    try {
                        $query = db_update('lperson_lprole');
                        $and = db_and()
                        -> condition('id_lperson',$id_lperson)
                        -> condition('id_lprole',$key);
                        $id_lperson_lprole = $query -> condition($and) -> fields($fields) -> execute();
                    } catch (Exception $ex) {
                        drupal_set_message('Errore: '.$ex,'error');
                    }
                }
            }
        }
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    return $id_lperson;
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function update_branch_lproles_callback($form, &$form_state) {
    $id_lperson_parent = $form_state["build_info"]["args"]["1"];
    
    // abilito il/i ruolo/i selezionato/i
    
    foreach(getAllBranches('getif_data', $id_lperson_parent) AS $id_lperson) {
        $curr_ids_lperson_lprole = getLPersonLProleIdsByLPersonId('getif_data', $id_lperson);
        // disabilito tutti i ruoli del Soggetto e delle Strutture
        foreach ($curr_ids_lperson_lprole AS $id_lperson_lprole) {
            setRecordState('lperson_lprole', 'getif_data', 'id_lperson_lprole', $id_lperson_lprole, 'active', 2);
        } 
        // abilito tutti i ruoli del Soggetto e delle Strutture
        foreach($form_state['values']['lproles'] AS $id_lprole => $is_checked) {
            if ($is_checked == $id_lprole) {
                $fields = array(
                    'id_lperson' => $id_lperson,
                    'id_lprole' => $id_lprole,
                    'active' => 1,
                );
                $key = array(
                    'id_lperson' => $id_lperson,
                    'id_lprole' => $id_lprole
                );
                db_set_active('getif_data');
                try {
                    $query = db_merge('lperson_lprole');
                    $id_lperson_lprole = $query -> key($key) ->fields($fields)->execute();
                } catch (Exception $ex) {
                    drupal_set_message('Errore: '.$ex,'error');
                }
                db_set_active();
            }
            
        }
        // disabilito tutti i ruoli di persone
        
        $allowed_proles = getAllowedProleByLPId('getif_data',$id_lperson);
        $where = '';
        foreach ($allowed_proles AS $key_prole_id => $descriprion_prole) {
            $where .= ('id_prole <> '.$key_prole_id.' AND ');
        }
        $person_lpersons = getAllPersonsByLPId('getif_data',$id_lperson);
        
        foreach ($person_lpersons AS $person_lperson) {
            
            $fields = array(
                'active' => 2
            );
            
            try {
                db_set_active('getif_data');
                $query = db_update('person_lperson_prole');
                $query ->fields($fields)->where($where.('id_person_lperson ='.$person_lperson->id_person_lperson))->execute();
                db_set_active();
            } catch (Exception $ex) {
                drupal_set_message('Errore: '.$ex,'error');
            }
            
        }
        
    }
    
    return $form['fs_branches']['branch_container'];
}


/* end */

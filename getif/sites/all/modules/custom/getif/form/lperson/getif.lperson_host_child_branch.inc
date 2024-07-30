<?php

/**
 * Theme lperson_child_branch
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_host_child_branch_form($variables){
    $form = $variables['form'];
    $header_content = array();
    if (arg(3) == 'new') {
        $options['page_title'] = 'Nuovo Laboratorio di '.$form['fs_branch']['#description'];
        return getif_form_theme($form,null,$options);
    } elseif (arg(3) == 'edit') {
        $options['page_title'] = $form['fs_branch']['#description'];
    }

    $options['show_fs_title'] = false;
    return getif_form_theme($form,$header_content,$options);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function lperson_host_child_branch_form($form, &$form_state) {
    $controller = $form_state["build_info"]["args"]["0"];
    if ($controller == 'new') {
        $id_lperson_parent = $form_state["build_info"]["args"]["1"];
        $lperson_parent = getLPersonById('getif_data',$id_lperson_parent);
        $fs_branch_description = _strformat($lperson_parent->name);
    } elseif ($controller == "edit"){
        $id_lperson = $form_state["build_info"]["args"]["1"];
        $lperson = getRecordById('lperson','getif_data', $id_lperson, 'active');
        $lperson_parent = getLPersonById('getif_data',$lperson->id_lperson_parent);
        $id_lperson_parent = $lperson_parent -> id_lperson;
        $form_state['id_lperson_parent'] = $id_lperson_parent;
        $fs_branch_description = 'Modifica Laboratorio di ' . _strformat($lperson_parent->name) . ': ' . $lperson->name;
    }
    $required = true;
    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Gestione Laboratori'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_back'),
    );

    $form['markup'] = array(
        '#markup' => _strformat($lperson_parent->name),
        '#access' => false
    );
    $fs_branch_title = t('Anagrafe Laboratorio').($controller == 'edit'?'&nbsp;'.t('di').'&nbsp;'._strformat($lperson_parent->name):'');
    $form['nav']['back']['#attributes']['id_lperson_parent'] = $id_lperson_parent;
    $form['fs_branch'] = array(
        '#type' => 'container',
        '#title' => $fs_branch_title,
        '#description' => !empty($fs_branch_description)?$fs_branch_description:'',
        '#prefix' => '<div id="fs-branch-div">',
        '#suffix' => '</div>'
    );
    $form['fs_branch']['branch_container'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="branch-ajax-wrapper">',
        '#suffix' => '</div>',
    );

    /* Nome del laboratorio */
    $form['fs_branch']['branch_container']['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Denominazione Laboratorio'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required
    );
    /* Email di rif. del laboratorio */
    $form['fs_branch']['branch_container']['email_address'] = array(
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
    /* Telefono di rif. del laboratorio */
    $form['fs_branch']['branch_container']['phone'] = array(
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

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Salva')
    );

    if ($controller == 'edit') {
        // get person record
        $lperson = getRecordById('lperson', 'getif_data', $id_lperson);
        // populate fields
        $form['fs_branch']['branch_container']['name']['#default_value'] = ucwords($lperson->name);
        $form['fs_branch']['branch_container']['phone']['#default_value'] = $lperson ->phone;
        $form['fs_branch']['branch_container']['email_address']['#default_value'] = strtolower($lperson ->email_address);
    }
    return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_host_child_branch_form_validate($form, &$form_state) {
    if(!empty($form_state['values']['branch_container']['name'])) {
        db_set_active('getif_data');
        $query = db_select('lperson', 'lp');
        if ($form_state["build_info"]["args"]["0"] == 'new') {
            $query->condition('name', db_like(_strformat($form_state['values']['branch_container']['name'])), 'LIKE');
            $query->condition('id_lperson_parent', $form_state["build_info"]["args"]["1"]);
            $query->condition('level', 2);
        } else {
            $query->where(
                'lp.name LIKE \''.$form_state["values"]['branch_container']["name"].'\' AND
                  lp.id_lperson <> '.$form_state["build_info"]["args"]["1"].' AND 
                  lp.active IN (1,2)
                ');
        }
        $query->fields('lp', array('id_lperson'));

        $id_person = $query->execute()->fetchAssoc();
        db_set_active();
        if (!empty($id_person)) {
            form_set_error('name', t('Laboratorio con questo nome esistente.'));
        }
    }
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_host_child_branch_form_submit($form, &$form_state) {
    if($form_state["build_info"]["args"][0] == "new") {
        $id_lperson = save($form, $form_state);
        unset($id_lperson);
        drupal_set_message(t("Dati inseriti con successo"));
        drupal_goto('lperson_host/branch/edit/'.$form_state["build_info"]["args"][1],array('query'=>array('new_lab'=>'active')));
    } elseif ($form_state["build_info"]["args"][0] == "edit") {
        $id_lperson = edit($form, $form_state);
        unset($id_lperson);
        drupal_set_message(t("Dati aggiornati con successo"));
        drupal_goto('lperson_host/branch/edit/'.$form_state['id_lperson_parent'],array('query'=>array('new_lab'=>'active')));
    }
}


/**
 * @param $form
 * @param $form_state
 */
function goto_back($form, &$form_state) {
    $id_lperson_parent = $form_state['clicked_button']['#attributes']['id_lperson_parent'];
    getif_goto('lperson_host/branch/edit/'.$id_lperson_parent,array('query'=>array('new_lab'=>'active')),302,true);
}

/**
 * @param $form
 * @param $form_state
 * @return DatabaseStatementInterface|int
 * @throws Exception
 */
function save($form, &$form_state) {
    $id_lperson_parent = $form_state["build_info"]["args"]["1"];
    $fields = array(
        'name' => _strformat($form_state['values']['branch_container']['name']),
        'phone' => !empty($form_state['values']['branch_container']['phone'])?$form_state['values']['branch_container']['phone']:null,
        'email_address' => !empty($form_state['values']['branch_container']['email_address'])?strtolower($form_state['values']['branch_container']['email_address']):null,
        'id_lperson_parent' => $id_lperson_parent,
        'level' => 2,
        'active' => 1
    );
    // insert to DB
    db_set_active('getif_data');
    $query = db_insert('lperson');
    $id_lperson = $query->fields($fields)->execute();
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
        'phone' => !empty($form_state['values']['branch_container']['phone'])?$form_state['values']['branch_container']['phone']:null,
        'email_address' => !empty($form_state['values']['branch_container']['email_address'])?strtolower($form_state['values']['branch_container']['email_address']):null,
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    if (!empty($form_state['values']['branch_container']['name'])) { // Laboratorio
        $fields = array_merge($fields,array(
            'name' => _strformat($form_state['values']['branch_container']['name'])
        ));
    }
    db_set_active('getif_data');
    try {
        $query = db_update('lperson');
        $query -> fields($fields) -> condition('id_lperson',$id_lperson)->execute();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    return $id_lperson;
}

/* end */
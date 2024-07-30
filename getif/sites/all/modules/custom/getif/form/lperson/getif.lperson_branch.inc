<?php

/**
 * Theme lperson_branch
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_branch_form($variables){

    $form = $variables['form'];
    $buttons = drupal_render($form['actions']['submit']).drupal_render($form['actions']['goto_branches']);
    $back_submit = drupal_render($form['actions']['back']);
    $output = '';
    $output .= '<div class="col-md-10 form-container">';
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
function lperson_branch_form($form, &$form_state) {
    $action = $form_state["build_info"]["args"]["0"];
    if ($action == 'new') {
        $form_state_values = session_get("lperson_branch");
    } elseif ($action == "edit"){
        $id_lperson = $form_state["build_info"]["args"]["1"];
    } elseif($action == "view") {
        $form_state_values = session_get('lperson_branch');
        // se la variabile di sessione è vuota non fa il redirect
        if(empty($form_state_values)) {
            drupal_goto('lperson/new');
        }
    }
    $required = true;
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
            'list_name' => 'lperson_host'
        )
    );
    $form['actions']['back'] = array(
        '#type' => 'button',
        '#value' => t('Gestione Strutture'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_back'),
    );
    $lperson = getRecordById('lperson','getif_data', $id_lperson, 'active');
    $form['actions']['back']['#attributes']['id_lperson_parent'] = $lperson->id_lperson_parent;
    $form['fs_branch'] = array(
        '#type' => 'fieldset',
        '#title' => t('Anagrafe Struttura / Dipartimento / Segreteria'),
        '#prefix' => '<div id="fs-branch-div">',
        '#suffix' => '</div>',
    );
    $form['fs_branch']['branch_container'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="branch-ajax-wrapper">',
        '#suffix' => '</div>',
    );
    $header = array(t('Denominazione Struttura'),t('P.IVA'),t('Numero Dipendenti'));
    $rows = !empty($form_state['branch_rows'])?$form_state['branch_rows']:array();
    $options = array();

    /* Nome della Struttura */
    $form['fs_branch']['branch_container']['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Denominazione Struttura'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required
    );
    /* Sede della Struttura */
    $form['fs_branch']['branch_container']['seat'] = array(
        '#type' => 'textfield',
        '#title' => t('Sede della struttura'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required
    );
    /* Identificativo Fiscale della Struttura */
    $form['fs_branch']['branch_container']['tax_code'] = array(
        '#type' => 'textfield',
        '#title' => t("Numero Identificativo"),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required
    );

    /* Numero di dipendenti */
    $form['fs_branch']['branch_container']['num_employers'] = array(
        '#type' => 'textfield',
        '#title' => t('Numero di dipendenti'),
        '#attributes' => array(
            'check_for_draft_save'=> 'no',
            ' type' => 'number', // insert space before attribute name :)
        ),
        '#required' => $required
    );
    /* Indirizzo delle Struttura */
    $form['fs_branch']['branch_container']['address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo"),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    /* Telefono di rif. della Struttura */
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
    /* Email di rif. della Struttura */
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

    // Laboratori
    $form['fs_lperson_location_area'] = array(
        '#type' => 'fieldset',
        '#title' => t('Laboratori'),
        '#prefix' => '<div id="fs-lperson-location-area-div">',
        '#suffix' => '</div>',
    );
    $form['fs_lperson_location_area']['lperson_location_area_container'] = array(
        '#type' => 'container',
        '#weight' => 80,
        '#tree' => TRUE,
        '#prefix' => '<div id="lperson-location-area-wrapper">',
        '#suffix' => '</div>',
        '#weight' => 0,
    );
    $lperson_location_areas = getAllRecordByField('lperson_location_area','getif_data','id_lperson',$id_lperson,'active');

    $rows = array();
    foreach ($lperson_location_areas as $lperson_location_area) {
        $rows[$lperson_location_area->id_lperson_location_area] = array(
            $lperson_location_area->name
        );
        $form['remove_lperson_location_area_'.$lperson_location_area->id_lperson_location_area]  = array (
            '#type' => 'submit',
            '#name' => 'remove_lperson_location_area_'.$lperson_location_area->id_lperson_location_area,
            '#value' => 'Elimina',
            '#submit' => array('remove_lperson_location_area_submit'),
            '#id' => 'edit-remove-lperson-location-area-'.$lperson_location_area->id_lperson_location_area,
            '#ajax' => array(
                'callback' => 'add_lperson_location_area_callback',
                'wrapper' => 'lperson-location-area-wrapper',
            ),
            '#attributes' => array(
                'id_lperson_location_area' => $lperson_location_area->id_lperson_location_area,
            ),
        );
        $form['remove_lperson_location_area_'.$lperson_location_area->id_lperson_location_area] = ajax_pre_render_element($form['remove_lperson_location_area_'.$lperson_location_area->id_lperson_location_area]);
        $lperson_location_area->actions = drupal_render($form['remove_lperson_location_area_'.$lperson_location_area->id_lperson_location_area]);
        $rows[$lperson_location_area->id_lperson_location_area] = array(
            $lperson_location_area->name,
            $lperson_location_area->actions
        );
    }

    $form['fs_lperson_location_area']['remove_lperson_location_areas']  = array (
        '#type' => 'submit',
        '#value' => 'Rimuovi selezionati',
        '#submit' => array('remove_lperson_location_areas_submit'),
        '#ajax' => array(
            'callback' => 'add_lperson_location_area_callback',
            'wrapper' => 'lperson-location-area-wrapper',
        ),
        '#name' => 'remove-lperson-locatiion-areas',
        '#attributes' => array(
            'id_lperson' => $id_lperson,
        ),
        '#weight' => -1,
    );
    $header = array(t('Nome'),'Azioni');
    $form['fs_lperson_location_area']['lperson_location_area_container']['table'] = array
    (
        '#type' => 'tableselect',
        '#header' => $header,
        '#options' => $rows,
        '#empty' => t('Table has no row!'),
    );

    $form['fs_lperson_location_area']['lperson_location_area_name']  = array (
        '#type' => 'textfield',
    );

    $form['fs_lperson_location_area']['add_lperson_location_area']  = array (
        '#type' => 'submit',
        '#value' => 'Aggiungi Laboratorio',
        '#submit' => array('add_lperson_location_area_submit'),
        '#ajax' => array(
            'callback' => 'add_lperson_location_area_callback',
            'wrapper' => 'lperson-location-area-wrapper',
        ),
        '#attributes' => array(
            'id_lperson' => $id_lperson,
        ),
    );
    unset($rows);
    unset($header);


    // Fieldset Figure
    $form['fs_person'] = array(
        '#type' => 'fieldset',
        '#title' => t('Figure'),
        '#prefix' => '<div id="fs-person-div">',
        '#suffix' => '</div>',
    );
    $form['fs_person']['persons_container'] = array(
        '#type' => 'container',
        '#weight' => 80,
        '#tree' => TRUE,
        '#prefix' => '<div id="js-ajax-branch-persons-wrapper">',
        '#suffix' => '</div>',
        '#weight' => 0,
    );

    $persons = getAllPersonsByLPId('getif_data',$id_lperson);
    $rows = array();
    foreach ($persons as $person) {

        $positions = getPersonLPersonPositions($person->id_person_lperson);
        // get Position
        $person->positions = '<ul>';
        foreach ($positions AS $position) {
            // Pulsante per rimuovere il ruolo
            $form['remove_position_'.$position->id_person_lperson_position]  = array (
                '#type' => 'submit',
                '#name' => 'remove_position_'.$position->id_person_lperson_position,
                '#value' => 'Elimina Posizione',
                '#submit' => array('remove_position_submit'),
                '#id' => 'edit-remove-position-'.$position->id_person_lperson_position,
                '#attributes' => array(
                    'id' => 'edit-remove-position-'.$position->id_person_lperson_position,
                    'id_person_lperson_position' => $position->id_person_lperson_position,
                ),
                '#ajax' => array(
                    'callback' => 'add_position_callback',
                    'wrapper' => 'js-ajax-branch-persons-wrapper',
                )
            );
            $form['remove_position_'.$position->id_person_lperson_position] = ajax_pre_render_element($form['remove_position_'.$position->id_person_lperson_position]);

            $person->positions .= '<li>'.drupal_render($form['remove_position_'.$position->id_person_lperson_position]).' '.$position->description.'</li>';
        }
        // Add role
        $form['position_'.$person->id_person_lperson]  = array (
            '#type' => 'select',
            '#name' => 'position_'.$person->id_person_lperson,
            '#options' => getLibOptions('lib_position','getif_data'),
            '#attributes' => array(
                'id' => 'edit-position-'.$person->id_person_lperson,
            )
        );
        // Button Add position
        $form['add_position_'.$person->id_person_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'add_position_'.$person->id_person_lperson,
            '#value' => 'Aggiungi posizione',
            '#submit' => array('add_position_submit'),
            '#id' => 'edit-add-position-'.$person->id_person_lperson,
            '#attributes' => array(
                'id' => 'edit-add-position-'.$person->id_person_lperson,
                'id_person_lperson' => $person->id_person_lperson,
            ),
            '#ajax' => array(
                'callback' => 'add_position_callback',
                'wrapper' => 'js-ajax-branch-persons-wrapper',
            )
        );
        $form['add_position_'.$person->id_person_lperson] = ajax_pre_render_element($form['add_position_'.$person->id_person_lperson]);
        $person->positions .= '</ul>'. drupal_render($form['position_'.$person->id_person_lperson]) . drupal_render($form['add_position_'.$person->id_person_lperson]);



        $proles = getPersonLPersonProles($person->id_person_lperson);
        // get Roles
        $person->proles = '<ul>';
        foreach ($proles AS $prole) {
            // Pulsante per rimuovere il ruolo
            $form['remove_prole_'.$prole->id_person_lperson_prole]  = array (
                '#type' => 'submit',
                '#name' => 'remove_prole_'.$prole->id_person_lperson_prole,
                '#value' => 'Elimina Ruolo',
                '#submit' => array('remove_prole_submit'),
                '#id' => 'edit-remove-prole-'.$prole->id_person_lperson_prole,
                '#attributes' => array(
                    'id' => 'edit-remove-prole-'.$prole->id_person_lperson_prole,
                    'id_person_lperson_prole' => $prole->id_person_lperson_prole,
                ),
                '#ajax' => array(
                    'callback' => 'add_prole_callback',
                    'wrapper' => 'js-ajax-branch-persons-wrapper',
                )
            );
            $form['remove_prole_'.$prole->id_person_lperson_prole] = ajax_pre_render_element($form['remove_prole_'.$prole->id_person_lperson_prole]);

            $person->proles .= '<li>'.drupal_render($form['remove_prole_'.$prole->id_person_lperson_prole]).' '.$prole->description.'</li>';
        }
        // Add role
        $form['prole_'.$person->id_person_lperson]  = array (
            '#type' => 'select',
            '#name' => 'prole_'.$person->id_person_lperson,
            '#options' => getAllowedProleByLPId('getif_data',$id_lperson),
            '#attributes' => array(
                'id' => 'edit-prole-'.$person->id_person_lperson,
            )
        );
        // Button Add prole
        $form['add_prole_'.$person->id_person_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'add_prole_'.$person->id_person_lperson,
            '#value' => 'Aggiungi ruolo',
            '#submit' => array('add_prole_submit'),
            '#id' => 'edit-add-prole-'.$person->id_person_lperson,
            '#attributes' => array(
                'id' => 'edit-add-prole-'.$person->id_person_lperson,
                'id_person_lperson' => $person->id_person_lperson,
            ),
            '#ajax' => array(
                'callback' => 'add_prole_callback',
                'wrapper' => 'js-ajax-branch-persons-wrapper',
            )
        );
        $form['add_prole_'.$person->id_person_lperson] = ajax_pre_render_element($form['add_prole_'.$person->id_person_lperson]);
        // Button remove person_lperson
        $form['remove_person_'.$person->id_person_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'remove_person_'.$person->id_person_lperson,
            '#value' => 'Elimina Figura',
            '#submit' => array('remove_person_submit'),
            '#id' => 'edit-remove-person-'.$person->id_person_lperson,
            '#ajax' => array(
                'callback' => 'add_person_callback',
                'wrapper' => 'js-ajax-branch-persons-wrapper',
            ),
            '#attributes' => array(
                'id_person_lperson' => $person->id_person_lperson,
            ),
        );
        $form['remove_person_'.$person->id_person_lperson] = ajax_pre_render_element($form['remove_person_'.$person->id_person_lperson]);
        $person->proles .= '</ul>'. drupal_render($form['prole_'.$person->id_person_lperson]) . drupal_render($form['add_prole_'.$person->id_person_lperson]);
        $person->actions = drupal_render($form['remove_person_'.$person->id_person_lperson]);
        $rows[$person->id_person_lperson] = array(
            $person->title.' '.$person->firstname.' '.$person->lastname,
            $person->tax_code,
            $person->positions,
            $person->proles,
            $person->actions
        );
    }


    $form['fs_person']['remove_persons']  = array (
        '#type' => 'submit',
        '#value' => 'Rimuovi selezionati',
        '#submit' => array('remove_persons_submit'),
        '#ajax' => array(
            'callback' => 'add_person_callback',
            'wrapper' => 'js-ajax-branch-persons-wrapper',
        ),
        '#attributes' => array(
            'id_lperson' => $id_lperson,
        ),
        '#weight' => -1,
    );
    $header = array(t('Nome'),t('Cod.Fisc.'),t('Posizioni'),t('Ruoli'),'Azioni');
    $form['fs_person']['persons_container']['table'] = array
    (
        '#type' => 'tableselect',
        '#header' => $header,
        '#options' => $rows,
        '#empty' => t('Table has no row!'),
    );

    $form['fs_person']['person']  = array (
        '#type' => 'textfield',
        '#autocomplete_path' => 'person_list_autocomplete_callback'
    );
    $form['fs_person']['person_id'] = array(
        '#type'  => 'hidden',
        '#attributes'=>array(
            'id'   => 'edit-person-id'
        )
    );
    $form['fs_person']['add_person']  = array (
        '#type' => 'submit',
        '#value' => 'Aggiungi Figura',
        '#submit' => array('add_person_submit'),
        '#ajax' => array(
            'callback' => 'add_person_callback',
            'wrapper' => 'js-ajax-branch-persons-wrapper',
        ),
        '#attributes' => array(
            'id_lperson' => $id_lperson,
        ),
    );
    if ($action == "edit") {
        // get person record
        $lperson = getRecordById('lperson', 'getif_data', $id_lperson);
        // populate fields
        $form['fs_branch']['branch_container']['name']['#default_value'] = ucwords($lperson->name);
        $form['fs_branch']['branch_container']['seat']['#default_value'] = ucwords($lperson->seat);
        $form['fs_branch']['branch_container']['tax_code']['#default_value'] = strtoupper($lperson->tax_code);
        $form['fs_branch']['branch_container']['num_employers']['#default_value']  = $lperson->num_employers;
        $form['fs_branch']['branch_container']['address']['#default_value'] = $lperson ->address;
        $form['fs_branch']['branch_container']['phone']['#default_value'] = $lperson ->phone;
        $form['fs_branch']['branch_container']['email_address']['#default_value'] = strtolower($lperson ->email_address);
        $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Salva'),
            '#suffix' => ('<div>&nbsp;</div>')
        );
    }
    if (!empty($form_state_values)) {
        $form['fs_branch']['branch_container']['name']['#default_value'] = !empty($form_state_values['name'])?$form_state_values['name']."":'';
        $form['fs_branch']['branch_container']['seat']['#default_value'] = !empty($form_state_values['seat'])?$form_state_values['seat']."":'';
        $form['fs_branch']['branch_container']['tax_code']['#default_value'] = !empty($form_state_values['tax_code'])?$form_state_values['tax_code']."":'';
        $form['fs_branch']['branch_container']['num_employers']['#default_value'] = !empty($form_state_values['num_employers'])?$form_state_values['num_employers']."":'';
        $form['fs_branch']['branch_container']['address']['#default_value'] = !empty($form_state_values['address'])?$form_state_values['address']."":'';
        $form['fs_branch']['branch_container']['phone']['#default_value'] = !empty($form_state_values['phone'])?$form_state_values['phone']."":'';
        $form['fs_branch']['branch_container']['email_address']['#default_value'] = !empty($form_state_values['email_address'])?$form_state_values['email_address']."":'';
    }
    return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_branch_form_validate($form, &$form_state) {
    if ($form_state["build_info"]["args"]["0"] == 'new') {
        // controllo che esiste già il codice fiscale inserito
        if(!empty($form['fs_branch']['branch_container']['tax_code'])) {
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
function lperson_branch_form_submit($form, &$form_state) {
    if($form_state["build_info"]["args"][0] == "new") {
        session_set('lperson_branch',$form_state['input']);
        drupal_goto('branch/view');
    } elseif ($form_state["build_info"]["args"][0] == "view") {
        unset($_SESSION['lperson_branch']);
        $id_lperson = save($form, $form_state);
        drupal_goto('branch/edit/'.$id_lperson);
    } elseif ($form_state["build_info"]["args"][0] == "edit") {
        $id_lperson = edit($form, $form_state);
        drupal_set_message(t("Dati aggiornati con successo"));
        drupal_goto('branch/edit/'.$id_lperson);
    }
}


/**
 * @param $form
 * @param $form_state
 */
function goto_back($form, &$form_state) {

    $id_lperson_parent = $form_state['clicked_button']['#attributes']['id_lperson_parent'];
    getif_goto('lperson/branches/'.$id_lperson_parent,array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function edit($form, &$form_state) {
    $id_lperson = $form_state["build_info"]["args"][1];
    $fields = array(
        'name' => _strformat($form_state['values']['branch_container']['name']),
        'seat' => _strformat($form_state['values']['branch_container']['seat']),
        'vat_number' => strtoupper($form_state['values']['branch_container']['tax_code']),
        'tax_code' => strtoupper($form_state['values']['branch_container']['tax_code']),
        'num_employers' => $form_state['values']['branch_container']['num_employers'],
        'address' => !empty(_strformat($form_state['values']['branch_container']['address']))?_strformat($form_state['values']['branch_container']['address']):null,
        'phone' => !empty($form_state['values']['branch_container']['phone'])?$form_state['values']['branch_container']['phone']:null,
        'email_address' => !empty($form_state['values']['branch_container']['email_address'])?strtolower($form_state['values']['branch_container']['email_address']):null,
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    db_set_active('getif_data');
    try {
        $query = db_update('lperson');
        $id_lperson_m = $query -> fields($fields) -> condition('id_lperson',$id_lperson)->execute();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    return $id_lperson;
}

/**
 * @param $form
 * @param $form_state
 */
function add_position_submit($form, &$form_state) {
    $id_person_lperson = $form_state['clicked_button']['#attributes']['id_person_lperson'];
    
    $fields = array(
        'id_person_lperson' => $id_person_lperson,
        'id_position' => $form_state['values']['position_'.$id_person_lperson],
        'active' => 1
    );
    $key = array(
        'id_person_lperson' => $id_person_lperson,
        'id_position' => $form_state['values']['position_'.$id_person_lperson]
    );
    db_set_active('getif_data');
    try {
        $query = db_merge('person_lperson_position');
        $query -> key($key) ->fields($fields) ->execute();
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
function remove_position_submit($form, &$form_state) {
    $id_person_lperson_position = $form_state['clicked_button']['#attributes']['id_person_lperson_position'];
    $fields = array(
        'active' => 2
    );
    db_set_active('getif_data');
    try {
        $query = db_update('person_lperson_position');
        $query ->fields($fields) -> where('id_person_lperson_position = '.$id_person_lperson_position) ->execute();
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
function add_prole_submit($form, &$form_state) {
    $id_person_lperson = $form_state['clicked_button']['#attributes']['id_person_lperson'];

    $fields = array(
        'id_person_lperson' => $id_person_lperson,
        'id_prole' => $form_state['values']['prole_'.$id_person_lperson],
        'active' => 1
    );
    $key = array(
        'id_person_lperson' => $id_person_lperson,
        'id_prole' => $form_state['values']['prole_'.$id_person_lperson]
    );
    db_set_active('getif_data');
    try {
        $query = db_merge('person_lperson_prole');
        $query -> key($key) ->fields($fields) ->execute();
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
function remove_prole_submit($form, &$form_state) {
    $id_person_lperson_prole = $form_state['clicked_button']['#attributes']['id_person_lperson_prole'];
    $fields = array(
        'active' => 2
    );
    db_set_active('getif_data');
    try {
        $query = db_update('person_lperson_prole');
        $query ->fields($fields) -> where('id_person_lperson_prole = '.$id_person_lperson_prole) ->execute();
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
 * @return mixed
 */
function add_position_callback($form, &$form_state) {
    return $form['fs_person']['persons_container'];
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_prole_callback($form, &$form_state) {
    return $form['fs_person']['persons_container'];
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_person_callback($form, &$form_state) {
    return $form['fs_person']['persons_container'];
}


/**
 * @param $form
 * @param $form_state
 */
function add_person_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    $id_person = $form_state['input']['person_id'];
    
    $fields = array(
        'id_person' => $id_person,
        'id_lperson' => $id_lperson,
        'active' => 1
    );
    $key = array(
        'id_person' => $id_person,
        'id_lperson' => $id_lperson,
    );
    db_set_active('getif_data');
    try {
        $query = db_merge('person_lperson');
        $id_person_lperson = $query -> key($key) ->fields($fields)->execute();
        $form_state['persons_map'][$id_person_lperson] = $id_person_lperson;
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
function remove_person_submit($form, &$form_state) {
    $id_person_lperson = $form_state['clicked_button']['#attributes']['id_person_lperson'];
    $fields = array(
        'active' => 2
    );
    $where = 'id_person_lperson = '.$id_person_lperson;
    db_set_active('getif_data');
    try {
        // Elimina l'associazione persona - struttura
        $query = db_update('person_lperson');
        $query -> fields($fields)-> where($where) ->execute();
        // Elimina i ruoli associati alla persona presso la struttura
        $fields = array(
            'id_person_lperson' => $id_person_lperson,
            'active' => 2
        );
        $where = 'id_person_lperson = '.$id_person_lperson;
        try {
            $query = db_update('person_lperson_prole');
            $query -> fields($fields)->where($where)->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
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
function remove_persons_submit($form, &$form_state) {
    $selected = array_filter($form_state['values']['persons_container']['table']);

    // elimina elementi selezionati
    foreach ($selected as $id_person_lperson => $item) {
        $fields = array(
            'active' => 2
        );
        $where = 'id_person_lperson = '.$id_person_lperson;
        db_set_active('getif_data');
        try {
            $query = db_update('person_lperson');
            $query -> fields($fields)-> where($where) ->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_lperson_location_area_callback ($form, &$form_state) {
    return $form['fs_lperson_location_area']['lperson_location_area_container'];
}

/**
 * @param $form
 * @param $form_state
 */
function add_lperson_location_area_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    $lperson_location_area_name = $form_state['input']['lperson_location_area_name'];
    $fields = array(
        'name' => $lperson_location_area_name,
        'id_lperson' => $id_lperson,
        'active' => 1
    );
    $key = array(
        'name' => $lperson_location_area_name,
        'id_lperson' => $id_lperson,
    );
    db_set_active('getif_data');
    try {
        $query = db_merge('lperson_location_area');
        $query -> key($key) ->fields($fields)->execute();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}

/* end */

/**
 * @param $form
 * @param $form_state
 */
function remove_lperson_location_areas_submit($form, &$form_state) {
    $selected = array_filter($form_state['values']['lperson_location_area_container']['table']);
    // elimina elementi selezionati
    foreach ($selected as $id_lperson_location_area => $item) {
        $fields = array(
            'active' => 2
        );
        $where = 'id_lperson_location_area = '.$id_lperson_location_area;
        db_set_active('getif_data');
        try {
            $query = db_update('lperson_location_area');
            $query -> fields($fields)-> where($where) ->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}

/**
 * @param $form
 * @param $form_state
 */
function remove_lperson_location_area_submit($form, &$form_state) {
    $id_lperson_location_area = $form_state['clicked_button']['#attributes']['id_lperson_location_area'];
    $fields = array(
        'active' => 2
    );
    $where = 'id_lperson_location_area = '.$id_lperson_location_area;
    db_set_active('getif_data');
    try {
        // Elimina l'associazione persona - struttura
        $query = db_update('lperson_location_area');
        $query -> fields($fields)-> where($where) ->execute();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}
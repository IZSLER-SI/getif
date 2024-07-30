<?php

/**
 * Theme sezione nuova frequenza volontaria Scheda FV.3
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_vinternship_3_form($variables){
    $form = $variables['form'];
    $header_content = array();
    $output = '';
    if(!empty(arg(2))) {
        $output .= get_internship_new_header(arg(2));
    }
    $output .= '<div class="panel panel-default">';
    $output .= '
        <ul class="nav nav-tabs" style = "background-color: #f5f5f5;">
            <li class="active"><a href="#panel1" data-toggle="tab">Frequentatore</a></li>
            <li><a href="#panel2" data-toggle="tab">Scheda FV.1</a></li>
            <li><a href="#panel3" data-toggle="tab">Scheda FV.2</a></li>
        </ul>
        <div class="tab-content">
            <div id="panel1" class="tab-pane active panel-body ">
               '.drupal_render($form['intern_data']). '
            </div>
            <div id="panel2" class="tab-pane panel-body ">
               '.drupal_render($form['internship1_data']).drupal_render($form['richiesta_frequenza_volontaria']).'
            </div>
             <div id="panel3" class="tab-pane panel-body ">
               '.drupal_render($form['internship2_data']).drupal_render($form['dichiarazione_frequenza_volontaria']).'
            </div>
        </div>';
    $output .= '</div>';
    $header_content[] = array('html' => $output,'has_separator' => false);
    $options = array();
    $options['show_fs_title'] = true;
    return getif_form_theme($form,$header_content,$options);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function vinternship_3_form($form, &$form_state) {
    $form_state['controller'] = $form_state["build_info"]["args"][0];
    if(isset($form_state["build_info"]["args"][1])) {
        $form_state['step'] = $form_state["build_info"]["args"][1];
    }
    $form_state['id_internship'] = !empty($form_state["build_info"]["args"][2])?$form_state["build_info"]["args"][2]:'';
    $form_state_values = session_get("new_internship_3");
    if ($form_state['controller'] == 'view') {
        if (!empty(session_get('new_internship_3'))) {
            $form_state['controller'] .= '-confirm';
            $form_state_values = session_get("new_internship_3");
        } else {
            if(empty($form_state['id_internship'])) {
                getif_goto('vinternship/list');
            } else {
                $internship = getVInternshipById('getif_data', $form_state['id_internship']);
                $form_state_values['aim'] = $internship->note;
                $form_state_values['positive_opinion_attachment'] = !empty($internship->attachments['parere_favorevole']->id_file_managed)?$internship->attachments['parere_favorevole']->id_file_managed:null;
            }
        }
    }
    if(empty($internship)) {
        $internship = getVInternshipById('getif_data', $form_state['id_internship']);
    }
    $form['intern_data'] = array(
        '#markup' => getVInternDataByInternshipObj($internship)
    );
    $form['internship1_data'] = array(
        '#markup' => getVInternship1DataByInternshipObj($internship)
    );
    $form['internship2_data'] = array(
        '#markup' => getVInternship2DataByInternshipObj($internship)
    );
    foreach ($internship->attachments AS $meta => $attachment) {
        if ($meta == 'dichiarazione_frequenza_volontaria' || $meta == 'richiesta_frequenza_volontaria') {
            $form[$meta]['download_attachment_' . $attachment->id_internship_attachment] = array(
                '#type' => 'button',
                '#name' => 'download_attachment_' . $attachment->id_internship_attachment,
                '#value' => ucwords('Download '.str_replace('_',' ',$meta)),
                '#validate' => array('download_attachment_submit'),
                '#id' => 'edit-download-agreement-attachment-' . $attachment->id_internship_attachment,
                '#attributes' => array(
                    'id' => 'edit-download-agreement-attachment-' . $attachment->id_internship_attachment,
                    'id_internship_attachment' => $attachment->id_internship_attachment,
                    'fid' => $attachment->id_file_managed,
                ),
                '#limit_validation_errors' => array(),
            );
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
        '#value' => t('Frequenze volontarie'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'vinternship'
        )
    );
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Indietro Scheda FV.').($form_state['step']-1),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back'),
    );

    // Responsabili/referenti della frequenza
    $form['fs_contact_person'] = [
        '#type' => 'container',
        '#title' => t('Responsabile e Referenti'),
        '#prefix' => '<div id="fs-cperson-wrapper">',
        '#suffix' => '</div>',
    ];
    $form['fs_contact_person']['cpersons_container'] = array(
        '#type' => 'container',
        '#weight' => 80,
        '#tree' => TRUE,
        '#prefix' => '<div id="js-ajax-cperson-wrapper">',
        '#suffix' => '</div>',
        '#weight' => 0,
    );

    // se ci sono già responsabili/referenti
    if (empty($form_state['field_cpersons'])) {
        foreach ($internship->project_contacts as $item) {
            $form_state_values['field_cpersons'][$item->id_person_lperson_prole] = $item->id_person_lperson_prole;
        }
    }

    if (!empty($form_state_values['field_cpersons']) && empty($form_state['field_cpersons'])) {
        $form_state['field_cpersons'] = $form_state_values['field_cpersons'];
    } else {
        $form_state['field_cpersons'] = isset($form_state['field_cpersons']) ? $form_state['field_cpersons'] : array();
    }
    $header = array(t('Nome'), t('Cognome'), t('Codice Fiscale'), t('Sede'), t('Responsabile'));
    $rows = array();
    if (!empty($form_state['field_cpersons'])) {
        $results = $internship->project_contacts;
        foreach($results as $key => $result) {
            $form['check_cp_primary_'.$result->id_person_lperson_prole]  = array (
                '#type' => 'submit',
                '#name' => 'check_cp_primary_'.$result->id_person_lperson_prole,
                '#id' => 'check_cp_primary_'.$result->id_person_lperson_prole,
                '#value' => '<span class="glyphicon glyphicon-star-empty" aria-hidden="true"></span>',
                '#submit' => array('check_cp_primary_submit'),
                '#ajax' => array(
                    'callback' => 'add_cperson_callback',
                    'wrapper' => 'js-ajax-cperson-wrapper',
                    'class' => array('btn','glyphicon','glyphicon-trash')
                ),
                '#attributes' => array(
                    'id_person_lperson_prole' => $result->id_person_lperson_prole,
                ),
                '#limit_validation_errors' => array(array('branch_container','table'))
            );
            if ($form_state['controller'] == 'view') {
                $form['check_cp_primary_'.$result->id_person_lperson_prole]['#attributes']['disabled'] = '';
            }
            if ( $result->flg_primary == 1) {
                $form['check_cp_primary_'.$result->id_person_lperson_prole]['#value'] = '<span class="glyphicon glyphicon-star" aria-hidden="true"></span>';
            }
            $form['check_cp_primary_'.$result->id_person_lperson_prole] = ajax_pre_render_element($form['check_cp_primary_'.$result->id_person_lperson_prole]);
            $rows[$result->id_person_lperson_prole] = array(
                $result->firstname,
                $result->lastname,
                $result->tax_code,
                $result->lperson_name,
                drupal_render($form['check_cp_primary_'.$result->id_person_lperson_prole]),
            );
        }
        unset($results);
        unset($result);
    }
    $form['fs_contact_person']['remove_name'] = array(
        '#type' => 'submit',
        '#value' => t('Rimuovi'),
        '#submit' => ['remove_cpersons_submit'],
        '#ajax' => [
            'callback' => 'add_cperson_callback',
            'wrapper' => 'js-ajax-cperson-wrapper',
        ],
        '#weight' => -50,
        '#name' => 'remove_cperson',
        '#access' => $form_state['controller'] == 'new'?TRUE:FALSE
    );


    $form['fs_contact_person']['cpersons_container']['table'] = array
    (
        '#type' => 'tableselect',
        '#header' => $header,
        '#options' => $rows,
        '#empty' => t('Selezionare almeno un responsabile della frequenza volontaria!'),
    );

    $form['fs_contact_person']['cperson']= array(
        '#type' => 'textfield',
        '#title' => t('Cerca').getRequiredHtml(),
        '#description' => t('Selezionare un soggetto referente secondario inserendo NOME O COGNOME O COD.FISC.'),
        '#autocomplete_path' => 'host_tutor_autocomplete_callback/3/'.$internship->id_internship,
        '#weight' => 1,
        '#access' => $form_state['controller'] == 'new'?TRUE:FALSE
    );
    $form['fs_contact_person']['cperson_id'] = array(
        '#type'  => 'hidden',
        '#weight' => 2,
        '#attributes'=>array(
            'id'   => 'edit-cperson_id'
        )
    );
    $form['fs_contact_person']['add_cperson'] = array(
        '#type' => 'submit',
        '#value' => t('Aggiungi'),
        '#submit' => ['add_cperson_submit'],
        '#ajax' => array(
            'callback' => 'add_cperson_callback',
            'wrapper' => 'js-ajax-cperson-wrapper',
        ),
        '#weight' => 100,
        '#access' => $form_state['controller'] == 'new'?TRUE:FALSE
    );
    // Parere favorevole
    $form['fs_project'] = array(
        '#type' => 'container',
        '#title' => t('Documenti frequenza'),
        '#prefix' => '<div id="fs-project-div">',
        '#suffix' => '</div>',
    );
    // Motivo della frequenza - campo di testo libero
    $form['fs_project']['aim']= array(
        '#type' => 'textarea',
        '#title' => t('Motivo della Frequenza'),
        '#description' => t('Inserisci il motivo della frequenza')
    );
    $form['fs_project']['positive_opinion_attachment'] = array(
        '#type' => 'managed_file',
        '#title' => t('Parere favorevole del Dirigente Responsabile della U.O. Ospitante IOFZ-003 C'),
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#description' => t('Click "Browse..." to select an attachment to upload.'),
        '#upload_validators' => array(
            'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
        ),
        '#upload_location' => 'public://attached/internship/'.$form_state['id_internship'].'/',
    );
    // Submit Button
    $form['actions']['submit'] = array(
        '#type' => 'submit',
    );
    if ($form_state['controller'] == "new") {
        if (!empty($_SESSION['new_internship_3'])) {
            fill_data($form,$_SESSION['new_internship_3']);
            unset($_SESSION['new_internship_3']);
        }
        $form['actions']['submit']['#value'] = t('Salva');
        $form['actions']['submit']['#attributes']['controller'] = $form_state['controller'];
        $form['actions']['submit']['#attributes']['step'] = $form_state['step'];
        $form['actions']['submit']['#attributes']['id_internship'] = $form_state['id_internship'];
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler proseguire?")){return false;}';
        $form['actions']['submit']['#attributes']['flg_update'] = false;
        $form['actions']['update']['#access'] = false;
    } elseif ($form_state['controller'] == "view") {
        fill_data($form,$form_state_values); // da cancellare
        $form['nav']['submit'] = array(
            '#type' => 'submit',
        );
        $form['nav']['submit']['#value'] = t('Prosegui Scheda FV.').($form_state['step']+1);
        $form['nav']['submit']['#attributes']['controller'] = $form_state['controller'];
        $form['nav']['submit']['#attributes']['step'] = $form_state['step'];
        $form['nav']['submit']['#attributes']['id_internship'] = $form_state['id_internship'];
        $form['nav']['submit']['#attributes']['flg_update'] = false;
        // Button Modifica
        // se lo stato della frequenza è != 0 (Annullato) OR < 5 (5 - attivo OR 6 - attivo con proroga OR 7 - concluso) la funzione di modifica è disponibile:
        if ($internship->internship_state->state > 0 AND $internship->internship_state->state < 5 AND $internship->internship_state->date_start == NULL) {
            $form['actions']['update'] = array(
                '#type' => 'submit',
            );
            $form['actions']['update']['#value'] = t('Modifica');
            $form['actions']['update']['#attributes']['controller'] = $form_state['controller'];
            $form['actions']['update']['#attributes']['step'] = $form_state['step'];
            $form['actions']['update']['#attributes']['id_internship'] = $form_state['id_internship'];
            $form['actions']['update']['#attributes']['flg_update'] = true;
            $form['actions']['update']['#limit_validation_errors'] = array();
            $form['actions']['update']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler proseguire? I dati di questa scheda e di quelle successive verranno persi.")){return false;}';
        }
        disable_form_editing($form);
    }
    return $form;
}

/**
 * @param $form
 * @param $form_state_values
 */
function fill_data(&$form, $form_state_values) {
    $form['fs_project']['aim']['#default_value'] = !empty($form_state_values['aim'])?$form_state_values['aim']:'';
    if (!empty($form_state_values['attachment'])) {
        if (!empty($form_state_values['attachment']['fid']))
            $form['fs_project']['attachment']['#default_value'] = $form_state_values['attachment']['fid'];
        elseif (is_string($form_state_values['attachment']))
            $form['fs_project']['attachment']['#default_value'] = $form_state_values['attachment'];
    }
    if (!empty($form_state_values['positive_opinion_attachment'])) {
        if (!empty($form_state_values['positive_opinion_attachment']['fid']))
            $form['fs_project']['positive_opinion_attachment']['#default_value'] = $form_state_values['attachment']['fid'];
        elseif (is_string($form_state_values['positive_opinion_attachment']))
            $form['fs_project']['positive_opinion_attachment']['#default_value'] = $form_state_values['positive_opinion_attachment'];
    }
}

/**
 * @param $form
 */
function disable_form_editing(&$form) {
    _iterate_form($form, function(&$element, $form){
        if (!empty($element['#type']) && ($element['#type'] == 'submit' || $element['#type'] == 'button')) {
            if (!empty($element['#submit']) && $element['#submit'] != array('back')) {
                $element['#access'] = false;
            }
            if (!empty($element['#validate']) && $element['#validate'] != array('go_back')
                && $element['#validate'] != array('download_attachment_submit')
                && $element['#validate'] != array('goto_dashboard')
                && $element['#validate'] != array('goto_list')) {
                $element['#access'] = false;
            }
        } else {
            $element['#disabled'] = true;
        }
    });
}

/**
 * @param $form
 * @param $form_state
 */
function go_back ($form, &$form_state) {
    if ($form_state['controller'] == 'new') {
        getif_goto('vinternship/view/2/'.$form_state['id_internship'],array(),302,true);
    } elseif ($form_state['controller'] == 'view-confirm') {
        getif_goto('vinternship/new/3/'.$form_state['id_internship'],array(),302,true);
    } elseif ($form_state['controller'] == 'view') {
        getif_goto('vinternship/view/2/'.$form_state['id_internship'],array(),302,true);
    }
}

/**
 * @param $form
 * @param $form_state
 */
function vinternship_3_form_submit($form, &$form_state) {
    $destination = '';
    if ($form_state['controller'] == 'new') {
        $id_internship = save($form, $form_state);
        $destination = 'vinternship/new/4/'.$id_internship;
        unset($_SESSION['new_internship_3']);
        drupal_set_message(t("Dati inseriti con successo"));
    } elseif ($form_state['controller'] == 'view') {
        if ($form_state['clicked_button']['#attributes']['flg_update'] == true) {
            delete_vinternship_step_data($form_state['id_internship'],$form_state['step']);
            $destination = 'vinternship/new/' . (intval($form_state['step'])) . '/' . $form_state['id_internship'];;
            drupal_set_message(t("Dati eliminati con successo"));
        } else {

            if (getInternshipStateById('getif_data', $form_state['id_internship']) > $form_state['step']) {
                $destination = 'vinternship/view/' . (intval($form_state['step']) + 1) . '/' . $form_state['id_internship'];
            } else {
                $destination = 'vinternship/new/' . (intval($form_state['step']) + 1) . '/' . $form_state['id_internship'];
            }
        }
    }
    drupal_goto($destination);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function save($form, &$form_state) {
    global $user;
    $id_internship = $form_state['id_internship'];
    // Motivo della Frequenza
    $fields = array(
        'id_internship' => $id_internship,
        'note' => $form_state['values']['aim'],
        'date_upd' => date("Y-m-d H:i:s", time()),
        'active' => 1
    );
    try {
        db_set_active('getif_data');
        $query = db_update('internship');
        $query -> fields($fields) -> condition('id_internship',$id_internship) ->condition('active',1) ->execute();
        db_set_active();
        // watchdog
        $w_type = 'getif'.'internship';
        $w_message = t('Update item with id_internship = %id_internship');
        $w_variables = array('%id_internship'=>$id_internship);
        watchdog($w_type, $w_message, $w_variables);
        db_set_active();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    // Allegato Parere Favorevole Dirigente Responsabile
    if (!empty($form_state['values']['positive_opinion_attachment'])) {
        try {
            db_set_active('getif_data');
            $query = db_update('internship_attachment');
            $query->fields(array(
                'active' => 0,
            ))->condition(db_and()->condition('id_internship', $id_internship)->condition('meta', 'parere_favorevole', 'LIKE'))->execute();
            db_set_active();
            // watchdog
            $w_type = 'getif_' . 'internship_attachment';
            $w_message = t('Delete items with id_internship: %id AND meta: %meta');
            $w_variables = array('%id' => $id_internship, '%meta' => 'parere_favorevole');
            watchdog($w_type, $w_message, $w_variables);
        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }
        try {
            db_set_active('getif_data');
            $query = db_insert('internship_attachment');
            $id_internship_attachment = $query->fields(array(
                'id_internship' => $id_internship,
                'id_file_managed' => $form_state['values']['positive_opinion_attachment'],
                'date_application' => date("Y-m-d H:i:s", time()),
                'meta' => 'parere_favorevole',
                'date_upd' => date("Y-m-d H:i:s", time()),
            ))->execute();
            db_set_active();
            // watchdog
            $w_type = 'getif' . 'id_internship_attachment';
            $w_message = t('Insert %id');
            $w_variables = array('%id' => $id_internship_attachment);
            watchdog($w_type, $w_message, $w_variables);
            // cambio lo stato del file in PERMANENTE
            $fid = $form_state['values']['positive_opinion_attachment'];
            $file = file_load($fid);
            $file->status = FILE_STATUS_PERMANENT;
            file_save($file);
            // Aggiungo un record in file_usage
            $file = new stdClass();
            $file->fid = $fid;
            file_usage_add($file, 'getif', 'internship_attachment', $id_internship_attachment);

        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }
    }
    // modifica stato frequenza
    $fields = array(
        'state' => 3,
        'active' => 1,
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    try {
        db_set_active('getif_data');
        $query = db_update('internship_state');
        $query -> fields($fields) -> condition('id_internship',$id_internship) -> condition('active',1)-> execute();
        db_set_active();
        // watchdog
        $w_type = 'getif_'.'internship_state';
        $w_message = t('Update item with id_internship: %id');
        $w_variables = array('%id'=>$id_internship);
        watchdog($w_type, $w_message, $w_variables);
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    // utente che ha modificato la scheda frequenza volontaria
    try {
        db_set_active('getif_data');
        // insert internship_user
        $query = db_insert('internship_user');
        $id_internship_user = $query -> fields(array(
            'id_internship' => $id_internship,
            'uid' => $user->uid,
            'action' => 'update'
        ))->execute();
        db_set_active();
        // watchdog
        $w_type = 'getif_'.'internship_user';
        $w_message = t('Insert item %id');
        $w_variables = array('%id'=>$id_internship_user);
        watchdog($w_type, $w_message, $w_variables);
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    return $id_internship;
}

/**
 * @param $form
 * @param $form_state
 */
function vinternship_3_form_validate($form, &$form_state) {
    $current_path = current_path();
    if (strpos($current_path, 'ajax') === false) {
        if(empty($form_state['values']['aim'])) {
            form_set_error('aim', t('il campo Motivo della Frequenza è obbligatorio'));
        }
        if(empty($form_state['field_cpersons'])) {
            form_set_error('cperson', t('Devi inserire almeno un responsabile/referente.'));
        }
    }
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_cperson_callback($form, &$form_state) {
    return $form['fs_contact_person']['cpersons_container'];
}


/**
 * @param $form
 * @param $form_state
 */
function add_cperson_submit($form, &$form_state) {
    $items = $form_state['field_cpersons'];
    $id_person = $form_state['values']['cperson_id'];
    if (!empty($id_person) && !in_array($id_person, $items)) {
        $form_state['field_cpersons'][$id_person] = $id_person;
        $form_state['rebuild'] = TRUE;
        // insert to DB
        $fields = array(
            'id_internship' => $form_state['id_internship'],
            'id_person_lperson_prole' => $id_person,
            'flg_primary' => (count($form_state['field_cpersons']) == 1)?1:0
        );
        $key = array(
            'id_internship' => $form_state['id_internship'],
            'id_person_lperson_prole' => $id_person,
            'active' => 1
        );
        db_set_active('getif_data');
        try {
            $query = db_merge('internship_project_contact');
            $id_internship_project_contact = $query -> key($key)->fields($fields)->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
        $form_state['rebuild'] = TRUE;
        drupal_set_message('Responsabile/Referente inserito con successo.', 'status');
        return;
    }
    $form_state['rebuild'] = TRUE;
    drupal_set_message('Responsabile/Referente non selezionato o gi&agrave; inserito.', 'warning');

}


/**
 * @param $form
 * @param $form_state
 */
function remove_cpersons_submit($form, &$form_state) {
    $selected = ($form_state['values']['cpersons_container']['table']);
    // elimina elementi selezionati
    foreach ($selected as $key => $item) {
        if($item != 0) {
            $fields = array(
                'id_internship' => $form_state['id_internship'],
                'id_person_lperson_prole' => $key,
                'active' => 0
            );
            $cond = array(
                'id_internship' => $form_state['id_internship'],
                'id_person_lperson_prole' => $key
            );
            db_set_active('getif_data');
            try {
                $query = db_merge('internship_project_contact');
                $id_intership_lperson= $query -> key($cond)->fields($fields)->execute();
            } catch (Exception $ex) {
                drupal_set_message('Errore: '.$ex,'error');
            }
            db_set_active();
            unset($form_state['field_cpersons'][$key]);
        }
    }
    // se rimane un solo elemento questo va reso primario
    if (count($form_state['field_cpersons']) == 1) {
        foreach ($form_state['field_cpersons'] as $key => $item) {
            $fields = array(
                'id_internship' => $form_state['id_internship'],
                'id_person_lperson_prole' => $key,
                'flg_primary' => 1,
                'active' => 1
            );
            $cond = array(
                'id_internship' => $form_state['id_internship'],
                'id_person_lperson_prole' => $key
            );
            db_set_active('getif_data');
            try {
                $query = db_merge('internship_project_contact');
                $id_intership_lperson = $query -> key($cond)->fields($fields)->execute();
            } catch (Exception $ex) {
                drupal_set_message('Errore: '.$ex,'error');
            }
            db_set_active();
        }
    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}

/**
 * @param $form
 * @param $form_state
 */
function check_cp_primary_submit($form, &$form_state) {

    $fields = array(
        'flg_primary' => 0,
    );
    $where = 'id_internship = '.$form_state['id_internship'].' and active = 1';
    try {
        db_set_active('getif_data');
        $query = db_update('internship_project_contact');
        $query ->fields($fields)->where($where)->execute();
        db_set_active();
    } catch (Exception $ex) {

    }
    $id_person_lperson_prole = $form_state['clicked_button']['#attributes']['id_person_lperson_prole'];
    $fields = array(
        'flg_primary' => 1,
    );
    $where = 'id_internship = '.$form_state['id_internship'].' and id_person_lperson_prole = '.$id_person_lperson_prole.' and active = 1';
    try {
        db_set_active('getif_data');
        $query = db_update('internship_project_contact');
        $query ->fields($fields)->where($where)->execute();
        db_set_active();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}

/* end */

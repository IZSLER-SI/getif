<?php

/**
 * Theme sezione nuova frequenza volontaria Scheda FV.4
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_vinternship_4_form($variables){
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
            <li><a href="#panel4" data-toggle="tab">Scheda FV.3</a></li>
        </ul>
        <div class="tab-content">
            <div id="panel1" class="tab-pane active panel-body ">
               '.drupal_render($form['intern_data']).'
            </div>
            <div id="panel2" class="tab-pane panel-body ">
               '.drupal_render($form['internship1_data']).drupal_render($form['richiesta_frequenza_volontaria']).'
            </div>
            <div id="panel3" class="tab-pane panel-body ">
               '.drupal_render($form['internship2_data']).drupal_render($form['dichiarazione_frequenza_volontaria']).'
            </div>
            <div id="panel4" class="tab-pane panel-body ">
               '.drupal_render($form['internship3_data']).drupal_render($form['parere_favorevole']).'
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
function vinternship_4_form($form, &$form_state) {
    $form_state['controller'] = $form_state["build_info"]["args"][0];
    if(isset($form_state["build_info"]["args"][1])) {
        $form_state['step'] = $form_state["build_info"]["args"][1];
    }
    $form_state['id_internship'] = !empty($form_state["build_info"]["args"][2])?$form_state["build_info"]["args"][2]:'';
    $internship = getVInternshipById('getif_data', $form_state['id_internship']);
    $form_state_values = session_get("new_internship_4");
    if ($form_state['controller'] == 'view') {
        if(empty($form_state['id_internship'])) {
            getif_goto('vinternship/list');
        } else {
            $rc_policy = json_decode($internship->insurance->rc_policy);
            $accident_policy = json_decode($internship->insurance->accident_policy);
            $form_state_values['rc_company'] = $rc_policy->company;
            $form_state_values['rc_policy_number'] = $rc_policy->policy_number;
            $form_state_values['accident_company'] = $accident_policy->company;
            $form_state_values['accident_policy_number'] = $accident_policy->policy_number;
            $meta_flags = json_decode($internship->meta_flags);
            $form_state_values['flag1'] = $meta_flags->flag1;
            $form_state_values['flag2'] = $meta_flags->flag2;
            $form_state_values['flag3'] = $meta_flags->flag3;
            $form_state_values['flag1_lprole'] = $meta_flags->flag1_lprole;
            $form_state_values['flag2_lprole'] = $meta_flags->flag2_lprole;
            $form_state_values['flag3_lprole'] = $meta_flags->flag3_lprole;
        }
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
    $form['internship3_data'] = array(
        '#markup' => getVInternship3DataByInternshipObj($internship)
    );
    foreach ($internship->attachments AS $meta => $attachment) {
        if ($meta == 'richiesta_frequenza_volontaria' || $meta == 'dichiarazione_frequenza_volontaria'  || $meta == 'parere_favorevole') {
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
    if (empty(session_get('internship'))) {
        session_set('internship',$internship);
    }

    $required = true;
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

    // Fieldset Estremi Assicurativi
    $form['fs_insurance'] = array(
        '#type' => 'container',
        '#title' => t('Estremi Assicurativi'),
        '#prefix' => '<div id="fs-insurance-div">',
        '#suffix' => '</div>',
    );
    $form['fs_insurance']['rc_company'] = array(
        '#type' => 'textfield',
        '#title' => t('Compagnia RC'),
        '#description' => t('Inserire Compagnia RC'),
        '#attributes' => array(
            'autocomplete' => 'off'
        ),
        '#required' => $required,

    );
    $form['fs_insurance']['rc_policy_number'] = array(
        '#type' => 'textfield',
        '#title' => t('Numero di polizza'),
        '#description' => t('Inserire numero di polizza RC'),
        '#attributes' => array(
            'autocomplete' => 'off'
        ),
        '#required' => $required,
    );
    $form['fs_insurance']['accident_company'] = array(
        '#type' => 'textfield',
        '#title' => t('Compagnia Assicurativa per infortuni'),
        '#description' => t('Inserire compagnia per infortuni'),
        '#attributes' => array(
            'autocomplete' => 'off'
        ),
        '#required' => $required,
    );
    $form['fs_insurance']['accident_policy_number'] = array(
        '#type' => 'textfield',
        '#title' => t('Numero di polizza infortuni'),
        '#description' => t('Inserire numero di polizza'),
        '#attributes' => array(
            'autocomplete' => 'off'
        ),
        '#required' => $required,
    );

    // FLAG
    $form['fs_checklist'] = array(
        '#type' => 'container',
        '#title' => t('Adempimenti'),
    );
    $lprole_options = getLibOptions('lib_lprole', 'getif_data');
    $lprole_options[1] = 'Altro Soggetto';
    $form['fs_checklist']['flag1'] = array(
        '#type' => 'checkbox',
        '#title' => t('Flag di conferma della prenotazione della visita del Medico Competente per la Sorveglianza Sanitaria e data, con indicazione se avvenuta presso:'),
        '#default_value' => 0,
        '#prefix' => '<div style="display:inline-block">',
        '#suffix' => '</div>',
        '#required' => $required,
    );
    $form['fs_checklist']['flag1_lprole'] = array(
        '#type' => 'select',
        '#title' => 'Visita presso',
        '#title_display' => 'invisible',
        '#empty_option' => t('- Seleziona -'),
        '#options' => $lprole_options,
        '#prefix' => '<div style="padding-left:10px;display:inline-block">',
        '#suffix' => '</div>',
        '#required' => true
    );
    $form['fs_checklist']['flag2'] = array(
        '#type' => 'checkbox',
        '#title' => t('Flag di conferma dell’avvenuta formazione generale in materia di salute e sicurezza negli ambienti di
lavoro e attestato in allegato, con indicazione se avvenuta presso:'),
        '#default_value' => 0,
        '#prefix' => '<div style="display:inline-block">',
        '#suffix' => '</div>',
        '#required' => $required,
    );
    $form['fs_checklist']['flag2_lprole'] = array(
        '#type' => 'select',
        '#title' => 'Formazione generale presso',
        '#title_display' => 'invisible',
        '#empty_option' => t('- Seleziona -'),
        '#options' => $lprole_options,
        '#prefix' => '<div style="padding-left:10px;display:inline-block">',
        '#suffix' => '</div>',
        '#required' => true
    );
    $form['fs_checklist']['flag3'] = array(
        '#type' => 'checkbox',
        '#title' => t('Flag di conferma dell’avvenuta formazione specifica in materia di salute e sicurezza negli ambienti di
lavoro e attestato in allegato, con indicazione se avvenuta presso:'),
        '#default_value' => 0,
        '#prefix' => '<div style="display:inline-block">',
        '#suffix' => '</div>',
        '#required' => $required,
    );
    $form['fs_checklist']['flag3_lprole'] = array(
        '#type' => 'select',
        '#title' => 'Formazione specifica presso',
        '#title_display' => 'invisible',
        '#empty_option' => t('- Seleziona -'),
        '#options' => $lprole_options,
        '#prefix' => '<div style="padding-left:10px;display:inline-block">',
        '#suffix' => '</div>',

        '#required' => true
    );

    // Submit Button
    $form['actions']['submit'] = array(
        '#type' => 'submit',
    );
    if ($form_state['controller'] == "new") {
        if (!empty($_SESSION['new_internship_4'])) {
            fill_data($form,$_SESSION['new_internship_4']);
            unset($_SESSION['new_internship_4']);
        }
        $form['actions']['submit']['#value'] = t('Salva');
        $form['actions']['submit']['#attributes']['controller'] = $form_state['controller'];
        $form['actions']['submit']['#attributes']['step'] = $form_state['step'];
        $form['actions']['submit']['#attributes']['id_internship'] = $form_state['id_internship'];
        $form['actions']['submit']['#attributes']['flg_update'] = false;
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler proseguire?")){return false;}';
        $form['actions']['update']['#access'] = false;
    } elseif ($form_state['controller'] == "view") {
        fill_data($form,$form_state_values);
        $form['nav']['submit'] = array(
            '#type' => 'submit',
        );
        $form['nav']['submit']['#value'] = t('Prosegui Gestione Frequenza');
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
 * @param $form_state
 */
function vinternship_4_form_validate($form, &$form_state){
    // empty
}

/**
 * @param $form
 * @param $form_state
 */
function vinternship_4_form_submit($form, &$form_state) {
    $destination = '';
    if ($form_state['controller'] == 'new') {
        $id_internship = save($form, $form_state);
        $destination = 'vinternship/manage/'.$id_internship;
        unset($_SESSION['new_internship_4']);
        drupal_set_message(t("Dati inseriti con successo"));
    } elseif ($form_state['controller'] == 'view') {
        if ($form_state['clicked_button']['#attributes']['flg_update'] == true) {
            delete_vinternship_step_data($form_state['id_internship'],$form_state['step']);
            $destination = 'vinternship/new/' . (intval($form_state['step'])) . '/' . $form_state['id_internship'];;
            drupal_set_message(t("Dati eliminati con successo"));
        } else {
            $destination = 'vinternship/manage/' . $form_state['id_internship'];
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
    $id_internship = $form_state['id_internship'];
    // Inserisci i dati dell'assicurazione
    $rc_insurance = json_encode(array('company'=>$form_state['values']['rc_company'],'policy_number'=>$form_state['values']['rc_policy_number']),JSON_UNESCAPED_UNICODE);
    $insurance = json_encode(array('company'=>$form_state['values']['accident_company'],'policy_number'=>$form_state['values']['accident_policy_number']));
    try {
        db_set_active('getif_data');
        $query = db_insert('internship_insurance');
        $id_internship_insurance = $query -> fields(array(
            'id_internship' => $id_internship,
            'rc_policy' => $rc_insurance,
            'accident_policy' => $insurance,
            'active' => 1
        ))->execute();
        db_set_active();
        // watchdog
        $w_type = 'getif'.'internship_insurance';
        $w_message = t('Insert %id');
        $w_variables = array('%id'=>$id_internship_insurance);
        watchdog($w_type, $w_message, $w_variables);
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    // Inserisci i dati dei flag di formazione
    try {
        $flag = json_encode(array('flag1'=>$form_state['values']['flag1'],'flag2'=>$form_state['values']['flag2'],'flag3'=>$form_state['values']['flag3'],
            'flag1_lprole'=>$form_state['values']['flag1_lprole'],'flag2_lprole'=>$form_state['values']['flag2_lprole'],'flag3_lprole'=>$form_state['values']['flag3_lprole']));
        // update flag
        db_set_active('getif_data');
        $query = db_update('internship');
        $query -> condition('id_internship',$id_internship);
        $query -> fields(array(
            'meta_flags' => $flag,
            'date_upd' => date("Y-m-d H:i:s", time())
        ))->execute();
        db_set_active();
        db_set_active();
        // watchdog
        $w_type = 'getif_'.'internship';
        $w_message = t('Update item with id_internship: %id');
        $w_variables = array('%id'=>$id_internship);
        watchdog($w_type, $w_message, $w_variables);
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    // update stato della frequenza e data
    $fields = array(
        'state' => 4,
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
    global $user;
    // utente che ha modificato la scheda frequenza
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
 * @param $form_state_values
 */
function fill_data(&$form, $form_state_values) {
    $form['fs_insurance']['rc_company']['#default_value'] = !empty($form_state_values['rc_company'])?$form_state_values['rc_company']:'';
    $form['fs_insurance']['rc_policy_number']['#default_value'] = !empty($form_state_values['rc_policy_number'])?$form_state_values['rc_policy_number']:'';
    $form['fs_insurance']['accident_company']['#default_value'] = !empty($form_state_values['accident_company'])?$form_state_values['accident_company']:'';
    $form['fs_insurance']['accident_policy_number']['#default_value'] = !empty($form_state_values['accident_policy_number'])?$form_state_values['accident_policy_number']:'';
    $form['fs_checklist']['flag1']['#default_value'] = !empty($form_state_values['flag1'])?$form_state_values['flag1']:'';
    $form['fs_checklist']['flag2']['#default_value'] = !empty($form_state_values['flag2'])?$form_state_values['flag2']:'';
    $form['fs_checklist']['flag3']['#default_value'] = !empty($form_state_values['flag3'])?$form_state_values['flag3']:'';
    $form['fs_checklist']['flag1_lprole']['#default_value'] = !empty($form_state_values['flag1_lprole'])?$form_state_values['flag1_lprole']:'';
    $form['fs_checklist']['flag2_lprole']['#default_value'] = !empty($form_state_values['flag2_lprole'])?$form_state_values['flag2_lprole']:'';
    $form['fs_checklist']['flag3_lprole']['#default_value'] = !empty($form_state_values['flag3_lprole'])?$form_state_values['flag3_lprole']:'';

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
        getif_goto('vinternship/view/3/'.$form_state['id_internship'],array(),302,true);
    } elseif ($form_state['controller'] == 'view-confirm') {
        getif_goto('vinternship/new/4/'.$form_state['id_internship'],array(),302,true);
    } elseif ($form_state['controller'] == 'view') {
        getif_goto('vinternship/view/3/'.$form_state['id_internship'],array(),302,true);
    }
}

/* end */
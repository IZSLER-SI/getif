<?php

/**
 * Theme sezione nuovo tirocinio Scheda Ti.1
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_internship_1_form($variables){
    $form = $variables['form'];
    $header_content = array();
    if(!empty(arg(2))) {
        $header_content[]['html'] = get_internship_new_header(arg(2));
    }
    $options = array();
    $options['show_fs_title'] = true;
    return getif_form_theme($form,$header_content,$options);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function internship_1_form($form, &$form_state) {
    // get arguments
    $form_state['controller'] = $form_state["build_info"]["args"][0];
    if (isset($form_state["build_info"]["args"][1])) {
        $form_state['step'] = $form_state["build_info"]["args"][1];
    }
    $form_state['id_internship'] = !empty($form_state["build_info"]["args"][2]) ? $form_state["build_info"]["args"][2] : '';
    // redirect

    if ($form_state['controller'] == 'view') {
        if (empty($form_state['id_internship'])) {
            getif_goto('internship/list');
        }
    }
    if (!empty($form_state['id_internship'])) { // edit
        $internship = getInternshipById('getif_data', $form_state['id_internship']);
        $form_state_values = array(
            'intern' => $internship->person->firstname . ' ' . $internship->person->lastname . ' (' . $internship->person->tax_code . ')',
            'promoter' => $internship->promoter->name,
            'promoter_id' => $internship->promoter->id_lperson_lprole,
            'host' => $internship->host->name,
            'host_id' => $internship->host->id_lperson_lprole,
            'agreement' => array_search($internship->agreement->number_code, getAgreementsByHP($internship->promoter->id_lperson_lprole, $internship->host->id_lperson_lprole)),
            'internship_type' => $internship->internship_type->flg_extra_curricular . '|' . $internship->internship_type->id_internship_type,
            'date_application' => $internship->date_application,
            'date_start' => $internship->date_start,
            'date_end' => $internship->date_end,
            'attachment' => !empty($internship->attachments['richiesta_tirocinio']->id_file_managed)?$internship->attachments['richiesta_tirocinio']->id_file_managed:null
        );
    }
    if (!empty(session_get('new_internship_1'))) {
        $form_state_values = session_get('new_internship_1');
    }

    $required = TRUE;
    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    $form['nav']['goto_list'] = array(
        '#type' => 'button',
        '#value' => t('Tirocini'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'internship'
        )
    );
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Indietro'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back'),
    );

    /* TIROCINANTE */
    // Fieldset Tirocinante
    $form['fs_intern'] = array(
        '#type' => 'container',
        '#title' => t('Tirocinante'),
        '#prefix' => '<div id="fs-intern-div">',
        '#suffix' => '</div>',

    );
    // Campo di ricerca tirocinante - visualizza il Nome Cognome (Cod.Fisc.)
    $form['fs_intern']['intern'] = array(
        '#type' => 'textfield',
        '#title' => t('Tirocinante'),
        '#description' => t('Selezionare un tirocinante inserendo NOME O COGNOME O COD.FISC oppure creane uno nuovo'),
        '#autocomplete_path' => 'intern_autocomplete_callback',
        '#ajax' => array(
            'callback' => 'ajax_intern_after_autocomplete_callback',
            'wrapper' => 'fs-intern-div',
            'progress' => array(
                'message' => '',
                'type' => 'throbber',
            ),
        ),
        '#attributes' => array(
            'class' => array('auto_submit', 'form-autocomplete'),
            'placeholder' => t('RSSMRA75L01H501 - Mario Rossi'),
        ),
        '#required' => $required
    );
    // id del tirocinante
    $form['fs_intern']['intern_id'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'id' => 'edit-intern_id'
        )
    );
    $form['fs_intern']['new_intern_submit'] = array(
        '#type' => 'button',
        '#value' => t('Nuovo Tirocinante'),
        '#limit_validation_errors' => array(),
        '#validate' => array('new_intern_submit'),
        '#attributes' => array(
            'onsubmit' => 'return false'
        ),
    );
    $form['fs_intern']['new_intern_submit']['#attributes']['onkeypress'][] = "jQuery('input').keydown(function(e) {if (e.keyCode == 13) {e.preventDefault(); jQuery('#edit-submit').mousedown();}});";
    /*CONVENZIONE*/
    $form['fs_agreement'] = array(
        '#type' => 'container',
        '#title' => t('Convenzione'),
        '#prefix' => '<div id="fs-agreement-div">',
        '#suffix' => '</div>',
    );

    // Prende l'host IZSLER che ha id = 1
    $host = getRecordById('lperson','getif_data', 1);
    $form_state['host'] = $host->name;
    // Soggetto ospitante
    $form['fs_agreement']['host'] = array(
        '#type' => 'textfield',
        '#title' => t('Soggetto Ospitante'),
        '#description' => t('Selezionare un Soggetto Ospitante inserendo ragione sociale, p.iva o codice fiscale'),
        '#default_value' => $form_state['host'],
        '#attributes' => array(
            'placeholder' => t('P.IVA / Cod.Fisc. - Nome Soggetto '),
            'style' => 'max-width: 460px',
            'disabled' => ''
        ),
        '#required' => $required
    );

    $form['fs_agreement']['host_id'] = array(
        '#type' => 'hidden',
        '#default_value' => $host->id_lperson,
        '#attributes' => array(
            'id' => 'host_id',
        ),
    );

    // Soggetto Promotore
    $form['fs_agreement']['promoter'] = array(
        '#type' => 'textfield',
        '#title' => t('Soggetto Promotore'),
        '#description' => t('Selezionare un Soggetto Promotore inserendo ragione sociale, p.iva o codice fiscale'),
        '#autocomplete_path' => 'lperson_lprole_autocomplete_callback/1',
        '#ajax' => array(
            'callback' => 'ajax_ph_after_autocomplete_callback',
            'wrapper' => 'agreement-div',
            'progress' => array(
                'message' => '',
                'type' => 'throbber',
            ),

        ),
        '#attributes' => array(
            'placeholder' => t('P.IVA / Cod.Fisc. - Nome Soggetto '),
        ),
        '#required' => $required,
    );

    $form['fs_agreement']['promoter_id'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'id' => 'promoter_id',
        ),
    );
    // Convenzione tra Soggetto Promotore e Ospitante scelto. Questo campo serve per il controllo della visibilità delle date di tirocinio
    // Verrà sostituito con un campo visibile dopo la scelta dei Soggetti Promotore e Ospitante
    $host_id = empty($form_state['input']['host_id']) ? (empty($form_state_values['host_id']) ? null : $form_state_values['host_id']) : $form_state['input']['host_id'];
    $promoter_id = empty($form_state['input']['promoter_id']) ? (empty($form_state_values['promoter_id']) ? null : $form_state_values['promoter_id']) : $form_state['input']['promoter_id'];
    $form['fs_agreement']['agreement_div_ajax_wrapper'] = array('#prefix' => '<div id="agreement-div">', '#suffix' => '</div>');
    $form['fs_agreement']['agreement_div_ajax_wrapper']['agreement'] = array(
        '#type' => 'select',
        '#title' => t('Convenzione'),
        '#options' => array(),
        '#empty_option' => t('- Seleziona -'),
        '#prefix' => '<div style="display:none;">',
        '#suffix' => '</div>',
        '#name' => 'agreement',
        '#states' => array(
            'visible' => array(
                ':input[name="promoter"]' => array('filled' => TRUE),
            ),
        ),
    );

    if (!empty($promoter_id) && !empty($host_id)) {

        $form['fs_agreement']['agreement_div_ajax_wrapper']['insert_agreement'] = array(
            '#type' => 'button',
            '#value' => t('Nuova Convenzione'),
            '#limit_validation_errors' => array(),
            '#validate' => array('new_agreement_submit'),
            '#suffix' => '<br><br>'
        );
        $options = getAgreementsByHPIds($promoter_id, $host_id);
        if (!empty($options)) {
            $form['fs_agreement']['agreement_div_ajax_wrapper']['agreement'] = array(
                '#type' => 'select',
                '#title' => t('Convenzione'),
                '#options' => $options,
                '#empty_option' => t('- Seleziona -'),
                '#ajax' => array(
                    'event' => 'change',
                    'callback' => 'internship_type_ajax_callback',
                    'wrapper' => 'type-ajax-wrapper',
                ),
                '#required' => $required,
            );
            $form['fs_agreement']['agreement_div_ajax_wrapper']['type_ajax_wrapper'] = array('#prefix' => '<div id="type-ajax-wrapper">', '#suffix' => '</div>');
            $id_agreement_selected = empty($form_state['input']['agreement']) ?
                (empty($form_state_values['agreement']) ? '0' : $form_state_values['agreement']) : $form_state['input']['agreement'];

            if ($id_agreement_selected != '0') {
                if (empty(getAgreementCurricularFlg($id_agreement_selected))) { // se non è specificato
                    $type_options = getInternshipTypeOptions('lib_internship_type', 'getif_data');
                    $type = '';
                } else {
                    if (getAgreementCurricularFlg($id_agreement_selected) == '2') {
                        $type_options = getInternshipTypeOptions('lib_internship_type', 'getif_data', 'flg_extra_curricular', '1');
                        $type = t('extracurriculare');
                    } elseif (getAgreementCurricularFlg($id_agreement_selected) == '1') {
                        $type_options = getInternshipTypeOptions('lib_internship_type', 'getif_data', 'flg_extra_curricular', '0');
                        $type = t('curriculare');
                    } elseif (getAgreementCurricularFlg($id_agreement_selected) == '3') {
                        $type_options = getInternshipTypeOptions('lib_internship_type', 'getif_data');
                        $type = t('curriculare').'/'.t('extracurriculare');
                    } else {
                        $type_options = array();
                        $type = '';
                    }
                }
                $agreement = getRecordById('agreement', 'getif_data', $id_agreement_selected);
                $agreement_suffix = '<div {$class} {$style}>La convenzione {$name} scade il {$date_end}.</div>';
                $vars = array(
                    '{$class}' => '',
                    '{$name}' => strtoupper($agreement->number_code),
                    '{$style}' => 'style="padding:3px 7px 3px 7px;margin-bottom: 20px"',
                    '{$date_end}' => date('d-m-Y', strtotime($agreement->date_end))
                );

                if (getDaysDiff(date('Y-m-d'),$agreement->date_end) < 60) {
                    $vars['{$class}'] = 'class="btn-danger"';
                } else {
                    $vars['{$class}'] = 'class="btn-warning"';
                }
                $agreement_suffix = strtr($agreement_suffix, $vars);
                $form['fs_agreement']['agreement_div_ajax_wrapper']['type_ajax_wrapper']['internship_type'] = array(
                    '#type' => 'radios',
                    '#empty_option' => t('- select a subtype -'),
                    '#title' => 'Tipi di Tirocinio ' . $type,
                    '#required' => $required,
                    '#options' => $type_options,
                    '#prefix' => strtr($agreement_suffix, $vars)
                );
            }
        } else {
            $form['fs_agreement']['agreement_div_ajax_wrapper']['agreement_markup'] = array(
                '#markup' => '<div class="alert messages error">' . t('Non ci sono convenzioni attive per i due Soggetti') . '</div>',
            );
        }

    }
    // Date Tirocinio - Questo fieldset sarà visibile solo se è stata scelta la Convenzione
    $form['fs_data'] = array(
        '#type' => 'container',
        '#title' => '',
        '#states' => array(
            'visible' => array(
                ':input[name="agreement"]' => array('!value' => ''),
            )
        )
    );
    // Data di Richiesta Tirocinio
    $form['fs_data']['date_application'] = array(
        '#type' => 'textfield',
        '#title' => t('Data di presentazione domanda'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date', 'js-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_application'
        ),
        '#prefix' => '<legend class="panel-heading-2"><span class="panel-title">Date</span></legend><div style="padding:5px">'
    );
    $form['fs_data']['date_start'] = array(
        '#type' => 'textfield',
        '#title' => t('Data di inizio tirocinio'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date', 'js-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_start'
        ),
    );
    $form['fs_data']['date_end'] = array(
        '#type' => 'textfield',
        '#title' => t('Data di fine tirocinio'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date', 'js-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_end',
            'maxDuration' => 12
        ),
        '#suffix' => '</div>'
    );

    // Allegato Richiesta Tirocinio
    $form['fs_attachment'] = array(
        '#type' => 'container',
        '#title' => t('Allegato Richiesta Tirocinio'),
    );
    $form['fs_attachment']['attachment'] = array(
        '#type' => 'managed_file',
        '#title' => 'File Allegato Richiesta Tirocinio',
        '#suffix' => '<span>' . getRequiredHtml() . '</span>',
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#description' => t('Click "Browse..." to select an attachment to upload.'),
        '#upload_validators' => array(
            'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
        ),
        '#upload_location' => 'public://attached/internship/' . (getMaxKey("internship", "getif_data") + 1) . '/'
    );
    // Submit Button
    $form['actions']['submit'] = array(
        '#type' => 'submit',
    );
    if ($form_state['controller'] == 'new') {
        $form['nav']['back']['#access'] = false;
        $form['actions']['submit']['#value'] = t('Salva');
        $form['actions']['submit']['#attributes']['controller'] = $form_state['controller'];
        $form['actions']['submit']['#attributes']['step'] = $form_state['step'];
        $form['actions']['submit']['#attributes']['id_internship'] = $form_state['id_internship'];
        $form['actions']['submit']['#attributes']['flg_update'] = false;
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler proseguire?")){return false;}';
        $form['actions']['update']['#access'] = false;
        if (!empty($_SESSION['new_internship_1'])) {
            fill_data($form, $_SESSION['new_internship_1'], $form_state);
            unset($_SESSION['new_internship_1']);
        }
    } elseif ($form_state['controller'] == 'view') {
        $form['nav']['back']['#access'] = false;
        fill_data($form, $form_state_values, $form_state); // da cancellare
        $form['nav']['submit'] = array(
            '#type' => 'submit',
        );
        $form['nav']['submit']['#value'] = t('Prosegui Scheda Ti.') . ($form_state['step'] + 1);
        $form['nav']['submit']['#attributes']['controller'] = $form_state['controller'];
        $form['nav']['submit']['#attributes']['step'] = $form_state['step'];
        $form['nav']['submit']['#attributes']['id_internship'] = $form_state['id_internship'];
        $form['nav']['submit']['#attributes']['flg_update'] = false;
        // Button Modifica
        // se lo stato del tirocinio è != 0 (Annullato) OR < 5 (5 - attivo OR 6 - attivo con proroga OR 7 - concluso) la funzione di modifica è disponibile:
        if ($internship->internship_state->state > 0 AND $internship->internship_state->state < 5 AND $internship->internship_state->date_start == NULL) {
            $form['actions']['update'] = array(
                '#type' => 'submit',
                '#submit' => array('internship_1_form_update')
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
 */
function disable_form_editing(&$form) {
    _iterate_form($form, function(&$element, $form){
        if (!empty($element['#type']) && ($element['#type'] == 'submit' || $element['#type'] == 'button')) {
            if (!empty($element['#submit']) && $element['#submit'] != array('back') && $element['#submit'] != array('internship_1_form_update')) {
                $element['#access'] = false;
            }
            if (!empty($element['#validate']) && $element['#validate'] != array('go_back') && $element['#validate'] != array('goto_dashboard') && $element['#validate'] != array('goto_list')) {
                $element['#access'] = false;
            }
        } else {
            $element['#disabled'] = true;
        }
    });
}


/**
 * @param $form
 * @param $form_state_values
 * @param $form_state
 */
function fill_data(&$form, $form_state_values, &$form_state) {
    $form['fs_intern']['intern']['#title'] = t('Tirocinante');
    $form['fs_intern']['intern']['#default_value'] = !empty($form_state_values['intern'])?_strformat($form_state_values['intern']):'';
    $form['fs_intern']['intern_id']['#value'] = !empty($form_state_values['intern_id'])?$form_state_values['intern_id']:'';
    // agreement
    $form['fs_agreement']['promoter']['#default_value'] = !empty($form_state_values['promoter'])?$form_state_values['promoter']:'';
    $form['fs_agreement']['promoter_id']['#value'] = !empty($form_state_values['promoter_id'])?$form_state_values['promoter_id']:'';
    $form['fs_agreement']['host']['#default_value'] = !empty($form_state_values['host'])?$form_state_values['host']:'';
    $form['fs_agreement']['host_id']['#value'] = !empty($form_state_values['host_id'])?$form_state_values['host_id']:'';
    $form['fs_agreement']['agreement_div_ajax_wrapper']['agreement']['#default_value'] = !empty($form_state_values['agreement'])?$form_state_values['agreement']:'';
    // other data
    if (!empty($form['fs_agreement']['agreement_div_ajax_wrapper']['type_ajax_wrapper']['internship_type'])) {
        $id_internship_type = !empty($form_state_values['internship_type']) ? $form_state_values['internship_type'] : '';
        if (array_key_exists($id_internship_type, $form['fs_agreement']['agreement_div_ajax_wrapper']['type_ajax_wrapper']['internship_type']['#options']))
            $form['fs_agreement']['agreement_div_ajax_wrapper']['type_ajax_wrapper']['internship_type']['#default_value'] = $id_internship_type;
    }
    if (!empty($form_state_values['date_application'])) {
        $form['fs_data']['date_application']['#default_value'] = date("d-m-Y",strtotime($form_state_values['date_application']));
    }
    if (!empty($form_state_values['date_start'])) {
        $form['fs_data']['date_start']['#default_value'] = date("d-m-Y",strtotime($form_state_values['date_start']));
    }
    if (!empty($form_state_values['date_end'])) {
        $form['fs_data']['date_end']['#default_value'] = date("d-m-Y",strtotime($form_state_values['date_end']));
    }
    if (!empty($form_state_values['attachment'])) {
        if (!empty($form_state_values['attachment']['fid']))
            $form['fs_attachment']['attachment']['#default_value'] = $form_state_values['attachment']['fid'];
        elseif (is_string($form_state_values['attachment']))
            $form['fs_attachment']['attachment']['#default_value'] = $form_state_values['attachment'];
    }
}


/**
 * @param $form
 * @param $form_state
 */
function go_back ($form, &$form_state) {
    if ($form_state['controller'] == 'new') {
        getif_goto('internship/list',array(),302,true);
    } elseif ($form_state['controller'] == 'view-confirm') {
        getif_goto('internship/new/1',array(),302,true);
    } elseif ($form_state['controller'] == 'view') {
        getif_goto('internship/list',array(),302,true);
    }
}


/**
 * @param $form
 * @param $form_state
 */
function internship_1_form_validate($form, &$form_state) {

    // Controllo sulla selezione del tipo di tirocinio
    if(empty($form_state['values']['internship_type'])) {
        form_set_error('internship_type', t('Devi selezionare il tipo di tirocinio.'));
    }
    // Controllo selezione convenzione attiva
    if(empty($form['fs_agreement']['agreement_div_ajax_wrapper']['agreement'])) {
        form_set_error('agreement', t('Devi selezionare un SO e un SP con una convenzione attiva oppure crearne una nuova.'));
    }

    /* Controlli avanzati */

    /* 1. Controllo tirocinante selezionato non abbia altri tirocini attivi */

    if(!empty($form_state['values']['intern_id']) && check_intern_internship_active($form_state['values']['intern_id']) != 0) {
        form_set_error('intern', t('Il tirocinante selezionato ha già un tirocinio attivo'));
    }
    // 2. Controllare che le date previste del tirocinio non siano fuori le date della convenzione
    if(!empty($form_state['values']['agreement']) && !empty($form_state['values']['date_start']) && !empty($form_state['values']['date_end'])) {
        $agreement = getRecordById('agreement', 'getif_data', $form_state['values']['agreement']);
        if(!empty($agreement) && getDaysDiff($agreement->date_start,date("Y-m-d", strtotime($form_state['values']['date_start']))) < 0) {
            form_set_error('date_start', t('La data di inizio tirocinio non può essere precedente alla data di inizio della convenzione: '.date("d-m-Y", strtotime($agreement->date_start))));
        }
    }
    // 3. Controllare la successione delle date
    if(!empty($form_state['values']['date_application']) && !empty($form_state['values']['date_start'])) {
        if (getDaysDiff(date("Y-m-d", strtotime($form_state['values']['date_application'])), date("Y-m-d", strtotime($form_state['values']['date_start']))) < 0) {
            form_set_error('date_start', t('La data di inizio tirocinio non può essere successiva alla data di presentazione della domanda.'));
        }
    }
    if(!empty($form_state['values']['date_start']) && !empty($form_state['values']['date_end'])) {
        if(getDaysDiff(date("Y-m-d", strtotime($form_state['values']['date_start'])),date("Y-m-d", strtotime($form_state['values']['date_end']))) < 0) {
            form_set_error('date_start', t('La data di fine tirocinio non può essere successiva alla data di inizio.'));
        } else {
            // 4. Controllo durata massima Tirocinio: non può durare più di 12 mesi
            if (!empty($form_state['values']['date_start']) && !empty($form_state['values']['date_end'])) {
                if (getMonthsDiff(date("Y-m-d", strtotime($form_state['values']['date_start'])),date("Y-m-d", strtotime($form_state['values']['date_end']))) >= 12) {
                    form_set_error('date_end', t('Il tirocinio non può durare più di 12 mesi.'));
                }
            }
            // 5. Controllo durata tirocinio extracurriculare
            if (!empty($form_state['values']['date_start']) && !empty($form_state['values']['date_end']) &&
                !empty($form_state['values']['date_start']) && !empty($form_state['values']['date_end']) &&
                !empty($form_state['values']['internship_type']) && explode('|',$form_state['values']['internship_type'])[0] == '1') {
                if (getMonthsDiff(date("Y-m-d", strtotime($form_state['values']['date_start'])),date("Y-m-d", strtotime($form_state['values']['date_end']))) < 2) {
                    form_set_error('date_end', t('Il tirocinio extracurriculare deve durare almeno due mesi.'));
                }
            }
        }
    }
}


/**
 * @param $form
 * @param $form_state
 */
function internship_1_form_update($form, &$form_state) {
    if ($form_state['clicked_button']['#attributes']['flg_update'] == true) {
        delete_internship_step_data($form_state['id_internship'], $form_state['step']);
        $destination = 'internship/new/' . (intval($form_state['step']));
        drupal_set_message(t("Dati eliminati con successo"));
    } else {
        if (getInternshipStateById('getif_data', $form_state['id_internship']) > $form_state['step']) {
            $destination = 'internship/view/' . (intval($form_state['step']) + 1) . '/' . $form_state['id_internship'];
        } else {
            $destination = 'internship/new/' . (intval($form_state['step']) + 1) . '/' . $form_state['id_internship'];
        }
    }
    drupal_goto($destination);
}


/**
 * @param $form
 * @param $form_state
 */
function internship_1_form_submit($form, &$form_state) {
    $controller = $form_state['clicked_button']['#attributes']['controller'];
    $destination = '';
    if ($controller == 'new') {
        $form_state['values']['internship_type'] = $form_state['input']['internship_type'];
        $id_internship = save($form, $form_state);
        $destination = 'internship/new/2/'.$id_internship;
        unset($_SESSION['new_internship_1']);
        drupal_set_message(t("Dati inseriti con successo"));
    } elseif ($controller == 'view') {
        if ($form_state['clicked_button']['#attributes']['flg_update'] == true) {
            delete_internship_step_data($form_state['id_internship'],$form_state['step']);
            $destination = 'internship/new/' . (intval($form_state['step']));
            drupal_set_message(t("Dati eliminati con successo"));
        } else {
            if (getInternshipStateById('getif_data',$form_state['id_internship']) > $form_state['step']) {
                $destination = 'internship/view/'.(intval($form_state['step'])+1).'/'.$form_state['id_internship'];
            } else {
                $destination = 'internship/new/'.(intval($form_state['step'])+1).'/'.$form_state['id_internship'];
            }
        }
    }
    drupal_goto($destination);
}


/**
 * @param $form
 * @param $form_state
 * @return DatabaseStatementInterface|int
 */
function save($form, &$form_state) {
    // insert new internship
    try {
        db_set_active('getif_data');
        $query = db_insert('internship');
        $id_internship = $query->fields(array(
            'flg_voluntary' => '0',
            'id_internship_type' => explode('|', $form_state['values']['internship_type'])[1],
            'date_application' => date("Y-m-d", strtotime($form_state['values']['date_application'])),
            'date_start' => date("Y-m-d", strtotime($form_state['values']['date_start'])),
            'date_end' => date("Y-m-d", strtotime($form_state['values']['date_end'])),
        ))->execute();
        db_set_active();
        // watchdog
        $w_type = 'getif_internship';
        $w_message = t('Insert item %id');
        $w_variables = array('%id'=>$id_internship);
        watchdog($w_type, $w_message, $w_variables);
        // internhsip person
        $id_person = $form_state['values']['intern_id'];
        try {
            db_set_active('getif_data');
            $query = db_insert('internship_person');
            $fields = array(
                'id_internship' => $id_internship,
                'id_person' => $id_person,
            );
            $id_internship_person = $query -> fields($fields)->execute();
            db_set_active();
            // watchdog
            $w_type = 'getif_internship_person';
            $w_message = t('Insert item %id');
            $w_variables = array('%id'=>$id_internship_person);
            watchdog($w_type, $w_message, $w_variables);
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        // get Agreement ID by IZSLER number
        try {
            db_set_active('getif_data');
            $id_agreement = getAgreementByNumIZS($form['fs_agreement']['agreement_div_ajax_wrapper']['agreement']['#options'][$form_state['values']['agreement']]);
            // insert internship_agreement
            $query = db_insert('internship_agreement');
            $id_internship_agreement = $query -> fields(array(
                'id_internship' => $id_internship,
                'id_agreement' => $id_agreement,
            ))->execute();
            db_set_active();
            // watchdog
            $w_type = 'getif_internship_agreement';
            $w_message = t('Insert item %id');
            $w_variables = array('%id'=>$id_internship_agreement);
            watchdog($w_type, $w_message, $w_variables);
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        // insert internship state
        try {
            db_set_active('getif_data');
            $query = db_insert('internship_state');
            $id_internship_state = $query -> fields(array(
                'id_internship' => $id_internship,
                'state' => 1,
                'date_upd' => date("Y-m-d H:i:s", time()),
            ))->execute();
            db_set_active();
            // watchdog
            $w_type = 'getif_internship_state';
            $w_message = t('Insert item %id');
            $w_variables = array('%id'=>$id_internship_state);
            watchdog($w_type, $w_message, $w_variables);
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        // file
        // se è stato allegato un file allora lo salva
        if (!empty($form_state['values']['attachment'])) {
            try {

                db_set_active('getif_data');
                // prima elimino l'allegato precedente
                $query = db_update('internship_attachment');
                $query->fields(array(
                    'active' => 0,
                ))->condition(db_and()->condition('id_internship', $id_internship)->condition('meta', 'richiesta_tirocinio', 'LIKE'))->execute();
                db_set_active();
                // watchdog
                $w_type = 'getif_' . 'internship_attachment';
                $w_message = t('Delete items with id_internship: %id AND meta: %meta');
                $w_variables = array('%id' => $id_internship, '%meta' => 'richiesta_tirocinio');
                watchdog($w_type, $w_message, $w_variables);

                // poi inserisco il nuovo allegato
                db_set_active('getif_data');
                $query = db_insert('internship_attachment');
                $id_internship_attachment = $query->fields(array(
                    'id_internship' => $id_internship,
                    'id_file_managed' => $form_state['values']['attachment'],
                    'date_application' => date("Y-m-d H:i:s", time()),
                    'meta' => 'richiesta_tirocinio',
                    'date_upd' => date("Y-m-d H:i:s", time()),
                ))->execute();
                db_set_active();

                // watchdog
                $w_type = 'getif_' . 'internship_attachment';
                $w_message = t('Insert item %id');
                $w_variables = array('%id' => $id_internship_attachment);
                watchdog($w_type, $w_message, $w_variables);
                // cambio lo stato del file in PERMANENTE
                $fid = $form_state['values']['attachment'];
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

        global $user;
        // utente che ha creato la scheda tirocinio
        try {
            db_set_active('getif_data');
            // insert internship_user
            $query = db_insert('internship_user');
            $id_internship_user = $query -> fields(array(
                'id_internship' => $id_internship,
                'uid' => $user->uid,
                'action' => 'create'
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

    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    return $id_internship;
}

/**
 * @param $form
 * @param $form_state
 */
function edit($form, &$form_state) {
    // empty
}


/**
 * @param $form
 * @param $form_state
 */
function new_intern_submit($form, $form_state) {
    unset($_SESSION['new_internship_1']);
    session_set('new_internship_1',$form_state['values']);
    if (isset($_SESSION['prev'])) {
        if ($_SESSION['prev'] != drupal_get_destination()["destination"]) {
            session_set('prev',(drupal_get_destination()["destination"]));
        }
    }
    getif_goto('intern/new',array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function new_agreement_submit($form, $form_state) {
    unset($_SESSION['new_internship_1']);
    session_set('new_internship_1',array_merge($form_state['input'],array('host'=>$form_state['host'])));
    session_set('prev',(drupal_get_destination()["destination"]));
    getif_goto('agreement/new',array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function ajax_ph_after_autocomplete_callback($form, &$form_state) {
    if($form_state['values']['promoter'] == '') {
        $form['fs_agreement']['promoter_id']['#value'] = '';
    } elseif($form_state['values']['host'] == '') {
        $form['fs_agreement']['host_id']['#value'] = '';
    }
    return $form['fs_agreement']['agreement_div_ajax_wrapper'];
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function internship_type_ajax_callback($form, $form_state) {
    return $form['fs_agreement']['agreement_div_ajax_wrapper']['type_ajax_wrapper'];
}


/* end */
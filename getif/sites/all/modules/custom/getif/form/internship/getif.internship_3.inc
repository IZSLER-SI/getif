<?php

/**
 * Theme sezione nuovo tirocinio Scheda Ti.3
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_internship_3_form($variables){
    $form = $variables['form'];
    $header_content = array();
    $output = '';
    if(!empty(arg(2))) {
        $output .= get_internship_new_header(arg(2));
    }
    $output .= '<div class="panel panel-default">';
    $output .= '
        <ul class="nav nav-tabs" style = "background-color: #f5f5f5;">
            <li class="active"><a href="#panel1" data-toggle="tab">Tirocinante</a></li>
            <li><a href="#panel2" data-toggle="tab">Scheda Ti.1</a></li>
            <li><a href="#panel3" data-toggle="tab">Scheda Ti.2</a></li>
        </ul>
        <div class="tab-content">
            <div id="panel1" class="tab-pane active panel-body ">
               '.drupal_render($form['intern_data']). drupal_render($form['dichiarazione_compatibilita_borsa_di_studio']) . '
            </div>
            <div id="panel2" class="tab-pane panel-body ">
               '.drupal_render($form['internship1_data']).drupal_render($form['richiesta_tirocinio']).'
            </div>
             <div id="panel3" class="tab-pane panel-body ">
               '.drupal_render($form['internship2_data']).drupal_render($form['comunicazione_dati_tirocinio']).'
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
function internship_3_form($form, &$form_state) {

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
                getif_goto('internship/list');
            } else {
                $internship = getInternshipById('getif_data', $form_state['id_internship']);

                $form_state_values['aim'] = $internship->note;
                $form_state_values['attachment'] = !empty($internship->attachments['progetto_formativo']->id_file_managed)?$internship->attachments['progetto_formativo']->id_file_managed:null;
                $form_state_values['positive_opinion_attachment'] = !empty($internship->attachments['parere_favorevole']->id_file_managed)?$internship->attachments['parere_favorevole']->id_file_managed:null;
            }
        }
    }
    if(empty($internship)) {
        $internship = getInternshipById('getif_data', $form_state['id_internship']);
    }

    $form['intern_data'] = array(
        '#markup' => getInternDataByInternshipObj($internship)
    );
    $form['internship1_data'] = array(
        '#markup' => getInternship1DataByInternshipObj($internship)
    );
    $form['internship2_data'] = array(
        '#markup' => getInternship2DataByInternshipObj($internship)
    );
    foreach ($internship->attachments AS $meta => $attachment) {
        if ($meta == 'dichiarazione_compatibilita_borsa_di_studio' || $meta == 'richiesta_tirocinio' || $meta == 'comunicazione_dati_tirocinio') {
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
        '#value' => t('Tirocini'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'internship'
        )
    );
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Indietro Scheda Ti.').($form_state['step']-1),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back'),
    );
    // Fieldset Promoter Tutor
    $form['fs_promoter_tutor'] = array(
        '#type' => 'container',
        '#title' => t('Tutor Soggetto Promotore').'&nbsp;'.
            $internship->promoter->name.
            (!empty($internship->promoter->parent)?'&nbsp;('.$internship->promoter->parent->name.')':''),
        '#field_suffix' => $internship->promoter->name,
        '#prefix' => '<div id="fs-promoter_tutor-div">',
        '#suffix' => '</div>',
        
    );
    $form['fs_promoter_tutor']['promoter_tutors_container'] = array(
        '#type' => 'container',
        '#weight' => 80,
        '#tree' => TRUE,
        '#prefix' => '<div id="js-ajax-promoter-tutors-wrapper">',
        '#suffix' => '</div>',
        '#weight' => 0,
    );

    // Promoter Tutor - campo di ricerca - visualizza il Cod.Fisc.
    $form['fs_promoter_tutor']['promoter_tutor']= array(
        '#type' => 'textfield',
        '#title' => t('Cerca').'<span class="form-required" title="This field is required.">*</span>',
        '#description' => t('Selezionare un tutor del soggetto promotore inserendo NOME O COGNOME O COD.FISC e cliccare su Aggiungi'),
        '#autocomplete_path' => 'tutor_autocomplete_callback/1/'.$internship->promoter->id_lperson,
        '#access' => $form_state['controller'] == 'new'?TRUE:FALSE
    );
    $form['fs_promoter_tutor']['promoter_tutor_id'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'id' => 'edit-promoter-tutor_id'   
        )
    );
    // se ci sono già tutor del Soggetto Promotore
    if (empty($form_state['field_promoter_tutors'])) {

        if (!empty($internship->promoter->tutor->id_person_lperson_prole)) {
            $form_state_values['field_promoter_tutors'][$internship->promoter->tutor->id_person_lperson_prole] = $internship->promoter->tutor->id_person_lperson_prole;
        }
    }

    if (!empty($form_state_values['field_promoter_tutors']) && empty($form_state['field_promoter_tutors'])) {
        $form_state['field_promoter_tutors'] = $form_state_values['field_promoter_tutors'];
    } else {
        $form_state['field_promoter_tutors'] = isset($form_state['field_promoter_tutors']) ? $form_state['field_promoter_tutors'] : array();
    }
    $header = array(t('Nome'), t('Cognome'), t('Cod. Fiscale'));

    $rows = array();

    // se ci sono già tutor del Soggetto ospitante
    if (!empty($form_state['field_promoter_tutors'])) {
        $rows[$internship->promoter->tutor->id_person_lperson_prole] = array(
            $internship->promoter->tutor->firstname,
            $internship->promoter->tutor->lastname,
            $internship->promoter->tutor->tax_code,
        );
    }


    $form['fs_promoter_tutor']['remove_promoter_tutor'] = array(
        '#type' => 'submit',
        '#value' => t('Rimuovi'),
        '#name' => 'edit-remove-promoter-tutor',
        '#submit' => array('remove_promoter_person_submit'),
        '#ajax' => array(
            'callback' => 'add_promoter_tutor_callback',
            'wrapper' => 'js-ajax-promoter-tutors-wrapper',

        ),
        '#weight' => -50,
    );
    $form['fs_promoter_tutor']['promoter_tutors_container']['table'] = array
    (
        '#type' => 'tableselect',
        '#header' => $header,
        '#options' => $rows,
        '#empty' => t('Selezionare un tutor del Soggetto Promotore!'),
    );

    $form['fs_promoter_tutor']['add_promoter_tutor'] = array(
        '#type' => 'submit',
        '#value' => t('Aggiungi'),
        '#submit' => array('add_promoter_tutor_submit'),
        '#ajax' => array(
            'callback' => 'add_promoter_tutor_callback',
            'wrapper' => 'js-ajax-promoter-tutors-wrapper',
        ),
        '#weight' => 100,
        '#name' => 'add_promoter_tutor',
    );

    unset($rows);
    unset($header);


    // Fieldset Host Tutor
    $form['fs_host_tutor'] = array(
        '#type' => 'container',
        '#title' => t('Tutor Soggetto Ospitante').'&nbsp;'.$internship->host->name,
        '#prefix' => '<div id="fs-host_tutor-div">',
        '#suffix' => '</div>',
    );
    $form['fs_host_tutor']['host_tutors_container'] = array(
        '#type' => 'container',
        '#weight' => 80,
        '#tree' => TRUE,
        '#prefix' => '<div id="js-ajax-host-tutors-wrapper">',
        '#suffix' => '</div>',
        '#weight' => 0,
    );
    // se ci sono già tutor del Soggetto ospitante
    if (empty($form_state['field_host_tutors'])) {
        foreach ($internship->host->tutor as $item) {
            $form_state_values['field_host_tutors'][$item->id_person_lperson_prole] = $item->id_person_lperson_prole;
        }
    }

    if (!empty($form_state_values['field_host_tutors']) && empty($form_state['field_host_tutors'])) {
        $form_state['field_host_tutors'] = $form_state_values['field_host_tutors'];
    } else {
        $form_state['field_host_tutors'] = isset($form_state['field_host_tutors']) ? $form_state['field_host_tutors'] : array();
    }
    $field_host_tutors = $form_state['field_host_tutors'];
    $header = array(t('Nome'), t('Cognome'), t('Cod. Fiscale'), t('Sede'),t('Tutor principale'));

    $rows = array();
    if (!empty($form_state['field_host_tutors'])) {
        $results = $internship->host->tutor;

        foreach($results as $key => $result) {
            $form['check_h_primary_'.$result->id_person_lperson_prole]  = array (
                '#type' => 'submit',
                '#name' => 'check_h_primary_'.$result->id_person_lperson_prole,
                '#id' => 'check_h_primary_'.$result->id_person_lperson_prole,
                '#value' => '<span class="glyphicon glyphicon-star-empty" aria-hidden="true"></span>',
                '#submit' => array('check_h_primary_submit'),
                '#ajax' => array(
                    'callback' => 'add_host_tutor_callback',
                    'wrapper' => 'js-ajax-host-tutors-wrapper',
                    'class' => array('btn','glyphicon','glyphicon-trash')
                ),
                '#attributes' => array(
                    'id_person_lperson_prole' => $result->id_person_lperson_prole
                ),
                '#limit_validation_errors' => array(array('branch_container','table'))
            );
            if ($form_state['controller'] == 'view') {
                $form['check_h_primary_'.$result->id_person_lperson_prole]['#attributes']['disabled'] = '';
            }
            if ( $result->flg_primary == 1) {
                $form['check_h_primary_'.$result->id_person_lperson_prole]['#value'] = '<span class="glyphicon glyphicon-star" aria-hidden="true"></span>';
            }
            $form['check_h_primary_'.$result->id_person_lperson_prole] = ajax_pre_render_element($form['check_h_primary_'.$result->id_person_lperson_prole]);
            $rows[$result->id_person_lperson_prole] = array(
                $result->firstname,
                $result->lastname,
                $result->tax_code,
                $result->lperson_name,
                drupal_render($form['check_h_primary_'.$result->id_person_lperson_prole]),
            );
        }
        unset($results);
        unset($result);
    }
    $form['fs_host_tutor']['remove_tutor'] = array(
        '#type' => 'submit',
        '#value' => t('Rimuovi'),
        '#submit' => array('remove_host_person_submit'),
        '#ajax' => array(
            'callback' => 'add_host_tutor_callback',
            'wrapper' => 'js-ajax-host-tutors-wrapper',
        ),
        '#weight' => -50,
    );
    $form['fs_host_tutor']['host_tutors_container']['table'] = array
    (
        '#type' => 'tableselect',
        '#header' => $header,
        '#options' => $rows,
        '#empty' => t('Selezionare almeno un tutor del Soggetto Ospitante!'),
    );


    $form['fs_host_tutor']['host_tutor']= array(
        '#type' => 'textfield',
        '#title' => t('Cerca').'<span class="form-required" title="This field is required.">*</span>',
        '#description' => t('Selezionare uno o più tutor del Soggetto Ospitante inserendo NOME O COGNOME O COD.FISC. e cliccare su Aggiungi'),
        '#autocomplete_path' => 'host_tutor_autocomplete_callback/2/'.$form_state['id_internship'],
        '#weight' => 1,
        '#access' => $form_state['controller'] == 'new'?TRUE:FALSE
    );
    $form['fs_host_tutor']['host_tutor_id'] = array(
        '#type'  => 'hidden',
        '#weight' => 2,
        '#attributes'=>array(
            'id'   => 'edit-host-tutor_id'
        )
    );
    $form['fs_host_tutor']['add_host_tutor'] = array(
        '#type' => 'submit',
        '#value' => t('Aggiungi'),
        '#submit' => array('add_host_tutor_submit'),
        '#ajax' => array(
            'callback' => 'add_host_tutor_callback',
            'wrapper' => 'js-ajax-host-tutors-wrapper',
        ),
        '#weight' => 100,
        '#name' => 'edit-add-host-tutor',

    );

    // Responsabili del progetto formativo
    $form['fs_contact_person'] = [
        '#type' => 'container',
        '#title' => t('Responsabili e Referenti Secondari del Progetto Formativo'),
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

    // se ci sono già responsabili/referenti del progetto
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

    $field_cpersons = $form_state['field_cpersons'];
    $header = array(t('Nome'), t('Cognome'), t('tax_code'), t('Sede'), t('Responsabile'));

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
        '#empty' => t('Selezionare almeno un responsabile del Progetto Formativo!'),


    );

    $form['fs_contact_person']['cperson']= array(
        '#type' => 'textfield',
        '#title' => t('Cerca').getRequiredHtml(),
        '#description' => t('Selezionare un responsabile del progetto formativo e uno o più referenti secondari inserendo NOME O COGNOME O COD.FISC e cliccare su Aggiungi'),
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
    
    // Progetto Formativo
    $form['fs_project'] = array(
        '#type' => 'container',
        '#title' => t('Progetto Formativo'),
        '#prefix' => '<div id="fs-project-div">',
        '#suffix' => '</div>',
    );
    // Obiettivi del tirocinio - campo di testo libero
    $form['fs_project']['aim']= array(
        '#type' => 'textarea',
        '#title' => t('Obiettivi del tirocinio').'<span class="form-required" title="This field is required.">*</span>',
        '#description' => t('Inserisci gli obiettivi del tirocinio'),
      
    );
    // Allegato Progetto Formativo
    $form['fs_project']['attachment'] = array(
        '#type' => 'managed_file',
        '#title' => 'Allegato Progetto Formativo',
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#description' => t('Click "Browse..." to select an attachment to upload.'),
        '#upload_validators' => array(
            'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
        ),
        '#upload_location' => 'public://attached/internship/'.$form_state['id_internship'].'/',
    );
    // Parere favorevole Progetto Formativo
    $form['fs_project']['positive_opinion_attachment'] = array(
        '#type' => 'managed_file',
        '#title' => 'Parere favorevole del Dirigente Responsabile della U.O. Ospitante IOFZ-002 E',
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
        $form['actions']['submit']['#attributes']['flg_update'] = false;
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler proseguire?")){return false;}';
        $form['actions']['update']['#access'] = false;
    } elseif ($form_state['controller'] == "view") {
        fill_data($form,$form_state_values); // da cancellare
        $form['nav']['submit'] = array(
            '#type' => 'submit',
        );
        $form['nav']['submit']['#value'] = t('Prosegui Scheda Ti.').($form_state['step']+1);
        $form['nav']['submit']['#attributes']['controller'] = $form_state['controller'];
        $form['nav']['submit']['#attributes']['step'] = $form_state['step'];
        $form['nav']['submit']['#attributes']['id_internship'] = $form_state['id_internship'];
        $form['nav']['submit']['#attributes']['flg_update'] = false;
        // Button Modifica
        // se lo stato del tirocinio è != 0 (Annullato) OR < 5 (5 - attivo OR 6 - attivo con proroga OR 7 - concluso) la funzione di modifica è disponibile:
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
    $form['fs_promoter_tutor']['promoter_tutor']['#default_value'] = !empty($form_state_values['promoter_tutor'])?_strformat($form_state_values['promoter_tutor']):'';
    $form['fs_promoter_tutor']['promoter_tutor_id']['#default_value'] = !empty($form_state_values['promoter_tutor_id'])?$form_state_values['promoter_tutor_id']:'';
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
            if (!empty($element['#validate']) && $element['#validate'] != array('go_back') && $element['#validate'] != array('download_attachment_submit')) {
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
        getif_goto('internship/view/2/'.$form_state['id_internship'],array(),302,true);
    } elseif ($form_state['controller'] == 'view-confirm') {
        getif_goto('internship/new/3/'.$form_state['id_internship'],array(),302,true);
    } elseif ($form_state['controller'] == 'view') {
        getif_goto('internship/view/2/'.$form_state['id_internship'],array(),302,true);
    }
}

/**
 * @param $form
 * @param $form_state
 */
function internship_3_form_validate($form, &$form_state) {
    $current_path = current_path();
    if (strpos($current_path, 'ajax') === false) {
        if(empty($form_state['field_promoter_tutors'])) {
            form_set_error('promoter_tutor', t('Devi inserire il Tutor del Soggetto Promoter.'));
        }
        if(empty($form_state['field_host_tutors'])) {
            form_set_error('host_tutor', t('Devi inserire almeno un Tutor del Soggetto Ospitante.'));
        }
        if(empty($form_state['values']['aim'])) {
            form_set_error('aim', t('Devi specificare gli obiettivi del Tirocinio.'));
        }
        if(empty($form_state['field_cpersons'])) {
            form_set_error('cperson', t('Devi inserire almeno un responsabile del Progetto Formativo.'));
        }
    }
}

/**
 * @param $form
 * @param $form_state
 */
function internship_3_form_submit($form, &$form_state) {
    $destination = '';
    if ($form_state['controller'] == 'new') {
        $id_internship = save($form, $form_state);
        $destination = 'internship/new/4/'.$id_internship;
        unset($_SESSION['new_internship_3']);
        drupal_set_message(t("Dati inseriti con successo"));
    } elseif ($form_state['controller'] == 'view') {
        if ($form_state['clicked_button']['#attributes']['flg_update'] == true) {
            delete_internship_step_data($form_state['id_internship'],$form_state['step']);
            $destination = 'internship/new/' . (intval($form_state['step'])) . '/' . $form_state['id_internship'];;
            drupal_set_message(t("Dati eliminati con successo"));
        } else {

            if (getInternshipStateById('getif_data', $form_state['id_internship']) > $form_state['step']) {
                $destination = 'internship/view/' . (intval($form_state['step']) + 1) . '/' . $form_state['id_internship'];
            } else {
                $destination = 'internship/new/' . (intval($form_state['step']) + 1) . '/' . $form_state['id_internship'];
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
    $id_internship = $form_state['id_internship'];
    // Obiettivo del Tirocinio
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
    // Allegato Progetto Formativo
    // se è stato allegato un file allora lo salva
    if (!empty($form_state['values']['attachment'])) {
        try {
            db_set_active('getif_data');
            $query = db_update('internship_attachment');
            $query->fields(array(
                'active' => 0,
            ))->condition(db_and()->condition('id_internship', $id_internship)->condition('meta', 'progetto_formativo', 'LIKE'))->execute();
            db_set_active();
            // watchdog
            $w_type = 'getif_' . 'internship_attachment';
            $w_message = t('Delete items with id_internship: %id AND meta: %meta');
            $w_variables = array('%id' => $id_internship, '%meta' => 'progetto_formativo');
            watchdog($w_type, $w_message, $w_variables);
        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }
        try {
            db_set_active('getif_data');
            $query = db_insert('internship_attachment');
            $id_internship_attachment = $query->fields(array(
                'id_internship' => $id_internship,
                'id_file_managed' => $form_state['values']['attachment'],
                'date_application' => date("Y-m-d H:i:s", time()),
                'meta' => 'progetto_formativo',
                'date_upd' => date("Y-m-d H:i:s", time()),
            ))->execute();
            db_set_active();
            // watchdog
            $w_type = 'getif' . 'internship_attachment';
            $w_message = t('Insert %id');
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

    // Allegato Parere Favorevole
    // se è stato allegato un file allora lo salva
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

    // modifica stato tirocinio
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

    global $user;
    // utente che ha modificato la scheda tirocinio
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


/* Occorre verificare il numero di dipendenti per i tirocini extracurriculari */
/**
 * @param $internship
 * @param $id_person_lperson_prole
 * @return mixed
 */
function internship_host_tutor_verification(&$internship, $id_person_lperson_prole) {
    /* Nel controllo si considerano anche i tirocini in stato di pratica */
    db_set_active('getif_data');
    $query = db_select('internship_host_tutor', 't1');
    $query->innerJoin('person_lperson_prole', 't2', 't1.id_person_lperson_prole = t2.id_person_lperson_prole');
    $query->innerJoin('internship', 't3', 't1.id_internship = t3.id_internship');
    $query->where(
        't1.id_internship != '.$internship->id_internship.' AND t2.id_person_lperson_prole ='.$id_person_lperson_prole.'
        AND '.$internship->date_start.'  AND t3.date_end > \''.$internship->date_start.'\'
        AND t3.date_start < \''.$internship->date_end.'\' AND t1.active = 1 AND t2.active = 1 AND t3.active = 1'
    );
    $result = $query->fields('t1',array('id_internship'))->countQuery()->execute()->fetchField();
    db_set_active();
    return $result;
}

/* Funzioni per aggiunta/rimozione Tutor del Soggetto Promoter */
/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_promoter_tutor_callback($form, &$form_state) {
    return $form['fs_promoter_tutor']['promoter_tutors_container'];
}

/**
 * @param $form
 * @param $form_state
 */
function add_promoter_tutor_submit($form, &$form_state) {
    $items = $form_state['field_promoter_tutors'];
    $id_person_lperson_prole = $form_state['values']['promoter_tutor_id'];
    if (!empty($id_person_lperson_prole) && !in_array($id_person_lperson_prole, $items) && count($items) == 0) {
        $form_state['field_promoter_tutors'][$id_person_lperson_prole] = $id_person_lperson_prole;
        $fields = array(
            'id_internship' => $form_state['id_internship'],
            'id_person_lperson_prole' => $id_person_lperson_prole
        );
        $key = array(
            'id_internship' => $form_state['id_internship'],
            'id_person_lperson_prole' => $id_person_lperson_prole,
            'active' => 1
        );
        db_set_active('getif_data');
        try {
            $query = db_merge('internship_promoter_tutor');
            $query->key($key)->fields($fields)->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }
        db_set_active();

        $form_state['rebuild'] = TRUE;
        drupal_set_message('Tutor inserito con successo.', 'status');
        return;
    }
    $form_state['rebuild'] = TRUE;
    drupal_set_message('Tutor non selezionato o gi&agrave; inserito.', 'warning');

}

/**
 * @param $form
 * @param $form_state
 */
function remove_promoter_person_submit($form, &$form_state) {
    $selected = ($form_state['values']['promoter_tutors_container']['table']);
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
                $query = db_merge('internship_promoter_tutor');
                $id_intership_lperson= $query -> key($cond)->fields($fields)->execute();
            } catch (Exception $ex) {
                drupal_set_message('Errore: '.$ex,'error');
            }
            db_set_active();
            unset($form_state['field_promoter_tutors'][$key]);
        }
    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}



/* Funzioni per aggiunta/rimozione Tutor del Soggetto Ospitante */
/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_host_tutor_callback($form, &$form_state) {
    return $form['fs_host_tutor']['host_tutors_container'];
}

/**
 * @param $form
 * @param $form_state
 */
function add_host_tutor_submit($form, &$form_state) {
    $items = $form_state['field_host_tutors'];
    $id_person_lperson_prole = $form_state['values']['host_tutor_id'];
    if (!empty($id_person_lperson_prole) && !in_array($id_person_lperson_prole, $items)) {
        $form_state['field_host_tutors'][$id_person_lperson_prole] = $id_person_lperson_prole;
        // verifica tutor non abbia più di 5 tirocinanti assegnati nello stesso periodo
        $internship = getInternshipById('getif_data',$form_state['id_internship']);
        $num_internship = internship_host_tutor_verification($internship, $id_person_lperson_prole);
        if ($num_internship > 5) {
            drupal_set_message('Il tutor non può gestire più di 5 Tirocini curriculari', 'error');
            return;
        } else {
            // insert to DB

            $fields = array(
                'id_internship' => $form_state['id_internship'],
                'id_person_lperson_prole' => $id_person_lperson_prole,
                'flg_primary' => (count($form_state['field_host_tutors']) == 1) ? 1 : 0
            );

            $key = array(
                'id_internship' => $form_state['id_internship'],
                'id_person_lperson_prole' => $id_person_lperson_prole,
                'active' => 1
            );
            db_set_active('getif_data');
            try {
                $query = db_merge('internship_host_tutor');
                $query->key($key)->fields($fields)->execute();
            } catch (Exception $ex) {
                drupal_set_message('Errore: ' . $ex, 'error');
            }
            db_set_active();
        }
        $form_state['rebuild'] = TRUE;
        drupal_set_message('Tutor inserito con successo.', 'status');
        return;
    }
    $form_state['rebuild'] = TRUE;
    drupal_set_message('Tutor non selezionato o gi&agrave; inserito.', 'warning');

}

/**
 * @param $form
 * @param $form_state
 */
function remove_host_person_submit($form, &$form_state) {
    $selected = ($form_state['values']['host_tutors_container']['table']);
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
                $query = db_merge('internship_host_tutor');
                $id_intership_lperson= $query -> key($cond)->fields($fields)->execute();
            } catch (Exception $ex) {
                drupal_set_message('Errore: '.$ex,'error');
            }
            db_set_active();
            unset($form_state['field_host_tutors'][$key]);
        }
    }
    // se rimane un solo elemento questo va reso primario
    if (count($form_state['field_host_tutors']) == 1) {
        foreach ($form_state['field_host_tutors'] as $key => $item) {
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
                $query = db_merge('internship_host_tutor');
                $id_intership_lperson = $query -> key($cond)->fields($fields)->execute();
            } catch (Exception $ex) {
                
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
function check_h_primary_submit($form, &$form_state) {

    $fields = array(
        'flg_primary' => 0,
    );
    $where = 'id_internship = '.$form_state['id_internship'].' and active = 1';
    try {
        db_set_active('getif_data');
        $query = db_update('internship_host_tutor');
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
        $query = db_update('internship_host_tutor');
        $query ->fields($fields)->where($where)->execute();
        db_set_active();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
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

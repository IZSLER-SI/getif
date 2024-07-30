<?php

/**
 * Theme sezione nuovo tirocinio Scheda Ti.2
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_internship_2_form($variables){
    $form = $variables['form'];
    $header_content = array();
    $output = '';
    if(!empty(arg(2))) {
        $output .= get_internship_new_header(arg(2));
    }
    if(!empty($form['intern_data'])) {
        $output .= '<div class="panel panel-default">';
        $output .= '
        <ul class="nav nav-tabs" style = "background-color: #f5f5f5;">
            <li class="active"><a href="#panel1" data-toggle="tab">Tirocinante</a></li>
            <li><a href="#panel2" data-toggle="tab">Scheda Ti.1</a></li>
        </ul>
        <div class="tab-content">
            <div id="panel1" class="tab-pane active panel-body">
               ' . drupal_render($form['intern_data']) . drupal_render($form['dichiarazione_compatibilita_borsa_di_studio']) . '
            </div>
            <div id="panel2" class="tab-pane panel-body">
               ' . drupal_render($form['internship1_data']) . drupal_render($form['richiesta_tirocinio']) . '
            </div>
        </div>';
        $output .= '</div>';
    }
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
function internship_2_form($form, &$form_state) {
    // get arguments
    $form_state['controller'] = $form_state["build_info"]["args"][0];
    if(isset($form_state["build_info"]["args"][1])) {
        $form_state['step'] = $form_state["build_info"]["args"][1];
    }
    $form_state['id_internship'] = !empty($form_state["build_info"]["args"][2])?$form_state["build_info"]["args"][2]:'';
    $form_state_values = session_get("new_internship_2");
    if ($form_state['controller'] == 'view') {
        if (!empty(session_get('new_internship_2'))) {
            $form_state['controller'] .= '-confirm';
            $form_state_values = session_get("new_internship_2");
        } else {
            if(empty($form_state['id_internship'])) {
                getif_goto('internship/list');
            } else {
                $internship = getInternshipById('getif_data', $form_state['id_internship']);
                $form_state_values = array(
                    'location' => $internship->host->id_lperson,
                    'attachment' => !empty($internship->attachments['comunicazione_dati_tirocinio']->id_file_managed)?array('fid' => $internship->attachments['comunicazione_dati_tirocinio']->id_file_managed):''
                );
                if($internship->internship_type->flg_extra_curricular == 1) { // solo per gli extracurriculari
                    $form_state_values = array(
                        'm_budget' => $internship->budget->m_amount,
                        'total_amount' => $internship->budget->a_amount,
                    );
                }
            }
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
    $required = TRUE;
    $internship = getInternshipById('getif_data',$form_state['id_internship']);
    internship_location_verification($internship,2);

    if(!check_intern_fulfilled($internship->person->id_internship_person)) {
        $form['fs_intern_data'] = array(
            '#type' => 'container',
        );
        $form['fs_intern_data']['markup'] = array(
            '#markup' => '<div class="alert alert-block alert-dismissible alert-danger messages error">Attenzione il profilo del tirocinante non è completo. Per proseguire clicca su completa.</div>',
        );
        $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Completa'),
            '#submit' => array('goto_intern_form'),
            '#limit_validation_errors' => array(),
        );
        $form_state['id_internship_person'] = $internship->person->id_internship_person;
    } else {
        budget_verification($form,$form_state);

        $form['intern_data'] = array(
            '#markup' => getInternDataByInternshipObj($internship)
        );
        $form['internship1_data'] = array(
            '#markup' => getInternship1DataByInternshipObj($internship)
        );
        foreach ($internship->attachments AS $meta => $attachment) {
            if ($meta == 'dichiarazione_compatibilita_borsa_di_studio' || $meta == 'richiesta_tirocinio') {
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


        // Strutture secondarie
        $form['fs_location'] = array(
            '#type' => 'container',
            '#title' => t('Strutture che ospitano il tirocinio'),
            '#prefix' => '<div id="fs-location-div">',
            '#suffix' => '</div>',
        );
        $form['fs_location']['field_container'] = [
            '#type' => 'container',
            '#weight' => 0,
            '#tree' => TRUE,
            '#prefix' => '<div id="js-ajax-location-wrapper">',
            '#suffix' => '</div>',
        ];
        if (empty($form_state['field_locations'])) {
            foreach ($internship->lperson as $item) {
                $form_state_values['field_locations'][$item->id_lperson] = $item->id_lperson;
            }
        }
        if (!empty($form_state_values) && empty($form_state['field_locations'])) {
            $form_state['field_locations'] = $form_state_values['field_locations'];
        } else {
            $form_state['field_locations'] = isset($form_state['field_locations']) ? $form_state['field_locations'] : array();
        }
        $field_count1 = $form_state['field_locations'];
        $header = array('ID', 'Ragione Sociale', 'Indirizzo', 'N. Impiegati', 'Primaria', 'Laboratori/Aree');
        if (!empty($field_count1)) {
            $results = getAllBranch($internship->host->id_lperson, $field_count1);

        } else {
            $results = array();
        }
        $rows = array();
        foreach ($results as $key => $result) {
            $form['check_branch_primary_'.$result->id_lperson]  = array (
                '#type' => 'submit',
                '#name' => 'check_branch_primary_'.$result->id_lperson,
                '#id' => 'check_branch_primary_'.$result->id_lperson,
                '#value' => '<span class="glyphicon glyphicon-star-empty" aria-hidden="true"></span>',
                '#submit' => array('check_branch_primary_submit'),
                '#ajax' => array(
                    'callback' => 'add_location_callback',
                    'wrapper' => 'js-ajax-location-wrapper',
                ),

                '#attributes' => array(
                    'id_lperson' => $result->id_lperson,

                ),
                '#limit_validation_errors' => array(array('branch_container','table'))
            );
            if ($form_state['controller'] == 'view') {
                $form['check_branch_primary_'.$result->id_lperson]['#attributes']['disabled'] = '';
            }
            if ( $result->flg_primary == 1) {
                $form['check_branch_primary_'.$result->id_lperson]['#value'] = '<span class="glyphicon glyphicon-star" aria-hidden="true"></span>';
            }
            $form['check_branch_primary_'.$result->id_lperson] = ajax_pre_render_element($form['check_branch_primary_'.$result->id_lperson]);


            $rows[$result->id_lperson] = array(
                $result->id_lperson,
                $result->name,
                $result->address,
                $result->num_employers,
                drupal_render($form['check_branch_primary_'.$result->id_lperson]),
            );

            // Prendi i Laboratori associati
            $lperson_location_areas = $internship->lperson_location_area;
            $result->lperson_location_area = '<ul>';

            foreach ($lperson_location_areas as $lperson_location_area) {

                if ($lperson_location_area->id_lperson_parent == $result->id_lperson) {
                    // Button Rimuovi Laboratorio
                    //die($lperson_location_area->id_internship_lperson_location_area);
                    $form['remove_lperson_location_area_' . $lperson_location_area->id_internship_lperson_location_area] = array(
                        '#type' => 'submit',
                        '#name' => 'remove_lperson_location_area_' . $lperson_location_area->id_internship_lperson_location_area,
                        '#value' => '',
                        '#submit' => array('remove_lperson_location_area_submit'),
                        '#id' => 'edit-remove-lperson-location-area-' . $lperson_location_area->id_internship_lperson_location_area,
                        '#attributes' => array(
                            'id' => 'edit-remove-lperson-location-area-' . $lperson_location_area->id_internship_lperson_location_area,
                            'id_internship_lperson_location_area' => $lperson_location_area->id_internship_lperson_location_area,
                            'class' => array('glyphicon glyphicon-trash')
                        ),
                        '#ajax' => array(
                            'callback' => 'add_location_callback',
                            'wrapper' => 'js-ajax-location-wrapper',
                        ),
                        '#limit_validation_errors' => array(array('field_container')),
                        '#access' => $form_state['controller'] == 'new' ? TRUE : FALSE
                    );
                    $form['remove_lperson_location_area_' . $lperson_location_area->id_internship_lperson_location_area] = ajax_pre_render_element($form['remove_lperson_location_area_' . $lperson_location_area->id_internship_lperson_location_area]);

                    $result->lperson_location_area .=
                        '<li>' . drupal_render($form['remove_lperson_location_area_' . $lperson_location_area->id_internship_lperson_location_area]) .
                        ' ' . $lperson_location_area->name . '</li>';
                }
            }
            $result->lperson_location_area .= '</ul>';

            // Cerca Laboratorio
            $form['lperson_location_area_' . $result->id_lperson] = array(
                '#type' => 'select',
                '#name' => 'lperson_location_area_' . $result->id_lperson,
                '#options' => getLocationAreaByLPId('getif_data', $result->id_lperson),
                '#attributes' => array(
                    'id' => 'edit-lperson-location-area-' . $result->id_lperson,
                ),
                '#access' => $form_state['controller'] == 'new' ? TRUE : FALSE
            );
            // Button Aggiungi Laboratorio
            $form['add_lperson_location_area_' . $result->id_lperson] = array(
                '#type' => 'submit',
                '#name' => 'add_lperson_location_area_' . $result->id_lperson,
                '#value' => 'Aggiungi',
                '#submit' => array('add_lperson_location_area_submit'),
                '#id' => 'edit-add-lperson-location-area-' . $result->id_lperson,
                '#attributes' => array(
                    'id' => 'edit-add-lperson-location-area-' . $result->id_lperson,
                    'id_lperson' => $result->id_lperson,
                ),
                '#ajax' => array(
                    'callback' => 'add_location_callback',
                    'wrapper' => 'js-ajax-location-wrapper',
                ),
                '#limit_validation_errors' => array(array('field_container'), array('lperson_location_area_' . $result->id_lperson)),
                '#access' => $form_state['controller'] == 'new' ? TRUE : FALSE
            );
            $form['add_lperson_location_area_' . $result->id_lperson] = ajax_pre_render_element($form['add_lperson_location_area_' . $result->id_lperson]);

            $rows[$result->id_lperson][] = $result->lperson_location_area . drupal_render($form['lperson_location_area_' . $result->id_lperson]) . drupal_render($form['add_lperson_location_area_' . $result->id_lperson]);
        }
        $form['fs_location']['field_container']['remove_name'] = [
            '#type' => 'submit',
            '#value' => t('Rimuovi'),
            '#submit' => ['remove_location_submit'],
            '#ajax' => [
                'callback' => 'add_location_callback',
                'wrapper' => 'js-ajax-location-wrapper',
            ],
            '#weight' => -50,
            '#name' => 'remove_location',
            '#limit_validation_errors' => array(array('field_container')),
            '#access' => $form_state['controller'] == 'new' ? TRUE : FALSE
        ];


        $form['fs_location']['field_container']['table'] = array
        (
            '#type' => 'tableselect',
            '#header' => $header,
            '#options' => $rows,
            '#empty' => t('Selezionare almeno una struttura!'),

        );


        $form['fs_location']['location'] = array(
            '#type' => 'textfield',
            '#title' => t('Cerca'),
            //'#description' => t('Aggiungi Struttura Secondaria'),
            '#autocomplete_path' => 'branch_autocomplete_callback/' . $internship->host->id_lperson,
            '#weight' => 70,
            '#access' => $form_state['controller'] == 'new' ? TRUE : FALSE
        );

        $form['fs_location']['location_id'] = array(
            '#type' => 'hidden',
            '#attributes' => array(
                'id' => 'edit-location_id'

            )
        );

        $form['fs_location']['add_name'] = array(
            '#type' => 'submit',
            '#value' => t('Aggiungi'),
            '#submit' => array('add_location_submit'),
            '#ajax' => array(
                'callback' => 'add_location_callback',
                'wrapper' => 'js-ajax-location-wrapper',
            ),
            '#weight' => 80,
            '#limit_validation_errors' => array(array('field_container'), array('location_id')),
            '#access' => $form_state['controller'] == 'new' ? TRUE : FALSE
        );
        // solo per extracurriculari
        if ($internship->internship_type->flg_extra_curricular == 1) {
            $form['fs_budget'] = array(
                '#type' => 'container',
                '#title' => t('Budget per Tirocini Extra-Curricolari'),
                '#prefix' => '<div id="fs-budget-div">',
                '#suffix' => '</div>',
            );
            $l_m_duration = round(getLMDuration($internship->date_start, $internship->date_end),2);
            $form['fs_budget']['l_m_duration'] = array(
                '#type' => 'textfield',
                '#title' => t('Durata prevista'),
                '#field_suffix' => '<div class="field_suffix">mesi</div>',
                '#description' => t('Durata prevista in mesi'),
                '#default_value' => round($l_m_duration,2),
                '#attributes' => array(
                    'type' => 'number',
                    'readonly' => 'readonly',
                    'class' => array('numeric_field'),
                    'maxlength' => 4
                ),
                '#required' => $required,
            );
            $form['fs_budget']['m_budget'] = array(
                '#type' => 'textfield',
                '#title' => t('Indennità mensile'),
                '#field_prefix' => '<div class = "input-group"><span class="input-group-addon">&euro;</span>',
                '#field_suffix' => '</div>',
                '#description' => t('Indennità mensile in &euro;'),
                '#attributes' => array(
                    ' type' => 'number',
                    'step' => '0.01',
                    'min' => 0,
                    'max' => 1000000.00,
                    'lang' => 'it',
                    'placeholder'=>"0,00",
                    'maxlength' => 9,
                    ' data-number-to-fixed' => 2,
                    ' data-number-stepfactor' => 100,
                    'class' => array('currency','form-control'),
                    'check_for_draft_save' => 'no',
                ),
                '#ajax' => array(
                    'callback' => 'budget_ax_callback',
                    'wrapper' => 'total_amount_div',
                ),
                '#required' => $required,
            );
            $form['fs_budget']['total_amount_div'] = array('#prefix' => '<div id="total_amount_div">', '#suffix' => '</div>');
            $total_amount = empty($form_state['values']['m_budget']) ? (empty($form_state_values['m_budget']) ? 0 : $form_state_values['m_budget']) : $form_state['values']['m_budget'];

            //if ($total_amount > 0) {
                $form['fs_budget']['total_amount_div']['total_amount'] = array(
                    '#type' => 'textfield',
                    '#title' => t('Importo complessivo previsto'),
                    '#field_prefix' => '<div class = "input-group"><span class="input-group-addon">&euro;</span>',
                    '#field_suffix' => '</div>',
                    '#description' => t('Importo complessivo previsto in &euro;'),
                    '#default_value' => str_replace('€ ', '',money_format('%.2n', round($total_amount * $l_m_duration,2))),
                    '#attributes' => array(
                        'style' => 'padding-right: 30px;',
                        'class' => array('currency','form-control'),
                        'check_for_draft_save' => 'no',
                        'disabled' => ''
                    ),
                );
                $form['fs_budget']['total_amount_div']['total_amount']  = ajax_pre_render_element($form['fs_budget']['total_amount_div']['total_amount'] );

            //}

        }
        // Allegato Comunicazione dei dati del Tirocinio (Allegato "A") IOFZ-002 B
        $form['fs_attachment'] = array(
            '#type' => 'container',
            '#title' => t('Comunicazione dei dati del Tirocinio (Allegato "A") IOFZ-002 B'),
        );
        $form['fs_attachment']['attachment'] = array(
            '#type' => 'managed_file',
            '#title' => 'Comunicazione dei dati del Tirocinio',
            '#title_display' => 'invisible',
            '#progress_message' => t('Please wait...'),
            '#progress_indicator' => 'bar',
            '#description' => t('Click "Browse..." to select an attachment to upload.'),
            '#upload_validators' => array(
                'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
            ),
            '#upload_location' => 'public://attached/internship/' . $form_state['id_internship'] . '/'
        );
        // Submit Button
        $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#weight' => 12
        );
        // Button Modifica Dati Tirocinante
        $form['actions']['update_intern_submit'] = array(
            '#type' => 'submit',
            '#submit' => array('update_intern_submit'),
            '#weight' => 10
        );
        $form['actions']['update_intern_submit']['#value'] = t('Modifica Dati Tirocinante');
        $form['actions']['update_intern_submit']['#attributes']['controller'] = $form_state['controller'];
        $form['actions']['update_intern_submit']['#attributes']['step'] = $form_state['step'];
        $form['actions']['update_intern_submit']['#attributes']['id_internship'] = $form_state['id_internship'];
        $form['actions']['update_intern_submit']['#attributes']['id_internship_person'] = $internship->person->id_internship_person;
        $form['actions']['update_intern_submit']['#limit_validation_errors'] = array();
        if ($form_state['controller'] == "new") {

            if (!empty($_SESSION['new_internship_2'])) {
                fill_data($form, $_SESSION['new_internship_2'], $form_state);
                unset($_SESSION['new_internship_2']);
            }
            $form['actions']['submit']['#value'] = t('Salva');
            $form['actions']['submit']['#attributes']['controller'] = $form_state['controller'];
            $form['actions']['submit']['#attributes']['step'] = $form_state['step'];
            $form['actions']['submit']['#attributes']['id_internship'] = $form_state['id_internship'];
            $form['actions']['submit']['#attributes']['flg_update'] = false;
            $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler proseguire?")){return false;}';
            $form['actions']['update']['#access'] = false;
            $form['actions']['update_intern_submit']['#attributes']['flg_update'] = false;
        } elseif ($form_state['controller'] == "view") {
            fill_data($form, $form_state_values, $form_state);
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
        } elseif ($form_state['controller'] == 'view-confirm') {
            fill_data($form, $_SESSION['new_internship_2'], $form_state);
            $form['actions']['submit']['#value'] = '<span class="icon glyphicon glyphicon-floppy-disk" aria-hidden="true"></span>&nbsp;' . t('Conferma salvataggio');
            $form['actions']['submit']['#attributes']['controller'] = $form_state['controller'];
            $form['actions']['submit']['#attributes']['step'] = $form_state['step'];
            $form['actions']['submit']['#attributes']['id_internship'] = $form_state['id_internship'];
            $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler proseguire? I dati non potranno più essere modificati.")){return false;}';
            disable_form_editing($form);
        }

    }
    return $form;
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
 * @param $form_state_values
 */
function fill_data(&$form, $form_state_values) {
    //$form['fs_location']['location']['#default_value'] = !empty($form_state_values['location'])?$form_state_values['location']."":'';
    $form['fs_budget']['m_budget']['#default_value'] = !empty($form_state_values['m_budget'])?$form_state_values['m_budget']:'';
    //$form['fs_budget']['total_amount_div']['total_amount']['#default_value'] = !empty($form_state_values['total_amount'])?$form_state_values['total_amount']:'';
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
        getif_goto('internship/view/1/'.$form_state['id_internship'],array(),302,true);
    } elseif ($form_state['controller'] == 'view-confirm') {
        getif_goto('internship/new/2/'.$form_state['id_internship'],array(),302,true);
    } elseif ($form_state['controller'] == 'view') {
        getif_goto('internship/view/1/'.$form_state['id_internship'],array(),302,true);
    }
}

/**
 * Verifica la presenza di un budget annuale nell'anno di inizio del Tirocinio
 * @param $form
 * @param $form_state
 */
function budget_verification($form, &$form_state) {
    $internship = getInternshipById('getif_data',$form_state['id_internship']);
    if($internship->internship_type->flg_extra_curricular == 1) { // se è extracurriculare
        db_set_active('getif_data');
        $query = db_select('budget', 'b');
        $query->fields('b');
        $query->condition('b.id_lperson', $internship->host->id_lperson);
        $query->condition('b.year', date('Y', strtotime($internship->date_start)));
        $query->condition('b.active', 1);
        $budget = $query->execute()->fetchObject();
        db_set_active();
        if (!empty($budget)) {
            $total_amount = doubleval($budget->a_amount) + doubleval($budget->a_extra_amount);
            db_set_active('getif_data');
            $query = db_select('internship_budget', 't1');
            $query->innerJoin('internship', 't2', 't2.id_internship = t1.id_internship');
            $query->where('YEAR(t2.date_start) = ' . $budget->year . ' AND t1.active = 1 AND t2.active = 1');
            $query->fields('t1');
            $results = $query->execute()->fetchAll();
            db_set_active();
            $total_available_amount = $total_amount;
            foreach ($results AS $result) {
                $total_available_amount -= doubleval($result->a_amount);
            }
            if (!empty($form_state['values']['total_amount']) && $total_available_amount < $form_state['values']['total_amount']) {
                form_set_error('total_amount', t('Il budget impostato supera il budget annuale ancora disponibile di @b1 &euro;',
                    array('@b1' => money_format('%.2n', $total_available_amount))));
            }
        } else {
            form_set_error('total_amount', t('Devi prima inserire un budget annuale per tirocini extracurricolari'));
        }
    }

}


/**
 * @param $form
 * @param $form_state
 */
function internship_2_form_validate($form, &$form_state) {
    if(empty($form_state['field_locations'])) {
        form_set_error('location', t('Devi inserire almeno una Struttura ospitante.'));
    }
}

/**
 * @param $form
 * @param $form_state
 */
function update_intern_submit($form, &$form_state) {
    $destination = 'intern/edit/' . $form_state['clicked_button']['#attributes']['id_internship_person'];
    session_set('id_internship', $form_state['id_internship']);
    getif_goto($destination,array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function goto_intern_form($form, &$form_state) {
    $destination = 'intern/edit/'.$form_state['id_internship_person'];
    session_set('id_internship',$form_state['id_internship']);
    getif_goto($destination,array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function internship_2_form_submit($form, &$form_state) {
    $destination = '';
    if ($form_state['controller'] == 'new') {
        if (!empty($form_state['id_internship_person'])) {
            $destination = 'intern/edit/'.$form_state['id_internship_person'];
            session_set('id_internship',$form_state['id_internship']);
        } else {
            $id_internship = save($form, $form_state);
            $destination = 'internship/new/3/'.$id_internship;
            unset($_SESSION['new_internship_2']);
            drupal_set_message(t("Dati inseriti con successo"));
        }
    } elseif ($form_state['controller'] == 'view') {
        if (!empty($form_state['clicked_button']['#attributes']['id_internship_person'])) {
            $destination = 'intern/edit/' . $form_state['clicked_button']['#attributes']['id_internship_person'];
            session_set('id_internship', $form_state['id_internship']);
        } elseif ($form_state['clicked_button']['#attributes']['flg_update'] == true) {
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
    getif_goto($destination,array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 * @throws Exception
 */
function save($form, &$form_state) {
    global $user;
    $id_internship = $form_state['id_internship'];
    $internship = getInternshipById('getif_data', $id_internship);
    // solo per gli extracurriculari
    if($internship->internship_type->flg_extra_curricular == 1) {
        db_set_active('getif_data');
        $query = db_insert('internship_budget');
        $id_internship_budget = $query -> fields(array(
            'id_internship' => $id_internship,
            'a_amount' => round(floatval($form_state['values']['m_budget'])*floatvaldec($form_state['values']['l_m_duration'],','),2),
            'm_amount' => round(floatval($form_state['values']['m_budget']),2),
            'i_m_duration' => round(floatvaldec($form_state['values']['l_m_duration']),2)
        ))->execute();
        db_set_active();
        // watchdog
        $w_type = 'getif_'.'internship_budget';
        $w_message = t('Insert item %id');
        $w_variables = array('%id'=>$id_internship_budget);
        watchdog($w_type, $w_message, $w_variables);
    }
    // file
    // se è stato allegato un file allora lo salva
    if (!empty($form_state['values']['attachment'])) {
        try {
            db_set_active('getif_data');
            $query = db_update('internship_attachment');
            $query -> fields(array(
                'active' => 0,
            ))->condition(db_and()->condition('id_internship',$id_internship)->condition('meta','comunicazione_dati_tirocinio','LIKE'))->execute();
            db_set_active();
            // watchdog
            $w_type = 'getif_'.'internship_attachment';
            $w_message = t('Delete items with id_internship: %id AND meta: %meta');
            $w_variables = array('%id'=>$id_internship,'%meta'=>'comunicazione_dati_tirocinio');
            watchdog($w_type, $w_message, $w_variables);
            db_set_active('getif_data');
            $query = db_insert('internship_attachment');
            $id_internship_attachment= $query -> fields(array(
                'id_internship' => $id_internship,
                'id_file_managed' => $form_state['values']['attachment'],
                'date_application' => date("Y-m-d H:i:s", time()),
                'meta' => 'comunicazione_dati_tirocinio',
                'date_upd' => date("Y-m-d H:i:s", time()),
            ))->execute();
            db_set_active();
            // watchdog
            $w_type = 'getif_'.'internship_attachment';
            $w_message = t('Insert item %id');
            $w_variables = array('%id'=>$id_internship_attachment);
            watchdog($w_type, $w_message, $w_variables);
            // cambio lo stato del file in PERMANENTE
            $fid = $form_state['values']['attachment'];
            $file = file_load($fid);
            $file->status = FILE_STATUS_PERMANENT;
            file_save($file);
            // Aggiungo un record in file_usage
            $file = new stdClass();
            $file->fid = $fid;
            file_usage_add($file, 'getif','internship_attachment',$id_internship_attachment);
        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }
    }
    // modifica stato tirocinio
    $fields = array(
        'state' => 2,
        'active' => 1,
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    // modifica stato
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

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function budget_ax_callback($form, &$form_state) {
    return $form['fs_budget']['total_amount_div'];
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_location_callback($form, &$form_state) {
    return $form['fs_location']['field_container'];
}


/**
 * Funzione che verifica il numero di dipendenti presenti nell’Unità Operativa per i tirocini extracurriculari:
 * i. Le Unità Operative con un numero di dipendenti compreso tra 1 e 5, non possono ospitare più di 1 tirocinante.
 * ii. Le Unità Operative con un numero di dipendenti compreso tra 6 e 20, possono ospitare al massimo 2 tirocinanti.
 * iii. Le Unità Operative con più di 20 dipendenti possono ospitare un numero massimo di partecipanti non superiore al 10% dei dipendenti.
 * @param $internship
 * @param $id_lperson
 * @return mixed
 */
function internship_location_verification(&$internship, $id_lperson) {
    /* Nel controllo si considerano tutti i tirocini ad esclusione di quelli interrotti (0) o conclusi (7) */
    db_set_active('getif_data');
    $query = db_select('internship_lperson', 't1');
    $query->innerJoin('lperson', 't2', 't1.id_lperson = t2.id_lperson');
    $query->innerJoin('internship', 't3', 't1.id_internship = t3.id_internship');
    $query->innerJoin('internship_state', 't5', 't3.id_internship = t5.id_internship');
    $query->innerJoin('lib_internship_type', 't4', 't3.id_internship_type = t4.id_internship_type');
    $query->where(
        't1.id_internship != '.$internship->id_internship.' AND t2.id_lperson ='.$id_lperson.'
        AND '.$internship->date_start.'  AND t3.date_end > \''.$internship->date_start.'\'
        AND t5.state NOT IN (0,7)
        AND t3.date_start < \''.$internship->date_end.'\' AND t4.flg_extra_curricular = 1 AND t1.active = 1 AND t2.active = 1 AND t3.active = 1'
    );
    $result = $query->fields('t1',array('id_internship'))->countQuery()->execute()->fetchField();
    db_set_active();
    return $result;
}


/**
 * @param $form
 * @param $form_state
 */
function add_location_submit($form, &$form_state) {

    $items = !empty($form_state['field_locations'])?$form_state['field_locations']:array();

    $id_location = $form_state['values']['location_id'];
    if (!empty($id_location)) {
        if (!in_array($id_location, $items)) {
            // verifica il numero di di dipendenti per i tirocini extracurriculari
            $internship = getInternshipById('getif_data',$form_state['id_internship']);
            if ($internship->internship_type->flg_extra_curricular == 1) {
                $num_internship = internship_location_verification($internship, $id_location);
                $lperson = getRecordById('lperson','getif_data',$id_location);
                if ($lperson->num_employers >= 1   && $lperson->num_employers <= 5  &&  $num_internship >= 1) {
                    drupal_set_message(_strformat($lperson->name).' non può ospitare più di 1 Tirocinio extracurricolare' ,'error');
                    return;
                } elseif($lperson->num_employers > 5 && $lperson->num_employers <= 20 && $num_internship >= 2) {
                    drupal_set_message(_strformat($lperson->name).' non può ospitare più di 2 Tirocini extracurricolari' ,'error');
                    return;
                } elseif($lperson->num_employers > 20 && floatval($num_internship) >= floor(0.1*(floatval($lperson->num_employers)))) {
                    drupal_set_message(_strformat($lperson->name).' non può ospitare più di '.floor(0.1*(floatval($lperson->num_employers))).' Tirocini extracurricolari','error');
                    return;
                }
            }
            $form_state['field_locations'][$id_location] = $id_location;
            $form_state['rebuild'] = TRUE;
            // insert to DB
            $fields = array(
                'id_internship' => $form_state['id_internship'],
                'id_lperson' => $id_location,
                'flg_primary' => empty($form['fs_location']['field_container']['table']['#options']) ? 1 : 0,
                'active' => 1
            );
            $key = array(
                'id_internship' => $form_state['id_internship'],
                'id_lperson' => $id_location,

            );
            db_set_active('getif_data');
            try {
                $query = db_merge('internship_lperson');
                $id_intership_lperson = $query->key($key)->fields($fields)->execute();
            } catch (Exception $ex) {
                drupal_set_message('Errore: ' . $ex, 'error');
            }
            db_set_active();
        } else {
            drupal_set_message('Struttura già inserita.', 'warning');
        }
    } else {
        drupal_set_message('Nessuna struttura selezionata.', 'error');
    }

    //drupal_get_messag es();
}

/**
 * @param $form
 * @param $form_state
 */
function remove_location_submit($form, &$form_state) {
    $selected = ($form_state['values']['field_container']['table']);
    $flg_delete_all = false;
    foreach ($selected as $key => $item) {
        // se viene cancellata la struttura primaria, devono essere cancellate tutte le strutture
        if ($item != 0 && $form['fs_location']['field_container']['table']['#options'][$key][4] == 'Primaria') {
            $flg_delete_all = true;
            break;
        }
    }
    foreach ($selected as $key => $item) {
        if ($item != 0 || $flg_delete_all == true) {
            $fields = array(
                'id_internship' => $form_state['id_internship'],
                'id_lperson' => $key,
                'flg_primary' => 0,
                'active' => 0
            );
            $cond = array(
                'id_internship' => $form_state['id_internship'],
                'id_lperson' => $key,
            );
            try {
                // Rimuovi Struttura
                db_set_active('getif_data');
                $query = db_merge('internship_lperson');
                $query->key($cond)->fields($fields)->execute();
                db_set_active();
                // Rimuovi laboratori della struttura
                $internship = getInternshipById('getif_data',$form_state['id_internship']);
                $lperson_location_areas = $internship->lperson_location_area;
                foreach($lperson_location_areas as $lperson_location_area) {
                    if((int)$lperson_location_area->id_lperson == (int)$key) {
                        db_set_active('getif_data');
                        $fields = array(
                            'active' => 2
                        );
                        try {
                            $query = db_update('internship_lperson_location_area');
                            $query ->fields($fields)
                                -> where('id_internship = '.$form_state['id_internship'].' AND id_lperson_location_area = '.
                                    $lperson_location_area->id_lperson_location_area)
                                -> execute();
                        } catch (Exception $ex) {
                            drupal_set_message('Errore: '.$ex,'error');
                        }
                        db_set_active();
                    }
                }

            } catch (Exception $ex) {
                drupal_set_message('Errore: ' . $ex, 'error');
            }

            unset($form_state['field_locations'][$key]);
        }
    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}


/**
 * @param $form
 * @param $form_state
 */
function add_lperson_location_area_submit($form, &$form_state) {

    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    if (!empty($form_state['values']['lperson_location_area_'.$id_lperson])) {
        $fields = array(
            'id_internship' => $form_state['id_internship'],
            'id_lperson_location_area' => $form_state['values']['lperson_location_area_' . $id_lperson],
            'active' => 1
        );
        $key = array(
            'id_internship' => $form_state['id_internship'],
            'id_lperson_location_area' => $form_state['values']['lperson_location_area_' . $id_lperson],
        );
        db_set_active('getif_data');
        try {
            $query = db_merge('internship_lperson_location_area');
            $query->key($key)->fields($fields)->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }
        db_set_active();
    }

    $form_state['rebuild'] = TRUE;
}


/**
 * @param $form
 * @param $form_state
 */
function remove_lperson_location_area_submit($form, &$form_state) {
    $id_internship_lperson_location_area = $form_state['clicked_button']['#attributes']['id_internship_lperson_location_area'];
    $fields = array(
        'active' => 0
    );
    db_set_active('getif_data');
    try {
        $query = db_update('internship_lperson_location_area');
        $query ->fields($fields) -> where('id_internship_lperson_location_area = '.$id_internship_lperson_location_area) ->execute();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 */
function check_branch_primary_submit($form, &$form_state) {

    $fields = array(
        'flg_primary' => 0,
    );
    $where = 'id_internship = '.$form_state['id_internship'].' and active = 1';
    try {
        db_set_active('getif_data');
        $query = db_update('internship_lperson');
        $query ->fields($fields)->where($where)->execute();
        db_set_active();
    } catch (Exception $ex) {

    }
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    $fields = array(
        'flg_primary' => 1,
    );
    $where = 'id_internship = '.$form_state['id_internship'].' and id_lperson = '.$id_lperson.' and active = 1';
    try {
        db_set_active('getif_data');
        $query = db_update('internship_lperson');
        $query ->fields($fields)->where($where)->execute();
        db_set_active();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}



/* end */

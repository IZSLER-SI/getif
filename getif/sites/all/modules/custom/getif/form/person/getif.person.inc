<?php

/**
 * Theme figura
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_person_form($variables){
    $form = $variables['form'];
    drupal_add_js('
            jQuery("input[type=checkbox][data-toggle^=toggle]").bootstrapToggle({
                on: "Sì",
                off: "No",
                onstyle: "success"
            });
        ',array('type'=>'inline','scope' => 'footer'));
    if (arg(1) == 'new') {
        $options['page_title'] = 'Nuova Figura';
        return getif_form_theme($form,null,$options);
    } elseif (arg(1) == 'edit') {

        $output = '<div class="panel panel-default">';
        $output .= '
        <ul class="nav nav-tabs" style = "background-color: #f5f5f5;">';
        $output .= '
            <li class="'.(!isset($_GET['new_person'])?"active":"").'"><a href="#panel1" data-toggle="tab">'.$form['fs_person']['#title'].'</a></li>';
        if (!empty($form['fs_position']['#title']))
            $output .= '
                <li><a href="#panel2" data-toggle="tab">' . $form['fs_position']['#title'] . '</a></li>';
        if (!empty($form['fs_role']['#title']))
            $output .= '
            <li class="'.(isset($_GET['fs_role'])?"active":"").'"><a href="#panel3" data-toggle="tab">' . $form['fs_role']['#title'] . '</a></li>';
        $output .= '
        </ul>
        <div class="tab-content">
            <div id="panel1" class="tab-pane '.(!isset($_GET['new_person'])?"active":"").' panel-body ">
               '.drupal_render($form['fs_person']).drupal_render($form['fs_person_type']).'<hr/><div style="text-align:right">'.drupal_render($form['actions']).'</div>
            </div>';
        if (!empty($form['fs_position']['#title']))
            $output .= '
            <div id="panel2" class="tab-pane panel-body ">
               ' . drupal_render($form['fs_position']) . '
            </div>';
        if (!empty($form['fs_role']['#title']))
            $output .= '
            <div id="panel3" class="tab-pane '.(isset($_GET['new_person'])?"active":"").' panel-body ">
               ' . drupal_render($form['fs_role']) . '
            </div>
           ';
        $output .= '</div>';
        $header_content[]['html'] = $output;
        $options['page_title'] = t('Modifica Figura').': '.$form['fs_person']['#attributes']['description'];
        return getif_form_theme($form,$header_content,$options);
    }
}

/**
 * @param $form
 * @param $form_state
 */
function back_wizard_submit($form, &$form_state) {
    $back_url = 'lperson'.$form_state['lprole'] .'/branch/edit/'.$form_state['id_lperson'].'/#panel3';
    getif_goto($back_url,array('query'=>array('new_person'=>'1')),302,true);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function person_form($form, &$form_state) {
    $form_state['controller'] = $form_state["build_info"]["args"][0];
    $form_state['id_person'] = !empty($form_state["build_info"]["args"][1])?$form_state["build_info"]["args"][1]:'';
    if ($form_state['controller'] == 'new') {
        $form_state['id_lperson'] = !empty($form_state["build_info"]["args"][1])?$form_state["build_info"]["args"][1]:'';
        $form_state['lprole'] = (isset($_GET['lprole']) && $_GET['lprole'] == "2")?'_host':'_promoter';
    } elseif ($form_state['controller'] == 'edit') {
        $form_state['id_person'] = !empty($form_state["build_info"]["args"][1])?$form_state["build_info"]["args"][1]:'';
        $person = getRecordById('person', 'getif_data', $form_state['id_person']);
        $form_state_values['title'] = $person->id_title;
        $form_state_values['id_person'] = $person->id_person;
        $form_state_values['firstname'] = ucwords($person->firstname);
        $form_state_values['lastname'] = ucwords($person->lastname);
        if (!ControlloCodiceFiscale($person->tax_code)) {
            $form_state_values['tax_code_check'] = FALSE;
        } else {
            $form_state_values['tax_code_check'] = TRUE;
        }
        $form_state_values['tax_code'] = strtoupper($person->tax_code);
        $form_state_values['gender'] = $person->gender;
        $form_state_values['birthdate'] = $person->birthdate;
        $form_state_values['birthplace'] = ucwords($person->birthplace);
        $meta_field_obj = json_decode($person->meta_field);
        $type_registry = array();
        foreach($meta_field_obj AS $key => $value) {
            if (in_array($key,array('is_worker','is_intern','is_voluntary')) && $value == '1') {
                $type_registry[$key] = $key;
            }
        }
        $form_state_values['type_registry'] = $type_registry;
        $form_state_values['residence_address'] = $person ->residence_address;
        if (!empty($person->domicile_address)) {
            $form_state_values['domicile_check'] = true;
            $form_state_values['domicile_address'] = $person->domicile_address;
        } else {
            $form_state_values['domicile_check'] = false;
        }
        $form_state_values['domicile_address'] = $person ->domicile_address;
        $form_state_values['phone'] = $person ->phone;
        $form_state_values['email_address'] = strtolower($person ->email_address);
        if (!empty($person->id_qualification)) {
            $qualification = getRecordById('lib_qualification', 'getif_data', $person->id_qualification);
            $form_state_values['qualification'] = $qualification->name;
        }
        $form_state_values['qualification_detail'] = _strformat($person ->qualification_detail);
    }
    $format = 'd-m-Y';
    $required = true;
    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    if (!empty($_GET['is_intern'])) {
        $form['nav']['goto_list'] = array(
            '#type' => 'button',
            '#value' => t('Lista tirocinanti'),
            '#limit_validation_errors' => array(),
            '#validate' => array('goto_list'),
            '#attributes' => array(
                'list_name' => 'intern'
            )
        );
    } elseif (!empty($_GET['is_voluntary'])) {
        $form['nav']['goto_list'] = array(
            '#type' => 'button',
            '#value' => t('Lista frequentatori'),
            '#limit_validation_errors' => array(),
            '#validate' => array('goto_list'),
            '#attributes' => array(
                'list_name' => 'vintern'
            )
        );
    } else {
        $form['nav']['goto_list'] = array(
            '#type' => 'button',
            '#value' => t('Lista figure'),
            '#limit_validation_errors' => array(),
            '#validate' => array('goto_list'),
            '#attributes' => array(
                'list_name' => 'person'
            )
        );
    }
    if (!empty($form_state['id_lperson'])) { // provengo dalla struttura
        $form['nav']['back'] = array(
            '#type' => 'button',
            '#value' => t('Indietro'),
            '#limit_validation_errors' => array(),
            '#validate' => array('back_wizard_submit'),
        );
    }
    // Contenuto
    $form['fs_person'] = array(
        '#type' => 'item',
        '#title' => t('Dati anagrafici'),
        '#prefix' => '<div id="fs-intern-div">',
        '#suffix' => '</div>',
        '#title_display' => 'invisible'
    );
    $form['fs_person']['id_person'] = array(
        '#type' => 'hidden'
    );
    $form['fs_person']['title'] = array(
        '#type' => 'select',
        '#title' => t('Titolo'),
        '#description' => t('Selezionare il titolo'),
        '#empty_option' => t('- Seleziona -'),
        '#options' => getLibOptions('lib_title','getif_data'),
        '#required' => true,
    );
    $form['fs_person']['firstname'] = array(
        '#type' => 'textfield',
        '#title' => t('Nome'),
        '#description' => t('Inserire il nome'),
        '#required' => true,
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    $form['fs_person']['lastname'] = array(
        '#type' => 'textfield',
        '#title' => t('Cognome'),
        '#description' => t('Inserire il cognome'),
        '#required' => true,
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    $form['fs_person']['tax_code_check'] = array(
        '#type' => 'checkbox',
        '#title' => t("Codice fiscale disponibile?"),
        '#description' => t('Deselezionare nel caso in cui non si disponga del Codice Fiscale.'),
        '#default_value' => true,
        '#attributes' => array(
            'data-toggle'=> 'toggle',
        )
    );
    $form['fs_person']['tax_code'] = array(
        '#type' => 'textfield',
        '#title' => t("Codice fiscale"),
        '#description' => t('Inserire il Cod.Fiscale'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#states' => array(
            'invisible' => array(
                ':input[name="tax_code_check"]' => array('checked' => FALSE),
            ),
            'required' => array(
                ':input[name="tax_code_check"]' => array('checked' => TRUE),
            ),
        ),
    );
    $form['fs_person']['gender'] = array(
        '#type' => 'radios',
        '#title' => t('Genere'),
        '#description' => t('Selezionare il genere'),
        '#options' => array('F'=>'F','M'=>'M'),
        '#empty_option' => t('- seleziona il sesso -'),
        '#required' => $required,
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    $form['fs_person']['birthdate'] = array(
        '#type' => 'date_popup',
        '#title' => t('Data di nascita'),
        '#description' => t('Inserire la data di nascita: es. 04-12-1987'),
        '#date_format' => $format,
        '#date_label_position' => 'within',
        '#date_timezone' => date_default_timezone(),
        '#date_year_range' => "-90:-18",
        '#datepicker_options' => array(),
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date','js-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'data-original-title' => t('Inserire la data di nascita: es. 04-12-1987'),
        ),
    );
    $form['fs_person']['birthplace'] = array(
        '#type' => 'textfield',
        '#title' => t("Luogo di nascita"),
        '#description' => t('Inserire il luogo di nascita'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    if ($form_state['controller'] != 'new') {
        $form['fs_person_type'] = array(
            '#type' => 'item',
            '#title' => t('Tipo anagrafe'),
        );

        $form['fs_person_type']['type_registry'] = array(
            '#type' => 'checkboxes',
            '#title' => t("Tipo anagrafe"),
            '#title_display' => 'invisible',
            '#description' => t("Selezionare una o più anagrafi di appartenenza"),
            '#options' => array(
                'is_worker' => 'figura',
                'is_intern' => 'tirocinante',
                'is_voluntary' => 'frequentatore'
            ),
            '#attributes' => array(
                'data-toggle' => 'toggle',
            ),
            '#required' => true
        );
    }
    if (empty($_GET['is_intern']) && empty($_GET['is_voluntary'])) {
        $form['fs_person']['residence_address'] = array(
            '#type' => 'textfield',
            '#title' => t("Indirizzo di residenza"),
            '#description' => t('Inserire l\'indirizzo di residenza'),
            '#attributes' => array(
                'check_for_draft_save' => 'no',
                'autocomplete' => 'off'
            ),
        );

        $form['fs_person']['domicile_check'] = array(
            '#type' => 'checkbox',
            '#title' => t("L'indirizzo di domicilio è diverso dall'indirizzo di Residenza?"),
            '#title' => t("Selezionare solo se l'indirizzo di domicilio è diverso dall'indirizzo di Residenza"),
            '#suffix' => '<br>',
            '#attributes' => array(
                'data-toggle'=> 'toggle'
            ),
        );

        $form['fs_person']['domicile_address'] = array(
            '#type' => 'textfield',
            '#title' => t("Indirizzo di domicilio"),
            '#description' => t('Inserire l\'indirizzo di domicilio'),
            '#attributes' => array(
                'check_for_draft_save' => 'no',
                'autocomplete' => 'off'
            ),
            '#states' => array(
                'visible' => array(
                    ':input[name="domicile_check"]' => array('checked' => TRUE),
                ),
            ),
        );
        $form['fs_person']['phone'] = array(
            '#type' => 'textfield',
            '#title' => t("Numero di telefono"),
            '#description' => t('Inserire il numero di telefono'),
            '#size' => 20,
            '#maxlength' => 20,
            '#element_validate' => array('getif_phone_element_validate'),
            '#attributes' => array(
                'check_for_draft_save' => 'no',
                'autocomplete' => 'off'
            ),
        );
        $form['fs_person']['email_address'] = array(
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
        $form['fs_person']['qualification'] = array(
            '#type' => 'textfield',
            '#title' => t("Titolo di studio conseguito"),
            '#description' => t('Selezionare il titolo di studio conseguito oppure aggiungerne uno nuovo'),
            '#autocomplete_path' => 'qualification_autocomplete_callback',
            '#ajax' => array(
                'callback' => 'ajax_qualification_after_autocomplete_callback',
                'wrapper' => 'add_qualification_ajax_div',
                'progress' => array(
                    'message' => '',
                    'type' => 'throbber',
                ),
            ),
            '#attributes' => array(),
        );
        $form['fs_person']['add_container'] = array('#prefix' => '<div id="add_qualification_ajax_div">', '#suffix' => '</div>');
        $qualification_name = !empty($form_state['values']['qualification']) ? _strformat($form_state['values']['qualification']) : '';
        if (($qualification_name != '' && empty(getRecordByField('lib_qualification', 'getif_data', 'name', $qualification_name, 1)))) {
            $form['fs_person']['add_container']['submit'] = array(
                '#type' => 'submit',
                '#submit' => array('qualification_form_submit'),
                '#value' => t('Aggiungi titolo di studio "') . ' ' . $qualification_name . '"',
                '#ajax' => array(
                    'callback' => 'ajax_qualification_after_add_callback',
                    'wrapper' => 'add_qualification_ajax_div',
                    'method' => 'html',
                    'effect' => 'fade',
                ),
                '#limit_validation_errors' => array(),
                '#suffix' => '<br /><br />'
            );
            $form['fs_person']['add_container']['ajax_markup'] = array(
                '#type' => 'hidden',
                '#suffix' => '<div id="show_ajax_message_div">',
                '#suffix' => '</div>',
                '#value' => $qualification_name,
            );
        }
        $form['fs_person']['qualification_detail'] = array(
            '#type' => 'textfield',
            '#title' => t('Dettagli sul titolo di studio'),
            '#description' => t('Inserire ulteriori dettagli sul titolo di studio conseguito'),
            '#required' => false,
            '#attributes' => array(
                'check_for_draft_save' => 'no',
                'autocomplete' => 'off'
            ),
        );

        /* POSIZIONI C/O SOGGETTI */
        if ($form_state['controller'] == "edit") {
            $form['fs_position'] = array(
                '#type' => 'item',
                '#title' => t('Posizioni'),
                '#prefix' => '<div id="fs-position-div">',
                '#suffix' => '</div>',
                '#title_display' => 'invisible'
            );
            $form['fs_position']['position_container'] = array(
                '#type' => 'container',
                '#tree' => TRUE,
                '#prefix' => '<div id="position-ajax-wrapper">',
                '#suffix' => '</div>',
            );

            // recupera le posizioni impostate
            $results = getAllRecordByField('person_lperson', 'getif_data', 'id_person', $person->id_person, 'active');
            if (empty($form_state['position_rows'])) {
                foreach ($results as $key => $result) {
                    $lperson = getRecordById('lperson', 'getif_data', $result->id_lperson, 'active');
                    $person_lperson_positions = getAllRecordByField('person_lperson_position', 'getif_data', 'id_person_lperson', $result->id_person_lperson, 'active');
                    if ($lperson->level == 1) {
                        $lperson_parent = getRecordById('lperson', 'getif_data', $lperson->id_lperson_parent, 'active');
                    }
                    foreach ($person_lperson_positions as $key_plp => $person_lperson_position) {
                        $form_state['position_rows'][$person_lperson_position->id_person_lperson_position] = array(
                            getRecordById('lib_position', 'getif_data', $person_lperson_position->id_position, 'active')->description,
                            empty($lperson_parent->name)?$lperson->name:$lperson_parent->name . ' - ' . $lperson->name,
                        );
                    }
                }
            }
            $header = array(t('Posizione'), t('C/O'), t('Azioni'));
            $rows = !empty($form_state['position_rows']) ? $form_state['position_rows'] : array();
            $options = array();
            foreach ($rows as $key => $row) {
                // pulsante elimina
                $form['remove_person_lperson_position_' . $key] = array(
                    '#type' => 'submit',
                    '#name' => 'remove_person_lperson_position_' . $key,
                    '#value' => '',
                    '#submit' => array('remove_person_lperson_position_submit'),
                    '#id' => 'edit-remove-person-lperson-position-' . $key,
                    '#ajax' => array(
                        'callback' => 'add_position_callback',
                        'wrapper' => 'position-ajax-wrapper',
                    ),
                    '#attributes' => array(
                        'id_person_lperson_position' => $key,
                        'class' => array('btn', 'btn-remove', 'glyphicon', 'glyphicon-trash')
                    ),
                );
                $options[$key] = $row;
                $form['remove_person_lperson_position_' . $key] = ajax_pre_render_element($form['remove_person_lperson_position_' . $key]);
                $options[$key][] = drupal_render($form['remove_person_lperson_position_' . $key]);
            }
            $form['fs_position']['position_container']['table'] = array
            (
                '#theme' => 'table',
                '#header' => $header,
                '#rows' => $options,
                '#empty' => t('Table has no row!'),
                '#suffix' => '<hr>'
            );
            $form['fs_position']['position_container']['position'] = array(
                '#type' => 'select',
                '#title' => t('Nuova Posizione'),
                '#description' => t('Selezionare una posizione'),
                '#empty_option' => t('- Seleziona la posizione -'),
                '#options' => getLibOptions('lib_position', 'getif_data'),
                '#ajax' => array(
                    'event' => 'change',
                    'callback' => 'position_ajax_callback',
                    'wrapper' => 'where1-ajax-wrapper',
                ),
            );

            $id_position = empty($form_state['values']['position_container']['position']) ? (empty($form_state_values['position_container']['position']) ? '' : $form_state_values['position_container']['position']) : $form_state['values']['position_container']['position'];
            $form['fs_position']['position_container']['where1_ajax_wrapper'] = array('#prefix' => '<div id="where1-ajax-wrapper">', '#suffix' => '</div>');
            if (!empty($id_position)) {
                $form['fs_position']['position_container']['where1_ajax_wrapper']['where1'] = array(
                    '#type' => 'textfield',
                    '#title' => t('C/O'),
                    '#description' => t('Selezionare il Soggetto'),
                    '#autocomplete_path' => 'lperson_by_position_and_level_autocomplete_callback/' . $id_position,
                    '#ajax' => array(
                        'callback' => 'ajax_where1_after_autocomplete_callback',
                        'wrapper' => 'where1-ajax-wrapper',
                        'event' => 'blur',
                        'progress' => array(
                            'message' => '',
                            'type' => 'throbber',
                        ),
                    ),
                );
                $form['fs_position']['position_container']['where1_ajax_wrapper']['where1_id'] = array(
                    '#type' => 'hidden',
                    '#attributes' => array(
                        'id' => 'edit-position-container-where1-ajax-wrapper-where1_id',
                    ),
                    '#suffix' => "
                <script>jQuery(function($) {
                    var position_select = false;
                    $(\"#edit-position-container-where1-ajax-wrapper-where1\").bind('autocompleteSelect', function() {
                        var values = $(this).val().split('|');
                        $(this).val(values[0]);
                        if (values[1]) {
                            $(\"#edit-position-container-where1-ajax-wrapper-where1_id\").val(values[1]);
                            position_select = true;
                        }
                    }).blur(function() {
                        if(position_select == false) {
                            $(\"#edit-position-container-where1-ajax-wrapper-where1\").val(\"\");
                        }
                        position_select = false;
                    });
                });</script>"
                );
            }
            $form['fs_position']['position_container']['add_position'] = array(
                '#type' => 'submit',
                '#name' => 'add_position',
                '#value' => t('Aggiungi posizione'),
                '#limit_validation_errors' => array(),
                '#submit' => array('add_position_submit'),
                '#ajax' => array(
                    'callback' => 'add_position_callback',
                    'wrapper' => 'position-ajax-wrapper',
                ),
                '#weight' => 100,
            );
        }

        /* RUOLI */
        if ($form_state['controller'] == "edit") {
            $form['fs_role'] = array(
                '#type' => 'item',
                '#title' => t('Ruoli'),
                '#prefix' => '<div id="fs-role-div">',
                '#suffix' => '</div>',
                '#title_display' => 'invisible'
            );
            $form['fs_role']['role_container'] = array(
                '#type' => 'container',
                '#tree' => TRUE,
                '#prefix' => '<div id="role-ajax-wrapper">',
                '#suffix' => '</div>',
            );
            // recupera i ruoli impostati

            $results = getAllRecordByField('person_lperson', 'getif_data', 'id_person', $person->id_person, 'active');
            
            if (empty($form_state['role_rows'])) {
                foreach ($results as $key => $result) {

                    $lperson = getRecordById('lperson', 'getif_data', $result->id_lperson, 'active');
                    if ($lperson->level == 1) {
                        $lperson_parent = getRecordById('lperson', 'getif_data', $lperson->id_lperson_parent, 'active');
                    }
                    $person_lperson_proles = getAllRecordByField('person_lperson_prole', 'getif_data', 'id_person_lperson', $result->id_person_lperson, 'active');

                    foreach ($person_lperson_proles as $key_plp => $person_lperson_prole) {
                        $form_state['role_rows'][$person_lperson_prole->id_person_lperson_prole] = array(
                            getRecordById('lib_prole', 'getif_data', $person_lperson_prole->id_prole, 'active')->description,
                            $lperson_parent->name . ' - ' . $lperson->name,
                        );
                    }
                }
            }

            $header = array(t('Ruolo'), t('C/O'), t('Azioni'));
            $rows = !empty($form_state['role_rows']) ? $form_state['role_rows'] : array();
            $options = array();
            foreach ($rows as $key => $row) {
                // pulsante elimina
                $form['remove_person_lperson_prole_' . $key] = array(
                    '#type' => 'submit',
                    '#name' => 'remove_person_lperson_prole_' . $key,
                    '#value' => '',
                    '#submit' => array('remove_person_lperson_prole_submit'),
                    '#id' => 'edit-remove-person-lperson-prole-' . $key,
                    '#ajax' => array(
                        'callback' => 'add_role_callback',
                        'wrapper' => 'role-ajax-wrapper',
                    ),
                    '#attributes' => array(
                        'id_person_lperson_prole' => $key,
                        'id_person' => $person->id_person,
                        'class' => array('btn', 'btn-remove', 'glyphicon', 'glyphicon-trash'),
                    ),
                );
                $options[$key] = $row;
                $form['remove_person_lperson_prole_' . $key] = ajax_pre_render_element($form['remove_person_lperson_prole_' . $key]);
                $options[$key][] = drupal_render($form['remove_person_lperson_prole_' . $key]);
            }
            $form['fs_role']['role_container']['table'] = array
            (
                '#theme' => 'table',
                '#header' => $header,
                '#rows' => $options,
                '#empty' => t('Table has no row!'),
                '#suffix' => '<hr>'
            );
            $form['fs_role']['role_container']['prole'] = array(
                '#type' => 'select',
                '#title' => t('Nuovo Ruolo'),
                '#description' => t('Selezionare un ruolo'),
                '#empty_option' => t('- Seleziona il ruolo -'),
                '#options' => getLibOptions('lib_prole', 'getif_data'),
                '#ajax' => array(
                    'event' => 'change',
                    'callback' => 'prole_ajax_callback',
                    'wrapper' => 'where-ajax-wrapper',
                ),
            );
            
            $id_prole = empty($form_state['values']['role_container']['prole']) ? (empty($form_state_values['role_container']['prole']) ? '' : $form_state_values['role_container']['prole']) : $form_state['values']['role_container']['prole'];
            $form['fs_role']['role_container']['where_ajax_wrapper'] = array('#prefix' => '<div id="where-ajax-wrapper">', '#suffix' => '</div>');
            if (!empty($id_prole)) {
                $form['fs_role']['role_container']['where_ajax_wrapper']['where'] = array(
                    '#type' => 'textfield',
                    '#title' => t('C/O'),
                    '#description' => t('Selezionare il Soggetto'),
                    '#autocomplete_path' => 'lperson_by_prole_and_level_autocomplete_callback/' . $id_prole,

                );
                $form['fs_role']['role_container']['where_ajax_wrapper']['where_id'] = array(
                    '#type' => 'hidden',
                    '#attributes' => array(
                        'id' => 'edit-role-container-where-ajax-wrapper-where_id',
                    ),
                    '#suffix' => "
                    <script>jQuery(function($) {var role_select = false;
                        $(\"#edit-role-container-where-ajax-wrapper-where\").bind('autocompleteSelect', function() {
                            var values = $(this).val().split('|');
                            $(this).val(values[0]);
                            if (values[1]) {
                                $(\"#edit-role-container-where-ajax-wrapper-where_id\").val(values[1]);
                                role_select = true;
                            }
                        }).blur(function() {
                            if(role_select == false) {
                                $(\"#edit-role-container-where-ajax-wrapper-where\").val(\"\");
                            }
                            role_select = false;
                        });
                    });</script>"
                );
            }
            $form['fs_role']['role_container']['add_role'] = array(
                '#type' => 'submit',
                '#name' => 'add_role',
                '#value' => t('Aggiungi ruolo'),
                '#limit_validation_errors' => array(),
                '#submit' => array('add_role_submit'),
                '#ajax' => array(
                    'callback' => 'add_role_callback',
                    'wrapper' => 'role-ajax-wrapper',
                ),
                '#weight' => 100,
            );
        }
    }
    if ($form_state['controller'] == "edit")
        $form['fs_person']['#attributes']['description'] = $person->firstname.' '.$person->lastname;

    // Submit Button
    $form['actions']['submit'] = array(
        '#type' => 'submit',
    );

    if ($form_state['controller'] == "new") {
        $form['actions']['submit']['#value'] = t('Salva');
        $form['actions']['submit']['#attributes']['controller'] = $form_state['controller'];
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Conferma e prosegui.")){return false;}';
    } elseif ($form_state['controller'] == "edit") {
        fill_data($form, $form_state_values);
        $form['actions']['submit']['#value'] = t('Salva');
        $form['actions']['submit']['#attributes']['id_person'] = $form_state['id_person'];
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler applicare le modifiche?")){return false;}';
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
            if (!empty($element['#validate']) && $element['#validate'] != array('go_back')) {
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
function fill_data(&$form, &$form_state_values) {
    $form['fs_person']['id_person']['#value'] = $form_state_values['id_person'];
    $form['fs_person']['title']['#default_value'] = $form_state_values['title'];
    $form['fs_person']['firstname']['#default_value'] = !empty($form_state_values['firstname'])?$form_state_values['firstname']:'';
    $form['fs_person']['lastname']['#default_value'] = !empty($form_state_values['lastname'])?$form_state_values['lastname']:'';
    $form['fs_person']['tax_code']['#default_value'] = !empty($form_state_values['tax_code'])?$form_state_values['tax_code']:'';
    $form['fs_person']['tax_code_check']['#default_value'] = !empty($form_state_values['tax_code_check'])?$form_state_values['tax_code_check']:'';
    $form['fs_person']['birthplace']['#default_value'] = !empty($form_state_values['birthplace'])?$form_state_values['birthplace']:'';
    if(!empty($form_state_values['gender'])) {
        $form['fs_person']['gender']['#default_value'] = $form_state_values['gender'];
    }
    if (!empty($form_state_values['birthdate'])) {
        $form['fs_person']['birthdate']['#default_value']  = date("Y-m-d",strtotime($form_state_values['birthdate']));
    }
    if (arg(1) != 'new') {
        $form['fs_person_type']['type_registry']['#default_value'] = $form_state_values['type_registry'];
    }
    $form['fs_person']['residence_address']['#default_value'] = !empty($form_state_values['residence_address'])?$form_state_values['residence_address']:'';
    $form['fs_person']['domicile_check']['#default_value'] = !empty($form_state_values['domicile_check'])?$form_state_values['domicile_check']:false;
    $form['fs_person']['domicile_address']['#default_value'] = !empty($form_state_values['domicile_address'])?$form_state_values['domicile_address']:'';
    $form['fs_person']['phone']['#default_value'] = !empty($form_state_values['phone'])?$form_state_values['phone']:'';
    $form['fs_person']['email_address']['#default_value'] = !empty($form_state_values['email_address'])?$form_state_values['email_address']:'';
    $form['fs_person']['qualification']['#default_value'] = !empty($form_state_values['qualification'])?$form_state_values['qualification']:'';
    $form['fs_person']['qualification_detail']['#default_value'] = !empty($form_state_values['qualification_detail'])?$form_state_values['qualification_detail']."":'';
    $form['fs_person']['role']['#default_value'] = !empty($form_state_values['role'])?$form_state_values['role']:'';
    $form['fs_role']['promoter']['#default_value'] = !empty($form_state_values['promoter'])?$form_state_values['promoter']:'';
    $form['fs_role']['host']['#default_value'] = !empty($form_state_values['host'])?$form_state_values['host']:'';
    $form['fs_role']['host_contact_person']['#default_value'] = !empty($form_state_values['host_contact_person'])?$form_state_values['host_contact_person']:'';
}


/**
 * @param $form
 * @param $form_state
 */
function go_back ($form, &$form_state) {
    if ($form_state['controller'] == 'new') {
        getif_goto('person/list',array(),302,true);
    } elseif ($form_state['controller'] == 'view-confirm') {
        getif_goto('person/new',array(),302,true);
    } elseif ($form_state['controller'] == 'view') {
        getif_goto('person/list',array(),302,true);
    } elseif ($form_state['controller'] == 'edit') {
        getif_goto('person/list',array(),302,true);
    }
}

/**
 * @param $form
 * @param $form_state
 */
function person_form_validate($form, &$form_state) {
    if(!empty($form_state['values']['tax_code']) && ($form_state['values']['tax_code_check'])) {
        if (ControlloCodiceFiscale($form_state['values']['tax_code'])) {
            db_set_active('getif_data');
            $query = db_select('person', 'p');
            if ($form_state["build_info"]["args"]["0"] == 'new') {
                $query->condition('tax_code', db_like($form_state['values']['tax_code']), 'LIKE');
            } else {
                $query->where(
                    'p.tax_code LIKE \''.$form_state["values"]["tax_code"].'\' AND
                      p.id_person <> '.$form_state["build_info"]["args"]["1"].' AND 
                      p.active IN (1,2)
                    ');
            }
            $query->fields('p', array('id_person'));
            $id_person = $query->execute()->fetchAssoc();
            db_set_active();
            if (!empty($id_person)) {
                form_set_error('tax_code', t('Figura con questo codice fiscale esistente.'));
            }
        } else {
            form_set_error('tax_code', t('Codice Fiscale non valido.'));
        }
    }
    if (empty($_GET['is_intern']) && empty($_GET['is_voluntary'])) {
        // controllo sul titolo di studio
        if (!empty($form['fs_person']['add_container']['ajax_markup'])) {
            form_set_error('qualification', t('Il titolo di studio deve essere prima aggiunto alla lista.'));
        }
    }
}


/**
 * @param $form
 * @param $form_state
 */
function person_form_submit($form, &$form_state) {
    $controller = $form_state['controller'];
    $destination = '';
    if ($controller == 'new') {
        $id_person = save($form, $form_state);
        if (!empty($form_state['id_lperson'])) { // provengo dalla struttura
            $fields = array(
                'id_person' => $id_person,
                'id_lperson' => $form_state['id_lperson'],
            );
            db_set_active('getif_data');
            try {
                $query = db_insert('person_lperson');
                $id_person_lperson = $query -> fields($fields)->execute();
            } catch (Exception $ex) {
                drupal_set_message('Errore: '.$ex,'error');
            }
            db_set_active();
            $destination = 'lperson'.( $_GET['lprole'] == "2"?'_host':'_promoter').'/branch/edit/'.$form_state['id_lperson'];
            $_SESSION['new_person']['id_person'] = $id_person;
            $_SESSION['new_person']['id_person_lperson'] = $id_person_lperson;
            drupal_set_message(t("Dati inseriti con successo"));
            drupal_goto($destination,array('query'=>array('new_person'=>'1')));
        } else {
            $destination = 'person/list';
            unset($_SESSION['new_person']);
        }
        drupal_set_message(t("Dati inseriti con successo"));
    } elseif ($controller == 'edit') {
        $id_person = edit($form, $form_state);
        if (!empty($_GET['is_intern'])) {
            $destination = 'intern/list';
        } elseif (!empty($_GET['is_voluntary'])) {
            $destination = 'vintern/list';
        } else {
            $destination = 'person/list';
        }
        drupal_set_message(t("Dati modificati con successo"));
    }
    drupal_goto($destination);
}

/**
 * @param $form
 * @param $form_state
 */
function upgrade_submit($form, &$form_state) {
    /* prepara dati da aggiornare */
    $id_person = $form_state["build_info"]["args"][1];
    db_set_active('getif_data');
    $query = db_select('person','t1');
    $query->fields('t1',array('meta_field'));
    $query->condition('t1.id_person',$id_person);
    $meta_field = $query->execute()->fetchField();
    db_set_active();
    $meta_field_array = json_decode($meta_field);
    $meta_field_array->is_worker = '1';
    $fields = array(
        'meta_field' => json_encode($meta_field_array),
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    try {
        db_set_active('getif_data');
        $query = db_update('person');
        $query -> fields($fields) -> condition('id_person',$id_person)->execute();
        db_set_active();
        drupal_set_message(t("Dati modificati con successo"));
        drupal_goto("person/list");
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    drupal_set_message(t("Si sono verificati uno o più errori. Riprovare e se il problema persisiste contattare l'amministratore di sistema."),'error');
}


/**
 * @param $form
 * @param $form_state
 * @return DatabaseStatementInterface|int
 */
function save($form, &$form_state) {
    // get id_qualification
    if (!empty($form_state['values']['qualification'])) {
        db_set_active('getif_data');
        $query = db_select('lib_qualification','lq');
        try {
            $id_qualification = $query->fields('lq',array('id_qualification'))->condition('name',$form_state['values']['qualification'])->execute()->fetchField();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
    }
    /* insert into person */
    $fields = array(
        'id_title' => $form_state['values']['title'],
        'firstname' => _strformat($form_state['values']['firstname']),
        'lastname' => _strformat($form_state['values']['lastname']),
        'tax_code' => str_pad('N', 16,'N',STR_PAD_LEFT),
        'gender' => $form_state['values']['gender'],
        'birthdate' => ($form_state['values']['birthdate']),
        'birthplace' => _strformat($form_state['values']['birthplace']),
        'residence_address' => !empty(_strformat($form_state['values']['residence_address']))?_strformat($form_state['values']['residence_address']):null,
        'domicile_address' => !empty(_strformat($form_state['values']['domicile_address']))?_strformat($form_state['values']['domicile_address']):null,
        'phone' => !empty($form_state['values']['phone'])?$form_state['values']['phone']:null,
        'email_address' => !empty(strtolower($form_state['values']['email_address']))?strtolower($form_state['values']['email_address']):null,
        'id_qualification' => !empty($id_qualification)?$id_qualification:null,
        'qualification_detail' => !empty(_strformat($form_state['values']['qualification_detail']))?_strformat($form_state['values']['qualification_detail']):null,
        'meta_field' => json_encode(array('is_worker'=>'1'))
    );
    db_set_active('getif_data');
    if (!empty($form_state['values']['tax_code']) && $form_state['values']['tax_code_check']) {
        $fields['tax_code'] = strtoupper($form_state['values']['tax_code']);
        $has_tax_code = true;
    } else {
        $has_tax_code = false;
    }
    try {
        $query = db_insert('person');
        $id_person= $query -> fields($fields)->execute();
        // se non c'è il codice fiscale fa l'update del codice codice fiscale inserendo l'id della figura inserita
        if ($has_tax_code == false) {
            $query = db_update('person');
            $query->fields(
                array(
                    'tax_code ' => str_pad($id_person, 16, 'N', STR_PAD_LEFT)
                )
            );
            $query->condition('id_person', $id_person);
            $query->execute();
        }
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    // pulisci il form
    unset($_SESSION['new_person']);
    return $id_person;
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function edit($form, &$form_state) {
    /* prepara dati da aggiornare */
    $id_person = $form_state["build_info"]["args"][1];
    // get id_qualification
    if (!empty($form_state['values']['qualification'])) {
        db_set_active('getif_data');
        $query = db_select('lib_qualification','lq');
        try {
            $id_qualification = $query->fields('lq',array('id_qualification'))->condition('name',$form_state['values']['qualification'])->execute()->fetchAssoc();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
    }
    // get meta_field
    db_set_active('getif_data');
    $query = db_select('person','t1');
    $query->fields('t1',array('meta_field'));
    $query->condition('t1.id_person',$id_person);
    $meta_field = $query->execute()->fetchField();
    $meta_field_array = json_decode($meta_field,true);
    foreach ($form_state['values']['type_registry'] AS $key => $type) {
        if (strval($type) == strval($key)) {
            $meta_field_array[$key] = '1';
        } else {
            unset($meta_field_array[$key]);
        }
    }
    db_set_active();
    $fields = array(
        'id_title' => $form_state['values']['title'],
        'firstname' => _strformat($form_state['values']['firstname']),
        'lastname' => _strformat($form_state['values']['lastname']),
        'tax_code' => strtoupper($form_state['values']['tax_code']),
        'gender' => $form_state['values']['gender'],
        'birthdate' => ($form_state['values']['birthdate']),
        'birthplace' => _strformat($form_state['values']['birthplace']),
        'residence_address' => !empty($form_state['values']['residence_address'])?_strformat($form_state['values']['residence_address']):null,
        'phone' => !empty($form_state['values']['phone'])?$form_state['values']['phone']:null,
        'email_address' => !empty($form_state['values']['email_address'])?strtolower($form_state['values']['email_address']):null,
        'id_qualification' => !empty($id_qualification)?$id_qualification:null,
        'qualification_detail' => !empty($form_state['values']['qualification_detail'])?_strformat($form_state['values']['qualification_detail']):null,
        'meta_field' => json_encode($meta_field_array),
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    if (!empty($form_state['values']['domicile_check']) && $form_state['values']['domicile_check'] && !empty($form_state['values']['domicile_address'])) {
        $fields['domicile_address'] = _strformat($form_state['values']['domicile_address']);
    } else {
        $fields['domicile_address'] = '';
    }
    db_set_active('getif_data');
    try {
        $query = db_update('person');
        $query -> fields($fields) -> condition('id_person',$id_person)->execute();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    return $id_person;
}


/* qualification functions */
/**
 * @param $form
 * @param $form_state
 */
function qualification_form_submit($form, &$form_state) {
    drupal_set_message(t('Titolo di studio '.$form_state['values']['qualification'].' aggiunto!'));
    $form_state['rebuild'] = true;
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function ajax_qualification_after_autocomplete_callback($form, &$form_state) {
    return $form['fs_person']['add_container'];
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 * @throws Exception
 */
function ajax_qualification_after_add_callback($form, &$form_state) {
    setLibOption('lib_qualification','getif_data',array(
        'name' => $form_state['values']['qualification'],
        'description' => $form_state['values']['qualification']
    ));
    return $form['fs_person']['add_container'];
}

/* position functions */
/**
 * @param $form
 * @param $form_state
 */
function position_form_submit($form, &$form_state) {
    drupal_set_message(t('Posizione '.$form_state['values']['position'].' aggiunta!'));
    $form_state['rebuild'] = true;
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function ajax_position_after_autocomplete_callback($form, &$form_state) {
    return $form['fs_position']['add_position'];
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 * @throws Exception
 */
function ajax_position_after_add_callback($form, &$form_state) {
    setLibOption('lib_position','getif_data','name',$form_state['values']['position']);
    return $form['fs_position']['add_position'];
}


/**
 * @param $form
 * @param $form_state
 * @return array
 */
function ajax_where_after_autocomplete_callback($form, $form_state) {
    $value = $form_state['values']['role_container']['where_ajax_wrapper']['where'];
    $value_exploded = explode('|', $value);
    $value_id = $value_exploded[1];
    $value_name = $value_exploded[0];
    $form['fs_role']['role_container']['where_ajax_wrapper']['where']['#value'] = $value_name;
    
    if (!empty($value_id)) {
        $form['fs_role']['role_container']['where_ajax_wrapper']['where_id']['#value'] = $value_id;
    } else {
        $form['fs_role']['role_container']['where_ajax_wrapper']['where_id']['#value'] = $form_state['values']['role_container']['where_ajax_wrapper']['where_id'];
    }
    
    $commands = array();
    $commands[] = ajax_command_replace('#where-ajax-wrapper', drupal_render($form['fs_role']['role_container']['where_ajax_wrapper']));
    return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * @param $form
 * @param $form_state
 */
function add_role_submit($form, &$form_state) {
    $id_prole = $form_state['input']['role_container']['prole'];
    $where = $form_state['input']['role_container']['where_ajax_wrapper']['where'];
    $id_lperson = $form_state['input']['role_container']['where_ajax_wrapper']['where_id'];
    $id_person = $form_state['input']['id_person'];

    if (!empty($id_prole) && !empty($where) && !empty($id_lperson) && !empty($id_person)) {


        db_set_active('getif_data');
        $query = db_select('person_lperson', 't1');
        $query->fields('t1', array('id_person_lperson'));
        $query->condition('t1.id_person', $id_person);
        $query->condition('t1.id_lperson', $id_lperson);
        $query->condition('t1.active', 1);
        $id_person_lperson = $query->execute()->fetchAssoc();
        db_set_active();


        if (!$id_person_lperson) {
            $fields = array(
                'id_person' => $id_person,
                'id_lperson' => $id_lperson,
            );
            db_set_active('getif_data');
            try {
                $query = db_insert('person_lperson');
                $id_person_lperson = $query->fields($fields)->execute();
            } catch (Exception $ex) {
                drupal_set_message('Errore: ' . $ex, 'error');
            }
            db_set_active();
        }
        // se i campi sono avvalorati
        if (!empty($id_prole) && !empty($id_lperson)) {
            $row = array($form['fs_role']['role_container']['prole']['#options'][$id_prole], $where);
            // se la riga non è presente in tabella viene inserita
            if (!in_array($row, $form_state['role_rows'])) {
                $form_state['role_rows'][] = $row;
                // insert to DB
                $fields = array(
                    'id_person_lperson' => $id_person_lperson,
                    'id_prole' => $id_prole,
                );

                try {
                    db_set_active('getif_data');
                    $query = db_insert('person_lperson_prole');
                    $query->fields($fields)->execute();
                    db_set_active();
                    drupal_set_message(t("Ruolo inserito con successo."), 'status');
                } catch (Exception $ex) {
                    drupal_set_message('Errore: ' . $ex, 'error');
                }

            }
        }
    } else {
        drupal_set_message(t("Devi prima selezionare un ruolo e un Soggetto."), 'error');
    }
    // deseleziona campi
    $form_state['input']['role_container']['prole'] = '';
    $form_state['input']['role_container']['where_ajax_wrapper']['where'] = '';
    // rebuild
    $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 */
function remove_role_submit($form, &$form_state) {
    $selected = array_filter($form_state['values']['role_container']['table']);
    // controllo che la persona con quel ruolo non abbia tirocini attivi o pratiche di tirocinio aperte
    $tables = array('internship_host_tutor','internship_promoter_tutor','internship_project_contact');
    foreach ($tables as $table) {
        foreach ($selected as $id_person_lperson_prole) {
            db_set_active('getif_data');
            $query = db_select($table, 't1');
            $query->condition('t1.id_person_lperson_prole', $id_person_lperson_prole);
            $query->condition('t1.active', 1);
            $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
            $query->condition('t2.state', 0, '<>'); // tirocinio
            $query->condition('t2.state', 7, '<>');
            $query->condition('t2.active', 1);
            $result = $query->countQuery()->execute()->fetchField();
            db_set_active();
            if ($result > 0) {
                drupal_set_message(t("Ruolo/i presente/i in una pratica di tirocinio aperta e/o tirocinio attivo."),'error');
                return;
            }
        }
    }
    foreach ($selected as $key => $item) {
        try {
            // disabilita il record
            setRecordState('person_lperson_prole', 'getif_data', 'id_person_lperson_prole', $item, 'active', 2);
            // elimina dalla tabella
            unset($form_state['role_rows'][$item]);
            drupal_set_message(t("Ruolo/i eliminato con successo."),'status');
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        };
    }

}


/**
 * @param $form
 * @param $form_state
 */
function remove_person_lperson_prole_submit($form, &$form_state) {
    $id_person_lperson_prole = $form_state['clicked_button']['#attributes']['id_person_lperson_prole'];
    // controllo se la figura è associata ad un tirocinio attivo oppure ad una pratica di tirocinio aperto
    $error = false;
    $tables = array('internship_host_tutor','internship_promoter_tutor','internship_project_contact');
    foreach ($tables as $table) {
        db_set_active('getif_data');
        $query = db_select($table, 't1');
        $query->condition('t1.id_person_lperson_prole', $id_person_lperson_prole);
        $query->condition('t1.active', 1);
        $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
        $query->condition('t2.state', 0, '<>'); // tirocinio
        $query->condition('t2.state', 7, '<>');
        $query->condition('t2.active', 1);
        $result = $query->countQuery()->execute()->fetchField();
        db_set_active();
        if ($result > 0) {
            drupal_set_message(t("Il ruolo della figura selezionata non può essere cessato perché associato ad una pratica di tirocinio aperta e/o tirocinio attivo."),'error');
            $error = true;
        }
    }
    if($error) {
        return;
    } else {
        try {
            // disabilita il record
            setRecordState('person_lperson_prole', 'getif_data', 'id_person_lperson_prole', $id_person_lperson_prole, 'active', 2);
            drupal_set_message(t("Ruolo eliminato con successo."),'status');
            // elimina dalla tabella
            unset($form_state['role_rows'][$id_person_lperson_prole]);
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        };
    }
    $form_state['rebuild'] = TRUE;
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_role_callback($form, &$form_state) {
    return $form['fs_role']['role_container'];
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function prole_ajax_callback($form, $form_state) {
    // resetta i campi where e where_id
    $form['fs_role']['role_container']['where_ajax_wrapper']['where']['#value'] = '';
    $form['fs_role']['role_container']['where_ajax_wrapper']['where_id']['#value'] = '';
    return $form['fs_role']['role_container']['where_ajax_wrapper'];
}


/**
 * @param $form
 * @param $form_state
 */
function add_position_submit($form, &$form_state)
{
    $id_position = $form_state['input']['position_container']['position'];
    $where = $form_state['input']['position_container']['where1_ajax_wrapper']['where1'];
    $id_lperson = $form_state['input']['position_container']['where1_ajax_wrapper']['where1_id'];
    $id_person = $form_state['input']['id_person'];

    if (!empty($id_position) && !empty($where) && !empty($id_lperson) && !empty($id_person)) {
        db_set_active('getif_data');
        $query = db_select('person_lperson', 't1');
        $query->fields('t1', array('id_person_lperson'));
        $query->condition('t1.id_person', $id_person);
        $query->condition('t1.id_lperson', $id_lperson);
        $query->condition('t1.active', 1);
        $id_person_lperson = $query->execute()->fetchAssoc();
        db_set_active();


        if (!$id_person_lperson) {
            $fields = array(
                'id_person' => $id_person,
                'id_lperson' => $id_lperson,
                'active' => 1
            );

            try {
                db_set_active('getif_data');
                $query = db_insert('person_lperson');
                $id_person_lperson = $query->fields($fields)->execute();
                db_set_active();
            } catch (Exception $ex) {
                drupal_set_message('Errore: ' . $ex, 'error');
            }

        }

        // se i campi sono avvalorati
        if (!empty($id_position) && !empty($id_lperson)) {
            $row = array($form['fs_position']['position_container']['position']['#options'][$id_position], $where);
            // se la riga non è presente in tabella viene inserita
            if (!in_array($row, $form_state['position_rows'])) {
                $form_state['position_rows'][] = $row;
                // insert to DB
                $fields = array(
                    'id_person_lperson' => $id_person_lperson,
                    'id_position' => $id_position,
                    'active' => 1
                );

                try {
                    db_set_active('getif_data');
                    $query = db_insert('person_lperson_position');
                    $query->fields($fields)->execute();
                    db_set_active();
                    drupal_set_message(t("Posizione inserita con successo."), 'status');
                } catch (Exception $ex) {
                    drupal_set_message('Errore: ' . $ex, 'error');
                }


            }
        }
    }else {
        drupal_set_message(t("Devi prima selezionare un ruolo e un Soggetto."), 'error');
    }
    // deseleziona campi
    $form_state['input']['position_container']['position'] = '';
    $form_state['input']['position_container']['where1_ajax_wrapper']['where1'] = '';
    // rebuild
    $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 */
function remove_position_submit($form, &$form_state) {
    $selected = array_filter($form_state['values']['position_container']['table']);
    foreach ($selected as $key => $item) {
        try {
            // disabilita il record
            setRecordState('person_lperson_position', 'getif_data', 'id_person_lperson_position', $item, 'active', 2);
            // elimina dalla tabella
            unset($form_state['position_rows'][$item]);
            drupal_set_message(t("Posizione/i eliminata/e con successo."),'error');
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        };
    }
    $form_state['rebuild'] = TRUE;

}

/**
 * @param $form
 * @param $form_state
 */
function remove_person_lperson_position_submit($form, &$form_state) {
    $id_person_lperson_position = $form_state['clicked_button']['#attributes']['id_person_lperson_position'];
    try {
        // disabilita il record
        setRecordState('person_lperson_position', 'getif_data', 'id_person_lperson_position', $id_person_lperson_position, 'active', 2);
        // elimina dalla tabella
        unset($form_state['position_rows'][$id_person_lperson_position]);
        drupal_set_message(t("Posizione eliminata con successo."),'status');
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    };
    $form_state['rebuild'] = TRUE;
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_position_callback($form, &$form_state) {
    return $form['fs_position']['position_container'];
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function position_ajax_callback($form, $form_state) {
    // resetta i campi where e where_id
    $form['fs_position']['position_container']['where1_ajax_wrapper']['where1']['#value'] = '';
    $form['fs_position']['position_container']['where1_ajax_wrapper']['where1_id']['#value'] = '';
    return $form['fs_position']['position_container']['where1_ajax_wrapper'];
}


/**
 * @param $form
 * @param $form_state
 * @return array
 */
function ajax_where1_after_autocomplete_callback($form, $form_state) {

    $value = $form_state['values']['position_container']['where1_ajax_wrapper']['where1'];
    $value_exploded = explode('|', $value);
    $value_id = $value_exploded[1];
    $value_name = $value_exploded[0];
    $form['fs_position']['position_container']['where1_ajax_wrapper']['where1']['#value'] = $value_name;

    if (!empty($value_id)) {
        $form['fs_position']['position_container']['where1_ajax_wrapper']['where1_id']['#value'] = $value_id;
    } else {
        $form['fs_position']['position_container']['where1_ajax_wrapper']['where1_id']['#value'] = $form_state['values']['position_container']['where1_ajax_wrapper']['where1_id'];
    }
    $commands = array();
    $commands[] = ajax_command_replace('#where1-ajax-wrapper', drupal_render($form['fs_position']['position_container']['where1_ajax_wrapper']));
    return array('#type' => 'ajax', '#commands' => $commands);
}





/* end */

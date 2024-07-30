<?php


/**
 * Theme sezione nuovo/modifica tirocinante
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_intern_form($variables){
    $form = $variables['form'];
    $wizard = init();
    if (!isset($form_state['stage'])) {
        $form_state['stage'] = 'ti_1';
    }

    $header_content = array();
    $output = '';
    if ($wizard) {
        $output .= get_internship_new_header($wizard);

    }
    $header_content[] = array('html' => $output,'has_separator' => false);
    $options['show_fs_title'] = false;
    return getif_form_theme($form,$header_content,$options);
}

/**
 * @return bool|int
 */
function init() {
    $module_path = drupal_get_path('module', 'getif');
    $full_path = $module_path .'/css/getif.css';
    drupal_add_css($full_path);
    if (isset($_SESSION['prev'])) {
        if ($_SESSION['prev'] == "internship/new/1") {
            return 1;
        } elseif (strpos($_SESSION['prev'],"internship/new/2") === 0) {
            return 2;
        } else {
            return false;
        }

    }
}


/**
 * @return bool|int
 */
function check_wizard() {
    if (isset($_SESSION['prev'])) {
        if ($_SESSION['prev'] == "internship/new/1") {
            return 1;
        } elseif (strpos($_SESSION['prev'],"internship/new/2") === 0) {
            return 2;
        } else {
            return false;
        }
    }
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function intern_form($form, &$form_state) {
    $check_wizard = check_wizard();
    $controller = $form_state["build_info"]["args"][0];
    $required = true;
    $optional_required = true;
    if ($controller == "new") {
        if ($check_wizard == 1) { // provengo da nuovo tirocinio
            $optional_required = false;
            $form['nav']['back'] = array(
                '#type' => 'button',
                '#value' => t('Indietro'),
                '#limit_validation_errors' => array(),
                '#validate' => array('back_wizard_submit'),
            );
        }
        if (!empty(session_get('new_intern'))) { // provengo da view-confirm
            $form_state_values = session_get('new_intern');
            unset($_SESSION['new_intern']);
        }
    } elseif($controller == "edit"  || $controller == "view") {
        $form_state_values = session_get('new_intern');
    }
    // Buttons
    // Torna alla Dashboard
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#description' => t('Vai alla Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    // Torna alla lista dei Tirocini
    $form['nav']['goto_list'] = array(
        '#type' => 'button',
        '#value' => t('Tirocini'),
        '#description' => t('Vai alla lista dei tirocini'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'internship'
        )
    );

    // Fieldset
    $form['fs_intern'] = array(
        '#type' => 'container',
        '#title' => t('Tirocinante'),
        '#prefix' => '<div id="fs-intern-div">',
        '#suffix' => '</div>',
    );
    // Titolo, es. Dott., Dott.ssa, Sig., Sig.ra
    $form['fs_intern']['intern_div_ajax_wrapper']['title'] = array(
        '#type' => 'select',
        '#title' => t('Titolo'),
        '#description' => t('Seleziona il titolo'),
        '#empty_option' => t('- Seleziona -'),
        '#options' => getLibOptions('lib_title','getif_data'),
        '#required' => $required,
    );
    // Nome
    $form['fs_intern']['intern_div_ajax_wrapper']['firstname'] = array(
        '#type' => 'textfield',
        '#title' => t('Nome'),
        '#description' => t('Inserisci il nome'),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off'
        ),
    );
    // Cognome
    $form['fs_intern']['intern_div_ajax_wrapper']['lastname'] = array(
        '#type' => 'textfield',
        '#title' => t('Cognome'),
        '#description' => t('Inserisci il cognome'),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off'
        ),
    );
    // Check presenza codice fiscale
    $form['fs_intern']['intern_div_ajax_wrapper']['tax_code_check'] = array(
        '#type' => 'checkbox',
        '#title' => t("Codice fiscale disponibile?"),
        '#description' => t('Deselezionare nel caso non si dispone del Codice Fiscale.'),
        '#default_value' => TRUE,
        '#attributes' => array(
            'data-toggle'=> 'toggle',
        )
    );
    // Codice Fiscale
    $form['fs_intern']['intern_div_ajax_wrapper']['tax_code'] = array(
        '#type' => 'textfield',
        '#title' => t("Codice fiscale"),
        '#description' => t('Inserisci il codice fiscale'),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#attributes' => array(
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
    // Altro ID
    $form['fs_intern']['intern_div_ajax_wrapper']['id_code'] = array(
        '#type' => 'textfield',
        '#title' => t("Altro ID"),
        '#description' => t('Inserisci un altro ID (es. numero carta d\'identità oppure passaporto)'),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#attributes' => array(
            'autocomplete' => 'off'
        ),
        '#states' => array(
            'invisible' => array(
                ':input[name="tax_code_check"]' => array('checked' => TRUE),
            ),
            'required' => array(
                ':input[name="tax_code_check"]' => array('checked' => FALSE),
            ),
        ),
    );
    // Genere: Maschio: M / Femmina: F
    $form['fs_intern']['intern_div_ajax_wrapper']['gender'] = array(
        '#type' => 'radios',
        '#title' => t('Genere'),
        '#description' => t('Inserisci il genere'),
        '#options' => array('F'=>'F','M'=>'M'),
        '#empty_option' => t('- seleziona il sesso -'),
        '#required' => $required,
    );
    // Data di nascita
    $form['fs_intern']['intern_div_ajax_wrapper']['birthdate'] = array(
        '#type' => 'date_popup',
        '#title' => t('Data di nascita'),
        '#description' => t('Inserisci la data di nascita'),
        '#date_format' => GETIF_FORMAT,
        '#date_label_position' => 'within',
        '#date_timezone' => date_default_timezone(),
        '#date_year_range' => "-90:-18",
        '#datepicker_options' => array(),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'class' => array('js-date'),
            'placeholder' => 'gg-mm-aaaa'
        ),
    );
    // Luogo di nascita
    $form['fs_intern']['intern_div_ajax_wrapper']['birthplace'] = array(
        '#type' => 'textfield',
        '#title' => t("Luogo di nascita"),
        '#description' => t('Inserisci il luogo di nascita'),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
        )
    );
    // Indirizzo di residenza
    $form['fs_intern']['intern_div_ajax_wrapper']['residence_address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo di residenza"),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#required' => $optional_required,'#access' => $optional_required,
        '#attributes' => array(
            'autocomplete' => 'off',
        )
    );
    // Check se domicilio è diverso da residenza
    $form['fs_intern']['intern_div_ajax_wrapper']['domicile_check'] = array(
        '#type' => 'checkbox',
        '#title' => t("L'indirizzo di domicilio è diverso dall'indirizzo di Residenza?"),
        '#suffix' => '<br>',
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off',
            'data-toggle'=> 'toggle'
        ),
        '#access' => $optional_required,
    );
    // Indirizzo di domicilio
    $form['fs_intern']['intern_div_ajax_wrapper']['domicile_address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo di domicilio"),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#access' => $optional_required,
        '#attributes' => array(
            'autocomplete' => 'off',
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="domicile_check"]' => array('checked' => TRUE),
            ),
            'required' => array(
                ':input[name="domicile_check"]' => array('checked' => TRUE),
            ),
        ),
    );
    // Telefono
    $form['fs_intern']['intern_div_ajax_wrapper']['phone'] = array(
        '#type' => 'textfield',
        '#title' => t("Numero di telefono"),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#size' => 20,
        '#maxlength' => 20,
        '#element_validate' => array('getif_phone_element_validate'),
        '#required' => false,'#access' => $optional_required,
        '#attributes' => array(
            'autocomplete' => 'off',
        )
    );
    // Indirizzo Email
    $form['fs_intern']['intern_div_ajax_wrapper']['email_address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo Email"),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#default_value' => "",
        '#size' => 40,
        '#maxlength' => 40,
        '#element_validate' => array('getif_email_element_validate'),
        '#required' => $optional_required,'#access' => $optional_required,
        '#attributes' => array(
            'autocomplete' => 'off',
        )
    );
    // Qualifica
    $form['fs_intern']['intern_div_ajax_wrapper']['qualification'] = array(
        '#type' => 'textfield',
        '#title' => t("Titolo di studio conseguito"),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#autocomplete_path' => 'qualification_autocomplete_callback',
        '#ajax' => array(
            'callback' => 'ajax_qualification_after_autocomplete_callback',
            'wrapper' => 'add_qualification_ajax_div',
            'progress' => array(
                'message' => '',
                'type' => 'throbber',
            ),
        ),
        '#required' => $optional_required,'#access' => $optional_required,
    );
    $form['fs_intern']['intern_div_ajax_wrapper']['add_container'] = array('#prefix' => '<div id="add_qualification_ajax_div">', '#suffix' => '</div>');
    $qualification_name = !empty($form_state['values']['qualification'])?_strformat($form_state['values']['qualification']):'';
    if (($qualification_name != '' && empty(getRecordByField('lib_qualification','getif_data','name',$qualification_name,1)))) {
        $form['fs_intern']['intern_div_ajax_wrapper']['add_container']['submit'] = array(
            '#type' => 'submit',
            '#submit' => array('qualification_form_submit'),
            '#value' => t('Aggiungi titolo "').' '.$qualification_name.'"',
            '#ajax' => array(
                'callback' => 'ajax_qualification_after_add_callback',
                'wrapper' => 'add_qualification_ajax_div',
                'method' => 'html',
                'effect' => 'fade',
            ),
            '#limit_validation_errors' => array(),
            '#attributes' => array(
            ),
            '#suffix' => '<br /><br />'
        );
        $form['fs_intern']['intern_div_ajax_wrapper']['add_container']['ajax_markup'] = array(
            '#type' => 'hidden',
            '#suffix' => '<div id="show_ajax_message_div">',
            '#suffix' => '</div>',
            '#value' => $qualification_name,
        );
    }
    $form['fs_intern']['intern_div_ajax_wrapper']['qualification_detail'] = array(
        '#type' => 'textfield',
        '#title' => t('Dettagli sul titolo di studio'),
        '#attributes' => array('check_for_draft_save'=> 'no'),
        '#required' => false,'#access' => $optional_required,
        '#attributes' => array(
            'autocomplete' => 'off',
        )
    );

    // Corso che sta frequentando - previsto solo per curriculari
    if ($optional_required) {

        if (getInternshipTypeByInternshipId('getif_data', session_get('id_internship')) == 0) {
            $form['fs_intern']['intern_div_ajax_wrapper']['attended_course'] = array(
                '#type' => 'textfield',
                '#title' => t("Corso di studi in frequenza") . ' ' . t('(solo per tirocinanti curricolari)'),
                '#attributes' => array('check_for_draft_save' => 'no'),
                '#required' => $optional_required, '#access' => $optional_required,
                '#attributes' => array(
                    'autocomplete' => 'off',
                )
            );
            // Dettagli indirizzo del corso frequentato
            $form['fs_intern']['intern_div_ajax_wrapper']['attended_course_address'] = array(
                '#type' => 'textfield',
                '#title' => t("Indirizzo del corso di studio") . ' ' . t('(solo per tirocinanti curricolari)'),
                '#attributes' => array('check_for_draft_save' => 'no'),
                '#required' => false, '#access' => $optional_required,
                '#attributes' => array(
                    'autocomplete' => 'off',
                )
            );
            // Annualità in corso
            $form['fs_intern']['intern_div_ajax_wrapper']['attended_course_ontime'] = array(
                '#type' => 'textfield',
                '#title' => t("Annualità in corso") . ' ' . t('(solo per tirocinanti curricolari)'),
                '#attributes' => array('check_for_draft_save' => 'no'),
                '#required' => false, '#access' => $optional_required,
                '#attributes' => array(
                    'autocomplete' => 'off',
                )
            );
        }
    }
    // Tipo di tirocinante
    $form['fs_intern']['intern_div_ajax_wrapper']['intern_type'] = array(
        '#type' => 'select',
        '#title' => t('Tipo Tirocinante'),
        '#empty_option' => t('- Seleziona -'),
        '#options' => getLibOptions('lib_intern_type', 'getif_data'),
        '#ajax' => array(
            'callback' => 'intern_type_ajax_callback',
            'wrapper' => 'intern-type-div-ajax-wrapper',
            'progress' => array(
                'message' => '',
                'type' => 'throbber',
            )
        ),
        '#required' => $optional_required,'#access' => $optional_required
    );
    if (($controller == 'edit' || $controller == 'view') && empty($form_state['input']['intern_type'])) {
        $internship_person = getRecordById('internship_person', 'getif_data', $form_state["build_info"]["args"]["1"]);

        if(!empty( $internship_person->id_intern_type))
            $intern_type = $internship_person->id_intern_type;
    } else {
        $intern_type = empty($form_state['input']['intern_type'])?(empty($form_state_values['intern_type'])?'':$form_state_values['intern_type']):$form_state['input']['intern_type'];
    }
    $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper'] = array('#prefix' => '<div id="intern-type-div-ajax-wrapper">', '#suffix' => '</div>');



    /* Allegato compatibilità borsa di studio */
    $form['fs_intern']['intern_div_ajax_wrapper']['attachment'] = array(
        '#type' => 'managed_file',
        '#title' => t('Allegato di compatibilità borsa di studio'),
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#description' => t('Click "Browse..." to select an attachment to upload.'),
        '#access' => $optional_required,
        '#upload_validators' => array(
            'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
        ),
        '#limit_validation_errors' => array(),
        '#upload_location' => 'public://attached/internship/'.session_get('id_internship').'/',
        '#states' => array(
            'visible'=>array(
                ':input[name="intern_type"]'=>array('value'=>2)
            ),
            'required'=>array(
                ':input[name="intern_type"]'=>array('value'=>2)
            )

        )
    );

    if (!empty($intern_type)) {
        /* Orari di Servizio */
        if ($intern_type == 1) {
            $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper']['markup'] = array(
                '#markup' => '<h5>Orario di servizio</h5>',
            );
            $i = 0;
            while ($i < 7) {
                $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper']['ora_da_'.$i.'_0'] = array(
                    '#type' => 'textfield',
                    '#title' => 'Entrata:',
                    '#size' => '3',
                    '#prefix' => '<div class = "container-inline badge badge-secondary" style="width:100px;margin-right:20px"><b>'.$dow_text = ucwords(strftime("%A", strtotime("Monday +{$i} days"))).'</b></div><div class = "container-inline">',
                    '#suffix' => '</div>',
                    '#attributes' => array(
                        'class' => array('mask_time'),
                        'autocomplete' => 'off',
                    ),

                    '#access' => $optional_required
                );
                $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper']['ora_a_'.$i.'_0'] = array(
                    '#type' => 'textfield',
                    '#title' => 'Uscita:',
                    '#size' => '3',
                    '#prefix' => '<div class = "container-inline">',
                    '#suffix' => '</div>',
                    '#attributes' => array(
                        'class' => array('mask_time'),
                        'autocomplete' => 'off',
                    ),
                    '#access' => $optional_required
                );
                $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper']['ora_da_'.$i.'_1'] = array(
                    '#type' => 'textfield',
                    '#title' => 'Entrata:',
                    '#size' => '3',
                    '#prefix' => '<div class = "container-inline">',
                    '#suffix' => '</div>',
                    '#attributes' => array(
                        'class' => array('mask_time'),
                        'autocomplete' => 'off',
                    )
                );
                $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper']['ora_a_'.$i++.'_1'] = array(
                    '#type' => 'textfield',
                    '#title' => 'Uscita:',
                    '#size' => '3',
                    '#prefix' => '<div class = "container-inline">',
                    '#suffix' => '</div><div></div>',
                    '#attributes' => array(
                        'class' => array('mask_time'),
                        'autocomplete' => 'off',
                    )
                );
            }
        }
    }

    /* SUBMIT */
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#attributes' => array(
            'is_wizard' => $check_wizard,
            'controller' => $controller
        )
    );
    if ($form_state["build_info"]["args"]["0"] == "new") {
        $form['actions']['submit']['#value'] = t('Salva');
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Conferma e prosegui.")){return false;}';
    } elseif ($controller == 'edit' || $controller == 'view') {
        $form['actions']['submit']['#value'] = t('Salva');
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Conferma e prosegui.")){return false;}';
        $form['actions']['submit']['#attributes']['id_person'] = $internship_person->id_person;
        if (check_wizard() == 2 || $controller == 'view') {
            if (empty($internship_person)) {
                $internship_person = getRecordById('internship_person', 'getif_data', $form_state["build_info"]["args"]["1"]);
            }
            $person = getRecordById('person', 'getif_data', $internship_person->id_person);
            $form_state['id_person'] = $internship_person->id_person;
            if (!empty($internship_person->id_qualification)) {
                $qualification = getRecordById('lib_qualification', 'getif_data', $internship_person->id_qualification);
                $form['fs_intern']['intern_div_ajax_wrapper']['qualification']['#default_value'] = $qualification->name;
            }
            $form['fs_intern']['intern_div_ajax_wrapper']['title']['#default_value'] = $person->id_title;
            $form['fs_intern']['intern_div_ajax_wrapper']['firstname']['#default_value'] = ucwords($person->firstname);
            $form['fs_intern']['intern_div_ajax_wrapper']['lastname']['#default_value'] = ucwords($person->lastname);
            
            if (ControlloCodiceFiscale($person->tax_code)) {
                $form['fs_intern']['intern_div_ajax_wrapper']['tax_code_check']['#default_value'] = TRUE;
                $form['fs_intern']['intern_div_ajax_wrapper']['tax_code']['#default_value'] = strtoupper($person->tax_code);
            } else {
                $form['fs_intern']['intern_div_ajax_wrapper']['tax_code_check']['#default_value'] = FALSE;
                $form['fs_intern']['intern_div_ajax_wrapper']['id_code']['#default_value'] = strtoupper($person->tax_code);
            }
            $form['fs_intern']['intern_div_ajax_wrapper']['gender']['#default_value'] = array_search(strtoupper($person->gender),$form['fs_intern']['intern_div_ajax_wrapper']['gender']['#options']);
            $form['fs_intern']['intern_div_ajax_wrapper']['birthdate']['#default_value'] = $person->birthdate;
            $form['fs_intern']['intern_div_ajax_wrapper']['birthplace']['#default_value'] = $person->birthplace;
            $form['fs_intern']['intern_div_ajax_wrapper']['residence_address']['#default_value'] = $internship_person ->residence_address;
            if (!empty($internship_person->domicile_address)) {
                $form['fs_intern']['intern_div_ajax_wrapper']['domicile_check']['#default_value'] = true;
                $form['fs_intern']['intern_div_ajax_wrapper']['domicile_address']['#default_value'] = $internship_person->domicile_address;
            } else {
                $form['fs_intern']['intern_div_ajax_wrapper']['domicile_check']['#default_value'] = false;
            }
            $form['fs_intern']['intern_div_ajax_wrapper']['phone']['#default_value'] = $internship_person ->phone;
            $form['fs_intern']['intern_div_ajax_wrapper']['email_address']['#default_value'] = strtolower($internship_person ->email_address);
            $form['fs_intern']['intern_div_ajax_wrapper']['qualification_detail']['#default_value'] = $internship_person->qualification_detail;
            $form['fs_intern']['intern_div_ajax_wrapper']['intern_type']['#default_value'] = $internship_person->id_intern_type;

            // Corso che sta frequentando - previsto solo per curriculari
            if(getInternshipTypeByInternshipId('getif_data',session_get('id_internship')) == 0) {
                if (!empty($internship_person->attended_course)) {
                    $attended_course = json_decode($internship_person->attended_course);
                    $form['fs_intern']['intern_div_ajax_wrapper']['attended_course']['#default_value'] = $attended_course->name;
                    $form['fs_intern']['intern_div_ajax_wrapper']['attended_course_address']['#default_value'] = $attended_course->address;
                    $form['fs_intern']['intern_div_ajax_wrapper']['attended_course_ontime']['#default_value'] = $attended_course->ontime;

                }
            }
            if(!empty($internship_person->id_intern_type) && $internship_person->id_intern_type == 1) {
                $working_times = json_decode(  $internship_person->working_time );

                foreach($working_times as $key_wt => $working_time) {
                    $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper']['ora_da_'.$key_wt.'_0']['#default_value'] = $working_time[0];
                    $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper']['ora_a_'.$key_wt.'_0']['#default_value'] = $working_time[1];
                    if (count($working_time) > 2) {
                        $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper']['ora_da_' . $key_wt . '_1']['#default_value'] = $working_time[2];
                        $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper']['ora_a_' . $key_wt . '_1']['#default_value'] = $working_time[3];
                    }
                }
            }
            if(!empty($internship_person->id_intern_type) && $internship_person->id_intern_type == 2) {
                $attachments = getInternshipAttachmentsByInternshipId('getif_data',session_get('id_internship'));
                $form['fs_intern']['intern_div_ajax_wrapper']['attachment']['#default_value'] =
                    !empty($attachments['dichiarazione_compatibilita_borsa_di_studio']->id_file_managed)?$attachments['dichiarazione_compatibilita_borsa_di_studio']->id_file_managed:'';
            }
            $form['nav']['back'] = array(
                '#type' => 'submit',
                //'#attributes' => array('onClick' => 'location.href="'.$_SESSION['prev'].'"; return false;'),
                '#value' => t('Indietro'),
                '#submit' => array('back_wizard_submit'),
                '#limit_validation_errors' => array(),
            );
        }

        if ($controller == "view") {
            $form['actions']['submit']['#disabled'] = true;
            // disabilita elementi
            _iterate_form($form, function(&$element, $form){
                if (!empty($element['#type']) && $element['#type'] == 'submit') {
                    if (!empty($element['#submit']) && $element['#submit'] != array('back_submit')) {
                        $element['#access'] = false;
                    }
                }
            });
        }
    }
    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function edit_submit($form, &$form_state) {
    drupal_goto('intern/edit/'.$form_state["build_info"]["args"]["1"]);
}


/**
 * @param $form
 * @param $form_state
 */
function intern_form_validate($form, &$form_state) {
    if(!empty($form_state['values']['tax_code']) && ($form_state['values']['tax_code_check'])) {
        if (ControlloCodiceFiscale($form_state['values']['tax_code'])) {
            db_set_active('getif_data');
            $query = db_select('person', 'p');
            if ($form_state["build_info"]["args"]["0"] == 'new') {
                $query->condition('tax_code', db_like($form_state['values']['tax_code']), 'LIKE');
            } else {

                $query->where(
                    'p.tax_code LIKE \''.$form_state["values"]["tax_code"].'\' AND
                      p.id_person <> '.$form_state['id_person'].' AND 
                      p.active IN (1,2)
                    ');
            }
            $query->fields('p', array('id_person'));
            $id_person = $query->execute()->fetchAssoc();
            db_set_active();

            if (!empty($id_person)) {
                form_set_error('tax_code', t('Tirocinante con questo codice fiscale esistente.'));
            }
        } else {
            form_set_error('tax_code', t('Codice Fiscale non valido.'));
        }
    }
    if (check_wizard() == 2) {
        if ($form_state['values']['domicile_check'] && empty($form_state['values']['domicile_address'])) {
            form_set_error('domicile_address', t('Il campo indirizzo di domicilio è obbligatorio.'));
        }
        
        if ($form_state['input']['intern_type'] == 2) {
            if ($form_state['values']['attachment'] == 0) {
                form_set_error('attachment', t('L\'allegato di compatibilità della borsa di studio è obbligatorio.'));
            }
        }
    }
}

/**
 * @param $form
 * @param $form_state
 */
function back_submit ($form, &$form_state) {
    $is_wizard = $form_state['clicked_button']['#attributes']['is_wizard'];
    $controller = $form_state['clicked_button']['#attributes']['controller'];
    if ($controller == 'new' ) {
        if ($is_wizard) {
            getif_goto($_SESSION['prev'],array(),302,true);
        } else {
            drupal_goto('');
        }
    } elseif ($controller == 'view-confirm') {
        if($is_wizard == 1) {
            drupal_goto('intern/new');
        } elseif($is_wizard == 2) {
            drupal_goto('intern/edit/'.$form_state["build_info"]["args"]["1"]);
        } else {
            drupal_goto('intern/list');
        }
    } elseif ($controller == 'view') {

        if ($is_wizard == 1 || $is_wizard == 2) {
            getif_goto($_SESSION['prev'],array(),302,true);
        } else {
            drupal_goto('intern/list');
        }
    } elseif ($controller == 'edit') {
        drupal_goto('intern/list');
    }
}


/**
 * @param $form
 * @param $form_state
 */
function back_wizard_submit($form, &$form_state) {
    $back_url = $_SESSION['prev'];
    $_SESSION['prev'] = drupal_get_destination()["destination"];
    getif_goto($back_url,array(),302,true);
}


/**
 * @param $form
 * @param $form_state
 */
function intern_form_submit($form, &$form_state) {
    $controller = $form_state['clicked_button']['#attributes']['controller'];
    $is_wizard = $form_state['clicked_button']['#attributes']['is_wizard'];
    if($controller == "new") {
        unset($_SESSION['new_intern']);
        $id_person = save($form_state);
        if ($is_wizard == 1) {
            $_SESSION['prev'] = drupal_get_destination()["destination"];
            $_SESSION['intern_inserted'] = $id_person;
            $new_internship_1 = session_get('new_internship_1',array());
            $new_intern_name = ucfirst($form_state['values']['firstname']).' '.ucfirst($form_state['values']['lastname']);
            if (!empty($form_state['values']['tax_code']) && $form_state['values']['tax_code_check']) {
                $new_intern_name = $new_intern_name.' ('.strtoupper($form_state['values']['tax_code']).')';
            } elseif (!empty($form_state['values']['id_code']) && !$form_state['values']['tax_code_check']) {
                $new_intern_name = $new_intern_name.' ('.strtoupper($form_state['values']['id_code']).')';
            }
            $new_internship_1['intern'] = $new_intern_name;
            $new_internship_1['intern_id'] = $id_person;
            session_set('new_internship_1',$new_internship_1);
            drupal_set_message(t("Dati inseriti con successo"));
            getif_goto('internship/new/1', array(), 302, true);
        } elseif ($is_wizard == 2) {
            unset($_SESSION['new_intern']);
            $new_internship_1 = session_get('internship_id');
            edit($form,$form_state);
            getif_goto('internship/new/'.$is_wizard.'/'.$new_internship_1, array(), 302, true);
        } else
        {
            drupal_set_message(t("Dati inseriti con successo"));
            drupal_goto('intern/view/'.$id_person);
        }
    } elseif ($form_state["build_info"]["args"][0] == "edit") {
        if ($is_wizard == 2) {
            unset($_SESSION['new_intern']);
            $new_internship_1 = session_get('internship_id');
            edit($form, $form_state);
            drupal_goto($_SESSION['prev']);
        }
    }

}


/**
 * @param $form_state
 * @return DatabaseStatementInterface|int
 */
function save(&$form_state) {
    /* prepara dati da inserire nella tabella person */
    $fields = array(
        'id_title' => $form_state['values']['title'],
        'gender' => $form_state['values']['gender'],
        'firstname' => $form_state['values']['firstname'],
        'lastname' => $form_state['values']['lastname'],
        'birthdate' => $form_state['values']['birthdate'],
        'birthplace' => $form_state['values']['birthplace'],
        'meta_field' => json_encode(array('is_intern'=>'1'))
    );
    if (!empty($form_state['values']['tax_code']) && $form_state['values']['tax_code_check']) {
        $fields['tax_code'] = strtoupper($form_state['values']['tax_code']);
    }
    if (!empty($form_state['values']['id_code']) && !$form_state['values']['tax_code_check']) {
        $fields['tax_code'] = strtoupper($form_state['values']['id_code']);
    }
    try {
        db_set_active('getif_data');
        $query = db_insert('person');
        $id_person = $query->fields($fields)->execute();
        db_set_active();
        $w_type = 'getif_person';
        $w_message = t('Insert item %id');
        $w_variables = array('%id'=>$id_person);
        watchdog($w_type, $w_message, $w_variables);
        return $id_person;
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    return 0;
}

/**
 * @param $form
 * @param $form_state
 */
function edit($form, &$form_state) {
    /* prepara dati da inserire */
    $id_person = $form_state['clicked_button']['#attributes']['id_person'];
    $fields = array(
        'firstname' => $form_state['values']['firstname'],
        'lastname' => $form_state['values']['lastname'],
        'birthdate' => $form_state['values']['birthdate'],
        'birthplace' => $form_state['values']['birthplace'],
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    if (!empty($form_state['values']['tax_code']) && $form_state['values']['tax_code_check']) {
        $fields['tax_code'] = strtoupper($form_state['values']['tax_code']);
    }
    if (!empty($form_state['values']['id_code']) && !$form_state['values']['tax_code_check']) {
        $fields['tax_code'] = strtoupper($form_state['values']['id_code']);
    }
    db_set_active('getif_data');
    $query = db_update('person');
    $query -> fields($fields) -> condition('id_person',$id_person)->execute();
    db_set_active();
    // watchdog
    $w_type = 'getif_person';
    $w_message = t('Update item %id');
    $w_variables = array($id_person);
    watchdog($w_type, $w_message, $w_variables);
    db_set_active('getif_data');
    $fields = array(
        'residence_address' => _strformat($form_state['values']['residence_address']),
        'phone' => $form_state['values']['phone'],
        'email_address' => strtolower($form_state['values']['email_address']),
        'attended_course' => !empty($form_state['values']['attended_course'])?_strformat($form_state['values']['attended_course']):'',
        'qualification_detail' => _strformat($form_state['values']['qualification_detail']),
        'date_upd' => date("Y-m-d H:i:s", time()));
    if ($form_state['values']['domicile_check'] && !empty($form_state['values']['domicile_address'])) {
        $fields['domicile_address'] = _strformat($form_state['values']['domicile_address']);
    } else {
        $fields['domicile_address'] = '';
    }
    $query = db_select('lib_qualification','lq');
    $qualification = $query->fields('lq',array('id_qualification'))->condition('name',$form_state['values']['qualification'])->execute()->fetchField();
    db_set_active();
    if ($qualification != null) {
        $fields['id_qualification'] =  $qualification;
    }
    if(getInternshipTypeByInternshipId('getif_data',session_get('id_internship')) == 0) {
        $attended_course = json_encode(
            array(
            'name'=>$form_state['values']['attended_course'],
            'address'=>!empty($form_state['values']['attended_course_address'])?$form_state['values']['attended_course_address']:'',
            'ontime'=>!empty($form_state['values']['attended_course_ontime'])?$form_state['values']['attended_course_ontime']:'',
            ),JSON_UNESCAPED_UNICODE);
        $fields['attended_course'] =  $attended_course;
    }

    if (!empty($form_state['values']['intern_type']) || $form_state['values']['intern_type'] != 0) {
        $fields['id_intern_type'] =  $form_state['values']['intern_type'];
        if($form_state['values']['intern_type'] == 1) { // se dipendente
            $i = 0;
            $working_time = array();
            while ($i < 7) {
                if(!empty($form_state['values']['ora_da_'.$i.'_0']) && !empty($form_state['values']['ora_a_'.$i.'_0'])) {
                    $working_time[$i][] = $form_state['values']['ora_da_'.$i.'_0'];
                    $working_time[$i][] = $form_state['values']['ora_a_'.$i.'_0'];
                }
                if(!empty($form_state['values']['ora_da_'.$i.'_1']) && !empty($form_state['values']['ora_a_'.$i.'_1'])) {
                    $working_time[$i][] = $form_state['values']['ora_da_'.$i.'_1'];
                    $working_time[$i][] = $form_state['values']['ora_a_'.$i.'_1'];
                }
                $i++;
            }
            $fields['working_time'] =  json_encode($working_time);
        } elseif ($form_state['values']['intern_type'] == 2) {
            try {
                db_set_active('getif_data');
                // prima elimino l'allegato precedente
                $query = db_update('internship_attachment');
                $query
                    -> fields(array(
                        'active' => 0,
                        )
                    )
                    ->condition(db_and()
                    ->condition('id_internship',session_get('id_internship'))
                    ->condition('meta','dichiarazione_compatibilita_borsa_di_studio','LIKE'))->execute();
                db_set_active();
                // watchdog
                $w_type = 'getif_internship_attachment';
                $w_message = t('Delete items with id_internship:%id AND meta:%meta');
                $w_variables = array('%id'=>session_get('%id_internship'),'meta'=>'dichiarazione_compatibilita_borsa_di_studio');
                watchdog($w_type, $w_message, $w_variables);
                // poi inserisco il nuovo allegato
                db_set_active('getif_data');
                $query = db_insert('internship_attachment');
                $id_internship_attachment = $query -> fields(array(
                    'id_internship' => session_get('id_internship'),
                    'id_file_managed' => $form_state['values']['attachment'],
                    'date_application' => date("Y-m-d H:i:s", time()),
                    'meta' => 'dichiarazione_compatibilita_borsa_di_studio',
                    'date_upd' => date("Y-m-d H:i:s", time()),
                ))->execute();
                db_set_active();
                // watchdog
                $w_type = 'getif_internship_attachment';
                $w_message = t('Insert item %id');
                $w_variables = array('%id'=>$id_person);
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
                drupal_set_message('Errore: '.$ex,'error');
            }
        }
    }
    db_set_active('getif_data');
    $query = db_update('internship_person');
    $query -> fields($fields)->condition('id_internship_person',$form_state["build_info"]["args"]["1"])->execute();
    db_set_active();
    $w_type = 'getif_internship_person';
    $w_message = t('Update item %id');
    $w_variables = array('%id'=>$form_state["build_info"]["args"]["1"]);
    watchdog($w_type, $w_message, $w_variables);
}


/* qualification ajax functions */
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
    return $form['fs_intern']['intern_div_ajax_wrapper']['add_container'];
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
    return $form['fs_intern']['intern_div_ajax_wrapper']['add_container'];
}

/* intern type ajax functions */
/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function intern_type_ajax_callback($form, &$form_state) {
    return $form['fs_intern']['intern_div_ajax_wrapper']['intern_type_div_ajax_wrapper'];
}

/* end */

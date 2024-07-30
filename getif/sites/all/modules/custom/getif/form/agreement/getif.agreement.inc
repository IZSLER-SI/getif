<?php

/**
 * Theme muova/modifica convenzione
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_agreement_form($variables){
    $module_path = drupal_get_path('module', 'getif');
    $full_path = $module_path .'/css/getif.css';
    drupal_add_css($full_path);
    $form = $variables['form'];
    $wizard = check_wizard();
    $header_content = array();
    if ($wizard) {
        $header_content[]['html'] = get_internship_new_header($wizard);
    }
    $options = array();

    if (arg(1) == 'new') {
        $options['page_title'] = 'Nuova Convenzione';

    } elseif (arg(1) == 'edit') {
        $options['page_title'] = t('Modifica Convenzione').': '.$form['fs_agreement']['number_code']['#default_value'];
    }
    return getif_form_theme($form,null,$options);
}

/**
 * Form nuova/modifica convenzione
 * @param $form
 * @param $form_state
 * @return mixed
 * @throws InvalidMergeQueryException
 */
function agreement_form($form, &$form_state) {
    $check_wizard = check_wizard();
    $controller = $form_state["build_info"]["args"][0];
    $form_state['controller'] = $controller;
    if ($controller == "new") {
        if ($check_wizard) {
            $new_internship_1 = session_get('new_internship_1');
            $form_state_values['promoter'] = $new_internship_1['promoter'];
            $form_state_values['promoter_id'] = $new_internship_1['promoter_id'];
            $form_state_values['host'] = $new_internship_1['host'];
            $form_state_values['host_id'] = $new_internship_1['host_id'];
            $form['nav']['back'] = array(
                '#type' => 'button',
                '#value' => t('Indietro'),
                '#limit_validation_errors' => array(),
                '#validate' => array('back_wizard_submit'),
                '#weight' => 3
            );
        }
        if (!empty(session_get('new_agreement'))) {
            $form_state_values = session_get('new_agreement');
            unset($_SESSION['new_agreement']);
        }
    } elseif($controller == "edit" ) {
        $id_agreement = $form_state["build_info"]["args"]["1"];
        $form_state['id_agreement'] = $id_agreement;
        $agreement = getAgreementsById('getif_data', $id_agreement);
        $form_state_values = $agreement;
        $form_state_values['date_application'] = $agreement['date_application'];
        $form_state_values['date_start'] = $agreement['date_start'];
        $form_state_values['date_end'] = $agreement['date_end'];
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
        '#value' => t('Convenzioni'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'agreement'
        ),
    );
    $form['fs_agreement'] = array(
        '#type' => 'container',
        '#title' => t('Dati anagrafici Convenzione'),
        '#prefix' => '<div id="fs-agreement-div">'
    );

    // Soggetto ospitante
    $host = getRecordById('lperson','getif_data', 1);
    $form['fs_agreement']['host'] = array(
        '#type' => 'textfield',
        '#title' => t('Soggetto Ospitante'),
        '#description' => t('Selezionare un Soggetto Ospitante inserendo ragione sociale, p.iva o codice fiscale'),
        '#default_value' => $host->name,
        '#required' => $required,
        '#attributes' => array(
            'disabled' => ''
        )
    );
    $form['fs_agreement']['host_id'] = array(
        '#type'  => 'hidden',
        '#value' => $host->id_lperson,
        '#attributes' => array(
            'id' => 'host_id',
        ),
    );
    // Soggetto promotore
    $form['fs_agreement']['promoter'] = array(
        '#type' => 'textfield',
        '#title' => t('Soggetto Promotore'),
        '#name' => 'promoter',
        '#id' => 'edit-promoter',
        '#description' => t('Selezionare un Soggetto Promotore inserendo ragione sociale, p.iva o codice fiscale'),
        '#required' => $required,
    );
    $form['fs_agreement']['promoter_id'] = array(
        '#type'  => 'hidden',
        '#attributes' => array(
            'id' => 'promoter_id',
        ),
    );

    if (check_wizard() == false) { // se non provengo da nuovo_tirocinio_1
        $form['fs_agreement']['promoter']['#autocomplete_path'] = 'lperson_lprole_autocomplete_callback/1';
        $form['fs_agreement']['host']['#autocomplete_path'] = 'lperson_lprole_autocomplete_callback/2';
    } else {
        $form['fs_agreement']['host']['#disabled'] = true;
        $form['fs_agreement']['promoter']['#disabled'] = true;
    }
    // tipo di tirocini permessi dalla Convenzione
    $form['fs_agreement']['internship_type'] = array(
        '#type' => 'select',
        '#title' => t('Tipo Tirocinio'),
        '#description' => t('Selezionare il tipo di tirocinio regolamentato dalla Convenzione'),
        '#options' => array('1'=>'curricolare','2'=>'extracurricolare','3'=>'curriculari / extracurriculari'),
        '#empty_option' => t('- select an internship type -'),
        '#attributes' => array('check_for_draft_save'=> 'yes'),
        '#required' => $required
    );
    // Numero IZSLER
    $form['fs_agreement']['number_code'] = array(
        '#type' => 'textfield',
        '#title' => t('Numero IZSLER'),
        '#description' => t('Inserire il codice IZSLER che identifica la Convenzione'),
        '#required' => $required,
        '#size' => 64,
        '#attributes' => array(
            'maxlength' => '64'
        )
    );
    // ALTRI DATI
    $form['fs_data'] = array(
        '#type' => 'container',
        '#title' => t('Dates'),
    );
    // Data di registrazione convenzione
    $form['fs_data']['date_application'] = array(
        '#type' => 'textfield',
        '#title' => t('Data di registrazione convenzione'),
        '#description' => t('Inserire la data di registrazione della convenzione'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_application'
        )
    );
    // Data di avvio convenzione - dipende dalla data di registrazione
    $form['fs_data']['date_start'] = array(
        '#type' => 'textfield',
        '#title' => t('Data di inizio convenzione'),
        '#description' => t('Inserire la data di inizio della convenzione'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_start'
        ),
    );
    // Data di fine convenzione - dipende dalla data di registrazione e dalla data di avvio
    $form['fs_data']['date_end'] = array(
        '#type' => 'textfield',
        '#title' => t('Data di fine convenzione'),
        '#description' => t('Inserire la data di fine della convenzione'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_end',
            //'maxDuration' => 12
        )
    );
    // ALLEGATI
    $form['fs_attachment'] = array(
        '#type' => 'container',
        '#title' => t('Allegati'),
    );
    $form['fs_attachment']['attachment_container'] = array(
        '#type' => 'container',
        '#weight' => 0,
        '#tree' => TRUE,
        '#prefix' => '<div id="js-ajax-attachment-wrapper">',
        '#suffix' => '</div>'
    );
    $form['fs_attachment']['attachments'] = array(
        '#type' => 'plupload',
        '#title' => t('Upload files'),
        '#description' => t('Allegare uno o più documenti relativi alla Convenzione'),
        '#autoupload' => FALSE,
        '#autosubmit' => FALSE,
        '#submit_element' => '#id-of-your-submit-element',
        '#progress_indicator' => 'bar',
        '#upload_location'    => "public://tmp/",
        '#upload_validators' => array(
            'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS,
            //'file_validate_size' => 5 * 1024 * 1024,
        ),

    );
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Salva'),
        '#attributes' => array(
            'is_wizard' => $check_wizard,
            'controller' => $controller
        )
    );

    if ($controller == "new") {
        $form['fs_attachment']['#access'] = true;
        $form['actions']['submit']['#value'] = t('Salva');
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Conferma e prosegui.")){return false;}';
    } elseif ($form_state['controller'] == 'edit') {
        $num_internships = count(getAllRecordByField('internship_agreement','getif_data','id_agreement',$id_agreement));
        $is_expired = getDaysDiff(date("Y-m-d"),$agreement['date_end']) < 0?true:false;
        $has_internships = $num_internships > 0?true:false;
        $blocked = $is_expired || $has_internships;
        db_set_active('getif_data');
        $query = db_select('agreement_attachment', 't1');
        $query->fields('t1');
        $query->condition('t1.id_agreement', $id_agreement, '=');
        $query->condition('t1.active', '1', '=');
        $results = (array)$query->execute()->fetchAllAssoc('id_agreement_attachment', PDO::FETCH_ASSOC);
        db_set_active();
        $rows = array();
        $attachments = array();
        foreach ($results as $result) {
            $query = db_select('file_managed', 't1');
            $query->fields('t1', array('fid', 'filename', 'uri','filemime','filesize'));
            //$query->condition('t1.status',FILE_STATUS_PERMANENT,'<>');
            $query->condition('t1.fid', $result['id_file_managed'], '=');
            $attachments[$result['id_agreement_attachment']] = $query->execute()->fetchAssoc();
            $attachments[$result['id_agreement_attachment']]['meta'] = $result['meta'];
        }

        foreach ($attachments as $id_agreement_attachment => $attachment) {
            $form['download_agreement_attachment_' . $id_agreement_attachment] = array(
                '#type' => 'button',
                '#name' => 'download_agreement_attachment_' . $id_agreement_attachment,
                '#value' => 'Download',
                '#validate' => array('download_agreement_attachment_submit'),
                '#id' => 'edit-download-agreement-attachment-' . $id_agreement_attachment,
                '#attributes' => array(
                    'id' => 'edit-download-agreement-attachment-' . $id_agreement_attachment,
                    'id_agreement_attachment' => $id_agreement_attachment,
                    'fid' => $attachment['fid'],
                ),
                '#limit_validation_errors' => array(array('attachment_container')),
            );
            $form['download_agreement_attachment_' . $id_agreement_attachment] = ajax_pre_render_element($form['download_agreement_attachment_' . $id_agreement_attachment]);


            $form['remove_agreement_attachment_' . $id_agreement_attachment] = array(
                '#type' => 'button',
                '#name' => 'remove_agreement_attachment_' . $id_agreement_attachment,
                '#value' => 'Elimina',
                '#validate' => array('remove_agreement_attachment_submit'),
                '#id' => 'edit-remove-agreement-attachment-' . $id_agreement_attachment,
                '#attributes' => array(
                    'id' => 'edit-remove-agreement-attachment-' . $id_agreement_attachment,
                    'id_agreement_attachment' => $id_agreement_attachment,
                    'fid' => $attachment['fid'],
                ),
                '#ajax' => array(
                    'callback' => 'update_attachment_callback',
                    'wrapper' => 'js-ajax-attachment-wrapper',
                ),
                '#limit_validation_errors' => array(array('attachment_container')),
                '#access' => $blocked?false:true
            );
            $form['remove_agreement_attachment_' . $id_agreement_attachment] = ajax_pre_render_element($form['remove_agreement_attachment_' . $id_agreement_attachment]);
            // extension: pathinfo($attachment['uri'])['extension'],
            $rows[] = array(
                $attachment['fid'],
                $attachment['filename'],
                formatBytes($attachment['filesize']),
                drupal_render($form['download_agreement_attachment_' . $id_agreement_attachment]).
                ($blocked?'':drupal_render($form['remove_agreement_attachment_' . $id_agreement_attachment]))
            );

        }

        $header = array(t('ID'), t('Nome del file'), t('Dimensioni File'),t('AZIONI'));
        //$directoryname = 'attached/agreement/' . $id_agreement;
        $form['fs_attachment']['attachment_container']['table'] = array
        (
            '#type' => 'tableselect',
            '#header' => $header,
            '#options' => $rows,
            '#empty' => t('Nessun allegato in lista')
        );
        /* Blocca modifiche Convenzione se ci sono tirocini associati o è scaduta*/

        if ($blocked) {
            /* Blocca modifica Promotore */
            $form['fs_agreement']['promoter']['#disabled'] = TRUE;
            /* Bloccca modifica Ospitante */
            $form['fs_agreement']['host']['#disabled'] = TRUE;
            $form['fs_agreement']['internship_type']['#disabled'] = TRUE;

            if ($has_internships)
                $form['fs_agreement']['#prefix'] =
                    '<div class="col-md-12 alert error">La Convenzione ha associati '.$num_internships.' Tirocini'.($num_internships==1?"o":"").' e non pu&ograve; essere modificata.</div>'
                    .$form['fs_agreement']['#prefix'];
            else
                $form['fs_agreement']['#prefix'] =
                    '<div class="col-md-12 alert error">La Convenzione &egrave; scaduta ed non pu&ograve; essere modificata.</div>'
                    .$form['fs_agreement']['#prefix'];
            $form['fs_agreement']['number_code']['#disabled'] = TRUE;
            $form['fs_data']['date_application']['#disabled'] = TRUE;
            $form['fs_data']['date_start']['#disabled'] = TRUE;
            unset($form['actions']['submit']['#attributes']['onclick']);
        } else {

            $form['fs_data']['date_end_ajax_wrapper']['date_end']['#disabled'] = false;
        }
        $form['actions']['submit']['#value'] = t('Salva');
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler aggiornare?")){return false;}';
    }



    if (!empty($form_state_values)) {
        $form['fs_agreement']['promoter']['#default_value'] = !empty($form_state_values['promoter'])?$form_state_values['promoter']:'';
        $form['fs_agreement']['host']['#default_value'] = !empty($form_state_values['host'])?$form_state_values['host']:'';
        $form['fs_agreement']['promoter_id']['#value'] = !empty($form_state_values['promoter_id'])?$form_state_values['promoter_id']:'';
        $form['fs_agreement']['host_id']['#value'] = !empty($form_state_values['host_id'])?$form_state_values['host_id']:'';
        $form['fs_agreement']['internship_type']['#default_value'] = !empty($form_state_values['internship_type'])?$form_state_values['internship_type']:'';
        $form['fs_agreement']['number_code']['#default_value'] = !empty($form_state_values['number_code'])?$form_state_values['number_code']:'';
        if (!empty($form_state_values['date_application'])) {
            $form['fs_data']['date_application']['#default_value'] = date("d-m-Y",strtotime($form_state_values['date_application']));
        }
        if (!empty($form_state_values['date_start'])) {
            $form['fs_data']['date_start']['#default_value'] = date("d-m-Y",strtotime($form_state_values['date_start']));
        }
        if (!empty($form_state_values['date_end'])) {
            $form['fs_data']['date_end']['#default_value'] = date("d-m-Y",strtotime($form_state_values['date_end']));
        }
    }
    return $form;
}

/**
 * @return bool|int
 */
function check_wizard() {

    if (isset($_SESSION['prev'])) {
        if ($_SESSION['prev'] == "internship/new/1") {
            return 1;
        } else {
            return false;
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
        drupal_goto('agreement/new');
    } elseif ($controller == 'view') {
        if ($is_wizard) {
            getif_goto($_SESSION['prev'],array(),302,true);
        } else {
            drupal_goto('agreement/list');
        }
    } elseif ($controller == 'edit') {
        drupal_goto('agreement/list');
    }
}

/**
 * @param $form
 * @param $form_state
 */
function back_wizard_submit($form, &$form_state) {
    $back_url = $_SESSION['prev'];
    getif_goto($back_url,array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function agreement_form_validate($form, &$form_state) {
    // Controllo Numero IZSLER Convenzione
    if (!empty($form['fs_agreement']['number_code'])) {
        $agreement_cmp = getRecordByField('agreement', 'getif_data', 'number_code', $form_state['values']['number_code']);
        if (!empty($agreement_cmp)) {
            if($form_state['controller'] == 'new') {
                form_set_error('number_code', t('Esiste già una convenzione con questo Numero IZSLER.'));
            } elseif ($form_state['controller'] == 'edit') {
                if ($form_state['id_agreement'] != $agreement_cmp->id_agreement) {
                    form_set_error('number_code', t('Esiste già una convenzione con questo Numero IZSLER.'));
                }
            }
        }
    }
}

/**
 * @param $form
 * @param $form_state
 */
function agreement_form_submit($form, &$form_state) {
    $controller = $form_state['clicked_button']['#attributes']['controller'];
    if($controller == "new") {
        unset($_SESSION['new_agreement']);
        $id_agreement = save($form, $form_state);
        if (check_wizard()) {
            $_SESSION['new_internship_1']['promoter'] = $form_state['values']['promoter'];
            $_SESSION['new_internship_1']['promoter_id'] = $form_state['values']['promoter_id'];
            $_SESSION['new_internship_1']['host'] = $form_state['values']['host'];
            $_SESSION['new_internship_1']['host_id'] = $form_state['values']['host_id'];
            $_SESSION['new_internship_1']['agreement'] = $id_agreement;
            $_SESSION['agreement_new_wizard'] = $id_agreement;
            drupal_set_message(t("Dati inseriti con successo"));
            getif_goto('internship/new/1', array(), 302, true);
        } else {
            drupal_set_message(t("Dati inseriti con successo"));
            drupal_goto('agreement/list');
        }
    } elseif ($form_state["build_info"]["args"][0] == "edit") {
        edit($form, $form_state, $form_state["build_info"]["args"][1]);
        drupal_set_message(t("Dati aggiornati con successo"));
    }


}

/**
 * @param $form
 * @param $form_state
 * @return DatabaseStatementInterface|int
 */
function save($form, &$form_state) {
    try {
        db_set_active('getif_data');
        $query = db_insert('agreement');
        $id_agreement = $query -> fields(array(
            'id_host' => $form_state['values']['host_id'],
            'id_promoter' => $form_state['values']['promoter_id'],
            'number_code' => strtoupper($form_state['values']['number_code']),
            'date_application' => date("Y-m-d", strtotime($form_state['values']['date_application'])),
            'date_start' => date("Y-m-d", strtotime($form_state['values']['date_start'])),
            'date_end' => date("Y-m-d", strtotime($form_state['values']['date_end'])),
            'internship_type' => ($form_state['values']['internship_type']),
        ))->execute();
        db_set_active();
        $w_type = 'getif_agreement';
        $w_message = t('Insert item %id');
        $w_variables = array($id_agreement);
        watchdog($w_type, $w_message, $w_variables);
        // Inserisci allegati
        $saved_files = array(); //Array to capture file objects
        $scheme = variable_get('file_default_scheme', 'public') . '://';
        $directoryname = 'attached/agreement/'.$id_agreement; // Directory where images are collected
        $path = $scheme . $directoryname;
        file_prepare_directory($path, FILE_CREATE_DIRECTORY); // Create the folder if it doesn't exist
        if (!empty($form_state['values']['attachments'])) {
            foreach ($form_state['values']['attachments'] as $uploaded_file) {
                if ($uploaded_file['status'] == 'done') {
                    $source = $uploaded_file['tmppath'];
                    $destination = file_stream_wrapper_uri_normalize($path . '/' . $uploaded_file['name']);
                    $destination = file_unmanaged_move($source, $destination, FILE_EXISTS_RENAME);
                    $file = plupload_file_uri_to_object($destination);
                    file_save($file);
                    $saved_files[] = $file;
                    db_set_active('getif_data');
                    $query = db_insert('agreement_attachment');
                    $id_agreement_attachment = $query->fields(array(
                        'id_agreement' => $id_agreement,
                        'id_file_managed' => $file->fid,
                        'date_application' => date("Y-m-d H:i:s", time()),
                        'meta' => $uploaded_file['name']
                    ))->execute();
                    db_set_active();
                    $w_type = 'getif_agreement_attachment';
                    $w_message = t('Insert item %id');
                    $w_variables = array($id_agreement_attachment);
                    watchdog($w_type, $w_message, $w_variables);
                    // Aggiungo un record in file_usage
                    file_usage_add($file, 'getif', 'agreement_attachment', $id_agreement_attachment);
                } else {
                    form_set_error('attachments', "Upload of {$uploaded_file['name']} failed");
                }
            }
        }
        return $id_agreement;
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    return 0;
}

/**
 * @param $form
 * @param $form_state
 * @param $id_agreement
 * @throws Exception
 */
function edit($form, &$form_state, $id_agreement) {
    clean_cron_by_id('agreement',$form_state['id_agreement']);
    db_set_active('getif_data');
    $query = db_update('agreement');
    $fields = array(
        'id_host' => $form_state['values']['host_id'],
        'id_promoter' => $form_state['values']['promoter_id'],
        'number_code' => strtoupper($form_state['values']['number_code']),
        'internship_type' => ($form_state['values']['internship_type']),
        'date_application' => date('Y-m-d',strtotime($form_state['values']['date_application'])),
        'date_start' => date('Y-m-d',strtotime($form_state['values']['date_start'])),
        'date_end' => date('Y-m-d',strtotime($form_state['values']['date_end'])),
        'date_upd' => date("Y-m-d H:i:s", time()));
    $query->fields($fields)->where('id_agreement = '.$form_state['id_agreement'])->execute();
    db_set_active();
    $w_type = 'getif_agreement';
    $w_message = t('Update item %id');
    $w_variables = array('%id'=>$form_state['id_agreement']);
    watchdog($w_type, $w_message, $w_variables);

    // Inserisci allegati
    $saved_files = array(); //Array to capture file objects
    $scheme = variable_get('file_default_scheme', 'public') . '://';
    $directoryname = 'attached/agreement/'.$id_agreement; // Directory where images are collected
    $path = $scheme . $directoryname;
    file_prepare_directory($path, FILE_CREATE_DIRECTORY); // Create the folder if it doesn't exist

    foreach ($form_state['values']['attachments'] as $uploaded_file) {
        if ($uploaded_file['status'] == 'done') {
            $source = $uploaded_file['tmppath'];
            $destination = file_stream_wrapper_uri_normalize($path . '/' . $uploaded_file['name']);
            $destination = file_unmanaged_move($source, $destination, FILE_EXISTS_RENAME);
            $file = plupload_file_uri_to_object($destination);
            file_save($file);
            $saved_files[] = $file;
            db_set_active('getif_data');
            $query = db_insert('agreement_attachment');
            $id_agreement_attachment = $query -> fields(array(
                'id_agreement' => $id_agreement,
                'id_file_managed' => $file->fid,
                'date_application' => date("Y-m-d H:i:s", time()),
                'meta' => $uploaded_file['name']
            ))->execute();
            db_set_active();
            // Aggiungo un record in file_usage
            file_usage_add($file, 'getif','agreement_attachment',$id_agreement_attachment);
            $w_type = 'getif_agreement_attachment';
            $w_message = t('Insert item %id');
            $w_variables = array('%id'=>$id_agreement_attachment);
            watchdog($w_type, $w_message, $w_variables);
        } else {
            form_set_error('attachments', t("Upload of file {$uploaded_file['name']} failed"));
        }
    }
}

/**
 * @param $form
 * @param $form_state
 */
function download_agreement_attachment_submit($form, &$form_state) {
    $id_agreement_attachment = $form_state['clicked_button']['#attributes']['id_agreement_attachment'];
    $fid = $form_state['clicked_button']['#attributes']['fid'];
    $file = file_load($fid);
    file_usage_add($file, 'getif','agreement_attachment',$id_agreement_attachment);
    drupal_goto('download/',array('query' => array('fid' => $fid), 'html' => TRUE));
}

/**
 * @param $form
 * @param $form_state
 */
function remove_agreement_attachment_submit($form, &$form_state) {
    $id_agreement_attachment = $form_state['clicked_button']['#attributes']['id_agreement_attachment'];
    $fid = $form_state['clicked_button']['#attributes']['fid'];
    $fields = array(
        'active' => 0,
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    try {
        db_set_active('getif_data');
        $query = db_update('agreement_attachment');
        $query->fields($fields)->where('id_agreement_attachment = '.$id_agreement_attachment)->execute();
        db_set_active();
        $file = file_load($fid);
        $file->status = 0;
        file_save($file);
        file_usage_add($file, 'getif','agreement_attachment',$id_agreement_attachment);
        drupal_set_message('Elemento eliminato con successo.','status');
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    $form_state['rebuild'] = TRUE;
    $w_type = 'getif_agreement_attachment';
    $w_message = t('Delete item %id');
    $w_variables = array('%id'=>$id_agreement_attachment);
    watchdog($w_type, $w_message, $w_variables);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function update_attachment_callback($form, &$form_state) {
    return $form['fs_attachment']['attachment_container'];
}

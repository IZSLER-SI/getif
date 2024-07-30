<?php

/**
 * Theme sezione gestione tirocinio
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_internship_manage_form($variables){
    $form = $variables['form'];
    $header_content = array();
    $output = '<div class="panel panel-default">';
    $output .= '
        <ul class="nav nav-tabs" style = "background-color: #f5f5f5;">
            <li class="active"><a href="#panel1" data-toggle="tab">Tirocinante</a></li>
            <li><a href="#panel2" data-toggle="tab">Scheda Ti.1</a></li>
            <li><a href="#panel3" data-toggle="tab">Scheda Ti.2</a></li>
            <li><a href="#panel4" data-toggle="tab">Scheda Ti.3</a></li>
            <li><a href="#panel5" data-toggle="tab">Scheda Ti.4</a></li>
        </ul>
        <div class="tab-content">
            <div id="panel1" class="tab-pane active panel-body ">
               '.drupal_render($form['intern_data']).drupal_render($form['dichiarazione_compatibilita_borsa_di_studio']).'
            </div>
            <div id="panel2" class="tab-pane panel-body ">
               '.drupal_render($form['internship1_data']).drupal_render($form['richiesta_tirocinio']).'
            </div>
            <div id="panel3" class="tab-pane panel-body ">
               '.drupal_render($form['internship2_data']).drupal_render($form['comunicazione_dati_tirocinio']).'
            </div>
            <div id="panel4" class="tab-pane panel-body ">
               '.drupal_render($form['internship3_data']).drupal_render($form['progetto_formativo']).drupal_render($form['parere_favorevole']).'
            </div>
            <div id="panel5" class="tab-pane panel-body ">
               '.drupal_render($form['internship4_data']).'
            </div>
        </div>';
    $output .= '</div>';
    $header_content[] = array('html' => $output,'has_separator' => false);
    $options = array();
    $options['show_fs_title'] = true;
    if (!$form['fs_data']['#access'])
        unset($form['fs_data']);
    if (isset($form['fs_activation']['#access']) && is_bool($form['fs_activation']['#access']) && !$form['fs_activation']['#access']) {
        unset($form['fs_activation']);
    }
    return getif_form_theme($form,$header_content,$options);
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function internship_manage_form($form, &$form_state) {
    $form_state['id_internship'] = !empty($form_state["build_info"]["args"][0])?$form_state["build_info"]["args"][0]:'';
    $internship = getInternshipById('getif_data',$form_state['id_internship'],'active');
    session_set('id_internship',$form_state['id_internship']);
    session_set('internship',$internship);
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
        '#value' => t('Indietro Scheda Ti.4'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back'),
    );
    $form['intern_data'] = array(
        '#markup' => getInternDataByInternshipObj($internship)
    );
    $form['internship1_data'] = array(
        '#markup' => getInternship1DataByInternshipObj($internship)
    );
    $form['internship2_data'] = array(
        '#markup' => getInternship2DataByInternshipObj($internship)
    );
    $form['internship3_data'] = array(
        '#markup' => getInternship3DataByInternshipObj($internship)
    );
    $form['internship4_data'] = array(
        '#markup' => getInternship4DataByInternshipObj($internship)
    );
    foreach ($internship->attachments AS $meta => $attachment) {
        if ($meta == 'dichiarazione_compatibilita_borsa_di_studio' || $meta == 'richiesta_tirocinio' || $meta == 'comunicazione_dati_tirocinio'  || $meta == 'progetto_formativo' || $meta == 'parere_favorevole') {
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

    $form['fs_internship'] = array(
        '#type' => 'container',
        '#title' => t('Stato Tirocinio'),
    );
    $format = 'd-m-Y';
    $required = true;
    $form['fs_internship']['summary'] = array(
        '#markup' => getInternshipInformation($form_state['id_internship'])
    );

    db_set_active('getif_data');
    $query = db_select('internship_attachment','t1');
    $query->fields('t1');
    $query->condition('t1.id_internship',$internship->id_internship,'=');
    $query->condition('t1.active','1','=');
    $results = (array)$query->execute()->fetchAllAssoc('id_internship_attachment',PDO::FETCH_ASSOC);
    db_set_active();

    $exist_nullaosta = FALSE;
    $exist_allegato_b = FALSE;
    $rows = array();
    foreach($results as $result) {
        $query = db_select('file_managed','t1');
        $query->fields('t1',array('fid','filename','uri','filemime','filesize'));
        $query->condition('t1.fid',$result['id_file_managed'],'=');
        $attachments[$result['id_internship_attachment']] = $query->execute()->fetchAssoc();
        $attachments[$result['id_internship_attachment']]['meta'] = $result['meta'];
        if ($result['meta'] == "nulla_osta") {
            $exist_nullaosta = TRUE;
        } elseif ($result['meta'] == "allegato_b") {
            $exist_allegato_b = TRUE;
        }
    }
    if (!empty($attachments)) {
        foreach ($attachments as $id_internship_attachment => $attachment) {
            $form['download_attachment_' . $id_internship_attachment] = array(
                '#type' => 'button',
                '#name' => 'download_attachment_' . $id_internship_attachment,
                '#value' => 'Download',
                '#validate' => array('download_attachment_submit'),
                '#id' => 'edit-download-agreement-attachment-' . $id_internship_attachment,
                '#attributes' => array(
                    'id' => 'edit-download-agreement-attachment-' . $id_internship_attachment,
                    'id_internship_attachment' => $id_internship_attachment,
                    'fid' => $attachment['fid'],
                ),
                '#limit_validation_errors' => array(array('attachment_container')),
            );
            $form['download_attachment_' . $id_internship_attachment] = ajax_pre_render_element($form['download_attachment_' . $id_internship_attachment]);


            $rows[] = array(
                $attachment['fid'],
                _strformat(str_replace('_', ' ', $attachment['meta'])),
                $attachment['filename'],
                formatBytes($attachment['filesize']),
                drupal_render($form['download_attachment_' . $id_internship_attachment])
            );
        }
    }

    $header = array(t('ID'),t('Tipo Documento'),t('Nome del file'),t('Dimensioni'),t('AZIONI'));

    $form['fs_activation'] = array(
        '#type' => 'container',
        '#title' => t('Documenti'),
        '#access' => false
    );
    if($internship->internship_state->state == 4) {
        if (!empty($internship->internship_state->date_start)) {
            $form['fs_activation']['#access'] = true;
        }
        $form['fs_activation']['place'] = array (
            '#type' => 'textfield',
            '#title' => t('Luogo'),
            '#size' => 30,
            '#required' => true
        );
        $form['fs_activation']['date'] = array(
            '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
            '#title' => t('Data'),
            '#date_format' => $format,
            '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
            '#date_timezone' => date_default_timezone(), // Optional, if your date has a timezone other than the site timezone.
            '#date_increment' => 15, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.
            '#datepicker_options' => array(), // Optional, as of 7.x-2.6+, used to pass in additional parameters from the jQuery Datepicker widget.
            '#size' => 8,
            '#attributes' => array(
                'autocomplete' => 'off',
                'class' => array('js-date')
            ),
            '#default_value' => date("Y-m-d"),
            '#required' => true
        );
        $form['fs_activation']['cperson']= array(
            '#type' => 'textfield',
            '#title' => t('Firmatario documenti'),
            '#description' => t('Selezionare un firmatario'),
            '#autocomplete_path' => 'person_signatory_list_autocomplete_by_lperson_position_callback/'.GETIF_HOST,
            '#required' => true,

        );
        $form['fs_activation']['cperson_id'] = array(
            '#type'  => 'hidden',
            '#weight' => 2,
            '#attributes'=>array(
                'id'   => 'edit-cperson_id'
            )
        );
        $form['fs_activation']['genera_nulla_osta'] = array(
            '#type' => 'submit',
            '#value' => 'Genera Nulla Osta',
            '#submit' => array('genera_nulla_osta_submit'),
            '#ajax' => array(
                'callback' => 'genera_nulla_osta_callback',
                'wrapper' => 'attachments-wrapper',
            ),
            '#limit_validation_errors' => array(array('place'),array('date'),array('cperson_id'))
        );
        $form['fs_activation']['genera_allegato_b'] = array(
            '#type' => 'submit',
            '#value' => 'Genera Allegato B',
            '#submit' => array('genera_allegato_b_submit'),
            '#ajax' => array(
                'callback' => 'genera_nulla_osta_callback',
                'wrapper' => 'attachments-wrapper',
            ),
            '#limit_validation_errors' => array(array('place'),array('date'),array('cperson_id'))
        );
        $form['fs_activation']['attachments_wrapper'] = array('#prefix' => '<div id="attachments-wrapper">', '#suffix' => '</div>');
        $form['fs_activation']['attachments_wrapper']['table'] = array
        (
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $rows,
            '#empty' => t('Non è presente nessun allegato!'),
            '#prefix' => '<br/>',
            '#suffix' => '<hr>'
        );

    } elseif ($internship->internship_state->state > 4 || $internship->internship_state->state == 0) {
        $form['fs_activation'] = array(
            '#type' => 'container',
            '#title' => t('Documenti'),
        );
        $form['fs_activation']['attachments_wrapper']['table'] = array
        (
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $rows,
            '#empty' => t('Table has no row!'),
        );
    }
    if($internship->internship_state->state == 4) {
        $form_state_values = array(
            'upload_richiesta_tirocinio' => !empty($internship->attachments['richiesta_tirocinio']->id_file_managed)?$internship->attachments['richiesta_tirocinio']->id_file_managed:null,
            'upload_comunicazione_dati' => !empty($internship->attachments['comunicazione_dati_tirocinio']->id_file_managed)?array(
            'fid' => $internship->attachments['comunicazione_dati_tirocinio']->id_file_managed):'',
            'training_project_attachment' => !empty($internship->attachments['progetto_formativo']->id_file_managed)?$internship->attachments['progetto_formativo']->id_file_managed:null,
            'positive_opinion_attachment' => !empty($internship->attachments['parere_favorevole']->id_file_managed)?$internship->attachments['parere_favorevole']->id_file_managed:null
        );
        // Allegato Richiesta Tirocinio
        $form['fs_activation']['attachments_wrapper']['upload_richiesta_tirocinio'] = array(
            '#type' => 'managed_file',
            '#title' => 'Richiesta Tirocinio',
            '#suffix' => '<span>' . getRequiredHtml() . '</span>',
            '#progress_message' => t('Please wait...'),
            '#progress_indicator' => 'bar',
            '#description' => t('Click "Browse..." to select an attachment to upload.'),
            '#upload_validators' => array(
                'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
            ),
            '#upload_location' => 'public://attached/internship/'.$form_state['id_internship'].'/'
        );

        if (!empty($form_state_values['upload_richiesta_tirocinio'])) {
            if (!empty($form_state_values['upload_richiesta_tirocinio']['fid']))
                $form['fs_activation']['attachments_wrapper']['upload_richiesta_tirocinio']['#default_value'] = $form_state_values['upload_richiesta_tirocinio']['fid'];
            elseif (is_string($form_state_values['upload_richiesta_tirocinio']))
                $form['fs_activation']['attachments_wrapper']['upload_richiesta_tirocinio']['#default_value'] = $form_state_values['upload_richiesta_tirocinio'];
        }
        // Allegato Comunicazione dei dati del Tirocinio (Allegato "A") IOFZ-002 B
        $form['fs_activation']['attachments_wrapper']['upload_comunicazione_dati'] = array(
            '#type' => 'managed_file',
            '#title' => 'Comunicazione dei dati del Tirocinio (Allegato "A") IOFZ-002 B',
            '#progress_message' => t('Please wait...'),
            '#progress_indicator' => 'bar',
            '#description' => t('Click "Browse..." to select an attachment to upload.'),
            '#upload_validators' => array(
                'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
            ),
            '#upload_location' => 'public://attached/internship/' . $form_state['id_internship'] . '/',
        );
        if (!empty($form_state_values['upload_comunicazione_dati'])) {
            if (!empty($form_state_values['upload_comunicazione_dati']['fid']))
                $form['fs_activation']['attachments_wrapper']['upload_comunicazione_dati']['#default_value'] = $form_state_values['upload_comunicazione_dati']['fid'];
            elseif (is_string($form_state_values['upload_comunicazione_dati']))
                $form['fs_activation']['attachments_wrapper']['upload_comunicazione_dati']['#default_value'] = $form_state_values['upload_comunicazione_dati'];
        }
        // Progetto Formativo
        $form['fs_activation']['attachments_wrapper']['training_project_attachment'] = array(
            '#type' => 'managed_file',
            '#title' => 'Allegato Progetto Formativo',
            '#progress_message' => t('Please wait...'),
            '#progress_indicator' => 'bar',
            '#description' => t('Click "Browse..." to select an attachment to upload.'),
            '#upload_validators' => array(
                'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
            ),
            '#upload_location' => 'public://attached/internship/'.$form_state['id_internship'].'/',
            '#required' => $required
        );
        if (!empty($form_state_values['training_project_attachment'])) {
            if (!empty($form_state_values['training_project_attachment']['fid']))
                $form['fs_activation']['attachments_wrapper']['training_project_attachment']['#default_value'] = $form_state_values['training_project_attachment']['fid'];
            elseif (is_string($form_state_values['training_project_attachment']))
                $form['fs_activation']['attachments_wrapper']['training_project_attachment']['#default_value'] = $form_state_values['training_project_attachment'];
        }
        // Parere favorevole del Dirigente Responsabile della U.O. Ospitante IOFZ-002 E
        $form['fs_activation']['attachments_wrapper']['positive_opinion_attachment'] = array(
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
        if (!empty($form_state_values['positive_opinion_attachment'])) {
            if (!empty($form_state_values['positive_opinion_attachment']['fid']))
                $form['fs_activation']['attachments_wrapper']['positive_opinion_attachment']['#default_value'] = $form_state_values['positive_opinion_attachment']['fid'];
            elseif (is_string($form_state_values['positive_opinion_attachment']))
                $form['fs_activation']['attachments_wrapper']['positive_opinion_attachment']['#default_value'] = $form_state_values['positive_opinion_attachment'];
        }

        // Nullaosta firmato
        $form['fs_activation']['attachments_wrapper']['upload_nulla_osta'] = array(
            '#type' => 'managed_file',
            '#title' => 'Riallega Nulla Osta firmato',
            '#progress_message' => t('Please wait...'),
            '#progress_indicator' => 'bar',
            '#description' => t('Click "Browse..." to select an attachment to upload.'),
            '#required' => $required,
            '#upload_validators' => array(
                'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
            ),
            '#disabled' => $exist_nullaosta==TRUE?FALSE:TRUE,
            '#upload_location' => 'public://attached/internship/'.$form_state['id_internship'].'/'
        );
        // Allegato B firmato
        $form['fs_activation']['attachments_wrapper']['upload_allegato_b'] = array(
            '#type' => 'managed_file',
            '#title' => 'Riallega Allegato B firmato',
            '#progress_message' => t('Please wait...'),
            '#progress_indicator' => 'bar',
            '#description' => t('Click "Browse..." to select an attachment to upload.'),
            '#required' => $required,
            '#upload_validators' => array(
                'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
            ),
            '#disabled' => $exist_allegato_b==TRUE?FALSE:TRUE,
            '#upload_location' => 'public://attached/internship/'.$form_state['id_internship'].'/'
        );
    }
    $form['fs_activation_date'] = array(
        '#type' => 'container',
        '#title' => t('Data di Attivazione')
    );
    $form['fs_activation_date']['date_start'] = array(
        '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
        '#title' => t('Data di avvio effettiva'),
        '#date_format' => $format,
        '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
        '#date_timezone' => date_default_timezone(), // Optional, if your date has a timezone other than the site timezone.
        '#datepicker_options' => array(), // Optional, as of 7.x-2.6+, used to pass in additional parameters from the jQuery Datepicker widget.
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'class' => array('js-date')
        ),
    );
    $form['fs_activation_date']['date_start']['#datepicker_options']['minDate'] = date("d-m-Y", strtotime($internship->date_start));
    $form['fs_activation_date']['date_start']['#datepicker_options']['maxDate'] = date("d-m-Y", strtotime($internship->date_end));
    $form['fs_activation_date']['date_scheduled_end'] = array(
        '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
        '#title' => t('Data di fine prevista'),
        '#date_format' => $format,
        '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
        '#date_timezone' => date_default_timezone(), // Optional, if your date has a timezone other than the site timezone.
        '#datepicker_options' => array(), // Optional, as of 7.x-2.6+, used to pass in additional parameters from the jQuery Datepicker widget.
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'class' => array('js-date')
        ),
    );
    $form['fs_activation_date']['date_scheduled_end']['#datepicker_options']['minDate'] = date("d-m-Y", strtotime($internship->date_start));
    $form['fs_activation_date']['date_scheduled_end']['#datepicker_options']['maxDate'] = date("d-m-Y", strtotime($internship->date_end));
    $form['fs_activation_date']['date_scheduled_end']['#default_value'] = $internship->date_end;

    $form['fs_data'] = array(
        '#type' => 'container',
        '#title' => t('Gestione Tirocinio'),
        '#access' => false,
    );

    // Proroga
    $form['fs_data']['date_extension'] = array(
        '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
        '#title' => t('Data di Proroga'),
        '#title_display' => 'invisible',
        '#date_format' => $format,
        '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
        '#date_timezone' => date_default_timezone(), // Optional, if your date has a timezone other than the site timezone.
        '#access' => false,
        '#prefix' => '<div class="row"></div><div class="container-inline">',
        '#suffix' => '</div>',
        '#attributes' => array(
            'autocomplete' => 'off',
            'class' => array('js-date')
        ),

    );
    $form['fs_data']['date_extension']['#datepicker_options']['minDate'] =  date("d-m-Y", strtotime($internship->date_end));
    $form['fs_data']['date_extension']['#datepicker_options']['maxDate'] = date("d-m-Y", strtotime($internship->agreement->date_end));

    $form['fs_data']['submit_date_extension'] = array(
        '#type' => 'submit',
        '#value' => t('Conferma Proroga'),
        '#submit' => array('submit_date_extension'),
        '#access' => false,
        '#prefix' => '<div class="container-inline">',
        '#suffix' => '</div><div>',
    );
    $form['fs_data']['date_end'] = array(
        '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
        '#title' => t('Data di fine effettiva'),
        '#title_display' => 'invisible',
        '#date_format' => $format,
        '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
        '#date_timezone' => date_default_timezone(), // Optional, if your date has a timezone other than the site timezone.
        '#date_increment' => 15, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.
        '#attributes' => array(
            'autocomplete' => 'off',
            'class' => array('js-date')
        ),
        '#access' => false,
        '#prefix' => '<div class="row"></div><div class="container-inline">',
        '#suffix' => '</div>',
    );
    $form['fs_data']['date_end']['#datepicker_options']['minDate'] = date("d-m-Y", strtotime($internship->date_start));
    $form['fs_data']['date_end']['#datepicker_options']['maxDate'] = date("d-m-Y", strtotime($internship->agreement->date_end));

    $form['fs_data']['submit_date_end'] = array(
        '#type' => 'submit',
        '#value' => t('Conferma Conclusione'),
        '#submit' => array('submit_date_end'),
        '#access' => false,
        '#prefix' => '<div class="container-inline">',
        '#suffix' => '</div><div>',

    );
    $form['fs_data']['date_disable'] = array(
        '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
        '#title' => t('Data di interruzione'),
        '#title_display' => 'invisible',
        '#date_format' => GETIF_FORMAT,
        '#date_label_position' => 'within',
        '#date_timezone' => date_default_timezone(),
        '#attributes' => array(
            'autocomplete' => 'off',
            'class' => array('js-date')
        ),
        '#access' => false,
        '#prefix' => '<div class="row"></div><div class="container-inline">',
        '#suffix' => '</div>'
    );
    $form['fs_data']['date_disable']['#datepicker_options']['minDate'] = date("d-m-Y", strtotime($internship->internship_state->date_start));
    $form['fs_data']['date_disable']['#datepicker_options']['maxDate'] = date("d-m-Y");
    $form['fs_data']['submit_date_disable'] = array(
        '#type' => 'submit',
        '#value' => t('Conferma Interruzione'),
        '#submit' => array('submit_date_disable'),
        '#access' => false,
        '#prefix' => '<div class="container-inline">',
        '#suffix' => '</div><div>',
    );
    $form['fs_data']['submit_calendar'] = array(
        '#markup' => '<div class="row"><hr/></div><div class="container-inline">'.
            t('<a href="@url"><span class="glyphicon glyphicon-edit"></span> Compila registro presenze</a>', array(
                '@url' => url('internship/attendance/'.$internship->id_internship.'/'.date('m',strtotime($internship->internship_state->date_start)).'/'.date('y',strtotime($internship->internship_state->date_start))),
            )).'</div>',
        '#access' => false,
    );

    $noactive_states = array(1,2,3);
    if ($internship->internship_state->state == 0) {
        $form['fs_internship']['state']['#default_value'] = t('Interrotto');
        $form['fs_data']['#access'] = true;
        $form['fs_activation_date']['date_start']['#default_value'] = date("Y-m-d",strtotime($internship->internship_state->date_start));
        $form['fs_activation_date']['date_start']['#attributes']['disabled'] = true;
        $form['fs_activation_date']['date_scheduled_end']['#default_value'] = date("Y-m-d",strtotime($internship->date_end));
        $form['fs_activation_date']['date_scheduled_end']['#attributes']['disabled'] = true;
        $form['fs_data']['date_disable']['#access'] = true;
        $form['fs_data']['date_disable']['#default_value'] = $internship->internship_state->date_end;
        $form['fs_data']['date_disable']['#attributes']['disabled'] = true;
        $form['fs_data']['submit_calendar']['#access'] = true;
        unset($form['fs_data']['date_disable']['#title_display']);
    } elseif (in_array($internship->internship_state->state,$noactive_states)) {
        $form['fs_internship']['state']['#default_value'] = t('Non attivo');
    } elseif ($internship->internship_state->state == 4 && empty($internship->internship_state->date_start)) {
        $form['fs_internship']['state']['#default_value'] = t('Da attivare');
        $form['fs_activation']['#access'] = false;
        $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Conferma data di attivazione'),
            '#submit' => array('submit_date_start'),
            '#limit_validation_errors' => array(array('date_start'),array('date_scheduled_end')),
        );
        $form['actions']['submit']['#attributes']['class'] = array('btn-primary');
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler proseguire? I dati non potranno più essere modificati.")){return false;}';
    } elseif ($internship->internship_state->state == 4 && !empty($internship->internship_state->date_start)) {
        $form['fs_internship']['state']['#default_value'] = t('Da attivare');
        $form['fs_activation_date']['date_start']['#default_value'] = date("Y-m-d",strtotime($internship->internship_state->date_start));
        $form['fs_activation_date']['date_start']['#attributes']['disabled'] = true;
        $form['fs_activation_date']['date_scheduled_end']['#default_value'] = date("Y-m-d",strtotime($internship->date_end));
        $form['fs_activation_date']['date_scheduled_end']['#attributes']['disabled'] = true;
        $form['actions']['activate_submit'] = array(
            '#type' => 'submit',
            '#value' => t('Attiva Tirocinio'),

            '#submit' => array('activate_submit'),
            '#limit_validation_errors' => array(
                array('upload_richiesta_tirocinio'),
                array('upload_comunicazione_dati'),
                array('training_project_attachment'),
                array('positive_opinion_attachment'),
                array('upload_nulla_osta'),
                array('upload_allegato_b'),
                array('date_start'),
                array('date_scheduled_end')
            ),
        );
        $form['actions']['activate_button']['#attributes']['class'] = array('btn-primary');
        $form['actions']['activate_button']['#attributes']['onclick'] = 'if(!confirm("Sei sicuro di voler proseguire? I dati non potranno più essere modificati.")){return false;}';

    } elseif ($internship->internship_state->state == 5) {
        $form['fs_internship']['state']['#default_value'] = t('In corso');
        $form['fs_activation_date']['date_start']['#default_value'] = date("Y-m-d",strtotime($internship->internship_state->date_start));
        $form['fs_activation_date']['date_start']['#attributes']['disabled'] = true;
        $form['fs_activation_date']['date_scheduled_end']['#default_value'] = date("Y-m-d",strtotime($internship->date_end));
        $form['fs_activation_date']['date_scheduled_end']['#attributes']['disabled'] = true;
        $form['fs_data']['#access'] = true;
        if (strtotime($internship->internship_state->date_end_expected) <= strtotime(date("Y-m-d"))) {
            $form['fs_data']['date_end']['#access'] = true;
            $form['fs_data']['date_end']['#default_value'] = $internship->internship_state->date_end_expected;
            $form['fs_data']['date_end']['#attributes']['disabled'] = true;
            $form['fs_data']['submit_date_end']['#access'] = true;
            $form['fs_data']['date_extension']['#access'] = true;
            $form['fs_data']['submit_date_extension']['#access'] = true;
        } else {
            $form['fs_data']['date_disable']['#access'] = true;
            $form['fs_data']['submit_date_disable']['#access'] = true;
        }
        $form['fs_data']['submit_calendar']['#access'] = true;
    } elseif ($internship->internship_state->state == 6) {
        $form['fs_internship']['state']['#default_value'] = t('In corso');
        $form['fs_activation_date']['date_start']['#default_value'] = date("Y-m-d",strtotime($internship->internship_state->date_start));
        $form['fs_activation_date']['date_start']['#attributes']['disabled'] = true;
        $form['fs_activation_date']['date_scheduled_end']['#default_value'] = date("Y-m-d",strtotime($internship->date_end));
        $form['fs_activation_date']['date_scheduled_end']['#attributes']['disabled'] = true;
        $form['fs_data']['#access'] = true;
        if (strtotime($internship->internship_state->date_end_expected) <= strtotime(date("Y-m-d"))) {
            $form['fs_data']['date_end']['#access'] = true;
            $form['fs_data']['date_end']['#default_value'] = $internship->internship_state->date_end_expected;
            $form['fs_data']['date_end']['#attributes']['disabled'] = true;
            $form['fs_data']['submit_date_end']['#access'] = true;
        } else {
            $form['fs_data']['date_disable']['#access'] = true;
            $form['fs_data']['submit_date_disable']['#access'] = true;
        }
        unset($form['fs_data']['date_extension']['#title_display']);
        $form['fs_internship']['state']['#default_value'] = t('Attivo con proroga');
        $form['fs_data']['submit_calendar']['#access'] = true;
    } elseif ($internship->internship_state->state == 7) {
        $form['fs_internship']['state']['#default_value'] = t('Concluso');
        $form['fs_activation_date']['date_start']['#default_value'] = date("Y-m-d",strtotime($internship->internship_state->date_start));
        $form['fs_activation_date']['date_start']['#attributes']['disabled'] = true;
        $form['fs_activation_date']['date_scheduled_end']['#default_value'] = date("Y-m-d",strtotime($internship->date_end));
        $form['fs_activation_date']['date_scheduled_end']['#attributes']['disabled'] = true;
        $form['fs_data']['#access'] = true;
        $form['fs_data']['date_end']['#access'] = true;
        $form['fs_data']['date_end']['#default_value'] = $internship->internship_state->date_end;
        $form['fs_data']['date_end']['#attributes']['disabled'] = true;
        unset($form['fs_data']['date_end']['#title_display']);
        $form['fs_data']['submit_calendar']['#access'] = true;
    }
    return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function go_back ($form, &$form_state) {
    getif_goto('internship/view/4/'.arg(2),array(),302,true);

}

/**
 * @param $form
 * @param $form_state
 */
function internship_manage_form_validate($form, &$form_state) {

}

/**
 * @param $form
 * @param $form_state
 */
function internship_manage_form_submit($form, &$form_state) {
    //empty
}

/**
 * @param $form
 * @param $form_state
 */
function activate_submit($form, &$form_state) {
    global $user;
    $id_internship = $form_state['build_info']['args'][0];
    // Richiesta tirocinio
    if (!empty($form_state['values']['upload_richiesta_tirocinio']))
        save_internship_attachment($id_internship,'richiesta_tirocinio',$form_state['values']['upload_richiesta_tirocinio']);
    // comunicazione_dati_tirocinio
    if (!empty($form_state['values']['upload_comunicazione_dati']))
        save_internship_attachment($id_internship,'comunicazione_dati_tirocinio',$form_state['values']['upload_comunicazione_dati']);
    // Allegato Progetto Formativo
    if (!empty($form_state['values']['training_project_attachment']))
        save_internship_attachment($id_internship,'progetto_formativo',$form_state['values']['training_project_attachment']);
    // Allegato Parere Favorevole
    if (!empty($form_state['values']['positive_opinion_attachment']))
        save_internship_attachment($id_internship,'parere_favorevole',$form_state['values']['positive_opinion_attachment']);
    // nulla osta firmato
    save_internship_attachment($id_internship,'nulla_osta_firmato',$form_state['values']['upload_nulla_osta']);
    // allegato b firmato
    save_internship_attachment($id_internship,'allegato_b_firmato',$form_state['values']['upload_allegato_b']);
    // update stato del tirocinio e data
    try {
        db_set_active('getif_data');
        db_query("UPDATE internship_state SET state = 5, date_start = '".$form_state['values']['date_start']."', date_upd = NOW() WHERE id_internship = ".$id_internship.";");
        db_query("UPDATE internship SET date_end = '".$form_state['values']['date_scheduled_end']."', date_upd = NOW() WHERE id_internship = ".$id_internship.";");
        db_set_active();
        // watchdog
        $w_type = 'getif_'.'internship_state';
        $w_message = t('Update item with id_internship: %id');
        $w_variables = array('%id'=>$id_internship);
        watchdog($w_type, $w_message, $w_variables);
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    // inserisci registro presenze
    $fields = array(
        'id_internship'=> $id_internship,
        'register' => base64_encode('[{}]'),
        'is_closed' => 0,
        'active'    => 1
    );
    $key = array(
        'id_internship'=> $id_internship,
        'active' => 1
    );
    try {
        db_set_active('getif_data');
        $query = db_merge('internship_attendance_sheet');
        $query -> key($key) -> fields($fields) -> execute();
        db_set_active();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    // utente che ha attivato il tirocinio
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
    $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function allega_richiesta_tirocinio_callback($form, &$form_state) {
    $id_internship = $form_state['build_info']['args'][0];
    // Richiesta tirocinio
    // se è stato allegato un file allora lo salva
    if (!empty($form_state['values']['upload_richiesta_tirocinio'])) {
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
                'id_file_managed' => $form_state['values']['upload_richiesta_tirocinio'],
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
            $fid = $form_state['values']['upload_richiesta_tirocinio'];
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
    return $form['fs_activation']['attachments_wrapper'];

}



/**
 * @param $id_internship
 * @param $type
 * @param $upload
 * @throws Exception
 */
function save_internship_attachment($id_internship, $type, $upload) {
    // Salva allegati
    db_set_active('getif_data');
    $query = db_update('internship_attachment');
    $query -> fields(array(
        'active' => 0,
    ))->condition(db_and()->condition('id_internship',$id_internship)->condition('meta',$type,'LIKE'))->execute();
    $query = db_insert('internship_attachment');
    $id_internship_attachment= $query -> fields(array(
        'id_internship' => $id_internship,
        'id_file_managed' => $upload,
        'date_application' => date("Y-m-d H:i:s", time()),
        'meta' => $type,
        'date_upd' => date("Y-m-d H:i:s", time()),
    ))->execute();
    db_set_active();
    // cambio lo stato del file in PERMANENTE
    $fid = $upload;
    $file = file_load($fid);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    // Aggiungo un record in file_usage
    $file = new stdClass();
    $file->fid = $fid;
    file_usage_add($file, 'getif','internship_attachment',$id_internship_attachment);
    return;
}


/**
 * @param $form
 * @param $form_state
 * @throws \PhpOffice\PhpWord\Exception\Exception
 */
function genera_allegato_b_submit($form, &$form_state) {

    global $user;
    $id_internship = $form_state['build_info']['args'][0];
    $internship = getInternshipById('getif_data',$id_internship,'active');
    libraries_load('PHPWord'); // Load library as usual.
    // Creating the new document...
    $phpWord = new \PhpOffice\PhpWord\PhpWord();
    $filename = 'allegato_b_'.$id_internship.'.docx';
    $filepath = variable_get('file_public_path', conf_path() . '/files/attached/internship/');
    $document = $phpWord->loadTemplate($filepath.'allegato_b_tpl.docx');
    // Tirocinante
    $intern_name = _strformat($internship->person->firstname).' '._strformat($internship->person->lastname);
    $document->setValue('intern_name', _strformat($intern_name));
    $document->setValue('intern_tax_code', _strformat($internship->person->tax_code));
    $document->setValue('intern_birthdate', date('d/m/Y',strtotime($internship->person->birthdate)));
    $document->setValue('intern_birthplace', _strformat($internship->person->birthplace));
    $document->setValue('intern_residence_address', ($internship->person->residence_address));
    $document->setValue('intern_domicile_address', !empty($internship->person->domicile_address)?_strformat($internship->person->domicile_address):_strformat($internship->person->residence_address));
    $document->setValue('intern_phone', $internship->person->phone);
    $document->setValue('intern_email_address', strtolower($internship->person->email_address));
    $document->setValue('intern_qualification', _strformat($internship->person->qualification));

    // Dati Tirocinio
    $document->setValue('internship_type', ($internship->internship_type->flg_extra_curricular)?t('extracurricolare'):t('curricolare'));
    // Struttura Proponente
    $promoter_text = '';
    if (!empty($internship->promoter->parent)) {
        $promoter_text .= _strformat($internship->promoter->parent->name);
        if ($internship->promoter->id_lperson != $internship->promoter->parent->id_lperson) {
            $promoter_text .= ' - '._strformat($internship->promoter->name);
        }
    } else {
        $promoter_text .= _strformat($internship->promoter->name);
    }
    $attended_course = json_decode($internship->person->attended_course);
    
    if (!empty($attended_course) && !empty($attended_course->name)) {
        $promoter_text .= ' - ' . $attended_course->name;
    }
    $document->setValue('internship_promoter', $promoter_text);
    // STRUTTURA OGGETTO DELLA FREQUENZA E AUTORIZZAZIONE ALL’ ACCESSO DEI LABORATORI
    $lperson_text = $internship->lperson_primary->name.'</w:t><w:br/><w:t>';

    // Laboratori
    $lperson_location_area_list = array();
    foreach ($internship->lperson_location_area as $lperson_location_area) {
        if ($lperson_location_area->lperson_flg_primary == 1) {
            $lperson_location_area_list[] = $lperson_location_area->name;
        }
    }
    if (!empty($lperson_location_area_list))
        $lperson_text .= 'Laboratori: '.join($lperson_location_area_list,', ');
    $document->setValue('internship_branch',$lperson_text);
    // Motivazione delle Frequenza
    $document->setValue('internship_motivation',$internship->internship_type->description);
    // FLAG
    $meta_flags = json_decode($internship->meta_flags);
    $document->setValue('internship_flg1',($meta_flags->flag1_lprole == 1)?'Sì':'No');
    $document->setValue('internship_flg2',($meta_flags->flag2_lprole == 1)?'Sì':'No');
    $document->setValue('internship_flg3',($meta_flags->flag3_lprole == 1)?'Sì':'No');
    // INIZIO  DEL PERIODO DI FREQUENZA
    $date_start_effective = $internship->internship_state->date_start;
    if (empty($internship->internship_state ->date_end)) {
        $datetime1 = new DateTime($internship->date_start);
        $datetime2 = new DateTime($internship->date_end);
        $interval = $datetime1->diff($datetime2);
        $date_end_effective =$internship->date_end;
    } else {
        $date_end_effective =$internship->internship_state->date_end;
    }

    $document->setValue('internship_date_start', date('d/m/Y',strtotime($date_start_effective)));
    $document->setValue('internship_date_end', date('d/m/Y',strtotime($date_end_effective)));
    $rc_policy = json_decode($internship->insurance->rc_policy);
    $accident_policy = json_decode($internship->insurance->accident_policy);
    $document->setValue('rc_policy_number', 'Compagnia RC: '.$rc_policy->company.' - n. polizza: '.$rc_policy->policy_number);
    $document->setValue('accident_policy_number', 'Compagnia Infortuni: '.$accident_policy->company.' - n. polizza: '.$accident_policy->policy_number);
    $document->setValue('internship_aim', $internship->note);
    // Footer -date
    $document->setValue('place',$form_state['values']['place']);
    $document->setValue('date',date('d/m/Y',strtotime($form_state['values']['date'])));
    // Firmatario
    $cperson_id = explode(',',$form_state['values']['cperson_id']);
    $signatory_position = getRecordById('lib_position', 'getif_data', $cperson_id[1]);
    $document->setValue('posizione_firmatario',strtoupper(_strformat($signatory_position->description)));
    db_set_active('getif_data');
    $query = db_select('person','t1');
    $query->innerJoin('lib_title','t2','t1.id_title = t2.id_title');
    $query->condition('t1.id_person',$cperson_id[0]);
    $query->condition('t1.active',1);
    $query->condition('t2.active',1);
    $query->fields('t1',array('firstname','lastname'));
    $query->addField('t2','name','title');
    $signatory = (object)$query->execute()->fetchAssoc();
    db_set_active();
    $document->setValue('firmatario',strtoupper(_strformat($signatory->title.' '.$signatory->firstname.' '.$signatory->lastname)));
    // Utente responsabile del procedimento
    $user_position = getRecordById('lib_position', 'getif_data',$user->uid);
    $document->setValue('posizione_firmatario',strtoupper(_strformat($user_position->description)));
    db_set_active('getif_data');
    $query = db_select("profilo_utente", "pu");
    $query->innerJoin('person','p','p.id_person = pu.id_person');
    $query->condition('pu.active',1);
    $query->condition('p.active',1);
    $query->fields("p");
    $query->condition('pu.uid', $user->uid, '=');
    $operator = (object)$query->execute()->fetchAssoc();
    db_set_active();
    // Footer - Struttura competente
    $document->setValue('struttura_competente',T_STRUTT_COMPETENTE_ALLB);
    // Footer - Responsabile procedimento
    $document->setValue('operatore','');
    // Sigle header
    $document->setValue('sigle',strtoupper(substr($signatory->firstname,0,1)).strtoupper(substr($signatory->lastname,0,1)).'/'.
        strtolower(substr($operator->firstname,0,1)).strtolower(substr($operator->lastname,0,1))
    );

    $filepath = ('public://attached/internship/'.$id_internship.'/');
    if (!drupal_valid_path($filepath)) { // se non esiste la cartella la crea
        file_prepare_directory($filepath, FILE_CREATE_DIRECTORY);
    }
    $uri = $filepath.$filename;

    $flg_new = false;
    if (!file_exists($uri)) {
        $flg_new = true;
    }
    $document->saveAs($uri);



    // Recupera il file e inseriscilo
    $match = file_scan_directory($filepath,  '/' . $filename . '/', $options = array(), $depth = 0);

    if (!empty($match) && $flg_new) {
        $file = reset($match); //if there is only one file
        $file = file_save((object)array(
            'uid' => $user->uid,
            'filename' => $filename,
            'uri' => $filepath.$filename,
            'status' => FILE_STATUS_PERMANENT,
            'filemime' => file_get_mimetype($file->uri),
        ));
        try {
            db_set_active('getif_data');
            // prima elimino l'allegato precedente
            $query = db_update('internship_attachment');
            $query -> fields(array(
                'active' => 0,
            ))->condition(db_and()->condition('id_internship',$id_internship)->condition('meta','allegato_b','LIKE'))->execute();
            // poi inserisco il nuovo allegato
            $query = db_insert('internship_attachment');
            $query -> fields(array(
                'id_internship' => $id_internship,
                'id_file_managed' => $file->fid,
                'date_application' => date("Y-m-d H:i:s", time()),
                'meta' => 'allegato_b',
                'date_upd' => date("Y-m-d H:i:s", time()),
            ))->execute();
            db_set_active();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }



    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}


/**
 * @param $form
 * @param $form_state
 * @throws \PhpOffice\PhpWord\Exception\Exception
 */
function genera_nulla_osta_submit($form, &$form_state) {
    global $user;
    $id_internship = $form_state['build_info']['args'][0];
    $internship = getInternshipById('getif_data',$id_internship,'active');
    libraries_load('PHPWord'); // Load library as usual.
    // Creating the new document...
    $phpWord = new \PhpOffice\PhpWord\PhpWord();
    $filename = 'nulla_osta_'.$id_internship.'.docx';
    $filepath = variable_get('file_public_path', conf_path() . '/files/attached/internship/');
    $document = $phpWord->loadTemplate($filepath.'nullaosta_tpl.docx');

    // Intestazione
    $document->setValue('place',$form_state['values']['place']);
    $document->setValue('date',date('d/m/Y',strtotime($form_state['values']['date'])));

    // Tirocinante
    $intern_text = 'Gent.le '.
        _strformat($internship->person->title).' '.
        _strformat($internship->person->firstname).' '._strformat($internship->person->lastname).'</w:t><w:br/><w:t>'.
        ((!empty($internship->person->domicile_address) || $internship->person->domicile_address != '')? _strformat($internship->person->domicile_address): _strformat($internship->person->residence_address));
    $document->setValue('recipient_intern', $intern_text);
    // Soggetto Promotore
    $promoter_text = 'Spett.le'.' ';
    if ($internship->promoter->level == 1) { // se è una struttura aggiungo Ragione Sociale
        $promoter_text .= _strformat($internship->promoter->parent->name).'</w:t><w:br/><w:t>';
    }
    $promoter_text .= _strformat($internship->promoter->name).'</w:t><w:br/><w:t>';
    $promoter_text .= _strformat($internship->promoter->address);
    $document->setValue('recipient_promoter', $promoter_text);
    // Responsabile tirocinio e tutor
    $internship->host->persons = array();
    foreach($internship->project_contacts as $key => $project_contact) {
        $internship->host->persons[$project_contact->tax_code] = $project_contact;
        if ($project_contact->flg_primary == "1") {
            $document->setValue('internship_dirigente_responsabile',_strformat($project_contact->title).' '.
                _strformat($project_contact->firstname).' '._strformat($project_contact->lastname));
        }
    }
    foreach($internship->host->tutor as $key => $tutor) {
        $internship->host->persons[$tutor->tax_code] = $tutor;
    }
    $document->cloneRow('recipient_host_persons', count((array)$internship->host->persons));
    $i = 1;
    foreach ($internship->host->persons as $host_person) {
        $host_person_text = 'Gent.le '.
            _strformat($host_person->title).' '.
            _strformat($host_person->firstname).' '._strformat($host_person->lastname).'</w:t><w:br/><w:t>'.
            (!empty($host_person->position)?_strformat($host_person->position).'</w:t><w:br/><w:t>':'').
            _strformat($host_person->lperson_name);
        $document->setValue('recipient_host_persons#'.$i++, $host_person_text);
    }
    // Tipo tirocinio
    $document->setValue('internship_type', ($internship->internship_type->flg_extra_curricular)?t('extracurricolare'):t('curricolare'));
    // Date tirocinio
    $date_start_effective = $internship->internship_state->date_start;
    if (empty($internship->internship_state ->date_end)) {
        $datetime1 = new DateTime($internship->date_start);
        $datetime2 = new DateTime($internship->date_end);
        $interval = $datetime1->diff($datetime2);
        $date_end_effective =$internship->date_end;
    } else {
        $date_end_effective =$internship->internship_state->date_end;
    }
    $document->setValue('internship_date_start', date('d/m/y',strtotime($date_start_effective)));
    $document->setValue('internship_date_end', date('d/m/y',strtotime($date_end_effective)));
    $document->setValue('internship_date_application', date('d/m/y',strtotime($internship->date_application)));

    // Strutture / Laboratori
    $lperson_location_list = array();
    foreach ($internship->lperson as $lperson) {
        $lperson_location_area_list = array();
        foreach ($lperson->lperson_location_area as $lperson_location_area) {
            $lperson_location_area_list[] = $lperson_location_area->name;
        }
        if (empty($lperson_location_area_list)) {
            $lperson_location_list[] .= 'ai laboratori di ' . $lperson->name;
        } else {
            $lperson_location_list[] .= 'ai laboratori ' . join($lperson_location_area_list, ',') . ' di ' . $lperson->name;
        }

    }

    $document->setValue('internship_lperson_location_area',join($lperson_location_list, ', '));
    $document->setValue('promoter_name', _strformat($internship->promoter->name));
    $document->setValue('host_name', _strformat($internship->host->name));
    $document->setValue('promoter_departement_name', _strformat($internship->promoter->departement->name));
    $document->setValue('promoter_departement_address', _strformat($internship->promoter->departement->address));

    // Firmatario
    $cperson_id = explode(',',$form_state['values']['cperson_id']);
    $signatory_position = getRecordById('lib_position', 'getif_data', $cperson_id[1]);
    $document->setValue('posizione_firmatario',strtoupper(_strformat($signatory_position->description)));
    db_set_active('getif_data');
    $query = db_select('person','t1');
    $query->innerJoin('lib_title','t2','t1.id_title = t2.id_title');
    $query->condition('t1.id_person',$cperson_id[0]);
    $query->condition('t1.active',1);
    $query->condition('t2.active',1);
    $query->fields('t1',array('firstname','lastname'));
    $query->addField('t2','name','title');
    $signatory = (object)$query->execute()->fetchAssoc();
    db_set_active();
    $document->setValue('firmatario',strtoupper(_strformat($signatory->title.' '.$signatory->firstname.' '.$signatory->lastname)));
    // Utente responsabile del procedimento
    $user_position = getRecordById('lib_position', 'getif_data',$user->uid);
    $document->setValue('posizione_firmatario',strtoupper(_strformat($user_position->description)));
    db_set_active('getif_data');
    $query = db_select("profilo_utente", "pu");
    $query->innerJoin('person','p','p.id_person = pu.id_person');
    $query->condition('pu.active',1);
    $query->condition('p.active',1);
    $query->fields("p");
    $query->condition('pu.uid', $user->uid, '=');
    $operator = (object)$query->execute()->fetchAssoc();
    db_set_active();
    // Footer - Struttura competente
    $document->setValue('struttura_competente',T_STRUTT_COMPETENTE_ALLB);
    // Footer - Responsabile procedimento
    $document->setValue('operatore','');
    // Sigle header
    $document->setValue('sigle',strtoupper(substr($signatory->firstname,0,1)).strtoupper(substr($signatory->lastname,0,1)).'/'.
        strtolower(substr($operator->firstname,0,1)).strtolower(substr($operator->lastname,0,1))
    );

    //
    $filepath = ('public://attached/internship/'.$id_internship.'/');
    if (!drupal_valid_path($filepath)) { // se non esiste la cartella la crea
        file_prepare_directory($filepath, FILE_CREATE_DIRECTORY);
    }
    $uri = $filepath.$filename;
    $flg_new = false;
    if (!file_exists($uri)) {
        $flg_new = true;
    }
    $document->saveAs($uri);
    // Recupera il file e inseriscilo
    $match = file_scan_directory($filepath,  '/' . $filename . '/', $options = array(), $depth = 0);

    if (!empty($match) && $flg_new) {
        $file = reset($match); //if there is only one file
        $file = file_save((object)array(
            'uid' => $user->uid,
            'filename' => $filename,
            'uri' => $filepath.$filename,
            'status' => FILE_STATUS_PERMANENT,
            'filemime' => file_get_mimetype($file->uri),
        ));

        try {
            db_set_active('getif_data');
            // prima elimino l'allegato precedente
            $query = db_update('internship_attachment');
            $query -> fields(array(
                'active' => 0,
                'date_upd' => date("Y-m-d H:i:s", time())
            ))->condition(db_and()->condition('id_internship',$id_internship)->condition('meta','nulla_osta','LIKE'))->execute();
            // poi inserisco il nuovo allegato
            $query = db_insert('internship_attachment');
            $query -> fields(array(
                'id_internship' => $id_internship,
                'id_file_managed' => $file->fid,
                'date_application' => date("Y-m-d H:i:s", time()),
                'meta' => 'nulla_osta',
                'date_upd' => date("Y-m-d H:i:s", time()),
            ))->execute();
            db_set_active();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
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
function genera_nulla_osta_callback($form, &$form_state) {
    return $form['fs_activation']['attachments_wrapper'];

}


/**
 * @param $form
 * @param $form_state
 */
function redirect_submit($form, $form_state) {
    drupal_goto('internship/new/'.((session_get('internship')->internship_state->state)+1).'/'.session_get('id_internship'));
}


/**
 * @param $form
 * @param $form_state
 * @throws InvalidMergeQueryException
 */
function submit_date_start($form, $form_state) {
    clean_cron_by_id('internship',$form_state['id_internship']); // aggiorno le notifiche
    // insert date_start without changing state
    if(!empty($form_state['values']['date_start'])) {
        db_set_active('getif_data');
        $fields = array(
            'date_start' => ($form_state['values']['date_start']),
            'date_upd' => date('Y-m-d H:i:s')
        );
        $cond = array(
            'id_internship' => session_get('id_internship'),
            'active' => 1,
        );
        $query = db_merge('internship_state');
        $query -> key($cond) -> fields($fields) -> execute();
        $fields = array(
            'date_end' => ($form_state['values']['date_scheduled_end']),
            'date_upd' => date('Y-m-d H:i:s')
        );
        $cond = array(
            'id_internship' => session_get('id_internship'),
            'active' => 1,
        );
        $query = db_merge('internship');
        $query -> key($cond) -> fields($fields) -> execute();
        db_set_active();
    }
    drupal_set_message(t("Data di attivazione inserita con successo."));
}


/**
 * @param $form
 * @param $form_state
 * @throws InvalidMergeQueryException
 */
function submit_date_end($form, $form_state) {
    clean_cron_by_id('internship',$form_state['id_internship']); // aggiorno le notifiche
    // insert internship state
    $today = date('Y-m-d H:i:s');
    // insert new internship
    if(!empty($form_state['values']['date_end'])) {
        db_set_active('getif_data');
        $fields = array(
            'date_end' => ($form_state['values']['date_end']),
            'state' => 7
        );
        $cond = array(
            'id_internship' => session_get('id_internship'),
            'active' => 1,
        );
        $query = db_merge('internship_state');
        $id_internship = $query -> key($cond) -> fields($fields) -> execute();
        db_set_active();
    }
}

/**
 * @param $form
 * @param $form_state
 * @throws InvalidMergeQueryException
 */
function submit_date_disable($form, $form_state) {
    clean_cron_by_id('internship',$form_state['id_internship']); // aggiorno le notifiche
    // modify internship state
    if(!empty($form_state['values']['date_disable'])) {
        db_set_active('getif_data');
        $fields = array(
            'date_end' => ($form_state['values']['date_disable']),
            'state' => 0
        );
        $cond = array(
            'id_internship' => session_get('id_internship'),
            'active' => 1,
        );
        $query = db_merge('internship_state');
        $query -> key($cond) -> fields($fields) -> execute();
        db_set_active();
    }
    getif_cron();
}

/**
 * @param $form
 * @param $form_state
 * @throws InvalidMergeQueryException
 */
function submit_date_extension($form, $form_state) {
    clean_cron_by_id('internship',$form_state['id_internship']); // aggiorno le notifiche
    // insert internship state
    $today = date('Y-m-d H:i:s');
    // insert new internship
    if(!empty($form_state['values']['date_extension'])) {
        db_set_active('getif_data');
        $fields = array(
            'date_end' => null,
            'date_extension' => ($form_state['values']['date_extension']),
            'state' => 6
        );
        $cond = array(
            'id_internship' => session_get('id_internship'),
            'state' => 5,
            'active' => 1,
        );
        $query = db_merge('internship_state');
        $id_internship = $query -> key($cond) -> fields($fields) -> execute();
        db_set_active();
    }
}



function submit_registro($form, $form_state) {
    $url = $form_state['clicked_button']['#attributes']['url'];
    drupal_goto($url);
}
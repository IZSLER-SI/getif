<?php

/**
 * Theme sezione nuova frequenza volontaria Scheda FV.1
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_vinternship_1_form($variables){
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
 * Form sezione nuova frequenza volontaria Scheda FV.1
 * @param $form
 * @param $form_state
 * @return mixed
 */
function vinternship_1_form($form, &$form_state) {
    // get arguments
    $form_state['controller'] = $form_state["build_info"]["args"][0];
    if (isset($form_state["build_info"]["args"][1])) {
        $form_state['step'] = $form_state["build_info"]["args"][1];
    }
    $form_state['id_internship'] = !empty($form_state["build_info"]["args"][2]) ? $form_state["build_info"]["args"][2] : '';
    // redirect
    if ($form_state['controller'] == 'view') {
        if (empty($form_state['id_internship'])) {
            getif_goto('vinternship/list');
        }
    }
    if (!empty($form_state['id_internship'])) { // edit
        $internship = getVInternshipById('getif_data', $form_state['id_internship']);
        $form_state_values = array(
            'intern' => $internship->person->firstname . ' ' . $internship->person->lastname . ' (' . $internship->person->tax_code . ')',
            'host' => $internship->host->name,
            'host_id' => $internship->host->id_lperson_lprole,
            'date_application' => $internship->date_application,
            'date_start' => $internship->date_start,
            'date_end' => $internship->date_end,
            'attachment' => !empty($internship->attachments['richiesta_frequenza_volontaria']->id_file_managed)?$internship->attachments['richiesta_frequenza_volontaria']->id_file_managed:null
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
        '#value' => t('Lista frequenze volontarie'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'vinternship'
        )
    );
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Indietro'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back'),
    );

    /* Frequentatore */
    $form['fs_intern'] = array(
        '#type' => 'container',
        '#title' => t('Frequentatore volontario'),
        '#prefix' => '<div id="fs-intern-div">',
        '#suffix' => '</div>',

    );
    // Campo di ricerca frequentatore - visualizza il {Nome} {Cognome} - {Cod.Fisc.}
    $form['fs_intern']['intern'] = array(
        '#type' => 'textfield',
        '#title' => t('Frequentatore'),
        '#description' => t('Selezionare un frequentatore volontario inserendo NOME O COGNOME O COD.FISC oppure creane uno nuovo'),
        '#autocomplete_path' => 'vintern_autocomplete_callback',
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
    // id del frequentatore
    $form['fs_intern']['intern_id'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'id' => 'edit-intern_id'
        )
    );
    // button per andare alla maschera di inserimento di un nuovo frequentatore
    $form['fs_intern']['new_intern_submit'] = array(
        '#type' => 'button',
        '#value' => t('Nuovo Frequentatore'),
        '#limit_validation_errors' => array(),
        '#validate' => array('new_intern_submit'),
        '#attributes' => array(
            'onsubmit' => 'return false'
        ),
    );
    $form['fs_intern']['new_intern_submit']['#attributes']['onkeypress'][] = "jQuery('input').keydown(function(e) {if (e.keyCode == 13) {e.preventDefault(); jQuery('#edit-submit').mousedown();}});";

    /* SOGGETTO OSPITANTE */
    /*CONVENZIONE*/
    $form['fs_agreement'] = array(
        '#type' => 'container',
        '#title' => t('Soggetto Ospitante'),
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
    /* Date Frequenza Volontaria */
    $form['fs_data'] = array(
        '#type' => 'container',
        '#title' => t('Date'),
    );
    // Data di Richiesta dell'interessato
    $form['fs_data']['date_application'] = array(
        '#type' => 'textfield',
        '#title' => t('Data di richiesta dell\'interessato'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date', 'js-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_application'
        )
    );
    // Data di inizio prevista della Frequenza
    $form['fs_data']['date_start'] = array(
        '#type' => 'textfield',
        '#title' => t('Data di inizio frequenza'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date', 'js-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_start'
        ),
    );
    // Data di fine prevista della Frequenza
    $form['fs_data']['date_end'] = array(
        '#type' => 'textfield',
        '#title' => t('Data di fine frequenza'),
        '#required' => $required,
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date', 'js-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_end',
            'maxDuration' => 12
        )
    );

    /* Allegato Richiesta dell'interessato */
    $form['fs_attachment'] = array(
        '#type' => 'container',
        '#title' => t('Allegato richiesta dell\'interessato'),
    );
    $form['fs_attachment']['attachment'] = array(
        '#type' => 'managed_file',
        '#title' => t('Allegato richiesta dell\'interessato'),
        '#title_display' => 'invisible',
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#description' => t('Click "Browse..." to select an attachment to upload.'),
        '#upload_validators' => array(
            'file_validate_extensions' => GETIF_VALIDATE_EXTENSIONS
        ),
        '#upload_location' => 'public://attached/internship/' . (getMaxKey("internship", "getif_data") + 1) . '/',
    );
    /* Submit Button */
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
        $form['actions']['submit']['#attributes']['onclick'] = 'if(!confirm("Conferma e prosegui.")){return false;}';
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
        $form['nav']['submit']['#value'] = t('Prosegui Scheda FV.') . ($form_state['step'] + 1);
        $form['nav']['submit']['#attributes']['controller'] = $form_state['controller'];
        $form['nav']['submit']['#attributes']['step'] = $form_state['step'];
        $form['nav']['submit']['#attributes']['id_internship'] = $form_state['id_internship'];
        $form['nav']['submit']['#attributes']['flg_update'] = false;
        // Button Modifica
        // se lo stato della frequenza è != 0 (Annullato) OR < 5 (5 - attivo OR 6 - attivo con proroga OR 7 - concluso) la funzione di modifica è disponibile:
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
 * @param $form_state
 */
function vinternship_1_form_validate($form, &$form_state) {
    // 1. Controllo che il frequentatore selezionato non abbia altre frequenze e/o tirocini attivi
    if(!empty($form_state['values']['intern_id']) && check_intern_internship_active($form_state['values']['intern_id']) != 0) {
        form_set_error('intern', t('Il frequentatore selezionato ha già una frequenza e/o tirocinio attivo'));
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
            // 4. Controllo durata massima Frequenza: non può durare più di 12 mesi
            if (!empty($form_state['values']['date_start']) && !empty($form_state['values']['date_end'])) {
                if (getMonthsDiff(date("Y-m-d", strtotime($form_state['values']['date_start'])),date("Y-m-d", strtotime($form_state['values']['date_end']))) >= 12) {
                    form_set_error('date_end', t('Il tirocinio non può durare più di 12 mesi.'));
                }
            }
        }
    }
}

/**
 * @param $form
 * @param $form_state
 */
function vinternship_1_form_submit($form, &$form_state) {
    $controller = $form_state['clicked_button']['#attributes']['controller'];
    $destination = '';
    if ($controller == 'new') {
        $id_internship = save($form, $form_state);
        if (empty($id_internship)) {
            drupal_set_message(t("Errore nell'inserimento dei dati. Se il problema persiste contattare l'assistenza."));
            $destination = '';
        } else {
            $destination = 'vinternship/new/2/' . $id_internship;
            unset($_SESSION['new_internship_1']);
            drupal_set_message(t("Dati inseriti con successo"));
        }
    } elseif ($controller == 'view') {
        if ($form_state['clicked_button']['#attributes']['flg_update'] == true) {
            delete_internship_step_data($form_state['id_internship'],$form_state['step']);
            $destination = 'vinternship/new/' . (intval($form_state['step']));
            drupal_set_message(t("Dati eliminati con successo"));
        } else {
            if (getInternshipStateById('getif_data',$form_state['id_internship']) > $form_state['step']) {
                $destination = 'vinternship/view/'.(intval($form_state['step'])+1).'/'.$form_state['id_internship'];
            } else {
                $destination = 'vinternship/new/'.(intval($form_state['step'])+1).'/'.$form_state['id_internship'];
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
    // Inserimento nuova Frequenza Volontaria - table `internship`

    try {
        db_set_active('getif_data');
        $query = db_insert('internship');
        $id_internship = $query->fields(array(
            'flg_voluntary' => '1', // è una frequenza volontaria
            'id_internship_type' => null, // la frequenza volontaria non ha tipo
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
        // Inserimento nuova persona - table `internhsip_person`
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
        // Inserimento stato della frequenza - table `internship_state`
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
        // inserimento allegato - tables `getif_data`.`internship_attachment`
        try {
            if (!empty($form_state['values']['attachment'])) {
                db_set_active('getif_data');
                // 01. Prima elimina l'allegato precedente
                $query = db_update('internship_attachment');
                $query->fields(array(
                    'active' => 0,
                ))->condition(db_and()->condition('id_internship', $id_internship)->condition('meta', 'richiesta_frequenza_volontaria', 'LIKE'))->execute();
                db_set_active();
                // watchdog
                $w_type = 'getif_' . 'internship_attachment';
                $w_message = t('Delete items with id_internship: %id AND meta: %meta');
                $w_variables = array('%id' => $id_internship, '%meta' => 'richiesta_frequenza_volontaria');
                watchdog($w_type, $w_message, $w_variables);

                // 02. Inserisce il nuovo allegato
                db_set_active('getif_data');
                $query = db_insert('internship_attachment');
                $id_internship_attachment = $query->fields(array(
                    'id_internship' => $id_internship,
                    'id_file_managed' => $form_state['values']['attachment'],
                    'date_application' => date("Y-m-d H:i:s", time()),
                    'meta' => 'richiesta_frequenza_volontaria',
                    'date_upd' => date("Y-m-d H:i:s", time()),
                ))->execute();
                db_set_active();
                // watchdog
                $w_type = 'getif_' . 'internship_attachment';
                $w_message = t('Insert item %id');
                $w_variables = array('%id' => $id_internship_attachment);
                watchdog($w_type, $w_message, $w_variables);

                // 03. Cambia lo stato del file in PERMANENTE
                $fid = $form_state['values']['attachment'];
                $file = file_load($fid);
                $file->status = FILE_STATUS_PERMANENT;
                file_save($file);

                // 04. Aggiunge un record in file_usage con contatore ad 1
                $file = new stdClass();
                $file->fid = $fid;
                file_usage_add($file, 'getif', 'internship_attachment', $id_internship_attachment);
            }
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        // Preleva l'utente che ha aperto la pratica
        global $user;
        // Inserisce l'utente che ha aperto la pratica - table internship_user
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
        return $id_internship;
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    return;
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
 * @param $form_state_values
 * @param $form_state
 */
function fill_data(&$form, $form_state_values, &$form_state) {
    // Frequentatore
    $form['fs_intern']['intern']['#title'] = t('Frequentatore');
    $form['fs_intern']['intern']['#default_value'] = !empty($form_state_values['intern'])?_strformat($form_state_values['intern']):'';
    $form['fs_intern']['intern_id']['#value'] = !empty($form_state_values['intern_id'])?$form_state_values['intern_id']:'';
    // Soggetto Ospitante
    $form['fs_agreement']['host']['#default_value'] = !empty($form_state_values['host'])?$form_state_values['host']:'';
    $form['fs_agreement']['host_id']['#value'] = !empty($form_state_values['host_id'])?$form_state_values['host_id']:'';
    // Date
    if (!empty($form_state_values['date_application'])) {
        $form['fs_data']['date_application']['#default_value'] = date("d-m-Y",strtotime($form_state_values['date_application']));
    }
    if (!empty($form_state_values['date_start'])) {
        $form['fs_data']['date_start']['#default_value'] = date("d-m-Y",strtotime($form_state_values['date_start']));
    }
    if (!empty($form_state_values['date_end'])) {
        $form['fs_data']['date_end']['#default_value'] = date("d-m-Y",strtotime($form_state_values['date_end']));
    }
    // Allegato
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
        getif_goto('vinternship/list',array(),302,true);
    } elseif ($form_state['controller'] == 'view') {
        getif_goto('vinternship/list',array(),302,true);
    }
}


/**
 * @param $form
 * @param $form_state
 */
function internship_1_form_update($form, &$form_state) {
    if ($form_state['clicked_button']['#attributes']['flg_update'] == true) {
        delete_vinternship_step_data($form_state['id_internship'], $form_state['step']);
        $destination = 'vinternship/new/' . (intval($form_state['step']));
        drupal_set_message(t("Dati eliminati con successo"));
    } else {
        if (getInternshipStateById('getif_data', $form_state['id_internship']) > $form_state['step']) {
            $destination = 'vinternship/view/' . (intval($form_state['step']) + 1) . '/' . $form_state['id_internship'];
        } else {
            $destination = 'vinternship/new/' . (intval($form_state['step']) + 1) . '/' . $form_state['id_internship'];
        }
    }
    drupal_goto($destination);
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
    getif_goto('vintern/new',array(),302,true);
}
/* end file */
<?php

/**
 * Theme nuovo/modifica utente
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_user_form($variables){
    $form = $variables['form'];
    $header_content = array();
    $options = array();
    if (empty(arg(2))) {
        $options['page_title'] = t('Nuovo utente');
    } else {
        $options['page_title'] = t('Modifica utente').': '.$form['fs_user']['#title'];
    }
    $options['show_fs_title'] = false;
    return getif_form_theme($form,$header_content,$options);
}

/**
 * Form nuovo/modifica utente
 * @param $form
 * @param $form_state
 * @return mixed
 * @throws InvalidMergeQueryException
 */
function user_form($form, &$form_state) {
    global $user;
    $required = true;
    $form_state['controller'] = $form_state["build_info"]["args"][0];
    $form_state['id_utente'] = !empty($form_state["build_info"]["args"][1])?$form_state["build_info"]["args"][1]:null;
    //verifico se esiste il caso
    if(!empty($form_state['id_utente'])){
        $utente = getAllRecordByField('users', 'getif_drupal', 'uid', $form_state['id_utente'], 'status');
        $utente = reset($utente);
        $form['uid'] = array(
            '#type' => 'hidden',
            '#value' => $utente->uid,
            '#attributes' => array('check_for_draft_save'=> 'no'),
        );
        $query = db_select("users_roles", "ur");
        $query->fields("ur", array("rid"));
        $query->condition('ur.uid', $utente->uid, '=');
        $results = $query->execute()->fetchAll();
        $user_roles = array();
        foreach($results AS $role) {
            $user_roles[$role->rid] = $role->rid;
        }
        db_set_active('getif_data');
        $query = db_select("profilo_utente", "pu");
        $query->innerJoin('person','p','p.id_person = pu.id_person');
        $query->innerJoin('lib_title','t','t.id_title = p.id_title');
        $query->fields("p");
        $query->addField("t","name","title");
        $query->condition('pu.uid', $utente->uid, '=');
        $profilo = (object)$query->execute()->fetchAssoc();
        db_set_active();
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
        '#value' => t('Lista utenti'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'guser'
        )
    );
    $form['fs_user'] = array(
        '#type' => 'container',
        '#title' => t('Utente'),
        '#prefix' => '<div id="fs-user-div">',
        '#suffix' => '</div>',
    );
    $form['fs_user']['person']  = array (
        '#type' => 'textfield',
        '#title' => 'Seleziona Persona',
        '#description' => 'Selezionare una persona inserendo nome, cognome o codice fiscale',
        '#autocomplete_path' => 'person_list_autocomplete_callback',
        '#required' => (isset($utente)) ? FALSE : $required,
    );
    $form['fs_user']['person_id'] = array(
        '#type'  => 'hidden',
        '#attributes'=>array(
            'id'   => 'edit-person-id'
        )
    );
    $form['fs_user']['pass'] = array(
        '#type' => 'password_confirm',
        '#description' => t('Inserire la stessa password in entrambi i campi'),
        '#size' => 32,
        '#required' => (isset($utente)) ? FALSE : $required,
    );
    if (in_array('administrator', $user->roles) || in_array('operator', $user->roles) || in_array('operatore', $user->roles)) {
        $roles = array('operatore','tutor');
        $options = array();

        foreach($roles as $role_name) {
            $role = user_role_load_by_name($role_name);
            if ($role_name == 'tutor') {
                $options[$role->rid] = 'tutor/referente';
            } else {
                $options[$role->rid] = $role_name;
            }
        }
        $form['fs_user']['role'] = array(
            '#type' => 'checkboxes',
            '#title' => t('Permessi'),
            '#description' => 'Selezionare uno o più gruppi di permessi da assegnare all\'utente',
            '#options' => $options,
            '#attributes' => array(
                'check_for_draft_save'=> 'yes',
                'data-toggle'=> 'toggle'
            ),
            '#required' => $required,
            '#ajax' => array(
                'event' => 'change',
                'callback' => 'utenti_ajax_callback',
                'wrapper' => 'ajax-wrapper',
            ),
        );
    }
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#description' => t('Salva'),
        '#value' => t('Salva'),
        '#name' => 'submit_line',
        '#validate' => array('utenti_form_validate'),
        '#submit' => array('utenti_form_submit'),
    );
    //se non siamo nella fase di rebuild del form
    if($form_state['rebuild'] == false)
    {
        //metto i valori di default se la baseline_basic_info esiste già
        if(isset($utente)){
            $form['fs_user']['name']['#default_value'] = $utente->name;
            $form['fs_user']['role']['#default_value'] = $user_roles;
            if (!empty($profilo) ){
                $form['fs_user']['person']['#default_value'] = $profilo->title.' '.$profilo->firstname.' '.$profilo->lastname.' ('.$profilo->tax_code.')';
                $form['fs_user']['person_id']['#default_value'] = $profilo->id_person;
                if(!empty(arg(1))) {
                    $form['fs_user']['person']['#disabled'] = 'disabled';
                }
                $form['fs_user']['#title'] = $profilo->firstname.' '.$profilo->lastname;
            }
        }
    }
    return $form;
}

/**
 * @param $form
 * @param $form_state
 * @throws InvalidMergeQueryException
 */
function utenti_form_submit($form, &$form_state){

    global $base_url;
    require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');

    //costruzione dell'array di inserimento/aggiornamento
    $person = getRecordByField('person','getif_data','id_person',$form_state['values']['person_id']);
    $array_dati = array(
        //'name' => clean_user_name($form_state['values']['name']),
        'name' => clean_user_name($person->tax_code),
        'mail' => $person->email_address,
        'status' => 1,
    );

    //caso di aggiornamento
    if(!empty($form_state['values']['uid']))
    {
        // modifica utente
        if (!empty($form_state['values']['pass'])) {
            $array_dati['pass'] = user_hash_password(trim($form_state['values']['pass']));
        }
        $key = array(
            'uid' => $form_state['values']['uid']
        );
        db_merge('users')
            ->key($key)
            ->fields($array_dati)
            ->condition('uid', $form_state['values']['uid'],'=')
            ->execute();
        // modifica user_roles
        foreach($form_state['values']['role'] as $id_role => $is_selected) {
            if ($is_selected == $id_role) {
                $fields = array(
                    'rid' => $id_role,
                );
                $key = array(
                    'rid' => $id_role,
                    'uid' => $form_state['values']['uid'],
                );
                db_merge('users_roles')
                    ->key($key)
                    ->fields($fields)
                    ->condition('uid', $form_state['values']['uid'],'=')
                    ->execute();
            } else {
                db_delete('users_roles')
                    ->condition('uid', $form_state['values']['uid'],'=')
                    ->condition('rid', $id_role,'=')
                    ->execute();
            }
        }
        // modifica profilo utente
        $fields = array(
            'id_person' => (!empty($form_state['values']['person_id'])) ? $form_state['values']['person_id'] : 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
            'active' => 1
        );
        db_set_active('getif_data');
        db_update('profilo_utente')
            ->fields($fields)
            ->condition('uid', $form_state['values']['uid'],'=')
            ->execute();
        db_set_active();
        drupal_set_message(t("Utente modificato con successo"));
    }
    //caso di inserimento
    else {
        $array_dati['uid'] = getMaxKey('users', NULL) + 1;
        $array_dati['pass'] = user_hash_password(trim($form_state['values']['pass']));
        $array_dati['created'] = time();
        $array_dati['timezone'] = 'Europe/Rome';
        try {
            db_insert('users')
                ->fields($array_dati)
                ->execute();
            foreach($form_state['values']['role'] as $id_role => $is_selected) {
                if ($is_selected == $id_role) {
                    db_insert('users_roles')
                        ->fields(array(
                            'uid' => $array_dati['uid'],
                            'rid' => $id_role,
                        ))
                        ->execute();
                }
            }
            try {
                $dati_profilo['uid'] = $array_dati['uid'];
                $dati_profilo['id_person'] = $form_state['values']['person_id'];
                db_set_active('getif_data');
                db_insert('profilo_utente')
                    ->fields($dati_profilo)
                    ->execute();
                db_set_active();
                if (EMAIL_NOTIFY) {
                    // L'utente è inserito da un operatore per effettuare un primo accesso bisogna mandargli un link di accesso
                    $account = user_load($dati_profilo['uid']);
                    $link = user_pass_reset_url($account);
                    $module = 'getif';
                    $key = 'key';
                    $language = language_default();
                    $params = array();
                    $from = NULL;
                    $send = FALSE;
                    $email = $array_dati['mail'];
                    $message = drupal_mail($module, $key, $email, $language, $params, $from, $send);
                    $message['subject'] = 'Creazione Utente Ge.Ti.F.';
                    $message['body'] = array();
                    $message['body'][] = 'Gentile '.clean_user_name($form_state['values']['name']).', abbiamo impostato le tue credenziali di accesso al software di Gestione Tirocini e Frequenze Volontarie Ge.Ti.F.';
                    $message['body'][] = 'Il tuo account di accesso corrisponde all\'indirizzo email: '.$array_dati['mail'];
                    $message['body'][] = 'Prima di tutto dovrai scegliere la password di accesso facendo click sul seguente link oppure copiandolo e incollandolo nella barra degli indirizzi del browser potrai impostare la password.';
                    $message['body'][] =  $link;
                    $message['body'][] = 'Il link può essere usato una sola volta e sarà attivo per 24 ore.';
                    $message['body'][] = 'I successivi accessi che effettuerai avverranno all’indirizzo '.$base_url;
                    $message['body'][] = 'Se hai bisogno di assistenza puoi scrivere un\'e-mail a '.MAINTENANCE_EMAIL;
                    // Retrieve the responsible implementation for this message.
                    $system = drupal_mail_system($module, $key);
                    // Format the message body.
                    $message = $system->format($message);
                    // Send e-mail.
                    $message['result'] = $system->mail($message);
                }
            } catch (Exception $ex) {
                drupal_set_message('Errore: '.$ex,'error');
            }
            drupal_set_message(t("Utente inserito con successo. Un'email è stata inviata all'indirizzo email dell'utente."));
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
    }

    drupal_goto('guser/list');
}

/**
 * @param $form
 * @param $form_state
 */
function utenti_form_validate($form, &$form_state){
    if (!empty($form_state['values']['name'])) {
        $query = db_select('users','u');
        $query->condition('u.name',clean_user_name($form_state['values']['name']),'LIKE');
        if(!empty($form_state['values']['uid'])) { // caso aggiornamento
            $query->condition('u.uid',$form_state['values']['uid'],'<>');
        }
        $query->fields('u');
        $num_users = $query->countQuery()->execute()->fetchField();;
        if ($num_users > 0) {
            form_set_error('nome', 'Il nome utente specificato è già in uso');
        }
    }

    if (empty($form_state['values']['uid'])) {
        db_set_active('getif_data');
        $query = db_select('profilo_utente','pu');
        $query -> fields('pu');
        $query -> condition ('pu.id_person',$form_state['values']['person_id']);
        $query -> condition ('pu.active',1);
        $result = $query->countQuery()->execute()->fetchField();
        db_set_active();
        if ($result > 0) {
            form_set_error('person', 'La persona selezionata ha già un utente associato');
        }

    }

    if (strlen($form_state['values']['pass']) != 0 && strlen($form_state['values']['pass']) < 8) {
        form_set_error('pass', 'La password deve essere lunga almeno 8 caratteri');
    }
}

/** end */
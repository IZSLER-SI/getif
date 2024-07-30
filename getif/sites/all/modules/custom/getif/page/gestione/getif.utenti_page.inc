<?php

/**
 * @return string
 * @throws Exception
 */
function _tabella_utenti() {
    global $user, $base_url;
    $module_path = drupal_get_path('module', 'getif');
    $full_path = $module_path .'/css/getif.css';
    drupal_add_css($full_path);
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    $id_utente = arg(1);
    session_set('id_utente', $id_utente);
    $output = '';
    $output .= '<div class="col-md-12 form-container">';
    $output .= '
    <div class="bootstrap">
        <div class="page-head">
            <div class="wrapper clearfix"><h1 class="page-title">'.drupal_get_title().'</h1>
                <div class="page-bar toolbarBox">
                    <div class="btn-toolbar">
                        <ul id="toolbar-nav" class="nav nav-pills pull-right collapse navbar-collapse">
                            <li>
                                <button id="edit-goto-dashboard" onclick="location.href=\''.$base_url.'\';" value="Dashboard" class="btn btn-default form-submit icon-before">
                                <span class="icon glyphicon glyphicon-dashboard" aria-hidden="true"></span>Dashboard</button>
                            </li>
                        </ul>
                            
                    </div>
                </div>
            </div>
        </div>
    </div>';


    $output .= '<div class="row form-container">
                    <div class="col-sm-12 col-xs-12">';
    $header = array(
        array(
            "data" => t('Utente'),
        ),
        array(
            "data" => t('Username'),
        ),
        array(
            "data" => t('Email'),
        ),
        array(
            "data" => t('Ruolo'),
        ),
        array(
            "data" => t('Status'),
        ),
        array(
            "data" => '&nbsp;',
        ),
    );
    db_set_active('getif_drupal');
    $query = db_query('
      SELECT u.uid, u.name, u.mail, GROUP_CONCAT(ur.rid) as roles FROM `users` as u 
      INNER JOIN users_roles AS ur ON ur.uid = u.uid 
      INNER JOIN role as r ON r.rid = ur.rid where u.status = 1 AND r.rid <> 3 GROUP BY u.uid
    ');
    db_set_active();

    while($result = $query->fetchObject()) {
        // Prende i dati anagrafici della persona associata all'utente

        db_set_active('getif_data');
        $query_person = db_select('profilo_utente','pu');
        $query_person -> innerJoin('person','pe','pe.id_person = pu.id_person');
        $query_person -> innerJoin('lib_title','lt','pe.id_title = lt.id_title');
        $query_person -> fields('pe');
        $query_person -> addField('lt','name','title');
        $query_person -> condition ('pu.uid',$result->uid);
        $query_person -> condition ('pu.active',1);
        $query_person -> condition ('pe.active',1);
        $person = (object)($query_person->execute()->fetchAssoc());
        db_set_active();
        $upd_url = url($base_url . "/utenti/" . $result->uid, array('query' => drupal_get_query_parameters()));
        $del_url = url($base_url . "/delete_record/utenti/" . $result->uid, array('query' => drupal_get_query_parameters()));
        $upd_btn = "<a href='" . $upd_url . "' class='btn btn-sm glyphicon glyphicon-pencil'></a>";
        $del_btn = "<a href='" . $del_url . "' class='btn btn-sm glyphicon glyphicon-trash'></i></a>";
        $roles = array();
        $role_list = explode(',',$result->roles);
        foreach ($role_list as $role) {
            $roles[] = user_role_load($role)->name;
        }
        $account = user_load($result->uid);
        $rows[] = array(
            'data' => array(
                ucwords($person->title.' '.$person->firstname.' '.$person->lastname),
                $result->name,
                $result->mail,
                join($roles,', '),
                $account->status?'<span class="circle_step green" style="font-size: 1.0em;">&nbsp;</span>':'<span class="circle_step" style="font-size: 1.0em;"></span>',
                $upd_btn . $del_btn
            ),
            'class' => ($result->uid === $id_utente) ? array('success') : null,
        );
    }



    $output .= '<fieldset class="panel panel-default form-wrapper" id="edit-fs-users">
                 <legend class="panel-heading">
                    <span class="panel-title fieldset-legend">Utenti</span>
                </legend>
                <div class="panel-body" id="edit-fs-users-body">
                    <div class="table-responsive">';

    $form = drupal_get_form('utenti_page_form');

    $output .= drupal_render($form).'
               
            </div>';
    $output .= '<hr/>';
    $output .= theme_table(
            array(
                "header" => $header,
                "rows" => $rows,
                'attributes' => array('id'=>'tabella', 'class' => array('table', 'table-striped', 'table-hover')),
                "sticky" => false, // Table header will be sticky
                "caption" => "",
                "colgroups" => array(),
                "empty" => t("Table has no row!") // The message to be displayed if table is empty
            )
        ).theme("pager");
    $output .=' </div></fieldset>.</div></div></div>';


    $output .= ' <script>
                jQuery(document).ready(function() {
                    // Setup - add a text input to each footer cell
                   
         
                    var table = jQuery("#tabella").DataTable( {
                        pageLength: 10,
                        "scrollX": false,
                        orderCellsTop: true,
                        fixedHeader: true,
                        columnDefs: [ { orderable: false, targets: [5] } ],
                        "order": [[ 0, "DESC" ]],
                        language: {
                            "emptyTable":     "No",
                            "info":           "Visualizzati da _START_ a _END_ su _TOTAL_ elementi totali",
                            "infoEmpty":      "Nessun record trovato",
                            "infoFiltered":   "(filtrati su _MAX_ elementi totali)",
                            "infoPostFix":    "",
                            "thousands":      ",",
                            "lengthMenu":     "Visualizza _MENU_ record",
                            "loadingRecords": "Caricamento...",
                            "processing":     "Elaborazione...",
                            "search":         "Ricerca:",
                            "zeroRecords":    "Nessun elemento trovato",
                            "paginate": {
                                "first":      "Prima",
                                "last":       "Ultima",
                                "next":       "Successiva",
                                "previous":   "Precedente"
                            }   
                        },
                    } );
                } );
                
                    
            </script>';

    return $output;
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function utenti_page_form($form, &$form_state){

    $uid = 1;
    $account = user_load($uid);
    $link = user_pass_reset_url($account);
    global $user;
    $required = true;
    $id_utente = session_get('id_utente');

    //verifico se esiste il caso
    if(!empty($id_utente)){
        $utente = getAllRecordByField('users', 'getif_drupal', 'uid', $id_utente, 'status');
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

    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Nome utente'),
        '#attributes' => array(
            'check_for_draft_save'=> 'yes',
            'placeholder' => 'Inserire il nome utente',
            'style' => 'display:block;max-width:32.5%',
        ),
        '#prefix' => '<br>',
        '#required' => $required,
        '#size' => 32,

    );

    $form['pass'] = array(
        '#type' => 'password_confirm',
        '#description' => t('Enter the same password in both fields'),
        '#size' => 32,
        '#required' => (isset($utente)) ? FALSE : $required,
    );

    $form['person']  = array (
        '#type' => 'textfield',
        '#title' => 'Seleziona Persona',
        '#autocomplete_path' => 'person_list_autocomplete_callback',
        '#required' => (isset($utente)) ? FALSE : $required,
    );

    $form['person_id'] = array(
        '#type'  => 'hidden',
        '#attributes'=>array(
            'id'   => 'edit-person-id'
        )
    );

    if (in_array('administrator', $user->roles) || in_array('operator', $user->roles) || in_array('operatore', $user->roles)) {
        $roles = array('operatore','tutor');
        $options = array();

        foreach($roles as $role_name) {
            $role = user_role_load_by_name($role_name);
            $options[$role->rid] = $role_name;
        }

        $form['role'] = array(
            '#type' => 'checkboxes',
            '#title' => t('Ruolo'),
            '#options' => $options,
            '#attributes' => array('check_for_draft_save'=> 'yes'),
            '#required' => $required,
            '#ajax' => array(
                'event' => 'change',
                'callback' => 'utenti_ajax_callback',
                'wrapper' => 'ajax-wrapper',
            ),
        );
    }

    $form['submit_line'] = array(
        '#type' => 'submit',
        '#description' => (empty($id_utente)) ? t('Aggiungi') : t('Modifica'),
        '#value' => (empty($id_utente)) ? t('Aggiungi') : t('Modifica'),
        '#name' => 'submit_line',
        '#validate' => array('utenti_form_validate'),
        '#submit' => array('utenti_form_submit'),
        '#attributes' => array('save_type' => 'submit_line'),
    );

    if(!empty($id_utente)){
        $form['undo'] = array(
            '#type' => 'button',
            '#description' => t('Annulla'),
            '#value' => t('Annulla'),
            '#limit_validation_errors' => array(),
            '#validate' => array('go_back_utenti'),
        );
    }

    //se non siamo nella fase di rebuild del form
    if($form_state['rebuild'] == false)
    {
        //metto i valori di default se la baseline_basic_info esiste già
        if(isset($utente)){

            $form['name']['#default_value'] = $utente->name;
            $form['role']['#default_value'] = $user_roles;
            if (!empty($profilo) ){
                $form['person']['#default_value'] = $profilo->title.' '.$profilo->firstname.' '.$profilo->lastname.' ('.$profilo->tax_code.')';
                $form['person_id']['#default_value'] = $profilo->id_person;
                if(!empty(arg(1))) {
                    $form['person']['#disabled'] = 'disabled';
                }
            }
        }
    }

    return $form;
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function utenti_ajax_callback($form, $form_state) {
    return $form['ajax_wrapper'];
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
        'name' => clean_user_name($form_state['values']['name']),
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
            drupal_set_message(t("Utente inserito con successo"));
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
    }

    go_back_utenti();
}

/**
 *
 */
function go_back_utenti() {
    global $base_url;

    drupal_goto(url($base_url . "/utenti", array('query' => drupal_get_query_parameters())));
}

/**
 *
 */
function go_back() {
    drupal_goto("dashboard");
}

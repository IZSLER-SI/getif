<?php

/**
 * Theme lista figure
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_person_list_view_form($variables){
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    $form = $variables['form'];
    $form_filter = '<div class="col-md-3">'.drupal_render($form['filter_panel']['filter_active']).'</div>';
    $form_filter .= '<div class="col-md-3">'.drupal_render($form['filter_panel']['filter_position']).'</div>';
    $form_filter .= '<div class="col-md-3">'.drupal_render($form['filter_panel']['filter_prole']).'</div>';
    $form_filter .= '<div class="col-md-3">'.drupal_render($form['filter_panel']['filter_lperson']).'</div>';
    $form_filter .= '<div class="col-md-12">'.drupal_render($form['filter_panel']['save']).drupal_render($form['filter_panel']['reset']).'</div>';
    $header_content[] = array('html' => $form_filter,'has_separator' => true);
    $options = array();
    $options['show_fs_title'] = false;
    return getif_form_theme($form,$header_content,$options);
}

/**
 * Form lista figure
 * @param $form
 * @param $form_state
 * @return mixed
 */
function person_list_view_form($form, &$form_state) {
    // Top Buttons
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back')
    );
    $form['filter_panel']['filter_active'] = array(
        '#type' => 'select',
        '#title' => 'Stato',
        '#empty_option' => t('- Tutti -'),
        '#options' => array('1'=>'Attivi','2'=>'Disabilitati'),
        '#default_value' => isset($_GET['active'])?$_GET['active']:'',
    );
    $form['filter_panel']['filter_prole'] = array(
        '#type' => 'select',
        '#title' => 'Ruolo',
        '#empty_option' => t('- Tutti i ruoli -'),
        '#options' => getLibOptions('lib_prole','getif_data'),
        '#default_value' => isset($_GET['prole'])?$_GET['prole']:'',
    );
    $form['filter_panel']['filter_position'] = array(
        '#type' => 'select',
        '#title' => 'Posizione',
        '#empty_option' => t('- Tutti le posizioni -'),
        '#options' => getLibOptions('lib_position','getif_data'),
        '#default_value' => isset($_GET['position'])?$_GET['position']:'',
    );
    $form['filter_panel']['filter_lperson'] = array(
        '#type' => 'select',
        '#title' => 'Soggetto',
        '#empty_option' => t('- Tutti i Soggetti -'),
        '#options' => getAllParentLPersons('getif_data'),
        '#default_value' => isset($_GET['lperson'])?$_GET['lperson']:'',
    );

    $form['filter_panel']['save'] = array(
        '#type' => 'submit',
        '#value' => 'Filtra',
        '#prefix' => '<div class="container-inline">',
        '#suffix' => '</div>',
    );
    if (!empty($_GET['active']) || !empty($_GET['position']) || !empty($_GET['prole']) || !empty($_GET['lperson'])) {
        $form['filter_panel']['reset'] = array(
            '#type' => 'submit',
            '#value' => 'Reset',
            '#attributes' => array(
                'reset' => true
            ),
            '#prefix' => '<div class="container-inline">',
            '#suffix' => '</div>',
        );
    }
    $form['nav']['new'] = array(
        '#type' => 'button',
        '#value' => t('Nuova').' '.t('Figura'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_new'),
    );
    $header = array(
        t('ID'),
        t('Nome'),
        t('Cod. Fisc.'),
        t('Titolo di studio'),
        t('Posizioni'),
        t('Ruoli'),
        t('Attivo'),
        t('Azioni')
    );
    db_set_active('getif_data');
    $query = db_select('person', 't1');
    $query->leftJoin('lib_qualification', 't2', 't1.id_qualification = t2.id_qualification AND t2.active = 1');
    // filtri
    if (!empty($_GET['active'])) {
        $query->condition('t1.active', $_GET['active'],'=');

    } else {
        $query->condition('t1.active', array(1,2),'IN');
    }
    if (!empty($_GET['prole'])) {
        $query->innerJoin('person_lperson','t3','t1.id_person = t3.id_person');
        $query->innerJoin('person_lperson_prole','t4','t3.id_person_lperson = t4.id_person_lperson');
        $query->condition('t4.id_prole', $_GET['prole']);
        $query->condition('t3.active', 1);
        $query->condition('t4.active', 1);

    }
    if (!empty($_GET['lperson'])) {
        $query->innerJoin('person_lperson','t5','t1.id_person = t5.id_person');
        $query->innerJoin('lperson','t6','t6.id_lperson = t5.id_lperson');
        $query->where('t6.id_lperson ='.$_GET['lperson'].' OR t6.id_lperson_parent ='.$_GET['lperson']);
        $query->condition('t5.active', 1);
        $query->condition('t6.active', 1);

    }
    if (!empty($_GET['position'])) {
        $query->innerJoin('person_lperson','t7','t1.id_person = t7.id_person');
        $query->innerJoin('person_lperson_position','t8','t7.id_person_lperson = t8.id_person_lperson');
        $query->condition('t8.id_position', $_GET['position']);
        $query->condition('t7.active', 1);
        $query->condition('t8.active', 1);
    }
    $query->addField('t2','name','qualification_name');
    $results = $query
        ->where('t1.meta_field LIKE \'%"is_worker":"1"%\'')
        ->fields('t1')
        ->groupBy('t1.id_person')
        ->orderBy('t1.id_person','DESC')
        ->execute()->fetchAll();
    db_set_active();
    $rows = array();
    $form['fs_person'] = array(
        '#type' => 'item',
        '#title' => t('Lista Figure'),
        '#prefix' => '<div id="fs-agreement-div">',
        '#suffix' => '</div>',
        '#title_display' => 'invisible',
        '#access' =>true
    );
    $form['fs_person']['person_container'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="person-ajax-wrapper">',
        '#suffix' => '</div>',
    );
    foreach($results as $result) {
        $data = array(
            l($result->id_person, 'person/edit/'.$result->id_person),
            _strformat($result->firstname).' '._strformat($result->lastname),
            ControlloCodiceFiscale($result->tax_code)?strtoupper($result->tax_code):'',
            ucwords($result->qualification_name),

        );
        // recupera i ruoli e le posizioni impostate
        $testo = '<ul>';
        $testo_position = '<ul>';
        $person_lpersons = getAllRecordByField('person_lperson', 'getif_data' , 'id_person', $result->id_person, 'active', array(1,2));
        foreach($person_lpersons as $person_lperson) {
            if ($person_lperson -> active == 1) {
                $person_lperson_proles = getAllRecordByField('person_lperson_prole', 'getif_data', 'id_person_lperson', $person_lperson->id_person_lperson, 'active', array(1,2));
                foreach ($person_lperson_proles as $person_lperson_prole) {
                    if ($person_lperson_prole->active == 1) {
                        $testo .= '<li>';
                        if (!empty($person_lperson->id_lperson))
                        $testo .= getPersonLPersonProleText($person_lperson_prole->id_prole, $person_lperson->id_lperson, $testo);
                        $testo .= '</li>';
                    }
                }
                $person_lperson_positions = getAllRecordByField('person_lperson_position', 'getif_data', 'id_person_lperson', $person_lperson->id_person_lperson, 'active', array(1,2));
                foreach ($person_lperson_positions as $person_lperson_position) {
                    if ($person_lperson_position->active == 1) {
                        $testo_position .= '<li>';
                        $testo_position .= getPersonLPersonPositionText($person_lperson_position->id_position, $person_lperson->id_lperson, $testo_position);
                        $testo_position .= '</li>';
                    }
                }
            }
        }
        $form['edit_person_'.$result->id_person]  = array (
            '#type' => 'submit',
            '#name' => 'edit_person_'.$result->id_person,
            '#value' => '',
            '#submit' => array('edit_person_submit'),
            '#id' => 'edit-edit-person-'.$result->id_person,
            '#attributes' => array(
                'id_person' => $result->id_person,
                'class' => array('btn','glyphicon','glyphicon-pencil'),
            ),
            '#limit_validation_errors' => array(array('person_container','table'))
        );


        // Button remove person_person
        $form['remove_person_'.$result->id_person]  = array (
            '#type' => 'submit',
            '#name' => 'remove_person_'.$result->id_person,
            '#value' => '',
            '#submit' => array('remove_person_submit'),
            '#id' => 'edit-remove-person-'.$result->id_person,
            '#ajax' => array(
                'callback' => 'add_person_callback',
                'wrapper' => 'person-ajax-wrapper',

            ),
            '#attributes' => array(
                'id_person' => $result->id_person,
                'class' => array('btn','btn-remove','glyphicon','glyphicon-trash'),
                'onclick' => 'if(!confirm("Sei sicuro di voler eliminare la Figura? I dati andranno persi definitivamente.")){return false;}'
            ),
            '#limit_validation_errors' => array(array('person_container','table'))
        );
        // necessario per associare la funzione ajax
        $form['remove_person_'.$result->id_person] = ajax_pre_render_element($form['remove_person_'.$result->id_person]);

        // Button disable person
        $form['disable_person_'.$result->id_person]  = array (
            '#type' => 'submit',
            '#name' => 'disable_person_'.$result->id_person,
            '#value' => '',
            '#submit' => array('disable_person_submit'),
            '#id' => 'edit-disable-person-'.$result->id_person,
            '#ajax' => array(
                'callback' => 'add_person_callback',
                'wrapper' => 'person-ajax-wrapper',
            ),
            '#attributes' => array(
                'id_person' => $result->id_person,
                'class' => array('btn','btn-disable'),
                'data-toggle'=> 'toggle',
                'button_checked' => $result->active==1?true:false,
            ),
            '#limit_validation_errors' => array(array('person_container','table'))
        );
        // necessario per associare la funzione ajax
        $form['disable_person_'.$result->id_person] = ajax_pre_render_element($form['disable_person_'.$result->id_person]);
        // Una figura con ruolo attivo in un tirocinio non può essere disabilitata
        // Una figura disabilitata che ha avuto ruoli in almeno un tirocinio non può essere eliminata
        // controllo se la figura è associata ad un tirocinio attivo oppure ad una pratica di tirocinio aperto
        $flg_internship_active = false;
        $tables = array('internship_host_tutor','internship_promoter_tutor','internship_project_contact');
        foreach ($tables as $table) {
            $person_lpersons = getAllRecordByField('person_lperson', 'getif_data' , 'id_person', $result->id_person, 'active');
            foreach($person_lpersons as $person_lperson) {
                $person_lperson_proles = getAllRecordByField('person_lperson_prole', 'getif_data' , 'id_person_lperson', $person_lperson->id_person_lperson, 'active');
                foreach($person_lperson_proles as $person_lperson_prole) {
                    db_set_active('getif_data');
                    $query = db_select($table,'t1');
                    $query->condition('t1.id_person_lperson_prole',$person_lperson_prole->id_person_lperson_prole);
                    $query->condition('t1.active',1);
                    $query->innerJoin('internship_state','t2','t1.id_internship = t2.id_internship');
                    $query->condition('t2.state',0,'<>'); // tirocinio
                    $query->condition('t2.state',7,'<>');
                    $query->condition('t2.active',1);
                    $r = $query->countQuery()->execute()->fetchField();
                    db_set_active();
                    if ($r > 0) {
                        $flg_internship_active = true;
                    }
                }
            }
        }


        $flg_intern = false;
        $intern = getAllRecordByField('internship_person', 'getif_data' , 'id_person', $result->id_person, 'active');
        if (!empty($intern)) {
            $flg_intern = true;
        }

        // controllo se la figura è associata ad un utente attivo
        db_set_active('getif_data');
        $query = db_select('profilo_utente','t1');
        $query->condition('t1.id_person',$result->id_person);
        $query->condition('t1.active',1);
        $query->fields('t1',array('uid'));
        $r = $query->execute()->fetchField();
        db_set_active();
        $flg_person_user = false;
        if (!empty($r)) {
            $flg_person_user = true;
        }

        $testo .= '</ul>';
        $testo_position .= '</ul>';
        $data[] = $testo_position;
        $data[] = $testo;
        $rows[$result->id_person] = $data;

        if($result->active == 1 && !$flg_internship_active && !$flg_person_user && !$flg_intern) { // se person è attiva ma non è associata a tirocini attivi o in stato di pratica come figura e come tirocinante/frequentatore
            // funzioni permesse: edit/disable
            // enable/disable
            array_push($rows[$result->id_person],drupal_render($form['disable_person_' . $result->id_person]));
            // edit - remove
            // Button remove person_person
            $form['remove_person_'.$result->id_person]  = array (
                '#type' => 'button',
                '#value' => '',
                '#attributes' => array(
                    'id_person' => $result->id_person,
                    'class' => array('btn','glyphicon','glyphicon-trash'),
                    'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false;',
                    'disabled' => ''
                ),
            );
            array_push($rows[$result->id_person],drupal_render($form['edit_person_' . $result->id_person]).drupal_render($form['remove_person_' . $result->id_person]));
        } elseif ($result->active == 1 && ($flg_internship_active || $flg_person_user || $flg_intern)) { // se person è attiva ma è associata a tirocini attivi o in stato di pratica
            // funzioni permesse: edit
            // enable/disable
            $form['disable_person_'.$result->id_person]  = array (
                '#type' => 'button',
                '#value' => '',
                '#attributes' => array(
                    'id_person' => $result->id_person,
                    'data-toggle'=> 'toggle',
                    'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false',
                    'button_checked' => $result->active==1?true:false
                ),
            );
            array_push($rows[$result->id_person],drupal_render($form['disable_person_' . $result->id_person]));
            // edit - remove
            // Button remove person_person
            $form['remove_person_'.$result->id_person]  = array (
                '#type' => 'button',
                '#value' => '',
                '#attributes' => array(
                    'id_person' => $result->id_person,
                    'class' => array('btn','glyphicon','glyphicon-trash'),
                    'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false;',
                    'disabled' => ''
                ),
            );
            array_push($rows[$result->id_person],drupal_render($form['edit_person_' . $result->id_person]).drupal_render($form['remove_person_' . $result->id_person]));
        } elseif($result->active == 2) { // se person è disabilita
            $form['edit_person_'.$result->id_person]  = array (
                '#type' => 'button',
                '#value' => '',
                '#attributes' => array(
                    'id_person' => $result->id_person,
                    'class' => array('btn','glyphicon','glyphicon-pencil'),
                    'onclick' => 'alert("'.t('Non è possibile modificare questo elemento.').'");return false',
                    'disabled' => ''
                ),
            );
            // enable/disable
            $form['disable_person_'.$result->id_person]['#attributes']['class'] = array('btn','btn-enable');
            $form['disable_person_'.$result->id_person]['#submit'] = array('enable_person_submit');
            array_push($rows[$result->id_person],drupal_render($form['disable_person_' . $result->id_person]));
            if (!(!$flg_internship_active && !$flg_person_user && !$flg_intern)) { // se non ha uno storico di tirocini associati
                // funzioni permesse: enable
                // remove
                // Button remove person_person
                $form['remove_person_' . $result->id_person] = array(
                    '#type' => 'button',
                    '#value' => '',
                    '#attributes' => array(
                        'id_person' => $result->id_person,
                        'class' => array('btn', 'glyphicon', 'glyphicon-trash'),
                        'onclick' => 'alert("' . t('Non è possibile eliminare questo elemento.') . '");return false;',
                        'disabled' => ''
                    ),
                );
            }
            array_push($rows[$result->id_person],drupal_render($form['edit_person_' . $result->id_person]).drupal_render($form['remove_person_' . $result->id_person]));
        }

    }
    $js_table = '
           <script>
                jQuery(document).ready(function() {
                    var table = jQuery("#tabella").DataTable( {
                        pageLength: @pageLength,
                        scrollX: false,
                        orderCellsTop: true,
                        fixedHeader: true,
                        columnDefs: [
                            { orderable: false, targets: [6] },
                            { orderable: false, targets: [7] },
                            { responsivePriority: 1, targets: 7 },
                            { responsivePriority: 1, targets: 6 },
                        ],
                        responsive: @responsive,
                        order: [[ 0, "DESC" ]],
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
                jQuery("button[type=submit][data-toggle^=toggle]").bootstrapToggle();                
            </script>';
    $form['fs_person']['person_container']['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('Table has no row!'),
        '#attributes' => array('id' => 'tabella'),
        '#suffix' => strtr($js_table,array('@responsive' => RESPONSIVE_FLG,'@pageLength' => TABLE_PAGELENGTH))
    );
    return $form;
}


/**
 * @param $id_prole
 * @param $id_lperson
 * @param $testo
 */
function getPersonLPersonProleText($id_prole, $id_lperson, &$testo) {
    $lperson_lprole_description = getRecordById('lib_prole', 'getif_data', $id_prole, 'active')->description;
    $lperson = getRecordById('lperson', 'getif_data', $id_lperson, 'active');
    $lperson_name = '';
    if (!empty($lperson->level) && $lperson->level == 1) { // se è una struttura
        $lperson_parent = getRecordByField('lperson', 'getif_data', 'id_lperson', $lperson->id_lperson_parent,'active');
        $lperson_name = $lperson_parent->name.' - ';
    }
    if (!empty($lperson->name))
        $lperson_name .= $lperson->name;
    $testo.= $lperson_lprole_description.' c/o '.$lperson_name;
}


/**
 * @param $id_prole
 * @param $id_lperson
 * @param $testo
 */
function getPersonLPersonPositionText($id_prole, $id_lperson, &$testo) {

    $lperson_lprole_description = getRecordById('lib_position', 'getif_data', $id_prole, 'active')->description;
    $lperson = getRecordById('lperson', 'getif_data', $id_lperson, 'active');
    $lperson_name = '';
    if ($lperson->level == 1) { // se è una struttura
        $lperson_parent = getRecordByField('lperson', 'getif_data', 'id_lperson', $lperson->id_lperson_parent,'active');
        $lperson_name = $lperson_parent->name.' - ';
    }
    $lperson_name .= $lperson->name;
    $testo.= $lperson_lprole_description.' c/o '.$lperson_name;
}


/**
 * @param $form
 * @param $form_state
 */
function person_list_view_form_submit($form, &$form_state) {
    if (!empty($form_state['clicked_button']['#attributes']['reset'])) {
        drupal_goto('person/list/', array());
    } else {
        $args = array();
        $args['active'] = $form_state['values']['filter_active'];
        $args['prole'] = $form_state['values']['filter_prole'];
        $args['position'] = $form_state['values']['filter_position'];
        $args['lperson'] = $form_state['values']['filter_lperson'];
        drupal_goto('person/list/', array('query' => $args));
    }
}


/**
 * @param $form
 * @param $form_state
 */
function remove_person_submit_old($form, &$form_state) {
    $id_person = $form_state['clicked_button']['#attributes']['id_person'];

    // controllo se la figura è associata ad un tirocinio attivo oppure ad una pratica di tirocinio aperto
    $tables = array('internship_host_tutor','internship_promoter_tutor','internship_project_contact');
    foreach ($tables as $table) {
        $person_lpersons = getAllRecordByField('person_lperson', 'getif_data' , 'id_person', $id_person, 'active');
        foreach($person_lpersons as $person_lperson) {
            $person_lperson_proles = getAllRecordByField('person_lperson_prole', 'getif_data' , 'id_person_lperson', $person_lperson->id_person_lperson, 'active');
            foreach($person_lperson_proles as $person_lperson_prole) {
                db_set_active('getif_data');
                $query = db_select($table,'t1');
                $query->condition('t1.id_person_lperson_prole',$person_lperson_prole->id_person_lperson_prole);
                $query->condition('t1.active',1);
                $query->innerJoin('internship_state','t2','t1.id_internship = t2.id_internship');
                $query->condition('t2.state',0,'<>'); // tirocinio
                $query->condition('t2.state',7,'<>');
                $query->condition('t2.active',1);
                $result = $query->countQuery()->execute()->fetchField();
                db_set_active();
                if ($result > 0) {
                    drupal_set_message(t("La figura selezionata non può essere disattivata perché presente in una pratica di tirocinio aperta e/o tirocinio attivo."),'error');
                    return;
                }
            }
        }
    }
    // controllo se la figura è associata ad un utente attivo
    db_set_active('getif_data');
    $query = db_select('profilo_utente','t1');
    $query->condition('t1.id_person',$id_person);
    $query->condition('t1.active',1);
    $query->fields('t1',array('uid'));
    $result = $query->execute()->fetchField();
    db_set_active();
    if (!empty($result)) {
        drupal_set_message(t("La figura selezionata non può essere disattivata perché associata ad un utente attivo."),'error');
        return;
    }
    // disattivazione figura
    $fields = array(
        'date_upd' => date("Y-m-d H:i:s", time()),
        'active' => 0
    );
    $where = 'id_person = ' . $id_person;
    try {
        db_set_active('getif_data');
        // Elimina la convenzione
        $query = db_update('person');
        $query->fields($fields)->where($where)->execute();
        db_set_active();
        // watchdog
        $w_type = 'getif_person';
        $w_message = t('Disable item :id');
        $w_variables = array('%id'=>$id_person);
        watchdog($w_type, $w_message, $w_variables);
        drupal_set_message(t("Figura eliminata con successo"));
    } catch (Exception $ex) {
        drupal_set_message('Errore: ' . $ex, 'error');
    }

}


/**
 * @param $form
 * @param $form_state
 */
function goto_new($form, &$form_state) {
    getif_goto('person/new',array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function go_back ($form, &$form_state) {
    getif_goto('',array(),302,true);
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_person_callback($form, &$form_state) {
    return $form['fs_person']['person_container'];
}


/**
 * @param $form
 * @param $form_state
 */
function remove_person_submit($form, &$form_state) {
    $id_person = $form_state['clicked_button']['#attributes']['id_person'];
    db_set_active('getif_data');
    try {
        // disabilita i ruoli della figura presso una struttura
        db_set_active('getif_data');
        db_query(
            'UPDATE person_lperson_prole AS t1 INNER JOIN person_lperson AS t2 ON t1.id_person_lperson = t2.id_person_lperson AND t2.id_person = '.$id_person.' SET t1.active = 0'
        );
        db_set_active();
        // disabilita l'associazione di una figura ad una struttura
        setRecordState('person_lperson', 'getif_data', 'id_person', $id_person, 'active', 0, 'active = 2');
        // disabilita la figura
        setRecordState('person', 'getif_data', 'id_person', $id_person, 'active', 0);
        drupal_set_message('Elemento eliminato con successo.','status');
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
function disable_person_submit($form, &$form_state) {
    $id_person = $form_state['clicked_button']['#attributes']['id_person'];
    db_set_active('getif_data');
    try {
        // disabilita i ruoli della figura presso una struttura
        db_set_active('getif_data');
        db_query(
            'UPDATE person_lperson_prole AS t1 INNER JOIN person_lperson AS t2 ON t1.id_person_lperson = t2.id_person_lperson AND t2.id_person = '.$id_person.' SET t1.active = 2'
        );
        db_set_active();
        // disabilita l'associazione di una figura ad una struttura
        setRecordState('person_lperson', 'getif_data', 'id_person', $id_person, 'active', 2, 'active = 1');
        // disabilita la figura
        setRecordState('person', 'getif_data', 'id_person', $id_person, 'active', 2);
        drupal_set_message('Elemento disabilitato con successo.','status');
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
function enable_person_submit($form, &$form_state) {
    $id_person = $form_state['clicked_button']['#attributes']['id_person'];
    db_set_active('getif_data');
    try {
        // abilita la figura
        setRecordState('person', 'getif_data', 'id_person', $id_person, 'active', 1);
        drupal_set_message('Elemento abilitato con successo.','status');
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
function edit_person_submit($form, &$form_state) {
    $id_person = $form_state['clicked_button']['#attributes']['id_person'];
    getif_goto('person/edit/'.$id_person,array(),302,true);
}

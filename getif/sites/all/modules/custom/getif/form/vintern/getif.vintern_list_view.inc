<?php

/**
 * Theme lista frequentatori
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_vintern_list_view_form($variables){
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/rowsGroup/js/datatables.rowsGroup.js');
    $form = $variables['form'];
    return getif_form_theme($form);
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function vintern_list_view_form($form, &$form_state) {
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back')
    );
    db_set_active('getif_data');
    $query = db_select('person', 't1');
    $query->fields('t1', array('id_person', 'firstname', 'lastname','tax_code','active'));
    $query->condition(
        db_or()->condition('t1.meta_field','%"is_voluntary":"1"%','LIKE')
    );
    $query->condition('t1.active',array(1,2),'IN');
    $query->orderBy('t1.id_person','ASC');
    $results = (object)$query->execute()->fetchAll();
    db_set_active();


    $rows = array();
    foreach($results as $result) {
        db_set_active('getif_data');
        $query = db_select('internship_person', 't1');
        $query->innerJoin('internship', 't2', 't1.id_internship = t2.id_internship');
        $query->fields('t2', array('id_internship', 'flg_voluntary'));
        $query->condition('t1.id_person', $result->id_person);
        $query->condition('t1.active', 1);
        $query->condition('t2.active', 1);
        $query->orderBy('t1.id_internship');
        $internship_list = (object)$query->execute()->fetchAll();
        db_set_active();

        $form['edit_person_' . $result->id_person] = array(
            '#type' => 'submit',
            '#name' => 'edit_person_' . $result->id_person,
            '#value' => '',
            '#submit' => array('edit_person_submit'),
            '#id' => 'edit-edit-person-' . $result->id_person,
            '#attributes' => array(
                'id_person' => $result->id_person,
                'class' => array('btn', 'glyphicon', 'glyphicon-pencil'),
            ),
            '#limit_validation_errors' => array(array('person_container', 'table'))
        );
        $button_update = drupal_render($form['edit_person_' . $result->id_person]);
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
        $flg_intern = false;
        if (!empty((array)$internship_list)) {
            foreach ($internship_list AS $internship_item) {
                if ($internship_item->flg_voluntary) {
                    $internship = getVInternshipById('getif_data', $internship_item->id_internship);
                    $intern_link = l($result->id_person, 'vintern/view/' . ((int)$internship->person->id_internship_person));
                    $internship_state = getVInternshipStateText($internship);
                    if ($internship->internship_state->state >= 1 && $internship->internship_state->state < 4) {
                        $internship_link = l('Frequenza #' . $internship->id_internship, 'vinternship/new/' . ((int)$internship->internship_state->state + 1) . '/' . $internship->id_internship);
                    } else {
                        $internship_link = l('Frequenza #' . $internship->id_internship, 'vinternship/manage/' . $internship->id_internship);
                    }
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
                    // remove
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
                    $rows[$result->id_person.'-'.$internship->id_internship] = array(
                        $result->id_person,
                        $result->firstname,
                        $result->lastname,
                        $result->tax_code,
                        $internship_link,
                        drupal_render($form['disable_person_' . $result->id_person]),
                        $button_update.drupal_render($form['remove_person_' . $result->id_person])
                    );
                }
            }
        } else {
            $internship_link = 'Nessuna frequenza';
            $rows[$result->id_person] = array(
                l($result->id_person, 'person/edit/'.$result->id_person),
                $result->firstname,
                $result->lastname,
                $result->tax_code,
                $internship_link,
                //$button_update
            );
            // Button disable person
            $form['disable_person_'.$result->id_person]  = array (
                '#type' => 'submit',
                '#name' => 'disable_person_'.$result->id_person,
                '#value' => '',
                '#submit' => array('disable_person_submit'),
                '#id' => 'edit-disable-person-'.$result->id_person,
                '#ajax' => array(
                    'callback' => 'add_person_callback',
                    'wrapper' => 'ajax-container',
                ),
                '#attributes' => array(
                    'id_person' => $result->id_person,
                    'class' => array('btn','btn-disable'),
                    'data-toggle'=> 'toggle',
                    'onclick' => 'if(!confirm("Sei sicuro di voler disabilitare la Figura?")){return false;}',
                    'button_checked' => $result->active==1?true:false,
                ),
                '#limit_validation_errors' => array(array('container','table'))
            );
            // necessario per associare la funzione ajax
            $form['disable_person_'.$result->id_person] = ajax_pre_render_element($form['disable_person_'.$result->id_person]);
            // Button remove person_person
            $form['remove_person_'.$result->id_person]  = array (
                '#type' => 'submit',
                '#name' => 'remove_person_'.$result->id_person,
                '#value' => '',
                '#submit' => array('remove_person_submit'),
                '#id' => 'edit-remove-person-'.$result->id_person,
                '#ajax' => array(
                    'callback' => 'add_person_callback',
                    'wrapper' => 'ajax-container',
                ),
                '#attributes' => array(
                    'id_person' => $result->id_person,
                    'class' => array('btn','btn-remove','glyphicon','glyphicon-trash'),
                    'onclick' => 'if(!confirm("Sei sicuro di voler eliminare la Figura? I dati andranno persi definitivamente.")){return false;}'
                ),
                '#limit_validation_errors' => array(array('container','table'))
            );
            // necessario per associare la funzione ajax
            $form['remove_person_'.$result->id_person] = ajax_pre_render_element($form['remove_person_'.$result->id_person]);

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
                array_push($rows[$result->id_person],$button_update.drupal_render($form['remove_person_' . $result->id_person]));
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
                array_push($rows[$result->id_person],$button_update.drupal_render($form['remove_person_' . $result->id_person]));
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

    }
    $header = array(
        array('data' => t('ID')),
        array('data' => t('Nome')),
        array('data' => t('Cognome')),
        array('data' => t('Codice fiscale')),
        array('data' => t('Frequenze')),
        array('data' => t('Attivo')),
        array('data' => t('Azioni'))
    );
    $form['fs_table_panel'] = array(
        '#type' => 'item',
        '#title' => 'Lista frequentatori volontari',
        '#title_display' => 'invisible',
        '#access' =>true
    );

    $form['fs_table_panel']['container'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="ajax-container">',
        '#suffix' => '</div>',
    );

    $js_table = '
         <script>
            jQuery(document).ready(function() {
                var table = jQuery("#tabella").DataTable( {
                    /*rowsGroup: [
                        0,1,2,3
                    ],*/
                    order: [],
                    scrollX: false,
                    orderCellsTop: true,
                    fixedHeader: true,
                    pageLength: @pageLength,
                    columnDefs: [
                        { orderable: false, targets: [5] },
                        { orderable: false, targets: [6] },
                        { responsivePriority: 2, targets: 0 },
                        { responsivePriority: 2, targets: 1 },
                        { responsivePriority: 2, targets: 2 },
                        { responsivePriority: 2, targets: 3 },
                        { responsivePriority: 1, targets: 4 },
                        { responsivePriority: 1, targets: 5 },
                        { responsivePriority: 1, targets: 6 }
                    ],
                    responsive: @responsive,
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
            jQuery(\'button[type=submit][data-toggle^=toggle]\').bootstrapToggle();
        </script>';
    $form['fs_table_panel']['container']['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('Table has no row!'),
        '#attributes' => array(
            'id' => 'tabella'
        ),
        '#suffix' => strtr($js_table,array('@responsive' => RESPONSIVE_FLG,'@pageLength' => TABLE_PAGELENGTH))
    );
    return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function vintern_list_view_form_validate($form, &$form_state) {

}

/**
 * @param $form
 * @param $form_state
 */
function vintern_list_view_form_submit($form, &$form_state) {

}


/**
 * @param $form
 * @param $form_state
 */
function edit_person_submit($form, &$form_state) {
    $id_person = $form_state['clicked_button']['#attributes']['id_person'];
    getif_goto('person/edit/'.$id_person,array('query'=>array('is_voluntary'=>1)),302,true);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_person_callback($form, &$form_state) {
    return $form['table_panel']['container'];
}

/**
 * @param $form
 * @param $form_state
 */
function remove_person_submit($form, &$form_state) {
    $id_person = $form_state['clicked_button']['#attributes']['id_person'];
    db_set_active('getif_data');
    try {
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
        // disabilita la person
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
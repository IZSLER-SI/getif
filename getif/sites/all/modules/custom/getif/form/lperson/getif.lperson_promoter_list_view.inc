<?php

/**
 * Theme lperson_promoter_list_view
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_promoter_list_view_form($variables){
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    $form = $variables['form'];
    return getif_form_theme($form);
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function lperson_promoter_list_view_form($form, &$form_state) {
    db_set_active('getif_data');
    $query = db_select('lperson', 't1');
    // filtri
    $_GET['lprole'] = 1;
    if (!empty($_GET['lprole'])) {
        $query->innerJoin('lperson_lprole','t2','t1.id_lperson = t2.id_lperson');
        $query->condition('t2.id_lprole', $_GET['lprole']);
    }

    $results = $query
        ->fields('t1')
        ->condition('t1.level',0)
        ->condition('t1.active',array(1,2),'IN')
        ->orderBy('t1.date_add', 'DESC')
        ->execute();
    db_set_active(); 
    $rows = array();
    foreach($results as $key => $result) {
        $rows[$result->id_lperson] = array(
            l($result->id_lperson, 'lperson_promoter/edit/'.$result->id_lperson),
            $result->name
        );

        // Ruoli
        $lperson_lproles = getAllRecordByField('lperson_lprole', 'getif_data' , 'id_lperson', $result->id_lperson, 'active');
        $testo = '<ul>';
        foreach($lperson_lproles as $lperson_lprole) {
            $testo .= '<li>';
            $testo .= get_lperson_names($lperson_lprole->id_lperson, $lperson_lprole->id_lprole,$testo);
            $testo .= '</li>';
        }
        $testo .= '</ul>';
        $rows[$result->id_lperson][] = $testo;
        // Strutture
        db_set_active('getif_data');
        $query_branch = db_select('lperson', 't1');
        $results_branch = $query_branch
            ->fields('t1')
            ->condition('id_lperson_parent',$result->id_lperson,'=')
            ->condition('t1.active', 1)
            ->execute();
        db_set_active();
        $testo = '<ul>';
        foreach($results_branch as $branch) {
            $testo .= '<li>';
            if ($branch->id_lperson == $result->id_lperson)
                $branch->name = $branch->name.' - '.$branch->seat;
            $testo .= l($branch->name,'lperson_promoter/branch/edit/'.$branch->id_lperson);
            $testo .= '</li>';
        }
        $testo .= '</ul>';
        $rows[$result->id_lperson][] = $testo;


        $form['edit_lperson_'.$result->id_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'edit_lperson_'.$result->id_lperson,
            '#value' => '',
            '#submit' => array('edit_lperson_submit'),
            '#id' => 'edit-edit-lperson-'.$result->id_lperson,
            '#attributes' => array(
                'id_lperson' => $result->id_lperson,
                'class' => array('btn','glyphicon','glyphicon-pencil'),
            ),
            '#limit_validation_errors' => array(array('lperson_container','table'))
        );
        // Button disable person_lperson
        $form['disable_lperson_'.$result->id_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'disable_lperson_'.$result->id_lperson,
            '#value' => '',
            '#submit' => array('disable_lperson_submit'),
            '#id' => 'edit-disable-lperson-'.$result->id_lperson,
            '#ajax' => array(
                'callback' => 'add_lperson_callback',
                'wrapper' => 'lperson-ajax-wrapper',
            ),
            '#attributes' => array(
                'id_lperson' => $result->id_lperson,
                'class' => array('btn','btn-disable'),
                'data-toggle'=> 'toggle',
                'button_checked' => $result->active==1?true:false
            ),
            '#limit_validation_errors' => array(array('lperson_container','table'))
        );
        // necessario per associare la funzione ajax
        $form['disable_lperson_'.$result->id_lperson] = ajax_pre_render_element($form['disable_lperson_'.$result->id_lperson]);
        // Button remove person_lperson
        $form['remove_lperson_'.$result->id_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'remove_lperson_'.$result->id_lperson,
            '#description' => 'Attiva/Disattiva',
            '#value' => '',
            '#submit' => array('remove_lperson_submit'),
            '#id' => 'edit-remove-lperson-'.$result->id_lperson,
            '#ajax' => array(
                'callback' => 'add_lperson_callback',
                'wrapper' => 'lperson-ajax-wrapper',
            ),
            '#attributes' => array(
                'id_lperson' => $result->id_lperson,
                'class' => array('btn','btn-remove','glyphicon','glyphicon-trash'),
                'onclick' => 'if(!confirm("Sei sicuro di voler eliminare il Soggetto Promotore? I dati andranno persi definitivamente.")){return false;}'
            ),
            '#limit_validation_errors' => array(array('lperson_container','table'))
        );
        // necessario per associare la funzione ajax
        $form['remove_lperson_'.$result->id_lperson] = ajax_pre_render_element($form['remove_lperson_'.$result->id_lperson]);

        db_set_active('getif_data');
        $query = db_select('internship_agreement','t1');
        $query -> innerJoin('agreement','t2','t1.id_agreement = t2.id_agreement');
        $query -> innerJoin('lperson_lprole','t3','t2.id_promoter = t3.id_lperson_lprole');
        $query -> innerJoin('lperson','t4','(t4.level = 0 AND t4.id_lperson = '.$result->id_lperson.' AND t4.id_lperson = t3.id_lperson) OR (t4.level = 1 AND t4.id_lperson_parent = '.$result->id_lperson.' AND t4.id_lperson_parent = t3.id_lperson)');
        $query -> innerJoin('internship_state','t5','t1.id_internship = t5.id_internship');
        $query -> condition('t5.state',array(1,2,3,4,5,6),'IN');
        $query -> condition('t1.active',1);
        $query -> condition('t2.active',1);
        $query -> condition('t3.active',1);
        $query -> condition('t4.active',1);
        $query -> condition('t5.active',1);
        $r = intval($query -> countQuery() -> execute() -> fetchField());
        db_set_active();

        if($result->active == 1 && $r == 0) { // se lperson è attiva ma non è associata a tirocini attivi o in stato di pratica
            // funzioni permesse: edit/disable

            // enable/disable
            array_push($rows[$result->id_lperson],drupal_render($form['disable_lperson_' . $result->id_lperson]));
            // edit - remove
            // Button remove
            $form['remove_lperson_'.$result->id_lperson]  = array (
                '#type' => 'button',
                '#value' => '',
                '#attributes' => array(
                    'class' => array('btn','glyphicon','glyphicon-trash'),
                    'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false;',
                    'disabled' => ''
                ),
            );
            array_push($rows[$result->id_lperson],
                drupal_render($form['edit_lperson_' . $result->id_lperson]).
                drupal_render($form['remove_lperson_' . $result->id_lperson]));
        } elseif($result->active == 1 && $r > 0) { // se lperson è attiva ma è associata a tirocini attivi o in stato di pratica

            // funzioni permesse: edit
            // enable/disable
            $form['disable_lperson_'.$result->id_lperson]  = array (
                '#type' => 'button',
                '#value' => '',
                '#attributes' => array(
                    'class' => array('btn','glyphicon','glyphicon-trash'),
                    'data-toggle'=> 'toggle',
                    'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false',
                    'button_checked' => $result->active==1?true:false
                ),
            );
            array_push($rows[$result->id_lperson],drupal_render($form['disable_lperson_' . $result->id_lperson]));
            // edit - remove
            // Button remove
            $form['remove_lperson_'.$result->id_lperson]  = array (
                '#type' => 'button',
                '#value' => '',
                '#attributes' => array(
                    'class' => array('btn','glyphicon','glyphicon-trash'),
                    'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false;',
                    'disabled' => ''
                ),
            );
            array_push($rows[$result->id_lperson],
                drupal_render($form['edit_lperson_' . $result->id_lperson]).
                drupal_render($form['remove_lperson_' . $result->id_lperson]));

        } elseif($result->active == 2) { // se lperson è disabilita
            db_set_active('getif_data');
            $query = db_select('internship_lperson','t1');
            $query -> condition('t1.id_internship_lperson',$result->id_lperson);
            $r = intval($query -> countQuery() -> execute() -> fetchField());
            db_set_active();
            $form['edit_lperson_'.$result->id_lperson]  = array (
                '#type' => 'button',
                '#value' => '',
                '#attributes' => array(
                    'class' => array('btn','glyphicon','glyphicon-pencil'),
                    'onclick' => 'alert("'.t('Non è possibile modificare questo elemento.').'");return false',
                    'disabled' => ''
                ),
            );
            $form['disable_lperson_'.$result->id_lperson]['#attributes']['class'] = array('btn','btn-enable');
            $form['disable_lperson_'.$result->id_lperson]['#submit'] = array('enable_lperson_submit');
            array_push($rows[$result->id_lperson],drupal_render($form['disable_lperson_' . $result->id_lperson]));
            if (!($r == 0)) { // se non ha uno storico di tirocini associati
                // funzioni permesse: enable
                // Button remove person_person
                $form['remove_lperson_' . $result->id_lperson] = array(
                    '#type' => 'button',
                    '#value' => '',
                    '#attributes' => array(
                        'class' => array('btn', 'glyphicon', 'glyphicon-trash'),
                        'onclick' => 'alert("' . t('Non è possibile eliminare questo elemento.') . '");return false;',
                        'disabled' => ''
                    ),
                );
            }
            array_push($rows[$result->id_lperson],
                drupal_render($form['edit_lperson_' . $result->id_lperson]).
                drupal_render($form['remove_lperson_' . $result->id_lperson]));
        }
    }
    // Top Buttons
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
        '#attributes' => array()
    );
    $form['nav']['new'] = array(
        '#type' => 'button',
        '#value' => t('Nuovo').' '.t('Soggetto'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_new'),
    );
    $header = array(
        t('ID'),
        t('Ragione Sociale'),
        t('Ruolo'),
        t('Segreteria/Dipartimento'),
        t('Attivo'),
        t('Azioni')
    );

    $form['fs_lperson'] = array(
        '#type' => 'item',
        '#title' => t('Lista Soggetti'),
        '#prefix' => '<div id="fs-lperson-div">',
        '#suffix' => '</div>',
        '#title_display' => 'invisible',
        '#access' =>true
    );
    $form['fs_lperson']['lperson_container'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="lperson-ajax-wrapper">',
        '#suffix' => '</div>',
    );

    $form['fs_lperson']['lperson_container']['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('Table has no row!'),
        '#attributes' => array('id' => 'tabella'),
        '#suffix' => strtr('
            <script>
                jQuery(document).ready(function() {
                    // Setup - add a text input to each footer cell
                    var table = jQuery("#tabella").DataTable( {
                        pageLength: @pageLength,
                        scrollX: false,
                        orderCellsTop: true,
                        fixedHeader: true,
                        columnDefs: [
                            { orderable: false, targets: [4] },
                            { orderable: false, targets: [5] },
                            { responsivePriority: 1, targets: 0 },
                            { responsivePriority: 1, targets: 5 },
                            { responsivePriority: 1, targets: 4 }
                        ],
                        responsive: @responsive,
                        order: [[ 0, "desc" ]],
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
             </script>
        ',array('@responsive' => RESPONSIVE_FLG,'@pageLength' => TABLE_PAGELENGTH))
    );
    return $form;
}

/**
 * @param $id_lperson
 * @param $id_lprole
 * @param $testo
 */
function get_lperson_names($id_lperson, $id_lprole, &$testo) {
    $lperson_lprole_description = getRecordById('lib_lprole', 'getif_data', $id_lprole, 'active')->description;
    $testo.= $lperson_lprole_description;
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_promoter_list_view_form_validate($form, &$form_state) {
    // nothing
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_promoter_list_view_form_submit($form, &$form_state) {
    $controller = $form_state['clicked_button']['#attributes']['controller'];
    if ($form_state['clicked_button']['#attributes']['reset']) {
        drupal_goto('lperson_promoter/list/', array());
    } else {
        drupal_goto('lperson_promoter/list/', array('query' => array('lprole' => $form_state['values']['filter'])));
    }
}

/**
 * @param $form
 * @param $form_state
 */
function goto_new($form, &$form_state) {
    getif_goto('lperson_promoter/new',array(),302,true);
}


/**
 * @param $form
 * @param $form_state
 */
function edit_lperson_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    getif_goto('lperson_promoter/edit/'.$id_lperson,array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function remove_lperson_submit($form, &$form_state)
{
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    db_set_active('getif_data');
    try {
        // disabilita la struttura
        setRecordState('lperson', 'getif_data', 'id_lperson', $id_lperson, 'active', 0);
        // disabilita i ruoli associati alla struttura
        $ids_lperson_lprole = getLPersonLProleIdsByLPersonId('getif_data', $id_lperson);
        foreach ($ids_lperson_lprole AS $id_lperson_lprole) {
            setRecordState('lperson_lprole', 'getif_data', 'id_lperson_lprole', $id_lperson_lprole, 'active', 0);
        }
        drupal_set_message('Elemento eliminato con successo.', 'status');
    } catch (Exception $ex) {
        drupal_set_message('Errore: ' . $ex, 'error');
    }
    db_set_active();
    $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 */
function disable_lperson_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    db_set_active('getif_data');
    try {
        // disabilita la struttura
        setRecordState('lperson', 'getif_data', 'id_lperson', $id_lperson, 'active', 2);
        // disabilita i ruoli associati alla struttura
        $ids_lperson_lprole = getLPersonLProleIdsByLPersonId('getif_data', $id_lperson);
        foreach ($ids_lperson_lprole AS $id_lperson_lprole) {
            setRecordState('lperson_lprole', 'getif_data', 'id_lperson_lprole', $id_lperson_lprole, 'active', 2);
        }
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
function enable_lperson_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    db_set_active('getif_data');
    try {
        // abilita la struttura
        setRecordState('lperson', 'getif_data', 'id_lperson', $id_lperson, 'active', 1);
        setRecordState('lperson_lprole', 'getif_data', 'id_lperson', $id_lperson, 'active', 1);
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
 * @return mixed
 */
function add_lperson_callback($form, &$form_state) {
    return $form['fs_lperson']['lperson_container'];
}
<?php

/**
 * Theme lperson_branch_manage
 * Gestione Strutture Soggetto Promotore
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_promoter_branch_manage_form($variables){
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    $form = $variables['form'];
    $options['page_title'] = 'Gestione '.$form['fs_branches']['#title'];
    return getif_form_theme($form,null,$options);
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function lperson_promoter_branch_manage_form($form, &$form_state) {
    $controller = $form_state["build_info"]["args"]["0"];
    $id_lperson = $form_state["build_info"]["args"]["1"];
    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Anagrafica Soggetto'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_back'),
    );


    $lperson_parent = getLPersonById('getif_data',$id_lperson);

    /* SEDE LEGALE - BRANCH con campo level = 0 */

    $form['fs_head_office'] = array(
        '#type' => 'container',
        '#title' => t('Sede Legale').' '.t('di').' '._strformat($lperson_parent->name),
        '#prefix' => '<div id="fs-branch-div">',
        '#suffix' => '</div>',
    );
    $form['fs_head_office']['#prefix'] = '<div id="fs-branch-div"><legend class="panel-heading-2"><span class="panel-title fieldset-legend">'.$form['fs_head_office']['#title'].'</span></legend>';
    $form['fs_head_office']['table_head_office'] = array(
        '#theme' => 'table',
        '#empty' => t('Non ci sono elementi!')
    );

    /* STRUTTURE - BRANCH */

    $form['fs_branches'] = array(
        '#type' => 'container',
        '#title' => t('Segr. / Dip.').' '.t('di').' '._strformat($lperson_parent->name),
        '#prefix' => '<div id="fs-branch-div">',
        '#suffix' => '</div>',
        '#title_display' => 'invisible'
    );
    $form['fs_branches']['#prefix'] = '<div id="fs-branch-div"><legend class="panel-heading-2"><span class="panel-title fieldset-legend">'.$form['fs_branches']['#title'].'</span></legend>';
    $form['fs_branches']['branch_container'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="branch-ajax-wrapper">',
        '#suffix' => '</div>',
    );
    // recupera le strutture annidate
    $branches = getAllRecordByField('lperson', 'getif_data' , 'id_lperson_parent', $id_lperson, 'active', array(1,2));

    $rows_head_office = array(); // array delle sedi legali
    $rows = array(); // array delle strutture
    foreach ($branches as $branch) {
        $form['edit_branch_'.$branch->id_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'edit_branch_'.$branch->id_lperson,
            '#value' => '',
            '#submit' => array('edit_branch_submit'),
            '#id' => 'edit-edit-branch-'.$branch->id_lperson,
            '#attributes' => array(
                'id_lperson' => $branch->id_lperson,
                'class' => array('btn','glyphicon','glyphicon-pencil'),
            ),
            '#limit_validation_errors' => array(array('branch_container','table'))
        );
        // Button disable person_lperson
        $form['disable_branch_'.$branch->id_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'disable_branch_'.$branch->id_lperson,
            '#value' => '',
            '#submit' => array('disable_branch_submit'),
            '#id' => 'edit-disable-branch-'.$branch->id_lperson,
            '#ajax' => array(
                'callback' => 'add_branch_callback',
                'wrapper' => 'branch-ajax-wrapper',
            ),
            '#attributes' => array(
                'id_lperson' => $branch->id_lperson,
                'class' => array('btn','btn-disable'),
                'data-toggle'=> 'toggle',
                'button_checked' => $branch->active==1?true:false
            ),
            '#limit_validation_errors' => array(array('branch_container','table'))
        );
        // necessario per associare la funzione ajax
        $form['disable_branch_'.$branch->id_lperson] = ajax_pre_render_element($form['disable_branch_'.$branch->id_lperson]);
        // Button remove person_lperson
        $form['remove_branch_'.$branch->id_lperson]  = array (
            '#type' => 'submit',
            '#name' => 'remove_branch_'.$branch->id_lperson,
            '#value' => '',
            '#submit' => array('remove_branch_submit'),
            '#id' => 'edit-remove-branch-'.$branch->id_lperson,
            '#ajax' => array(
                'callback' => 'add_branch_callback',
                'wrapper' => 'branch-ajax-wrapper',
            ),
            '#attributes' => array(
                'id_lperson' => $branch->id_lperson,
                'class' => array('btn','btn-remove','glyphicon','glyphicon-trash'),
                'onclick' => 'if(!confirm("Sei sicuro di voler eliminare la Struttura? I dati andranno persi definitivamente.")){return false;}'
            ),
            '#limit_validation_errors' => array(array('branch_container','table'))
        );
        // necessario per associare la funzione ajax
        $form['remove_branch_'.$branch->id_lperson] = ajax_pre_render_element($form['remove_branch_'.$branch->id_lperson]);

        if ($branch->level == 0) { // Se è sede legale
            $rows_head_office[$branch->id_lperson] = array(
                _strformat($branch->name),
                strtoupper($branch->tax_code),
                (!empty($branch->email_address)?strtolower($branch->email_address).'<br>':'').
                (!empty($branch->certified_email_address)?'[PEC] '.strtolower($branch->certified_email_address):''),
                (!empty($branch->phone)?$branch->phone. '<br>':'').(!empty($branch->fax)?'[FAX] '.$branch->fax:''),
                drupal_render($form['edit_branch_'.$branch->id_lperson])
            );
            unset($form['disable_branch_'.$branch->id_lperson]);
            unset($form['remove_branch_'.$branch->id_lperson]);
        } else {
            $rows[$branch->id_lperson] = array(
                _strformat($branch->name),
                (!empty($branch->email_address)?strtolower($branch->email_address).'<br>':'').
                (!empty($branch->certified_email_address)?'[PEC] '.strtolower($branch->certified_email_address):''),
                (!empty($branch->phone)?$branch->phone. '<br>':'').(!empty($branch->fax)?'[FAX] '.$branch->fax:''),

            );

            db_set_active('getif_data');
            $query = db_select('internship_lperson','t1');
            $query -> condition('t1.id_lperson',$branch->id_lperson);
            $query -> condition('t1.active',1);
            $query -> innerJoin('internship_state','t2','t1.id_internship = t2.id_internship');
            $query -> condition('t2.state',array(1,2,3,4,5,6),'IN');
            $query -> condition('t2.active',1);
            $result = intval($query -> countQuery() -> execute() -> fetchField());
            db_set_active();

            if($branch->active == 1 && $result == 0) { // se lperson è attiva ma non è associata a tirocini attivi o in stato di pratica
                // funzioni permesse: edit/disable
                // enable/disable
                array_push($rows[$branch->id_lperson],drupal_render($form['disable_branch_' . $branch->id_lperson]));
                // edit - remove
                // Button remove
                $form['remove_branch_'.$branch->id_lperson]  = array (
                    '#type' => 'button',
                    '#value' => '',
                    '#attributes' => array(
                        'class' => array('btn','glyphicon','glyphicon-trash'),
                        'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false;',
                        'disabled' => ''
                    ),
                );
                array_push($rows[$branch->id_lperson],
                    drupal_render($form['edit_branch_' . $branch->id_lperson]).
                    drupal_render($form['remove_branch_' . $branch->id_lperson]));
            } elseif($branch->active == 1 && $result > 0) { // se lperson è attiva ma è associata a tirocini attivi o in stato di pratica


                // funzioni permesse: edit
                // enable/disable
                $form['disable_branch_'.$branch->id_lperson]  = array (
                    '#type' => 'button',
                    '#value' => '',
                    '#attributes' => array(
                        'class' => array('btn','glyphicon','glyphicon-trash'),
                        'data-toggle'=> 'toggle',
                        'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false',
                        'button_checked' => $branch->active==1?true:false
                    ),
                );
                array_push($rows[$branch->id_lperson],drupal_render($form['disable_branch_' . $branch->id_lperson]));
                // edit - remove
                // Button remove
                $form['remove_branch_'.$branch->id_lperson]  = array (
                    '#type' => 'button',
                    '#value' => '',
                    '#attributes' => array(
                        'class' => array('btn','glyphicon','glyphicon-trash'),
                        'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false;',
                        'disabled' => ''
                    ),
                );
                array_push($rows[$branch->id_lperson],
                    drupal_render($form['edit_branch_' . $branch->id_lperson]).
                    drupal_render($form['remove_branch_' . $branch->id_lperson]));

            } elseif($branch->active == 2) { // se lperson è disabilita
                $form['disable_branch_'.$branch->id_lperson]['#attributes']['class'] = array('btn','btn-enable');
                $form['disable_branch_'.$branch->id_lperson]['#submit'] = array('enable_branch_submit');
                $form['edit_branch_'.$branch->id_lperson]  = array (
                    '#type' => 'button',
                    '#value' => '',
                    '#attributes' => array(
                        'class' => array('btn','glyphicon','glyphicon-pencil'),
                        'onclick' => 'alert("'.t('Non è possibile modificare questo elemento.').'");return false',
                        'disabled' => ''
                    ),
                );
                array_push($rows[$branch->id_lperson],drupal_render($form['disable_branch_' . $branch->id_lperson]));
                db_set_active('getif_data');
                $query = db_select('internship_lperson','t1');
                $query -> condition('t1.id_internship_lperson',$branch->id_lperson);
                $result = intval($query -> countQuery() -> execute() -> fetchField());
                db_set_active();

                if ($result != 0) { // se non ha uno storico di tirocini associati
                    // funzioni permesse: enable
                    // funzioni permesse: enable
                    // Button remove person_person
                    $form['remove_branch_' . $branch->id_lperson] = array(
                        '#type' => 'button',
                        '#value' => '',
                        '#attributes' => array(
                            'class' => array('btn', 'glyphicon', 'glyphicon-trash'),
                            'onclick' => 'alert("' . t('Non è possibile eliminare questo elemento.') . '");return false;',
                            'disabled' => ''
                        ),
                    );

                }
                array_push($rows[$branch->id_lperson],
                    drupal_render($form['edit_branch_' . $branch->id_lperson]).
                    drupal_render($form['remove_branch_' . $branch->id_lperson]));
            }

        }
    }
    // Tabella delle sede_legali
    $header_head_office = array(t('Ragione Sociale'),t('P.IVA / Cod.Fisc.'),t('PEC / Email'),t('Tel / Fax'),t('Azioni'));
    $form['fs_head_office']['table_head_office']['#header'] = $header_head_office;
    $form['fs_head_office']['table_head_office']['#rows'] = $rows_head_office;
    // Tabella delle strutture
    $header = array(
        t('Denominazione Segr. / Dip.'),
        t('PEC / Email'),
        t('Tel / Fax'),
        t('Attiva'),
        t('Azioni')
    );
    $form['fs_branches']['branch_container']['table'] = array
    (
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => !empty($rows)?$rows:array(array()),
        '#empty' => t('Non ci sono elementi!'),
        '#attributes' => array('id' => 'tabella'),
        '#suffix' => strtr('
            <script>
                jQuery(document).ready(function() {
                    var table = jQuery("#tabella").DataTable( {
                        pageLength: @pageLength,
                        scrollX: false,
                        orderCellsTop: true,
                        fixedHeader: true,
                        columnDefs: [
                            { orderable: false, targets: [3] },
                            { orderable: false, targets: [4] },
                            { responsivePriority: 1, targets: 0 },
                            { responsivePriority: 1, targets: 4 },
                            { responsivePriority: 1, targets: 3 }
                        ],
                        responsive: @responsive,
                        order: [[ 0, "ASC" ]],
                        language: {
                            "emptyTable":     "-",
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
    $form['nav']['new'] = array(
        '#type' => 'button',
        '#value' => t('Nuova').' '.t('Segr. / Dip.'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_new'),
    );
    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function lperson_promoter_branch_manage_form_validate($form, &$form_state) {
    // empty
}


/**
 * @param $form
 * @param $form_state
 */
function goto_back($form, &$form_state) {
    getif_goto('lperson_promoter/edit/'.$form_state["build_info"]["args"]["1"],array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function goto_new($form, &$form_state) {
    getif_goto('lperson_promoter/branch/new/'.$form_state["build_info"]["args"]["1"],array(),302,true);
}


/**
 * @param $form
 * @param $form_state
 */
function remove_branches_submit($form, &$form_state) {
    $selected = array_filter($form_state['values']['branch_container']['table']);
    // per ogni stuttura associata
    foreach ($selected as $id_lperson => $item) {
        try {
            // disabilita la struttura
            setRecordState('lperson', 'getif_data', 'id_lperson', $id_lperson, 'active', 2);
            // disabilita i ruoli associati alla struttura
            $ids_lperson_lprole = getLPersonLProleIdsByLPersonId('getif_data', $id_lperson);
            foreach ($ids_lperson_lprole AS $id_lperson_lprole) {
                setRecordState('lperson_lprole', 'getif_data', 'id_lperson_lprole', $id_lperson_lprole, 'active', 2);
            }
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        };
    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}

/**
 * @param $form
 * @param $form_state
 */
function remove_branch_submit($form, &$form_state)
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
function disable_branch_submit($form, &$form_state) {
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
function enable_branch_submit($form, &$form_state) {
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
 */
function edit_branch_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    getif_goto('lperson_promoter/branch/edit/'.$id_lperson,array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_branch_callback($form, &$form_state) {
    return $form['fs_branches']['branch_container'];
}


/* end */

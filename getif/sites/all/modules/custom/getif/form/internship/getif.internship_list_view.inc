<?php

/**
 * Theme lista tirocini
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_internship_list_view_form($variables){
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_js(strtr('
            function format ( d ) {
                // `d` is the original data object for the row
                return \'<table cellpadding="5" cellspacing="5" border="0" style="padding-left:50px;">\'+
                    \'<tr>\'+
                        \'<td valign="top" style="padding:5px"><b>Dettagli Tirocinante:</b></td>\'+
                        \'<td valign="top" style="padding:5px">\'+d.dati_tirocinante+\'</td>\'+
                        \'<td valign="top" style="padding:5px">\'+d.link_tirocinante+\'</td>\'+
                    \'</tr>\'+
                \'</table>\';
            }
            function strip_html_tags(str)
            {
              if ((str===null) || (str===\'\'))
                return false;
              else
                str = str.toString();
              return str.replace(/<[^>]*>/g, \'\');
            }
            var fixNewLine = {
                exportOptions: {
                    format: {
                        body: function ( data, column, row ) {
                            return strip_html_tags(data.replace(/<br\s*\/?>/gi,"\r\n"));
                        }
                    }
                }
            };
            jQuery(document).ready(function() {
                var table = jQuery("#tabella").DataTable( {
                    pageLength: @pageLength,
                    scrollX: false,
                    orderCellsTop: true,
                    fixedHeader: true,
                    dom: "<\"toolbar_top\">B<\"toolbar_ex\">lfrtip",
                    buttons:[
                        jQuery.extend( true, {}, fixNewLine, {
                            extend: \'csvHtml5\',
                            title: "tirocini_'.date("d-m-Y").'",
                            exportOptions: {
                                columns: \':not(.notexport)\'
                            }
                        } ),
                        jQuery.extend( true, {}, fixNewLine, {
                            extend: \'excelHtml5\',
                            title: "tirocini_'.date("d-m-Y").'",
                            exportOptions: {
                                columns: \':not(.notexport)\'
                            }
                        } ),
                    ],
                    columns: [
                        { "data": "id" },
                        {
                            "className":      \'details-control\',
                            "orderable":      false,
                            "data":           "tirocinante",
                            "defaultContent": ""
                        },
                        { "data": "dati_tirocinante" },
                        { "data": "link_tirocinante" },
                        { "data": "convenzione" },
                        { "data": "strutture_so" },
                        { "data": "tutor_sp" },
                        { "data": "tutor_so" },
                        { "data": "resp_sp" },
                        { "data": "data_inizio" },
                        { "data": "data_fine" },
                        { "data": "stato" },
                        { "data": "registro" },
                        { "data": "azioni" }
                    ],
                    columnDefs: [
                        {
                            "targets": [ 2 ],
                            "visible": false,
                            "searchable": true
                        },
                        {
                            "targets": [ 3 ],
                            "visible": false,
                            "searchable": false
                        },
                        { type: "date-eu", targets: [9] },
                        { type: "date-eu", targets: [10] },
                        { orderable: false, targets: [12] },
                        { orderable: false, targets: [13] },
                        { responsivePriority: 1, targets: 13 },
                        { responsivePriority: 1, targets: 12 },
                        { responsivePriority: 1, targets: 11 }
                    ],
                    responsive: true,
                    order: [[ 0, "desc" ]],
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
                jQuery("div.toolbar_top").html("<h4 style=\"margin-top:0\">Esporta:</h4>");
                jQuery("div.toolbar_ex").html("<br/>");
                 // Add event listener for opening and closing details
                jQuery(\'#tabella tbody\').on(\'click\', \'td.details-control\', function () {
                    var tr = jQuery(this).closest(\'tr\');
                    var row = table.row( tr );
             
                    if ( row.child.isShown() ) {
                        // This row is already open - close it
                        row.child.hide();
                        tr.removeClass(\'shown\');
                    }
                    else {
                        // Open this row
                        row.child( format(row.data()) ).show();
                        tr.addClass(\'shown\');
                    }
                } );
            } );
        ',array('@responsive' => RESPONSIVE_FLG,'@pageLength' => TABLE_PAGELENGTH)),array('type'=>'inline','scope'=>'footer'));
    $form = $variables['form'];
    $header_content = array();
    $form_filter = '<div class="row">
            <div class="col-md-12 form-container">
                <fieldset class="panel panel-default form-wrapper">
                    <div class="panel-body">';
    $form_filter .= '<div class="col-md-3">'.drupal_render($form['filter_panel']['state']).'</div>';
    $form_filter .= '<div class="col-md-12">'.drupal_render($form['filter_panel']['save']).drupal_render($form['filter_panel']['reset']).'</div>';
    $form_filter .= '</div>
                </fieldset>
            </div>
        </div>';
    $header_content[] = array('html' => $form_filter,'has_separator' => false);
    $options = array();
    $options['show_fs_title'] = false;
    return getif_form_theme($form,$header_content,$options);
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function internship_list_view_form($form, &$form_state) {
    global $user;
    // Top Buttons
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back'),
    );

    db_set_active('getif_data');
    $query = db_select('internship', 't1');
    $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
    $query
        ->fields('t1', array('id_internship', 'date_start', 'date_end'))
        ->fields('t2', array('state'))
        ->condition("t1.flg_voluntary",0,'=') // è un tirocinio
        ->condition("t1.active",1,'=')
        ->condition("t2.active",1,'=');
    // filtro tutor
    if (in_array('tutor',$user->roles)) {
        $id_person = $_SESSION['user']['id_person'];
        $query1 = db_select('internship_host_tutor','t1');
        $query1->innerJoin('person_lperson_prole','t2','t1.id_person_lperson_prole = t2.id_person_lperson_prole AND id_prole = 2');
        $query1->innerJoin('person_lperson','t3','t2.id_person_lperson = t3.id_person_lperson');
        $query1->innerJoin('person','t4','t4.id_person = t3.id_person');
        $query1->fields('t1',array('id_internship'));
        $ids_internship = $query1->where('t4.id_person = '.$id_person.' AND t1.active = 1 AND t2.active = 1 AND t3.active = 1 AND t4.active = 1')->execute()->fetchCol();
        if (!empty($ids_internship))
            $query->condition("t1.id_internship",$ids_internship,'IN');
        else {
            $query->condition(0,1);
        }
        $user_is_tutor = true;
    } else {
        $user_is_tutor = false;
    }



    // filtro stato
    if (isset($_GET['state'])) {
        if ($_GET['state'] == 'all') {
            $query->condition('t2.state', array(0,1,2,3,4,5,6,7), 'IN');
            $state_default_value = 'all';
        } elseif ($_GET['state'] == 'pending') {
            $query->condition('t2.state', array(1,2,3,4), 'IN');
            $state_default_value = 'pending';
        } elseif ($_GET['state'] == 'active') {
            $query->condition('t2.state', array(5,6), 'IN');
            $state_default_value = 'active';
        } else {
            $query->condition('t2.state', $_GET['state'], '=');
            $state_default_value = $_GET['state'];
        }
    } else  {
        $query->condition('t2.state', array(0,1,2,3,4,5,6,7), 'IN');
        $state_default_value = 'all';
    }
    $results = $query
        ->execute();
    db_set_active();

    $rows = array();
    foreach($results as $key => $item) {
        $internship = getInternshipById('getif_data', $item->id_internship);
        if (!empty($internship->promoter->tutor->title)) {
            $internship_promoter_tutor_text = '<b>' . _strformat($internship->promoter->tutor->title) . ' ' . _strformat($internship->promoter->tutor->firstname) . ' ' . _strformat($internship->promoter->tutor->lastname) . '</b>';
        } else {
            $internship_promoter_tutor_text = '';
        }
        if (!empty($internship->promoter)) {
            if ($internship->promoter->level == 1) {
                $internship_promoter = $internship->promoter->parent->name;
                $internship_promoter_branch = ' - '.$internship->promoter->name;
            } else {
                $internship_promoter = $internship->promoter->name;
                $internship_promoter_branch = '';
            }
        } else {
            $internship_promoter = '';
            $internship_promoter_branch = '';
        }
        $internship_lpersons_text = '';
        foreach($internship->lperson AS $internship_lperson) {
            $internship_lperson_name = _strformat($internship_lperson->name);
            if ($internship_lperson->flg_primary) {
                $internship_lpersons_text .= '<b>' . $internship_lperson_name . '</b>'.'<br/>';
            } else {
                $internship_lpersons_text .= $internship_lperson_name . '<br/>';
            }
        }
        $internship_host_tutors_text = '';
        foreach($internship->host->tutor AS $host_tutor) {
            $host_tutor_name = _strformat($host_tutor->title).' '.
                _strformat($host_tutor->firstname).' '._strformat($host_tutor->lastname);
            if ($host_tutor->flg_primary) {
                $internship_host_tutors_text .= '<b>' . $host_tutor_name . '</b>'.'<br/>';
            } else {
                $internship_host_tutors_text .= $host_tutor_name . '<br>';
            }
        }
        $internship_host_cperson_text = '';
        foreach($internship->project_contacts AS $cperson) {
            $cperson_name = _strformat($cperson->title).' '.
                _strformat($cperson->firstname).' '._strformat($cperson->lastname);
            if ($cperson->flg_primary) {
                $internship_host_cperson_text .= '<b>' . $cperson_name . '</b>'.'<br/>';
            } else {
                $internship_host_cperson_text .= $cperson_name . '<br/>';
            }
        }
        if($internship->internship_state->state >=1 && $internship->internship_state->state < 4) {
            $link = l($internship->id_internship, 'internship/new/'.((int)$internship->internship_state->state +1).'/'.$internship->id_internship);
            $url = 'internship/new/'.((int)$internship->internship_state->state +1).'/'.$internship->id_internship;
        } else {
            $link = l($internship->id_internship, 'internship/manage/'.$internship->id_internship);
            $url = 'internship/manage/'.$internship->id_internship;
        }

        // Button
        if (array_key_exists('3',$user->roles) || array_key_exists('4',$user->roles)) { // se è un amministratore oppure un operatore
            $form['remove_internship_' . $internship->id_internship] = array(
                '#type' => 'submit',
                '#name' => 'remove_internship_' . $internship->id_internship,
                '#value' => '',
                '#submit' => array('remove_internship_submit'),
                '#id' => 'edit-remove-agreement-' . $internship->id_internship,
                '#attributes' => array(
                    'id_internship' => $internship->id_internship,
                    'class' => array('btn', 'glyphicon', 'glyphicon-trash'),
                    'onclick' => 'if(!confirm("Sei sicuro di voler eliminare il Tirocinio? I dati andranno persi definitivamente.")){return false;}'
                ),
            );
        }
        $form['view_intern_' . $internship->id_internship] = array(
            '#type' => 'submit',
            '#value' => '',
            '#name' => 'view_intern_' . $internship->id_internship,
            '#submit' => array('view_intern_submit'),
            '#id' => 'edit-view-intern-submit-' . $internship->id_internship,
            '#attributes' => array(
                'id_internship' => $internship->id_internship,
                'id_internship_person' => $internship->person->id_internship_person,
                'class' => array('btn', 'glyphicon', 'glyphicon-eye-open'),
            ),
        );

        $rows[$key][1] = $link;
        $rows[$key][] = $internship->person->firstname.' '.$internship->person->lastname.'<br>'.$internship->person->tax_code;
        $rows[$key][] = getInternDataByInternshipObj($internship,false);
        $rows[$key][] = drupal_render($form['view_intern_' . $internship->id_internship]);
        $rows[$key][] =
            '<b>N.IZSLER: </b>'.$internship->agreement->number_code.'<br>'.
            '<b>S.Promotore: </b>'.$internship_promoter.' '.$internship_promoter_branch.'<br>';
        $rows[$key][] = !empty($internship_lpersons_text)?$internship_lpersons_text:'-';
        $rows[$key][] = !empty($internship_promoter_tutor_text)?$internship_promoter_tutor_text:'-';
        $rows[$key][] = !empty($internship_host_tutors_text)?$internship_host_tutors_text:'-';
        $rows[$key][] = !empty($internship_host_cperson_text)?$internship_host_cperson_text:'-';
        $rows[$key][] = !empty($internship->internship_state->date_start)?
            date('d-m-Y',strtotime($internship->internship_state->date_start)):
            date('d-m-Y',strtotime($internship->date_start));
        $rows[$key][] = !empty($internship->internship_state->date_start)?(
        !empty($internship->internship_state->date_end)?
            date('d-m-Y',strtotime($internship->internship_state->date_end)):
            date('d-m-Y',strtotime($internship->internship_state->date_end_expected))
        ):(date('d-m-Y',strtotime($internship->date_end)));
        $rows[$key][] = getInternshipStateText($internship);

        $rows[$key][] = ($internship->internship_state->state==0 || $internship->internship_state->state==5 || $internship->internship_state->state==6 || $internship->internship_state->state==7)?
            t('<a href="@url"><span class="glyphicon glyphicon-edit"></span> Registro</a>', array(
                '@url' => url('internship/attendance/'.$internship->id_internship.'/'.date('m',strtotime($internship->internship_state->date_start)).'/'.date('y',strtotime($internship->internship_state->date_start))),
            )):'';
        if (array_key_exists('3',$user->roles) || array_key_exists('4',$user->roles)) { // se è un amministratore oppure un operatore
            $rows[$key][] = t('<a href="@url"><span class="btn glyphicon glyphicon-pencil"></span>&nbsp;</a>', array(
                    '@url' => url($url),
                )).
                drupal_render($form['remove_internship_'.$internship->id_internship]
                );
        } else {
            $rows[$key][] = t('-');
        }

    }
    $header = array(
        array('data' => t('ID'), 'class' => ''),
        array('data' => t('Tirocinante'), 'class' => 'details-control'),
        array('data' => t('Dati tirocinante'), 'class' => ''),
        array('data' => t('Link tirocinante'), 'class' => 'notexport'),
        array('data' => t('Convenzione'), 'class' => ''),
        array('data' => t('Strutture Osp.'), 'class' => ''),
        array('data' => t('Tutor S.P.'), 'class' => ''),
        array('data' => t('Tutor S.O.'), 'class' => ''),
        array('data' => t('Resp./Ref. S.O.'), 'class' => ''),
        array('data' => t('Data inizio'), 'class' => ''),
        array('data' => t('Data fine'), 'class' => ''),
        array('data' => t('Stato'), 'class' => ''),
        array('data' => t('Registro'), 'class' => 'notexport'),
        array('data' => t('Azioni'), 'class' => 'notexport')
    );

    $form['filter_panel']['state'] = array(
        '#type' => 'select',
        '#title' => 'Stato tirocinio:',
        '#options' => GETIF_REPORT_STATES,
        '#default_value' => $state_default_value,
    );

    $form['filter_panel']['save'] = array(
        '#type' => 'submit',
        '#value' => 'Filtra',
    );

    if (isset($_GET['state'])) {
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
        '#value' => t('Nuovo').' '.t('Tirocinio'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_new'),
        '#access' => !$user_is_tutor
    );


    $form['fs_table_panel'] = array(
        '#type' => 'container',
        '#title' => 'Lista tirocini',
        '#title_display' => 'invisible',
        '#access' =>true
    );

    $form['fs_table_panel']['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => !empty($rows)?$rows:array(0=>array()),
        '#empty' => t('Table has no row!'),
        '#attributes' => array(
            'id' => 'tabella'
        )
    );
    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function goto_new($form, &$form_state) {
    getif_goto('internship/new/1',array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function internship_list_view_form_validate($form, &$form_state) {
    //empty
}

/**
 * @param $form
 * @param $form_state
 */
function internship_list_view_form_submit($form, &$form_state) {
    if (!empty($form_state['clicked_button']['#attributes']['reset'])) {
        drupal_goto('internship/list/', array());
    } else
        drupal_goto('internship/list/', array('query' => array('state' => $form_state['values']['state'])));
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
 */
function remove_internship_submit($form, &$form_state) {
    $id_internship = $form_state['clicked_button']['#attributes']['id_internship'];
    delete_internship_step_data($id_internship,1);
}

/**
 * @param $form
 * @param $form_state
 */
function view_intern_submit($form, &$form_state) {
    $id_internship = $form_state['clicked_button']['#attributes']['id_internship'];
    $id_internship_person = $form_state['clicked_button']['#attributes']['id_internship_person'];
    $destination = 'intern/view/' . $id_internship_person;
    session_set('id_internship', $id_internship);
    getif_goto($destination,array(),302,true);
}

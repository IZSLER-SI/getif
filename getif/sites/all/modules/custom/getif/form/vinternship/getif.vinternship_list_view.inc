<?php

/**
 * Theme lista frequenze
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_vinternship_list_view_form($variables){
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_js(strtr('
            function format ( d ) {
                // `d` is the original data object for the row
                return \'<table cellpadding="5" cellspacing="5" border="0" style="padding-left:50px;">\'+
                    \'<tr>\'+
                        \'<td valign="top" style="padding:5px"><b>Dettagli frequentatore:</b></td>\'+
                        \'<td valign="top" style="padding:5px">\'+d.dati_frequentatore+\'</td>\'+
                        \'<td valign="top" style="padding:5px">\'+d.link_frequentatore+\'</td>\'+
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
                            title: "frequenze_'.date("d-m-Y").'",
                            exportOptions: {
                                columns: \':not(.notexport)\'
                            }
                        } ),
                        jQuery.extend( true, {}, fixNewLine, {
                            extend: \'excelHtml5\',
                            title: "frequenze_'.date("d-m-Y").'",
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
                            "data":           "frequentatore",
                            "defaultContent": ""
                        },
                        { "data": "dati_frequentatore" },
                        { "data": "link_frequentatore" },
                        { "data": "ente_promotore" },
                        { "data": "strutture_so" },
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
                        { type: "date-eu", targets: [7] },
                        { type: "date-eu", targets: [8] },
                        { orderable: false, targets: [10] },
                        { orderable: false, targets: [11] },
                        { responsivePriority: 1, targets: 0 },
                        { responsivePriority: 1, targets: 11 },
                        { responsivePriority: 1, targets: 10 }
                    ],
                    order: [[ 0, "desc" ]],
                    responsive: @responsive,
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
                jQuery("div.toolbar_top").html("<h3 style=\"margin-top:0\">Esporta:</h3>");
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
 * Form lista frequenze
 * @param $form
 * @param $form_state
 * @return mixed
 */
function vinternship_list_view_form($form, &$form_state) {
    global $user;
    // Top Buttons
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back')
    );

    db_set_active('getif_data');
    $query = db_select('internship', 't1');
    $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
    $query
        ->fields('t1', array('id_internship', 'date_start', 'date_end'))
        ->fields('t2', array('state'))
        ->condition("t1.flg_voluntary",1,'=') // è una frequenza volontaria
        ->condition("t1.active",1,'=')
        ->condition("t2.active",1,'=');
    // filtro tutor
    if (in_array('tutor',$user->roles)) {
        $id_person = $_SESSION['user']['id_person'];
        $query1 = db_select('internship_project_contact','t1');
        $query1->innerJoin('person_lperson_prole','t2','t1.id_person_lperson_prole = t2.id_person_lperson_prole AND id_prole = 3');
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
        $internship = getVInternshipById('getif_data', $item->id_internship);
        $contact_institution = ' - ';
        $attended_course = ' - ';
        if (!empty($internship->person->attended_course)) {
            $attended_course_obj = json_decode($internship->person->attended_course);
            if (!empty($attended_course_obj->name)) {
                $attended_course = $attended_course_obj->name;
            }
            if (!empty($attended_course_obj->contact_institution)) {
                $contact_institution = $attended_course_obj->contact_institution;
            }
        }
        $internship_lpersons_text = '';
        foreach($internship->lperson AS $internship_lperson) {
            $internship_lperson_name = _strformat($internship_lperson->name);
            if ($internship_lperson->flg_primary) {
                $internship_lpersons_text .= '<b>' . $internship_lperson_name . '</b>'.'<br>';
            } else {
                $internship_lpersons_text .= $internship_lperson_name . '<br>';
            }
        }
        $internship_host_cperson_text = '';
        foreach($internship->project_contacts AS $cperson) {
            $cperson_name = _strformat($cperson->title).' '.
                _strformat($cperson->firstname).' '._strformat($cperson->lastname);
            if ($cperson->flg_primary) {
                $internship_host_cperson_text .= '<b>' . $cperson_name . '</b>'.'<br>';
            } else {
                $internship_host_cperson_text .= $cperson_name . '<br>';
            }
        }
        if($internship->internship_state->state >=1 && $internship->internship_state->state < 4) {
            $link = l($internship->id_internship, 'vinternship/new/'.((int)$internship->internship_state->state +1).'/'.$internship->id_internship);
            $url = 'vinternship/new/'.((int)$internship->internship_state->state +1).'/'.$internship->id_internship;
        } else {
            $link = l($internship->id_internship, 'vinternship/manage/'.$internship->id_internship);
            $url = 'vinternship/manage/'.$internship->id_internship;
        }

        // Button
        if (array_key_exists('3',$user->roles) || array_key_exists('4',$user->roles)) { // se è un amministratore oppure un operatore
            $form['remove_internship_' . $internship->id_internship] = array(
                '#type' => 'submit',
                '#name' => 'remove_internship_' . $internship->id_internship,
                '#value' => '',
                '#submit' => array('remove_vinternship_submit'),
                '#id' => 'edit-remove-agreement-' . $internship->id_internship,
                '#attributes' => array(
                    'id_internship' => $internship->id_internship,
                    'class' => array('btn', 'glyphicon', 'glyphicon-trash'),
                    'onclick' => 'if(!confirm("Sei sicuro di voler eliminare la frequenza volontaria? I dati andranno persi definitivamente.")){return false;}'
                ),
            );
        }
        $rows[$key][1] = $link;
        $rows[$key][] = $internship->person->firstname.' '.$internship->person->lastname.'<br>'.$internship->person->tax_code;
        $rows[$key][] = getVInternDataByInternshipObj($internship,false);
        $rows[$key][] = strtr('<a href="@url"><span class="btn glyphicon glyphicon-eye-open"></span>Vedi</a>', array(
            '@url' => url('vintern/view/'.((int)$internship->person->id_internship_person))));
        $rows[$key][] = $contact_institution;
        $rows[$key][] = $internship_lpersons_text;
        $rows[$key][] = $internship_host_cperson_text;
        $rows[$key][] = !empty($internship->internship_state->date_start)?
            date('d-m-Y',strtotime($internship->internship_state->date_start)):
            date('d-m-Y',strtotime($internship->date_start));
        $rows[$key][] = !empty($internship->internship_state->date_start)?(
        !empty($internship->internship_state->date_end)?
            date('d-m-Y',strtotime($internship->internship_state->date_end)):
            date('d-m-Y',strtotime($internship->internship_state->date_end_expected))
        ):(date('d-m-Y',strtotime($internship->date_end)));
        $rows[$key][] = getVInternshipStateText($internship);
        $rows[$key][] = ($internship->internship_state->state==0 || $internship->internship_state->state==5 || $internship->internship_state->state==6 || $internship->internship_state->state==7)?
            t('<a href="@url"><span class="glyphicon glyphicon-edit"></span> Registro</a>', array(
                '@url' => url('vinternship/attendance/'.$internship->id_internship.'/'.date('m',strtotime($internship->internship_state->date_start)).'/'.date('y',strtotime($internship->internship_state->date_start))),
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
        array('data' => t('Frequentatore'), 'class' => 'details-control'),
        array('data' => t('Dati frequentatore'), 'class' => ''),
        array('data' => t('Link frequentatore'), 'class' => 'notexport'),
        array('data' => t('Ente promotore'), 'class' => ''),
        array('data' => t('Strutture Osp.'), 'class' => ''),
        array('data' => t('Resp./Ref. S.O.'), 'class' => ''),
        array('data' => t('Data inizio'), 'class' => ''),
        array('data' => t('Data fine'), 'class' => ''),
        array('data' => t('Stato'), 'class' => 'notexport'),
        array('data' => t('Registro'), 'class' => 'notexport'),
        array('data' => t('Azioni'), 'class' => 'notexport')
    );

    $states = array(
        'all' => '- Seleziona -',
        'pending' => 'Pratiche non terminate',
        '0' => 'Interrotte',
        '5' => 'Attive',
        '6' => 'Prorogate',
        '7' => 'Concluse',

    );

    $form['filter_panel']['state'] = array(
        '#type' => 'select',
        '#title' => 'Stato frequenza:',
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
        '#value' => t('Nuova').' '.t('Frequenza volontaria'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_new'),
        '#access' => !$user_is_tutor
    );


    $form['fs_table_panel'] = array(
        '#type' => 'item',
        '#title' => 'Lista frequenze',
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
    getif_goto('vinternship/new/1',array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function vinternship_list_view_form_validate($form, &$form_state) {
    //empty
}

/**
 * @param $form
 * @param $form_state
 */
function vinternship_list_view_form_submit($form, &$form_state) {
    if (!empty($form_state['clicked_button']['#attributes']['reset'])) {
        drupal_goto('vinternship/list/', array());
    } else
        drupal_goto('vinternship/list/', array('query' => array('state' => $form_state['values']['state'])));
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
function remove_vinternship_submit($form, &$form_state) {
    $id_internship = $form_state['clicked_button']['#attributes']['id_internship'];
    delete_vinternship_step_data($id_internship,1);
}
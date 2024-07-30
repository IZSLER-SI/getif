<?php

/**
 * Form presenze_servizio
 * @param $variables
 * @return mixed
 */

function theme_presenze_servizio_form($variables){
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    drupal_add_js('
            /* Formatting function for row details - modify as you need */
            function format ( d ) {
                // `d` is the original data object for the row
                return \'<table cellpadding="5" cellspacing="0" border="0" style="padding-left:50px;">\'+
                    \'<tr>\'+
                        \'<td>Full name:</td>\'+
                        \'<td>\'+d.name+\'</td>\'+
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
                            return strip_html_tags(data.replace( /<br\s*\/?>/gi,"\r\n"));
                        }
                    }
                }
            };
            jQuery(function($) {
                var table = $("#tabella").DataTable( {
                    dom: "<\"toolbar_top\">B<\"toolbar_ex\">lfrtip",
                    buttons:[
                        $.extend( true, {}, fixNewLine, {
                            extend: \'csvHtml5\',
                            title: "report_id'.(!empty($_GET['internship'])?$_GET['internship']:'')."_".date("d-m-Y").'"
                        } ),
                        $.extend( true, {}, fixNewLine, {
                            extend: \'excelHtml5\',
                            title: "report_id'.(!empty($_GET['internship'])?$_GET['internship']:'')."_".date("d-m-Y").'"
                        } ),
                    ],
                    rowsGroup: [
                        0,1,2
                    ],
                    
                    pageLength: 30,
                    "scrollX": false,
                    //responsive: true,
                    columnDefs: [
                        { orderable: false, targets: [0] },
                        { orderable: false, targets: [1] },
                        { orderable: false, targets: [2] }
                     ],
                    "order": [[ 0, "desc" ]],
                    lengthMenu: [[10, 25, 50, 100, -1], [10, 25, 50, 100, "Tutti"]],
                    language: {
                        "emptyTable":     "Nessun elemento.",
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
                $("div.toolbar_top").html("<h3>Esporta:</h3>");
                $("div.toolbar_ex").html("<br/>");
                // Add event listener for opening and closing details
                $(\'#tabella tbody\').on(\'click\', \'td.details-control\', function () {
                    var tr = $(this).closest(\'tr\');
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
            jQuery.extend( jQuery.fn.dataTableExt.oSort, {
                "date-eu-pre": function ( date ) {
                    date = date.replace(" ", "");
                     
                    if ( ! date ) {
                        return 0;
                    }
             
                    var year;
                    var eu_date = date.split(/[\.\-\/]/);
             
                    /*year (optional)*/
                    if ( eu_date[2] ) {
                        year = eu_date[2];
                    }
                    else {
                        year = 0;
                    }
             
                    /*month*/
                    var month = eu_date[1];
                    if ( month.length == 1 ) {
                        month = 0+month;
                    }
             
                    /*day*/
                    var day = eu_date[0];
                    if ( day.length == 1 ) {
                        day = 0+day;
                    }
             
                    return (year + month + day) * 1;
                },
             
                "date-eu-asc": function ( a, b ) {
                    return ((a < b) ? -1 : ((a > b) ? 1 : 0));
                },
             
                "date-eu-desc": function ( a, b ) {
                    return ((a < b) ? 1 : ((a > b) ? -1 : 0));
                }
            } );
            ',array('type'=>'inline','scope' => 'footer'));
    $form = $variables['form'];
    $header_content = array();
    $vars = array(
        '{$title}'      => drupal_get_title(),
        '{$filter}'     => drupal_render($form['filter_panel'])
    );
    $output = '
        <div class="row">
            <div class="col-md-12 form-container">
                '.$form['fs_table_panel']['table']['#prefix'].'
                <fieldset class="panel panel-default form-wrapper">
                    <div class="panel-body">
                        <p>
                            <button class="btn btn-primary" type="button" data-toggle="collapse" data-target="#collapse1" aria-expanded="false" aria-controls="collapse1">
                                Mostra/Nascondi filtri
                            </button>
                        </p>
                        <div class="collapse in" id="collapse1" aria-expanded="true">
                            <div class="card card-body">
                                {$filter}
                            </div>
                        </div>
                    </div>
                </fieldset>
            </div>
        </div>
    ';
    unset($form['fs_table_panel']['table']['#prefix']);
    $output = strtr($output,$vars);
    $header_content[] = array('html' => $output,'has_separator' => false);
    $options = array();
    $options['show_fs_title'] = false;
    return getif_form_theme($form,$header_content,$options);
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function presenze_servizio_form($form, &$form_state) {
    $reset_enabled = false;
    // Top Buttons
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back'),
    );
    $form['nav']['goto_list'] = array(
        '#type' => 'button',
        '#value' => t('Report'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'report'
        )
    );
    // Filtri
    $form['filter_panel']['internship'] = array(
        '#type' => 'textfield',
        '#title' => t('Tirocinio'),
        '#size' => 120,
        '#maxlength' => 120,
        '#autocomplete_path' => 'internship_intern_autocomplete_callback',
        '#required' => true,
        '#attributes' => array(
            'autocomplete' => 'off',
        ),
    );
    // ID del tirocinio
    $form['filter_panel']['internship_id'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'id' => 'edit-internship_id'
        )
    );

    $form['filter_panel']['save'] = array(
        '#type' => 'submit',
        '#value' => 'Filtra',
    );
    $form['filter_panel']['reset'] = array(
        '#type' => 'submit',
        '#value' => 'Reset',
        '#access' => false,
        '#attributes' => array(
            'reset' => true
        ),
        '#prefix' => '<div class="container-inline">',
        '#suffix' => '</div>',
    );
    $form['fs_table_panel'] = array(
        '#type' => 'item',
        '#title' => 'Presenze in orario di servizio ',
        '#title_display' => 'invisible',
        '#access' => true,
    );
    // Tabella
    $header = array(
        t('ID tirocinio'),
        t('Cognome'),
        t('Nome'),
        t('Giorno'),
        t('Orario Registro'),
        t('Orario Dipendente')
    );
    $form['fs_table_panel']['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#empty' => t('Table has no row!'),
        '#attributes' => array(
            'id' => 'tabella'
        ),
        '#prefix' => '<p><span class="glyphicon glyphicon-info-sign"></span>&nbsp;Report delle date dei tirocini di un dipendente in conflitto con orario di servizio per verifica da U.O. Personale.</p>'
    );

    // Popolare tabella se è stato selezionato un tirocinante
    if (isset($_GET['internship'])) {
        $reset_enabled = true;
        // Query
        db_set_active('getif_data');
        $query = db_select('internship', 't1');
        $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
        $query
            ->fields('t1', array('id_internship', 'date_start', 'date_end'))
            ->fields('t2', array('state'))
            ->condition("t1.flg_voluntary", 0, '=')// è una frequenza volontaria
            ->condition("t1.active", 1, '=')
            ->condition("t2.active", 1, '=');

        // filtro tirocinante
        $query->condition('t1.id_internship', $_GET['internship']);

        // filtro data
        if (isset($_GET['from']) && isset($_GET['to'])) {
            $query->condition('t2.date_start', date('Y-m-d', strtotime($_GET['from'])), '>=');
            $query->condition('t2.date_start', date('Y-m-d', strtotime($_GET['to'])), '<=');
            $form['filter_panel']['date_start']['#default_value'] = date('d-m-Y', strtotime($_GET['from']));
            $form['filter_panel']['date_end']['#default_value'] = date('d-m-Y', strtotime($_GET['to']));
            $reset_enabled = true;
        }
        // filtro stato
        $query->condition('t2.state', array(0, 5, 6, 7), 'IN'); // tirocini 5 - attivi, 6 - prorogati, 7- conclusi, 0 - interrotti
        $results = (object)$query->execute()->fetchAssoc();
        db_set_active();
        if (!empty($results->id_internship)) {
            $internship = getInternshipById('getif_data', $results->id_internship);
            $form['fs_table_panel']['#title'] = $form['fs_table_panel']['#title'] . ' ' . $internship->person->firstname . ' ' . $internship->person->lastname;
            $internship_register_base64 = !empty($internship->attendance_sheet->register) ? $internship->attendance_sheet->register : '';
            if (!empty($internship_register_base64)) {
                $internship_register = base64_decode($internship_register_base64);
                $form_state_input_container = json_decode($internship_register, true);
                $form_state_time_keys = processTimeKeys($form_state_input_container);
            }
            $date_start_effective = $internship->internship_state->date_start;
            if (empty($internship->internship_state->date_end)) {
                $datetime1 = new DateTime($internship->date_start);
                $datetime2 = new DateTime($internship->date_end);
                $interval = $datetime1->diff($datetime2);
                $date_end_effective = date('Y-m-d', strtotime($date_start_effective . '+' . $interval->format('%R%a days')));
            } else {
                $date_end_effective = $internship->internship_state->date_end;
            }
            $working_times = (json_decode($internship->person->working_time));
            $working_times_array = array();
            $rows = array();
            if(!empty($working_times)) {
                foreach ($working_times as $key_wt => $working_time) {
                    if (!empty($working_time[0]) || !empty($working_time[2])) {
                        if (!empty($working_time[0])) {
                            $working_times_array[MAPPING_DAYS[$key_wt]][] = $working_time[0];
                            $working_times_array[MAPPING_DAYS[$key_wt]][] = $working_time[1];
                        }
                        if (!empty($working_time[2])) {
                            $working_times_array[MAPPING_DAYS[$key_wt]][] = $working_time[2];
                            $working_times_array[MAPPING_DAYS[$key_wt]][] = $working_time[3];
                        }
                    }
                }
                $dates = dateRange($date_start_effective, $date_end_effective);
                foreach ($dates as $key => $date) {
                    $form_state['time_keys_' . $key] = !empty($form_state_time_keys[$date]) ? $form_state_time_keys[$date] : array(0 => 0);
                    $time_keys = $form_state['time_keys_' . $key];
                    $is_overlapped = false;
                    $testo = '';
                    foreach ($time_keys as $time_key) {
                        if (!empty($time_key['ora_da']) && $time_key['ora_a']) {
                            $time_attendance = !empty($time_key['ora_da']) ? 'da: ' . $time_key['ora_da'] . ' ' : '';
                            $time_attendance .= !empty($time_key['ora_a']) ? 'a: ' . $time_key['ora_a'] . ' ' : '';
                            $t11 = $time_key['ora_da'];
                            $t12 = $time_key['ora_a'];
                            if (!empty($working_times_array[ucwords(strftime("%a", strtotime($date)))])) {
                                $n = count($working_times_array[ucwords(strftime("%a", strtotime($date)))]);
                                for ($i = 0; $i < $n; $i = $i + 2) {
                                    $t01 = $working_times_array[ucwords(strftime("%a", strtotime($date)))][$i];
                                    $t02 = $working_times_array[ucwords(strftime("%a", strtotime($date)))][$i + 1];
                                    if ((date($t11) < date($t01) && date($t12) <= date($t01)) || date($t11) >= date($t02)) {
                                        $testo .= '';
                                    } else {
                                        $testo .= '<div class="alert-danger">' . $time_attendance . '</div>';
                                        $is_overlapped = true;
                                    }
                                }
                            } else {
                                $testo .= '<div class="alert-success">' . $time_attendance . '</div>';
                            }
                        }
                    }
                    if ($is_overlapped == true) {
                        $rows[$key][1] = $internship->id_internship;
                        $rows[$key][] = $internship->person->firstname;
                        $rows[$key][] = $internship->person->lastname;
                        $rows[$key][] = ucwords(strftime("%A, %d %b %G", strtotime($date)));
                        $rows[$key][] = $testo;
                        if (!empty($working_times_array[ucwords(strftime("%a", strtotime($date)))])) {
                            $time_employer_text = $working_times_array[ucwords(strftime("%a", strtotime($date)))][0] . ' ' . $working_times_array[ucwords(strftime("%a", strtotime($date)))][1];
                            if (count($working_times_array[ucwords(strftime("%a", strtotime($date)))]) > 2) {
                                $time_employer_text .= '<br>' . $working_times_array[ucwords(strftime("%a", strtotime($date)))][2] . ' ' . $working_times_array[ucwords(strftime("%a", strtotime($date)))][3];
                            }
                            $rows[$key][] = $time_employer_text;
                        } else {
                            $rows[$key][] = '';
                        }
                    }

                }
            }
            $form['filter_panel']['internship']['#default_value'] = 'Tir. #' . $internship->id_internship . ' ' . $internship->person->tax_code . ' - ' . $internship->person->firstname . ' ' . $internship->person->lastname;
            $form['filter_panel']['internship_id']['#value'] = $internship->id_internship;
            $form['fs_table_panel']['table']['#rows'] = $rows;
            drupal_get_messages();
        } else {
            $form['fs_table_panel']['table']['#rows'] = array();
            $internship = getInternshipById('getif_data', $_GET['internship']);
            $form['filter_panel']['internship']['#default_value'] = 'Tir. #' . $internship->id_internship . ' ' . $internship->person->tax_code . ' - ' . $internship->person->firstname . ' ' . $internship->person->lastname;
            $form['filter_panel']['internship_id']['#value'] = $internship->id_internship;
        }
        if ($reset_enabled) {
            $form['filter_panel']['reset']['#access'] = true;
        }
    }
    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function presenze_servizio_form_validate($form, &$form_state) {
    //empty
}

/**
 * @param $form
 * @param $form_state
 */
function presenze_servizio_form_submit($form, &$form_state)
{
    if (!empty($form_state['clicked_button']['#attributes']['reset'])) {
        drupal_goto(current_path().'/', array());
    } else {
        $query = array();
        if (!empty($form_state['input']['internship_id'])) {
            $query['internship'] = $form_state['input']['internship_id'];
        }
        if (!empty($form_state['values']['date_start']) && !empty($form_state['values']['date_end'])) {
            $query['from'] = $form_state['values']['date_start'];
            $query['to'] = $form_state['values']['date_end'];
        }
        drupal_goto(current_path().'/', array('query' => $query));
    }
}

/**
 * @param $form
 * @param $form_state
 */
function go_back ($form, &$form_state) {
    getif_goto('',array(),302,true);
}

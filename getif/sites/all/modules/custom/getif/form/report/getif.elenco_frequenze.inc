<?php

/**
 * Form report12
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_elenco_frequenze_form($variables){
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
        '{$filter}'     => drupal_render($form['filter_panel']),
        '{$view}'       => drupal_render($form['view_panel']),
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
                            <button class="btn btn-primary" type="button" data-toggle="collapse" data-target="#collapse2" aria-expanded="false" aria-controls="collapse2">
                                Mostra/Nascondi colonne
                            </button>
                        </p>
                        <div class="collapse in" id="collapse1" aria-expanded="true">
                            <div class="card card-body">
                                {$filter}
                            </div>
                        </div>
                         <div class="collapse" id="collapse2" aria-expanded="true">
                            <div class="card card-body">
                                {$view}
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
function elenco_frequenze_form($form, &$form_state) {
    global $user;
    $reset_enabled = false;
    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
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

    db_set_active('getif_data');
    $query = db_select('internship', 't1');
    $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
    $query
        ->fields('t1', array('id_internship', 'date_start', 'date_end'))
        ->fields('t2', array('state'))
        ->condition("t1.flg_voluntary",1,'=') // è una frequenza volontaria
        ->condition("t1.active",1,'=')
        ->condition("t2.active",1,'=');

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
    // filtro data
    $date_type = isset($_GET['date_type'])?$_GET['date_type']:'';
    if (isset($_GET['from']) && isset($_GET['to'])) {
        if ($date_type == 'date_application') {
            $query->condition('t1.date_application', date('Y-m-d', strtotime($_GET['from'])), '>=');
            $query->condition('t1.date_application', date('Y-m-d', strtotime($_GET['to'])), '<=');
        } elseif ($date_type == 'date_start') {
            $query->condition('t2.date_start', date('Y-m-d', strtotime($_GET['from'])), '>=');
            $query->condition('t2.date_start', date('Y-m-d', strtotime($_GET['to'])), '<=');
        } elseif ($date_type == 'date_end') {
            $query->condition('t2.date_end', date('Y-m-d', strtotime($_GET['from'])), '>=');
            $query->condition('t2.date_end', date('Y-m-d', strtotime($_GET['to'])), '<=');
        }
    }
    $results = $query
        ->execute();
    db_set_active();
    $rows = array();
    foreach($results as $key => $item) {
        $internship = getVInternshipById('getif_data', $item->id_internship);
        $internship_host_cperson_text = '';
        $internship_host_cpersons_text = '<b>Referenti:</b><br/>';
        foreach($internship->project_contacts AS $cperson) {
            $cperson_name = _strformat($cperson->title).' '.
                _strformat($cperson->firstname).' '._strformat($cperson->lastname).'<br>';
            if ($cperson->flg_primary) {
                $internship_host_cperson_text .= $cperson_name .'<br>';
            } else {
                $internship_host_cpersons_text .= $cperson_name . '<br>';
            }
        }
        $attended_course = '';
        $contact_institution = '';
        if (!empty($internship->person->attended_course)) {
            $attended_course_obj = json_decode($internship->person->attended_course);
            if (!empty($attended_course_obj->contact_institution)) {
                $contact_institution = $attended_course_obj->contact_institution;
            }
            if (!empty($attended_course_obj->name)) {
                $attended_course = $attended_course_obj->name;
            }
        }

        $rc_policy = !empty($internship->insurance->rc_policy)?json_decode($internship->insurance->rc_policy):'';
        $accident_policy = !empty($internship->insurance->accident_policy)?json_decode($internship->insurance->accident_policy):'';

        // popola righe
        $rows[$key][1] = $internship->id_internship;
        $rows[$key][] = $contact_institution;
        $rows[$key][] = $attended_course;
        $rows[$key][] = $internship->person->firstname;
        $rows[$key][] = $internship->person->lastname;
        $rows[$key][] = $internship->person->qualification;
        $rows[$key][] = getVInternDataByInternshipObj($internship,false);
        $rows[$key][] = !empty($internship->lperson_primary->name)?$internship->lperson_primary->name:'';
        $rows[$key][] = date('d-m-Y',strtotime($internship->date_application));
        $rows[$key][] = date('d-m-Y',strtotime($internship->date_start));
        $rows[$key][] = date('d-m-Y',strtotime($internship->internship_state->date_start));
        $rows[$key][] = !empty($internship->internship_state->date_extension)?'Si':'No';
        $rows[$key][] = !empty($internship->internship_state->date_end)?
            format_date(strtotime($internship->internship_state->date_end),'custom','d-m-Y',date_default_timezone()):
            format_date(strtotime($internship->internship_state->date_end_expected),'custom','d-m-Y',date_default_timezone());

        $rows[$key][] = !empty($internship->internship_state->date_end)?
                format_date(strtotime($internship->internship_state->date_end),'custom','d-m-Y',date_default_timezone()):
                '';
        $rows[$key][] = !empty($rc_policy)?$rc_policy->company:'';
        $rows[$key][] = !empty($rc_policy)?$rc_policy->policy_number:'';
        $rows[$key][] = !empty($accident_policy)?$accident_policy->company:'';
        $rows[$key][] = !empty($accident_policy)?$accident_policy->policy_number:'';
        $rows[$key][] = getInternshipStateText($internship);
        $rows[$key][] = $internship_host_cperson_text;

    }
    /* Filtri */
    // Filtro stato
    $form['filter_panel']['state'] = array(
        '#type' => 'select',
        '#title' => 'Stato:',
        '#options' => GETIF_REPORT_STATES,
        '#default_value' => $state_default_value,
    );

    // Filtro date da/a
    $form['filter_panel']['date_type'] = array(
        '#type' => 'select',
        '#title' => t('Tipo data:'),
        '#name' => 'date_type',
        '#empty_option' => 'Nessun filtro',
        '#options' => array(
            'date_application' => 'Data richiesta',
            'data_start' => 'Data inizio',
            'data_end' => 'Data fine'
        )
    );
    $form['filter_panel']['date_format'] = array(
        '#type' => 'select',
        '#title' => t('Formato data'),
        '#name' => 'date_format',
        '#options' => array(
            'year' => 'Anno',
            'range' => 'Data da/a'
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="date_type"]' => array('!value' => ''),
            ),
        ),
    );
    $form['filter_panel']['date_year'] = array(
        '#type' => 'date_select',
        '#title' => t('Anno'),
        '#date_timezone' => date_default_timezone(),
        '#date_format' => 'Y',
        '#date_year_range' => '2016:now',
        '#date_label_position' => 'within',
        '#default_value' => date('Y'),
        '#states' => array(
            'visible' => array(
                ':input[name="date_type"]' => array('!value' => ''),
                ':input[name="date_format"]' => array('value' => 'year')
            ),
            'required' => array(
                ':input[name="date_type"]' => array('!value' => ''),
                ':input[name="date_format"]' => array('value' => 'year')
            )
        ),

    );
    $form['filter_panel']['date_from'] = array(
        '#type' => 'textfield',
        '#title' => t('Da:'),
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date', 'js-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_start'
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="date_type"]' => array('!value' => ''),
                ':input[name="date_format"]' => array('value' => 'range')
            ),
            'required' => array(
                ':input[name="date_type"]' => array('!value' => ''),
                ':input[name="date_format"]' => array('value' => 'range')
            )
        )
    );
    $form['filter_panel']['date_to'] = array(
        '#type' => 'textfield',
        '#title' => t('A:'),
        '#attributes' => array(
            'autocomplete' => 'off',
            'maxlength' => 10,
            'class' => array('form-date', 'js-date'),
            'placeholder' => t('gg-mm-aaaa'),
            'range' => 'date_end',
        ),
        '#states' => array(
            'visible' => array(
                ':input[name="date_type"]' => array('!value' => ''),
                ':input[name="date_format"]' => array('value' => 'range')
            ),
            'required' => array(
                ':input[name="date_type"]' => array('!value' => ''),
                ':input[name="date_format"]' => array('value' => 'range')
            )
        )
    );

    $form['filter_panel']['save'] = array(
        '#type' => 'submit',
        '#value' => 'Filtra',
    );

    if (isset($_GET['date_type'])) {
        $form['filter_panel']['date_type']['#default_value'] = $_GET['date_type'];
        $date_format = isset($_GET['date_format'])?$_GET['date_format']:'';
        if ($date_format == 'year') {
            $form['filter_panel']['date_format']['#default_value'] = $date_format;
            $form['filter_panel']['date_year']['#default_value'] = date('Y',strtotime($_GET['from']));
            $reset_enabled = true;
        } elseif ($date_format == 'range') {
            $form['filter_panel']['date_format']['#default_value'] = $date_format;
            $form['filter_panel']['date_from']['#default_value'] = date('d-m-Y',strtotime($_GET['from']));
            $form['filter_panel']['date_to']['#default_value'] = date('d-m-Y',strtotime($_GET['to']));
            $reset_enabled = true;
        }
    }

    if ($reset_enabled) {
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
    $form['fs_table_panel'] = array(
        '#type' => 'container',
        '#title' => 'Report frequenze volontarie',
        '#title_display' => 'invisible',
        '#access' =>true
    );

    $date_label = array(
        1 => 'Data richiesta',
        2 => 'Data avvio prevista',
        3 => 'Data avvio effettiva',
        4 => 'Data prevista conclusione/proroga',
        5 => 'Data conclusione effettiva'
    );

    // Tabella
    $header = array(
        1 => t('ID'),
        t('Ente di riferimento'),
        t('Corso frequentato'),
        t('Cognome'),
        t('Nome'),
        t('Titolo di studio'),
        t('Dati frequentatore'),
        t('Struttura di attivazione'),
        $date_label[1],
        $date_label[2],
        $date_label[3],
        t('Proroga'),
        $date_label[4],
        $date_label[5],
        t('Compagnia RC'),
        t('Polizza RC'),
        t('Compagnia Infortuni'),
        t('Polizza infortuni'),
        t('Stato'),
        t('Note')
    );


    $form['view_panel']['scolumn'] = array(
        '#type' => 'checkboxes',
        '#title' => 'Mostra colonne:',
        '#name' => 'scolumn',
        '#options' => $header,
        '#attributes' => array(
            'class' => array('form-check-inline')
        )
    );

    if(!empty($_GET['hide'])) {
        $form['view_panel']['scolumn']['#default_value'] = explode('-',$_GET['hide']);


    }
    $form['fs_table_panel']['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('Table has no row!'),
        '#attributes' => array(
            'id' => 'tabella'
        ),
        '#prefix' => '<p><span class="glyphicon glyphicon-info-sign"></span>&nbsp;Elenco di tutte le frequenze volontarie.</p>'
    );

    $params['columnDefs'] = 'columnDefs: [';
    foreach ($date_label AS $date) {
        if (!empty(array_search($date,$header))) {
            $params['columnDefs'] .= '{ type: "date-eu", targets: '.array_search($date,array_values($header)).' },';
        }
    }
    $params['columnDefs'] .= '],';
    $script = '
        jQuery(function($) {
            var table = $("#tabella").DataTable( {
                dom: "<\"toolbar_top\">B<\"toolbar_ex\">lfrtip",
                buttons:[
                    $.extend( true, {}, fixNewLine, {
                        extend: \'csvHtml5\',
                        title: "report_'.date("d-m-Y").'",
                        exportOptions: {
                            columns: \':visible\'
                        }
                    } ),
                    $.extend( true, {}, fixNewLine, {
                        extend: \'excelHtml5\',
                        title: "report_'.date("d-m-Y").'",
                        exportOptions: {
                            columns: \':visible\'
                        }
                    } ),
                ],
                pageLength: 10,
                scrollX: false,
                orderCellsTop: true,
                fixedHeader: true,
                //responsive: true,
                '.$params['columnDefs'].'      
                order: [[ 0, "desc" ]],
                lengthMenu: [[10, 25, 50, 100, -1], [10, 25, 50, 100, "Tutti"]],
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
            $("div.toolbar_top").html("Esporta:<br/><br/>");
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
            $("input[id*=\'edit-scolumn-\'").each(function( index ) {
                $(this).attr("data-column",index);
                // Get the column API object
                var column = table.column( $(this).attr(\'data-column\') );
                // Toggle the visibility
                column.visible($(this).prop("checked"));
            });
            
            $("input[id*=\'edit-scolumn-\'").on("click", function (e) {
                // Get the column API object
                var column = table.column( $(this).attr(\'data-column\') );
                // Toggle the visibility
                column.visible($(this).prop("checked"));
            } );
        } );
     ';

    drupal_add_js($script,'inline');
    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function report_01_form_validate($form, &$form_state) {
    //empty
}

/**
 * @param $form
 * @param $form_state
 */
function elenco_frequenze_form_submit($form, &$form_state)
{
    if (!empty($form_state['clicked_button']['#attributes']['reset'])) {
        $query = array();
        if (!empty($form_state['values']['scolumn'])) {
            $query['hide'] = join($form_state['values']['scolumn'],'-');
        }
        drupal_goto(current_path(), array('query' => $query));
    } else {
        $query = array();
        if (in_array($form_state['values']['state'],array(0,7))) {
            $query['state'] = $form_state['values']['state'];
        } elseif (in_array($form_state['values']['state'],array(5,6))) {
            $query['state'] = 'active';
        } elseif (in_array($form_state['values']['state'],array(1,2,3,4))) {
            $query['state'] = 'pending';
        }
        if (!empty($form_state['values']['date_format']) && !empty($form_state['values']['date_type'])) {
            if ($form_state['values']['date_format'] == 'year') {
                if(!empty($form_state['values']['date_year'])) {
                    $query['date_type'] = $form_state['values']['date_type'];
                    $query['date_format'] = $form_state['values']['date_format'];
                    $query['from'] = '01-01-' . $form_state['values']['date_year'];
                    $query['to'] = '31-12-' . $form_state['values']['date_year'];
                }
            } else {
                $query['date_type'] = $form_state['values']['date_type'];
                $query['date_format'] = $form_state['values']['date_format'];
                $query['from'] = $form_state['values']['date_from'];
                $query['to'] = $form_state['values']['date_to'];
            }
        }
        if (!empty($form_state['values']['scolumn'])) {
            $query['hide'] = join($form_state['values']['scolumn'],'-');
        }
        drupal_goto(current_path(), array('query' => $query));
    }
}

/**
 * @param $form
 * @param $form_state
 */
function go_back ($form, &$form_state) {
    getif_goto('',array(),302,true);
}
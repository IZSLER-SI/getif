<?php

/**
 * Form elenco_tirocini
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_elenco_tirocini_form($variables){
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
function elenco_tirocini_form($form, &$form_state) {
    global $user;
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
    // Query
    db_set_active('getif_data');
    $query = db_select('internship', 't1');
    $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
    $query->innerJoin('lib_internship_type', 't3', 't1.id_internship_type = t3.id_internship_type');
    $query
        ->fields('t1', array('id_internship', 'date_start', 'date_end'))
        ->fields('t2', array('state'))
        ->condition("t1.flg_voluntary",0,'=') // è una frequenza volontaria
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
    // filtro tipo di tirocinio
    if (isset($_GET['itype'])) {
        $itype = explode('-',$_GET['itype']);
        $or = db_or();
        foreach($itype AS $value) {
            $or->condition('t3.flg_extra_curricular', strval(intval($value)-1));
        }
        $query->condition($or);
        if (isset($_GET['icat'])) {
            $icat = explode('-',$_GET['icat']);
            $or = db_or();
            foreach ($icat AS $value) {
                $or->condition('t3.id_internship_type', $value);
            }
            $query->condition($or);
        }
    }
    $results = $query
        ->execute();
    db_set_active();

    $rows = array();
    foreach($results as $key => $item) {
        $internship = getInternshipById('getif_data', $item->id_internship);
        // Soggetto promotore
        $internship_promoter_tutor_text = '';
        $internship_promoter = '';
        $internship_promoter_branch = '';
        if (!empty($internship->promoter)) {
            if ($internship->promoter->level == 1) {
                $internship_promoter = $internship->promoter->parent->name;
                $internship_promoter_branch = $internship->promoter->name;
            } else {
                $internship_promoter = $internship->promoter->name;
                $internship_promoter_branch = '-';
            }
            if (!empty($internship->promoter->tutor->lastname))
                $internship_promoter_tutor_text = '<b>' . _strformat($internship->promoter->tutor->title) . ' ' . _strformat($internship->promoter->tutor->firstname) . ' ' . _strformat($internship->promoter->tutor->lastname) . '</b>';
        }
        $internship_host_tutors_text = '<b>Tutor secondari:</b><br/>';
        $internship_host_tutor_text = '';
        foreach($internship->host->tutor AS $host_tutor) {
            $host_tutor_name = _strformat($host_tutor->title).' '.
                _strformat($host_tutor->firstname).' '._strformat($host_tutor->lastname);
            if ($host_tutor->flg_primary) {
                $internship_host_tutor_text .= $host_tutor_name;
            } else {
                $internship_host_tutors_text .= $host_tutor_name . '<br>';
            }
        }
        $internship_host_tutors_text .= '<hr/>';
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
        $attended_course = ' - ';
        if (!empty($internship->person->attended_course)) {
            $attended_course_obj = json_decode($internship->person->attended_course);
            if (!empty($attended_course_obj)) {
                $attended_course = $attended_course_obj->name;
            }
        }
        // Estremi assicurazioni
        $rc_policy = !empty($internship->insurance->rc_policy)?json_decode($internship->insurance->rc_policy):'';
        $accident_policy = !empty($internship->insurance->accident_policy)?json_decode($internship->insurance->accident_policy):'';
        // Dati
        $rows[$key][1] = $internship->id_internship;
        $rows[$key][] = $internship->agreement->number_code;
        $rows[$key][] = $internship_promoter;
        $rows[$key][] = $internship_promoter_branch;
        $rows[$key][] = $attended_course;
        $rows[$key][] = $internship->person->firstname;
        $rows[$key][] = $internship->person->lastname;
        $rows[$key][] = $internship->person->qualification;
        $rows[$key][] = getInternDataByInternshipObj($internship,false);
        $rows[$key][] = $internship->lperson_primary->name;
        $rows[$key][] = $internship_host_tutor_text;
        $rows[$key][] = $internship_promoter_tutor_text;
        $rows[$key][] = $internship_host_cperson_text;
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
        $rows[$key][] = $internship_host_tutors_text.$internship_host_cpersons_text;

    }
    // filtri
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
            'date_start' => 'Data inizio',
            'date_end' => 'Data fine'
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
    // Filtro tipo tirocinio
    $form['filter_panel']['internship_type'] = array(
        '#type' => 'checkboxes',
        '#title' => 'Tipo Tirocinio:',
        '#options' => array('1'=>'curricolare','2'=>'extracurricolare'),

        '#name' => 'internship_type',
        '#ajax' => array(
            'event' => 'change',
            'callback' => 'internship_type_ajax_callback',
            'wrapper' => 'type-ajax-wrapper',
        ),
    );
    if(isset($_GET['itype'])) {
        $itype = explode('-',$_GET['itype']);
        foreach($itype AS $value) {
            $form['filter_panel']['internship_type']['#default_value'][$value] = $value;
        }
        $form_state_values['internship_type'] = $form['filter_panel']['internship_type']['#default_value'];
    } else {
        $form_state_values['internship_type'] = array(1=>1, 2=>2);
        $form['filter_panel']['internship_type']['#default_value'] = $form_state_values['internship_type'];
    }
    $internship_type = empty($form_state['input']['internship_type']) ?
        (empty($form_state_values['internship_type']) ? array() : $form_state_values['internship_type']) : $form_state['input']['internship_type'];


    $type_options = array();
    $is_checked = false;
    foreach ($internship_type AS $key => $el) {
        if ($el == $key) {
            $type_options = $type_options + getInternshipTypeOptions1('lib_internship_type', 'getif_data', 'flg_extra_curricular', strval(intval($el)-1));
            $is_checked = true;
        }
    }
    $form['filter_panel']['internship_type_wrapper'] = array('#prefix' => '<div id="type-ajax-wrapper">', '#suffix' => '</div>');
    if ($is_checked) {
        $form['filter_panel']['internship_type_wrapper']['internship_category'] = array(
            '#type' => 'checkboxes',
            '#title' => 'Categoria Tirocinio:',
            '#options' => $type_options,
            '#checkall' => TRUE
        );
        if(isset($_GET['icat'])) {
            $reset_enabled = true;
            $icat = explode('-',$_GET['icat']);

            $form['filter_panel']['internship_type_wrapper']['internship_category']['#default_value'] = array();
            foreach($icat AS $key => $value) {
                $form['filter_panel']['internship_type_wrapper']['internship_category']['#default_value'][$value] = $value;
            }
        } else {
            foreach ($type_options AS $key => $value) {
                $form_state_values['internship_category'][$key] = $key;
            }

            if (!empty($form_state_values['internship_category']))
                $form['filter_panel']['internship_type_wrapper']['internship_category']['#value'] = $form_state_values['internship_category'];
            else
                unset($form['filter_panel']['internship_type_wrapper']['internship_category']['#checkall']);
        }
    }
    // Salva
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
    // Reset
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
        '#type' => 'item',
        '#title' => 'Elenco Tirocini',
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
        t('Convenzione (n. prot.)'),
        t('Ente Promotore'),
        t('Segreteria Ente Promotore'),
        t('Corso frequentato'),
        t('Cognome'),
        t('Nome'),
        t('Titolo di studio'),
        t('Dati tirocinante'),
        t('Struttura di attivazione'),
        t('Tutor Soggetto Ospitante'),
        t('Tutor Soggetto Promotore'),
        t('Responsabile'),
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
        '#prefix' => '<p><span class="glyphicon glyphicon-info-sign"></span>&nbsp;Elenco di tutti tirocini.</p>'
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
                        title: "elenco_tirocini_'.date("d-m-Y").'",
                        exportOptions: {
                            columns: \':visible\'
                        }
                    } ),
                    $.extend( true, {}, fixNewLine, {
                        extend: \'excelHtml5\',
                        title: "elenco_tirocini_'.date("d-m-Y").'",
                        exportOptions: {
                            columns: \':visible\'
                        }
                    } ),
                ],
                pageLength: 10,
                "scrollX": false,
                orderCellsTop: true,
                fixedHeader: true,
                //responsive: true,
                '.$params['columnDefs'].'
                    
                "order": [[ 0, "desc" ]],
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
function elenco_tirocini_form_validate($form, &$form_state) {
    //empty
}

/**
 * @param $form
 * @param $form_state
 */
function elenco_tirocini_form_submit($form, &$form_state)
{
    if (!empty($form_state['clicked_button']['#attributes']['reset'])) {
        $query = array();
        if (!empty($form_state['values']['scolumn'])) {
            $query['hide'] = join($form_state['values']['scolumn'],'-');
        }
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
        if (!empty($form_state['input']['internship_type'])) {
            $query['itype'] = array();
            foreach($form_state['input']['internship_type'] AS $key => $value) {
                if ($value == $key)
                    $query['itype'][] = $key;

            }
            $query['itype'] = join($query['itype'],'-');
            if(!empty($form_state['input']['internship_category'])) {
                $query['icat'] = array();
                foreach($form_state['input']['internship_category'] AS $key => $value) {
                    if ($value != 0 && $value == $key)
                        $query['icat'][] = $key;

                }
                if (!empty($query['icat']))
                    $query['icat'] = join($query['icat'],'-');
            }
        }
        if (!empty($form_state['values']['scolumn'])) {
            $query['hide'] = join($form_state['values']['scolumn'],'-');
        }
    }
    drupal_goto(current_path(), array('query' => $query));
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
function internship_type_ajax_callback($form, $form_state) {
    return $form['filter_panel']['internship_type_wrapper'];
}


/**
 * Restituisce l'array con i Tipi di tirocinio con chiave = id
 * @param $lib
 * @param null $schema
 * @param null $field_name
 * @param null $field_value
 * @param null $exclude_id
 * @return array
 */
function getInternshipTypeOptions1($lib, $schema = null, $field_name = null, $field_value = null, $exclude_id = null){
    $key = getPrimaryKeyTable($lib, $schema);
    //cambio schema
    db_set_active($schema);
    $query = "SELECT `id_".substr($lib,4)."` AS `id`,`description`, `flg_extra_curricular` FROM `{" . $lib . "}` WHERE `active`=1";
    if ($field_name != null && $field_value != null) {
        $query .= " AND ".$field_name." = '".$field_value."'";
    }
    if($exclude_id != null) {
        $query .= " AND $key != $exclude_id";
    }
    //trovo i record della tabella
    $lib_elements = db_query($query);
    //ritorno nello schema di default
    db_set_active();
    //costruisco l'array da ritornare
    $array_elements = array();
    foreach ($lib_elements as $lib_element)
    {
        $array_elements[$lib_element->id] =  $lib_element->description;
    }
    //ritorno;
    return $array_elements;
}
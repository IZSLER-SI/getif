<?php

/**
 * Form report_ore_tutor
 * @param $variables
 * @return mixed
 */

function theme_report_ore_tutor_form($variables){
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
                            title: "report_ore_tutor_'.date("d-m-Y").'"
                        } ),
                        $.extend( true, {}, fixNewLine, {
                            extend: \'excelHtml5\',
                            title: "report_ore_tutor_'.date("d-m-Y").'"
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
        '{$filter}'     => drupal_render($form['filter_panel']),
        '{$view}'       => drupal_render($form['view_panel']),
    );

    $output = "";
    $output .= '
        <div class="row">
            <div class="col-md-12 form-container">
                ' . $form['fs_table_panel']['table']['#prefix'] . '
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
function report_ore_tutor_form($form, &$form_state) {
    $reset_enabled = false;
    $is_closed = $form_state['build_info']['args'][0];
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
    $query->innerJoin('lib_internship_type', 't33', 't1.id_internship_type = t33.id_internship_type');
    $query->innerJoin('internship_host_tutor', 't3', 't1.id_internship = t3.id_internship');
    $query->innerJoin('internship_attendance_sheet', 't4', 't1.id_internship = t4.id_internship');
    $query->innerJoin('person_lperson_prole', 't5', 't3.id_person_lperson_prole = t5.id_person_lperson_prole');
    $query->innerJoin('person_lperson', 't6', 't5.id_person_lperson = t6.id_person_lperson');
    $query->innerJoin('person', 't7', 't7.id_person = t6.id_person');
    // filtro stato
    if (isset($_GET['state'])) {
        $reset_enabled = true;
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
    // filtro tipo di tirocinio
    if (isset($_GET['itype'])) {
        $reset_enabled = true;
        $itype = explode('-',$_GET['itype']);
        $or = db_or();
        foreach($itype AS $value) {
            $or->condition('t33.flg_extra_curricular', strval(intval($value)-1));
        }
        $query->condition($or);
        if (isset($_GET['icat'])) {
            $icat = explode('-',$_GET['icat']);
            $or = db_or();
            foreach ($icat AS $value) {
                $or->condition('t33.id_internship_type', $value);
            }
            $query->condition($or);
        }
    }
    // filtro data
    $date_type = isset($_GET['date_type'])?$_GET['date_type']:'';
    if (isset($_GET['from']) && isset($_GET['to'])) {
        $reset_enabled = true;
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
    $query
        ->fields('t1', array('id_internship'))
        ->condition("t1.flg_voluntary", 0, '=') // tirocinio
        ->condition("t1.active", 1, '=')
        ->condition("t2.active",1)
        ->condition("t3.active", 1)
        ->condition("t4.active", 1)
        ->condition("t5.active", 1)
        ->condition("t6.active", 1)
        ->condition("t7.active", 1);
    // filtro tutor
    if (!empty($_GET['id_host_tutor'])) {
        $query->condition('t7.id_person',$_GET['id_host_tutor']);
        $host_tutor = getRecordById('person','getif_data', $_GET['id_host_tutor']);
        $form['filter_panel']['host_tutor']['#default_value'] = $host_tutor->tax_code.' - '.$host_tutor->firstname.' '.$host_tutor->lastname;
        $form['filter_panel']['host_tutor_id']['#value'] = $host_tutor->id_person;
        $reset_enabled = true;
    }
    // filtro registro chiuso
    if ($is_closed) {
        $query->condition('t4.is_closed',$is_closed);
        $reset_enabled = true;
    }
    // filtro stato
    $query ->addExpression('GROUP_CONCAT(t3.id_person_lperson_prole SEPARATOR \'|\')', 'id_person_lperson_proles');
    $query ->addExpression('GROUP_CONCAT(t7.id_person SEPARATOR \'|\')', 'id_persons');
    $query ->addExpression('GROUP_CONCAT(CONCAT(t7.firstname,\' \',t7.lastname) SEPARATOR \'|\')', 'name_persons');
    $query->condition('t2.state', array(0, 5, 6, 7), 'IN'); // tirocini 5 - attivi, 6 - prorogati, 7- conclusi, 0 - interrotti
    $query->groupBy('t1.id_internship');
    $query->orderBy('t1.id_internship');
    $results = $query->execute()->fetchAll();
    db_set_active();
    // costruisco colonne/righe
    $header = array();
    $rows = array();
    foreach($results AS $result) {
        $id_persons = explode('|', $result->id_persons);
        $name_persons = explode('|', $result->name_persons);
        foreach ($id_persons AS $key => $id_person) {
            $header[$id_person] = $name_persons[$key];
        }
        $rows[$result->id_internship][0] = '<b>Tirocinio' . $result->id_internship . '</b>';
    }
    // costruisco dati
    foreach($results AS $result) { // per ogni tirocinio

        $internship = getInternshipById('getif_data', $result->id_internship);
        $rows[$result->id_internship][0] = '<b>' . $internship->person->firstname . ' ' . $internship->person->lastname . '<br/>(ID ' . $internship->id_internship . ')</b>';
        // registro e date
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
            $date_end_effective = $internship->date_end;
        } else {
            $date_end_effective = $internship->internship_state->date_end;
        }
        $dates = dateRange($date_start_effective, $date_end_effective);
        // ---
        $id_persons = explode('|', $result->id_persons);
        // inizializza tabella
        foreach ($header AS $id_person => $value) {
            $rows[$result->id_internship][$id_person] = '-';
        }
        // riempi tabella
        foreach ($id_persons AS $id_person) {
            $header[$id_person] =
            $numero_ore = 0;
            foreach ($internship->host->tutor as $internship_host_tutor) {
                if ($internship_host_tutor->id_person == $id_person) {
                    $header[$id_person] = $internship_host_tutor->firstname . ' ' . $internship_host_tutor->lastname . '<br/>' . $internship_host_tutor->tax_code;
                    foreach ($dates as $key => $date) { // per ogni giorno
                        $form_state['time_keys_' . $key] = !empty($form_state_time_keys[$date]) ? $form_state_time_keys[$date] : array(0 => 0);
                        $time_keys = $form_state['time_keys_' . $key];
                        foreach ($time_keys as $time_key) { // per ogni orario di entrata - uscita
                            if (!empty($time_key['ora_da']) && !empty($time_key['ora_a'])) {
                                $id_lperson = $time_key['where']; // id della Struttura di presenza
                                if ($internship_host_tutor->id_lperson == $id_lperson) { // prendo solo le ore presso la struttura di frequenza in cui opera il tutor
                                    $t11 = $time_key['ora_da'];
                                    $t12 = $time_key['ora_a'];
                                    $diff = round((time_to_decimal($t12) - time_to_decimal($t11)) / 60, 2);
                                    $numero_ore += $diff;
                                }
                            }
                        }
                    }
                }
            }

            $rows[$result->id_internship][$id_person] = $numero_ore . ' ' . t('ore');
        }

    }
    array_unshift($header,'');

    // Filtri
    $form['filter_panel']['host_tutor_id'] = array(
        '#type'  => 'hidden',
        '#attributes'=>array(
            'id'   => 'edit-host-tutor_id'
        ),
    );
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
    // Controlli tipo tirocinio
    if(isset($_GET['itype'])) {
        $reset_enabled = true;
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
            '#checkall' => TRUE,
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
    // Salva
    $form['filter_panel']['save'] = array(
        '#type' => 'submit',
        '#value' => 'Filtra',
        '#weight' => 99,
        '#prefix' => '<hr/>'
    );
    // Reset
    $form['filter_panel']['reset'] = array(
        '#type' => 'submit',
        '#value' => 'Reset',
        '#access' => false,
        '#attributes' => array(
            'reset' => true
        ),
        '#prefix' => '<div class="container-inline">',
        '#suffix' => '</div>',
        '#weight' => 100
    );
    $form['fs_table_panel'] = array(
        '#type' => 'item',
        '#title' => t('Report delle ore complessive di attività di ogni Tirocinio associato ad un tutor'),
        '#title_display' => 'invisible',
        '#access' => true
    );
    // Tabella
    $form['fs_table_panel']['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#empty' => t('Table has no row!'),
        '#attributes' => array(
            'id' => 'tabella'
        )
    );
    $form['fs_table_panel']['table']['#header'] = $header;
    $form['fs_table_panel']['table']['#rows'] = !empty($rows)?$rows:array();
    if ($reset_enabled) {
        $form['filter_panel']['reset']['#access'] = true;
    }
    if ($is_closed) {
        $form['fs_table_panel']['#title'] = t('Report per attestazione delle ore di attività di un tutor.');
        $form['fs_table_panel']['table']['#prefix'] = '<p><span class="glyphicon glyphicon-info-sign"></span>&nbsp;Report per attestazione delle ore di attività di un tutor.</p>';
    } else {
        $form['fs_table_panel']['#title'] = t('Report delle ore complessive di attività di ogni Tirocinio associato ad un tutor');
        $form['fs_table_panel']['table']['#prefix'] = '<p><span class="glyphicon glyphicon-info-sign"></span>&nbsp;Report delle ore complessive di attività di ogni Tirocinio associato ad un tutor.</p>';
    }
    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function report_ore_tutor_form_validate($form, &$form_state) {
    //empty
}

/**
 * @param $form
 * @param $form_state
 */
function report_ore_tutor_form_submit($form, &$form_state)
{
    if (!empty($form_state['clicked_button']['#attributes']['reset'])) {
        $query = array();
        drupal_goto(current_path().'/', $query);
    } else {
        $query = array();
        if (!empty($form_state['input']['host_tutor_id'])) {
            $query['id_host_tutor'] = $form_state['input']['host_tutor_id'];
        }
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

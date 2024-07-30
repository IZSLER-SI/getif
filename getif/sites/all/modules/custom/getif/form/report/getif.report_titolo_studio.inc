<?php

/**
 * Theme report_titolo_studio
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_report_titolo_studio_form($variables){
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
                            title: "report_titolo_studio_'.date("d-m-Y").'"
                        } ),
                        $.extend( true, {}, fixNewLine, {
                            extend: \'excelHtml5\',
                            title: "report_titolo_studio_'.date("d-m-Y").'"
                        } ),
                    ],
                    pageLength: 10,
                    "scrollX": false,
                    orderCellsTop: true,
                    fixedHeader: true,
                    //responsive: true,
                  
                        
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
 * Form report_titolo_studio
 * @param $form
 * @param $form_state
 * @return mixed
 */
function report_titolo_studio_form($form, &$form_state) {
    $is_voluntary = $form_state['build_info']['args'][0];
    $where = 't1.flg_voluntary = 0 AND ';
    //filtro tirocinio/frequenza
    if ($is_voluntary) {
        $where = 't1.flg_voluntary = '.$is_voluntary.' AND ';
    }
    // filtro stato
    if (isset($_GET['state'])) {
        if ($_GET['state'] == 'all') {
            $where .= 't3.state IN ('.join(',',array(0,1,2,3,4,5,6,7)).') AND ';
            $state_default_value = 'all';
        } elseif ($_GET['state'] == 'pending') {
            $where .= 't3.state IN ('.join(',',array(1,2,3,4)).') AND ';
            $state_default_value = 'pending';
        } elseif ($_GET['state'] == 'active') {
            $where .= 't3.state IN ('.join(',',array(5,6)).') AND ';
            $state_default_value = 'active';
        } else {
            $where .= 't3.state = '.$_GET['state'].' AND ';
            $state_default_value = $_GET['state'];
        }
    } else  {
        $where .= 't3.state IN ('.join(',',array(0,1,2,3,4,5,6,7)).') AND ';
        $state_default_value = 'all';
    }
    // filtro data
    $date_type = isset($_GET['date_type'])?$_GET['date_type']:'';
    // filtro tipo di tirocinio
    if (isset($_GET['itype'])) {
        $itype = explode('-',$_GET['itype']);

        $or = array();
        foreach($itype AS $value) {
            $or[] = 't5.flg_extra_curricular = '.strval(intval($value)-1);
        }
        if (!empty($or))
            $where .= '('.join(' OR ',$or).') AND ';
        $or = array();
        if (isset($_GET['icat'])) {
            $icat = explode('-',$_GET['icat']);
            foreach ($icat AS $value) {
                $or[] = 't5.id_internship_type =\''.$value.'\'';
            }
            if (!empty($or))
                $where .= '('.join(' OR ',$or).') AND ';
        }
    }
    if (isset($_GET['from']) && isset($_GET['to'])) {

        if ($date_type == 'date_application') {
            $where .= 't1.date_application >= \''.date('Y-m-d', strtotime($_GET['from'])).'\' AND ';
            $where .= 't1.date_application <= \''.date('Y-m-d', strtotime($_GET['to'])).'\' AND ';
        } elseif ($date_type == 'date_start') {
            $where .= 't3.date_start >= \''.date('Y-m-d', strtotime($_GET['from'])).'\' AND ';
            $where .= 't3.date_start <= \''.date('Y-m-d', strtotime($_GET['to'])).'\' AND ';
        } elseif ($date_type == 'date_end') {
            $where .= 't3.date_end >= \''.date('Y-m-d', strtotime($_GET['from'])).'\' AND ';
            $where .= 't3.date_end <= \''.date('Y-m-d', strtotime($_GET['to'])).'\' AND ';
        }
    }
    db_set_active('getif_data');
    $query = db_query(
        'SELECT t22.name as qualification,t4.name AS lperson_name
                FROM `internship` AS t1 
                INNER JOIN `internship_person` AS t2 ON t1.id_internship = t2.id_internship
                INNER JOIN `lib_qualification` AS t22 ON t22.id_qualification = t2.id_qualification 
                INNER JOIN `internship_state` AS t3 ON t3.id_internship = t2.id_internship 
                LEFT JOIN `lib_internship_type` AS t5 ON t1.id_internship_type = t5.id_internship_type
                INNER JOIN (SELECT st1.id_internship, st1.id_lperson, st2.name, st1.active 
                FROM internship_lperson AS st1 INNER JOIN lperson AS st2 ON st1.id_lperson = st2.id_lperson) AS t4 ON t1.id_internship = t4.id_internship 
                WHERE '.$where.' t1.active = 1 AND t2.active = 1 AND t3.active = 1 AND t4.active = 1;'
    );
    $results = $query->fetchAll();
    db_set_active();
    $rows = array();
    $header = array();
    $data = array();
    // costruisci header
    foreach($results as $key => $item) {
        if (!in_array($item->lperson_name,$header)) {
            $header[$item->lperson_name] = $item->lperson_name;
            $data[$item->lperson_name] = '0';
        }
    }

    // costruisci righe
    $i = 1;
    $qualification_array = array();
    foreach($results as $key => $item) {
        $qualification = $item->qualification;
        if (!in_array($qualification, $qualification_array)) {
            $i++;
            $qualification_array[$i] = $qualification;
            $rows[$i][0] = '<b>'.$qualification.'</b>';
            $rows[$i] = array_merge($rows[$i], $data);
            $rows[$i][$item->lperson_name] = 1;
        } else {
            $rows[array_search($qualification,$qualification_array)][$item->lperson_name] += 1;
        }

    }
    array_unshift($header,'');

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
    // Filtro stato dei tirocini
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
            'range' => 'filter_date_start'
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
            'range' => 'filter_date_end'
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
    $reset_enabled = false;
    // Filtro tipo tirocinio
    if (!$is_voluntary) {
        $form['filter_panel']['internship_type'] = array(
            '#type' => 'checkboxes',
            '#title' => 'Tipo Tirocinio:',
            '#options' => array('1' => 'curricolare', '2' => 'extracurricolare'),
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
            $reset_enabled = true;
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
                $type_options = $type_options + _getInternshipTypeOptions('lib_internship_type', 'getif_data', 'flg_extra_curricular', strval(intval($el)-1));
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
                $form['filter_panel']['internship_type_wrapper']['internship_category']['#value'] = array();
                foreach($icat AS $key => $value) {
                    $form['filter_panel']['internship_type_wrapper']['internship_category']['#value'][$value] = $value;
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
    }
    if ($is_voluntary) {
        $form['filter_panel']['voluntary_filter']['#default_value'] = $is_voluntary+1;
        $voluntary_text = 'frequenze volontarie';
    } else {
        $voluntary_text = 'tirocini';
    }
    if (isset($_GET['date_type'])) {
        $form['filter_panel']['date_type']['#default_value'] = $_GET['date_type'];
        $date_format = isset($_GET['date_format'])?$_GET['date_format']:'';
        if ($date_format == 'year') {
            $form['filter_panel']['date_format']['#default_value'] = $date_format;
            $form['filter_panel']['date_year']['#default_value'] = date('Y',strtotime($_GET['from']));
        } elseif ($date_format == 'range') {
            $form['filter_panel']['date_format']['#default_value'] = $date_format;
            $form['filter_panel']['date_from']['#default_value'] = date('d-m-Y',strtotime($_GET['from']));
            $form['filter_panel']['date_to']['#default_value'] = date('d-m-Y',strtotime($_GET['to']));
        }
        $reset_enabled = true;
    }
    $form['filter_panel']['save'] = array(
        '#type' => 'submit',
        '#value' => 'Filtra',
    );
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
    // Tabella
    $form['fs_table_panel'] = array(
        '#type' => 'item',
        '#title' => $is_voluntary == 0?'Report numero tirocini per titolo di studio/struttura di attivazione':'Report numero frequenze volontarie per titolo di studio/struttura di attivazione',
        '#title_display' => 'invisible',
        '#access' =>true
    );
    $form['fs_table_panel']['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('Table has no row!'),
        '#attributes' => array(
            'id' => 'tabella'
        ),
        '#prefix' => '<p><span class="glyphicon glyphicon-info-sign"></span>&nbsp;Report numero di '.$voluntary_text.' per titolo di studio in frequenza/struttura di attivazione.</p>'
    );
    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function report_titolo_studio_form_validate($form, &$form_state) {
    //empty
}

/**
 * @param $form
 * @param $form_state
 */
function report_titolo_studio_form_submit($form, &$form_state)
{
    if (!empty($form_state['clicked_button']['#attributes']['reset'])) {
        $query = array();
        drupal_goto(current_path(), array('query' => $query));
    } else {
        $query = array();
        if (in_array($form_state['values']['state'],array(0,5,6,7))) {
            $query['state'] = $form_state['values']['state'];
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
        if (!empty($form_state['values']['internship_type'])) {
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
function _getInternshipTypeOptions($lib, $schema = null, $field_name = null, $field_value = null, $exclude_id = null){
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
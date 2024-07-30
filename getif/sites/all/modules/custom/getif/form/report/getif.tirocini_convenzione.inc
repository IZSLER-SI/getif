<?php

/**
 * theme tirocini_convenzione
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_tirocini_convenzione_form($variables){
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    drupal_add_js('
            jQuery(function($) {
                var agreeement_select = false;
                $("#edit-agreement").bind(\'autocompleteSelect\', function() {
            
                    var values = $(this).val().split(\'|\');
                    $(this).val(values[0]);
                    if (values[1]) {
                        $("#edit-agreement_id").val(values[1]);
                        agreeement_select = true;
                    }
            
                }).blur(function() {
                    if(agreeement_select == false) {
                        $("#edit-agreement").val("");
                    }
                    agreeement_select = false;
                });
            });
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
                            var output = strip_html_tags(data.replace( /<br\s*\/?>/gi,"\r\n"));
                            console.log(output);
                            if (output == false)
                                return "";
                            return output;
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
 * form tirocini_convenzione
 * @param $form
 * @param $form_state
 * @return mixed
 */
function tirocini_convenzione_form($form, &$form_state) {
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
    db_set_active('getif_data');
    $query = db_select('internship', 't1');
    $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
    $query->innerJoin('lib_internship_type', 't3', 't1.id_internship_type = t3.id_internship_type');
    $query->innerJoin('internship_agreement', 't4', 't1.id_internship = t4.id_internship');
    $query
        ->fields('t1', array('id_internship', 'date_start', 'date_end'))
        ->fields('t2', array('state'))
        ->condition("t1.flg_voluntary",0,'=') // è una frequenza volontaria
        ->condition("t1.active",1,'=')
        ->condition("t2.active",1,'=')
        ->condition("t4.active",1,'=');
    // filtro convenzione
    if (isset($_GET['agreement'])) {
        $query->condition('t4.id_agreement',$_GET['agreement']);
    } else {
        $query->condition('t4.id_agreement','0');
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
    $query->condition('t2.state', array(0,5,6,7), 'IN'); // tirocini 5 - attivi, 6 - prorogati, 7- conclusi, 0 - interrotti
    $results = $query
        ->execute();
    db_set_active();

    $rows = array();
    foreach($results as $key => $item) {
        $internship = getInternshipById('getif_data', $item->id_internship);
        $internship_host_tutors_text = '';
        foreach($internship->host->tutor AS $host_tutor) {
            $host_tutor_name = _strformat($host_tutor->title).' '.
                _strformat($host_tutor->firstname).' '._strformat($host_tutor->lastname);
            if ($host_tutor->flg_primary) {
                $internship_host_tutors_text .= '<b>' . $host_tutor_name . '</b>'.'<br>';
                $host_primary_tutor = new \stdClass;
                $host_primary_tutor->firstname = $host_tutor->firstname;
                $host_primary_tutor->lastname = $host_tutor->lastname;
                $host_primary_tutor->email_address = $host_tutor->email_address;
                $host_primary_tutor->phone = $host_tutor->phone;
            } else {
                $internship_host_tutors_text .= $host_tutor_name . '<br>';
            }
        }
        $internship_host_cperson_text = '';
        foreach($internship->project_contacts AS $cperson) {
            $cperson_name = _strformat($cperson->title).' '.
                _strformat($cperson->firstname).' '._strformat($cperson->lastname).'<br>';
            if ($cperson->flg_primary) {
                $internship_host_cperson_text .= '<b>' . $cperson_name . '</b>'.'<br>';
                $cperson_primary_tutor = new \stdClass;
                $cperson_primary_tutor->firstname = $cperson->firstname;
                $cperson_primary_tutor->lastname = $cperson->lastname;
                $cperson_primary_tutor->email_address = $cperson->email_address;
                $cperson_primary_tutor->phone = $cperson->phone;
            } else {
                $internship_host_cperson_text .= $cperson_name . '<br>';
            }
        }
        // tirocinante
        $rows[$key][] = $internship->person->firstname;
        $rows[$key][] = $internship->person->lastname;
        $rows[$key][] = $internship->person->tax_code;
        $rows[$key][] = !empty($internship->person->phone)?$internship->person->phone:'';
        $rows[$key][] = $internship->person->email_address;
        $rows[$key][] = $internship->person->residence_address;
        // Date
        $rows[$key][] = date('d-m-Y',strtotime($internship->date_start));
        $rows[$key][] = date('d-m-Y',strtotime($internship->internship_state->date_start));
        // Tutor Soggetto Ospitante
        $rows[$key][] = $host_primary_tutor->firstname;
        $rows[$key][] = $host_primary_tutor->lastname;
        $rows[$key][] = $host_primary_tutor->email_address;
        $rows[$key][] = !empty($host_primary_tutor->phone)?$host_primary_tutor->phone:'';
        // Tutor Soggetto Promotore
        $rows[$key][] = $internship->promoter->tutor->firstname;
        $rows[$key][] = $internship->promoter->tutor->lastname;
        $rows[$key][] = $internship->promoter->tutor->email_address;
        $rows[$key][] = !empty($internship->promoter->tutor->phone)?$internship->promoter->tutor->phone:'';
        // Responsabile U.O. di riferimento
        $rows[$key][] = $cperson_primary_tutor->firstname;
        $rows[$key][] = $cperson_primary_tutor->lastname;
        $rows[$key][] = $cperson_primary_tutor->email_address;
        $rows[$key][] = $cperson_primary_tutor->phone;
        // Stato del tirocinio
        $rows[$key][] = getInternshipStateText($internship);


    }
    // filtri
    $form['filter_panel']['agreement'] = array(
        '#type' => 'textfield',
        '#title' => t('Convenzione'),
        '#autocomplete_path' => 'agreement_autocomplete_callback',
        '#required' => true,
        '#attributes' => array(
            'id' => 'edit-agreement'
        ),
        '#weight' => 10
    );
    $form['filter_panel']['agreement_id'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'id' => 'edit-agreement_id',
        ),
        '#weight' => 11
    );
    $agreement_text = '';
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
        '#states' => array(
            'invisible' => array(
                ':input[name="agreement"]' => array('filled' => FALSE),
            ),
        ),
        '#weight' => 20
    );
    if(isset($_GET['itype'])) {
        $itype = explode('-',$_GET['itype']);
        foreach($itype AS $value) {
            $form['filter_panel']['internship_type']['#value'][$value] = $value;
        }
        $form_state_values['internship_type'] = $form['filter_panel']['internship_type']['#value'];
    } else {
        $form_state_values['internship_type'] = array(1=>1, 2=>2);
        $form['filter_panel']['internship_type']['#value'] = $form_state_values['internship_type'];
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
    $form['filter_panel']['internship_type_wrapper'] = array('#weight' => 21,'#prefix' => '<div id="type-ajax-wrapper">', '#suffix' => '</div>');
    if ($is_checked) {

        $form['filter_panel']['internship_type_wrapper']['internship_category'] = array(
            '#type' => 'checkboxes',
            '#title' => 'Categoria Tirocinio:',
            '#options' => $type_options,
            '#checkall' => TRUE,
            '#states' => array(
                'invisible' => array(
                    ':input[name="agreement"]' => array('value' => ''),
                ),
            ),
            '#weight' => 21
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
    if (isset($_GET['agreement'])) {
        // Filtro stato dei tirocini
        $form['filter_panel']['state'] = array(
            '#type' => 'select',
            '#title' => 'Stato:',
            '#options' => GETIF_REPORT_STATES,
            '#default_value' => $state_default_value,
            '#weight' => 12
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
            ),
            '#weight' => 13
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
            '#weight' => 14
        );
        $form['filter_panel']['date_year'] = array(
            '#type' => 'date_select',
            '#title' => t('Anno'),
            '#date_timezone' => date_default_timezone(),
            '#date_format' => 'Y',
            '#date_year_range' => '2016:now',
            '#default_value' => date('Y'),
            '#date_label_position' => 'within',
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
            '#weight' => 15
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
            ),
            '#weight' => 16
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
            ),
            '#weight' => 17
        );

        $agreement = getRecordById('agreement','getif_data',$_GET['agreement']);
        $agreement_text .= 'Note: convenzione collettiva con N. IZSLER: '.$agreement->number_code.' da '.date('d-m-Y',strtotime($agreement->date_start)).' a '.date('d-m-Y',strtotime($agreement->date_end));
        $form['filter_panel']['agreement']['#default_value'] = $agreement->number_code;
        $form['filter_panel']['agreement_id']['#value'] = $agreement->id_agreement;
        $form['filter_panel']['date_year']['#date_year_range'] = date('d-m-Y',strtotime($agreement->date_start)).':'.date('d-m-Y',strtotime($agreement->date_end));
        $form['filter_panel']['date_from']['#attributes']['minDate'] = date('d-m-Y',strtotime($agreement->date_start));
        $form['filter_panel']['date_from']['#attributes']['maxDate'] = date('d-m-Y',strtotime($agreement->date_end));
        $form['filter_panel']['date_to']['#attributes']['maxDate'] = date('d-m-Y',strtotime($agreement->date_end));
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
        }
        $reset_enabled = true;
    }
    $form['filter_panel']['save'] = array(
        '#type' => 'submit',
        '#value' => 'Filtra',
        '#weight' => 99
    );
    if ($reset_enabled) {
        $form['filter_panel']['reset'] = array(
            '#type' => 'submit',
            '#value' => 'Reset',
            '#limit_validation_errors' => array(),
            '#attributes' => array(
                'reset' => true
            ),
            '#prefix' => '<div class="container-inline">',
            '#suffix' => '</div>',
            '#weight' => 100
        );

    }
    $form['fs_table_panel'] = array(
        '#type' => 'item',
        '#title' => 'Tirocini attivati per '.$agreement_text,
        '#title_display' => 'invisible',
        '#access' =>true
    );

    $date_label = array(
        1 => 'Data richiesta',
        2 => 'Data avvio prevista',
        3 => 'Data attivazione',
        4 => 'Data prevista conclusione/proroga',
        5 => 'Data conclusione effettiva'
    );

    // Tabella
    $header = array(
        t('Nome'),
        t('Cognome'),
        t('Codice Fiscale'),
        t('Telefono'),
        t('Email'),
        t('Residenza'),
        $date_label[1],
        $date_label[3],
        t('Nome Tutor S.O.'),
        t('Cognome Tutor S.O.'),
        t('Email Tutor S.O.'),
        t('Telefono Tutor S.O.'),
        t('Nome Tutor S.P.'),
        t('Cognome Tutor S.P.'),
        t('Email Tutor S.P.'),
        t('Telefono Tutor S.P.'),
        t('Nome Responsabile U.O.'),
        t('Cognome Responsabile U.O.'),
        t('Email Responsabile U.O.'),
        t('Telefono Responsabile U.O.'),
        t('Stato')
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
    } else {
        $form['view_panel']['scolumn']['#default_value'] = explode('-',GETIF_REPORT_TIROCINI_CONVENZIONE_COLONNE);
    }
    $form['fs_table_panel']['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => empty($rows)?array(array()):$rows,
        '#empty' => t('Table has no row!'),
        '#attributes' => array(
            'id' => 'tabella'
        ),
        '#prefix' => '<p><span class="glyphicon glyphicon-info-sign"></span>&nbsp;Report di tutti i tirocini afferenti ad una convenzione: selezionare una convenzione per visualizzare i dati.</p>'
    );

    if (!empty($agreement_text)) {
        $form['table_panel']['table']['#footer'] = array(
            array(
                array(
                    'colspan' => count($header),
                    'data' => $agreement_text,
                    'style' => ['background-color: grey;', 'text-align: left;', 'color: white;']
                )
            )
        );
    }

    $params['columnDefs'] = 'columnDefs: [';
    foreach ($date_label AS $date) {
        if (!empty(array_search($date,$header))) {
            $params['columnDefs'] .= '{ type: "date-eu", targets: '.array_search($date,array_values($header)).' },';
        }
    }
    if (!empty($agreement->id_agreement)) {
        $params['columnDefs'] .= '],';
        $export_filename = 'tirocini_convenzione_' . $agreement->id_agreement . '_' . date("d-m-Y");
        $script = '
            jQuery(function($) {
                var table = $("#tabella").DataTable( {
                    dom: "<\"toolbar_top\">B<\"toolbar_ex\">lfrtip",
                    buttons:[
                        $.extend( true, {}, fixNewLine, {
                            extend: \'csvHtml5\',
                            title: "' . $export_filename . '",
                            exportOptions: {
                                columns: \':visible\'
                            }
                        } ),
                        $.extend( true, {}, fixNewLine, {
                            extend: \'excelHtml5\',
                            title: "' . $export_filename . '",
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
                    ' . $params['columnDefs'] . '
                        
                    "order": [[ 0, "desc" ]],
                    lengthMenu: [[10, 25, 50, 100, -1], [10, 25, 50, 100, "Tutti"]],
                    language: {
                        "emptyTable":     "",
                        "info":           "Visualizzati da _START_ a _END_ su _TOTAL_ elementi totali",
                        "infoEmpty":      "",
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
    }

    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function tirocini_convenzione_form_validate($form, &$form_state) {
    //empty
}

/**
 * @param $form
 * @param $form_state
 */
function tirocini_convenzione_form_submit($form, &$form_state)
{
    if (!empty($form_state['clicked_button']['#attributes']['reset'])) {
        $query = array();
        if (!empty($form_state['values']['scolumn'])) {
            $query['hide'] = join($form_state['values']['scolumn'],'-');
        }
        drupal_goto(current_path(), array('query' => $query));
    } else {
        $query = array();
        if (!empty($form_state['values']['agreement']) && !empty($form_state['input']['agreement_id'])) {
            $query['agreement'] = $form_state['input']['agreement_id'];
        }
        if (!empty($form_state['values']['state']) && in_array($form_state['values']['state'],array(0,5,6,7))) {
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
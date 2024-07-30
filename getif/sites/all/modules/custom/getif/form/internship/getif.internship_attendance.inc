<?php


/**
 * Theme registro tirocinio
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_internship_attendance_form($variables){
    $module_path = drupal_get_path('module', 'getif');
    $full_path = $module_path .'/js/js-timeentry/jquery.timeentry.css';
    drupal_add_css($full_path);
    $full_path = $module_path .'/js/js-timeentry/jquery.plugin.js';
    drupal_add_js($full_path);
    $full_path = $module_path .'/js/js-timeentry/jquery.timeentry.js';
    drupal_add_js($full_path);
    drupal_add_js('
            jQuery( document ).ready(function( $ ) {
                  $(\'.timeRange\').timeEntry({beforeShow: customRange}); 
 
                    function customRange(input) { 
                        var hh = parseInt(input.value.split(":")[0]);
                        var mm = parseInt(input.value.split(":")[1]);
                        return { defaultTime: (input.id.includes("-ora-a")?
                            (!isNaN(hh)?new Date(0, 0, 0, hh, 0, 0):new Date(0, 0, 0, 18, 0, 0)):(!isNaN(hh)?new Date(0, 0, 0, hh, 0, 0):new Date(0, 0, 0, 8, 0, 0)))
                            , minTime: (input.id.includes("-ora-a") ? 
                            $(\'#\'+input.id.replace("-ora-a","-ora-da")).timeEntry(\'getTime\') : null),  
                            maxTime: (input.id === \'edit-container-2019-05-11-0-ora-da\' ? 
                            $(\'#\'+input.id.replace("-ora-da","-ora-a")).timeEntry(\'getTime\') : null)
                            }; 
                   }
                   
                   var time = document.getElementsByClassName(\'timeRange\'); //Get all elements with class "time"
                    for (var i = 0; i < time.length; i++) { //Loop trough elements
                        time[i].addEventListener(\'keyup\', function (e) {; //Add event listener to every element
                            var reg = /[0-9]/;
                            if (this.value.length == 2 && reg.test(this.value)) this.value = this.value + ":"; //Add colon if string length > 2 and string is a number 
                            if (this.value.length > 5) this.value = this.value.substr(0, this.value.length - 1); //Delete the last digit if string length > 5
                        });
                    };
            });
            jQuery.timeEntry.setDefaults({show24Hours: true,showSeconds: false});
            '
        ,array('type'=>'inline','scope' => 'footer')
    );
    $form = $variables['form'];
    $options['page_title'] = drupal_render($form['titolo']);
    $output = '';
    $output .= '<div class="row">';
    $output .= '<div class="col-md-12 form-container">';
    $output .= '<fieldset class="panel panel-default form-wrapper" id="edit-fs-'.str_replace('_','-',$form['#form_id']).'">';
    $output .= '<legend class="panel-heading bootstro" id="edit-'.str_replace('_','-',$form['#form_id']).'-heading" data-bootstro-title="Navigazione '.$options['page_title'].'" data-bootstro-content="Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Tirocini</li></ul>" data-bootstro-width="600px" data-bootstro-placement="bottom">
                 <div style="float:left">
                 <span class="panel-title fieldset-legend">'.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()).'</span>
                 </div>
                 <div style="float:right">'.drupal_render($form['nav']).'</div>
                </legend>';
    }*/
    $output .= '<div class="panel-body bootstro" id="edit-' . str_replace('_', '-', $form['#form_id']) . '-body" data-bootstro-title="Maschera" data-bootstro-content="La maschera permette di inserire gli orari di entrata-uscita e la struttura frequentata.<br/>E\' possibile inserire più di un orario entrata-uscita nella stessa giornata.<br/>La paginazione delle giornate é organizzata per mesi.<br/>Per salvare le modifiche apportate cliccare sul pulsante &quot;Salva&quot;. Nel caso di tirocinio concluso o interrotto sarà possibile chiudere il registro cliccando sul pulsante &quot;Chiudi Registro&quot;." data-bootstro-width="600px" data-bootstro-placement="bottom">';

    $output .= '<div class="panel-body">';
    $output .= '<nav aria-label="Page navigation">
        <ul class="pagination">' . drupal_render($form['pagination']) . '
        </ul>
    </nav>';
    $output .= '<table id="tabella" class="table table-hover table-striped sticky-enabled tableheader-processed sticky-table">
                <thead>
                    <tr>
                        <th>' . t("Giorno") . '</th>
                         <th>' . t("Entrata/Uscita") . '</th>
                    </tr>
                </thead>
            </tbody>';

    foreach ($form['#dates'] as $key_test => $date) {
        $key = $date;
        if (date("m", strtotime($date)) == arg(3) && date("y", strtotime($date)) == arg(4)) {
            $output .= '<tr>';
            $output .= '<td style="vertical-align:top;padding:32px 10px 10px 10px"><span style="font-weight:bold">' . ucwords(strftime("%A, %d %b %G", strtotime($date))) . '</span></td>';
            $output .= '<td style="padding:10px">' . drupal_render($form['container'][$key]) . '</td>';
            $output .= '</tr>';
        }
    }
    $output .= '</tbody></table>';
    $output .= '</div>';
    $output .= '<hr/>';
    $output .= '<div style="text-align:right">' . drupal_render($form['actions']) . '</div>';
    unset($form['actions']);
    $output .= '</div>';
    $output .= '</fieldset>';
    $output .= drupal_render_children($form);
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';

    return $output;
}


/**
 *
 */
function go_back () {
    getif_goto('internship/list',array(),302,true);
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function internship_attendance_form($form, &$form_state) {

    $id_internship = $form_state["build_info"]["args"]["1"];
    $internship = getInternshipById('getif_data',$id_internship);
    $internship_register_base64 = !empty($internship->attendance_sheet->register)?$internship->attendance_sheet->register:'';
    $is_open = (!empty($internship->attendance_sheet->is_closed))?0:1;
    if (!empty($internship_register_base64)) {
        $internship_register = base64_decode($internship_register_base64);
        $form_state_input_container = json_decode($internship_register,true);
        // Build the initial fields if this is not being rebuilt
        // from ajax request.
        if (!array_key_exists('clicked_button', $form_state)) {
            $form_state_time_keys = processArray($form_state_input_container);
        }
    }
    $date_start_effective = $internship->internship_state->date_start;
    if (empty($internship->internship_state ->date_end)) {
        if ($internship->internship_state->state == 6 && !empty($internship->internship_state->date_extension)) {
            $date_end_effective = $internship->internship_state->date_extension;
        } else {
            $datetime1 = new DateTime($internship->date_start);
            $datetime2 = new DateTime($internship->date_end);
            $interval = $datetime1->diff($datetime2);
            $date_end_effective = $internship->date_end;
        }
    } else {
        $date_end_effective =$internship->internship_state->date_end;
    }


    $months = getArrayMonths($date_start_effective,$date_end_effective);

    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    $form['nav']['goto_list'] = array(
        '#type' => 'button',
        '#value' => t('Tirocini'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_list'),
        '#attributes' => array(
            'list_name' => 'internship'
        )
    );
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Indietro'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back'),
    );
    $form['nav']['help'] = array(
        '#markup' => '<a href="#" class="help-btn" data-toggle="tooltip" data-original-title="Help contenuto pagina">
                                <span class="glyphicon glyphicon-question-sign" style="font-size:20px;">
                            </a>'
    );

    $form['titolo'] = array (
        '#markup' => t('Registro delle presenze di '.$internship->person->firstname.' '.$internship->person->lastname),
    );
    $dates = dateRange($date_start_effective,$date_end_effective);
    $form['#dates'] = $dates;
    $form['container'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
    );

    $lperson_list = array();
    foreach ($internship->lperson AS $lperson) {
        $lperson_list[$lperson->id_lperson] = $lperson->name;
    }

    $mapping_days = array(
        '0' => 'Lun',
        '1' => 'Mar',
        '2' => 'Mer',
        '3' => 'Gio',
        '4' => 'Ven',
        '5' => 'Sab',
        '6' => 'Dom',
    );
    $working_times_text_array = array();
    if (!empty($internship->person->working_time)) {
        $working_times = (json_decode($internship->person->working_time));
        foreach ($working_times as $key_wt => $working_time) {
            if (!empty($working_time[0]) || !empty($working_time[2])) {
                $working_times_text_array[$mapping_days[$key_wt]] = '<br/><div class="alert alert-warning"><table><tr><td valign="top" >Orario dipendente:&nbsp;</td>';
                if (!empty($working_time[0])) {
                    $working_times_text_array[$mapping_days[$key_wt]] .= '<td>dalle ' . $working_time[0] . ' alle ' . $working_time[1] . '<br>';
                }
                if (!empty($working_time[2])) {
                    $working_times_text_array[$mapping_days[$key_wt]] .= 'dalle ' . $working_time[2] . ' alle ' . $working_time[3];
                }
                $working_times_text_array[$mapping_days[$key_wt]] .= '</td></tr></table></div>';
            }

        }
    }


    foreach ($dates as $date) {

        $key = $date;
        if (date("m", strtotime($date)) == $form_state["build_info"]["args"]["2"] && date("y", strtotime($date)) == $form_state["build_info"]["args"]["3"]) {
            $form['container'][$key] = [
                '#type' => 'container',
                '#tree' => TRUE,
                '#prefix' => '<div id="container_'.$key.'">',
                '#suffix' => '</div>',

            ];
            if (!array_key_exists('clicked_button', $form_state)) {
                $form_state['time_keys_'.$key] = !empty($form_state_time_keys[$key])?$form_state_time_keys[$key] : array(0=>0);
            } else {
                $form_state['time_keys_'.$key] = isset($form_state['time_keys_'.$key]) ? $form_state['time_keys_'.$key] : array(0=>0);

            }
            $time_keys =  $form_state['time_keys_'.$key];

            $form['container'][$key]['data']  = array(
                '#type' => 'hidden',
                '#value' => $date
            );
            foreach ($time_keys as $time_key) {

                $form['container'][$key][$time_key]['ora_da']  = array(
                    '#type' => 'textfield',
                    '#title' => 'Entrata:',
                    '#size'  => '3',
                    '#prefix' => '<div class = "container-inline">',
                    '#suffix' => '</div>',
                    '#disabled' => $is_open?false:true,
                    '#attributes' => array(
                        'class' => array('time','timeRange'),
                        'autocomplete' => 'off'
                    )
                );
                $form['container'][$key][$time_key]['ora_a']= array(
                    '#type' => 'textfield',
                    '#title' => 'Uscita:',
                    '#size'  => '3',
                    '#prefix' => '<div class = "container-inline">',
                    '#suffix' => '</div>',
                    '#disabled' => $is_open?false:true,
                    '#attributes' => array(
                        'class' => array('time','timeRange'),
                        'autocomplete' => 'off'
                    )
                );
                $form['container'][$key][$time_key]['where']= array(
                    '#type' => 'select',
                    '#title' => t('Struttura:'),
                    '#options' => $lperson_list,
                    '#prefix' => '<div class = "container-inline">',
                    '#suffix' => '</div><br><br>',
                    '#disabled' => $is_open?false:true,
                );

                if (!array_key_exists('clicked_button', $form_state)) {
                    $form['container'][$key][$time_key]['ora_da']['#value'] = !empty($form_state_input_container[$key][$time_key]['ora_da'])?$form_state_input_container[$key][$time_key]['ora_da']:'';
                    $form['container'][$key][$time_key]['ora_a']['#value'] = !empty($form_state_input_container[$key][$time_key]['ora_a'])?$form_state_input_container[$key][$time_key]['ora_a']:'';
                    $form['container'][$key][$time_key]['where']['#value'] = !empty($form_state_input_container[$key][$time_key]['where'])?$form_state_input_container[$key][$time_key]['where']:$internship->lperson_primary->id_lperson;

                } else {
                    $form['container'][$key][$time_key]['ora_da']['#default_value'] = !empty($form_state_input_container[$key][$time_key]['ora_da'])?$form_state_input_container[$key][$time_key]['ora_da']:'';
                    $form['container'][$key][$time_key]['ora_a']['#default_value'] = !empty($form_state_input_container[$key][$time_key]['ora_a'])?$form_state_input_container[$key][$time_key]['ora_a']:'';
                    $form['container'][$key][$time_key]['where']['#default_value'] = !empty($form_state_input_container[$key][$time_key]['where'])?$form_state_input_container[$key][$time_key]['where']:$internship->lperson_primary->id_lperson;
                }
            }


            $form['container'][$key]['add_time'] = array(
                '#type' => 'submit',
                '#name' => 'add_time_'.$key,
                '#value' => t('Aggiungi orario'),
                '#submit' => ['add_time_submit'],
                '#prefix' => '<div class = "container-inline">',
                '#suffix' => '</div>',
                '#ajax' => array(
                    'callback' => 'add_time_callback',
                    'wrapper' => 'container_'.$key
                ),
                '#attributes' => array(
                    'date_key' => $key,
                    'class' => array('btn-success')
                ),
                '#limit_validation_errors' => array(),
                '#access' => $is_open,
                '#weight' => 1,
            );
            $form['container'][$key]['remove_time'] = array(
                '#type' => 'submit',
                '#name' => 'remove_time_'.$key,
                '#value' => t('Rimuovi orario'),
                '#submit' => ['remove_time_submit'],
                '#prefix' => '<div class = "container-inline">',
                '#suffix' => '</div>',
                '#ajax' => array(
                    'callback' => 'add_time_callback',
                    'wrapper' => 'container_'.$key
                ),
                '#attributes' => array(
                    'date_key' => $key,
                    'class' => array('btn-danger')
                ),
                '#limit_validation_errors' => array(),
                '#access' => $is_open,
                '#weight' => 2,
            );

            $form['container'][$key]['working_time']= array(
                '#markup' => '',
                '#weight' => 3,
                '#prefix' => '<br>'
            );
            if (!empty($working_times_text_array[ucwords(strftime("%a", strtotime($date)))]))
                $form['container'][$key]['working_time']['#markup'] = $working_times_text_array[ucwords(strftime("%a", strtotime($date)))];

        }
    }


    foreach ($months as $month) {
        $class = array('btn-default');
        if(strcmp($month, $form_state["build_info"]["args"]["2"].'-'.$form_state["build_info"]["args"]["3"]) == 0) {
            $class = array_merge($class, array('active'));
        }
        $args = explode('-',$month);
        $form['pagination']['goto_'.$month] = array(
            '#type' => 'submit',
            '#submit' => array('internship_attendance_form_goto_submit'),
            '#value' => ucwords(strftime("%b %Y",date_create_from_format('m-y', $month)->getTimestamp())),
            '#name' => 'goto_'.$month,
            '#attributes' => array(
                'class' => $class,
                'month' => ($args[0]),
                'year' => $args[1]
            ),
            '#limit_validation_errors' => array(),
            '#prefix' => '<li>',
            '#suffix' => '</li>'
        );
    }

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Salva'),
        '#access' => $is_open,
    );
    $form['actions']['close_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Chiudi Registro'),
        '#submit' => array('close_submit'),
        '#attributes' => array(
            'onclick' => 'if(!confirm("Il registro non potrà più essere modificato dopo la chiusura. Proseguire?")){return false;}'
        ),
        '#access' => ($is_open && ($internship->internship_state->state == 0 || $internship->internship_state->state == 7)),
    );

    return $form;
}


/**
 * @param $start_str
 * @param $end_str
 * @return array
 */
function getArrayMonths($start_str, $end_str) {
    $start    = (new DateTime($start_str))->modify('first day of this month');
    $end      = (new DateTime($end_str))->modify('first day of next month');
    $interval = DateInterval::createFromDateString('1 month');
    $period   = new DatePeriod($start, $interval, $end);
    $months = array();
    foreach ($period as $dt) {
        $months[$dt->format("m-y")] = $dt->format("m-y");
    }
    return $months;
}

/**
 * @param $form
 * @param $form_state
 */
function add_time_submit($form, &$form_state) {
    $key = $form_state['triggering_element']['#attributes']['date_key'];
    $c = max($form_state['time_keys_'.$key])+1;
    if (!empty($form_state['input']['container'][$key][$c -1]['ora_da']) && !empty($form_state['input']['container'][$key][$c -1]['ora_a'])) {
        $form_state['time_keys_'.$key][$c] = $c;
        $form_state['rebuild'] = TRUE;
    }
    drupal_get_messages();
}

/**
 * @param $form
 * @param $form_state
 */
function remove_time_submit($form, &$form_state) {
    $key = $form_state['triggering_element']['#attributes']['date_key'];
    $c = max($form_state['time_keys_'.$key]);
    if (!empty($form_state['input']['container'][$key][$c -1]['ora_da']) && !empty($form_state['input']['container'][$key][$c -1]['ora_a'])) {
        unset($form_state['time_keys_'.$key][$c]);
        $form_state['rebuild'] = TRUE;
    }
    drupal_get_messages();
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_time_callback($form, &$form_state) {
    $key = $form_state['triggering_element']['#attributes']['date_key'];
    return $form['container'][$key];

}


/**
 * @param $form
 * @param $form_state
 */
function internship_attendance_form_validate($form, &$form_state) {
    foreach($form_state['input']['container'] AS $date => $values) {
        foreach($values AS $time_key => $time) {
            if (!empty($time['ora_da']) || !empty($time['ora_a'])) {
                if (preg_match('#([01]?[0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])?$#', $time['ora_da']) != 1) {
                    form_set_error('edit-container-' . $date . '-' . $time_key . '-ora_da', t('Orario entrata '.ucwords(strftime("%A, %d %b %G", strtotime($date))).' non valido.'));
                }
                if (preg_match('#([01]?[0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])?$#', $time['ora_a']) != 1) {
                    form_set_error('edit-container-' . $date . '-' . $time_key . '-ora_a', t('Orario uscita '.ucwords(strftime("%A, %d %b %G", strtotime($date))).' non valido.'));
                }
            }
        }
    }
}


/**
 * @param $form
 * @param $form_state
 */
function internship_attendance_form_goto_submit($form, &$form_state) {

    $month = $form_state['clicked_button']['#attributes']['month'];
    $year = $form_state['clicked_button']['#attributes']['year'];
    drupal_goto('internship/attendance/'.$form_state["build_info"]["args"]["1"].'/'.$month.'/'.$year);
}

/**
 * @param $form
 * @param $form_state
 */
function internship_attendance_form_prev_submit($form, &$form_state) {
    internship_attendance_form_submit($form,$form_state);
    $n_pages = ceil((floatval($form_state["build_info"]["args"]["2"]))/10.0);

    if ($n_pages != 1) {
        drupal_goto('internship/attendance/'.$form_state["build_info"]["args"]["1"].'/'.(intval($form_state["build_info"]["args"]["2"])-10));
    } else {
        drupal_get_messages();
    }
}

/**
 * @param $form
 * @param $form_state
 */
function internship_attendance_form_next_submit($form, &$form_state) {
    internship_attendance_form_submit($form,$form_state);
    $n_pages = ceil(floatval(count($form['#dates'])-(floatval($form_state["build_info"]["args"]["2"])))/10);
    if ($n_pages != 1) {
        drupal_goto('internship/attendance/'.$form_state["build_info"]["args"]["1"].'/'.(intval($form_state["build_info"]["args"]["2"])+10));
    } else {
        drupal_get_messages();
    }
}

/**
 * @param $form
 * @param $form_state
 */
function close_submit($form, &$form_state) {
    $fields = array(
        'is_closed' => 1,
    );
    try {
        db_set_active('getif_data');
        $query = db_update('internship_attendance_sheet');
        $query->fields($fields)->where('id_internship = '.$form_state["build_info"]["args"]["1"].' and active = 1')->execute();
        db_set_active();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    clean_cron_by_id('internship_attendance_sheet',$form_state["build_info"]["args"]["1"]);
}

/**
 * @param $form
 * @param $form_state
 */
function internship_attendance_form_submit($form, &$form_state) {

    $id_internship = $form_state["build_info"]["args"]["1"];
    db_set_active('getif_data');
    $elements = db_query("
        SELECT t1.register
        FROM `internship_attendance_sheet` AS t1
        WHERE t1.id_internship = ".$id_internship." AND t1.active = 1;
    ");
    db_set_active();

    $form_state_input_container = $form_state['input']['container'];
    $internship_register_base64 = $elements->fetchCol(0); // registro dal db
    if (is_array(json_decode(base64_decode($internship_register_base64[0]),true))) { // se esiste un registro completo o incompleto
        $internship_register_old = json_decode(base64_decode($internship_register_base64[0]),true);
        $internship_register = array_replace($internship_register_old, $form_state_input_container);
    } else {
        $internship_register = $form_state_input_container; // nuova porzione del registro
    }
    $file_base64 = base64_encode(json_encode($internship_register));
    $fields = array(
        'id_internship'=> $form_state["build_info"]["args"]["1"],
        'register' => $file_base64,
        'date_upd' => date("Y-m-d H:i:s"),
        'active'    => 1
    );
    $key = array(
        'id_internship'=> $form_state["build_info"]["args"]["1"],
        'active' => 1
    );
    try {
        db_set_active('getif_data');
        $query = db_merge('internship_attendance_sheet');
        $query -> key($key) -> fields($fields) -> execute();
        db_set_active();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
}
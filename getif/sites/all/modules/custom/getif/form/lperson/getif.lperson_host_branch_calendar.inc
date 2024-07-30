<?php

/**
 * Theme lperson_branch_calendar
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_host_branch_calendar_form($variables){
    drupal_add_js(drupal_get_path('module', 'getif') . '/js/monthly.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/css/monthly.css');
    $form = $variables['form'];
    return getif_form_theme($form,null,null);
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function lperson_host_branch_calendar_form($form, &$form_state) {
    global $base_url;
    $id_lperson = $form_state["build_info"]["args"]["1"];
    $lperson = getRecordById('lperson','getif_data', $id_lperson, 'active');
    $lperson_parent = getLPersonById('getif_data',$lperson->id_lperson_parent);
    $id_lperson_parent = $lperson_parent -> id_lperson;
    // Top Buttons
    $form['nav']['goto_dashboard'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_dashboard'),
    );
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Gestione Strutture'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_back'),
    );
    $form['nav']['back']['#attributes']['id_lperson_parent'] = $id_lperson_parent;
    db_set_active('getif_data');
    $query = db_select('internship_lperson','t1');
    $query->innerJoin('lperson','t2','t1.id_lperson = t2.id_lperson');
    $query->innerJoin('internship','t3','t3.id_internship = t1.id_internship');
    $query->innerJoin('internship_state','t4','t4.id_internship = t3.id_internship');
    $query->innerJoin('internship_person','t5','t5.id_internship = t3.id_internship');
    $query->innerJoin('person','t6','t5.id_person = t6.id_person');
    $query->condition('t2.id_lperson',$id_lperson);
    $query->condition('t3.active',1);
    $query->condition('t4.active',0,'<>');
    $query->fields('t3');
    $query->addField('t4','date_start','internship_state_date_start');
    $query->addField('t4','date_end','internship_state_date_end');
    $query->addField('t4','state','state');
    $query->fields('t6',array('firstname','lastname'));
    $internships = $query->execute()->fetchAll();
    db_set_active();
    $monthly_array = array('monthly' => array());
    $legend = '';
    foreach ($internships AS $internship) {
        if (empty($internship->internship_state_date_start)) {
            $date_start_effective = $internship->date_start; // data di inizio  programmata
            $date_end_effective = $internship->date_end;    // data di fine programmata
        } else {
            $date_start_effective = $internship->internship_state_date_start;
            if (empty($internship->internship_state_date_end)) {
                $datetime1 = new DateTime($internship->date_start);
                $datetime2 = new DateTime($internship->date_end);
                $interval = $datetime1->diff($datetime2);
                $date_end_effective =$internship->date_end;
            } else {
                $date_end_effective = $internship->internship_state_date_end;
            }
        }
        $color = getColor($internship->id_internship*3);
        if ($internship->flg_voluntary == 0) { // Tirocinio
            $name = 'Tirocinio #'.$internship->id_internship.' '.$internship->firstname.' '.$internship->lastname;
            $url =
                !in_array($internship->state,array(4,5,6,7))?
                    $base_url.'/internship/view/'.(intval($internship->state)+1).'/'.$internship->id_internship:
                    $base_url.'/internship/manage/'.$internship->id_internship;
        } else { // Frequenza
            $name = 'Frequenza #'.$internship->id_internship.' '.$internship->firstname.' '.$internship->lastname;
            $url =
                !in_array($internship->state,array(4,5,6,7))?
                    $base_url.'/vinternship/view/'.(intval($internship->state)+1).'/'.$internship->id_internship:
                    $base_url.'/vinternship/manage/'.$internship->id_internship;
        }

        $monthly_array['monthly'][] = array(
            'id'=> $internship->id_internship,
            'name' => $name,
            "startdate" => $date_start_effective,
            "enddate" => $date_end_effective,
            "color" => $color,
            "url" => $url
        );
        $legend .= '
            <div style="margin: 5px;display:inline-block">
                <div style="display:inline-block;vertical-align:top;margin-right:1px;min-width:20px;height:20px;background-color:'.$color.'">&nbsp;</div>
                <div style="display:inline-block;vertical-align:top;max-width:100px">
                    <span>'
            .$name.'
                    </span>
                </div>
            </div>';
    }
    $monthly_json = json_encode($monthly_array);
    $fs_branch_calendar_title = t('Calendario tirocini / frequenze').' '.t('di').'&nbsp;'._strformat($lperson->name);

    $form['fs_branch_calendar'] = array(
        '#type' => 'container',
        '#title' => $fs_branch_calendar_title,
        '#prefix' => '<div id="fs-branch-div">',
        '#suffix' => '</div>',
    );
    $form['fs_branch_calendar']['markup'] = array(
        '#markup' => '
                <h2>Legenda</h2>
                '.$legend.'<hr>
                <div style="width:100%; display:inline-block;">
                    <div class="monthly" id="mycalendar"></div>
                </div>
                <script type="text/javascript">
                    jQuery(function($) {
                        var sampleEvents = '.$monthly_json.'
                        $(window).load( function() {
                            $(\'#mycalendar\').monthly({
                                mode: \'event\',
                                dataType: \'json\',
                                events: sampleEvents
                            });
                        });
                    });
                </script >'
    );
    return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function goto_back($form, &$form_state) {
    $id_lperson_parent = $form_state['clicked_button']['#attributes']['id_lperson_parent'];
    getif_goto('lperson_host/branches/'.$id_lperson_parent,array(),302,true);
}

/**
 * @param $num
 * @return string
 */
function getColor($num) {
    $hash = md5('color' . $num); // modify 'color' to get a different palette
    return
        '#'.
        (substr($hash, 0, 2)). // r
        (substr($hash, 2, 2)). // g
        (substr($hash, 4, 2)); //b
}

/* end */
<?php

function front_page() {
    global $base_url, $user;
    if(in_array('administrator',$user->roles) || in_array('amministratore',$user->roles) || in_array('operatore',$user->roles) || in_array('operator
    ',$user->roles)) {
        // Card Tirocini
        db_set_active('getif_data');
        $query = db_select('internship','t1');
        $query->fields('t1',array('id_internship'));
        $num_internship = $query->where( 't1.flg_voluntary = 0 AND t1.active = 1')->countQuery()->execute()->fetchField();
        db_set_active();
        db_set_active('getif_data');
        $query = db_select('internship','t1');
        $query->innerJoin('internship_state','t2','t1.id_internship = t2.id_internship');
        $query->fields('t1',array('id_internship'));
        $num_internship_on = $query->where( 't1.flg_voluntary = 0 AND t2.date_end is NULL AND t2.state IN (5,6) AND t1.active = 1 AND t2.active=1')->countQuery()->execute()->fetchField();
        db_set_active();
        $inactive_states = array(1,2,3,4);
        db_set_active('getif_data');
        $query = db_select('internship','t2');
        $query->innerJoin('internship_state','t3','t2.id_internship = t3.id_internship');
        $query->fields('t2',array('id_internship'));
        $num_internship_applicated = $query
            ->where('t2.flg_voluntary = 0 AND t3.state IN ('.join($inactive_states,',').') AND t2.active = 1 AND t3.active = 1')
            ->countQuery()->execute()->fetchField();
        db_set_active();
        // Card Frequenze
        db_set_active('getif_data');
        $query = db_select('internship','t1');
        $query->fields('t1',array('id_internship'));
        $num_vinternship = $query->where( 't1.flg_voluntary = 1 AND t1.active = 1')->countQuery()->execute()->fetchField();
        db_set_active();
        db_set_active('getif_data');
        $query = db_select('internship','t1');
        $query->innerJoin('internship_state','t2','t1.id_internship = t2.id_internship');
        $query->fields('t1',array('id_internship'));
        $num_vinternship_on = $query->where( 't1.flg_voluntary = 1 AND t2.date_end is NULL AND t2.state IN (5,6) AND t1.active = 1 AND t2.active=1')->countQuery()->execute()->fetchField();
        db_set_active();
        $inactive_states = array(1,2,3,4);
        db_set_active('getif_data');
        $query = db_select('internship','t2');
        $query->innerJoin('internship_state','t3','t2.id_internship = t3.id_internship');
        $query->fields('t2',array('id_internship'));
        $num_vinternship_applicated = $query
            ->where('t2.flg_voluntary = 1 AND t3.state IN ('.join($inactive_states,',').') AND t2.active = 1 AND t3.active = 1')
            ->countQuery()->execute()->fetchField();
        db_set_active();
    } else {
        // Card Tirocini
        db_set_active('getif_data');
        $query = db_select('profilo_utente', 't1');
        $query->innerJoin('person', 't2', 't1.id_person = t2.id_person');
        $query->fields('t1', array('id_person'));
        $id_person = $query->where('t1.uid = ' . $user->uid . ' AND t2.active = 1')->execute()->fetchField();
        db_set_active();
        db_set_active('getif_data');
        $query = db_select('internship_host_tutor', 't1');
        $query->innerJoin('internship','t0','t0.id_internship = t1.id_internship');
        $query->innerJoin('person_lperson_prole', 't2', 't1.id_person_lperson_prole = t2.id_person_lperson_prole AND id_prole = 2');
        $query->innerJoin('person_lperson', 't3', 't2.id_person_lperson = t3.id_person_lperson');
        $query->innerJoin('person', 't4', 't4.id_person = t3.id_person');
        $query->fields('t1', array('id_internship'));
        $query->condition('t4.id_person', $id_person);
        $num_internship = $query->where('t0.flg_voluntary = 0 AND t0.active = 1 AND t1.active = 1 AND t2.active = 1 AND t3.active = 1 AND t4.active = 1')->countQuery()->execute()->fetchField();
        db_set_active();
        db_set_active('getif_data');
        $query = db_select('internship_host_tutor', 't1');
        $query->innerJoin('internship','t0','t0.id_internship = t1.id_internship');
        $query->innerJoin('person_lperson_prole', 't2', 't1.id_person_lperson_prole = t2.id_person_lperson_prole AND id_prole = 2');
        $query->innerJoin('person_lperson', 't3', 't2.id_person_lperson = t3.id_person_lperson');
        $query->innerJoin('person', 't4', 't4.id_person = t3.id_person');
        $query->innerJoin('internship_state','t5','t1.id_internship = t5.id_internship');
        $query->fields('t1', array('id_internship'));
        $query->condition('t4.id_person', $id_person);
        $num_internship_on = $query->where('t0.flg_voluntary = 0 AND t0.active = 1 AND t5.date_end is NULL AND t5.state IN (5,6) AND t1.active = 1 AND t2.active = 1 AND t3.active = 1 AND t4.active = 1 AND t5.active = 1')->countQuery()->execute()->fetchField();
        db_set_active();
        $inactive_states = array(1,2,3,4);
        db_set_active('getif_data');
        $query = db_select('internship_host_tutor', 't1');
        $query->innerJoin('internship','t0','t0.id_internship = t1.id_internship');
        $query->innerJoin('person_lperson_prole', 't2', 't1.id_person_lperson_prole = t2.id_person_lperson_prole AND id_prole = 2');
        $query->innerJoin('person_lperson', 't3', 't2.id_person_lperson = t3.id_person_lperson');
        $query->innerJoin('person', 't4', 't4.id_person = t3.id_person');
        $query->innerJoin('internship_state','t5','t1.id_internship = t5.id_internship');
        $query->fields('t1',array('id_internship'));
        $query->condition('t4.id_person', $id_person);
        $num_internship_applicated = $query
            ->where('t0.flg_voluntary = 0 AND t0.active = 1 AND t5.state IN ('.join($inactive_states,',').') AND t2.active = 1 AND t3.active = 1')
            ->countQuery()->execute()->fetchField();
        db_set_active();
        // Card Frequenze
        db_set_active('getif_data');
        $query = db_select('profilo_utente', 't1');
        $query->innerJoin('person', 't2', 't1.id_person = t2.id_person');
        $query->fields('t1', array('id_person'));
        $id_person = $query->where('t1.uid = ' . $user->uid . ' AND t2.active = 1')->execute()->fetchField();
        db_set_active();
        db_set_active('getif_data');
        $query = db_select('internship_project_contact', 't1');
        $query->innerJoin('internship','t0','t0.id_internship = t1.id_internship');
        $query->innerJoin('person_lperson_prole', 't2', 't1.id_person_lperson_prole = t2.id_person_lperson_prole AND id_prole = 3');
        $query->innerJoin('person_lperson', 't3', 't2.id_person_lperson = t3.id_person_lperson');
        $query->innerJoin('person', 't4', 't4.id_person = t3.id_person');
        $query->fields('t1', array('id_internship'));
        $query->condition('t4.id_person', $id_person);
        $num_vinternship = $query->where('t0.flg_voluntary = 1 AND t0.active = 1 AND t1.active = 1 AND t2.active = 1 AND t3.active = 1 AND t4.active = 1')->countQuery()->execute()->fetchField();
        db_set_active();
        db_set_active('getif_data');
        $query = db_select('internship_project_contact', 't1');
        $query->innerJoin('internship','t0','t0.id_internship = t1.id_internship');
        $query->innerJoin('person_lperson_prole', 't2', 't1.id_person_lperson_prole = t2.id_person_lperson_prole AND id_prole = 3');
        $query->innerJoin('person_lperson', 't3', 't2.id_person_lperson = t3.id_person_lperson');
        $query->innerJoin('person', 't4', 't4.id_person = t3.id_person');
        $query->innerJoin('internship_state','t5','t1.id_internship = t5.id_internship');
        $query->fields('t1', array('id_internship'));
        $query->condition('t4.id_person', $id_person);
        $num_vinternship_on = $query->where('t0.flg_voluntary = 1 AND t0.active = 1 AND t5.date_end is NULL AND t5.state IN (5,6) AND t1.active = 1 AND t2.active = 1 AND t3.active = 1 AND t4.active = 1 AND t5.active = 1')->countQuery()->execute()->fetchField();
        db_set_active();
        $inactive_states = array(1,2,3,4);
        db_set_active('getif_data');
        $query = db_select('internship_project_contact', 't1');
        $query->innerJoin('internship','t0','t0.id_internship = t1.id_internship');
        $query->innerJoin('person_lperson_prole', 't2', 't1.id_person_lperson_prole = t2.id_person_lperson_prole AND id_prole = 3');
        $query->innerJoin('person_lperson', 't3', 't2.id_person_lperson = t3.id_person_lperson');
        $query->innerJoin('person', 't4', 't4.id_person = t3.id_person');
        $query->innerJoin('internship_state','t5','t1.id_internship = t5.id_internship');
        $query->fields('t1',array('id_internship'));
        $query->condition('t4.id_person', $id_person);
        $num_vinternship_applicated = $query
            ->where('t0.flg_voluntary = 1 AND t0.active = 1 AND t5.state IN ('.join($inactive_states,',').') AND t2.active = 1 AND t3.active = 1')
            ->countQuery()->execute()->fetchField();
        db_set_active();
    }
    $output = '';
    $output .= '<div class="col-md-12 form-container">';
    $output .= '
        
        <div class="container-fluid">
            <div class="row">
                <div class="col-md-6">
                    <div class="card messages">
                        <div class="main">
                            <article onclick="location.href=\'' . url($base_url . "/internship/list") . '\'">
                                <div class="info">
                                    <div class="temp">' . $num_internship . '</div>
                                    <div>Tirocini totali</div>
                                </div>
                            </article>
                        </div>
                    </div>
                    <div class="card messages">
                        <div class="main" style="background:green">
                            <article onclick="location.href=\'' . url($base_url . "/internship/list",array("query"=>array('state'=>'5'))) . '\'">
                                <div class="info">
                                    <div class="temp">' . $num_internship_on . '</div>
                                    <div>Tirocini attivi</div>
                                </div>
                            </article>
                        </div>
                    </div>
                    <div class="card messages">
                        <div class="main" style="background:#f0ad4e">
                            <article onclick="location.href=\'' . url($base_url . "/internship/list",array("query"=>array('state'=>'pending'))) . '\'">
                                <div class="info">
                                    <div class="temp">' . $num_internship_applicated . '</div>
                                    <div>Tirocini in attesa</div>
                                </div>
                            </article>
                        </div>
                    </div>    
                </div>
                <div class="col-md-6">
                    <div class="card messages">
                        <div class="main">
                            <article onclick="location.href=\'' . url($base_url . "/vinternship/list") . '\'">
                                <div class="info">
                                    <div class="temp">' . $num_vinternship . '</div>
                                    <div>Frequenze totali</div>
                                </div>
                            </article>
                        </div>
                    </div>
                    <div class="card messages">
                        <div class="main" style="background:green">
                            <article onclick="location.href=\'' . url($base_url . "/vinternship/list",array("query"=>array('state'=>'5'))) . '\'">
                                <div class="info">
                                    <div class="temp">' . $num_vinternship_on . '</div>
                                    <div>Frequenze attive</div>
                                </div>
                            </article>
                        </div>
                    </div>
                    <div class="card messages">
                        <div class="main" style="background:#f0ad4e">
                            <article onclick="location.href=\'' . url($base_url . "/vinternship/list",array("query"=>array('state'=>'pending'))) . '\'">
                                <div class="info">
                                    <div class="temp">' . $num_vinternship_applicated . '</div>
                                    <div>Frequenze in attesa</div>
                                </div>
                            </article>
                        </div>
                    </div>
                </div>
             
             </div>
             
         </div>';
    $output .= '</div>';
    return $output;
}

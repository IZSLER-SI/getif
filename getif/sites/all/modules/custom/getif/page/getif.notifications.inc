<?php

function getif_notifications() {

    global $user, $base_url;
    /* Notifiche */
    $notifications = array();
    $n_notifications = 0;
    if (in_array('administrator',$user->roles) || in_array('amministratore',$user->roles) || in_array('operator',$user->roles) || in_array('operatore',$user->roles)) {
        // Tirocinio in scadenza
        db_set_active('getif_data');
        $query = db_select('cron', 't1');
        $query->innerJoin('internship', 't2', 't1.id_table = t2.id_internship AND t2.flg_voluntary = 0');
        $query->condition('t1.table_name', 'internship');
        $query->fields('t1');
        $query->condition('t1.state', '1');
        $results = $query->execute()->fetchAll();
        db_set_active();
        foreach ($results AS $result) {
            $notifications[] =  t('<a href="@url" class="list-group-item list-group-item-warning">Tirocinio <b>#@id</b> in scadenza</a>',
                array(
                    '@url' => url('internship/manage/'.$result->id_table),
                    '@id' => $result->id_table
                )
            );
            $n_notifications++;
        }
        // Frequenza volontaria in scadenza
        db_set_active('getif_data');
        $query = db_select('cron', 't1');
        $query->innerJoin('internship', 't2', 't1.id_table = t2.id_internship AND t2.flg_voluntary = 1');
        $query->condition('t1.table_name', 'internship');
        $query->fields('t1');
        $query->condition('t1.state', '1');
        $results = $query->execute()->fetchAll();
        db_set_active();
        foreach ($results AS $result) {
            $notifications[] =  t('<a href="@url" class="list-group-item list-group-item-warning">Frequenza volontaria <b>#@id</b> in scadenza</a>',
                array(
                    '@url' => url('vinternship/manage/'.$result->id_table),
                    '@id' => $result->id_table
                )
            );
            $n_notifications++;
        }
        // Tirocinio concluso da confermare
        db_set_active('getif_data');
        $query = db_select('cron', 't1');
        $query->innerJoin('internship', 't2', 't1.id_table = t2.id_internship AND t2.flg_voluntary = 0');
        $query->condition('t1.table_name', 'internship');
        $query->fields('t1');
        $query->condition('t1.state', '2');
        $results = $query->execute()->fetchAll();
        db_set_active();
        foreach ($results AS $result) {
            $notifications[] =  t('<a href="@url" class="list-group-item list-group-item-warning">Tirocinio <b>#@id</b> concluso da confermare</a>',
                array(
                    '@url' => url('internship/manage/'.$result->id_table),
                    '@id' => $result->id_table
                )
            );
            $n_notifications++;
        }
        // Frequenza conclusa da confermare
        db_set_active('getif_data');
        $query = db_select('cron', 't1');
        $query->innerJoin('internship', 't2', 't1.id_table = t2.id_internship AND t2.flg_voluntary = 1');
        $query->condition('t1.table_name', 'internship');
        $query->fields('t1');
        $query->condition('t1.state', '2');
        $results = $query->execute()->fetchAll();
        db_set_active();
        foreach ($results AS $result) {
            $notifications[] =  t('<a href="@url" class="list-group-item list-group-item-warning">Frequenza volontaria <b>#@id</b> concluso da confermare</a>',
                array(
                    '@url' => url('vinternship/manage/'.$result->id_table),
                    '@id' => $result->id_table
                )
            );
            $n_notifications++;
        }
        // Convenzioni in scadenza
        db_set_active('getif_data');
        $query = db_select('cron', 't1');
        $query->fields('t1');
        $query->condition('t1.table_name', 'agreement');
        $query->condition('t1.state', '1');
        $results = $query->execute()->fetchAll();
        db_set_active();
        foreach ($results AS $result) {
            $notifications[] =  t('<a href="@url" class="list-group-item list-group-item-warning">Convenzione <b>#@id</b> in scadenza</a>',
                array(
                    '@url' => url('agreement/edit/'.$result->id_table),
                    '@id' => $result->id_table
                )
            );
            $n_notifications++;
        }
    }
    // Registro presenze tirocini da chiudere
    db_set_active('getif_data');
    $query = db_select('cron', 't1');
    $query->innerJoin('internship', 't2', 't1.id_table = t2.id_internship AND t2.flg_voluntary = 0');
    $query->innerJoin('internship_state', 't3', 't1.id_table = t3.id_internship');
    $query->condition('t1.table_name', 'internship_attendance_sheet');
    $query->fields('t1');
    $query->fields('t3');
    $query->condition('t1.state', '1');
    $results = $query->execute()->fetchAll();
    db_set_active();
    foreach ($results as $result) {
        $notifications[] =  t('<a href="@url" class="list-group-item list-group-item-warning">Registro tirocinio <b>#@id</b> da chiudere</a>',
            array(
                '@url' => url('internship/attendance/'.$result->id_internship.'/'.date('m',strtotime($result->date_start)).'/'.date('y',strtotime($result->date_start))),
                '@id' => $result->id_internship
            )
        );
        $n_notifications++;
    }
    // Registro presenze frequenze volontarie da chiudere
    db_set_active('getif_data');
    $query = db_select('cron', 't1');
    $query->innerJoin('internship', 't2', 't1.id_table = t2.id_internship AND t2.flg_voluntary = 1');
    $query->innerJoin('internship_state', 't3', 't1.id_table = t3.id_internship');
    $query->condition('t1.table_name', 'internship_attendance_sheet');
    $query->fields('t1');
    $query->fields('t3');
    $query->condition('t1.state', '1');
    $results = $query->execute()->fetchAll();
    db_set_active();
    foreach ($results as $result) {
        $notifications[] =  t('<a href="@url" class="list-group-item list-group-item-warning">Registro frequenza <b>#@id</b> da chiudere</a>',
            array(
                '@url' => url('vinternship/attendance/'.$result->id_internship.'/'.date('m',strtotime($result->date_start)).'/'.date('y',strtotime($result->date_start))),
                '@id' => $result->id_internship
            )
        );
        $n_notifications++;
    }
    $module_path = drupal_get_path('module', 'getif');
    $full_path = $module_path .'/css/getif.css';
    drupal_add_css($full_path);
    $id_utente = arg(1);
    session_set('id_utente', $id_utente);
    $output = '';
    $output .= '<div class="col-md-12 form-container">';
    /*$output .= '
    <div class="bootstrap"><div class="page-head"><div class="wrapper clearfix"><h1 class="page-title">'.drupal_get_title().'</h1>
        <div class="page-bar toolbarBox">
            <div class="btn-toolbar">
                <ul id="toolbar-nav" class="nav nav-pills pull-right collapse navbar-collapse">
                    <li>
                        <button id="edit-goto-dashboard" onclick="location.href=\''.$base_url.'\';" value="Dashboard" class="btn btn-default form-submit icon-before">
                        <span class="icon glyphicon glyphicon-dashboard" aria-hidden="true"></span>Dashboard</button>
                    </li>
                </ul>
                    
            </div>
        </div>
    </div></div></div>';*/

    $output .= '<fieldset class="panel panel-default form-wrapper">
                <legend class="panel-heading bootstro" data-bootstro-title="Navigazione '.drupal_get_title().'" data-bootstro-content="Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li></ul>" data-bootstro-width="600px" data-bootstro-placement="bottom">
                    <div style="float:left">
                        <span class="panel-title fieldset-legend">Notifiche</span>
                    </div>
                    <div style="float:right">
                        <button id="edit-goto-dashboard" onclick="location.href=\''.$base_url.'\';" value="Dashboard" class="btn btn-default form-submit icon-before">
                        <span class="icon glyphicon glyphicon-dashboard" aria-hidden="true"></span>Dashboard</button>
                        <a href="#" class="help-btn" data-toggle="tooltip" data-original-title="Help contenuto pagina">
                            <span class="glyphicon glyphicon-question-sign" style="font-size:20px;">
                        </a>
                    </div>
                </legend>
                <div class="panel-body bootstro" data-bootstro-title="Maschera" data-bootstro-content="La maschera permette di consultare le notifiche." data-bootstro-width="600px" data-bootstro-placement="bottom">
                    <div class="table-responsive">';
    $output .=
        '<div class="list-group">';
    $output .='<div class="header-msgs">'.format_plural($n_notifications, '<h1><b>1</b> <small>notifica','<h1><b>@count</b> <small>notifiche').'</small></h1></div>';
    foreach ($notifications AS $notification) {
        $output .= $notification;
    }
    $output .=
        '</div>';
    $output .= '</div></div></fieldset>';

    return $output;
}

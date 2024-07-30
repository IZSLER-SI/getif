<?php

/**
 * Theme lperson_list_view
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_list_view_form($variables){
    
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    $form = $variables['form'];
    $output = '';
    $output .= '<div class="col-md-12 form-container">';
    $output .= '
    <div class="bootstrap"><div class="page-head"><div class="wrapper clearfix"><h1 class="page-title">'.drupal_get_title().'</h1>
        <div class="page-bar toolbarBox">
            <div class="btn-toolbar">
                <ul id="toolbar-nav" class="nav nav-pills pull-right collapse navbar-collapse">
                    <li>
                        '.drupal_render($form['actions']['back']).'
                    </li>
                    <li>
                        '.drupal_render($form['actions']['new']).'
                    </li>
                </ul>
                    
            </div>
        </div>
    </div></div></div>';
    $output .= '<div class="row">';
    $output .= '<div class="col-md-12 form-container">';
    $output .= '<div class="panel panel-default">';
    $output .= '<div class="panel-body">';
    $output .= '<div class="col-md-1">'.drupal_render($form['filter_panel']['filter']).'</div>';
    $output .= '<div class="col-md-12">'.drupal_render($form['filter_panel']['save']).drupal_render($form['filter_panel']['reset']).'</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '<div class="row">';
    $output .= '<div class="col-md-12 form-container">';
    $output .= drupal_render_children($form);
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '
            <script>
                jQuery(document).ready(function() {
                    // Setup - add a text input to each footer cell
                   
         
                    var table = jQuery("#tabella").DataTable( {
                        pageLength: 10,
                        "scrollX": false,
                        orderCellsTop: true,
                        fixedHeader: true,
                        columnDefs: [ { orderable: false, targets: [4] } ],
                        "order": [[ 0, "desc" ]],
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
                } );
                
                    
            </script>
            ';
    return $output;
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function lperson_list_view_form($form, &$form_state) {
    db_set_active('getif_data');
    $query = db_select('lperson', 't1');
    // filtri
    if (!empty($_GET['lprole'])) {
        $query->innerJoin('lperson_lprole','t2','t1.id_lperson = t2.id_lperson');
        $query->condition('t2.id_lprole', $_GET['lprole']);
    }


    $results = $query
        ->fields('t1')
        //->isNull('id_lperson_parent')
        ->condition('level',0)
        ->execute();
    db_set_active(); 
    $rows = array();
    foreach($results as $key => $result) {
        $rows[$key] = array(
            l($result->id_lperson, 'lperson/edit/'.$result->id_lperson),
            $result->name
        );

        // Ruoli
        $lperson_lproles = getAllRecordByField('lperson_lprole', 'getif_data' , 'id_lperson', $result->id_lperson, 'active');
        $testo = '<ul>';
        foreach($lperson_lproles as $lperson_lprole) {
            $testo .= '<li>';
            $testo .= test($lperson_lprole->id_lperson, $lperson_lprole->id_lprole,$testo);
            $testo .= '</li>';
        }
        $testo .= '</ul>';
        $rows[$key][] = $testo;
        // Strutture
        db_set_active('getif_data');
        $query_branch = db_select('lperson', 't1');
        $results_branch = $query_branch
            ->fields('t1')
            ->condition('id_lperson_parent',$result->id_lperson,'=')
            ->condition('t1.active', 1)
            ->execute();
        db_set_active();
        $testo = '<ul>';
        foreach($results_branch as $branch) {
            $testo .= '<li>';
            if ($branch->id_lperson == $result->id_lperson)
                $branch->name = $branch->name.' - '.$branch->seat;
            $testo .= l($branch->name,'branch/edit/'.$branch->id_lperson);
            $testo .= '</li>';
        }
        $testo .= '</ul>';
        $rows[$key][] = $testo;
        $rows[$key][] =
        t('<a href="@url"><span class="btn glyphicon glyphicon-eye-open"></span>&nbsp;</a>', array(
            '@url' => url('lperson/edit/'.$result->id_lperson),
        )).t('<a href="@url"><span class="btn glyphicon glyphicon-pencil"></span>&nbsp;</a>', array(
            '@url' => url('lperson/edit/'.$result->id_lperson),
        )).
        drupal_render($form['remove_internship_'.$result->id_internship]);
    }
    // Top Buttons
    $form['actions']['back'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back'),
        '#attributes' => array(
        )
    );

    $form['filter_panel']['filter'] = array(
        '#type' => 'select',
        '#title' => '',
        '#empty_option' => t('- Tutti -'),
        '#options' => array(1=>'Promotore',2=>'Ospitante'),
        '#default_value' => $_GET['lprole'],
    );

    $form['filter_panel']['save'] = array(
        '#type' => 'submit',
        '#value' => 'Filtra',
        '#prefix' => '<div class="container-inline">',
        '#suffix' => '</div>',
    );
    if (!empty($_GET['lprole'])) {
        $form['filter_panel']['reset'] = array(
            '#type' => 'submit',
            '#value' => 'Reset',
            '#attributes' => array(
                'class' => array('glyphicon', 'glyphicon-erase'),
                'reset' => true
            ),
            '#prefix' => '<div class="container-inline">',
            '#suffix' => '</div>',
        );
    }
    $form['actions']['new'] = array(
        '#type' => 'button',
        '#value' => t('Nuovo').' '.t('Soggetto'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_new'),
    );
    $header = array(
        t('ID'),
        t('Ragione Sociale'),
        t('Ruoli'),
        t('Strutture'),
        t('Azioni')
    );
    $form['fs_lperson'] = array
    (
        '#type' => 'fieldset',
        '#title' => t('Lista Soggetti'),
        '#prefix' => '<div id="fs-agreement-div">',
        '#suffix' => '</div>',
    );
    $form['fs_lperson']['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('Table has no row!'),
        '#attributes' => array('id' => 'tabella'),
    );
    return $form;
}

/**
 * @param $id_lperson
 * @param $id_lprole
 * @param $testo
 */
function test($id_lperson, $id_lprole, &$testo) {
    $lperson = getRecordById('lperson', 'getif_data', $id_lperson, 'active');
    $lperson_lprole_description = getRecordById('lib_lprole', 'getif_data', $id_lprole, 'active')->description;
    $testo.= $lperson_lprole_description;
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_list_view_form_validate($form, &$form_state) {
    
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_list_view_form_submit($form, &$form_state) {
    $controller = $form_state['clicked_button']['#attributes']['controller'];
    if ($form_state['clicked_button']['#attributes']['reset']) {
        drupal_goto('lperson/list/', array());
    } else {
        drupal_goto('lperson/list/', array('query' => array('lprole' => $form_state['values']['filter'])));
    }
}

/**
 * @param $form
 * @param $form_state
 */
function goto_new($form, &$form_state) {
    getif_goto('lperson/new',array(),302,true);
}




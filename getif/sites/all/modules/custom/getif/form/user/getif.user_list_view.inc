<?php

/**
 * Theme lista utenti
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_user_list_view_form($variables) {
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_js(strtr('
            jQuery(document).ready(function() {
                var table = jQuery("#tabella").DataTable( {
                    pageLength: @pageLength,
                    scrollX: false,
                    orderCellsTop: true,
                    fixedHeader: true,
                    columnDefs: [
                        { orderable: false, targets: [4] },
                        { orderable: false, targets: [5] },
                        { responsivePriority: 1, targets: 0 },
                        { responsivePriority: 1, targets: 5 },
                        { responsivePriority: 1, targets: 4 }
                    ],
                    responsive: @responsive,
                    order: [[ 0, "DESC" ]],
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
        ',array('@responsive' => RESPONSIVE_FLG,'@pageLength' => TABLE_PAGELENGTH)),array('type'=>'inline','scope'=>'footer'));
    $form = $variables['form'];
    $header_content = array();
    $options = array();
    $options['show_fs_title'] = false;
    return getif_form_theme($form,$header_content,$options);
}


/**
 * Form lista convenzioni
 * @param $form
 * @param $form_state
 * @return mixed
 */
function user_list_view_form($form, &$form_state) {
    global $user, $base_url;
    $id_utente = arg(1);
    // Top Buttons
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('back_submit'),
    );
    $form['nav']['new'] = array(
        '#type' => 'button',
        '#value' => t('Nuovo').' '.t('Utente'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_new'),
    );

    $header = array(
        t('Utente'),
        t('Username'),
        t('Email'),
        t('Ruolo'),
        t('Status'),
        '&nbsp;',
    );


    db_set_active('getif_drupal');
    $query = db_query('
      SELECT u.uid, u.name, u.mail, GROUP_CONCAT(ur.rid) as roles FROM `users` as u 
      INNER JOIN users_roles AS ur ON ur.uid = u.uid 
      INNER JOIN role as r ON r.rid = ur.rid where u.status = 1 AND r.rid <> 3 GROUP BY u.uid
    ');
    db_set_active();

    while($result = $query->fetchObject()) {
        // Prende i dati anagrafici della persona associata all'utente

        db_set_active('getif_data');
        $query_person = db_select('profilo_utente','pu');
        $query_person -> innerJoin('person','pe','pe.id_person = pu.id_person');
        $query_person -> innerJoin('lib_title','lt','pe.id_title = lt.id_title');
        $query_person -> fields('pe');
        $query_person -> addField('lt','name','title');
        $query_person -> condition ('pu.uid',$result->uid);
        $query_person -> condition ('pu.active',1);
        $query_person -> condition ('pe.active',1);
        $person = (object)($query_person->execute()->fetchAssoc());
        db_set_active();
        $upd_url = url($base_url . "/guser/edit/" . $result->uid, array('query' => drupal_get_query_parameters()));
        $upd_btn = "<a href='" . $upd_url . "' class='btn btn-sm glyphicon glyphicon-pencil'></a>";
        $roles = array();
        $role_list = explode(',',$result->roles);
        foreach ($role_list as $role) {
            $roles[] = user_role_load($role)->name;
        }
        $account = user_load($result->uid);
        $rows[] = array(
            'data' => array(
                ucwords($person->title.' '.$person->firstname.' '.$person->lastname),
                $result->name,
                $result->mail,
                join($roles,', '),
                $account->status?'<span class="circle_step green" style="font-size: 1.0em;">&nbsp;</span>':'<span class="circle_step" style="font-size: 1.0em;"></span>',
                $upd_btn
            ),
            'class' => ($result->uid === $id_utente) ? array('success') : null,
        );
    }

    $form['fs_user'] = array(
        '#type' => 'item',
        '#title' => t('Lista utenti'),
        '#prefix' => '<div id="fs-user-div">',
        '#suffix' => '</div>',
        '#title_display' => 'invisible',
        '#access' =>true
    );

    $form['fs_user']['table'] = array(
        '#theme' => 'table',
        "#header" => $header,
        "#rows" => $rows,
        "#empty" => t("Table has no row!"),
        '#attributes' => array(
            'id'=>'tabella',
            'class' => array('table', 'table-striped', 'table-hover')
        ),
    );
    return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function back_submit($form, &$form_state) {
    $back_url = '/';
    getif_goto($back_url,array(),302,false);
}

/**
 * @param $form
 * @param $form_state
 */
function goto_new($form, &$form_state) {
    getif_goto('guser/new',array(),302,true);
}

/* end */
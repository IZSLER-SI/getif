<?php

/**
 * Theme lista convenzioni
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_agreement_list_view_form($variables) {
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    drupal_add_js(strtr('
            jQuery(document).ready(function() {
                var table = jQuery("#tabella").DataTable( {
                    pageLength: @pageLength,
                    scrollX: false,
                    orderCellsTop: true,
                    fixedHeader: true,
                    columnDefs: [
                        { orderable: false, targets: [8] },
                        { type: "date-eu", targets: [4] },
                        { type: "date-eu", targets: [5] },
                        { responsivePriority: 1, targets: 0 },
                        { responsivePriority: 1, targets: 6 },
                        { responsivePriority: 1, targets: 7 },
                        { responsivePriority: 1, targets: 8 }
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
    return getif_form_theme($form,'',false,false);
}


/**
 * Form lista convenzioni
 * @param $form
 * @param $form_state
 * @return mixed
 */
function agreement_list_view_form($form, &$form_state) {
    // Top Buttons
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('back_submit'),
    );
    $form['nav']['new'] = array(
        '#type' => 'button',
        '#value' => t('Nuova').' '.t('Convenzione'),
        '#limit_validation_errors' => array(),
        '#validate' => array('goto_new'),
    );

    session_set('prev',drupal_get_destination()["destination"]);
    $header = array(
        t('ID'),
        t('S. Promotore'),
        t('S. Ospitante'),
        t('N. IZSLER'),
        t('Data Inizio'),
        t('Data Fine'),
        t('N. Tir.'),
        t('Stato'),
        t('Azioni')
    );
    db_set_active('getif_data');
    $query = db_select('agreement', 't1');
    $query->addField('t3','name','host_name');
    $query->addField('t3','tax_code','host_tax_code');
    $query->addField('t5','tax_code','promoter_tax_code');
    $query->addField('t5','name','promoter_name');
    $query->leftJoin('lperson_lprole', 't2', 't1.id_host = t2.id_lperson_lprole');
    $query->leftJoin('lperson', 't3', 't2.id_lperson = t3.id_lperson');
    $query->leftJoin('lperson_lprole', 't4', 't1.id_promoter = t4.id_lperson_lprole');
    $query->leftJoin('lperson', 't5', 't4.id_lperson = t5.id_lperson');
    $query->condition('t1.active',1);
    $query->condition('t2.active', 1);
    $query->condition('t3.active', 1);
    $query->condition('t4.active', 1);
    $query->condition('t5.active', 1);
    $results = $query
    ->fields('t1', array('id_agreement','number_code','date_start','date_end','date_application','internship_type'))
        ->orderBy('t1.id_agreement','DESC')
    ->execute()->fetchAll();
    db_set_active();
    $rows = array();
    foreach($results as $result) {
        $n_internships = count(getAllRecordByField('internship_agreement','getif_data','id_agreement',$result->id_agreement));
        $form['remove_agreement_'.$result->id_agreement]  = array (
            '#type' => 'submit',
            '#name' => 'remove_agreement_'.$result->id_agreement,
            '#value' => '',
            '#submit' => array('remove_agreement_submit'),
            '#id' => 'edit-remove-agreement-'.$result->id_agreement,
            '#attributes' => array(
                'id_agreement' => $result->id_agreement,
                'class' => array('btn','glyphicon','glyphicon-trash'),
                'onclick' => 'if(!confirm("Sei sicuro di voler eliminare la Convenzione?")){return false;}'
            ),
        );
        // Una convenzione con tirocini non può essere eliminata
        if ($n_internships > 0) {
            $form['remove_agreement_'.$result->id_agreement]['#attributes']['class'][] = 'disabled';
            $form['remove_agreement_'.$result->id_agreement] = array(
                '#markup' => '<div class="btn glyphicon glyphicon-trash"></div>',
                '#access' => false,
                '#attributes' => array(
                    'class' => array('btn','btn-disabled','disabled','glyphicon','glyphicon-trash'),
                )
            );
        }
        $form['remove_agreement_'.$result->id_agreement] = ajax_pre_render_element($form['remove_agreement_'.$result->id_agreement]);

        $rows[$result->id_agreement] = array(
            l($result->id_agreement,'/agreement/edit/'.$result->id_agreement),
            '<span>'.$result->host_name.'<br/>'.$result->host_tax_code.'</span>',
            '<span>'.$result->promoter_name.'<br/>'.((strlen($result->promoter_tax_code) != 36)?$result->promoter_tax_code:'').'</span>',
            $result->number_code,
            format_date(strtotime($result->date_start),'custom','d-m-Y',date_default_timezone()),
            format_date(strtotime($result->date_end),'custom','d-m-Y',date_default_timezone())
        );
        if (new DateTime() > new DateTime($result->date_end)) {
            $state = '<div class="btn-danger" style="padding:3px 7px">Scaduta</div>';
        } else {
            $state = '<div class="btn-success" style="padding:3px 7px">In corso</div>';
        }
        array_push($rows[$result->id_agreement],$n_internships);
        array_push($rows[$result->id_agreement],$state);
        array_push($rows[$result->id_agreement],t('<a href="@url"><span class="btn glyphicon glyphicon-pencil"></span>&nbsp;</a>', array(
                '@url' => url('agreement/edit/'.$result->id_agreement),
            ))
            .drupal_render($form['remove_agreement_'.$result->id_agreement]));
        
    }
    $form['fs_agreement'] = array
    (
        '#type' => 'item',
        '#title' => t('Lista Convenzioni'),
        '#prefix' => '<div id="fs-agreement-div">',
        '#suffix' => '</div>',
        '#title_display' => 'invisible',
        '#access' =>true
    );
    $form['fs_agreement']['table'] = array
    (
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('Table has no row!'),
        '#attributes' => array(
            'id' => 'tabella'
        )
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
function lista_tirocinanti_form_validate($form, &$form_state) {
    // empty
}

/**
 * @param $form
 * @param $form_state
 */
function lista_tirocinanti_form_submit($form, &$form_state) {
   // empty
}

/**
 * @param $form
 * @param $form_state
 */
function remove_agreement_submit($form, &$form_state)
{

    $id_agreement = $form_state['clicked_button']['#attributes']['id_agreement'];
    $fields = array(
        'active' => 0
    );
    $where = 'id_agreement = ' . $id_agreement;
    try {
        // Elimina la convenzione
        db_set_active('getif_data');
        $query = db_update('agreement');
        $query->fields($fields)->where($where)->execute();
        db_set_active();
        $w_type = 'getif_agreement';
        $w_message = t('Delete item %id');
        $w_variables = array('%id'=>$id_agreement);
        watchdog($w_type, $w_message, $w_variables);
        drupal_set_message(t("Convenzione eliminata con successo"));
    } catch (Exception $ex) {
        drupal_set_message('Errore: ' . $ex, 'error');
    }
}

/**
 * @param $form
 * @param $form_state
 */
function goto_new($form, &$form_state) {
    getif_goto('agreement/new',array(),302,true);
}

/* end */
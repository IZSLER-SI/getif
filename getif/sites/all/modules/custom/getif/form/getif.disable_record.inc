<?php

/**
 * @param $variables
 * @return string
 * @throws Exception
 */
function theme_disable_record_form($variables)
{
    $module_path = drupal_get_path('module', 'getif');
    $full_path = $module_path .'/css/getif.css';
    drupal_add_css($full_path);
    $form = $variables['form'];
    $output = "";

    $row = array();

    $row[] = array(
        'data' => array(
            array('data'=>'<h2>Sei sicuro di voler disabilitare il record?</h2>', 'colspan'=>'2'),
        ),
    );
    $row[] = array(
        'data' => array(
            array('data'=>drupal_render($form['no']), 'colspan'=>'1'),
            array('data'=>drupal_render($form['submit']), 'colspan'=>'1'),
        ),
    );
    $output .= theme('table', array(
        'rows' => $row,
        'attributes' => array('class'=>"tabellaDisableRecord")
    ));
    $output .= drupal_render_children($form);
    return $output;
}

/**
 * hook form eliminazione record
 * @param $form
 * @param $form_state
 */
function delete_record_form($form, &$form_state){
    $page = arg(1);
    $id = arg(2);
    $form = array();
    $form['page'] = array(
        '#type' => 'hidden',
        '#value' => $page,
    );
    $form['id'] = array(
        '#type' => 'hidden',
        '#value' => $id,
    );
    $form['no'] = array(
        '#type' => 'submit',
        '#value' => t('No'),
        '#attributes' => array(
            'onClick' => 'window.history.go(-1)',
        ),
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Si'),
    );
    return $form;
}

/**
 * hook validate eliminazione record: non faccio niente
 * @param $form
 * @param $form_state
 */
function delete_record_form_validate($form, &$form_state){
    // empty
}


/**
 * hook form submit eliminazione record
 * @param $form
 * @param $form_state
 */
function delete_record_form_submit($form, &$form_state) {
    global $base_url;
    $page = $form_state['input']['page'];
    $id = $form_state['input']['id'];
    switch ($page) {
        case 'utenti':
            $table = 'users';
            $id_column = 'uid';
            $goto = 'utenti';
            $array_dati = array('status' => 0);
            break;
        default:
            form_set_error('', t('Unrecognized table'));
            return;
    }
    if ($form_state['clicked_button']['#value']!="No" and $form_state['clicked_button']['#value']!="no" and $form_state['clicked_button']['#value']!="NO") {
        if ($table == "users") {
            // aggiorno la tabella users
            db_set_active();
            db_update($table)
                ->fields($array_dati)
                ->condition($id_column, $id, '=')
                ->execute();

            $log = $array_dati;
            $log['table_key'] = $id;
            watchdog('query_update', $table, $log);
            db_set_active();

            $fields = array(
                'date_upd' => date("Y-m-d H:i:s", time()),
                'active' => 2
            );
            db_set_active('getif_data');
            db_update('profilo_utente')
                ->fields($fields)
                ->condition($id_column, $id, '=')
                ->execute();
            db_set_active();
            drupal_set_message(t("Elemento rimosso con successo"));
        }
    }
    // Ritorno alla pagina richiesta
    drupal_goto(url($base_url . '/' . $goto, array('query' => drupal_get_query_parameters())));
}

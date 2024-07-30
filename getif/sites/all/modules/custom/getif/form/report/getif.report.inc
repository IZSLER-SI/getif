<?php

/**
 * theme report
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_report_form($variables){
    drupal_add_js(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.js');
    drupal_add_css(drupal_get_path('module', 'getif') . '/DataTables/datatables.min.css');
    $form = $variables['form'];
    return getif_form_theme($form);
}


/**
 * form report
 * @param $form
 * @param $form_state
 * @return mixed
 */
function report_form($form, &$form_state) {
    // Top Buttons
    $form['nav']['back'] = array(
        '#type' => 'button',
        '#value' => t('Dashboard'),
        '#limit_validation_errors' => array(),
        '#validate' => array('go_back'),
    );
    $html = '
    <p>'.
        l(t('Tirocini attivati per convenzione collettiva'),
            'report/tirocini-convenzione',
            array(
                'query'=>array(
                    'state'=>4,
                    'hide'=> GETIF_REPORT_TIROCINI_CONVENZIONE_COLONNE
                ),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
        l(t('Tirocini per corso frequentato per struttura di attivazione'),
            'report/corso_frequentato/0',
            array(
                'query'=>array(),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
        l(t('Frequenze volontarie per corso frequentato per struttura di attivazione'),
            'report/corso_frequentato/1',
            array(
                'query'=>array(),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
        l(t('Tirocini per titolo di studio per struttura di attivazione'),
            'report/titolo_studio/0',
            array(
                'query'=>array(),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
        l(t('Frequenze volontarie per titolo di studio per struttura di attivazione'),
            'report/titolo_studio/1',
            array(
                'query'=>array(),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
        l(t('Elenco dei laureati che svolgono tirocini'),
            'report/elenco_laureati',
            array(
                'query'=>array(
                    'state'=>'all',
                    'hide'=>'2-3-4-5-6-7-8-10-11-14-15-16-17-18-19-20-21-22-23-24-0-0-0-0-0'
                ),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
        l(t('Elenco di tutti i tirocini'),
            'report/elenco_tirocini',
            array(
                'query'=>array(
                    'state'=>'all',
                    'hide'=>'2-3-4-5-6-7-8-10-11-14-15-16-17-18-19-20-21-22-23-24-0-0-0-0-0'
                ),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
        l(t('Elenco di tutte le frequenze volontarie'),
            'report/elenco_frequenze',
            array(
                'query'=>array(
                    'state'=>'all',
                    'hide'=>'2-3-4-5-6-8-9-10-11-12-13-14-15-16-17-18-19-0-0-0'
                ),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
        l(t('Presenze in orario di servizio'),
            'report/presenze_servizio',
            array(
                'query'=>array(),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
        l(t('Report delle ore complessive di attività di ogni Tirocinio associato ad un tutor'),
            'report/ore_tutor/0',
            array(
                'query'=>array(),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
        l(t('Report per attestazione delle ore di attività di un tutor'),
            'report/ore_tutor/1',
            array(
                'query'=>array(),
                'attributes' => array('class' => array(
                    'list-group-item')
                )
            )
        ).
    '</p >';
    $form['fs_table_panel'] = array(
        '#type' => 'item',
        '#title' => 'Report tirocinio',
        '#title_display' => 'invisible',
        '#access' => true
    );
    $form['fs_table_panel']['markup'] = array(
        '#markup' => $html
    );
    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function report_form_validate($form, &$form_state) {
    //empty
}

/**
 * @param $form
 * @param $form_state
 */
function report_form_submit($form, &$form_state)
{
    if (!empty($form_state['clicked_button']['#attributes']['reset'])) {
        drupal_goto(current_path(), array());
    } else {
        $query = array();
        if (in_array($form_state['values']['filter'],array(0,5,6,7))) {
            $query['state'] = $form_state['values']['filter'];
        }
        if (!empty($form_state['values']['date_start']) && !empty($form_state['values']['date_end'])) {
            $query['from'] = $form_state['values']['date_start'];
            $query['to'] = $form_state['values']['date_end'];
        }
        if (!empty($form_state['values']['test'])) {
            $query['hide'] = join($form_state['values']['test'],'-');
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

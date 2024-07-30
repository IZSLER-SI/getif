<?php

/**
 * Theme lperson_branch
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_lperson_host_branch_form($variables){
    $form = $variables['form'];
    if (arg(2) == 'new') {
        $options['page_title'] = 'Nuova Struttura di '.$form['fs_branch']['#description'];
        return getif_form_theme($form,null,$options);
    } elseif (arg(2) == 'edit') {
        $output = '';
        $output .= '<div class="panel panel-default">';
        $output .= '
        <ul class="nav nav-tabs" style = "background-color: #f5f5f5;">';
        $output .= '
            <li class="' . (!isset($_GET['new_person']) && !isset($_GET['new_lab']) ? "active" : "") . '">
                <a href="#panel1" data-toggle="tab">' . $form['fs_branch']['#title'] . '</a></li>';
        if (!empty($form['fs_lperson_location_area']['#access'])) {
            $output .= '
            <li class="' . (isset($_GET['new_lab']) ? "active" : "") . '"><a href="#panel2" data-toggle="tab">' . $form['fs_lperson_location_area']['#title'] . '</a></li>';
        }
        if (!empty($form['fs_person']['#access'])) {
            $output .= '
            <li class="' . (isset($_GET['new_person']) ? "active" : "") . '"><a href="#panel3" data-toggle="tab">' . $form['fs_person']['#title'] . '</a></li>';
        }
        $output .= '
        </ul>
        <div class="tab-content">
            <div id="panel1" class="tab-pane ' . (!isset($_GET['new_person']) && !isset($_GET['new_lab']) ? "active" : "") . ' panel-body ">
               ' . drupal_render($form['fs_branch']) . '<hr/><div style="text-align:right">' . drupal_render($form['actions']) . '</div>
            </div>';

        if (!empty($form['fs_lperson_location_area']['#access'])) {
            $output .= '
            <div id="panel2" class="tab-pane ' . (isset($_GET['new_lab']) ? "active" : "") . ' panel-body">
               ' . drupal_render($form['fs_lperson_location_area']) . '
            </div>';
        }
        if (!empty($form['fs_person']['#access'])) {
            $output .= '
            <div id="panel3" class="tab-pane ' . (isset($_GET['new_person']) ? "active" : "") . ' panel-body>
               ' . drupal_render($form['fs_person']) . '
            </div>
           ';
        }
        $output .= '</div>';
        $header_content[]['html'] = $output;
        $options['page_title'] = $form['fs_branch']['#description'];
        return getif_form_theme($form, $header_content,$options);
    }
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function lperson_host_branch_form($form, &$form_state) {
    $controller = $form_state["build_info"]["args"]["0"];
    if ($controller == 'new') {
        $id_lperson_parent = !empty($form_state["build_info"]["args"]["1"])?$form_state["build_info"]["args"]["1"]:null;
        if(!$id_lperson_parent) {
            drupal_goto();
        }
        $lperson_parent = getLPersonById('getif_data',$id_lperson_parent);
        $fs_branch_description = _strformat($lperson_parent->name);
    } elseif ($controller == "edit"){
        $id_lperson = !empty($form_state["build_info"]["args"]["1"])?$form_state["build_info"]["args"]["1"]:null;
        if(!$id_lperson) {
            drupal_goto();
        }
        $lperson = getRecordById('lperson','getif_data', $id_lperson, 'active');
        $lperson_parent = getLPersonById('getif_data',$lperson->id_lperson_parent);
        $id_lperson_parent = $lperson_parent -> id_lperson;
        $fs_branch_title = t('Dati anagrafici');
        if ($lperson_parent->name == $lperson->name) {
            $fs_branch_description = 'Modifica Sede Legale di '._strformat($lperson_parent->name);
        } else {
            $fs_branch_description = 'Modifica Struttura di ' . _strformat($lperson_parent->name) . ': ' . $lperson->name;
        }
    } else {
        drupal_goto();
    }
    $required = true;
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
    $form['fs_branch'] = array(
        '#type' => 'item',
        '#title' => !empty($fs_branch_title)?$fs_branch_title:'',
        '#description' => !empty($fs_branch_description)?$fs_branch_description:'',
        '#prefix' => '<div id="fs-branch-div">',
        '#suffix' => '</div>',
        '#title_display' => 'invisible'
    );
    $form['fs_branch']['branch_container'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="branch-ajax-wrapper">',
        '#suffix' => '</div>',
    );

    /* Nome della Struttura */
    $form['fs_branch']['branch_container']['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Denominazione Struttura'),
        '#description' => t('Inserire la denominazione della struttura'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required
    );
    /* Sede della Struttura */
    $form['fs_branch']['branch_container']['seat'] = array(
        '#type' => 'textfield',
        '#title' => t('Sede della struttura'),
        '#description' => t('Inserire la sede della struttura'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required
    );
    /* Identificativo Fiscale della Struttura */
    $form['fs_branch']['branch_container']['tax_code'] = array(
        '#type' => 'textfield',
        '#title' => t("Numero Identificativo"),
        '#description' => t('Inserire il numero identificativo di struttura'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#required' => $required
    );

    /* Numero di dipendenti */
    $form['fs_branch']['branch_container']['num_employers'] = array(
        '#type' => 'textfield',
        '#title' => t('Numero di dipendenti'),
        '#description' => t('Inserire il numero di dipendenti struttura'),
        '#attributes' => array(
            'check_for_draft_save'=> 'no',
            ' type' => 'number', // insert space before attribute name :)
        ),
        '#required' => $required
    );
    /* Indirizzo delle Struttura */
    $form['fs_branch']['branch_container']['address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo"),
        '#description' => t('Inserire l\'indirizzo della struttura'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );
    /* Email di rif. della Struttura */
    $form['fs_branch']['branch_container']['email_address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo Email"),
        '#description' => t('Inserire l\'indirizzo email della struttura'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#default_value' => "",
        '#size' => 40,
        '#maxlength' => 40,
        '#element_validate' => array('getif_email_element_validate')
    );
    /* PEC di rif. della Struttura */
    $form['fs_branch']['branch_container']['certified_email_address'] = array(
        '#type' => 'textfield',
        '#title' => t("Indirizzo di Posta Elettronica Certificata (PEC)"),
        '#description' => t('Inserire l\'indirizzo di Posta Elettronica Certificata (PEC) della struttura'),
        '#default_value' => "",
        '#size' => 40,
        '#maxlength' => 40,
        '#element_validate' => array('getif_email_element_validate'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );

    /* Telefono di rif. della Struttura */
    $form['fs_branch']['branch_container']['phone'] = array(
        '#type' => 'textfield',
        '#title' => t("Numero di telefono"),
        '#description' => t('Inserire il numero di telefono della struttura'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
        '#size' => 20,
        '#maxlength' => 20,
        '#element_validate' => array('getif_phone_element_validate')
    );
    /* Fax dello Struttura */
    $form['fs_branch']['branch_container']['fax'] = array(
        '#type' => 'textfield',
        '#title' => t("Numero di fax"),
        '#description' => t('Inserire il numero di fax della struttura'),
        '#required' => false,
        '#size' => 20,
        '#maxlength' => 20,
        '#element_validate' => array('getif_phone_element_validate'),
        '#attributes' => array(
            'check_for_draft_save' => 'no',
            'autocomplete' => 'off'
        ),
    );

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Salva')
    );

    if ($controller == 'edit') {
        // Laboratori
        $form['fs_lperson_location_area'] = array(
            '#type' => 'item',
            '#title' => t('Laboratori'),
            '#prefix' => '<div id="fs-lperson-location-area-div">',
            '#suffix' => '</div>',
            '#title_display' => 'invisible',
            '#access' =>true
        );
        $form['fs_lperson_location_area']['lperson_location_area_container'] = array(
            '#type' => 'container',
            '#weight' => 80,
            '#tree' => TRUE,
            '#prefix' => '<div id="lperson-location-area-wrapper">',
            '#suffix' => '</div>',
            '#weight' => 0,
        );
        db_set_active('getif_data');
        $query = db_select('lperson','t1');
        $query->condition('id_lperson_parent',$id_lperson);
        $query->condition('level',2);
        $query->condition('active',array(1,2),'IN');
        $query->fields('t1');
        $lperson_location_areas = $query->execute()->fetchAll();
        db_set_active();

        $rows = array();
        foreach ($lperson_location_areas as $lperson_location_area) {
            $rows[$lperson_location_area->id_lperson] = array(
                $lperson_location_area->name
            );
            $form['edit_lperson_location_area_'.$lperson_location_area->id_lperson]  = array (
                '#type' => 'submit',
                '#name' => 'edit_lperson_location_area_'.$lperson_location_area->id_lperson,
                '#value' => '',
                '#submit' => array('edit_lperson_location_area_submit'),
                '#id' => 'edit-edit-lperson-location-area-'.$lperson_location_area->id_lperson,
                '#attributes' => array(
                    'class' => array('btn','glyphicon','glyphicon-pencil'),
                    'id_lperson_location_area' => $lperson_location_area->id_lperson
                ),
                '#limit_validation_errors' => array(array('lperson_location_area_container','table'))
            );
            // Button disable person_lperson
            $form['disable_lperson_location_area_'.$lperson_location_area->id_lperson]  = array (
                '#type' => 'submit',
                '#name' => 'disable_lperson_location_area_'.$lperson_location_area->id_lperson,
                '#value' => '',
                '#submit' => array('disable_lperson_location_area_submit'),
                '#id' => 'edit-disable-lperson-location-area-'.$lperson_location_area->id_lperson,
                '#ajax' => array(
                    'callback' => 'add_lperson_location_area_callback',
                    'wrapper' => 'lperson-location-area-wrapper',
                ),
                '#attributes' => array(
                    'id_lperson_location_area' => $lperson_location_area->id_lperson,
                    'class' => array('btn','btn-disable'),
                    'data-toggle'=> 'toggle',
                    'button_checked' => $lperson_location_area->active==1?true:false
                ),
                '#limit_validation_errors' => array(array('lperson_location_area_container','table'))
            );
            $form['disable_lperson_location_area_'.$lperson_location_area->id_lperson] = ajax_pre_render_element($form['disable_lperson_location_area_'.$lperson_location_area->id_lperson]);

            $form['remove_lperson_location_area_'.$lperson_location_area->id_lperson]  = array (
                '#type' => 'submit',
                '#name' => 'remove_lperson_location_area_'.$lperson_location_area->id_lperson,
                '#value' => '',
                '#submit' => array('remove_lperson_location_area_submit'),
                '#id' => 'edit-remove-lperson-location-area-'.$lperson_location_area->id_lperson,
                '#ajax' => array(
                    'callback' => 'add_lperson_location_area_callback',
                    'wrapper' => 'lperson-location-area-wrapper',
                ),
                '#attributes' => array(
                    'class' => array('btn','glyphicon','glyphicon-trash'),
                    'id_lperson_location_area' => $lperson_location_area->id_lperson
                ),
                '#limit_validation_errors' => array(array('lperson_location_area_container','table'))
            );
            $form['remove_lperson_location_area_'.$lperson_location_area->id_lperson] = ajax_pre_render_element($form['remove_lperson_location_area_'.$lperson_location_area->id_lperson]);

            $rows[$lperson_location_area->id_lperson] = array(
                $lperson_location_area->name,
                $lperson_location_area->email_address,
                $lperson_location_area->phone
            );

            db_set_active('getif_data');
            $query = db_select('internship_lperson_location_area','t1');
            $query -> condition('t1.id_lperson_location_area',$lperson_location_area->id_lperson);
            $query -> condition('t1.active',1);
            $query -> innerJoin('internship_state','t2','t1.id_internship = t2.id_internship');
            $query -> condition('t2.state',array(1,2,3,4,5,6),'IN');
            $query -> condition('t2.active',1);
            $result = intval($query -> countQuery() -> execute() -> fetchField());
            db_set_active();

            if($lperson_location_area->active == 1 && $result == 0) { // se lperson è attiva ma non è associata a tirocini attivi o in stato di pratica
                // funzioni permesse: edit/disable
                // enable/disable
                array_push($rows[$lperson_location_area->id_lperson],drupal_render($form['disable_lperson_location_area_' . $lperson_location_area->id_lperson]));
                // edit - remove
                // Button remove
                $form['remove_lperson_location_area_'.$lperson_location_area->id_lperson]  = array (
                    '#type' => 'button',
                    '#value' => '',
                    '#attributes' => array(
                        'class' => array('btn','glyphicon','glyphicon-trash'),
                        'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false;',
                        'disabled' => ''
                    ),
                );
                array_push($rows[$lperson_location_area->id_lperson],
                    drupal_render($form['edit_lperson_location_area_' . $lperson_location_area->id_lperson]).
                    drupal_render($form['remove_lperson_location_area_' . $lperson_location_area->id_lperson]));
            } elseif($lperson_location_area->active == 1 && $result > 0) { // se lperson è attiva ma è associata a tirocini attivi o in stato di pratica


                // funzioni permesse: edit
                // enable/disable
                $form['disable_lperson_location_area_'.$lperson_location_area->id_lperson]  = array (
                    '#type' => 'button',
                    '#value' => '',
                    '#attributes' => array(
                        'class' => array('btn','glyphicon','glyphicon-trash'),
                        'data-toggle'=> 'toggle',
                        'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false',
                        'button_checked' => $lperson_location_area->active==1?true:false
                    ),
                );
                array_push($rows[$lperson_location_area->id_lperson],drupal_render($form['disable_lperson_location_area_' . $lperson_location_area->id_lperson]));
                // edit - remove
                // Button remove
                $form['remove_lperson_location_area_'.$lperson_location_area->id_lperson]  = array (
                    '#type' => 'button',
                    '#value' => '',
                    '#attributes' => array(
                        'class' => array('btn','glyphicon','glyphicon-trash'),
                        'onclick' => 'alert("'.t('Non è possibile eliminare questo elemento.').'");return false;',
                        'disabled' => ''
                    ),
                );
                array_push($rows[$lperson_location_area->id_lperson],
                    drupal_render($form['edit_lperson_location_area_' . $lperson_location_area->id_lperson]).
                    drupal_render($form['remove_lperson_location_area_' . $lperson_location_area->id_lperson]));

            } elseif($lperson_location_area->active == 2) { // se lperson è disabilita
                $form['disable_lperson_location_area_'.$lperson_location_area->id_lperson]['#attributes']['class'] = array('btn','btn-enable');
                $form['disable_lperson_location_area_'.$lperson_location_area->id_lperson]['#submit'] = array('enable_lperson_location_area_submit');
                $form['edit_lperson_location_area_'.$lperson_location_area->id_lperson]  = array (
                    '#type' => 'button',
                    '#value' => '',
                    '#attributes' => array(
                        'class' => array('btn','glyphicon','glyphicon-pencil'),
                        'onclick' => 'alert("'.t('Non è possibile modificare questo elemento.').'");return false',
                        'disabled' => ''
                    ),
                );
                array_push($rows[$lperson_location_area->id_lperson],drupal_render($form['disable_lperson_location_area_' . $lperson_location_area->id_lperson]));
                db_set_active('getif_data');
                $query = db_select('internship_lperson','t1');
                $query -> condition('t1.id_internship_lperson',$lperson_location_area->id_lperson);
                $result = intval($query -> countQuery() -> execute() -> fetchField());
                db_set_active();

                if ($result != 0) { // se non ha uno storico di tirocini associati
                    // funzioni permesse: enable
                    // funzioni permesse: enable
                    // Button remove person_person
                    $form['remove_lperson_location_area_' . $lperson_location_area->id_lperson] = array(
                        '#type' => 'button',
                        '#value' => '',
                        '#attributes' => array(
                            'class' => array('btn', 'glyphicon', 'glyphicon-trash'),
                            'onclick' => 'alert("' . t('Non è possibile eliminare questo elemento.') . '");return false;',
                            'disabled' => ''
                        ),
                    );

                }
                array_push($rows[$lperson_location_area->id_lperson],
                    drupal_render($form['edit_lperson_location_area_' . $lperson_location_area->id_lperson]).
                    drupal_render($form['remove_lperson_location_area_' . $lperson_location_area->id_lperson]));
            }
        }
        $header = array(t('Nome'),t('Indirizzo email'),t('Telefono'),t('Attiva'),'Azioni');
        $form['fs_lperson_location_area']['lperson_location_area_container']['table'] = array
        (
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $rows,
            '#empty' => t('Table has no row!'),
            '#suffix' => '
                <script>
                    jQuery(\'button[type=submit][data-toggle^=toggle]\').bootstrapToggle(); 
                </script>'
        );
        unset($rows);
        unset($header);

        $form['fs_lperson_location_area']['add_lperson_location_area']  = array (
            '#type' => 'submit',
            '#value' => 'Aggiungi Laboratorio',
            '#submit' => array('add_lperson_location_area_submit'),
            '#attributes' => array(
                'id_lperson' => $id_lperson,
            ),
        );

        // Fieldset Figure
        $form['fs_person'] = array(
            '#type' => 'item',
            '#title' => t('Figure'),
            '#prefix' => '<div id="fs-person-div">',
            '#suffix' => '</div>',
            '#title_display' => 'invisible',
            '#access' =>true
        );
        $form['fs_person']['persons_container'] = array(
            '#type' => 'container',
            '#weight' => 80,
            '#tree' => TRUE,
            '#prefix' => '<div id="js-ajax-branch-persons-wrapper">',
            '#suffix' => '</div>',
            '#weight' => 0,
        );

        $persons = getAllPersonsByLPId('getif_data',$id_lperson);
        $rows = array();
        foreach ($persons as $person) {
            $positions = getPersonLPersonPositions($person->id_person_lperson);
            // get Position
            $person->positions = '<ul>';
            foreach ($positions AS $position) {
                // Pulsante per rimuovere il ruolo
                $form['remove_position_'.$position->id_person_lperson_position]  = array (
                    '#type' => 'submit',
                    '#name' => 'remove_position_'.$position->id_person_lperson_position,
                    '#value' => '',
                    '#submit' => array('remove_position_submit'),
                    '#id' => 'edit-remove-position-'.$position->id_person_lperson_position,
                    '#attributes' => array(
                        'id' => 'edit-remove-position-'.$position->id_person_lperson_position,
                        'id_person_lperson_position' => $position->id_person_lperson_position,
                        'class' => array('btn','btn-remove','glyphicon','glyphicon-trash'),
                    ),
                    '#ajax' => array(
                        'callback' => 'add_position_callback',
                        'wrapper' => 'js-ajax-branch-persons-wrapper',
                    )
                );
                $form['remove_position_'.$position->id_person_lperson_position] = ajax_pre_render_element($form['remove_position_'.$position->id_person_lperson_position]);

                $person->positions .= '<li>'.drupal_render($form['remove_position_'.$position->id_person_lperson_position]).' '.'<div class ="el'.$position->id_position.'"><span>'.$position->description.'</span></div></li>';
            }
            // Add position
            $form['position_'.$person->id_person_lperson]  = array (
                '#type' => 'select',
                '#name' => 'position_'.$person->id_person_lperson,
                '#options' => getAllowedPositionByLPId('getif_data',$id_lperson),
                '#attributes' => array(
                    'id' => 'edit-position-'.$person->id_person_lperson,
                )
            );
            // Button Add position
            $form['add_position_'.$person->id_person_lperson]  = array (
                '#type' => 'submit',
                '#name' => 'add_position_'.$person->id_person_lperson,
                '#value' => 'Aggiungi posizione',
                '#submit' => array('add_position_submit'),
                '#id' => 'edit-add-position-'.$person->id_person_lperson,
                '#attributes' => array(
                    'id' => 'edit-add-position-'.$person->id_person_lperson,
                    'id_person_lperson' => $person->id_person_lperson,
                ),
                '#ajax' => array(
                    'callback' => 'add_position_callback',
                    'wrapper' => 'js-ajax-branch-persons-wrapper',
                )
            );
            $form['add_position_'.$person->id_person_lperson] = ajax_pre_render_element($form['add_position_'.$person->id_person_lperson]);
            $person->positions .= '</ul>'. drupal_render($form['position_'.$person->id_person_lperson]) . drupal_render($form['add_position_'.$person->id_person_lperson]);
            $proles = getPersonLPersonProles($person->id_person_lperson);
            // get Roles
            $person->proles = '<ul>';
            foreach ($proles AS $prole) {
                // Pulsante per rimuovere il ruolo
                $form['remove_prole_'.$prole->id_person_lperson_prole]  = array (
                    '#type' => 'submit',
                    '#name' => 'remove_prole_'.$prole->id_person_lperson_prole,
                    '#value' => '',
                    '#submit' => array('remove_prole_submit'),
                    '#id' => 'edit-remove-prole-'.$prole->id_person_lperson_prole,
                    '#attributes' => array(
                        'id' => 'edit-remove-prole-'.$prole->id_person_lperson_prole,
                        'id_person_lperson_prole' => $prole->id_person_lperson_prole,
                        'class' => array('btn','btn-remove','glyphicon','glyphicon-trash'),
                    ),
                    '#ajax' => array(
                        'callback' => 'add_prole_callback',
                        'wrapper' => 'js-ajax-branch-persons-wrapper',
                    )
                );
                $form['remove_prole_'.$prole->id_person_lperson_prole] = ajax_pre_render_element($form['remove_prole_'.$prole->id_person_lperson_prole]);

                $person->proles .= '<li>'.drupal_render($form['remove_prole_'.$prole->id_person_lperson_prole]).' '.'<span class ="el'.$prole->id_prole.'">'.$prole->description.'</span></li>';
            }
            // Add role
            $form['prole_'.$person->id_person_lperson]  = array (
                '#type' => 'select',
                '#name' => 'prole_'.$person->id_person_lperson,
                '#options' => getAllowedProleByLPId('getif_data',$id_lperson),
                '#attributes' => array(
                    'id' => 'edit-prole-'.$person->id_person_lperson,
                )
            );
            // Button Add prole
            $form['add_prole_'.$person->id_person_lperson]  = array (
                '#type' => 'submit',
                '#name' => 'add_prole_'.$person->id_person_lperson,
                '#value' => 'Aggiungi ruolo',
                '#submit' => array('add_prole_submit'),
                '#id' => 'edit-add-prole-'.$person->id_person_lperson,
                '#attributes' => array(
                    'id' => 'edit-add-prole-'.$person->id_person_lperson,
                    'id_person_lperson' => $person->id_person_lperson,
                ),
                '#ajax' => array(
                    'callback' => 'add_prole_callback',
                    'wrapper' => 'js-ajax-branch-persons-wrapper',
                )
            );
            $form['add_prole_'.$person->id_person_lperson] = ajax_pre_render_element($form['add_prole_'.$person->id_person_lperson]);
            // Button remove person_lperson
            $form['remove_person_'.$person->id_person_lperson]  = array (
                '#type' => 'submit',
                '#name' => 'remove_person_'.$person->id_person_lperson,
                '#value' => 'Elimina Figura',
                '#submit' => array('remove_person_submit'),
                '#id' => 'edit-remove-person-'.$person->id_person_lperson,
                '#ajax' => array(
                    'callback' => 'add_person_callback',
                    'wrapper' => 'js-ajax-branch-persons-wrapper',
                ),
                '#attributes' => array(
                    'id_person_lperson' => $person->id_person_lperson,
                    'class' => array('btn','btn-remove')
                ),
            );
            $form['remove_person_'.$person->id_person_lperson] = ajax_pre_render_element($form['remove_person_'.$person->id_person_lperson]);
            $person->proles .= '</ul>'. drupal_render($form['prole_'.$person->id_person_lperson]) . drupal_render($form['add_prole_'.$person->id_person_lperson]);
            $person->actions = drupal_render($form['remove_person_'.$person->id_person_lperson]);
            $rows[$person->id_person_lperson] = array(
                $person->title.' '.$person->firstname.' '.$person->lastname,
                $person->tax_code,
                $person->positions,
                $person->proles,
                $person->actions
            );
        }

        $header = array(t('Nome'),t('Cod.Fisc.'),t('Posizioni'),t('Ruoli'),'Azioni');
        $form['fs_person']['persons_container']['table'] = array
        (
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $rows,
            '#empty' => t('Table has no row!'),
        );

        $form['fs_person']['person']  = array (
            '#type' => 'textfield',
            '#autocomplete_path' => 'person_list_autocomplete_by_lperson_callback/'.$id_lperson
        );
        $form['fs_person']['person_id'] = array(
            '#type'  => 'hidden',
            '#attributes'=>array(
                'id'   => 'edit-person-id'
            )
        );
        $form['fs_person']['add_person']  = array (
            '#type' => 'submit',
            '#value' => 'Aggiungi Figura',
            '#submit' => array('add_person_submit'),
            '#ajax' => array(
                'callback' => 'add_person_callback',
                'wrapper' => 'js-ajax-branch-persons-wrapper',
            ),
            '#attributes' => array(
                'id_lperson' => $id_lperson,
            ),
        );
        $form['fs_person']['new_person']  = array (
            '#type' => 'submit',
            '#value' => 'Nuova Figura',
            '#submit' => array('new_person_submit'),
            '#attributes' => array(
                'id_lperson' => $id_lperson,
            ),
        );
        // get person record
        $lperson = getRecordById('lperson', 'getif_data', $id_lperson);
        // populate fields
        if ($lperson->level == 1) {
            $form['fs_branch']['branch_container']['name']['#default_value'] = ucwords($lperson->name);
            $form['fs_branch']['branch_container']['tax_code']['#default_value'] = strtoupper($lperson->tax_code);
            $form['fs_branch']['branch_container']['num_employers']['#default_value']  = $lperson->num_employers;
        } else {;
            $form['fs_branch']['branch_container']['name']['#access'] = false;
            $form['fs_branch']['branch_container']['tax_code']['#access'] = false;
            $form['fs_branch']['branch_container']['seat']['#title'] = 'Sede Legale';
            $form['fs_branch']['branch_container']['num_employers']['#access'] = false;
            $form['fs_lperson_location_area']['#access'] = false;
        }
        $form['fs_branch']['branch_container']['seat']['#default_value'] = ucwords($lperson->seat);
        $form['fs_branch']['branch_container']['address']['#default_value'] = $lperson ->address;
        $form['fs_branch']['branch_container']['phone']['#default_value'] = $lperson ->phone;
        $form['fs_branch']['branch_container']['fax']['#default_value'] = strtolower($lperson->fax);
        $form['fs_branch']['branch_container']['email_address']['#default_value'] = strtolower($lperson ->email_address);
        $form['fs_branch']['branch_container']['certified_email_address']['#default_value'] = strtolower($lperson->certified_email_address);

    }
    return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_host_branch_form_validate($form, &$form_state) {
    if(!empty($form_state['values']['branch_container']['tax_code'])) {
        db_set_active('getif_data');
        $query = db_select('lperson', 'lp');
        if ($form_state["build_info"]["args"]["0"] == 'new') {
            $query->condition('tax_code', db_like($form['fs_branch']['branch_container']['tax_code']), 'LIKE');
        } else {
            $query->where(
                'lp.tax_code LIKE \''.$form_state["values"]['branch_container']["tax_code"].'\' AND
                  lp.id_lperson <> '.$form_state["build_info"]["args"]["1"].' AND 
                  lp.active IN (1,2)
                ');
        }
        $query->fields('lp', array('id_lperson'));
        $id_person = $query->execute()->fetchAssoc();
        db_set_active();
        if (!empty($id_person)) {
            form_set_error('tax_code', t('Struttura con questo identificativo esistente.'));
        }
    }
}

/**
 * @param $form
 * @param $form_state
 */
function lperson_host_branch_form_submit($form, &$form_state) {
    if($form_state["build_info"]["args"][0] == "new") {
        $id_lperson = save($form, $form_state);
        drupal_set_message(t("Dati inseriti con successo"));
        drupal_goto('lperson_host/branch/edit/'.$id_lperson);
    } elseif ($form_state["build_info"]["args"][0] == "edit") {
        $id_lperson = edit($form, $form_state);
        drupal_set_message(t("Dati aggiornati con successo"));
        drupal_goto('lperson_host/branch/edit/'.$id_lperson);
    }
}

/**
 * @param $form
 * @param $form_state
 */
function new_person_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    session_set('new_person_lperson', array('lperson' => $id_lperson));
    getif_goto('person/new/'.$id_lperson,array('query'=>array('lprole'=>'2')),302,true);
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
 * @param $form
 * @param $form_state
 * @return DatabaseStatementInterface|int
 * @throws Exception
 */
function save($form, &$form_state) {
    $id_lperson_parent = $form_state["build_info"]["args"]["1"];
    $ids_lprole = array(2=>2); // Soggetto Ospitante
    $fields = array(
        'name' => _strformat($form_state['values']['branch_container']['name']),
        'seat' => _strformat($form_state['values']['branch_container']['seat']),
        'vat_number' => strtoupper($form_state['values']['branch_container']['tax_code']),
        'tax_code' => strtoupper($form_state['values']['branch_container']['tax_code']),
        'num_employers' => !empty($form_state['values']['branch_container']['num_employers'])?$form_state['values']['branch_container']['num_employers']:0,
        'address' => !empty($form_state['values']['branch_container']['address'])?_strformat($form_state['values']['branch_container']['address']):null,
        'phone' => !empty($form_state['values']['branch_container']['phone'])?$form_state['values']['branch_container']['phone']:null,
        'fax' => !empty($form_state['values']['branch_container']['fax'])?$form_state['input']['branch_container']['fax']:null,
        'email_address' => !empty($form_state['values']['branch_container']['email_address'])?strtolower($form_state['values']['branch_container']['email_address']):null,
        'certified_email_address' => !empty($form_state['values']['branch_container']['certified_email_address'])?strtolower($form_state['values']['branch_container']['certified_email_address']):null,
        'id_lperson_parent' => $id_lperson_parent,
        'level' => 1,
        'active' => 1
    );
    // insert to DB
    db_set_active('getif_data');
    $query = db_insert('lperson');
    $id_lperson = $query->fields($fields)->execute();
    foreach ($ids_lprole AS $key_id_lprole => $id_lprole) {
        $fields = array(
            'id_lperson' => $id_lperson,
            'id_lprole' => $key_id_lprole,
            'active' => 1
        );
        try {
            $query = db_insert('lperson_lprole');
            $query->fields($fields)->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }

    }
    db_set_active();
    return $id_lperson;
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function edit($form, &$form_state) {
    $id_lperson = $form_state["build_info"]["args"][1];
    $fields = array(
        'seat' => _strformat($form_state['values']['branch_container']['seat']),
        'address' => !empty(_strformat($form_state['values']['branch_container']['address']))?_strformat($form_state['values']['branch_container']['address']):null,
        'phone' => !empty($form_state['values']['branch_container']['phone'])?$form_state['values']['branch_container']['phone']:null,
        'fax' => !empty($form_state['values']['branch_container']['fax'])?$form_state['values']['branch_container']['fax']:null,
        'certified_email_address' => !empty($form_state['values']['branch_container']['certified_email_address'])?strtolower($form_state['values']['branch_container']['certified_email_address']):null,
        'email_address' => !empty($form_state['values']['branch_container']['email_address'])?strtolower($form_state['values']['branch_container']['email_address']):null,
        'date_upd' => date("Y-m-d H:i:s", time()),
    );
    if (!empty($form_state['values']['branch_container']['name'])) { // Struttura
        $fields = array_merge($fields,array(
            'name' => _strformat($form_state['values']['branch_container']['name']),
            'vat_number' => strtoupper($form_state['values']['branch_container']['tax_code']),
            'tax_code' => strtoupper($form_state['values']['branch_container']['tax_code']),
            'num_employers' => $form_state['values']['branch_container']['num_employers'],
        ));
    }
    db_set_active('getif_data');
    try {
        $query = db_update('lperson');
        $id_lperson_m = $query -> fields($fields) -> condition('id_lperson',$id_lperson)->execute();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    return $id_lperson;
}

/**
 * @param $form
 * @param $form_state
 */
function add_position_submit($form, &$form_state) {
    $id_person_lperson = $form_state['clicked_button']['#attributes']['id_person_lperson'];
    db_set_active('getif_data');
    $r = db_query("
            SELECT t1.*
            FROM `person_lperson_position` AS t1
            WHERE 
            t1.id_person_lperson = " . $id_person_lperson . " AND t1.id_position = " . $form_state['values']['position_' . $id_person_lperson] . "
            AND t1.active = 1 LIMIT 1;
        ")->fetchObject();
    db_set_active();
    $fields = array(
        'id_person_lperson' => $id_person_lperson,
        'id_position' => $form_state['values']['position_'.$id_person_lperson],
        'active' => 1
    );
    if (empty($r)) { // se la figura è già associata alla Struttura

        try {
            db_set_active('getif_data');
            $query = db_insert('person_lperson_position');
            $query->fields($fields)->execute();
            db_set_active();
            drupal_set_message(t("Posizione inserita con successo."), 'status');
        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }
    } else {
        drupal_set_message(t("Posizione già associata o errore nell'inserimento."), 'error');
    }
    $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 */
function remove_position_submit($form, &$form_state) {
    $id_person_lperson_position = $form_state['clicked_button']['#attributes']['id_person_lperson_position'];
    $fields = array(
        'active' => 2,
        'date_upd' => date("Y-m-d H:i:s", time())
    );
    db_set_active('getif_data');
    try {
        $query = db_update('person_lperson_position');
        $query ->fields($fields) -> where('id_person_lperson_position = '.$id_person_lperson_position) ->execute();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}

/**
 * @param $form
 * @param $form_state
 */
function add_prole_submit($form, &$form_state)
{
    $id_person_lperson = $form_state['clicked_button']['#attributes']['id_person_lperson'];

    db_set_active('getif_data');
    $r = db_query("
            SELECT t1.*
            FROM `person_lperson_prole` AS t1
            WHERE 
            t1.id_person_lperson = " . $id_person_lperson . " AND t1.id_prole = " . $form_state['values']['prole_' . $id_person_lperson] . "
            AND t1.active = 1 LIMIT 1;
        ")->fetchObject();
    db_set_active();


    $fields = array(
        'id_person_lperson' => $id_person_lperson,
        'id_prole' => $form_state['values']['prole_' . $id_person_lperson],
        'active' => 1
    );
    if (empty($r)) { // se la figura è già associata alla Struttura
        try {
            db_set_active('getif_data');
            $query = db_insert('person_lperson_prole');
            $query->fields($fields)->execute();
            db_set_active();
            drupal_set_message(t("Ruolo inserito con successo."), 'status');
        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }
    } else {
        drupal_set_message(t("Ruolo già associato o errore nell'inserimento."), 'error');
    }
    $form_state['rebuild'] = TRUE;

}

/**
 * @param $form
 * @param $form_state
 */
function remove_prole_submit($form, &$form_state) {

    $id_person_lperson_prole = $form_state['clicked_button']['#attributes']['id_person_lperson_prole'];

    // controllo che la persona con quel ruolo non abbia tirocini attivi o pratiche di tirocinio aperte
    $tables = array('internship_host_tutor','internship_promoter_tutor','internship_project_contact');
    foreach ($tables as $table) {
        db_set_active('getif_data');
        $query = db_select($table, 't1');
        $query->condition('t1.id_person_lperson_prole', $id_person_lperson_prole);
        $query->condition('t1.active', 1);
        $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
        $query->condition('t2.state', 0, '<>'); // tirocinio
        $query->condition('t2.state', 7, '<>');
        $query->condition('t2.active', 1);
        $result = $query->countQuery()->execute()->fetchField();
        db_set_active();
        if ($result > 0) {
            drupal_set_message(t("Ruolo/i presente/i in una pratica di tirocinio aperta e/o tirocinio attivo."),'error');
            return;
        }
    }


    $fields = array(
        'active' => 2,
        'date_upd' => date("Y-m-d H:i:s", time())
    );
    db_set_active('getif_data');
    try {
        $query = db_update('person_lperson_prole');
        $query ->fields($fields) -> where('id_person_lperson_prole = '.$id_person_lperson_prole) ->execute();
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_position_callback($form, &$form_state) {
    return $form['fs_person']['persons_container'];
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_prole_callback($form, &$form_state) {
    return $form['fs_person']['persons_container'];
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_person_callback($form, &$form_state) {
    return $form['fs_person']['persons_container'];
}


/**
 * @param $form
 * @param $form_state
 */
function add_person_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson'];
    $id_person = $form_state['input']['person_id'];
    if (!empty($id_person)) {
        db_set_active('getif_data');
        $r = db_query("
            SELECT t1.*
            FROM `person_lperson` AS t1
            WHERE 
            t1.id_person = " . $id_person . " AND t1.id_lperson = " . $id_lperson . "
            AND t1.active = 1 LIMIT 1;
        ")->fetchObject();
        db_set_active();
        $fields = array(
            'id_person' => $id_person,
            'id_lperson' => $id_lperson,
            'active' => 1
        );
        if (empty($r)) { // se la figura è già associata alla Struttura
            try {
                db_set_active('getif_data');
                $query = db_insert('person_lperson');
                $query->fields($fields)->execute();
                db_set_active();
                drupal_set_message(t("Figura associata con successo."), 'status');
            } catch (Exception $ex) {
                drupal_set_message('Errore: ' . $ex, 'error');
            }
        } else {
            drupal_set_message(t("Figura già associata."), 'error');
        }
    } else {
        drupal_set_message(t("Devi prima selezionare una figura."), 'error');
    }
    $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 */
function remove_person_submit($form, &$form_state) {
    $id_person_lperson = $form_state['clicked_button']['#attributes']['id_person_lperson'];
    $selected = getAllRecordByField('person_lperson_prole', 'getif_data', 'id_person_lperson', $id_person_lperson);

    // controllo che la persona con quel ruolo non abbia tirocini attivi o pratiche di tirocinio aperte
    $tables = array('internship_host_tutor','internship_promoter_tutor','internship_project_contact');
    foreach ($tables as $table) {
        foreach ($selected as $person_lperson_prole) {

            db_set_active('getif_data');
            $query = db_select($table, 't1');
            $query->condition('t1.id_person_lperson_prole', $person_lperson_prole->id_person_lperson_prole);
            $query->condition('t1.active', 1);
            $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
            $query->condition('t2.state', 0, '<>'); // tirocinio
            $query->condition('t2.state', 7, '<>');
            $query->condition('t2.active', 1);
            $result = $query->countQuery()->execute()->fetchField();
            db_set_active();
            if ($result > 0) {
                drupal_set_message(t("La Figura non può essere eliminata perché ha un ruolo/i presente/i in una pratica di tirocinio aperta e/o tirocinio attivo."),'error');
                return;
            }
        }
    }
    $fields = array(
        'active' => 2,
        'date_upd' => date("Y-m-d H:i:s", time())
    );
    $where = 'id_person_lperson = '.$id_person_lperson;
    try {
        db_set_active('getif_data');
        // Elimina l'associazione persona - struttura
        $query = db_update('person_lperson');
        $query -> fields($fields)-> where($where) ->execute();
        db_set_active();
        // Elimina i ruoli associati alla persona presso la struttura
        $fields = array(
            'id_person_lperson' => $id_person_lperson,
            'active' => 2,
            'date_upd' => date("Y-m-d H:i:s", time())
        );
        $where = 'id_person_lperson = '.$id_person_lperson;
        try {
            db_set_active('getif_data');
            $query = db_update('person_lperson_prole');
            $query -> fields($fields)->where($where)->execute();
            db_set_active();
            drupal_set_message(t("Figura rimossa con successo."),'status');

        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 */
function remove_persons_submit($form, &$form_state) {
    $selected = array_filter($form_state['values']['persons_container']['table']);
    // elimina elementi selezionati
    foreach ($selected as $id_person_lperson => $item) {
        $fields = array(
            'active' => 2,
            'date_upd' => date("Y-m-d H:i:s", time())
        );
        $where = 'id_person_lperson = '.$id_person_lperson;
        db_set_active('getif_data');
        try {
            $query = db_update('person_lperson');
            $query -> fields($fields)-> where($where) ->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
    }
    $form_state['rebuild'] = TRUE;
    drupal_get_messages();
}


/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function add_lperson_location_area_callback ($form, &$form_state) {
    return $form['fs_lperson_location_area']['lperson_location_area_container'];
}

/**
 * @param $form
 * @param $form_state
 */
function edit_lperson_location_area_submit($form, &$form_state) {
    $id_lperson_location_area = $form_state['clicked_button']['#attributes']['id_lperson_location_area'];
    getif_goto('lperson_host/branch/child/edit/'.$id_lperson_location_area,array(),302,true);
}

/**
 * @param $form
 * @param $form_state
 */
function disable_lperson_location_area_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson_location_area'];
    db_set_active('getif_data');
    try {
        // abilita il laboratorio
        setRecordState('lperson', 'getif_data', 'id_lperson', $id_lperson, 'active', 2);
        drupal_set_message('Elemento disabilitato con successo.','status');
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 */
function enable_lperson_location_area_submit($form, &$form_state) {
    $id_lperson = $form_state['clicked_button']['#attributes']['id_lperson_location_area'];
    db_set_active('getif_data');
    try {
        // abilita il laboratorio
        setRecordState('lperson', 'getif_data', 'id_lperson', $id_lperson, 'active', 1);
        drupal_set_message('Elemento abilitato con successo.','status');
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
    db_set_active();
    $form_state['rebuild'] = TRUE;
}



/**
 * @param $form
 * @param $form_state
 */
function remove_lperson_location_area_submit($form, &$form_state) {
    $id_lperson_location_area = $form_state['clicked_button']['#attributes']['id_lperson_location_area'];
    //controllo che il lab non sia utilizzato in pratiche di tirocinio aperta e/o tirocini attivi
    db_set_active('getif_data');
    $query = db_select('internship_lperson_location_area', 't1');
    $query->condition('t1.id_lperson_location_area', $id_lperson_location_area);
    $query->condition('t1.active', 1);
    $query->innerJoin('internship_state', 't2', 't1.id_internship = t2.id_internship');
    $query->condition('t2.state', 0, '<>'); // tirocinio
    $query->condition('t2.state', 7, '<>');
    $query->condition('t2.active', 1);
    $result = $query->countQuery()->execute()->fetchField();
    db_set_active();
    if ($result > 0) {
        drupal_set_message(t("Il Laboratorio non può essere eliminato perché è utilizzato in una pratica di tirocinio aperta e/o tirocinio attivo."),'error');
        return;
    }
    $fields = array(
        'active' => 2,
        'date_upd' => date("Y-m-d H:i:s", time())
    );
    $where = 'id_lperson = '.$id_lperson_location_area;

    try {
        // Elimina l'associazione persona - struttura
        db_set_active('getif_data');
        $query = db_update('lperson');
        $query -> fields($fields)-> where($where) ->execute();
        db_set_active();
        drupal_set_message(t("Elemento eliminato con successo."),'error');
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }

    $form_state['rebuild'] = TRUE;
}


/**
 * @param $form
 * @param $form_state
 */
function add_lperson_location_area_submit($form, &$form_state) {
    $id_lperson_location_area = $form_state['clicked_button']['#attributes']['id_lperson'];
    getif_goto('lperson_host/branch/child/new/'.$id_lperson_location_area,array(),302,true);
}


/* end */
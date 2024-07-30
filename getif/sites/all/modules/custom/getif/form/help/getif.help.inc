<?php

/**
 * Theme muova/modifica convenzione
 * @param $form
 * @param $form_state
 * @return mixed
 */

function theme_help_form($variables){
    $variables['page']['navigation'] = 'test';

}

/**
 * Form nuova/modifica convenzione
 * @param $form
 * @param $form_state
 * @return mixed
 * @throws InvalidMergeQueryException
 */
function help_form($form, &$form_state) {

    $form['step1'] = array
    (
        '#type' => 'radios',
        '#title' => t('Scegli l\'azione:'),
        '#name' => 'edit-step1',
        '#description' => t('Scegli l\'azione:'),
        '#default_value' => array('images'),
        '#options' => array
        (
            1 => t('voglio creare un nuovo tirocinio'),
            2 => t('voglio creare una nuova frequenza volontaria')
        ),
        '#attributes' => array(
            'name' => 'edit-step1'
        ),
        '#tree' => TRUE,
        '#prefix' => '<div class="list-group"><div class="list-group-item">',
        '#suffix' => '</div></div>'
    );

    $step2_1 = '
    <ul class="list-group">';

    $step2_1 .='
        <li class="list-group-item list-group-item-primary">Azioni preliminari:
            <ul class = "intended">
                <li>verificare che esista o altrimenti creare in anagrafe una convenzione attiva tra Soggetto Ospitante e Soggetto Promotore.</li>
                <li>verificare che esistano in anagrafe o altrimenti creare le figure con i seguenti ruoli presso la/e Struttura/e del Soggetto Ospitante:
                    <ul class = "intended">
                        <li>Tutor del Soggetto Ospitante</li>
                        <li>Responsabili/Referente del Progetto Formativo</li>
                    </ul>
                </li>
                <li>verificare che esista o altrimenti creare in anagrafe la figura con ruolo "Tutor del Soggetto Promotore" presso il Soggetto Promotore o presso il dipartimento/segreteria di questo, risultante in Convenzione</li>
                <li>verificare che esistano in anagrafe o altrimenti creare le figure che risulteranno firmatarie dei documenti "Nulla Osta" e "Allegato B" e che ricoprano una posizione tra quelle sotto elencate presso il Soggetto Ospitante o presso una struttura di esso:
                    <ul class = "intended">
                        <li>Direttore generale</li>
                        <li>Dirigente</li>
                        <li>Dirigente responsabile di struttura semplice</li>		
                        <li>Dirigente responsabile di struttura complessa</li>
                    </ul>
                </li>
                <li>nel caso di tirocinio extracurriculare verificare la presenza di un budget annuale per l\'anno di richiesta del tirocinio.</li>
            </ul>
        </li>';
    $step2_1 .= '
        <li class="list-group-item list-group-item-primary">Creazione Tirocinio:<ul class = "intended">';
    $step2_1 .= '<li>dal menu selezionare la voce "Tirocini" e cliccare sul pulsante <span value="Nuovo Tirocinio" class="btn btn-default form-submit icon-before"><span class="icon glyphicon glyphicon-plus" aria-hidden="true"></span>Nuovo Tirocinio</span></li>';
    $step2_1 .= '<li>seguire la procedura compilando correttamente i dati delle 4 schede e proseguire</li>';
    $step2_1 .= '<li>controllare il riepilogo dei dati, impostare una data di avvio del tirocinio e proseguire. Da questo momento in poi la pratica di tirocinio non potrà più essere modificata</li>';
    $step2_1 .= '<li>generare e riallegare i documenti "Nulla osta" e "Allegato B" debitamente firmati</li>';
    $step2_1 .= '<li>allegare i documenti mancanti (es. Parere favorevole del Dirigente Responsabile della U.O. Ospitante IOFZ-002 E) e confermare l\'avvio del tirocinio</li>';
    $step2_1 .= '
            </ul></li>';
    $step2_1 .= '
    </ul>';
    $step2_2 = '
    <ul class="list-group">';

    $step2_2 .='
        <li class="list-group-item list-group-item-primary">Azioni preliminari:
            <ul class = "intended">
                <li>verificare che esistano in anagrafe o altrimenti creare le figure con ruolo Responsabile/Referente presso la/e Struttura/e selezionata/e</li>
                <li>verificare che esistano in anagrafe o altrimenti creare le figure che risulteranno firmatarie dei documenti "Nulla Osta" e "Allegato B" e che ricoprano una posizione presso il Soggetto Ospitante o presso una struttura di esso. Le posizioni selezionabili sono:
                    <ul class = "intended">
                        <li>Direttore generale</li>
                        <li>Dirigente</li>
                        <li>Dirigente responsabile di struttura semplice</li>		
                        <li>Dirigente responsabile di struttura complessa</li>
                    </ul>
                </li>
            </ul>
        </li>';
    $step2_2 .= '
        <li class="list-group-item list-group-item-primary">Creazione Frequenza volontaria:<ul class = "intended">';
    $step2_2 .= '<li>dal menu selezionare la voce "Frequenze volontarie" e cliccare sul pulsante <span value="Nuova Frequenza Volontaria" class="btn btn-default form-submit icon-before"><span class="icon glyphicon glyphicon-plus" aria-hidden="true"></span>Nuova Frequenza Volontaria</span></li>';
    $step2_2 .= '<li>seguire la procedura compilando correttamente i dati delle 4 schede e proseguire</li>';
    $step2_2 .= '<li>controllare il riepilogo dei dati e impostare una data di avvio della frequenza volontaria e proseguire. Da questo momento in poi la pratica non potrà più essere modificata</li>';
    $step2_2 .= '<li>generare e riallegare i documenti "Nulla osta" e "Allegato B" debitamente firmati</li>';
    $step2_2 .= '<li>allegare i documenti mancanti (es. Parere favorevole del Dirigente Responsabile della U.O. Ospitante IOFZ-003 C) e confermare l\'avvio della frequenza volontaria</li>';
    $step2_2 .= '
            </ul></li>';
    $step2_2 .= '
    </ul>';
    $form['c_step2_1'] = array(
        '#type' => 'container',
        '#states' => array(
            'visible' => array(
                ':input[name="edit-step1"]' => array('value' => 1),
            ),
        ),
        '#tree' => TRUE,
    );
    $form['c_step2_1']['step2_1'] = array
    (
        '#markup' => $step2_1,

    );
    $form['c_step2_2'] = array(
        '#type' => 'container',
        '#states' => array(
            'visible' => array(
                ':input[name="edit-step1"]' => array('value' => 2),
            ),
        ),
        '#tree' => TRUE,
    );
    $form['c_step2_2']['step2_2'] = array
    (
        '#markup' => $step2_2,

    );


    return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function help_form_validate($form, &$form_state) {

}

/**
 * @param $form
 * @param $form_state
 */
function help_form_submit($form, &$form_state) {

}

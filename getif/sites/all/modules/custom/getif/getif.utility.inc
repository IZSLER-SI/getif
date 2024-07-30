<?php
/*** ************************* ***/
/***        CONFIGURATION      ***/
/*** ************************* ***/

include __DIR__.'/../../../../default/getif.config.php';

/*** ********************** ***/
/***        UTILITIES       ***/
/*** ********************** ***/

/**
 * @param $form
 * @param $header_content
 * @param $options
 * @return string
 */
function getif_form_theme (&$form,$header_content = null,$options = null) {

    $form['nav']['help'] = array(
        '#markup' => '<a href="#" class="help-btn" data-toggle="tooltip" data-original-title="Help contenuto pagina">
                                <span class="glyphicon glyphicon-question-sign" style="font-size:20px;">
                            </a>'
    );
    $help_form = array(
        'user_list_view_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>aprire la pagina per la creazione di un nuovo Utente</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene la lista degli utenti.<br/>Per visualizzare/gestire/modificare un Utente cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;.<br/><b>Nota bene:</b> per inserire un nuovo utente è necessario aver precedentemente creato una figura.'

            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo dei Tirocini. Per visualizzare/modificare un tirocinio cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'user_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista degli Utenti</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene le credenziali e i permessi dell\'utente all\'interno del sistema. E\' possibile modificare i dati e salvare le modifiche cliccando sul pulsante &quot;Salva&quot;'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo dei Tirocini. Per visualizzare/modificare un tirocinio cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'internship_list_view_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>aprire la pagina per la creazione di un nuovo Tirocinio</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene il riepilogo dei Tirocini.<br/>E\' possibile:<ul class=&quot;intended&quot;><li>visualizzare e modificare il registro presenze cliccando sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-edit&quot;&gt;&lt;/span&gt;.</li><li>visualizzare/gestire/modificare un tirocinio cliccando sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;</li><li>eliminare definitivamente un tirocinio cliccando sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-trash&quot;&gt;&lt;/span&gt;</li></ul>Attenzione: solo i tirocini con stato &quot;In attesa&quot; possono essere eliminati.'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo dei Tirocini. Per visualizzare/modificare un tirocinio cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'vinternship_list_view_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>aprire la pagina per la creazione di una nuova Frequenza Volontaria</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene il riepilogo delle frequenze volontarie.<br/>E\' possibile:<ul class=&quot;intended&quot;><li>visualizzare e modificare il registro presenze cliccando sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-edit&quot;&gt;&lt;/span&gt;.</li><li>visualizzare/gestire/modificare una frequenza volontaria cliccando sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;</li><li>eliminare definitivamente una frequenza volontaria cliccando sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-trash&quot;&gt;&lt;/span&gt;</li></ul>Attenzione: solo le frequenze volontarie con stato &quot;In attesa&quot; possono essere eliminati.'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo dei Tirocini. Per visualizzare/modificare un tirocinio cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'internship_1_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Tirocini</li><li>proseguire alla scheda successiva se la scheda corrente è già compilata</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta lo stato di avanzamento della pratica.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per la creazione di una nuova pratica Tirocinio. Per salvare/modificare i dati inseriti cliccare sul pulsante &quot;Salva&quot;'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo dei Tirocini. Per visualizzare/modificare un tirocinio cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'vinternship_1_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista delle Frequenze Volontarie</li><li>proseguire alla scheda successiva se la scheda corrente è già compilata</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta lo stato di avanzamento della pratica.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per la creazione di una nuova pratica Frequenza Volontaria. Per salvare/modificare i dati inseriti cliccare sul pulsante &quot;Salva&quot;'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'internship_2_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Tirocini</li><li>tornare alla scheda precedente</li><li>proseguire alla scheda successiva se la scheda corrente è già compilata</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta lo stato di avanzamento della pratica e il riepilogo dei dati già compilati.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per la creazione di una nuova pratica Tirocinio. Per salvare i dati inseriti cliccare sul pulsante &quot;Salva&quot;. Per modificare i dati inseriti cliccare sul pulsante &quot;Modifica&quot;. Per modificare i dati inseriti cliccare sul pulsante &quot;Modifica Dati Tirocinante&quot;. Per modificare i dati inseriti cliccare sul pulsante &quot;Modifica&quot;. Attenzione: modificando la scheda corrente i dati delle schede successive verranno persi definitivamente.'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo dei Tirocini. Per visualizzare/modificare un tirocinio cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'vinternship_2_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista delle Frequenze Volontarie</li><li>tornare alla scheda precedente</li><li>proseguire alla scheda successiva se la scheda corrente è già compilata</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta lo stato di avanzamento della pratica e il riepilogo dei dati già compilati.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per la creazione di una nuova pratica Frequenza Volontaria. Per salvare i dati inseriti cliccare sul pulsante &quot;Salva&quot;. Per modificare i dati inseriti cliccare sul pulsante &quot;Modifica&quot;. Per modificare i dati inseriti cliccare sul pulsante &quot;Modifica Dati Frequentatore&quot;. Per modificare i dati inseriti cliccare sul pulsante &quot;Modifica&quot;. Attenzione: modificando la scheda corrente i dati delle schede successive verranno persi definitivamente.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content' =>''
            )
        ),
        'intern_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Tirocini</li><li>tornare alla scheda tirocinio</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta lo stato di avanzamento della pratica.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per completare i dati del Tirocinante. Per salvare/modificare i dati inseriti cliccare sul pulsante &quot;Salva&quot;.'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo dei Tirocini. Per visualizzare/modificare un tirocinio cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'vintern_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista delle Frequenze Volontarie</li><li>tornare alla scheda Frequenza Volontaria</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta lo stato di avanzamento della pratica.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per completare i dati del Frequentatore Volontario. Per salvare/modificare i dati inseriti cliccare sul pulsante &quot;Salva&quot;.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'internship_3_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Tirocini</li><li>tornare alla scheda precedente</li><li>proseguire alla scheda successiva se la scheda corrente è già compilata</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta lo stato di avanzamento della pratica e il riepilogo dei dati già compilati.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per la creazione di una nuova pratica Tirocinio. Per salvare i dati inseriti cliccare sul pulsante &quot;Salva&quot;. Per modificare i dati inseriti cliccare sul pulsante &quot;Modifica&quot;. Attenzione: modificando la scheda corrente i dati delle schede successive verranno persi definitivamente.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'vinternship_3_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista delle Frequenze Volontarie</li><li>tornare alla scheda precedente</li><li>proseguire alla scheda successiva se la scheda corrente è già compilata</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta lo stato di avanzamento della pratica e il riepilogo dei dati già compilati.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per la creazione di una nuova pratica Frequenza Volontaria. Per salvare i dati inseriti cliccare sul pulsante &quot;Salva&quot;. Per modificare i dati inseriti cliccare sul pulsante &quot;Modifica&quot;. Attenzione: modificando la scheda corrente i dati delle schede successive verranno persi definitivamente.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'internship_4_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Tirocini</li><li>tornare alla scheda precedente</li><li>proseguire alla pagina di Gestione Tirocinio se tutte le schede risultano completate</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta lo stato di avanzamento della pratica e il riepilogo dei dati già compilati.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per la creazione di una nuova pratica Tirocinio. Per salvare i dati inseriti cliccare sul pulsante &quot;Salva&quot;. Per modificare i dati inseriti cliccare sul pulsante &quot;Modifica&quot;. Attenzione: modificando la scheda corrente i dati delle schede successive verranno persi definitivamente.'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo dei Tirocini. Per visualizzare/modificare un tirocinio cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'vinternship_4_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista delle Frequenze Volontarie</li><li>tornare alla scheda precedente</li><li>proseguire alla pagina di Gestione Frequenza Volontaria se tutte le schede risultano completate</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta lo stato di avanzamento della pratica e il riepilogo dei dati già compilati.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per la creazione di una nuova pratica Frequenza Volontaria. Per salvare i dati inseriti cliccare sul pulsante &quot;Salva&quot;. Per modificare i dati inseriti cliccare sul pulsante &quot;Modifica&quot;. Attenzione: modificando la scheda corrente i dati delle schede successive verranno persi definitivamente.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'internship_manage_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Tirocini</li><li>tornare alla pratica di Tirocinio</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta il riepilogo dei dati già compilati.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i dati sullo stato del tirocinio e la data di attivazione.<br/>Nel caso di tirocinio senza data di attivazione la maschera presenterà in aggiunta il campo data da editare e il pulsante di conferma.<br/>Nel caso di tirocinio con la data di attivazione confermata la maschera presenterà in aggiunta:<ul class=&quot;intended&quot;><li>gli strumenti per la generazione dei documenti &quot;Nulla osta&quot; e &quot;Allegato B&quot;</li><li>i campi per il caricamento dei documenti generati (debitamente firmati) e degli altri documenti allegabili</li><li>la lista dei documenti gi&agrave; allegati</li><li>gli strumenti di gestione dello stato del tirocinio: Data di interruzione / Data di proroga / Data di conclusione</li></ul>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'vinternship_manage_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista delle Frequenze Volontarie</li><li>tornare alla pratica di Frequenza Volontaria</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Questa area presenta il riepilogo dei dati già compilati.'
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i dati sullo stato della frequenza volontaria e la data di attivazione.<br/>Nel caso di frequenza volontaria senza data di attivazione la maschera presenterà in aggiunta il campo data da editare e il pulsante di conferma.<br/>Nel caso di frequenza volontaria con la data di attivazione confermata la maschera presenterà in aggiunta:<ul class=&quot;intended&quot;><li>gli strumenti per la generazione dei documenti &quot;Nulla osta&quot; e &quot;Allegato B&quot;</li><li>i campi per il caricamento dei documenti generati (debitamente firmati) e degli altri documenti allegabili</li><li>la lista dei documenti gi&agrave; allegati</li><li>gli strumenti di gestione dello stato della frequenza volontaria: Data di interruzione / Data di proroga / Data di conclusione</li></ul>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'intern_list_view_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene l\'anagrafe dei Tirocinanti.<br/>Per disabilitare/abilitare un tirocinante cliccare sul pulsante <div class=&quot;toggle btn btn-sm btn-success&quot; style=&quot;width: 48px; height: 29px;&quot;><button data-toggle=&quot;toggle&quot; button_checked=&quot;false&quot; class=&quot;btn form-submit&quot;></button><div class=&quot;toggle-group&quot;><label class=&quot;btn btn-success btn-sm toggle-on&quot;>Sì</label><label class=&quot;btn btn-default btn-sm active toggle-off&quot;>No</label><span class=&quot;toggle-handle btn btn-default btn-sm&quot;></span></div></div><br/>Per visualizzare/modificare i dati di un tirocinante cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;<br/>Per eliminare definitivamente un tirocinante cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-trash&quot;&gt;&lt;/span&gt;<br/><b>Nota bene (*):</b> i tirocinanti inseriti in una o più pratiche di tirocinio non possono essere eliminati.<br/><b>Nota bene (**):</b> un tirocinante disabilitato non potrà essere selezionato per un nuovo tirocinio.'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo dei Tirocini. Per visualizzare/modificare un tirocinio cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'vintern_list_view_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene l\'anagrafe dei frequentatori volontari.<br/>Per disabilitare/abilitare un frequentatore volontario cliccare sul pulsante <div class=&quot;toggle btn btn-sm btn-success&quot; style=&quot;width: 48px; height: 29px;&quot;><button data-toggle=&quot;toggle&quot; button_checked=&quot;false&quot; class=&quot;btn form-submit&quot;></button><div class=&quot;toggle-group&quot;><label class=&quot;btn btn-success btn-sm toggle-on&quot;>Sì</label><label class=&quot;btn btn-default btn-sm active toggle-off&quot;>No</label><span class=&quot;toggle-handle btn btn-default btn-sm&quot;></span></div></div><br/>Per visualizzare/modificare i dati di un frequentatore volontario cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;<br/>Per eliminare definitivamente un frequentatore volontario cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-trash&quot;&gt;&lt;/span&gt;<br/><b>Nota bene (*):</b> i frequentatori volontari inseriti in una o più pratiche di frequenza volontaria non possono essere eliminati.<br/><b>Nota bene (**):</b> un frequentatore volontario disabilitato non potrà essere selezionato per una nuova frequenza volontaria.'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo delle Frequenze volontarie. Per visualizzare/modificare una frequenza volontaria cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'lperson_host_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>aprire la maschera di gestione delle strutture del Soggetto Ospitante</li><li>la gestione dei budget annuali per i tirocini extracurriculari.</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i dati anagrafici del Soggetto Ospitante. E\' possibile modificare i dati e salvare le modifiche cliccando sul pulsante &quot;Salva&quot;'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>''
            )
        ),
        'lperson_host_branch_manage_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla pagina del Soggetto Ospitante</li><li>aprire la pagina per la creazione di una nuova Struttura del Soggetto Ospitante</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content' => ''
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene la sede legale e la lista delle strutture del Soggetto Ospitante.<br/>Per disabilitare/abilitare una struttura cliccare sul pulsante <div class=&quot;toggle btn btn-sm btn-success&quot; style=&quot;width: 48px; height: 29px;&quot;><button data-toggle=&quot;toggle&quot; button_checked=&quot;false&quot; class=&quot;btn form-submit&quot;></button><div class=&quot;toggle-group&quot;><label class=&quot;btn btn-success btn-sm toggle-on&quot;>Sì</label><label class=&quot;btn btn-default btn-sm active toggle-off&quot;>No</label><span class=&quot;toggle-handle btn btn-default btn-sm&quot;></span></div></div><br/>Per visualizzare/modificare i dati, gestire i laboratori, le figure associate alla struttura e le rispettive posizioni e ruoli cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;<br/>Per eliminare definitivamente una struttura cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-trash&quot;&gt;&lt;/span&gt;<br/><b>Nota bene (*):</b> le strutture che hanno delle figure associate o che sono in una o più pratiche di tirocinio/frequenza-volontaria non possono essere eliminate.<br/><b>Nota bene (**):</b> una struttura disabilitata non potrà essere selezionata per ospitare un/una tirocinio/frequenza-volontaria.'            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'lperson_host_branch_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla pagina di Gestione Strutture</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Nella scheda &quot;Dati anagrafici&quot; è possibile modificare i dati della struttura.'.'<br/>'.
                    'Nella scheda &quot;Laboratori&quot; è possibile gestire i laboratori della struttura.'.'<br/>'.
                    'Nella scheda &quot;Figure&quot; è possibile gestire le figure associate alla struttura, la posizione e i ruoli che la figura può ricoprire in un tirocinio (tutor, responsabile progetto formativo, referente, ecc.) presso la struttura.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'lperson_host_child_branch_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla pagina di Gestione dei Laboratori</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per inserire/modificare i dati del laboratorio della struttura. Per salvare/modificare i dati inseriti cliccare sul pulsante &quot;Salva&quot;.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'lperson_host_budget_manage_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla pagina del Soggetto Ospitante</li><li>aprire la pagina per l\'inserimento di un Nuovo Budget</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene la lista dei budget annuali per i tirocini extra-curriculari. Per visualizzare/modificare i dati cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'lperson_host_budget_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla pagina di Gestione dei Budget</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per inserire/modificare il budget annuale per i tirocini extra-curriculari. Per salvare/modificare i dati inseriti cliccare sul pulsante &quot;Salva&quot;.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'lperson_host_branch_calendar_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla pagina di Gestione Strutture</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera permette di visualizzare il calendario di occupazione delle Strutture per tirocini e frequenze volontarie'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'lperson_promoter_list_view_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>aprire la pagina di inserimento di un Nuovo Soggetto Promotore</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene la lista dei Soggetti Promotore.<br/>Per disabilitare/abilitare un Soggetto Promotore cliccare sul pulsante <div class=&quot;toggle btn btn-sm btn-success&quot; style=&quot;width: 48px; height: 29px;&quot;><button data-toggle=&quot;toggle&quot; button_checked=&quot;false&quot; class=&quot;btn form-submit&quot;></button><div class=&quot;toggle-group&quot;><label class=&quot;btn btn-success btn-sm toggle-on&quot;>Sì</label><label class=&quot;btn btn-default btn-sm active toggle-off&quot;>No</label><span class=&quot;toggle-handle btn btn-default btn-sm&quot;></span></div></div><br/>Per gestire un Soggetto Promotore cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;<br/>Per eliminare definitivamente un Soggetto Promotore cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-trash&quot;&gt;&lt;/span&gt;<br/><b>Nota bene (*):</b> i Soggetti Promotore associati ad almeno una convenzione e/o ad almeno una pratica di tirocinio/frequenza non possono essere eliminati.<br/><b>Nota bene (**):</b> un Soggetto Promotore disabilitato non potrà essere selezionato per creare una nuova convenzione.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'lperson_promoter_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Soggetti Promotore</li><li>aprire la pagina di Gestione delle Segreterie/Dipartimenti del Soggetto Promotore</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i dati anagrafici del Soggetto Promotore. E\' possibile modificare i dati e salvare le modifiche cliccando sul pulsante &quot;Salva&quot;'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>''
            )
        ),
        'lperson_promoter_branch_manage_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla pagina del Soggetto Promotore</li><li>aprire la pagina per l\'inserimento di una nuova Segreteria/Dipartimento</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene la sede legale e la lista delle segreterie/dipartimenti del Soggetto Promotore.<br/>Per disabilitare/abilitare una segr./dip. cliccare sul pulsante <div class=&quot;toggle btn btn-sm btn-success&quot; style=&quot;width: 48px; height: 29px;&quot;><button data-toggle=&quot;toggle&quot; button_checked=&quot;false&quot; class=&quot;btn form-submit&quot;></button><div class=&quot;toggle-group&quot;><label class=&quot;btn btn-success btn-sm toggle-on&quot;>Sì</label><label class=&quot;btn btn-default btn-sm active toggle-off&quot;>No</label><span class=&quot;toggle-handle btn btn-default btn-sm&quot;></span></div></div><br/>Per visualizzare/modificare i dati, le figure associate alla segr./dip. e i rispettivi ruoli cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;<br/>Per eliminare definitivamente una segr./dip. cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-trash&quot;&gt;&lt;/span&gt;<br/><b>Nota bene (*):</b> le segr./dip. che hanno delle figure associate o che sono in almeno una convenzione oppure in almeno una pratica di tirocinio/frequenza-volontaria non possono essere eliminate.<br/><b>Nota bene (**):</b> una segr./dip. disabilitata non potrà essere selezionata in una nuova convenzione.'            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'lperson_promoter_branch_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Soggetti Promotore</li><li>tornare alla pagina di Gestione Dipartimeni/Segreterie</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Nella scheda &quot;Dati anagrafici&quot; è possibile modificare i dati della segr./dip.'.'<br/>'.
                    'Nella scheda &quot;Figure&quot; è possibile gestire le figure associate alla segr./dip. e i ruoli che la figura può ricoprire in un tirocinio (tutor) per conto della segr./dip.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'agreement_list_view_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>aprire la pagina per la creazione di un nuova Convenzione</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene la lista della Convenzioni.<br/>E\' possibile:<ul class=&quot;intended&quot;><li>visualizzare/gestire/modificare una convenzione cliccando sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;</li><li>eliminare definitivamente una convenzione cliccando sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-trash&quot;&gt;&lt;/span&gt;</li></ul>Attenzione: le convenzioni con tirocini assegnati non possono essere eliminate.'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>'La tabella contiene il riepilogo dei Tirocini. Per visualizzare/modificare un tirocinio cliccare sul simbolo &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;'
            )
        ),
        'agreement_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista delle Convenzioni</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Riepilogo').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per l\'inserimento/modifica dei dati della Convenzione. Per salvare/modificare i dati inseriti cliccare sul pulsante &quot;Salva&quot;.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'person_list_view_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>aprire la pagina per la creazione di un nuova Figura</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene la lista delle Figure.<br/>Per disabilitare/abilitare una figura cliccare sul pulsante <div class=&quot;toggle btn btn-sm btn-success&quot; style=&quot;width: 48px; height: 29px;&quot;><button data-toggle=&quot;toggle&quot; button_checked=&quot;false&quot; class=&quot;btn form-submit&quot;></button><div class=&quot;toggle-group&quot;><label class=&quot;btn btn-success btn-sm toggle-on&quot;>Sì</label><label class=&quot;btn btn-default btn-sm active toggle-off&quot;>No</label><span class=&quot;toggle-handle btn btn-default btn-sm&quot;></span></div></div><br/>Per visualizzare/modificare i dati, i ruoli e le posizioni di una figura cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-pencil&quot;&gt;&lt;/span&gt;<br/>Per eliminare definitivamente una figura cliccare sul pulsante &lt;span class=&quot;btn glyphicon glyphicon-trash&quot;&gt;&lt;/span&gt;<br/><b>Nota bene (*):</b>: le figure associate ad un utente e/o inserite in una o più pratiche di tirocinio/frequenza con un ruolo attivo non possono essere eliminate.<br/><b>Nota bene (**):</b> una figura disabilitata non potrà essere selezionata per ricoprire un ruolo attivo in un/una tirocinio/frequenza.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'person_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista delle Figure</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Nella scheda &quot;Dati anagrafici&quot; è possibile modificare i dati della figura e l\'anagrafe di appartenenza.'.'<br/>'.
                    'Nella scheda &quot;Posizione&quot; è possibile gestire le posizioni della figura presso il Soggetto Ospitante.'.'<br/>'.
                    'Nella scheda &quot;Ruoli&quot; è possibile gestire i ruoli che la figura può ricoprire in un tirocinio (tutor, responsabile progetto formativo, referente, ecc.).'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'report_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene l\'elenco dei report.<br/>Per recarsi alla pagina del report desiderato cliccare sulla rispettiva voce.'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'tirocini_convenzione_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare all\'elenco dei Report</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'.'<br/>'.
                    'Per mostrare/nascondere colonne in tabella cliccare sul pulsante &quot;Mostra/Nascondi/Colonne&quot; e spuntare solo le colonne da mostrare'.'<br/>'.
                    '<b>Nota bene:</b> solo le colonne mostrate saranno esportate.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene il '.(!empty($form['fs_table_panel']['table']['#prefix'])?strip_tags($form['fs_table_panel']['table']['#prefix']):strtolower(drupal_get_title())).'.<br/>'.
                    'E\' possibile esportare i dati in formato <i>.csv</i> e in formato <i>.xlsx</i>'.'<br/>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'report_corso_frequentato_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare all\'elenco dei Report</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'.'<br/>'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene il '.(!empty($form['fs_table_panel']['table']['#prefix'])?strip_tags($form['fs_table_panel']['table']['#prefix']):strtolower(drupal_get_title())).'.<br/>'.
                    'E\' possibile esportare i dati in formato <i>.csv</i> e in formato <i>.xlsx</i>.'.'<br/>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'report_corso_frequentato_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare all\'elenco dei Report</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'.'<br/>'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene il report: '.(!empty($form['fs_table_panel']['table']['#prefix'])?strip_tags($form['fs_table_panel']['table']['#prefix']):strtolower(drupal_get_title())).'.<br/>'.
                    'E\' possibile esportare i dati in formato <i>.csv</i> e in formato <i>.xlsx</i>..'.'<br/>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'report_titolo_studio_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare all\'elenco dei Report</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'.'<br/>'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene il report: '.(!empty($form['fs_table_panel']['table']['#prefix'])?strip_tags($form['fs_table_panel']['table']['#prefix']):strtolower(drupal_get_title())).'.<br/>'.
                    'E\' possibile esportare i dati in formato <i>.csv</i> e in formato <i>.xlsx</i>.'.'<br/>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'elenco_tirocini_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare all\'elenco dei Report</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'.'<br/>'.
                    'Per mostrare/nascondere colonne in tabella cliccare sul pulsante &quot;Mostra/Nascondi/Colonne&quot; e spuntare solo le colonne da mostrare'.'<br/>'.
                    '<b>Nota bene</b>: solo le colonne mostrate saranno esportate.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene il report: '.(!empty($form['fs_table_panel']['table']['#prefix'])?strip_tags($form['fs_table_panel']['table']['#prefix']):strtolower(drupal_get_title())).'.<br/>'.
                    'E\' possibile esportare i dati in formato <i>.csv</i> e in formato <i>.xlsx</i>.'.'<br/>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'elenco_frequenze_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare all\'elenco dei Report</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'.'<br/>'.
                    'Per mostrare/nascondere colonne in tabella cliccare sul pulsante &quot;Mostra/Nascondi/Colonne&quot; e spuntare solo le colonne da mostrare'.'<br/>'.
                    '<b>Nota bene:</b> solo le colonne mostrate saranno esportate.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene il report: '.(!empty($form['fs_table_panel']['table']['#prefix'])?strip_tags($form['fs_table_panel']['table']['#prefix']):strtolower(drupal_get_title())).'.<br/>'.
                    'E\' possibile esportare i dati in formato <i>.csv</i> e in formato <i>.xlsx</i>.'.'<br/>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),
        'report_ore_tutor_form' => array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare all\'elenco dei Report</li></ul>'
            ),
            'top_panel' => array(
                'title'=>t('Filtro').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Per filtrare il contenuto della tabella sottostante selezionare i filtri desiderati e cliccare sul pulsante &quot;Filtra&quot;. Per azzerare i filtri cliccare sul pulsante &quot;Reset&quot;.'.'<br/>'.
                    'Per mostrare/nascondere colonne in tabella cliccare sul pulsante &quot;Mostra/Nascondi/Colonne&quot; e spuntare solo le colonne da mostrare'.'<br/>'.
                    '<b>Nota bene:</b> solo le colonne mostrate saranno esportate.'
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La tabella contiene il report: '.(!empty($form['fs_table_panel']['table']['#prefix'])?strip_tags($form['fs_table_panel']['table']['#prefix']):strtolower(drupal_get_title())).'.<br/>'.
                    'E\' possibile esportare i dati in formato <i>.csv</i> e in formato <i>.xlsx</i>.'.'<br/>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        ),

    );
    if (arg(1) == "new" || arg(2) == "new" || arg(3) == "new") {
        $help_form['user_form'] = array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista degli Utenti</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi per la creazione di un nuovo utente e l\'assegnazione dei permessi a partire da una figura già esistente all\'interno del sistema. E\' possibile salvare le modifiche cliccando sul pulsante &quot;Salva&quot;.'
            ),

        );
        $help_form['person_form'] = array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista delle Figure</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Tabella').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i campi da compilare per la creazione di una nuova Figura. Per salvare i dati inseriti cliccare sul pulsante &quot;Salva&quot;.'

            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        );
        $help_form['lperson_promoter_form'] = array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Soggetti Promotore</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera contiene i dati anagrafici del Soggetto Promotore. E\' possibile inserire i dati e salvare le modifiche cliccando sul pulsante &quot;Salva&quot;'
            ),
            'actions_panel' => array(
                'title'=>'titolo',
                'content'=>''
            )
        );
        $help_form['lperson_host_branch_form'] = array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla pagina di Gestione Strutture</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera permette di inserire i dati di una nuova struttura. E\' possibile salvare le modifiche cliccando sul pulsante &quot;Salva &quot;.'.'<br/>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        );
        $help_form['lperson_promoter_branch_form'] = array(
            'nav_panel' => array(
                'title'=>t('Navigazione:').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'Cliccando sugli appositi pulsanti è possibile:<ul class=&quot;intended&quot;><li>tornare alla Dashboard</li><li>tornare alla lista dei Soggetti Promotore</li><li>tornare alla pagina di Gestione Segreterie / Dipartimenti</li></ul>'
            ),
            'top_panel' => array(
                'title'=>'',
                'content'=>''
            ),
            'main_panel' => array(
                'title'=>t('Maschera').' '.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()),
                'content'=>'La maschera permette di inserire i dati di un/una nuovo/a Dipartimento/Segreteria. E\' possibile salvare le modifiche cliccando sul pulsante &quot;Salva &quot;.'.'<br/>'
            ),
            'actions_panel' => array(
                'title'=>'',
                'content'=>''
            )
        );
    }
    $output = '';
    $output .= '<div class="row">';
    $output .= '<div class="col-md-12 form-container">';
    $output .= '<fieldset class="panel panel-default form-wrapper" id="edit-fs-'.str_replace('_','-',$form['#form_id']).'">';
    $output .= '<legend class="panel-heading bootstro" id="edit-'.str_replace('_','-',$form['#form_id']).'-heading" data-bootstro-title="@nav_panel_title" data-bootstro-content="@nav_panel_content" data-bootstro-width="600px" data-bootstro-placement="bottom">
                 <div style="float:left">
                 <span class="panel-title fieldset-legend">'.(!empty($options['page_title'])?$options['page_title']:drupal_get_title()).'</span>
                 </div>
                 <div style="float:right">'.drupal_render($form['nav']).'</div>
                </legend>';
    $output .= '<div class="panel-body bootstro" id="edit-'.str_replace('_','-',$form['#form_id']).'-body" data-bootstro-title="@main_panel_title" data-bootstro-content="@main_panel_content" data-bootstro-width="600px" data-bootstro-placement="bottom">';
    if (!empty($header_content)) {
        foreach($header_content AS $item) {
            if (!empty($item['html'])) {
                if(!empty($help_form[$form['form_id']['#value']]['top_panel']['content']))
                    $output .= '<div class="panel-body bootstro" data-bootstro-title="@top_panel_title" data-bootstro-content="@top_panel_content" data-bootstro-width="600px" data-bootstro-placement="bottom" style="padding:0">';
                else
                    $output .= '<div class="panel-body" style="padding:0">';

                $output .= $item['html'];
                $output .= '</div>';
                if (!empty($item['has_separator'])) {
                    $output .= '<hr/>';
                }
            }
        }
    }
    foreach ($form AS $key_form => $item_form) {
        if (strpos($key_form, 'fs_') !== false) {
            $output .= '<div>';
            if (!empty($options['show_fs_title'])) {
                if (!empty($item_form['#title'])) {
                    $form[$key_form]['#title'] = '<legend class="panel-heading-2"><span class="panel-title">' . $form[$key_form]['#title'] . '</span></legend>';
                    $form[$key_form]['#prefix'] = '<div id="' . $key_form . '" style="padding:10px;">';
                    $form[$key_form]['#suffix'] = '</div>';
                    $output .= $form[$key_form]['#title'];
                }
            }
            $output .= '<div style="padding:5px">';
            $output .= drupal_render($form[$key_form]);
            $output .= '</div>';
            $output .= '</div>';
        }
    }
    $output .= '<hr/>';
    $output .= '<div style="text-align:right">'.drupal_render($form['actions']).'</div>';
    $output .= '</div>';
    $output .= '</fieldset>';
    $output .= drupal_render_children($form);
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output = strtr(
        $output,
        array(
            '@nav_panel_title' => $help_form[$form['form_id']['#value']]['nav_panel']['title'],
            '@nav_panel_content' => $help_form[$form['form_id']['#value']]['nav_panel']['content'],
            '@top_panel_title' => $help_form[$form['form_id']['#value']]['top_panel']['title'],
            '@top_panel_content' => $help_form[$form['form_id']['#value']]['top_panel']['content'],
            '@main_panel_title' => $help_form[$form['form_id']['#value']]['main_panel']['title'],
            '@main_panel_content' => $help_form[$form['form_id']['#value']]['main_panel']['content']
        )
    );

    return $output;
}


/**
 * @param $v
 * @param string $dec
 * @return float
 */
function floatvaldec($v, $dec=',') {
    return floatval(str_replace(',','.',str_replace('.','',$v)));
}

/**
 * Date range
 *
 * @param $first
 * @param $last
 * @param string $step
 * @param string $format
 * @return array
 */
function dateRange( $first, $last, $step = '+1 day', $format = 'Y-m-d' ) {
    $dates = [];
    $current = strtotime( $first );
    $last = strtotime( $last );

    while( $current <= $last ) {

        $dates[] = date( $format, $current );
        $current = strtotime( $step, $current );
    }

    return $dates;
}


/**
 * @param $arr
 * @return array
 * usata in internship_attendance
 */
function processArray($arr) {
    $arr2 = array();
    foreach ($arr as $key => $array) {
        foreach ($array as $key2 => $array2) {
            $arr2[$key][$key2] = $key2;
            unset($arr2[$key]['data']);
        }
    }
    return $arr2;
}


/**
 * @param $arr
 * @return array
 * usata in ore_tutor e presenze servizio
 */
function processTimeKeys($arr) {
    $arr2 = array();
    foreach ($arr as $key => $array) {
        foreach ($array as $key2 => $array2) {
            if (is_array($array2))
                $arr2[$key][$key2] = $array2;
        }
    }
    return $arr2;
}

/**
 * @param $time
 * @return float|int
 * questa funzione è usata nel caso di calcolo delle ore a partire da formati sbagliati ad esempio 8 invece di 08:00 (sostituisce strtotime)
 */
function time_to_decimal($time) {
    $timeArr = explode(':', $time);
    $decTime = ($timeArr[0]*60) + ($timeArr[1]) + ($timeArr[2]/60);
    return $decTime;
}

/**
 * @param $form
 */
function formReadOnly(&$form) {
    foreach($form as $name => $item){
        if(isset($item['#type']) && $name <> 'back' ){
            $form[$name]['#disabled'] = true;
        } elseif (isset($item['#type']) && $name == 'back'){
            $form[$name]['#description'] = t('Indietro');
            $form[$name]['#value'] = t('Indietro');
        }
    }
    unset($form['submit']);
}

/**
 * @param $session_name
 * @param null $default
 * @return null
 */
function session_get($session_name, $default = null) {
    if (isset($_SESSION[$session_name])) {
        return $_SESSION[$session_name];
    }
    return $default;
}

/**
 * @param $session_name
 * @param $session_value
 */
function session_set($session_name, $session_value) {
    $_SESSION[$session_name] = $session_value;
}

/**
 * Generica ormattazione stringhe
 * @param $string
 * @return mixed
 */
function _strformat($string) {
    return $string;
}

/**
 * Sostituisce le lettere speciali e accentate
 * @param $str
 * @return mixed
 */
function remove_accent($str)
{
    $a = array('À', 'Á', 'Â', 'Ã', 'Ä', 'Å', 'Æ', 'Ç', 'È', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', 'Ø', 'Ù', 'Ú', 'Û', 'Ü', 'Ý', 'ß', 'à', 'á', 'â', 'ã', 'ä', 'å', 'æ', 'ç', 'è', 'é', 'ê', 'ë', 'ì', 'í', 'î', 'ï', 'ñ', 'ò', 'ó', 'ô', 'õ', 'ö', 'ø', 'ù', 'ú', 'û', 'ü', 'ý', 'ÿ', 'Ā', 'ā', 'Ă', 'ă', 'Ą', 'ą', 'Ć', 'ć', 'Ĉ', 'ĉ', 'Ċ', 'ċ', 'Č', 'č', 'Ď', 'ď', 'Đ', 'đ', 'Ē', 'ē', 'Ĕ', 'ĕ', 'Ė', 'ė', 'Ę', 'ę', 'Ě', 'ě', 'Ĝ', 'ĝ', 'Ğ', 'ğ', 'Ġ', 'ġ', 'Ģ', 'ģ', 'Ĥ', 'ĥ', 'Ħ', 'ħ', 'Ĩ', 'ĩ', 'Ī', 'ī', 'Ĭ', 'ĭ', 'Į', 'į', 'İ', 'ı', 'Ĳ', 'ĳ', 'Ĵ', 'ĵ', 'Ķ', 'ķ', 'Ĺ', 'ĺ', 'Ļ', 'ļ', 'Ľ', 'ľ', 'Ŀ', 'ŀ', 'Ł', 'ł', 'Ń', 'ń', 'Ņ', 'ņ', 'Ň', 'ň', 'ŉ', 'Ō', 'ō', 'Ŏ', 'ŏ', 'Ő', 'ő', 'Œ', 'œ', 'Ŕ', 'ŕ', 'Ŗ', 'ŗ', 'Ř', 'ř', 'Ś', 'ś', 'Ŝ', 'ŝ', 'Ş', 'ş', 'Š', 'š', 'Ţ', 'ţ', 'Ť', 'ť', 'Ŧ', 'ŧ', 'Ũ', 'ũ', 'Ū', 'ū', 'Ŭ', 'ŭ', 'Ů', 'ů', 'Ű', 'ű', 'Ų', 'ų', 'Ŵ', 'ŵ', 'Ŷ', 'ŷ', 'Ÿ', 'Ź', 'ź', 'Ż', 'ż', 'Ž', 'ž', 'ſ', 'ƒ', 'Ơ', 'ơ', 'Ư', 'ư', 'Ǎ', 'ǎ', 'Ǐ', 'ǐ', 'Ǒ', 'ǒ', 'Ǔ', 'ǔ', 'Ǖ', 'ǖ', 'Ǘ', 'ǘ', 'Ǚ', 'ǚ', 'Ǜ', 'ǜ', 'Ǻ', 'ǻ', 'Ǽ', 'ǽ', 'Ǿ', 'ǿ');
    $b = array('A', 'A', 'A', 'A', 'A', 'A', 'AE', 'C', 'E', 'E', 'E', 'E', 'I', 'I', 'I', 'I', 'D', 'N', 'O', 'O', 'O', 'O', 'O', 'O', 'U', 'U', 'U', 'U', 'Y', 's', 'a', 'a', 'a', 'a', 'a', 'a', 'ae', 'c', 'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i', 'n', 'o', 'o', 'o', 'o', 'o', 'o', 'u', 'u', 'u', 'u', 'y', 'y', 'A', 'a', 'A', 'a', 'A', 'a', 'C', 'c', 'C', 'c', 'C', 'c', 'C', 'c', 'D', 'd', 'D', 'd', 'E', 'e', 'E', 'e', 'E', 'e', 'E', 'e', 'E', 'e', 'G', 'g', 'G', 'g', 'G', 'g', 'G', 'g', 'H', 'h', 'H', 'h', 'I', 'i', 'I', 'i', 'I', 'i', 'I', 'i', 'I', 'i', 'IJ', 'ij', 'J', 'j', 'K', 'k', 'L', 'l', 'L', 'l', 'L', 'l', 'L', 'l', 'l', 'l', 'N', 'n', 'N', 'n', 'N', 'n', 'n', 'O', 'o', 'O', 'o', 'O', 'o', 'OE', 'oe', 'R', 'r', 'R', 'r', 'R', 'r', 'S', 's', 'S', 's', 'S', 's', 'S', 's', 'T', 't', 'T', 't', 'T', 't', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'W', 'w', 'Y', 'y', 'Y', 'Z', 'z', 'Z', 'z', 'Z', 'z', 's', 'f', 'O', 'o', 'U', 'u', 'A', 'a', 'I', 'i', 'O', 'o', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'A', 'a', 'AE', 'ae', 'O', 'o');
    return str_replace($a, $b, $str);
}

/**
 * Genera lo slug: rimuove caratteri speciali e sostituisce gli spazi con trattino
 * @param $str
 * @return string
 */
function post_slug($str)
{
    return strtolower(preg_replace(array('/[^a-zA-Z0-9 -]/', '/[ -]+/', '/^-|-$/'),
        array('', '-', ''), remove_accent($str)));
}

/**
 * Verifica il Codice Fiscale in base al carattere di controllo
 * @param $cf
 * @return bool
 */
function ControlloCodiceFiscale($cf){
    if( $cf == '' )  return false;
    if( strlen($cf) != 16 )
        return false;
    $cf = strtoupper($cf);
    if( ! preg_match("/^[A-Z0-9]+$/", $cf) ){
        return false;
    }
    $s = 0;
    for( $i = 1; $i <= 13; $i += 2 ){
        $c = $cf[$i];
        if( '0' <= $c && $c <= '9' )
            $s += ord($c) - ord('0');
        else
            $s += ord($c) - ord('A');
    }
    for( $i = 0; $i <= 14; $i += 2 ){
        $c = $cf[$i];
        switch( $c ){
            case '0':  $s += 1;  break;
            case '1':  $s += 0;  break;
            case '2':  $s += 5;  break;
            case '3':  $s += 7;  break;
            case '4':  $s += 9;  break;
            case '5':  $s += 13;  break;
            case '6':  $s += 15;  break;
            case '7':  $s += 17;  break;
            case '8':  $s += 19;  break;
            case '9':  $s += 21;  break;
            case 'A':  $s += 1;  break;
            case 'B':  $s += 0;  break;
            case 'C':  $s += 5;  break;
            case 'D':  $s += 7;  break;
            case 'E':  $s += 9;  break;
            case 'F':  $s += 13;  break;
            case 'G':  $s += 15;  break;
            case 'H':  $s += 17;  break;
            case 'I':  $s += 19;  break;
            case 'J':  $s += 21;  break;
            case 'K':  $s += 2;  break;
            case 'L':  $s += 4;  break;
            case 'M':  $s += 18;  break;
            case 'N':  $s += 20;  break;
            case 'O':  $s += 11;  break;
            case 'P':  $s += 3;  break;
            case 'Q':  $s += 6;  break;
            case 'R':  $s += 8;  break;
            case 'S':  $s += 12;  break;
            case 'T':  $s += 14;  break;
            case 'U':  $s += 16;  break;
            case 'V':  $s += 10;  break;
            case 'W':  $s += 22;  break;
            case 'X':  $s += 25;  break;
            case 'Y':  $s += 24;  break;
            case 'Z':  $s += 23;  break;
        }
    }
    if( chr($s%26 + ord('A')) != $cf[15] )
        return false;
    return true;
}


/**
 * Funzione chiamata quando un file viene scaricato, aumenta il contatore "file_usage"
 * @param $form
 * @param $form_state
 */
function download_attachment_submit($form, &$form_state) {
    $id_internship_attachment = $form_state['clicked_button']['#attributes']['id_internship_attachment'];
    $fid = $form_state['clicked_button']['#attributes']['fid'];
    $file = file_load($fid);
    file_usage_add($file, 'getif','internship_attachment',$id_internship_attachment);
    drupal_goto('download/',array('query' => array('fid' => $fid), 'html' => TRUE));
}

/**
 * Funzione per il redirect verso la Dashboard
 * @param $form
 * @param $form_state
 */
function goto_dashboard ($form, &$form_state) {
    getif_goto('',array(),302,true);
}

/**
 * Funzione generica per il redirect verso la pagina di livello 1 (list-view)
 * @param $form
 * @param $form_state
 */
function goto_list ($form, &$form_state) {
    $list_name = $form_state['clicked_button']['#attributes']['list_name'];
    getif_goto($list_name.'/list',array(),302,true);
}

/**
 * Funzione per il riconoscimento di una data valida
 * @param $date
 * @param string $format
 * @return bool
 */
function isValidDate($date, $format= 'd-m-Y'){
    return $date == date($format, strtotime($date));
}

/**
 * Funzione per la pulizia dei nomi
 * @param $name
 * @return string
 */
function clean_name($name) {
    return strtolower(preg_replace(array('/[^a-zA-Z0-9 &-\']/', '/[\']+/','/[à]+/','/[èé]+/','/[ì]+/','/[ò]+/','/[ù]+/','/[À]+/','/[ÈÉ]+/','/[Ì]+/','/[Ò]+/','/[Ù]+/'),
        array('','\'', 'a\'','e\'','i\'','o\'','u\'','A\'','E\'','I\'','O\'','U\''), $name));
}

/**
 * Funzione per la pulizia degli username
 * @param $user_name
 * @return string
 */
function clean_user_name($user_name) {
    return strtolower(preg_replace(array('/[^a-zA-Z0-9.-_ ]/', '/[-_ ]+/'),
        array('', '.'), remove_accent($user_name)));
}

/**
 * @param $menu_tree
 * @param bool $is_submenu
 * @param $link_path_curr
 * @return string
 */
function render_menu_tree($menu_tree, $is_submenu = FALSE, $link_path_curr) {
    global $base_url;
    if (!$is_submenu)
        $output = '<ul class="menu nav">';
    else
        $output = '<ul class="dropdown-menu">';
    $active = 'active';
    foreach ($menu_tree as $key => $link) {
        if(!$link['link']['hidden']) {
            $term1 = explode('/',$link['link']['link_path'])[0];
            if (substr($link_path_curr,0,6) == 'person' && !empty($_GET['is_intern'])) {
                if ($term1 == 'intern') {
                    $class = $active;
                    $active = '';
                } else
                    $class = '';
            } elseif (substr($link_path_curr,0,6) == 'person' && !empty($_GET['is_voluntary'])) {
                if ($term1 == 'vintern') {
                    $class = $active;
                    $active = '';
                } else
                    $class = '';
            } else {
                if ($link_path_curr == $term1 || substr($link_path_curr, 0, strlen($term1)) == $term1) {
                    $class = $active;
                    $active = '';
                } else
                    $class = '';
            }
            $output .= '<li>';
            $link_path = '#';
            $link_title = $link['link']['link_title'];
            if($link['link']['link_path']) {
                $link_path = drupal_get_path_alias($link['link']['link_path']);
            }
            if(count($link['below']) > 0) {
                $output .= '<a class ="'.$class.'" href="'.base_path(). $link_path .'" title="'.$link_title.'">'.$link_title.'<span></span></a>';
            } else {
                $output .= '<a class ="'.$class.'" href="'.base_path(). $link_path . '">' . $link_title . '</a>';
            }
            $output .= '</li>';
        }
    }
    $output .= '</ul>';
    return $output;
}


/**
 * funzione che scansiona il form
 * @param $form
 * @param callable $callback
 */
function _iterate_form(&$form, callable $callback) {
    foreach (element_children($form) as $key) {
        $element = &$form[$key];
        $children = array_intersect_key($element, array_flip(element_children($element)));
        if (empty($children)) {
            call_user_func_array($callback, array(&$element, $key));
        }
        else {
            _iterate_form($element, $callback);
        }
    }
}

/**
 * Funzione di Redirect
 * @param string $path
 * @param array $options
 * @param int $http_response_code
 * @param bool $is_wizard
 */
function getif_goto($path = '', array $options = array(), $http_response_code = 302, $is_wizard = false) {
    if ($is_wizard) {
        session_set('prev',drupal_get_destination()["destination"]);
    }
    drupal_goto($path,$options,$http_response_code);
}


/**
 * Funzione per riordinare un array
 * @param $array
 * @return mixed
 */
function reorder_array($array) {
    $items = $array;
    unset($array);
    $i = 0;
    foreach ($items as $key => $item) {
        $array[$i] = $item;
        $i++;
    }
    return($array);
}


/**
 * Funzione di calcolo della differenza in giorni
 * @param $d1
 * @param $d2
 * @return int
 */
function getDaysDiff($d1, $d2) {
    return (int)round((strtotime($d2)-strtotime($d1))/86400);
}

/**
 * Funzione per il formato (unità di misura) della dimensione di un file
 * @param int $bytes Number of bytes (eg. 25907)
 * @param int $precision [optional] Number of digits after the decimal point (eg. 1)
 * @return string Value converted with unit (eg. 25.3KB)
 */
function formatBytes($bytes, $precision = 2) {
    $unit = ["B", "kB", "MB", "GB"];
    $exp = floor(log($bytes, 1024)) | 0;
    return round($bytes / (pow(1024, $exp)), $precision).' '.$unit[$exp];
}

/*** ******************** ***/
/***        Controls      ***/
/*** ******************** ***/
/**
 * Verifica che il tirocinante/frequentatore abbia già un tirocinio o frequenza programmata o in corso
 * @param $id_intern
 * @return int
 */
function check_intern_internship_active($id_intern) {
    db_set_active('getif_data');
    $query = db_select('internship_person','t1');
    $query->fields('t1');
    $query->innerJoin('internship_state','t2','t1.id_internship = t2.id_internship');
    $query->where('t1.id_person = '.$id_intern.' AND t1.active = 1 AND t2.active = 1 AND t2.state NOT IN (0,7)');
    $result = $query->countQuery()->execute()->fetchField();
    db_set_active();
    return (intval($result));
}


/**
 * @param $id_internship_person
 * @return bool
 */
function check_vintern_fulfilled($id_internship_person) {
    $intern = getRecordById('internship_person', 'getif_data', $id_internship_person);

    foreach ($intern as $key=>$field) {
        if ($key != 'id_intern_type' && $key != 'meta_field' && $key != 'meta_field' && $key != 'attended_course' && $key != 'working_time' && $key != 'meta_attachment' && $key != 'position' && $key != 'date_upd' && is_null($field))
            return false;
    }
    return true;
}

/**
 * @param $id_internship_person
 * @return bool
 */
function check_intern_fulfilled($id_internship_person) {
    $intern = getRecordById('internship_person', 'getif_data', $id_internship_person);
    if (!empty($intern->id_intern_type) && $intern->id_intern_type == 1) { // dipendente
        if (empty($intern->working_time))
            return false;
    }
    foreach ($intern as $key=>$field) {
        if ($key != 'meta_field' && $key != 'working_time' && $key != 'meta_attachment' && $key != 'position' && $key != 'date_upd' && is_null($field))
            return false;
    }
    return true;
}

/** Validation **/
function getif_email_element_validate($element, &$form_state, $form) {
    if (!empty($element['#value']) && !valid_email_address($element['#value'])) {
        form_error($element, t('Please enter a valid email address.'));
    }
}

/**
 * @param $h_name
 * @return bool
 */
function isValidHost($h_name) {
    if ($h_name == '' || getHostIdByName($h_name) == 0) {
        return false;
    }
    return true;
}

/**
 * @param $p_name
 * @return bool
 */
function isValidPromoter($p_name) {
    if ($p_name == '' || getPromoterIdByName($p_name) == 0) {
        return false;
    }
    return true;
}

/**
 * Funzione di validazione delle email, formato *****@*****.***
 * @param $element
 * @param $form_state
 * @param $form
 */
function getif_phone_element_validate($element, &$form_state, $form) {
    if (!empty($element['#value']) && !ctype_digit($element['#value'])) {
        form_error($element, t('Please enter a valid phone number.'));
    }
}


/*** *************************** ***/
/***            GET METHODS      ***/
/** **************************** ***/

function getLMDuration($date_start,$date_end) {
    $d1 = new DateTime($date_start);
    $d2 = new DateTime($date_end);
    $month_start = date('Y-m-01',strtotime($date_start));
    $dms = new DateTime($month_start);
    $month_end = date('Y-m-t',strtotime($date_start));
    $dme = new DateTime($month_end);
    $n_month = 0;
    // mese 1
    if($d1 != $dms) { // se non è il primo del mese
        $diff_days = $d1->diff($dme)->days + 1; // bisogna contare anche il giorno di inizio
        $tot_days = cal_days_in_month(CAL_GREGORIAN, $d1->format('m'), $d1->format('Y'));
        $n_month += ($diff_days/$tot_days);
        $di = (new DateTime($month_start))->add(new DateInterval('P1M'));
    } else { // se è il primo del mese
        $di = (new DateTime($month_start));
    }
    // da 2...n-1 mesi
    while ($di->format('Y-m')  < $d2->format('Y-m')) {
        $di->add(new DateInterval('P1M'));
        $n_month ++;
    }
    // mese n
    if ($di->modify('last day of this month') == $d2) { // se è l'ultimo del mese
        $n_month++;
    } else { // se non è l'ultimo del mese
        $month_end = date('Y-m-t', strtotime($date_end));
        $dme = new DateTime($month_end);
        $diff_days = $d2->diff($dme)->days;
        $tot_days = cal_days_in_month(CAL_GREGORIAN, $d2->format('m'), $d2->format('Y'));
        $n_month += (1-($diff_days/$tot_days));
    }
    return $n_month;
}




/**
 * Restituisce la differenza in mesi tra due date passate per stringa in formato Y-m-d
 * @param $dt1
 * @param $dt2
 * @return float|int
 */
function getMonthsDiff($dt1, $dt2) {
    $d1 = new DateTime($dt1);
    $d2 = new DateTime($dt2);
    return ($d1->diff($d2)->m + ($d1->diff($d2)->y)*12);
}

/**
 * Genera il Riepilogo di Scheda FV.1 della Frequenza Volontaria
 * @param $internship
 * @return string
 */
function getVInternship1DataByInternshipObj(&$internship) {
    // Struttura Proponente
    $text = '';
    $text .= '<b>Frequenza volontaria</b>'.
        ' dal '.date('d-m-Y',strtotime($internship->date_start)).
        ' al '.date('d-m-Y',strtotime($internship->date_end)).'<br>';
    $text .= '<hr><div><b>Allegati:</b></div><br/>';
    return $text;
}

/**
 * Genera il Riepilogo di Scheda FV.2 della Frequenza Volontaria
 * @param $internship
 * @return string
 */
function getVInternship2DataByInternshipObj(&$internship) {
    $text = '';
    // STRUTTURE OGGETTO DELLA FREQUENZA E AUTORIZZAZIONE ALL’ ACCESSO DEI LABORATORI
    foreach ($internship->lperson AS $lperson) {
        if ($lperson->flg_primary == 1) {
            $lperson_text = '<b>Struttura primaria</b>: ' . $lperson->name . '<br/>';
        } else {
            $lperson_text = '<b>Struttura secondaria</b>: ' . $lperson->name . '<br/>';
        }
        // Laboratori
        $lperson_location_area_list = array();
        foreach ($internship->lperson_location_area as $lperson_location_area) {
            if ($lperson_location_area->id_lperson_parent == $lperson->id_lperson) {
                $lperson_location_area_list[] = $lperson_location_area->name;
            }
        }
        $lperson_text .= '<b>Laboratori Struttura</b>: ' . join($lperson_location_area_list, ', ');
        $text .= $lperson_text.'<br>';
    }
    $text .= '<hr><div><b>Allegati:</b></div><br/>';
    return $text;
}

/**
 * Genera il Riepilogo di Scheda Ti.3 del Tirocinio
 * @param $internship
 * @return string
 */
function getVInternship3DataByInternshipObj(&$internship) {
    $text = '';
    // Responsabile/Referente
    foreach ($internship->project_contacts as $project_contact) {
        $project_contact_text =
            _strformat($project_contact->firstname).' '._strformat($project_contact->lastname).' - '.
            _strformat($internship->lperson_primary->name);
        if ($project_contact->flg_primary)
            $text .= '<b>Responsabile</b>: '.$project_contact_text.'<br/>';
        else
            $text .= '<b>Referente</b>: '.$project_contact_text.'<br/>';
    }
    $text .=  '<b>Motivo della Frequenza</b>: '.$internship->note;
    $text .= '<hr><div><b>Allegati:</b></div><br/>';
    return $text;

}

/**
 * Genera il Riepilogo di Scheda Ti.4 del Tirocinio
 * @param $internship
 * @return string
 */
function getVInternship4DataByInternshipObj(&$internship) {
    $text = '';
    $rc_policy = json_decode($internship->insurance->rc_policy);
    $text .= '<b>Compagnia RC</b>: '.$rc_policy->company.' - '.$rc_policy->policy_number.'<br/>';
    $accident_policy = json_decode($internship->insurance->accident_policy);
    $text .= '<b>Compagnia Assicurativa</b>: '.$accident_policy->company.' - '.$accident_policy->policy_number.'<br/>';
    $meta_flags = json_decode($internship->meta_flags);
    $text .= '<b>Formazione generale c/o</b>: Soggetto '.(($meta_flags->flag1_lprole == 1)?'Altro':'Ospitante').'<br/>';
    $text .= '<b>Formazione specifica c/o</b>: Soggetto '.(($meta_flags->flag2_lprole == 1)?'Altro':'Ospitante').'<br/>';
    $text .= '<b>Sorveglianza sanitaria c/o</b>: Soggetto '.(($meta_flags->flag3_lprole == 1)?'Altro':'Ospitante').'<br/>';
    return $text;
}


/**
 * Genera il Riepilogo dei dati del Tirocinante all'interno di Scheda Ti.1 e Ti.2 del Tirocinio
 * @param $internship
 * @return string
 */
function getVInternDataByInternshipObj(&$internship) {
    // Tirocinante
    $intern_name = ucwords($internship->person->firstname).' '.ucwords($internship->person->lastname);
    $text = '<b>Nome</b>: '.$intern_name.'<br />';
    $text .= '<b>Codice Fiscale</b>: '.$internship->person->tax_code.'<br>';
    $text .= '<b>Nato/a a</b>: '.ucwords($internship->person->birthplace).' <b>il giorno</b> '.date('d-m-Y',strtotime($internship->person->birthdate)).'<br/>';
    if (!empty($internship->person->residence_address)) {
        $text .= '<b>Residente a</b>: '.ucwords($internship->person->residence_address).'<br/>';
        $text .= '<b>Domiciliato/a</b>: ';
        if (!empty($internship->person->domicile_address)) {
            $text .= ucwords($internship->person->domicile_address) . '<br/>';
        } else {
            $text .= ucwords($internship->person->residence_address) . '<br/>';
        }
    }
    $text .= !empty($internship->person->phone)?'<b>Telefono</b>: '.$internship->person->phone.'<br/>':'';
    $text .= !empty($internship->person->email_address)?'<b>Email</b>: '.strtolower($internship->person->email_address).'<br/>':'';
    $text .= !empty($internship->person->email_address)?'<b>Titolo di studio</b>: '.ucwords(strtolower($internship->person->qualification)).
        (!empty($internship->person->qualification_detail)?' ('.$internship->person->qualification_detail.')':'').'<br/>':'';
    if (!empty($internship->person->attended_course)) {
        $attended_course = json_decode($internship->person->attended_course);
        if (!empty($attended_course)) {
            if (!empty($attended_course->name)) {
                $text .= '<b>Corso di studi in frequenza</b>: ' . $attended_course->name . '<br/>';
            }
        }
    }
    return $text;
}

/**
 * Restituisce info Tirocinio usate in Gestione Tirocinio
 * @param $id_internship
 * @return string
 */
function getVInternshipInformation(&$internship) {
    $text = 'Inizio previsto: '.date('d-m-Y',strtotime($internship->date_start)).'<br/>';
    $text .= 'Fine prevista: '.date('d-m-Y',strtotime($internship->date_end)).'<br/>';

    if ($internship->internship_state->state >= 5 || $internship->internship_state->state == 0) {
        $date_start_effective = $internship->internship_state->date_start;

        $datetime1 = new DateTime($internship->date_start);
        $datetime2 = new DateTime($internship->date_end);
        $interval = $datetime1->diff($datetime2);
        $date_end_effective = $internship->date_end;

        $text .= 'Inizio effettivo: ' . date('d-m-Y', strtotime($date_start_effective)) . '<br/>';
        if ($internship->internship_state->state != 7)
            $text .= 'Fine effettiva attesa: ' . date('d-m-Y', strtotime($date_end_effective)) . '<br/>';
        else {
            $text .= 'Fine programmata: ' . date('d-m-Y', strtotime($date_end_effective)) . '<br/>';
        }
        if (!empty($internship->internship_state->date_extension)) { // Proroga
            $text .= 'Prorogato fino a: '.date('d-m-Y',strtotime($internship->internship_state->date_extension)). '<br/>';
        }
        if ($internship->internship_state->state == 7) { // Proroga
            $text .= 'Concluso il: '.date('d-m-Y',strtotime($internship->internship_state->date_end)). '<br/>';
        } elseif ($internship->internship_state->state == 0) {
            $text .= 'Interrotto il: '.date('d-m-Y',strtotime($internship->internship_state->date_end)). '<br/>';
        }
    }
    return $text;
}

/**
 * Genera il Riepilogo di Scheda Ti.1 del Tirocinio
 * @param $internship
 * @return string
 */
function getInternship1DataByInternshipObj(&$internship) {
    // Struttura Proponente
    $text = '';

    $text .= '<b>Tirocinio</b> '.(($internship->internship_type->flg_extra_curricular)?t('extracurricolare'):t('curricolare')).
        ' dal '.date('d-m-Y',strtotime($internship->date_start)).
        ' al '.date('d-m-Y',strtotime($internship->date_end)).
        ' con motivo: '.'<br/>'.
        '"<i>'.$internship->internship_type->description.'</i>"<br/>';
    $text .= '<b>Convenzione</b> N. '.$internship->agreement->number_code.
        ' dal '.date('d-m-Y',strtotime($internship->agreement->date_start)).
        ' al '.date('d-m-Y',strtotime($internship->agreement->date_end)).
        '</br>';
    $promoter_text = '';
    if (!empty($internship->promoter->parent)) {
        $promoter_text .= _strformat($internship->promoter->parent->name);
        if ($internship->promoter->id_lperson != $internship->promoter->parent->id_lperson) {
            $promoter_text .= ' - '._strformat($internship->promoter->name);
        }
    } else {
        $promoter_text .= _strformat($internship->promoter->name);
    }
    $text .= '<b>Soggetto Promotore</b>: '.$promoter_text.'<br/>';
    $host_text = '';
    if (!empty($internship->host->parent)) {
        $host_text .= _strformat($internship->host->parent->name);
        if ($internship->promoter->id_lperson != $internship->host->parent->id_lperson) {
            $host_text .= ' - '._strformat($internship->host->name);
        }
    } else {
        $host_text .= _strformat($internship->host->name);
    }
    $text .= '<b>Soggetto Ospitante</b>: '.$host_text.'<br/>';
    $text .= '<hr><div><b>Allegati:</b></div><br/>';
    return $text;
}

/**
 * Genera il Riepilogo di Scheda Ti.2 del Tirocinio
 * @param $internship
 * @return string
 */
function getInternship2DataByInternshipObj(&$internship) {
    $text = '';
    // STRUTTURE OGGETTO DELLA FREQUENZA E AUTORIZZAZIONE ALL’ ACCESSO DEI LABORATORI
    foreach ($internship->lperson AS $lperson) {
        if ($lperson->flg_primary == 1) {
            $lperson_text = '<b>Struttura primaria</b>: ' . $lperson->name . '<br/>';
        } else {
            $lperson_text = '<b>Struttura secondaria</b>: ' . $lperson->name . '<br/>';
        }
        // Laboratori
        $lperson_location_area_list = array();
        foreach ($internship->lperson_location_area as $lperson_location_area) {
            if ($lperson_location_area->id_lperson_parent == $lperson->id_lperson) {
                $lperson_location_area_list[] = $lperson_location_area->name;
            }
        }
        $lperson_text .= '<b>Laboratori Struttura</b>: ' . join($lperson_location_area_list, ', ');
        $text .= $lperson_text.'<br>';
    }
    if ($internship->internship_type->flg_extra_curricular) {
        // Budget
        $text .= '<b>Budget mensile</b>: '.money_format('%.2n',$internship->budget->m_amount);
    }
    $text .= '<hr><div><b>Allegati:</b></div><br/>';
    return $text;
}

/**
 * Genera il Riepilogo di Scheda Ti.3 del Tirocinio
 * @param $internship
 * @return string
 */
function getInternship3DataByInternshipObj(&$internship) {
    $text = '';
    // TUTOR SOGGETTO PROMOTORE
    $text .=  '<b>Tutor Soggetto Promotore</b>: '.
        _strformat($internship->promoter->tutor->firstname).' '._strformat($internship->promoter->tutor->lastname).'<br/>';
    // TUTORI SOGGETTO OSPITANTE
    foreach ($internship->host->tutor as $host_tutor) {
        $host_tutor_text =
            _strformat($host_tutor->firstname).' '._strformat($host_tutor->lastname).' - '.
            (!empty($host_tutor->position)?_strformat($host_tutor->position).'</br>':'').
            _strformat($host_tutor->lperson_name);
        if ($host_tutor->flg_primary)
            $text .= '<b>Tutor Soggetto Ospitante</b>: '.$host_tutor_text.'<br/>';
        else
            $text .= '<b>Tutor Secondario Soggetto Ospitante</b>: '.$host_tutor_text.'<br/>';
    }

    foreach ($internship->project_contacts as $project_contact) {
        $project_contact_text =
            _strformat($project_contact->firstname).' '._strformat($project_contact->lastname).' - '.
            _strformat($internship->lperson_primary->name);
        if ($project_contact->flg_primary)
            $text .= '<b>Responsabile Progetto Formativo</b>: '.$project_contact_text.'<br/>';
        else
            $text .= '<b>Referente</b>: '.$project_contact_text.'<br/>';
    }
    $text .=  '<b>Progetto Formativo</b>: '.$internship->note;
    $text .= '<hr><div><b>Allegati:</b></div><br/>';
    return $text;

}

/**
 * Genera il Riepilogo di Scheda Ti.4 del Tirocinio
 * @param $internship
 * @return string
 */
function getInternship4DataByInternshipObj(&$internship) {
    $text = '';
    $rc_policy = json_decode($internship->insurance->rc_policy);
    $text .= '<b>Compagnia RC</b>: '.$rc_policy->company.' - '.$rc_policy->policy_number.'<br/>';
    $accident_policy = json_decode($internship->insurance->accident_policy);
    $text .= '<b>Compagnia Assicurativa</b>: '.$accident_policy->company.' - '.$accident_policy->policy_number.'<br/>';
    $meta_flags = json_decode($internship->meta_flags);
    $text .= '<b>Formazione generale c/o</b>: Ente '.(($meta_flags->flag1_lprole == 1)?'Promotore':'Ospitante').'<br/>';
    $text .= '<b>Formazione specifica c/o</b>: Ente '.(($meta_flags->flag2_lprole == 1)?'Promotore':'Ospitante').'<br/>';
    $text .= '<b>Sorveglianza sanitaria c/o</b>: Ente '.(($meta_flags->flag3_lprole == 1)?'Promotore':'Ospitante').'<br/>';
    return $text;
}

/**
 * Genera il Riepilogo dei dati del Tirocinante all'interno di Scheda Ti.1 e Ti.2 del Tirocinio
 * @param $internship
 * @return string
 */
function getInternDataByInternshipObj(&$internship, $flg_attachment = true) {
    // Tirocinante
    $intern_name = ucwords($internship->person->firstname).' '.ucwords($internship->person->lastname);
    $text = '<b>Nome</b>: '.$intern_name.'<br />';
    $text .= '<b>Codice Fiscale</b>: '.$internship->person->tax_code.'<br>';
    $text .= '<b>Nato/a a</b>: '.ucwords($internship->person->birthplace).' <b>il giorno</b> '.date('d-m-Y',strtotime($internship->person->birthdate)).'<br/>';
    if (!empty($internship->person->residence_address)) {
        $text .= '<b>Residente a</b>: '.ucwords($internship->person->residence_address).'<br/>';
        $text .= '<b>Domiciliato/a</b>: ';
        if (!empty($internship->person->domicile_address)) {
            $text .= ucwords($internship->person->domicile_address) . '<br/>';
        } else {
            $text .= ucwords($internship->person->residence_address) . '<br/>';
        }
    }
    $text .= !empty($internship->person->phone)?'<b>Telefono</b>: '.$internship->person->phone.'<br/>':'';
    $text .= !empty($internship->person->email_address)?'<b>Email</b>: '.strtolower($internship->person->email_address).'<br/>':'';
    $text .= !empty($internship->person->email_address)?'<b>Titolo di studio</b>: '.ucwords(strtolower($internship->person->qualification)).
        (!empty($internship->person->qualification_detail)?' ('.$internship->person->qualification_detail.')':'').'<br/>':'';
    if (!empty($internship->person->attended_course)) {
        $attended_course = json_decode($internship->person->attended_course);
        if (!empty($attended_course)) {
            $text .= '<b>Corso di studi in frequenza</b>: '.$attended_course->name.'<br/>';
            $text .= '<b>Indirizzo del corso di studio</b>: '.$attended_course->address.'<br/>';
            $text .= '<b>Annualità in corso</b>: '.$attended_course->ontime.'<br/>';
        }
    }
    if (!empty($internship->person->id_intern_type)) {
        if ($internship->person->id_intern_type == 1) { // dipendente
            $text .= '<b>Tipo Tirocinante</b>: dipendente</br>';
            $working_times = json_decode(  $internship->person->working_time );
            $text .= '<b>Orari dipendente</b>:<br/>';
            foreach($working_times as $key_wt => $working_time) {
                $text .= ucwords(strftime("%A", strtotime("Monday +{$key_wt} days"))).' da ';
                $text .= $working_time[0].' a ';
                $text .= $working_time[1];
                if (!empty($working_time[2])) {
                    $text .=' / da ';
                    $text .= $working_time[2].' a ';
                    $text .= $working_time[3];
                }
                $text .= '<br/>';
            }
        } elseif ($internship->person->id_intern_type == 2) { // Borsista
            $text .= '<b>Tipo Tirocinante</b>: borsista<br>';
            if ($flg_attachment) {
                $text .= '<hr><div><b>Allegati:</b></div><br/>';
            }
        } elseif ($internship->person->id_intern_type = 3) { // esterno
            $text .= '<b>Tipo Tirocinante</b>: esterno';
        }
    }
    return $text;
}

/**
 * Restituisce gli allegati di un tirocinio
 * @param $schema
 * @param $id_internship
 * @return mixed
 */
function getInternshipAttachmentsByInternshipId($schema, $id_internship) {
    db_set_active($schema);
    //attachments
    $elements = db_query("
        SELECT t1.*
        FROM `internship_attachment` AS t1
        INNER JOIN `internship` AS t2
        ON t1.id_internship = t2.id_internship
        WHERE t2.id_internship = ".$id_internship." AND t1.active = 1 AND t2.active = 1 ORDER BY t1.meta ASC;
    ");
    db_set_active();
    return  $elements->fetchAllAssoc('meta');
}

/**
 * Restituisce il tipo di Tirocinio (curricolare o extra)
 * @param $schema
 * @param $id_internship
 * @return mixed
 */
function getInternshipTypeByInternshipId($schema, $id_internship) {
    db_set_active($schema);
    // dettagli tipo tirocinio
    $elements = db_query("
        SELECT flg_extra_curricular
        FROM `lib_internship_type` AS t1
        INNER JOIN `internship` AS t2
        ON t1.id_internship_type = t2.id_internship_type
        WHERE t2.id_internship = ".$id_internship." AND t1.active = 1 AND t2.active = 1;
    ");
    db_set_active();
    return $elements->fetchField();
}

/**
 * Restituisce info Tirocinio usate in Gestione Tirocinio
 * @param $id_internship
 * @return string
 */
function getInternshipInformation($id_internship) {

    $internship = getInternshipById('getif_data',$id_internship,'active');
    // Tirocinante

    $text = 'Inizio previsto: '.date('d-m-Y',strtotime($internship->date_start)).'<br/>';
    $text .= 'Fine prevista: '.date('d-m-Y',strtotime($internship->date_end)).'<br/>';

    if ($internship->internship_state->state >= 5 || $internship->internship_state->state == 0) {
        $date_start_effective = $internship->internship_state->date_start;

        $datetime1 = new DateTime($internship->date_start);
        $datetime2 = new DateTime($internship->date_end);
        $interval = $datetime1->diff($datetime2);
        $date_end_effective = $internship->date_end;

        $text .= 'Inizio effettivo: ' . date('d-m-Y', strtotime($date_start_effective)) . '<br/>';
        if ($internship->internship_state->state != 7)
            $text .= 'Fine effettiva attesa: ' . date('d-m-Y', strtotime($date_end_effective)) . '<br/>';
        else {
            $text .= 'Fine programmata: ' . date('d-m-Y', strtotime($date_end_effective)) . '<br/>';
        }
        if (!empty($internship->internship_state->date_extension)) { // Proroga
            $text .= 'Prorogato fino a: '.date('d-m-Y',strtotime($internship->internship_state->date_extension)). '<br/>';
        }
        if ($internship->internship_state->state == 7) { // Concluso
            $text .= 'Concluso il: '.date('d-m-Y',strtotime($internship->internship_state->date_end)). '<br/>';
        } elseif ($internship->internship_state->state == 0) { // Interrotto
            $text .= 'Interrotto il: '.date('d-m-Y',strtotime($internship->internship_state->date_end)). '<br/>';
        }
    }
    return $text;
}

/**
 * Restituisce l'etichetta dello stato del Tirocinio (usato in getif.report_ore_tutor.inc)
 * @param $internship
 * @return string
 */
function getInternshipStateText(&$internship) {
    if ($internship->internship_state->state == 0) {
        return '<div class="btn-basic" style="padding:3px 7px">Interrotto</div>';
    }
    if ($internship->internship_state->state <= 4) {
        return '<div class="btn-warning" style="padding:3px 7px">In attesa</div>';
    }
    if (($internship->internship_state->state == 5 || $internship->internship_state->state == 6) && !empty($internship->internship_state->date_end)) {
        return '<div class="btn-danger" style="padding:3px 7px">Concluso (Non confermato)</div>';
    }
    if ($internship->internship_state->state == 5) {
        return '<div class="btn-success" style="padding:3px 7px">Avviato</div>';
    }
    if ($internship->internship_state->state == 6) {
        return '<div class="btn-success" style="padding:3px 7px">in corso con proroga</div>';
    }

    if ($internship->internship_state->state == 7) {
        return '<div class="btn-basic" style="padding:3px 7px">Concluso</div>';
    }
    return '';
}

/**
 * Restituisce l'etichetta dello stato della frequenza
 * @param $internship
 * @return string
 */
function getVInternshipStateText(&$internship) {
    if ($internship->internship_state->state == 0) {
        return '<div class="btn-basic" style="padding:3px 7px">Interrotta</div>';
    }
    if ($internship->internship_state->state <= 4) {
        return '<div class="btn-warning" style="padding:3px 7px">In attesa</div>';
    }
    if (($internship->internship_state->state == 5 || $internship->internship_state->state == 6) && !empty($internship->internship_state->date_end)) {
        return '<div class="btn-danger" style="padding:3px 7px">Conclusa (Non confermata)</div>';
    }
    if ($internship->internship_state->state == 5) {
        return '<div class="btn-success" style="padding:3px 7px">Avviate</div>';
    }
    if ($internship->internship_state->state == 6) {
        return '<div class="btn-success" style="padding:3px 7px">in corso con proroga</div>';
    }

    if ($internship->internship_state->state == 7) {
        return '<div class="btn-basic" style="padding:3px 7px">Conclusa</div>';
    }
    return '';
}

/**
 * Restituisce l'array con i Tipi di tirocinio
 * @param $lib
 * @param null $schema
 * @param null $field_name
 * @param null $field_value
 * @param null $exclude_id
 * @return array
 */
function getInternshipTypeOptions($lib, $schema = null, $field_name = null, $field_value = null, $exclude_id = null){
    $key = getPrimaryKeyTable($lib, $schema);
    //cambio schema
    db_set_active($schema);
    $query = "SELECT `id_".substr($lib,4)."` AS `id`,`description`, `flg_extra_curricular` FROM `{" . $lib . "}` WHERE `active`=1";
    if ($field_name != null && $field_value != null) {
        $query .= " AND ".$field_name." = '".$field_value."'";
    }
    if($exclude_id != null) {
        $query .= " AND $key != $exclude_id";
    }
    //trovo i record della tabella
    $lib_elements = db_query($query);
    //ritorno nello schema di default
    db_set_active();
    //costruisco l'array da ritornare
    $array_elements = array();
    foreach ($lib_elements as $lib_element)
    {
        $array_elements[$lib_element->flg_extra_curricular.'|'.$lib_element->id] =  $lib_element->description;
    }
    //ritorno;
    return $array_elements;
}

/**
 * Restituisce l'asterisco per le label dei campi obbligatori
 * @return string
 */
function getRequiredHtml() {
    return '<span class="form-required" title="This field is required.">*</span>';
}

/**
 * Restituisce 1 se la Convenzione accetta tirocini curriculari, 2 se extra-curriculari
 * @param $id_agreement
 * @return mixed
 */
function getAgreementCurricularFlg($id_agreement) {
    db_set_active('getif_data');
    $elements = db_query("
        SELECT internship_type
        FROM `agreement`
        WHERE id_agreement= ".$id_agreement.";
    ");
    db_set_active();
    return $elements->fetchAssoc()['internship_type'];

}

/**
 * Restituisce le Convenzioni di una coppia Soggetto Promotore/Ospitante individuati tramite ID
 * @param $promoter_id
 * @param $host_id
 * @return array
 */
function getAgreementsByHPIds($promoter_id, $host_id) {
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.*
        FROM `agreement` AS t1
        INNER JOIN `lperson_lprole` AS t2
        ON t1.id_host = t2.id_lperson_lprole AND t2.id_lprole = 2
        INNER JOIN `lperson_lprole` AS t3
        ON t1.id_promoter = t3.id_lperson_lprole AND t3.id_lprole = 1
        WHERE t1.id_host = ".(int)$host_id." AND t1.id_promoter = ".(int)$promoter_id." AND date(t1.date_end) > date(NOW()) AND
        (t1.active = 1 AND t2.active = 1 AND t3.active = 1);
    ");
    $options = array();
    while($result = $results->fetchObject()) {
        $options[$result->id_agreement] = $result->number_code;
    }
    db_set_active();
    return $options;
}

/**
 * Restituisce lo stato di un Tirocinio individuato tramite ID
 * @param $schema
 * @param $id_internship
 * @return mixed
 */
function getInternshipStateById($schema, $id_internship) {
    db_set_active($schema);
    $elements = db_query("
        SELECT state
        FROM `internship_state`
        WHERE `id_internship` = ".$id_internship." AND `active` = 1;
    ");
    $internship_state = $elements->fetchField();
    db_set_active();
    return $internship_state;
}

/**
 * Restituisce i dati aggregati di Convenzione, S. Promotore e S. Ospitante tramite ID di Convenzione
 * @param $schema
 * @param $agreement_id
 * @return mixed
 */
function getAgreementsById($schema, $agreement_id) {
    db_set_active($schema);
    $results = db_query("
        SELECT t1.*, t2.id_lperson_lprole AS host_id, t3.id_lperson_lprole AS promoter_id, t21.name as host, t31.name as promoter
        FROM `agreement` AS t1
        INNER JOIN `lperson_lprole` AS t2
        ON t1.id_host = t2.id_lperson_lprole AND t2.id_lprole = 2
        INNER JOIN `lperson` AS t21
        ON t21.id_lperson = t2.id_lperson
        INNER JOIN `lperson_lprole` AS t3
        ON t1.id_promoter = t3.id_lperson_lprole AND t3.id_lprole = 1
        INNER JOIN `lperson` AS t31
        ON t31.id_lperson = t3.id_lperson
        WHERE t1.id_agreement = ".(int)$agreement_id." AND
        (t1.active = 1 AND t2.active = 1 AND t3.active = 1);
    ");
    db_set_active();
    return $results->fetchAssoc();
}

/**
 * Restituisce i dati aggregati di una Frequenza Volontaria
 * @param null $schema
 * @param $id_internship
 * @param string $check
 * @return object
 */
function getVInternshipById($schema = null, $id_internship, $check = 'active') {
    db_set_active($schema);
    // tirocinio
    $elements = db_query("
        SELECT * FROM `internship` WHERE `id_internship` = ".$id_internship." and `active` = 1;
    ");
    $internship = (object)$elements->fetchAssoc();
    // stato
    $elements = db_query("
        SELECT t2.*
        FROM `internship` AS t1
        INNER JOIN `internship_state` AS t2
        ON t1.id_internship = t2.id_internship AND t1.id_internship = ".$id_internship." AND t1.active IN (1,2) AND t2.active IN (1,2);
    ");
    $internship_state = (object)$elements->fetchAssoc();
    $internship->internship_state = $internship_state;
    $date_start_effective = $internship->internship_state->date_start;
    if (empty($internship->internship_state->date_end)) {
        $datetime1 = new DateTime($internship->date_start);
        $datetime2 = new DateTime($internship->date_end);
        $interval = $datetime1->diff($datetime2);
        if (!empty($internship->internship_state->date_extension)) {
            $date_end_expected = $internship->internship_state->date_extension;
        } else {
            $date_end_expected = $internship->date_end;
        }
    } else {
        $date_end_expected = $internship->internship_state->date_end;
    }
    $internship->internship_state->date_end_expected = $date_end_expected;

    // dettagli base tirocinante
    $elements = db_query("
        SELECT t1.*,t2.*,t3.description AS title
        FROM `person` AS t1
        INNER JOIN `internship_person` AS t2
        ON t1.id_person = t2.id_person
        INNER JOIN `lib_title` AS t3
        ON t1.id_title = t3.id_title
        WHERE t2.id_internship = ".$internship->id_internship." AND t1.active IN (1,2) AND t2.active IN (1,2) AND t3.active IN (1,2);
    ");
    $person = (object)$elements->fetchAssoc();
    $internship->person = $person;

    // qualifica tirocinante
    $elements = db_query("
        SELECT t2.name AS qualification
        FROM `internship_person` AS t1
        LEFT JOIN `lib_qualification` AS t2
        ON t1.id_qualification =  t2.id_qualification
        WHERE t1.id_internship = ".$internship->id_internship." AND t1.active IN (1,2) AND t2.active IN (1,2);
    ");
    $qualification = $elements->fetchField();
    $internship->person->qualification = $qualification;

    // Soggetto Ospitante
    $elements = db_query("
        SELECT t1.*,t2.id_lperson_lprole
        FROM `lperson` AS t1
        JOIN `lperson_lprole` AS t2
        ON t1.id_lperson = t2.id_lperson
        WHERE t2.id_lperson = ".GETIF_HOST." AND t1.active IN (1,2) AND t2.active IN (1,2);
    ");
    $host = (object)$elements->fetchAssoc();
    $internship->host = $host;

    // Laboratori
    $elements = db_query("
        SELECT t1.*,t2.id_lperson,t2.name,t2.id_lperson_parent,t3.flg_primary as lperson_flg_primary
        FROM `internship_lperson_location_area` AS t1
        INNER JOIN `lperson` AS t2
        ON t1.id_lperson_location_area = t2.id_lperson
        INNER JOIN `internship_lperson` AS t3
        ON t3.id_lperson = t2.id_lperson_parent AND t3.id_internship = t1.id_internship
        WHERE t1.id_internship = ".$id_internship." AND t1.active IN (1,2) AND t2.active IN (1,2) AND t3.active IN (1,2);
    ");
    $internship_lperson_location_area = (object)$elements->fetchAll();
    $internship->lperson_location_area = $internship_lperson_location_area;

    // branches
    $elements = db_query("
        SELECT t1.*,t2.*
        FROM `internship_lperson` AS t1
        INNER JOIN `lperson` AS t2
        ON t1.id_lperson = t2.id_lperson
        WHERE t1.id_internship = ".$id_internship." AND t1.active IN (1,2) AND t2.active IN (1,2) ORDER BY flg_primary DESC;
    ");
    $internship_lperson = $elements->fetchAll(\PDO::FETCH_GROUP|\PDO::FETCH_UNIQUE|\PDO::FETCH_OBJ);

    $internship_lpersons = array();
    foreach ($internship_lperson AS $internship_lperson_item) {

        //location_area
        $elements = db_query("
            SELECT t1.*,t2.id_lperson,t2.name,t4.flg_primary as lperson_flg_primary
            FROM `internship_lperson_location_area` AS t1
            INNER JOIN `lperson` AS t2
            ON t1.id_lperson_location_area = t2.id_lperson AND t2.level = 2
            INNER JOIN `lperson` AS t3
            ON t2.id_lperson_parent = t3.id_lperson
            INNER JOIN `internship_lperson` AS t4
            ON t4.id_lperson = t3.id_lperson AND t4.id_internship = t1.id_internship
            WHERE t1.id_internship = " . $id_internship . " AND t3.id_lperson = ".$internship_lperson_item->id_lperson." AND t1.active IN (1,2) AND t2.active IN (1,2) AND t3.active IN (1,2) AND t4.active IN (1,2);
        ");
        $internship_lperson_location_area = $elements->fetchAll(\PDO::FETCH_GROUP|\PDO::FETCH_UNIQUE|\PDO::FETCH_OBJ);
        $internship_lperson_item->lperson_location_area = (object)$internship_lperson_location_area;
        $internship_lpersons[] = $internship_lperson_item;


    }
    $internship->lperson = (object)$internship_lpersons;

    // primary branch
    $elements = db_query("
        SELECT t1.*,t2.name
        FROM `internship_lperson` AS t1
        INNER JOIN `lperson` AS t2
        ON t1.id_lperson = t2.id_lperson
        WHERE t1.id_internship = ".$id_internship." AND t1.flg_primary = 1 AND t1.active IN (1,2) AND t2.active IN (1,2);
    ");
    $internship_lperson_primary = (object)$elements->fetchAssoc();
    $internship->lperson_primary = $internship_lperson_primary;


    //contact_person (Responsabile/Referenti)
    $elements = db_query("
        SELECT t1.flg_primary, t3.*,t4.*,t42.name AS lperson_name, t5.description as title
        FROM `internship_project_contact` AS t1
        INNER JOIN `internship` AS t2
        ON t2.id_internship = t1.id_internship
        INNER JOIN `person_lperson_prole` AS t3
        ON t3.id_person_lperson_prole = t1.id_person_lperson_prole
        INNER JOIN `person_lperson` AS t41
        ON t41.id_person_lperson = t3.id_person_lperson
        INNER JOIN `lperson` AS t42
        ON t42.id_lperson = t41.id_lperson
        INNER JOIN `person` AS t4
        ON t4.id_person = t41.id_person
        INNER JOIN `lib_title` AS t5
        ON t4.id_title = t5.id_title
        WHERE t2.id_internship = ".$id_internship." AND t1.active IN (1,2) AND t2.active IN (1,2) AND t3.active IN (1,2) AND t4.active IN (1,2) AND t42.active IN (1,2) AND t41.active IN (1,2) AND t5.active IN (1,2);
    ");
    $internship_project_contacts = (object)$elements->fetchAll();
    // Preleva la posizione del contatto. Nel caso ce ne fosse più di una preleva la prima
    foreach($internship_project_contacts as &$internship_project_contacts_item) {
        $elements = db_query("
              SELECT  r1.name AS `position` FROM lib_position AS r1
              INNER JOIN `person_lperson_position` AS r2
              ON r1.id_position = r2.id_position 
              WHERE r1.active IN (1,2) AND r2.id_person_lperson = ".$internship_project_contacts_item->id_person_lperson." AND r2.active IN (1,2) LIMIT 1;
        ");
        $internship_project_contact_position = (object)$elements->fetchAssoc();
        if (!empty($internship_project_contact_position->position)) {
            $internship_project_contacts_item->position = $internship_project_contact_position->position;
        }
    }
    $internship->project_contacts = $internship_project_contacts;

    //insurance
    $elements = db_query("
        SELECT t1.*
        FROM `internship_insurance` AS t1
        INNER JOIN `internship` AS t2
        ON t1.id_internship = t2.id_internship
        WHERE t2.id_internship = ".$id_internship." AND t1.active IN (1,2) AND t2.active IN (1,2);
    ");
    $internship_insurance = (object)$elements->fetchAssoc();
    $internship->insurance = $internship_insurance;
    //ritorno nello schema di default

    //attachments
    $elements = db_query("
        SELECT t1.*
        FROM `internship_attachment` AS t1
        INNER JOIN `internship` AS t2
        ON t1.id_internship = t2.id_internship
        WHERE t2.id_internship = ".$id_internship." AND t1.active IN (1,2) AND t2.active IN (1,2) ORDER BY t1.meta ASC;
    ");
    $internship_attachment = $elements->fetchAllAssoc('meta');
    $internship->attachments = $internship_attachment;

    // Registro Presenze
    $elements = db_query("
        SELECT t1.*
        FROM `internship_attendance_sheet` AS t1   
        WHERE t1.id_internship = ".$id_internship." AND t1.active IN (1,2);
    ");
    $internship_attendance_sheet = (object)$elements->fetchAssoc();
    $internship->attendance_sheet = $internship_attendance_sheet;

    //ritorno nello schema di default
    db_set_active();
    return $internship;
}

/**
 * Restituisce i dati aggregati di un Tirocinio
 * @param null $schema
 * @param $id_internship
 * @param string $check
 * @return object
 */
function getInternshipById($schema = null, $id_internship, $check = 'active') {
    db_set_active($schema);
    // tirocinio
    $elements = db_query("
        SELECT * FROM `internship` WHERE `id_internship` = ".$id_internship." and `active` = 1;
    ");
    $internship = (object)$elements->fetchAssoc();
    db_set_active();
    if ($internship->flg_voluntary == '0') {
        db_set_active($schema);
        // stato
        $elements = db_query("
            SELECT t2.*
            FROM `internship` AS t1
            INNER JOIN `internship_state` AS t2
            ON t1.id_internship = t2.id_internship AND t1.id_internship = " . $id_internship . " AND t1.flg_voluntary = 0 AND t1.active IN (1,2) AND t2.active IN (1,2);
        ");
        $internship_state = (object)$elements->fetchAssoc();
        $internship->internship_state = $internship_state;
        $date_start_effective = $internship->internship_state->date_start;
        if (empty($internship->internship_state->date_end)) {
            $datetime1 = new DateTime($internship->date_start);
            $datetime2 = new DateTime($internship->date_end);
            $interval = $datetime1->diff($datetime2);
            if (!empty($internship->internship_state->date_extension)) {
                $date_end_expected = $internship->internship_state->date_extension;
            } else {
                $date_end_expected = $internship->date_end;
            }
        } else {
            $date_end_expected = $internship->internship_state->date_end;
        }
        $internship->internship_state->date_end_expected = $date_end_expected;

        // dettagli base tirocinante
        $elements = db_query("
            SELECT t1.*,t2.*,t3.description AS title
            FROM `person` AS t1
            INNER JOIN `internship_person` AS t2
            ON t1.id_person = t2.id_person AND t2.active IN (1,2)
            INNER JOIN `lib_title` AS t3
            ON t1.id_title = t3.id_title AND t3.active IN (1,2)
            WHERE t2.id_internship = " . $internship->id_internship . " AND t1.active IN (1,2);
        ");
        $person = (object)$elements->fetchAssoc();
        $internship->person = $person;

        // qualifica tirocinante
        $elements = db_query("
            SELECT t2.name AS qualification
            FROM `internship_person` AS t1
            LEFT JOIN `lib_qualification` AS t2
            ON t1.id_qualification =  t2.id_qualification AND t2.active IN (1,2)
            WHERE t1.id_internship = " . $internship->id_internship . " AND t1.active IN (1,2);
        ");
        $qualification = $elements->fetchField();
        $internship->person->qualification = $qualification;

        // dettagli tipo tirocinio
        $elements = db_query("
            SELECT *
            FROM `lib_internship_type` AS t1
            INNER JOIN `internship` AS t2
            ON t1.id_internship_type = t2.id_internship_type AND t2.active IN (1,2)
            WHERE t2.id_internship = " . $id_internship . " AND t1.active IN (1,2);
        ");
        $internship_type = (object)$elements->fetchAssoc();
        $internship->internship_type = $internship_type;

        // dettagli convenzione
        $elements = db_query("
            SELECT *
            FROM `agreement` AS t1
            INNER JOIN `internship_agreement` AS t2
            ON t1.id_agreement = t2.id_agreement AND t2.active IN (1,2)
            WHERE t2.id_internship = " . $id_internship . " AND t1.active IN (0,1,2);
        ");
        $agreement = (object)$elements->fetchAssoc();
        $internship->agreement = $agreement;

        // Soggetto Ospitante
        $elements = db_query("
            SELECT t1.*,t2.id_lperson_lprole
            FROM `lperson` AS t1
            JOIN `lperson_lprole` AS t2
            ON t1.id_lperson = t2.id_lperson AND t2.active IN (1,2)
            JOIN `agreement` AS t3
            ON t2.id_lperson_lprole = t3.id_host AND t3.active IN (0,1,2)
            WHERE t3.id_agreement= " . $agreement->id_agreement . " AND t1.active IN (1,2);
        ");
        $host = (object)$elements->fetchAssoc();
        $internship->host = $host;

        // Soggetto Promotore
        $elements = db_query("
            SELECT t1.*,t2.id_lperson_lprole
            FROM `lperson` AS t1
            JOIN `lperson_lprole` AS t2
            ON t1.id_lperson = t2.id_lperson AND t2.active IN (1,2) 
            JOIN `agreement` AS t3
            ON t2.id_lperson_lprole = t3.id_promoter AND t3.active IN (1,2)
            WHERE t3.id_agreement= " . $agreement->id_agreement . " AND t1.active IN (1,2);
        ");
        $promoter = (object)$elements->fetchAssoc();
        $internship->promoter = $promoter;

        // Dipartimento / Segreteria del Soggetto Promotore
        if ($internship->promoter->level == 1) {
            $elements = db_query("
                SELECT t1.*
                FROM `lperson` AS t1
                WHERE t1.`id_lperson` = " . $internship->promoter->id_lperson_parent . " AND t1.active IN (1,2);
            ");
            $promoter_parent = (object)$elements->fetchAssoc();
            $internship->promoter->parent = $promoter_parent;
        }

        // Budget
        $elements = db_query("
            SELECT t2.*
            FROM `internship` AS t1
            INNER JOIN `internship_budget` AS t2
            ON t1.id_internship = t2.id_internship AND t2.active IN (1,2)
            WHERE t1.id_internship = " . $id_internship . " AND t1.active IN (1,2);
        ");
        $internship_budget = (object)$elements->fetchAssoc();
        $internship->budget = $internship_budget;

        $elements = db_query("
            SELECT t1.*,t2.id_lperson,t2.name,t2.id_lperson_parent,t3.flg_primary as lperson_flg_primary
            FROM `internship_lperson_location_area` AS t1
            INNER JOIN `lperson` AS t2
            ON t1.id_lperson_location_area = t2.id_lperson AND t2.active IN (1,2)
            INNER JOIN `internship_lperson` AS t3
            ON t3.id_lperson = t2.id_lperson_parent AND t3.id_internship = t1.id_internship AND t3.active IN (1,2)
            WHERE t1.id_internship = " . $id_internship . " AND t1.active IN (1,2);
        ");
        $internship_lperson_location_area = (object)$elements->fetchAll();
        $internship->lperson_location_area = $internship_lperson_location_area;

        // branches
        $elements = db_query("
            SELECT t1.*,t2.*
            FROM `internship_lperson` AS t1
            INNER JOIN `lperson` AS t2
            ON t1.id_lperson = t2.id_lperson
            WHERE t1.id_internship = " . $id_internship . " AND t1.active IN (1,2) AND t2.active IN (1,2) ORDER BY flg_primary DESC;
        ");
        $internship_lperson = $elements->fetchAll(\PDO::FETCH_GROUP | \PDO::FETCH_UNIQUE | \PDO::FETCH_OBJ);

        $internship_lpersons = array();
        foreach ($internship_lperson AS $internship_lperson_item) {

            //location_area
            $elements = db_query("
                SELECT t1.*,t2.id_lperson,t2.name,t4.flg_primary as lperson_flg_primary
                FROM `internship_lperson_location_area` AS t1
                INNER JOIN `lperson` AS t2
                ON t1.id_lperson_location_area = t2.id_lperson AND t2.level = 2 AND t2.active IN (1,2)
                INNER JOIN `lperson` AS t3
                ON t2.id_lperson_parent = t3.id_lperson AND t3.active IN (1,2)
                INNER JOIN `internship_lperson` AS t4
                ON t4.id_lperson = t3.id_lperson AND t4.id_internship = t1.id_internship AND t4.active IN (1,2)
                WHERE t1.id_internship = " . $id_internship . " AND t3.id_lperson = " . $internship_lperson_item->id_lperson . " AND t1.active IN (1,2);
            ");
            $internship_lperson_location_area = $elements->fetchAll(\PDO::FETCH_GROUP | \PDO::FETCH_UNIQUE | \PDO::FETCH_OBJ);
            $internship_lperson_item->lperson_location_area = (object)$internship_lperson_location_area;
            $internship_lpersons[] = $internship_lperson_item;


        }
        $internship->lperson = (object)$internship_lpersons;

        // primary branch
        $elements = db_query("
            SELECT t1.*,t2.name
            FROM `internship_lperson` AS t1
            INNER JOIN `lperson` AS t2
            ON t1.id_lperson = t2.id_lperson AND t2.active IN (1,2)
            WHERE t1.id_internship = " . $id_internship . " AND t1.flg_primary = 1 AND t1.active IN (1,2);
        ");
        $internship_lperson_primary = (object)$elements->fetchAssoc();
        $internship->lperson_primary = $internship_lperson_primary;

        //promoter_tutor
        $elements = db_query("
            SELECT t3.*,t5.*,t6.description as title
            FROM `internship_promoter_tutor` AS t1
            INNER JOIN `internship` AS t2
            ON t2.id_internship = t1.id_internship AND t2.active IN (1,2)
            INNER JOIN `person_lperson_prole` AS t3
            ON t3.id_person_lperson_prole = t1.id_person_lperson_prole AND t3.active IN (1,2)
            INNER JOIN `person_lperson` AS t4
            ON t4.id_person_lperson = t3.id_person_lperson AND t4.active IN (1,2)
            INNER JOIN `person` AS t5
            ON t5.id_person = t4.id_person AND t5.active IN (1,2)
            INNER JOIN `lib_title` AS t6
            ON t5.id_title = t6.id_title AND t6.active IN (1,2)
            WHERE t2.id_internship = " . $id_internship . " AND t1.active IN (1,2);
        ");
        $internship_promoter_tutor = (object)$elements->fetchAssoc();
        $internship->promoter->tutor = $internship_promoter_tutor;

        //host_tutor - Tutor del Soggetto Ospitante
        $elements = db_query("
            SELECT t1.flg_primary, t3.*,t4.*, t42.id_lperson, t42.name AS lperson_name, t5.description as title, '' as `position`
            FROM `internship_host_tutor` AS t1
            INNER JOIN `internship` AS t2
            ON t2.id_internship = t1.id_internship AND t2.active IN (1,2) 
            INNER JOIN `person_lperson_prole` AS t3
            ON t3.id_person_lperson_prole = t1.id_person_lperson_prole AND t3.active IN (1,2) 
            INNER JOIN `person_lperson` AS t41
            ON t41.id_person_lperson = t3.id_person_lperson AND t41.active IN (1,2) 
            INNER JOIN `lperson` AS t42
            ON t42.id_lperson = t41.id_lperson AND t42.active IN (1,2) 
            INNER JOIN `person` AS t4
            ON t4.id_person = t41.id_person AND t4.active IN (1,2) 
            INNER JOIN `lib_title` AS t5
            ON t4.id_title = t5.id_title AND t5.active IN (1,2) 
            WHERE t2.id_internship = " . $id_internship . " AND t1.active IN (1,2) ORDER BY t1.flg_primary DESC;
        ");
        $internship_host_tutor = (object)$elements->fetchAll();
        // Preleva la posizione del tutor. Nel caso ce ne fosse più di una preleva la prima
        foreach ($internship_host_tutor as &$internship_host_tutor_item) {
            $elements = db_query("
                  SELECT  r1.name AS `position` FROM lib_position AS r1
                  INNER JOIN `person_lperson_position` AS r2
                  ON r1.id_position = r2.id_position AND r2.active IN (1,2)
                  WHERE r1.active IN (1,2) AND r2.id_person_lperson = " . $internship_host_tutor_item->id_person_lperson . " LIMIT 1;
            ");
            $internship_host_tutor_position = (object)$elements->fetchAssoc();
            if (!empty($internship_host_tutor_position->position)) {
                $internship_host_tutor_item->position = $internship_host_tutor_position->position;
            }
        }
        $internship->host->tutor = $internship_host_tutor;

        //contact_person
        $elements = db_query("
            SELECT t1.flg_primary, t3.*,t4.*,t42.name AS lperson_name, t43.name as position, t5.description as title
            FROM `internship_project_contact` AS t1
            INNER JOIN `internship` AS t2
            ON t2.id_internship = t1.id_internship AND t2.active IN (1,2)
            INNER JOIN `person_lperson_prole` AS t3
            ON t3.id_person_lperson_prole = t1.id_person_lperson_prole AND t3.active IN (1,2)
            INNER JOIN `person_lperson` AS t41
            ON t41.id_person_lperson = t3.id_person_lperson AND t41.active IN (1,2)
            INNER JOIN `lperson` AS t42
            ON t42.id_lperson = t41.id_lperson AND t42.active IN (1,2)
            LEFT JOIN (
              SELECT  r1.name, r2.id_person_lperson FROM lib_position AS r1
              INNER JOIN `person_lperson_position` AS r2
              ON r1.id_position = r2.id_position WHERE r1.active IN (1,2) AND r2.active IN (1,2) LIMIT 1) AS t43
            ON t3.id_person_lperson = t43.id_person_lperson
            INNER JOIN `person` AS t4
            ON t4.id_person = t41.id_person AND t4.active IN (1,2) 
            INNER JOIN `lib_title` AS t5
            ON t4.id_title = t5.id_title AND t5.active IN (1,2)
            WHERE t2.id_internship = " . $id_internship . " AND t1.active IN (1,2)
               ORDER BY t1.flg_primary DESC;
        ");
        $internship_project_contacts = (object)$elements->fetchAll();
        // Preleva la posizione del contatto. Nel caso ce ne fosse più di una preleva la prima
        foreach ($internship_project_contacts as &$internship_project_contacts_item) {
            $elements = db_query("
                  SELECT  r1.name AS `position` FROM lib_position AS r1
                  INNER JOIN `person_lperson_position` AS r2
                  ON r1.id_position = r2.id_position AND r2.active IN (1,2)
                  WHERE r1.active IN (1,2) AND r2.id_person_lperson = " . $internship_project_contacts_item->id_person_lperson . " LIMIT 1;
            ");
            $internship_host_tutor_position = (object)$elements->fetchAssoc();
            if (!empty($internship_host_tutor_position->position)) {
                $internship_project_contacts_item->position = $internship_host_tutor_position->position;
            }
        }
        $internship->project_contacts = $internship_project_contacts;


        //insurance
        $elements = db_query("
            SELECT t1.*
            FROM `internship_insurance` AS t1
            INNER JOIN `internship` AS t2
            ON t1.id_internship = t2.id_internship AND t2.active IN (1,2)
            WHERE t2.id_internship = " . $id_internship . " AND t1.active IN (1,2);
        ");
        $internship_insurance = (object)$elements->fetchAssoc();
        $internship->insurance = $internship_insurance;
        //ritorno nello schema di default

        //attachments
        $elements = db_query("
            SELECT t1.*
            FROM `internship_attachment` AS t1
            INNER JOIN `internship` AS t2
            ON t1.id_internship = t2.id_internship AND t2.active IN (1,2)
            WHERE t2.id_internship = " . $id_internship . " AND t1.active IN (1,2) ORDER BY t1.meta ASC;
        ");
        $internship_attachment = $elements->fetchAllAssoc('meta');
        $internship->attachments = $internship_attachment;

        // Registro Presenze
        $elements = db_query("
            SELECT t1.*
            FROM `internship_attendance_sheet` AS t1   
            WHERE t1.id_internship = " . $id_internship . " AND t1.active IN (1,2);
        ");
        $internship_attendance_sheet = (object)$elements->fetchAssoc();
        $internship->attendance_sheet = $internship_attendance_sheet;

        //ritorno nello schema di default
        db_set_active();
    } else {
        $internship = getVInternshipById($id_internship);
    }
    return $internship;
}

/**
 * Restituisce tutte le convenzioni in atto tra due Soggetti (1 Promotore, 1 Ospitante) tramite ID dei soggetti
 * @param $p_id
 * @param $h_id
 * @return array
 */
function getAgreementsByHP($p_id, $h_id) {
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.*
        FROM `agreement` AS t1
        WHERE t1.id_host = '".$h_id."' AND t1.id_promoter = '".$p_id."' AND t1.active = 1;
    ");
    $options = array();
    $i = 1;
    while($result = $results->fetchObject()) {
        $options[$result->id_agreement] = $result->number_code;
        $i += 1;
    }
    db_set_active();
    return $options;
}

/**
 * Restituisce tutte i Laboratori (location_area) tramite id della Struttura (lperson)
 * @param $id_lperson_parent
 * @param $selected_list
 * @return DatabaseStatementInterface
 */
function getAllLocationAreaByLPId($id_lperson_parent, $selected_list) {
    $where = '(';
    $n = count($selected_list);
    $i = 1;
    foreach($selected_list as $value) {

        $where .= "t1.id_lperson = ".$value."";
        if ($i++ ==  $n) {
            $where .= ") AND ";
        } else {
            $where .= " OR ";
        }
    }


    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.*
        FROM `lperson` AS t1
        WHERE ".$where."t1.active = 1
        AND t1.id_lperson_parent = ".$id_lperson_parent.";
    ");

    db_set_active();
    return $results;
}

/**
 * Restituisce tutte le Strutture tramite id_lperson padre e id delle strutture selezionate
 * @param $id_lperson_parent
 * @param $selected_list
 * @return DatabaseStatementInterface
 */
function getAllBranch($id_lperson_parent, $selected_list) {
    $where = '(';
    $n = count($selected_list);
    $i = 1;
    foreach($selected_list as $value) {

        $where .= "t1.id_lperson = ".$value."";
        if ($i++ ==  $n) {
            $where .= ") AND ";
        } else {
            $where .= " OR ";
        }
    }
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.*, t2.flg_primary
        FROM `lperson` AS t1
        INNER JOIN `internship_lperson` AS t2
        ON t2.id_lperson = t1.id_lperson
        WHERE ".$where."t1.active = 1 AND t2.active = 1
        AND t1.id_lperson_parent = ".$id_lperson_parent.";
    ");

    db_set_active();
    return $results;
}

/**
 * Restituisce tutte i Laboratori (location_area) tramite lista di ID Strutture
 * @param $selected_list
 * @return array
 */
function getAllLocationAreaByLPLId($selected_list) {
    $where = '(';
    $n = count($selected_list);
    $i = 1;
    foreach($selected_list as $value) {

        $where .= "t1.id_lperson = '".$value."'";
        if ($i++ ==  $n) {
            $where .= ") AND ";
        } else {
            $where .= " OR ";
        }
    }

    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.*,t2.name AS branch_name
        FROM `lperson_location` AS t1
        INNER JOIN `lperson` AS t2
        ON t1.id_lperson = t2.id_lperson
        WHERE ".$where."t1.active = 1  AND t2.active = 1 and t1.name NOT LIKE 'all';
    ");
    $options = array();
    while($result = $results->fetchObject()) {
        $options[$result->id_lperson_location] = $result->name.' di '.$result->branch_name;
    }
    db_set_active();

    return $options;
}

/**
 * Restituisce tutte le Strutture tramite LPerson padre
 * @param $id_lperson_parent
 * @return array
 */
function getBranchOptions($id_lperson_parent) {
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.id_lperson, t1.name
        FROM `lperson` AS t1
        WHERE t1.id_lperson_parent = $id_lperson_parent AND t1.active = 1;
    ");
    $options = array();
    while($result = $results->fetchObject()) {
        $options[$result->id_lperson] = $result->name;
    }
    db_set_active();
    return $options;
}

/**
 * Restituisce i dati delle persone attribuite ad una Struttura
 * @param $schema
 * @param $id_lperson
 * @return mixed
 */
function getAllPersonsByLPId($schema, $id_lperson) {
    db_set_active($schema);
    $results = db_query("
        SELECT t2.*,t1.id_person_lperson,t21.description as title
        FROM `person_lperson` AS t1
        INNER JOIN `person` AS t2
        ON t2.id_person = t1.id_person
        INNER JOIN `lib_title` AS t21
        ON t21.id_title = t2.id_title
        INNER JOIN `lperson` AS t3
        ON t1.id_lperson = t3.id_lperson AND t3.id_lperson = ".$id_lperson."
        WHERE t1.active = 1 AND t2.active = 1 AND t3.active = 1 AND t21.active = 1;
    ");

    db_set_active();
    return $results->fetchAll();
}

/**
 * Restituisce i ruoli ATTIVI di una persona presso una Struttura Ospitante/Promotrice
 * @param $id_person_lperson
 * @return mixed
 */
function getPersonLPersonProles($id_person_lperson) {
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.id_person_lperson_prole, t1.id_prole, t3.description
        FROM person_lperson_prole AS t1
        INNER JOIN `person_lperson` AS t2
        ON t1.id_person_lperson = t2.id_person_lperson AND t1.id_person_lperson = ".$id_person_lperson."
        INNER JOIN `lib_prole` AS t3
        ON t3.id_prole = t1.id_prole
        WHERE t1.active = 1 AND t2.active = 1 AND t3.active = 1;
    ");
    db_set_active();
    return $results->fetchAll();
}

/**
 * Restituisce le posizioni ATTIVE di una persona presso una Struttura Ospitante
 * @param $id_person_lperson
 * @return mixed
 */
function getPersonLPersonPositions($id_person_lperson) {
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.id_person_lperson_position, t1.id_position,t3.description
        FROM person_lperson_position AS t1
        INNER JOIN `person_lperson` AS t2
        ON t1.id_person_lperson = t2.id_person_lperson AND t1.id_person_lperson = ".$id_person_lperson."
        INNER JOIN `lib_position` AS t3
        ON t3.id_position = t1.id_position
        WHERE t1.active = 1 AND t2.active = 1 AND t3.active = 1;
    ");
    db_set_active();
    return $results->fetchAll();
}

/**
 * Restituisce l'array dei ruoli di un Soggetto (Ospitante o Promotore) tramite ID del Soggetto
 * @param $schema
 * @param $id_lperson
 * @return array
 */
function getLPersonLProles($schema, $id_lperson) {
    db_set_active($schema);
    $results = db_query("
        SELECT t2.id_lprole, t2.description
        FROM lperson_lprole AS t1
        INNER JOIN `lib_lprole` AS t2
        ON t2.id_lprole = t1.id_lprole
        WHERE t1.id_lperson = ".$id_lperson." AND t1.active = 1 AND t2.active = 1;
    ");
    db_set_active();
    $options = array();
    while($result = $results->fetchObject()) {
        $options[$result->id_lprole] = $result->description;
    }
    db_set_active();
    return $options;
}

/**
 * Restituisce l'array degli ID dei ruoli di un Soggetto (Ospitante o Promotore) tramite ID del Soggetto
 * @param $schema
 * @param $id_lperson
 * @return array
 */
function getLPersonLProleIdsByLPersonId($schema, $id_lperson) {
    db_set_active($schema);
    $results = db_query("
        SELECT t1.id_lperson_lprole
        FROM lperson_lprole AS t1
        INNER JOIN `lib_lprole` AS t2
        ON t2.id_lprole = t1.id_lprole
        WHERE t1.id_lperson = ".$id_lperson." AND t1.active = 1 AND t2.active = 1;
    ");
    db_set_active();
    $options = array();
    while($result = $results->fetchObject()) {
        $options[$result->id_lperson_lprole] = $result->id_lperson_lprole;
    }
    db_set_active();
    return $options;
}

/**
 * Restituisce i dati di una persona tramite ID
 * @param $schema
 * @param $id_lperson
 * @return mixed
 */
function getLPersonById($schema, $id_lperson) {
    db_set_active($schema);
    $results = db_query("
        SELECT t1.*
        FROM `lperson` AS t1
        WHERE t1.id_lperson = ".$id_lperson." AND t1.active = 1;
    ");
    db_set_active();
    return $results->fetchObject();
}

/**
 * Restituisce i Ruoli permessi per una Figura a seconda del Soggetto (lperson), del suo ruolo (lprole) e del livello (Sede Legale-Struttura-Laboratorio)
 * @param $schema
 * @param $id_lperson
 * @return array
 */
function getAllowedProleByLPId($schema, $id_lperson) {
    db_set_active($schema);
    $results = db_query("
        SELECT t4.id_prole, t4.description
        FROM lperson_lprole AS t0
        INNER JOIN lib_prole_lprole AS t1
        ON t1.id_lprole = t0.id_lprole
        INNER JOIN lperson AS t2
        ON t2.id_lperson = t0.id_lperson
        INNER JOIN lib_prole_lperson_level AS t3
        ON t3.id_lperson_level = t2.level
        INNER JOIN lib_prole AS t4
        ON t4.id_prole = t3.id_prole AND t4.id_prole = t1.id_prole
        WHERE t0.id_lperson = ".$id_lperson." AND t0.active = 1 AND t1.active = 1 AND t2.active = 1 AND t3.active = 1 AND t4.active = 1
        ORDER BY t4.description;;
    ");
    db_set_active();
    $options = array();
    while($result = $results->fetchObject()) {
        $options[$result->id_prole] = $result->description;
    }
    db_set_active();
    return $options;
}

/**
 * Restituisce i Ruoli permessi per una Figura a seconda del Soggetto (lperson), del suo ruolo (lprole) e del livello (Sede Legale-Struttura-Laboratorio)
 * @param $schema
 * @param $id_lperson
 * @return array
 */
function getAllowedPositionByLPId($schema, $id_lperson) {
    db_set_active($schema);
    $results = db_query("
        SELECT t3.id_position, t3.description
        FROM lperson AS t0
        INNER JOIN lib_position_lperson_level AS t1
        ON t1.id_lperson_level = t0.level
        INNER JOIN lperson AS t2
        ON t2.id_lperson = t0.id_lperson
        INNER JOIN lib_position AS t3
        ON t3.id_position = t1.id_position
        WHERE t2.id_lperson = ".$id_lperson." AND t0.active = 1 AND t1.active = 1 AND t2.active = 1 AND t3.active = 1
        ORDER BY t3.description;
    ");
    db_set_active();
    $options = array();
    while($result = $results->fetchObject()) {
        $options[$result->id_position] = $result->description;
    }
    db_set_active();
    return $options;
}


/**
 * Restituisce tutte la Sede Legale e le Strutture tramite ID del Soggetto
 * @param $schema
 * @param $id_lperson_parent
 * @return array
 */
function getAllBranches($schema, $id_lperson_parent) {
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.id_lperson
        FROM lperson AS t1
        WHERE (t1.id_lperson = ".$id_lperson_parent." OR t1.id_lperson_parent = ".$id_lperson_parent." )
        AND t1.active = 1;
    ");
    db_set_active();
    $options = array();
    while($result = $results->fetchObject()) {
        $options[$result->id_lperson] = $result->id_lperson;
    }
    db_set_active();
    return $options;
}

/**
 * Restituisce tutti Soggetti (lperson padri - level = 0), non le strutture
 * @param $schema
 * @return array
 */
function getAllParentLPersons($schema) {
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.id_lperson, t1.name
        FROM lperson AS t1
        WHERE (t1.level = 0)
        AND t1.active = 1;
    ");
    db_set_active();
    $options = array();
    while($result = $results->fetchObject()) {
        $options[$result->id_lperson] = $result->name;
    }
    db_set_active();
    return $options;
}

/**
 * Restituisce l'HTML dell'header delle pratiche di Tirocinio
 * @param $current_step
 * @return string
 */
function get_internship_new_header($current_step) {
    $stages = array(
        1 => array('data' => 'Richiesta Tirocinio'),
        2 => array('data' => 'Comunicazione Dati Tirocinio'),
        3 => array('data' => 'Approvazione Tirocinio'),
        4 => array('data' => 'Attivazione Tirocinio'),
    );
    $output = '<div class="steps">';
    foreach ($stages as $key => $value) {
        $class = 'circle_step ';
        if ($key < $current_step) {
            $class .= 'green';
        } elseif ($key == $current_step) {
            $class .= 'red';
        }
        $output .= '<span class="'.$class.'">'.$key.'</span>';
    }
    $output .= '</div>';
    return $output;
}

/**
 * Restituisce i Laboratori (ID e nome) di una Struttura passata per ID
 * @param $schema
 * @param $id_lperson
 * @return array
 */
function getLocationAreaByLPId($schema, $id_lperson) {
    db_set_active($schema);
    $results = db_query("
        SELECT t1.id_lperson, t1.name
        FROM `lperson` AS t1
        WHERE t1.level = 2 AND t1.id_lperson_parent = ".$id_lperson." AND t1.active = 1;
    ");
    $options = array();
    while($result = $results->fetchObject()) {
        $options[$result->id_lperson] = $result->name;
    }
    db_set_active();
    return $options;
}

/**
 * Restituisce i dati di una Convenzione tramite numero IZSLER
 * @param $name
 * @return mixed
 */
function getAgreementByNumIZS($name) {
    db_set_active('getif_data');
    $elements = db_query("
        SELECT t1.id_agreement
        FROM `agreement` AS t1
        WHERE t1.number_code LIKE '%".$name."%';
    ");
    $a = (object)$elements->fetchAssoc();
    return $a->id_agreement;
}

/**
 * Restituisce l'ID di un Soggetto Ospitante tramite nome del Soggetto
 * @param $h_name
 * @return int
 */
function getHostIdByName($h_name) {
    db_set_active('getif_data');
    $elements = db_query("
        SELECT t3.id_host
        FROM `lperson` AS t1
        INNER JOIN `lperson_lprole` AS t2
        ON t1.id_lperson = t2.id_lperson
        INNER JOIN `host` AS t3
        ON t2.id_lperson_lprole = t3.id_lperson_lprole
        WHERE t1.name LIKE '".$h_name."' LIMIT 1;
    ");
    $host = (object)$elements->fetchAssoc();
    if (!empty($host->id_host))
        return $host->id_host;
    return 0;
}

/**
 * Restituisce l'ID di un Soggetto Promotore tramite Nome
 * @param $p_name
 * @return int
 */
function getPromoterIdByName($p_name) {
    db_set_active('getif_data');
    $elements = db_query("
        SELECT t3.id_promoter
        FROM `lperson` AS t1
        INNER JOIN `lperson_lprole` AS t2
        ON t1.id_lperson = t2.id_lperson
        INNER JOIN `promoter` AS t3
        ON t2.id_lperson_lprole = t3.id_lperson_lprole
        WHERE t1.name LIKE '".$p_name."' LIMIT 1;
    ");
    $promoter = (object)$elements->fetchAssoc();
    db_set_active();
    if (!empty($promoter->id_promoter))
        return $promoter->id_promoter;
    return 0;
}

/**
 * Recupera la chiave primaria di una tabella
 * @param $lib
 * @param null $schema
 * @return mixed
 */
function getPrimaryKeyTable($lib, $schema = null){

    //cambio schema
    db_set_active($schema);

    //trovo la primary key della tabella
    $keys = db_query(
        "SHOW KEYS FROM `{".$lib."}` WHERE Key_name = 'PRIMARY'"
    );

    //ritorno nello schema di default
    db_set_active();

    //trovo il nome della primary key
    foreach ($keys as $key) {
        $table_key = $key->Column_name;
    }

    return $table_key;
}

/**
 * Restituisce la chiave esterna di una tabella
 * @param $table
 * @param null $schema
 * @return mixed
 */
function getForeignKeyTable($table, $schema = null){

    //cambio schema
    db_set_active($schema);

    //trovo la primary key della tabella
    $keys = db_query(
        "SHOW KEYS FROM `{".$table."}` WHERE Key_name LIKE '%fk%'"
    );

    //ritorno nello schema di default
    db_set_active();

    //trovo il nome della primary key
    foreach ($keys as $key) {
        $table_key = $key->Column_name;
    }

    return $table_key;
}

/**
 * Funzione per trovare un array di elementi da una libreria
 * come chiave la primary key
 * come valore desc
 * @param $lib
 * @param null $schema
 * @param null $field_name
 * @param null $field_value
 * @param null $exclude_id
 * @return multitype:NULL
 */
function getLibOptions($lib, $schema = null, $field_name = null, $field_value = null, $exclude_id = null){
    $key = getPrimaryKeyTable($lib, $schema);
    //cambio schema
    db_set_active($schema);
    $query = "SELECT `id_".substr($lib,4)."` AS `id`,`description` FROM `{" . $lib . "}` WHERE `active`=1 ORDER BY description";
    if ($field_name != null && $field_value != null) {
        $query .= " AND ".$field_name." = '".$field_value."'";
    }
    if($exclude_id != null) {
        $query .= " AND $key != $exclude_id";
    }
    //trovo i record della tabella
    $lib_elements = db_query($query);
    //ritorno nello schema di default
    db_set_active();
    //costruisco l'array da ritornare
    $array_elements = array();
    foreach ($lib_elements as $lib_element)
    {
        $array_elements[$lib_element->id] =  $lib_element->description;
    }
    //ritorno;
    return $array_elements;
}

/**
 * Prende la chiave più alta della tabella
 * @param $table
 * @param null $schema
 * @return mixed
 */
function getMaxKey($table, $schema = null){
    $key = getPrimaryKeyTable($table, $schema);
    db_set_active($schema);
    $max = db_query("
			SELECT MAX($key)
			FROM `{".$table."}`")->fetchField();
    db_set_active();
    return $max;
}

/**
 * Prende tutti i record dato un campo
 * @param string $table
 * @param string $field_name
 * @param string $field_value
 * @return array
 */
function getAllRecords($table, $schema = null, $check = 'active') {
    db_set_active($schema);
    //trovo i record della tabella
    $elements = db_query("
			SELECT *
			FROM `{".$table."}`
			WHERE 1"
    );
    //ritorno nello schema di default
    db_set_active();
    $array = array();
    foreach ($elements as $element)
    {
        $array[]= $element;
    }
    return $array;
}

/**
 * Prende tutti i record dato un campo
 * @param string $table
 * @param string $field_name
 * @param string $field_value
 * @return array
 */
function getAllRecordByField($table, $schema = null, $field_name, $field_value, $check = 'active', $check_value = 1) {
    if(is_array($check_value)) {
        $where = $check . " IN (" . join($check_value,',') . ") AND
            " . $field_name . " = '" . $field_value . "'";
    } else {
        $where = $check . " = " . $check_value . " AND
            " . $field_name . " = '" . $field_value . "'";
    }
    db_set_active($schema);
    //trovo i record della tabella
    $elements = db_query("
			SELECT *
			FROM `{".$table."}`
			WHERE ".$where.";"
    );
    //ritorno nello schema di default
    db_set_active();
    $array = array();
    foreach ($elements as $element)
    {
        $array[]= $element;
    }
    return $array;
}

/**
 * Prende tutti i record dato un campo
 * @param string $table
 * @param string $field_name
 * @param string $field_value
 * @return array
 */
function getRecordByField($table, $schema = null, $field_name, $field_value, $check = 'active', $check_value = 1) {

    db_set_active($schema);

    //trovo i record della tabella
    $elements = db_query("
		SELECT *
		FROM `{".$table."}`
		WHERE
		".$check." = ".$check_value." AND
		".$field_name." LIKE '".$field_value."'"
    );
    //ritorno nello schema di default
    $element = $elements->fetchAssoc(PDO::FETCH_ASSOC);
    db_set_active();
    if (!empty($element)) {
        return (object)$element;
    }
    return array();

}

/**
 * recupera un record dato la tabella e l'id
 * @param string $table
 * @param string $schema
 * @param $id
 */
function getRecordById($table, $schema = null, $id){
    $key = getPrimaryKeyTable($table, $schema);
    db_set_active($schema);
    //trovo i record della tabella
    $elements = db_query("
			SELECT *
			FROM `{".$table."}`
			WHERE
				`active` = 1 AND
				`".$key."` = ".$id
    );
    //ritorno nello schema di default
    db_set_active();
    foreach ($elements as $element)
    {
        return $element;
    }
    return null;
}


/*** ******************************/
/***        DELETE METHODS      ***/
/*** ************************** ***/

/**
 * Elimina i dati della schede Tirocinio individuata dall'argomento $step
 * @param $id_internship
 * @param $step
 */
function delete_internship_step_data($id_internship, $step) {
    global $user;
    clean_cron_by_id('internship',$id_internship); // aggiorno le notifiche
    // watchdog
    $w_type = 'getif_'.'internship_user';
    $w_message = t('Delete object internship item with id: %id_internship AND step: %step');
    $w_variables = array('%id'=>$id_internship,'%step'=>$step);
    watchdog($w_type, $w_message, $w_variables);
    if ($step <= 4) {
        // modifica internship_insurance - estremi assicurativi
        $fields = array(
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship_insurance');
            $query -> fields($fields) -> condition('id_internship',$id_internship)-> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
        // modifica internship - elimina flags
        $fields = array(
            'meta_flags' => NULL,
            'active' => 1,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship');
            $query -> fields($fields) -> condition('id_internship',$id_internship)-> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
        // modifica internship_state - stato tirocinio = 3
        $fields = array(
            'state' => 3,
            'active' => 1,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship_state');
            $query -> fields($fields) -> condition('id_internship',$id_internship)-> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
    }

    if ($step <= 3) {
        // Rimuovi tutor promotore
        $fields = array(
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship_promoter_tutor');
            $query -> fields($fields) -> condition('id_internship',$id_internship) -> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
        // Rimuovi tutor ospitante
        $fields = array(
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship_host_tutor');
            $query -> fields($fields) -> condition('id_internship',$id_internship) -> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
        // Rimuovi i Referenti
        $fields = array(
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship_project_contact');
            $query -> fields($fields) -> condition('id_internship',$id_internship) -> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();

        // elimina allegati
        db_set_active('getif_data');
        try {
            $query = db_update('internship_attachment');
            $query -> fields(array(
                'active' => 0,
                'date_upd' => date("Y-m-d H:i:s", time()),
            ))->condition(db_and()->condition('id_internship',$id_internship)->condition('meta','progetto_formativo','LIKE'))->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();

        db_set_active('getif_data');
        try {
            $query = db_update('internship_attachment');
            $query -> fields(array(
                'active' => 0,
                'date_upd' => date("Y-m-d H:i:s", time()),
            ))->condition(db_and()->condition('id_internship',$id_internship)->condition('meta','parere_favorevole','LIKE'))->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();

        // modifica stato tirocinio
        $fields = array(
            'state' => 2,
            'active' => 1,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship_state');
            $query -> fields($fields) -> condition('id_internship',$id_internship)-> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();

        // modifica progetto formativo
        $fields = array(
            'note' => NULL,
            'active' => 1,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship');
            $query -> fields($fields) -> condition('id_internship',$id_internship)-> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
    }

    if ($step <= 2) {
        $internship = getInternshipById('getif_data', $id_internship);
        // solo per gli extracurriculari
        // elimina budget
        if($internship->internship_type->flg_extra_curricular == 1) {
            db_set_active('getif_data');
            $fields = array(
                'active' => 0,
                'date_upd' => date("Y-m-d H:i:s", time()),
            );
            $query = db_update('internship_budget');
            $query -> fields($fields)->condition('id_internship',$id_internship)->execute();
            db_set_active();
        }
        // elimina allegati
        db_set_active('getif_data');
        $query = db_update('internship_attachment');
        $query -> fields(array(
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        ))->condition(db_and()->condition('id_internship',$id_internship)->condition('meta','comunicazione_dati_tirocinio','LIKE'))->execute();
        db_set_active();


        db_set_active('getif_data');
        // modifica stato tirocinio
        $fields = array(
            'state' => 1,
            'active' => 1,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        $key = array(
            'id_internship' => $id_internship,
        );
        try {
            $query = db_merge('internship_state');
            $query -> key($key) -> fields($fields) -> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();

        // elimina tutte strutture associate al tirocinio
        $fields = array(
            'flg_primary' => 0,
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        try {
            // Rimuovi Strutture
            db_set_active('getif_data');
            $query = db_update('internship_lperson');
            $query->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_set_active();
            // Rimuovi tutti i laboratori della struttura
            $internship = getInternshipById('getif_data',$id_internship);
            $lperson_location_areas = $internship->lperson_location_area;
            foreach($lperson_location_areas as $lperson_location_area) {
                if((int)$lperson_location_area->id_lperson == (int)$key) {
                    db_set_active('getif_data');
                    $fields = array(
                        'active' => 2,
                        'date_upd' => date("Y-m-d H:i:s", time()),
                    );
                    try {
                        $query = db_update('internship_lperson_location_area');
                        $query ->fields($fields)
                            -> where('id_internship = '.$id_internship.' AND id_lperson_location_area = '.
                                $lperson_location_area->id_lperson_location_area)
                            -> execute();
                    } catch (Exception $ex) {
                        drupal_set_message('Errore: '.$ex,'error');
                    }
                    db_set_active();
                }
            }

        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }
    }

    if ($step == 1) {
        $fields = array(
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        try {
            db_set_active('getif_data');
            db_update('internship_user')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_state')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_promoter_tutor')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_project_contact')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_person')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_lperson_location_area')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_lperson')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_insurance')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_host_tutor')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_budget')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_attendance_sheet')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_attachment')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_agreement')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_set_active();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
    }
    // utente che ha modificato la scheda tirocinio
    try {
        db_set_active('getif_data');
        // insert internship_user
        $query = db_insert('internship_user');
        $id_internship_user = $query -> fields(array(
            'id_internship' => $id_internship,
            'uid' => $user->uid,
            'action' => 'delete'
        ))->execute();
        db_set_active();
        // watchdog
        $w_type = 'getif_'.'internship_user';
        $w_message = t('Insert item %id');
        $w_variables = array('%id'=>$id_internship_user);
        watchdog($w_type, $w_message, $w_variables);
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
}

/*** ******************************/
/***        DELETE METHODS      ***/
/*** ************************** ***/

/**
 * Elimina i dati della schede Tirocinio individuata dall'argomento $step
 * @param $id_internship
 * @param $step
 */
function delete_vinternship_step_data($id_internship, $step) {
    global $user;
    clean_cron_by_id('internship',$id_internship); // aggiorno le notifiche
    // watchdog
    $w_type = 'getif_'.'internship_user';
    $w_message = t('Delete object internship item with id: %id_internship AND step: %step');
    $w_variables = array('%id'=>$id_internship,'%step'=>$step);
    watchdog($w_type, $w_message, $w_variables);
    if ($step <= 4) {
        // modifica internship_insurance - estremi assicurativi
        $fields = array(
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship_insurance');
            $query -> fields($fields) -> condition('id_internship',$id_internship)-> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
        // modifica internship - elimina flags
        $fields = array(
            'meta_flags' => NULL,
            'active' => 1,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship');
            $query -> fields($fields) -> condition('id_internship',$id_internship)-> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
        // modifica internship_state - stato tirocinio = 3
        $fields = array(
            'state' => 3,
            'active' => 1,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship_state');
            $query -> fields($fields) -> condition('id_internship',$id_internship)-> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
    }

    if ($step <= 3) {
        // Rimuovi i Referenti
        $fields = array(
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship_project_contact');
            $query -> fields($fields) -> condition('id_internship',$id_internship) -> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();

        // elimina allegati
        db_set_active('getif_data');
        try {
            $query = db_update('internship_attachment');
            $query -> fields(array(
                'active' => 0,
                'date_upd' => date("Y-m-d H:i:s", time()),
            ))->condition(db_and()->condition('id_internship',$id_internship)->condition('meta','parere_favorevole','LIKE'))->execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();

        // modifica stato tirocinio
        $fields = array(
            'state' => 2,
            'active' => 1,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship_state');
            $query -> fields($fields) -> condition('id_internship',$id_internship)-> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();

        // modifica motivo della frequenza
        $fields = array(
            'note' => NULL,
            'active' => 1,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        db_set_active('getif_data');
        try {
            $query = db_update('internship');
            $query -> fields($fields) -> condition('id_internship',$id_internship)-> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
    }

    if ($step <= 2) {
        // elimina allegati
        db_set_active('getif_data');
        $query = db_update('internship_attachment');
        $query -> fields(array(
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        ))->condition(db_and()->condition('id_internship',$id_internship)->condition('meta','dichiarazione_frequenza_volontaria','LIKE'))->execute();
        db_set_active();
        // modifica stato tirocinio
        db_set_active('getif_data');
        $fields = array(
            'state' => 1,
            'active' => 1,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        $key = array(
            'id_internship' => $id_internship,
        );
        try {
            $query = db_merge('internship_state');
            $query -> key($key) -> fields($fields) -> execute();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
        db_set_active();
        // elimina tutte strutture associate al tirocinio
        $fields = array(
            'flg_primary' => 0,
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        try {
            // Rimuovi Strutture
            db_set_active('getif_data');
            $query = db_update('internship_lperson');
            $query->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_set_active();
            // Rimuovi tutti i laboratori della struttura
            $internship = getVInternshipById('getif_data',$id_internship);
            $lperson_location_areas = $internship->lperson_location_area;
            foreach($lperson_location_areas as $lperson_location_area) {
                if((int)$lperson_location_area->id_lperson == (int)$key) {
                    db_set_active('getif_data');
                    $fields = array(
                        'active' => 2,
                        'date_upd' => date("Y-m-d H:i:s", time()),
                    );
                    try {
                        $query = db_update('internship_lperson_location_area');
                        $query ->fields($fields)
                            -> where('id_internship = '.$id_internship.' AND id_lperson_location_area = '.
                                $lperson_location_area->id_lperson_location_area)
                            -> execute();
                    } catch (Exception $ex) {
                        drupal_set_message('Errore: '.$ex,'error');
                    }
                    db_set_active();
                }
            }

        } catch (Exception $ex) {
            drupal_set_message('Errore: ' . $ex, 'error');
        }
    }

    if ($step == 1) {
        $fields = array(
            'active' => 0,
            'date_upd' => date("Y-m-d H:i:s", time()),
        );
        try {
            db_set_active('getif_data');
            db_update('internship_user')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_state')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_project_contact')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_person')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_lperson_location_area')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_lperson')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_insurance')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_budget')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_attendance_sheet')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship_attachment')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_update('internship')->fields($fields)->condition('id_internship',$id_internship)->execute();
            db_set_active();
        } catch (Exception $ex) {
            drupal_set_message('Errore: '.$ex,'error');
        }
    }
    // utente che ha modificato la scheda tirocinio
    try {
        db_set_active('getif_data');
        // insert internship_user
        $query = db_insert('internship_user');
        $id_internship_user = $query -> fields(array(
            'id_internship' => $id_internship,
            'uid' => $user->uid,
            'action' => 'delete'
        ))->execute();
        db_set_active();
        // watchdog
        $w_type = 'getif_'.'internship_user';
        $w_message = t('Insert item %id');
        $w_variables = array('%id'=>$id_internship_user);
        watchdog($w_type, $w_message, $w_variables);
    } catch (Exception $ex) {
        drupal_set_message('Errore: '.$ex,'error');
    }
}



/*** *************************** ***/
/***            SET METHODS      ***/
/** **************************** ***/


/**
 * Imposta lo stato del tirocinio
 * @param $table
 * @param null $schema
 * @param $field_name
 * @param $field_value
 * @param string $check
 * @param int $check_value
 * @param string $where
 */
function setRecordState($table, $schema = null, $field_name, $field_value, $check = 'active', $check_value = 1, $where = '') {
    db_set_active($schema);
    $query = db_update($table);
    $query
        ->fields(array($check => $check_value, 'date_upd' => date("Y-m-d H:i:s", time())))
        ->condition($field_name, $field_value,'=');
    if (!empty($where)) {
        $query->where($where);
    }
    $query->execute();
    db_set_active();
}

/**
 * Inserisce un nuovo record in libreria
 * @param $lib
 * @param null $schema
 * @param $field_name
 * @param null $field_value
 * @return DatabaseStatementInterface|int
 * @throws Exception
 */
function setLibOption($lib, $schema = null, $field_name, $field_value = null) {
    db_set_active($schema);
    if (is_array($field_name)) {
        $fields = $field_name;
    } else {
        $fields = array(
            $field_name => strtolower($field_value),
        );
    }
    $id = db_insert($lib) ->fields($fields)->execute();
    db_set_active();
    $w_type = 'getif_'.$lib;
    $w_message = t('Insert item %id');
    $w_variables = array('%id'=>$id);
    watchdog($w_type, $w_message, $w_variables);
    return $id;
}

/*** ************************** ***/
/***        AUTOCOMPLETE        ***/
/*** ************************** ***/


/************************************************/
/***********            TUTOR       *************/
/************************************************/

/**
 * Funzione di autocompletamento generica per tutor dei Soggetti e Responsabili/Referenti
 * @param $type
 * @param $id_lperson
 * @param string $string
 */
function tutor_autocomplete_callback($type, $id_lperson, $string = "") {
    $string = addslashes($string);
    $lperson_parent = getRecordById('lperson', 'getif_data', $id_lperson);

    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.id_lperson
        FROM lperson AS t1
        WHERE (t1.id_lperson = ".$id_lperson." OR ".(!empty($lperson_parent->id_lperson_parent)?'t1.id_lperson = '.$lperson_parent->id_lperson_parent:'').")
        AND t1.active = 1;
    ");

    $where = '';
    while($result = $results->fetchObject()) {
        $where .= ' t2.id_lperson = '.$result->id_lperson.' OR ';
    }
    if (!empty($where)) {
        $where = substr($where, 0, -4);
        $where = '(t1.firstname LIKE \'%'.$string.'%\' OR t1.lastname LIKE \'%'.$string.'%\' OR t1.tax_code LIKE \'%'.$string.'%\') AND ('.$where.')';
    }
    $results = db_query("
        SELECT t1.*,t2bis.id_lperson,t2bis.name,t2bis.level,t3.id_person_lperson_prole, t3.id_prole
        FROM `person` AS t1
        INNER JOIN `person_lperson` AS t2
        ON t2.id_person = t1.id_person
        INNER JOIN `lperson` AS t2bis
        ON t2bis.id_lperson = t2.id_lperson
        INNER JOIN `person_lperson_prole` AS t3
        ON t3.id_person_lperson = t2.id_person_lperson
        INNER JOIN `lib_prole` AS t4
        ON t4.id_prole = t3.id_prole AND t4.id_prole = ".$type."    
        WHERE ".$where." AND t1.active = 1 AND t2.active = 1 AND t2bis.active = 1 AND t3.active = 1 AND t4.active = 1;
    ");
    $tutors = $results->fetchAll();
    db_set_active();
    $users = array();
    foreach($tutors AS $result) {
        if (in_array($type,array(2,3))) {
            $name = $result->tax_code.' - '.$result->firstname.' '.$result->lastname.' ('.$result->name.')';
        }
        else {
            $parent_name = '';
            if ($result->level == 1) {
                $parent = $lperson_parent = getRecordById('lperson', 'getif_data', $lperson_parent->id_lperson_parent);
                $parent_name = ' - ' . $parent->name;
            }
            $name = $result->tax_code.' - '.$result->firstname.' '.$result->lastname.' ('.$result->name.$parent_name.')';
        }
        $users[] = array(
            'id'        =>  $name.'|'.$result->id_person_lperson_prole,
            'name'      => $name
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['id']] = $user['name'];
    }
    drupal_json_output($matches);
}

/**
 * Funzione di autocompletamento specifica per i tutor del Soggetto Ospitante
 * @param $type
 * @param $id_internship
 * @param string $string
 * @return string
 */
function host_tutor_autocomplete_callback($type, $id_internship, $string = "") {
    $string = addslashes($string);
    db_set_active('getif_data');
    $lperson_list = db_query("
        SELECT t1.id_lperson
        FROM internship_lperson AS t1
        WHERE t1.id_internship = ".$id_internship." AND t1.active = 1
    ")->fetchAllKeyed(0,0);

    if (!empty($lperson_list)) {
        $where = 't2.id_lperson IN (' . join($lperson_list, ',') . ') AND (t1.firstname LIKE \'%' . $string . '%\' OR t1.lastname LIKE \'%' . $string . '%\' OR t1.tax_code LIKE \'%' . $string . '%\')';
        $results = db_query("
        SELECT t1.*,t2bis.name,t3.id_person_lperson_prole, t3.id_prole
        FROM `person` AS t1
        INNER JOIN `person_lperson` AS t2
        ON t2.id_person = t1.id_person
        INNER JOIN `lperson` AS t2bis
        ON t2bis.id_lperson = t2.id_lperson
        INNER JOIN `person_lperson_prole` AS t3
        ON t3.id_person_lperson = t2.id_person_lperson
        INNER JOIN `lib_prole` AS t4
        ON t4.id_prole = t3.id_prole AND t4.id_prole = " . $type . "    
        WHERE " . $where . " AND t1.active = 1 AND t2.active = 1 AND t2bis.active = 1 AND t3.active = 1 AND t4.active = 1;
    ");
        $tutors = $results->fetchAll();
        db_set_active();
        $users = array();
        foreach ($tutors AS $result) {
            $name = $result->tax_code . ' - ' . $result->firstname . ' ' . $result->lastname . ' (' . $result->name . ')';
            $users[] = array(
                'id' => $name . '|' . $result->id_person_lperson_prole,
                'name' => $name
            );
        }
        $matches = array();
        foreach ($users as $user) {
            $matches[$user['id']] = $user['name'];
        }
        drupal_json_output($matches);
    } else {
        return '';
    }
}

/**
 * Funzione di autocompletamento specifica per i tutor del Soggetto Ospitante
 * @param $type
 * @param $id_internship
 * @param string $string
 * @return string
 */
function all_host_tutors_autocomplete_callback($type, $string = "") {
    $string = addslashes($string);
    db_set_active('getif_data');
    $where = 't1.firstname LIKE \'%' . $string . '%\' OR t1.lastname LIKE \'%' . $string . '%\' OR t1.tax_code LIKE \'%' . $string . '%\'';
    $results = db_query("
            SELECT t1.id_person, t1.firstname,t1.lastname,t1.tax_code,GROUP_CONCAT(t3.id_person_lperson_prole SEPARATOR '-') AS id_person_lperson_prole
            FROM `person` AS t1
            INNER JOIN `person_lperson` AS t2
            ON t2.id_person = t1.id_person
            INNER JOIN `lperson` AS t2bis
            ON t2bis.id_lperson = t2.id_lperson
            INNER JOIN `person_lperson_prole` AS t3
            ON t3.id_person_lperson = t2.id_person_lperson
            INNER JOIN `lib_prole` AS t4
            ON t4.id_prole = t3.id_prole AND t4.id_prole = " . $type . "    
            WHERE t1.active = 1 AND t2.active = 1 AND t2bis.active = 1 AND t3.active = 1 AND t4.active = 1 GROUP BY t1.id_person;
        ");
    $tutors = $results->fetchAll();
    db_set_active();
    $users = array();
    foreach ($tutors AS $result) {
        $name = $result->tax_code . ' - ' . $result->firstname . ' ' . $result->lastname;
        $users[] = array(
            'id' => $name . '|' . $result->id_person,
            'name' => $name
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['id']] = $user['name'];
    }
    drupal_json_output($matches);

}

/*** **************************************************** ***/
/*** *******            PERSONE FISICHE         ********* ***/
/*** **************************************************** ***/
/**
 * Funzione di autocompletamento generico per Figure
 * @param string $string
 */
function person_list_autocomplete_by_lperson_callback($id_lperson, $string = "") {
    $string = addslashes($string);
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.*,t2.description as title
        FROM `person` AS t1
        INNER JOIN `lib_title` AS t2
        ON t1.id_title = t2.id_title
        WHERE 
        t1.meta_field NOT LIKE '%\"is_intern\":\"1\"%' 
        AND (t1.firstname LIKE '%".db_like($string) ."%' OR t1.lastname LIKE '%".db_like($string) ."%' OR t1.tax_code LIKE '%".db_like($string) ."%') AND t1.active = 1 AND t2.active = 1;
    ");
    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        db_set_active('getif_data');
        $query = db_query("
            SELECT t1.*
            FROM `person_lperson` AS t1
            WHERE 
            t1.id_person = ".$result->id_person." AND t1.id_lperson = ".$id_lperson."
            AND t1.active = 1 LIMIT 1;
        ")->fetchObject();
        db_set_active();
        if (empty($query)) {
            $users[] = array(
                'id' => $result->title . ' ' . $result->firstname . ' ' . $result->lastname . ' (' . $result->tax_code . ')' . '|' . $result->id_person,
                'tax_code' => $result->tax_code,
                'name' => $result->title . ' ' . $result->firstname . ' ' . $result->lastname,
            );
        }
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['id']] = $user['name'].' ('.$user['tax_code'].')';
    }
    drupal_json_output($matches);
}


/*** **************************************************** ***/
/*** *******            PERSONE FISICHE         ********* ***/
/*** **************************************************** ***/
/**
 * Funzione di autocompletamento generico per Figure
 * @param string $string
 */
function person_list_autocomplete_callback($string = "") {
    $string = addslashes($string);
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.*,t2.description as title
        FROM `person` AS t1
        INNER JOIN `lib_title` AS t2
        ON t1.id_title = t2.id_title
        WHERE t1.meta_field NOT LIKE '%\"is_intern\":\"1\"%' AND (t1.firstname LIKE '%".db_like($string) ."%' OR t1.lastname LIKE '%".db_like($string) ."%' OR t1.tax_code LIKE '%".db_like($string) ."%') AND t1.active = 1 AND t2.active = 1;
    ");
    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id'        => $result->title.' '.$result->firstname.' '.$result->lastname.' ('.$result->tax_code.')'.'|'.$result->id_person,
            'tax_code'  => $result->tax_code,
            'name'      => $result->title.' '.$result->firstname.' '.$result->lastname,
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['id']] = $user['name'].' ('.$user['tax_code'].')';
    }
    drupal_json_output($matches);
}


/**
 * Funzione di autocompletamento per Figure impiegate in una determinata Struttura
 * @param $type
 * @param $id_lperson
 * @param string $string
 */
function person_autocomplete_callback($type, $id_lperson, $string = "") {
    $string = addslashes($string);
    $or = db_or()
        ->condition('lp.tax_code', '%' . db_like($string) . '%', 'LIKE')
        ->condition('lp.name', '%' . db_like($string) . '%', 'LIKE');
    $and = db_and()
        ->condition('tbl.active', 1)
        ->condition('lpr.active', 1)
        ->condition('lp.active', 1)
        ->condition('prlpr.active', 1);

    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.*,t2.id_person_prole_lperson_lprole
        FROM `person` AS t1
        INNER JOIN `person_prole_lperson_lprole` AS t2
        ON t2.id_person = t1.id_person
        INNER JOIN `lib_prole` AS t3
        ON t3.id_prole = t2.id_prole AND t3.id_prole = ".$type."  
        INNER JOIN `lperson_lprole` AS t4
        ON t4.id_lperson_lprole = t2.id_lperson_lprole AND t4.id_lperson = ".$id_lperson."
        WHERE (t1.firstname LIKE '%".db_like($string) ."%' OR t1.lastname LIKE '%".db_like($string) ."%' OR t1.tax_code LIKE '%".db_like($string) ."%') AND t1.active = 1 AND t2.active = 1 AND t3.active = 1 AND t4.active = 1;
    ");

    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id'        =>  $result->tax_code.' - '.$result->firstname.' '.$result->lastname.'|'.$result->id_person_prole_lperson_lprole,
            'tax_code'      => $result->tax_code,
            'firstname'          => $result->firstname,
            'lastname'          => $result->lastname,
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['id']] = $user['tax_code'] . ' - ' . $user['firstname'] . ' ' . $user['lastname'];
    }
    drupal_json_output($matches);
}

/*** **************************************************** ***/
/*** *******            PERSONE GIURIDICHE         ****** ***/
/*** **************************************************** ***/

/**
 * Funzione di autocompletamento per il recupero delle Strutture di un dato Soggetto
 * @param $id_lperson_parent
 * @param string $string
 */
function branch_autocomplete_callback($id_lperson_parent, $string = "") {
    $string = addslashes($string);
    $or = db_or()
        ->condition('t1.name', '%'.db_like($string).'%' , 'LIKE')
        ->condition('t1.tax_code', '%'.db_like($string).'%' , 'LIKE');
    $and = db_and()
        ->condition('t1.id_lperson_parent', $id_lperson_parent , '=')
        ->condition('t1.level', 1 , '=');
    db_set_active('getif_data');
    $query = db_select('lperson','t1');
    $query->condition($or);
    $query->condition($and);
    $query-> fields('t1');
    $results = $query->execute();
    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id'        => $result->name.'|'.$result->id_lperson,
            'name'      => $result->name
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['id']] = $user['name'];
    }
    drupal_json_output($matches);
}


/*** ********************** ***/
/***        Callbacks       ***/
/*** ********************** ***/

/**
 * Funzione per l'esecuzione dell'autocomplete dei CAP
 * @param string $string
 */
function _autocomplete_lib_zip_code($string = ""){
    $string = addslashes($string);
    $matches = array();

    //cambio schema
    db_set_active('irene');

    //scrivo la query
    $result = db_select('lib_zip_code', 'lib_zip_code')
        ->fields('lib_zip_code', array('id_lib_zip_code','description'))
        ->condition('description', '%' . db_like($string) . '%', 'LIKE')
        ->condition('active','1','=')
        ->orderBy('description', 'ASC')
        ->execute();

    db_set_active();

    // save the query to matches
    foreach ($result as $row) {
        $matches[$row->description] = check_plain($row->description);
    }

    // Return the result to the form in json
    drupal_json_output($matches);
}

/* CITIES */
/**
 * @param string $string
 */
function cities_autocomplete_callback($string = "") {
    $string = addslashes($string);
    db_set_active('getif_data');
    $or = db_or()
        ->condition('c.DESCRIZIONE', '%' . db_like($string) . '%', 'LIKE')
        ->condition('c.CAP', '%' . db_like($string) . '%', 'LIKE');
    $query = db_select('comuni', 'c');
    $query->innerJoin('province','p','p.PRO_ID = c.PRO_ID');
    $query->fields('c');
    $query->fields('p',array('SIGLA'));
    $query->condition($or);
    $results = $query->execute();
    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'cap'     => $result->CAP,
            'descrizione'      => strtoupper($result->DESCRIZIONE),
            'sigla'      => strtoupper($result->SIGLA),
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['descrizione'].' ('.$user['sigla'].')'.', CAP '.$user['cap'] . '|' . $user['cap']] = $user['descrizione'].' ('.$user['sigla'].')'.', CAP '.$user['cap'];
    }
    drupal_json_output($matches);
}

/* PERSON */
/**
 * @param string $string
 * @param bool $no_autocomplete
 * @return array
 */
function intern_autocomplete_callback($string = "", $no_autocomplete = false) {
    $string = addslashes($string);
    db_set_active('getif_data');
    $or = db_or()
        ->condition('p.tax_code', '%' . db_like($string) . '%', 'LIKE')
        ->condition('p.firstname', '%' . db_like($string) . '%', 'LIKE')
        ->condition('p.lastname', '%' . db_like($string) . '%', 'LIKE');
    $query = db_select('person', 'p');
    $query->fields('p');
    $query->condition($or);
    $query->where('p.meta_field LIKE \'%"is_intern":"1"%\'');
    $results = $query->execute();
    db_set_active();


    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id_person'     => $result->id_person,
            'tax_code'      => strtoupper($result->tax_code),
            'firstname'     => strtoupper($result->firstname),
            'lastname'      => strtoupper($result->lastname),
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['tax_code'] . ' - ' . $user['firstname'] . ' ' . $user['lastname'].'|'.$user['id_person']] = $user['tax_code'] . ' - ' . $user['firstname'] . ' ' . $user['lastname'];
    }
    if ($no_autocomplete == false) {
        drupal_json_output($matches);
    } else {
        return $matches;
    }
}

/* PERSON */
/**
 * @param string $string
 * @param bool $no_autocomplete
 * @return array
 */
function vintern_autocomplete_callback($string = "", $no_autocomplete = false) {
    $string = addslashes($string);
    db_set_active('getif_data');
    $or = db_or()
        ->condition('p.tax_code', '%' . db_like($string) . '%', 'LIKE')
        ->condition('p.firstname', '%' . db_like($string) . '%', 'LIKE')
        ->condition('p.lastname', '%' . db_like($string) . '%', 'LIKE');
    $query = db_select('person', 'p');
    $query->fields('p');
    $query->condition($or);
    $query->where('p.meta_field LIKE \'%"is_voluntary":"1"%\'');
    $results = $query->execute();
    db_set_active();


    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id_person'     => $result->id_person,
            'tax_code'      => strtoupper($result->tax_code),
            'firstname'     => strtoupper($result->firstname),
            'lastname'      => strtoupper($result->lastname),
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['tax_code'] . ' - ' . $user['firstname'] . ' ' . $user['lastname'].'|'.$user['id_person']] = $user['tax_code'] . ' - ' . $user['firstname'] . ' ' . $user['lastname'];
    }
    if ($no_autocomplete == false) {
        drupal_json_output($matches);
    } else {
        return $matches;
    }
}

/* PERSON */
/**
 * @param string $string
 * @param bool $no_autocomplete
 * @return array
 */
function internship_intern_autocomplete_callback($string = "", $no_autocomplete = false) {
    // solo se extra curriculare - dipendente
    $string = addslashes($string);
    db_set_active('getif_data');
    $or = db_or()
        ->condition('t1.id_internship', '%' . db_like($string) . '%', 'LIKE')
        ->condition('t3.tax_code', '%' . db_like($string) . '%', 'LIKE')
        ->condition('t3.firstname', '%' . db_like($string) . '%', 'LIKE')
        ->condition('t3.lastname', '%' . db_like($string) . '%', 'LIKE');
    $query = db_select('internship', 't1');
    $query->innerJoin('internship_person','t2','t1.id_internship = t2.id_internship');
    $query->innerJoin('person','t3','t3.id_person = t2.id_person');
    $query->fields('t1',array('id_internship'));
    $query->fields('t3',array('id_person','firstname','lastname','tax_code'));
    $query->condition($or);
    $query->orderBy('t1.date_start');
    $query->where('t3.meta_field LIKE \'%"is_intern":"1"%\' AND t1.active = 1 AND t2.active = 1 AND t3.active = 1');
    $results = $query->execute();
    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id_internship' => $result->id_internship,
            'id_person'     => $result->id_person,
            'tax_code'      => strtoupper($result->tax_code),
            'firstname'     => strtoupper($result->firstname),
            'lastname'      => strtoupper($result->lastname),
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches['Tir. #'.$user['id_internship'].' '.$user['tax_code'] . ' - ' . $user['firstname'] . ' ' . $user['lastname'].'|'.$user['id_internship']] =
            'Tir. #'.$user['id_internship'].' '.$user['tax_code'] . ' - ' . $user['firstname'] . ' ' . $user['lastname'];
    }
    if ($no_autocomplete == false) {
        drupal_json_output($matches);
    } else {
        return $matches;
    }
}

/* callback autocompletamento persone giuridiche in base al ruolo */
/**
 * @param $id_lprole
 * @param string $string
 */
function lperson_by_lprole_autocomplete_callback($id_lprole, $string = "") {
    $string = addslashes($string);
    $tbl = "lperson_lprole";

    $or = db_or()
        ->condition('lp.tax_code', '%' . db_like($string) . '%', 'LIKE')
        ->condition('lp.name', '%' . db_like($string) . '%', 'LIKE');
    $and = db_and()
        ->condition('lpr.id_lprole',$id_lprole)
        ->condition('tbl.active', 1)
        ->condition('lpr.active', 1)
        ->condition('lp.active', 1);
    db_set_active('getif_data');
    $query = db_select($tbl,'tbl');
    $query ->join('lperson_lprole', 'lpr', 'tbl.id_lperson_lprole = lpr.id_lperson_lprole');
    $query->join('lperson','lp','lpr.id_lperson = lp.id_lperson AND lp.id_lperson IS NOT NULL');
    $query->leftJoin('lperson','lpp','lp.id_lperson_parent = lpp.id_lperson AND (lp.level = 1)');
    $query->condition($or);
    $query->condition($and);
    $query-> fields('lp');
    $query-> fields('lpr',array('id_lperson_lprole'));
    $query-> addField('lpp', 'name','parent_name');
    $results = $query->execute();
    db_set_active();

    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id_lperson_lprole'      => $result->id_lperson_lprole,
            'tax_code'      => $result->tax_code,
            'name'          => (!empty($result->parent_name)?$result->parent_name.' - ':'').$result->name
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['name'].'|'.$user['id_lperson_lprole']] = $user['tax_code'] . ' - ' . $user['name'];
    }
    drupal_json_output($matches);
}

/** callback autocompletamento persone giuridiche in base al ruolo e al tipo */
/**
 * @param $id_lprole
 * @param string $string
 */
function lperson_by_lprole_and_level_autocomplete_callback($id_lprole, $string = "") {
    $string = addslashes($string);
    $tbl = "lperson_lprole";

    $or = db_or()
        ->condition('lp.tax_code', '%' . db_like($string) . '%', 'LIKE')
        ->condition('lp.name', '%' . db_like($string) . '%', 'LIKE');
    $and = db_and()
        ->condition('lpr.id_lprole',$id_lprole)
        ->condition('tbl.active', 1)
        ->condition('lpr.active', 1)
        ->condition('lp.active', 1);
    db_set_active('getif_data');
    $query = db_select($tbl,'tbl');
    $query ->join('lperson_lprole', 'lpr', 'tbl.id_lperson_lprole = lpr.id_lperson_lprole');
    $query->join('lperson','lp','lpr.id_lperson = lp.id_lperson AND lp.id_lperson IS NOT NULL');
    $query->leftJoin('lperson','lpp','lp.id_lperson_parent = lpp.id_lperson AND (lp.level = 1)');
    $query->condition($or);
    $query->condition($and);
    $query-> fields('lp');
    $query-> fields('lpr',array('id_lperson_lprole'));
    $query-> addField('lpp', 'name','parent_name');
    $results = $query->execute();
    db_set_active();
    die();
    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id_lperson_lprole'      => $result->id_lperson_lprole,
            'tax_code'      => $result->tax_code,
            'name'          => (!empty($result->parent_name)?$result->parent_name.' - ':'').$result->name
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['name'].'|'.$user['id_lperson_lprole']] = $user['tax_code'] . ' - ' . $user['name'];
    }
    drupal_json_output($matches);
}


/* callback autocompletamento persone giuridiche in base al ruolo */
/**
 * @param $id_prole
 * @param string $string
 */
function lperson_by_prole_autocomplete_callback($id_prole, $string = "") {
    $string = addslashes($string);
    $tbl = "lperson_lprole";

    $or = db_or()
        ->condition('lp.tax_code', '%' . db_like($string) . '%', 'LIKE')
        ->condition('lp.name', '%' . db_like($string) . '%', 'LIKE');
    $and = db_and()
        ->condition('tbl.active', 1)
        ->condition('lpr.active', 1)
        ->condition('lp.active', 1)
        ->condition('prlpr.active', 1);
    db_set_active('getif_data');
    $query = db_select($tbl,'tbl');
    $query ->join('lperson_lprole', 'lpr', 'tbl.id_lperson_lprole = lpr.id_lperson_lprole');
    if ($id_prole >= 2) {
        $query->join('lperson', 'lp', 'lpr.id_lperson = lp.id_lperson AND lp.id_lperson IS NOT NULL AND lp.level = 1');
    } else {
        $query->join('lperson', 'lp', 'lpr.id_lperson = lp.id_lperson AND lp.id_lperson IS NOT NULL');
    }
    $query->leftJoin('lperson','lpp','lp.id_lperson_parent = lpp.id_lperson AND (lp.level = 1)');
    $query->join('lib_prole_lprole', 'prlpr', 'prlpr.id_lprole = lpr.id_lprole AND prlpr.id_prole = :id', array(':id' => $id_prole));
    $query->condition($or);
    $query->condition($and);
    $query-> fields('lp');
    $query-> fields('lpr',array('id_lperson_lprole'));
    $query-> addField('lpp', 'name','parent_name');
    $results = $query->execute();
    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id_lperson_lprole'      => $result->id_lperson,
            'tax_code'      => $result->tax_code,
            'name'          => (!empty($result->parent_name)?$result->parent_name.' - ':'').$result->name
        );
    }
    $matches = array();
    foreach ($users as $user) {
        if(strlen($user['tax_code']) == 36) { // se è un uuid
            $matches[$user['name'].'|'.$user['id_lperson_lprole']] = $user['name'];
        } else {
            $matches[$user['name'] . '|' . $user['id_lperson_lprole']] = $user['tax_code'] . ' - ' . $user['name'];
        }
    }
    drupal_json_output($matches);
}


/* callback autocompletamento persone giuridiche in base al ruolo */
/**
 * @param $id_prole
 * @param string $string
 */
function lperson_by_prole_and_level_autocomplete_callback($id_prole, $string = "") {
    $string = addslashes($string);
    $or = db_or()
        ->condition('t2.tax_code', '%' . db_like($string) . '%', 'LIKE')
        ->condition('t2.name', '%' . db_like($string) . '%', 'LIKE');
    $and = db_and()
        ->condition('t3.id_prole', $id_prole)
        ->condition('t1.active', 1)
        ->condition('t2.active', 1)
        ->condition('t3.active', 1)
        ->condition('t4.active', 1);
    db_set_active('getif_data');
    $query = db_select('lperson_lprole','t1');
    $query->innerJoin(
        'lperson',
        't2',
        't2.id_lperson = t1.id_lperson');
    $query->leftJoin(
        'lperson',
        't22',
        't22.id_lperson = t2.id_lperson_parent AND t2.level = 1 AND t22.level = 0');
    $query->innerJoin(
        'lib_prole_lprole',
        't3',
        't3.id_lprole = t1.id_lprole'
    );
    $query->join(
        'lib_prole_lperson_level',
        't4',
        't4.id_prole = t3.id_prole AND t4.id_lperson_level = t2.level'
    );
    $query->condition($or);
    $query->condition($and);
    $query-> fields('t2');
    $query->addField('t22', 'name','parent_name');
    $query-> fields('t1',array('id_lperson_lprole'));
    $results = $query->execute();
    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id_lperson_lprole'      => $result->id_lperson,
            'tax_code'      => $result->tax_code,
            'name'          => (!empty($result->parent_name)?$result->parent_name.' - ':'').$result->name
        );
    }
    $matches = array();
    foreach ($users as $user) {
        if(strlen($user['tax_code']) == 36) { // se è un uuid
            $matches[$user['name'].'|'.$user['id_lperson_lprole']] = $user['name'];
        } else {
            $matches[$user['name'] . '|' . $user['id_lperson_lprole']] = $user['name'] .' - '.$user['tax_code'];
        }
    }
    drupal_json_output($matches);
}

/* callback autocompletamento persone giuridiche in base alla posizone */
/**
 * @param $id_position
 * @param string $string
 */
function lperson_by_position_and_level_autocomplete_callback($id_position, $string = "") {
    $string = addslashes($string);
    $or = db_or()
        ->condition('t2.tax_code', '%' . db_like($string) . '%', 'LIKE')
        ->condition('t2.name', '%' . db_like($string) . '%', 'LIKE');
    $and = db_and()
        ->condition('t1.id_lprole', 2)
        ->condition('t4.id_position', $id_position)
        ->condition('t1.active', 1)
        ->condition('t2.active', 1)
        ->condition('t4.active', 1);
    db_set_active('getif_data');
    $query = db_select('lperson_lprole','t1');
    $query->innerJoin(
        'lperson',
        't2',
        't2.id_lperson = t1.id_lperson'
    );
    $query->leftJoin(
        'lperson',
        't3',
        't3.id_lperson = t2.id_lperson_parent AND t2.level = 1 AND t3.level = 0'
    );
    $query->join(
        'lib_position_lperson_level',
        't4',
        't4.id_lperson_level = t2.level'
    );
    $query->condition($or);
    $query->condition($and);
    $query-> fields('t1',array('id_lperson_lprole'));
    $query-> fields('t2');
    $query->addField('t3', 'name','parent_name');
    $results = $query->execute();
    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id_lperson_lprole'      => $result->id_lperson,
            'tax_code'      => $result->tax_code,
            'name'          => (!empty($result->parent_name)?$result->parent_name.' - ':'').$result->name
        );
    }
    $matches = array();
    foreach ($users as $user) {
        if(strlen($user['tax_code']) == 36) { // se è un uuid
            $matches[$user['name'].'|'.$user['id_lperson_lprole']] = $user['name'];
        } else {
            $matches[$user['name'] . '|' . $user['id_lperson_lprole']] = $user['name'] .' - '.$user['tax_code'];
        }
    }
    drupal_json_output($matches);
}


/**
 * @param $id_lprole
 * @param string $string
 */
function lperson_lprole_autocomplete_callback($id_lprole, $string = "") {
    /* 1 : promotore, 2 : ospitante */
    $string = addslashes($string);
    $query = "
        (SELECT t1.*, t1.tax_code, t2.id_lperson_lprole, CONCAT(t1.name) AS composite_name
        FROM `lperson` AS t1
        INNER JOIN `lperson_lprole` AS t2
        ON t1.id_lperson = t2.id_lperson AND t2.id_lprole = ".$id_lprole."
        WHERE (t1.level = 0 AND (t1.tax_code LIKE '%".$string."%' OR t1.vat_number LIKE '%".$string."%' OR t1.name LIKE '%".$string."%'))
        AND t1.active = 1 AND t2.active = 1)
    ";
    if($id_lprole == 1){ // se è un soggetto promotore prendo anche i record figli
        $query .= " UNION ALL
        (SELECT t1.*, t3.tax_code, t4.id_lperson_lprole, CONCAT(t1.name,' di ',t3.name) AS composite_name
        FROM `lperson` AS t1
        INNER JOIN `lperson` AS t3
        ON t1.id_lperson_parent = t3.id_lperson
        INNER JOIN `lperson_lprole` AS t2
        ON t1.id_lperson_parent = t2.id_lperson AND t2.id_lprole = ".$id_lprole."
        INNER JOIN `lperson_lprole` AS t4
        ON t1.id_lperson = t4.id_lperson AND t4.id_lprole = ".$id_lprole."
        WHERE (t1.level = 1 AND (t3.tax_code LIKE '%".$string."%' OR t1.vat_number LIKE '%".$string."%' OR CONCAT(t1.name,' di ',t3.name) LIKE '%".$string."%')) 
        AND t1.active = 1 AND t2.active = 1);";
    } else {
        $query .= ';';
    }
    db_set_active('getif_data');
    $results = db_query($query);
    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        $users[] = array(
            'id_lperson_lprole' => $result->id_lperson_lprole,
            'tax_code'      => $result->tax_code,
            'name'          => (empty($result->composite_name))?$result->name:$result->composite_name,
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['name'].'|'.$user['id_lperson_lprole']] = $user['tax_code'] . ' - ' . $user['name'];
    }
    drupal_json_output($matches);
}

/**
 * @param string $string
 */
function qualification_autocomplete_callback($string = "") {
    $string = addslashes($string);
    db_set_active('getif_data');
    $or = db_or()
        ->condition('name', '%' . db_like($string) . '%', 'LIKE')
        ->condition('description', '%' . db_like($string) . '%', 'LIKE');
    $results = db_select('lib_qualification', 'q')->fields('q')->condition($or)->execute();
    db_set_active();

    $records = array();
    while($result = $results->fetchObject()) {
        $records[] = array(
            'name'      => ucfirst($result->name),
        );
    }
    $matches = array();
    foreach ($records as $record) {
        $matches[$record['name']] = $record['name'];
    }
    drupal_json_output($matches);
}

/**
 * @param string $string
 */
function position_autocomplete_callback($string = "") {
    $string = addslashes($string);
    db_set_active('getif_data');
    $or = db_or()
        ->condition('name', '%' . db_like($string) . '%', 'LIKE')
        ->condition('description', '%' . db_like($string) . '%', 'LIKE');
    $and = db_and()
        ->condition('active',1);
    $results = db_select('lib_position', 'q')->fields('q')->condition($or)->condition($and)->execute();
    db_set_active();

    $records = array();
    while($result = $results->fetchObject()) {
        $records[] = array(
            'name'      => ucfirst($result->name),
        );
    }
    $matches = array();
    foreach ($records as $record) {
        $matches[$record['name']] = $record['name'];
    }
    drupal_json_output($matches);
}

/**
 * @param string $string
 */
function person_signatory_list_autocomplete_by_lperson_position_callback($id_lperson,$string = "") {
    $string = addslashes($string);
    db_set_active('getif_data');
    $results = db_query("
        SELECT t1.*,t2.description as title, t7.id_position, t7.description as position_name,t6.name as lperson_name
        FROM `person` AS t1
        INNER JOIN `lib_title` AS t2
        ON t1.id_title = t2.id_title
        INNER JOIN `person_lperson` AS t3
        ON t3.id_person = t1.id_person
        INNER JOIN `person_lperson_position` AS t4
        ON t4.id_person_lperson = t3.id_person_lperson
        INNER JOIN `lib_position_signatory` AS t5
        ON t5.id_position = t4.id_position
        INNER JOIN `lperson` AS t6
        ON t6.id_lperson = t3.id_lperson
        INNER JOIN `lib_position` AS t7
        ON t5.id_position = t7.id_position
        WHERE
        t1.meta_field NOT LIKE '%\"is_intern\":\"1\"%' AND
        t1.meta_field NOT LIKE '%\"is_voluntary\":\"1\"%' AND
        (t1.firstname LIKE '%".db_like($string) ."%' OR t1.lastname LIKE '%".db_like($string) ."%' OR t1.tax_code LIKE '%".db_like($string) ."%' OR t7.name LIKE '%".db_like($string) ."%') AND
        t6.id_lperson_parent = ".$id_lperson." AND
        t1.active = 1 AND
        t2.active = 1 AND
        t3.active = 1 AND
        t4.active = 1 AND
        t5.active = 1 AND
        t6.active = 1 AND
        t7.active = 1;
    ");
    db_set_active();
    $users = array();
    while($result = $results->fetchObject()) {
        $name = $result->tax_code . ' - ' . $result->firstname . ' ' . $result->lastname . '<br>(' . $result->position_name.' C/O '.$result->lperson_name . ')';
        $users[] = array(
            'id' => str_replace('<br>', ' ', $name). '|' . $result->id_person.','.$result->id_position,
            'name' => $name
        );
    }
    $matches = array();
    foreach ($users as $user) {
        $matches[$user['id']] = $user['name'];
    }
    drupal_json_output($matches);
}


/**
 * @param string $string
 */
function agreement_autocomplete_callback($string = "") {
    $string = addslashes($string);
    db_set_active('getif_data');
    $or = db_or()
        ->condition('number_code', '%' . db_like($string) . '%', 'LIKE');
    $and = db_and()
        ->condition('active',1);
    $results = db_select('agreement', 'a')->fields('a')->condition($or)->condition($and)->execute();
    db_set_active();

    $records = array();
    while($result = $results->fetchObject()) {
        $records[] = array(
            'name'      => strtoupper($result->number_code),
            'id'        => $result->id_agreement
        );
    }
    $matches = array();
    foreach ($records as $record) {
        $matches[$record['name'].'|'.$record['id']] = $record['name'];
    }
    drupal_json_output($matches);
}

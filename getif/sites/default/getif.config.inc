<?php

/*** ************************* ***/
/***        CONFIGURATION      ***/
/*** ************************* ***/

define("GETIF_YEAR_RANGE","0:+1");
/**
 *
 */
define("GETIF_TODAY",date("Y-m-d"));
/**
 *
 */
define("GETIF_FORMAT","d-m-Y");
/**
 *
 */
define("EMAIL_NOTIFY",FALSE);
/**
 *
 */
define("MAINTENANCE_EMAIL","");
/**
 *
 */
define("GETIF_HOST",1);
/**
 *
 */
define("GETIF_REPORT_YEAR_START",2017);
/**
 *
 */
define("GETIF_REPORT_YEAR_END",intval(date("Y")));
/**
 *
 */
const GETIF_VALIDATE_EXTENSIONS = array('doc docx odt pdf p7m jpg jpeg gif png txt csv xls pdf ppt pps ods odp');
/**
 *
 */
const MAPPING_DAYS = array(
    '0' => 'Lun',
    '1' => 'Mar',
    '2' => 'Mer',
    '3' => 'Gio',
    '4' => 'Ven',
    '5' => 'Sab',
    '6' => 'Dom',
);
const GETIF_REPORT_STATES = array(
    'all' => 'Tutti',
    'pending' => 'In attesa',
    'active' => 'Avviati',
    '7' => 'Conclusi',
    '0' => 'Interrotti',
);

define("T_STRUTT_COMPETENTE_ALLB", "Formazione - Biblioteca E Comunicazione");


/**
 *
 */
define("GETIF_REPORT_TIROCINI_CONVENZIONE_COLONNE","0-1-2-3-4-5-6-7-8-9-10-11-12-13-14-15-16-17-18-19-20");
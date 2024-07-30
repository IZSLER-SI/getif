--
-- Table structure for table `agreement`
--

DROP TABLE IF EXISTS `agreement`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `agreement` (
  `id_agreement` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_promoter` int(11) unsigned NOT NULL COMMENT 'fk tabella lperson_lprole',
  `id_host` int(11) unsigned NOT NULL COMMENT 'fk tabella lperson_lprole',
  `number_code` varchar(64) DEFAULT NULL,
  `date_start` date DEFAULT NULL,
  `date_end` date DEFAULT NULL,
  `date_application` date DEFAULT NULL,
  `internship_type` tinyint(1) DEFAULT NULL COMMENT '''curriculari'' = 1,''extracurriculari''= 2',
  `meta_attachment` text DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_agreement`),
  KEY `agreement_ibfk_1` (`id_promoter`),
  KEY `agreement_ibfk_2` (`id_host`),
  KEY `num_izsler` (`number_code`),
  KEY `agreement_active_index` (`active`),
  CONSTRAINT `agreement_ibfk_1` FOREIGN KEY (`id_promoter`) REFERENCES `lperson_lprole` (`id_lperson_lprole`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `agreement_ibfk_2` FOREIGN KEY (`id_host`) REFERENCES `lperson_lprole` (`id_lperson_lprole`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=130 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `agreement_attachment`
--

DROP TABLE IF EXISTS `agreement_attachment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `agreement_attachment` (
  `id_agreement_attachment` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_agreement` int(11) unsigned NOT NULL COMMENT 'fk agreement table',
  `id_file_managed` int(10) unsigned DEFAULT NULL COMMENT 'fid della tabella file_managed di Drupal',
  `date_application` date DEFAULT NULL,
  `meta` text DEFAULT NULL COMMENT 'campi aggiuntivi',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_agreement_attachment`),
  KEY `id_file_managed` (`id_file_managed`),
  KEY `id_agreement` (`id_agreement`) USING BTREE,
  KEY `agreement_attachment_active_index` (`active`),
  CONSTRAINT `agreement_attachment_ibfk_1` FOREIGN KEY (`id_agreement`) REFERENCES `agreement` (`id_agreement`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=129 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `budget`
--

DROP TABLE IF EXISTS `budget`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `budget` (
  `id_budget` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_lperson` int(11) unsigned DEFAULT NULL,
  `year` int(4) unsigned DEFAULT NULL,
  `a_amount` float(10,2) DEFAULT NULL COMMENT 'budget annuale',
  `a_amount_protocol` varchar(12) DEFAULT NULL COMMENT 'protocollo del documento per il budget',
  `a_extra_amount` float(10,2) DEFAULT NULL COMMENT 'extra-budget annuale',
  `a_extra_amount_protocol` varchar(12) DEFAULT NULL COMMENT 'protocollo del documento per l''extra-budget',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_budget`),
  KEY `id_lperson` (`id_lperson`),
  KEY `budget_active_index` (`active`),
  CONSTRAINT `budget_ibfk_1` FOREIGN KEY (`id_lperson`) REFERENCES `lperson` (`id_lperson`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `comuni`
--

DROP TABLE IF EXISTS `comuni`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `comuni` (
  `COM_ID` int(11) DEFAULT NULL,
  `ISTAT` varchar(16) DEFAULT NULL,
  `DESCRIZIONE` varchar(255) DEFAULT NULL,
  `CAP` varchar(16) DEFAULT NULL,
  `ID_FISCALE` varchar(16) DEFAULT NULL,
  `SUPERFICIE` float DEFAULT NULL,
  `PRO_ID` int(11) DEFAULT NULL,
  `DISTRETTO_ID` int(11) DEFAULT NULL,
  `DT_INIVAL` datetime DEFAULT NULL,
  `DT_FINVAL` datetime DEFAULT NULL,
  `REF_ID` int(11) DEFAULT NULL,
  `UTENTE_ID` int(11) DEFAULT NULL,
  `LATITUDINE_MIN` float DEFAULT NULL,
  `LATITUDINE_MAX` float DEFAULT NULL,
  `LONGITUDINE_MIN` float DEFAULT NULL,
  `LONGITUDINE_MAX` float DEFAULT NULL,
  `ID_COMUNE` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `cron`
--

DROP TABLE IF EXISTS `cron`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cron` (
  `id_cron_table` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `table_name` varchar(32) NOT NULL,
  `id_table` int(11) unsigned NOT NULL,
  `state` tinyint(3) unsigned NOT NULL,
  `date_expired` timestamp NULL DEFAULT NULL,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_cron_table`)
) ENGINE=InnoDB AUTO_INCREMENT=2886 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship`
--

DROP TABLE IF EXISTS `internship`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship` (
  `id_internship` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `flg_voluntary` tinyint(4) NOT NULL DEFAULT 0 COMMENT '0 - tirocinio, 1 - frequenza volontaria',
  `id_internship_type` int(11) unsigned DEFAULT NULL COMMENT 'fk tabella lib_internship_type',
  `date_application` date DEFAULT NULL,
  `date_start` date DEFAULT NULL COMMENT 'data di partenza prevista',
  `date_end` date DEFAULT NULL COMMENT 'data di fine prevista',
  `meta_flags` text DEFAULT NULL COMMENT 'flag visite mediche - json field {"flg1":"1", "flg2":"0", "flg3":"0"}',
  `note` text DEFAULT NULL COMMENT 'Note aggiuntive',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship`),
  KEY `id_internship_type` (`id_internship_type`),
  KEY `internship_active_index` (`active`),
  CONSTRAINT `internship_ibfk_1` FOREIGN KEY (`id_internship_type`) REFERENCES `lib_internship_type` (`id_internship_type`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1777 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_agreement`
--

DROP TABLE IF EXISTS `internship_agreement`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_agreement` (
  `id_internship_agreement` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship',
  `id_agreement` int(11) unsigned NOT NULL COMMENT 'fk agreement',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_agreement`),
  KEY `id_internship` (`id_internship`),
  KEY `id_agreement` (`id_agreement`),
  KEY `internship_agreement_active_index` (`active`),
  CONSTRAINT `internship_agreement_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `internship_agreement_ibfk_2` FOREIGN KEY (`id_agreement`) REFERENCES `agreement` (`id_agreement`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1679 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_attachment`
--

DROP TABLE IF EXISTS `internship_attachment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_attachment` (
  `id_internship_attachment` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship table',
  `id_file_managed` int(10) unsigned NOT NULL COMMENT 'fid della tabella file_managed di Drupal',
  `date_application` date DEFAULT NULL,
  `meta` text DEFAULT NULL COMMENT 'campi aggiuntivi',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_attachment`),
  KEY `id_internship` (`id_internship`),
  KEY `id_file_managed` (`id_file_managed`),
  KEY `internship_attachment_active_index` (`active`),
  CONSTRAINT `internship_attachment_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=9589 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_attendance_sheet`
--

DROP TABLE IF EXISTS `internship_attendance_sheet`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_attendance_sheet` (
  `id_internship_attendance_sheet` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship',
  `register` blob DEFAULT NULL COMMENT 'registro base64',
  `is_closed` tinyint(1) unsigned DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_attendance_sheet`),
  KEY `id_internship` (`id_internship`),
  KEY `internship_attendance_sheet_active_index` (`active`),
  CONSTRAINT `internship_attendance_sheet_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1551 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_attendance_sheet_20200909`
--

DROP TABLE IF EXISTS `internship_attendance_sheet_20200909`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_attendance_sheet_20200909` (
  `id_internship_attendance_sheet` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship',
  `register` blob DEFAULT NULL COMMENT 'registro base64',
  `is_closed` tinyint(1) unsigned DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_attendance_sheet`),
  KEY `id_internship` (`id_internship`)
) ENGINE=InnoDB AUTO_INCREMENT=464 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_budget`
--

DROP TABLE IF EXISTS `internship_budget`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_budget` (
  `id_internship_budget` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship table',
  `a_amount` float(10,2) DEFAULT NULL COMMENT 'budget annuale',
  `m_amount` float(10,2) DEFAULT NULL COMMENT 'budget mensile per il tirocinio extracurricolare',
  `i_m_duration` float(10,2) DEFAULT NULL COMMENT 'durata mensile del tirocinio extracurricolare',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_budget`),
  KEY `id_internship` (`id_internship`),
  KEY `internship_budget_active_index` (`active`),
  CONSTRAINT `internship_budget_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=67 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_host_tutor`
--

DROP TABLE IF EXISTS `internship_host_tutor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_host_tutor` (
  `id_internship_host_tutor` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship',
  `id_person_lperson_prole` int(11) unsigned NOT NULL COMMENT 'fk person_prole_lperson_lprole',
  `flg_primary` tinyint(1) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_host_tutor`),
  KEY `id_internship` (`id_internship`),
  KEY `id_person_lperson_prole` (`id_person_lperson_prole`),
  KEY `internship_host_tutor_active_index` (`active`),
  CONSTRAINT `internship_host_tutor_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `internship_host_tutor_ibfk_2` FOREIGN KEY (`id_person_lperson_prole`) REFERENCES `person_lperson_prole` (`id_person_lperson_prole`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1649 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_insurance`
--

DROP TABLE IF EXISTS `internship_insurance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_insurance` (
  `id_internship_insurance` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship',
  `rc_policy` text DEFAULT NULL COMMENT 'Assicurazione RC, json format {"company":"nome_compagnia","policy_number":"ADC1321"}',
  `accident_policy` text DEFAULT NULL COMMENT 'Assicurazione Infortuni, json format {"company":"nome_compagnia","policy_number":"ADC1321"}',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_insurance`),
  UNIQUE KEY `id_internship` (`id_internship`,`active`),
  KEY `internship_insurance_active_index` (`active`),
  CONSTRAINT `internship_insurance_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1691 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_lperson`
--

DROP TABLE IF EXISTS `internship_lperson`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_lperson` (
  `id_internship_lperson` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship table',
  `id_lperson` int(11) unsigned NOT NULL COMMENT 'fk internship_lperson',
  `flg_primary` tinyint(4) NOT NULL DEFAULT 0 COMMENT 'Flag che indica se la struttura è primaria o secondaria, primary - 1, secondary - 0',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `areas` text DEFAULT NULL,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_lperson`),
  KEY `id_internship` (`id_internship`),
  KEY `id_lperson` (`id_lperson`),
  KEY `internship_lperson_active_index` (`active`),
  CONSTRAINT `internship_lperson_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `internship_lperson_ibfk_2` FOREIGN KEY (`id_lperson`) REFERENCES `lperson` (`id_lperson`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1795 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_lperson_location_area`
--

DROP TABLE IF EXISTS `internship_lperson_location_area`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_lperson_location_area` (
  `id_internship_lperson_location_area` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship table',
  `id_lperson_location_area` int(11) unsigned NOT NULL COMMENT 'fk internship_lperson_location_area',
  `flg_primary` tinyint(4) NOT NULL DEFAULT 0 COMMENT 'Flag che indica se la struttura è primaria o secondaria, primary - 1, secondary - 0',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_lperson_location_area`),
  UNIQUE KEY `id_internship` (`id_internship`,`id_lperson_location_area`,`active`),
  KEY `internship_lperson_location_area_ibfk_2` (`id_lperson_location_area`),
  KEY `internship_lperson_location_area_active_index` (`active`),
  CONSTRAINT `internship_lperson_location_area_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `internship_lperson_location_area_ibfk_3` FOREIGN KEY (`id_lperson_location_area`) REFERENCES `lperson` (`id_lperson`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=3088 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_person`
--

DROP TABLE IF EXISTS `internship_person`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_person` (
  `id_internship_person` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship table',
  `id_person` int(11) unsigned NOT NULL COMMENT 'fk person table',
  `residence_address` text DEFAULT NULL,
  `domicile_address` text DEFAULT NULL,
  `phone` varchar(50) DEFAULT NULL,
  `email_address` varchar(50) DEFAULT NULL,
  `id_qualification` int(11) unsigned DEFAULT NULL,
  `qualification_detail` text DEFAULT NULL,
  `attended_course` text DEFAULT NULL,
  `id_intern_type` int(11) unsigned DEFAULT NULL,
  `working_time` text DEFAULT NULL,
  `meta_field` text DEFAULT NULL,
  `meta_attachment` text DEFAULT NULL,
  `position` text DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_person`),
  KEY `id_internship` (`id_internship`),
  KEY `id_person` (`id_person`),
  KEY `id_qualification` (`id_qualification`),
  KEY `id_intern_type` (`id_intern_type`),
  KEY `internship_person_active_index` (`active`),
  CONSTRAINT `internship_person_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `internship_person_ibfk_2` FOREIGN KEY (`id_person`) REFERENCES `person` (`id_person`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `internship_person_ibfk_3` FOREIGN KEY (`id_qualification`) REFERENCES `lib_qualification` (`id_qualification`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `internship_person_ibfk_4` FOREIGN KEY (`id_intern_type`) REFERENCES `lib_intern_type` (`id_intern_type`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1777 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_project_contact`
--

DROP TABLE IF EXISTS `internship_project_contact`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_project_contact` (
  `id_internship_project_contact` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship table',
  `id_person_lperson_prole` int(11) unsigned NOT NULL COMMENT 'fk person_prole_lperson_lprole',
  `flg_primary` tinyint(4) NOT NULL DEFAULT 0 COMMENT 'Flag che indica se il referente è primario o secondario, primary - 1, secondary - 0',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_project_contact`),
  KEY `id_internship` (`id_internship`),
  KEY `id_person_lperson_prole` (`id_person_lperson_prole`),
  KEY `internship_project_contact_active_index` (`active`),
  CONSTRAINT `internship_project_contact_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `internship_project_contact_ibfk_2` FOREIGN KEY (`id_person_lperson_prole`) REFERENCES `person_lperson_prole` (`id_person_lperson_prole`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1751 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_promoter_tutor`
--

DROP TABLE IF EXISTS `internship_promoter_tutor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_promoter_tutor` (
  `id_internship_promoter_tutor` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship table',
  `id_person_lperson_prole` int(11) unsigned NOT NULL COMMENT 'fk person_prole_lperson_lprole',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_promoter_tutor`),
  KEY `id_internship` (`id_internship`),
  KEY `id_person_lperson_prole` (`id_person_lperson_prole`),
  KEY `internship_promoter_tutor_active_index` (`active`),
  CONSTRAINT `internship_promoter_tutor_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `internship_promoter_tutor_ibfk_2` FOREIGN KEY (`id_person_lperson_prole`) REFERENCES `person_lperson_prole` (`id_person_lperson_prole`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1640 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_state`
--

DROP TABLE IF EXISTS `internship_state`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_state` (
  `id_internship_state` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship table',
  `state` tinyint(4) DEFAULT NULL COMMENT '0-annullato,1-richiesta,2comunicazione,3-approvato,4-attivo,5-attivo+proroga,6-concluso',
  `date_start` date DEFAULT NULL,
  `date_end_scheduled` date DEFAULT NULL,
  `date_end` date DEFAULT NULL,
  `date_extension` date DEFAULT NULL,
  `meta` text DEFAULT NULL COMMENT 'campi aggiuntivi',
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_state`),
  KEY `id_internship` (`id_internship`),
  KEY `internship_state_active_index` (`active`),
  KEY `internship_state_state_index` (`state`),
  CONSTRAINT `internship_state_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1777 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `internship_user`
--

DROP TABLE IF EXISTS `internship_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `internship_user` (
  `id_internship_agreement` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_internship` int(11) unsigned NOT NULL COMMENT 'fk internship table',
  `uid` int(11) unsigned NOT NULL COMMENT 'fk users drupal',
  `action` varchar(128) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_agreement`),
  KEY `id_internship` (`id_internship`),
  KEY `uid` (`uid`),
  KEY `internship_user_active_index` (`active`),
  CONSTRAINT `internship_user_ibfk_1` FOREIGN KEY (`id_internship`) REFERENCES `internship` (`id_internship`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `internship_user_ibfk_2` FOREIGN KEY (`uid`) REFERENCES `getif_drupal`.`users` (`uid`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8791 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_intern_type`
--

DROP TABLE IF EXISTS `lib_intern_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_intern_type` (
  `id_intern_type` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL COMMENT 'dipendente, borsista, esterno',
  `description` text DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_intern_type`),
  KEY `lib_intern_type_active_index` (`active`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_internship_type`
--

DROP TABLE IF EXISTS `lib_internship_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_internship_type` (
  `id_internship_type` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `flg_extra_curricular` tinyint(4) NOT NULL DEFAULT 0 COMMENT '0 - curricolare, 1 - extracurricolare',
  `name` varchar(50) NOT NULL COMMENT 'Curriculari universitari, alternanza scuola-lavoro, etc.',
  `description` text DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_internship_type`),
  KEY `lib_internship_type_active_index` (`active`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_lperson_level`
--

DROP TABLE IF EXISTS `lib_lperson_level`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_lperson_level` (
  `id_lperson_level` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `description` varchar(32) NOT NULL,
  `active` tinyint(1) NOT NULL,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_lperson_level`),
  KEY `lib_lperson_level_active_index` (`active`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_lprole`
--

DROP TABLE IF EXISTS `lib_lprole`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_lprole` (
  `id_lprole` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `description` text DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_lprole`),
  KEY `lib_lprole_active_index` (`active`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_position`
--

DROP TABLE IF EXISTS `lib_position`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_position` (
  `id_position` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `description` text DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_position`),
  KEY `lib_position_active_index` (`active`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_position_lperson_level`
--

DROP TABLE IF EXISTS `lib_position_lperson_level`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_position_lperson_level` (
  `id_prole_lprole` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_position` int(11) unsigned NOT NULL,
  `id_lperson_level` int(11) unsigned NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_prole_lprole`),
  KEY `id_prole` (`id_position`),
  KEY `id_lprole` (`id_lperson_level`),
  KEY `lib_position_lperson_level_active_index` (`active`),
  CONSTRAINT `lib_position_lperson_level_ibfk_1` FOREIGN KEY (`id_position`) REFERENCES `lib_position` (`id_position`) ON UPDATE CASCADE,
  CONSTRAINT `lib_position_lperson_level_ibfk_2` FOREIGN KEY (`id_lperson_level`) REFERENCES `lib_lperson_level` (`id_lperson_level`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_position_signatory`
--

DROP TABLE IF EXISTS `lib_position_signatory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_position_signatory` (
  `id_position_signatory` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_position` int(11) unsigned NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_position_signatory`),
  KEY `id_prole` (`id_position`),
  KEY `lib_position_signatory_active_index` (`active`),
  CONSTRAINT `lib_position_signatory_ibfk_1` FOREIGN KEY (`id_position`) REFERENCES `lib_position` (`id_position`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_prole`
--

DROP TABLE IF EXISTS `lib_prole`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_prole` (
  `id_prole` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `description` text DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_prole`),
  KEY `lib_prole_active_index` (`active`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_prole_lperson_level`
--

DROP TABLE IF EXISTS `lib_prole_lperson_level`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_prole_lperson_level` (
  `id_prole_lprole` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_prole` int(11) unsigned NOT NULL,
  `id_lperson_level` int(11) unsigned NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_prole_lprole`),
  KEY `id_prole` (`id_prole`),
  KEY `id_lprole` (`id_lperson_level`),
  KEY `lib_prole_lperson_level_active_index` (`active`),
  CONSTRAINT `lib_prole_lperson_level_ibfk_1` FOREIGN KEY (`id_prole`) REFERENCES `lib_prole` (`id_prole`) ON UPDATE CASCADE,
  CONSTRAINT `lib_prole_lperson_level_ibfk_2` FOREIGN KEY (`id_lperson_level`) REFERENCES `lib_lperson_level` (`id_lperson_level`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_prole_lprole`
--

DROP TABLE IF EXISTS `lib_prole_lprole`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_prole_lprole` (
  `id_prole_lprole` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_prole` int(11) unsigned NOT NULL,
  `id_lprole` int(11) unsigned NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_prole_lprole`),
  KEY `id_prole` (`id_prole`),
  KEY `id_lprole` (`id_lprole`),
  KEY `lib_prole_lprole_active_index` (`active`),
  CONSTRAINT `lib_prole_lprole_ibfk_1` FOREIGN KEY (`id_prole`) REFERENCES `lib_prole` (`id_prole`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `lib_prole_lprole_ibfk_2` FOREIGN KEY (`id_lprole`) REFERENCES `lib_lprole` (`id_lprole`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_qualification`
--

DROP TABLE IF EXISTS `lib_qualification`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_qualification` (
  `id_qualification` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL COMMENT 'Laurea in Medicina, Veterinaria, Ingegneria Genetica',
  `description` text DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_qualification`),
  KEY `lib_qualification_active_index` (`active`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lib_title`
--

DROP TABLE IF EXISTS `lib_title`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lib_title` (
  `id_title` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `description` text DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_title`),
  KEY `lib_title_active_index` (`active`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lperson`
--

DROP TABLE IF EXISTS `lperson`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lperson` (
  `id_lperson` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(128) NOT NULL,
  `seat` varchar(128) DEFAULT NULL,
  `vat_number` varchar(36) DEFAULT NULL,
  `tax_code` varchar(36) DEFAULT NULL,
  `address` text DEFAULT NULL,
  `phone` varchar(50) DEFAULT NULL,
  `fax` varchar(50) DEFAULT NULL,
  `email_address` varchar(50) DEFAULT NULL,
  `certified_email_address` varchar(50) DEFAULT NULL,
  `num_employers` smallint(5) unsigned DEFAULT NULL COMMENT 'Numero Dipendenti',
  `note` text DEFAULT NULL,
  `id_lperson_parent` int(11) unsigned DEFAULT NULL,
  `level` int(11) unsigned DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_lperson`),
  KEY `id_lperson_parent` (`id_lperson_parent`),
  KEY `tax_code` (`tax_code`),
  KEY `is_parent` (`level`),
  KEY `name` (`name`),
  KEY `lperson_active_index` (`active`),
  CONSTRAINT `lperson_ibfk_1` FOREIGN KEY (`id_lperson_parent`) REFERENCES `lperson` (`id_lperson`) ON UPDATE CASCADE,
  CONSTRAINT `lperson_ibfk_2` FOREIGN KEY (`level`) REFERENCES `lib_lperson_level` (`id_lperson_level`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=254 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`%`*/ /*!50003 TRIGGER `before_insert_lperson_tax_code` BEFORE INSERT ON `lperson` FOR EACH ROW IF NEW.tax_code IS NULL THEN 
	SET new.tax_code = uuid();
	SET new.vat_number = new.tax_code;
END IF */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `lperson_config`
--

DROP TABLE IF EXISTS `lperson_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lperson_config` (
  `id_lperson_config` int(11) NOT NULL AUTO_INCREMENT,
  `id_lperson` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id_lperson_config`),
  KEY `id_lperson` (`id_lperson`),
  CONSTRAINT `lperson_config_ibfk_1` FOREIGN KEY (`id_lperson`) REFERENCES `lperson` (`id_lperson`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lperson_location_area`
--

DROP TABLE IF EXISTS `lperson_location_area`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lperson_location_area` (
  `id_lperson_location_area` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_lperson` int(11) unsigned NOT NULL,
  `name` varchar(50) NOT NULL COMMENT 'Dipartimento, Laboratorio',
  `description` text DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_lperson_location_area`),
  KEY `id_lperson` (`id_lperson`),
  KEY `lperson_location_area_active_index` (`active`),
  CONSTRAINT `lperson_location_area_ibfk_1` FOREIGN KEY (`id_lperson`) REFERENCES `lperson` (`id_lperson`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lperson_lprole`
--

DROP TABLE IF EXISTS `lperson_lprole`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lperson_lprole` (
  `id_lperson_lprole` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_lperson` int(11) unsigned NOT NULL,
  `id_lprole` int(11) unsigned NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_lperson_lprole`),
  KEY `id_lperson` (`id_lperson`),
  KEY `id_lprole` (`id_lprole`),
  KEY `lperson_lprole_active_index` (`active`),
  CONSTRAINT `lperson_lprole_ibfk_1` FOREIGN KEY (`id_lperson`) REFERENCES `lperson` (`id_lperson`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `lperson_lprole_ibfk_2` FOREIGN KEY (`id_lprole`) REFERENCES `lib_lprole` (`id_lprole`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=147 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `person`
--

DROP TABLE IF EXISTS `person`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `person` (
  `id_person` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `firstname` varchar(50) NOT NULL,
  `lastname` varchar(50) NOT NULL,
  `id_title` int(11) unsigned DEFAULT NULL,
  `gender` varchar(1) DEFAULT NULL,
  `tax_code` varchar(50) DEFAULT NULL,
  `birthdate` date DEFAULT NULL,
  `birthplace` varchar(50) DEFAULT NULL,
  `residence_address` text DEFAULT NULL,
  `domicile_address` text DEFAULT NULL,
  `phone` varchar(50) DEFAULT NULL,
  `email_address` varchar(50) DEFAULT NULL,
  `id_qualification` int(11) unsigned DEFAULT NULL,
  `qualification_detail` text DEFAULT NULL,
  `meta_field` text NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_person`),
  KEY `id_title` (`id_title`),
  KEY `id_qualification` (`id_qualification`),
  KEY `tax_code` (`tax_code`),
  KEY `firstname` (`firstname`),
  KEY `lastname` (`lastname`),
  KEY `person_active_index` (`active`),
  CONSTRAINT `person_ibfk_1` FOREIGN KEY (`id_title`) REFERENCES `lib_title` (`id_title`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `person_ibfk_2` FOREIGN KEY (`id_qualification`) REFERENCES `lib_qualification` (`id_qualification`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1857 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `person_lperson`
--

DROP TABLE IF EXISTS `person_lperson`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `person_lperson` (
  `id_person_lperson` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_person` int(11) unsigned NOT NULL,
  `id_lperson` int(11) unsigned NOT NULL,
  `position` varchar(64) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_person_lperson`),
  KEY `id_person` (`id_person`),
  KEY `id_lperson` (`id_lperson`),
  KEY `person_lperson_active_index` (`active`),
  CONSTRAINT `person_lperson_ibfk_1` FOREIGN KEY (`id_person`) REFERENCES `person` (`id_person`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `person_lperson_ibfk_2` FOREIGN KEY (`id_lperson`) REFERENCES `lperson` (`id_lperson`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=540 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `person_lperson_position`
--

DROP TABLE IF EXISTS `person_lperson_position`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `person_lperson_position` (
  `id_person_lperson_position` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_person_lperson` int(11) unsigned NOT NULL,
  `id_position` int(11) unsigned NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_person_lperson_position`),
  KEY `id_person_lperson` (`id_person_lperson`),
  KEY `id_position` (`id_position`),
  KEY `person_lperson_position_active_index` (`active`),
  CONSTRAINT `person_lperson_position_ibfk_1` FOREIGN KEY (`id_person_lperson`) REFERENCES `person_lperson` (`id_person_lperson`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `person_lperson_position_ibfk_2` FOREIGN KEY (`id_position`) REFERENCES `lib_position` (`id_position`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=153 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `person_lperson_prole`
--

DROP TABLE IF EXISTS `person_lperson_prole`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `person_lperson_prole` (
  `id_person_lperson_prole` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `id_person_lperson` int(11) unsigned NOT NULL,
  `id_prole` int(11) unsigned NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT 1,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id_person_lperson_prole`),
  KEY `id_person_lperson` (`id_person_lperson`),
  KEY `id_prole` (`id_prole`),
  KEY `person_lperson_prole_active_index` (`active`),
  CONSTRAINT `person_lperson_prole_ibfk_1` FOREIGN KEY (`id_person_lperson`) REFERENCES `person_lperson` (`id_person_lperson`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `person_lperson_prole_ibfk_2` FOREIGN KEY (`id_prole`) REFERENCES `lib_prole` (`id_prole`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=581 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `profilo_utente`
--

DROP TABLE IF EXISTS `profilo_utente`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `profilo_utente` (
  `uid` bigint(20) NOT NULL COMMENT 'id utente',
  `id_person` int(11) unsigned DEFAULT 0 COMMENT 'id relazione',
  `cognome` text DEFAULT NULL COMMENT 'cognome',
  `nome` text DEFAULT NULL COMMENT 'nome',
  `tabella` text DEFAULT NULL COMMENT 'tabella relazione',
  `ruolo` text DEFAULT NULL,
  `date_add` timestamp NOT NULL DEFAULT current_timestamp(),
  `date_upd` timestamp NULL DEFAULT NULL,
  `active` tinyint(1) DEFAULT 1,
  PRIMARY KEY (`uid`),
  KEY `active` (`uid`),
  KEY `id_person` (`id_person`),
  KEY `profilo_utente_active_index` (`active`),
  CONSTRAINT `profilo_utente_ibfk_1` FOREIGN KEY (`id_person`) REFERENCES `person` (`id_person`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci COMMENT='tabella che contiene il profilo utente';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `province`
--

DROP TABLE IF EXISTS `province`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `province` (
  `PRO_ID` int(11) DEFAULT NULL,
  `SIGLA` varchar(2) DEFAULT NULL,
  `ISTAT` varchar(16) DEFAULT NULL,
  `NOME` varchar(16) DEFAULT NULL,
  `REG_ID` int(11) DEFAULT NULL,
  `DT_INIVAL` datetime DEFAULT NULL,
  `DT_FINVAL` datetime DEFAULT NULL,
  `REF_ID` int(11) DEFAULT NULL,
  `UTENTE_ID` int(11) DEFAULT NULL,
  `ID_PROVINCIA` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
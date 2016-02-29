
-- --------------------------------------------------------

--
-- Table structure for table `chrSkillHistory`
--

DROP TABLE IF EXISTS `chrSkillHistory`;

CREATE TABLE `chrSkillHistory` (
  `characterID` INT(10) UNSIGNED NOT NULL,
  `typeID` INT(10) UNSIGNED NOT NULL,
  `level` INT(10) UNSIGNED NOT NULL,
  `points` DOUBLE UNSIGNED NOT NULL,
  `spPerMin` DOUBLE UNSIGNED NOT NULL DEFAULT '0',
  `eventID` INT(10) UNSIGNED NOT NULL,
  `eventTime` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`characterID`, `typeID`, `level`, `eventTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

--
-- Dumping data for table `chrSkillHistory`
--




-- MySQL dump 10.15  Distrib 10.0.36-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: EVE_Crucible
-- ------------------------------------------------------
-- Server version	10.0.36-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `repStandingChanges`
--

DROP TABLE IF EXISTS `repStandingChanges`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `repStandingChanges` (
  `eventID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `eventTypeID` int(10) unsigned NOT NULL DEFAULT '0',
  `eventDateTime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `fromID` int(10) unsigned NOT NULL DEFAULT '0',
  `toID` int(10) unsigned NOT NULL DEFAULT '0',
  `modification` double NOT NULL DEFAULT '0',
  `originalFromID` int(10) unsigned NOT NULL DEFAULT '0',
  `originalToID` int(10) unsigned NOT NULL DEFAULT '0',
  `int_1` int(10) unsigned NOT NULL DEFAULT '0',
  `int_2` int(10) unsigned NOT NULL DEFAULT '0',
  `int_3` int(10) unsigned NOT NULL DEFAULT '0',
  `msg` text NOT NULL,
  PRIMARY KEY (`eventID`),
  KEY `fromID` (`fromID`),
  KEY `toID` (`toID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `repStandingChanges`
--

LOCK TABLES `repStandingChanges` WRITE;
/*!40000 ALTER TABLE `repStandingChanges` DISABLE KEYS */;
/*!40000 ALTER TABLE `repStandingChanges` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:51

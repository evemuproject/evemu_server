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
-- Table structure for table `chrDefaultOverviews`
--

DROP TABLE IF EXISTS `chrDefaultOverviews`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrDefaultOverviews` (
  `overviewID` int(11) NOT NULL DEFAULT '0',
  `overviewName` text COLLATE utf8_unicode_ci,
  `overviewShortName` text COLLATE utf8_unicode_ci,
  `overviewNameID` int(11) DEFAULT NULL,
  `dataID` int(11) DEFAULT NULL,
  PRIMARY KEY (`overviewID`),
  KEY `overviewNameID` (`overviewNameID`),
  KEY `dataID` (`dataID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrDefaultOverviews`
--

LOCK TABLES `chrDefaultOverviews` WRITE;
/*!40000 ALTER TABLE `chrDefaultOverviews` DISABLE KEYS */;
INSERT INTO `chrDefaultOverviews` VALUES (3,'PvP','defaultpvp',59570,16533082),(4,'Mining','defaultmining',59571,16533083),(5,'WarpTo','defaultwarpto',59572,16533084),(6,'Loot','defaultloot',59573,16533085),(8,'All','defaultall',59574,16533086),(12,'Drones','defaultdrones',59575,16533087),(13,'General','default',59576,16533088);
/*!40000 ALTER TABLE `chrDefaultOverviews` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:47

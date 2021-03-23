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
-- Table structure for table `crpMedalData`
--

DROP TABLE IF EXISTS `crpMedalData`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crpMedalData` (
  `medalID` int(11) NOT NULL,
  `part` tinyint(1) NOT NULL,
  `graphic` varchar(150) COLLATE utf8_unicode_ci NOT NULL,
  `color` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crpMedalData`
--

LOCK TABLES `crpMedalData` WRITE;
/*!40000 ALTER TABLE `crpMedalData` DISABLE KEYS */;
INSERT INTO `crpMedalData` VALUES (8,1,'Caldari.1_1',-1),(8,1,'Caldari.1_2',-330271),(8,2,'compass.1_1',-1),(1,1,'Caldari.1_1',-1),(1,1,'Caldari.1_2',-330271),(1,2,'compass.1_1',-1),(2,1,'Caldari.1_1',-1),(2,1,'Caldari.1_2',-330271),(2,2,'compass.1_1',-1),(3,1,'Caldari.1_1',-1),(3,1,'Caldari.1_2',-330271),(3,2,'compass.1_1',-1),(4,1,'Caldari.1_1',-1),(4,1,'Caldari.1_2',-330271),(4,2,'compass.1_1',-1),(5,1,'Caldari.1_1',-1),(5,1,'Caldari.1_2',-330271),(5,2,'compass.1_1',-1),(6,1,'Caldari.1_1',-1),(6,1,'Caldari.1_2',-330271),(6,2,'compass.1_1',-1),(7,1,'Caldari.1_1',-1),(7,1,'Caldari.1_2',-330271),(7,2,'compass.1_1',-1);
/*!40000 ALTER TABLE `crpMedalData` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:49

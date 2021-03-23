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
-- Table structure for table `tutorials`
--

DROP TABLE IF EXISTS `tutorials`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tutorials` (
  `tutorialID` int(10) unsigned NOT NULL DEFAULT '0',
  `tutorialName` varchar(100) NOT NULL,
  `nextTutorialID` int(10) unsigned DEFAULT NULL,
  `categoryID` int(10) unsigned NOT NULL,
  PRIMARY KEY (`tutorialID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tutorials`
--

LOCK TABLES `tutorials` WRITE;
/*!40000 ALTER TABLE `tutorials` DISABLE KEYS */;
INSERT INTO `tutorials` VALUES (5,'Aura : Station Tutorial',6,1),(6,'Ship Hangar and boarding',7,1),(7,'Character Sheet',8,1),(8,'The Items Hangar',9,1),(9,'Reprocessing - Selling minerals',11,1),(11,'Wallet',12,1),(12,'Market',13,1),(13,'Fittings, station service',14,1),(14,'Map',16,1),(15,'Communication with other pilots',23,1),(16,'Undock',NULL,1),(17,'Aura : Flight tutorial',37,1),(18,'Navigation, manual',21,1),(19,'Navigation, Automatic',38,1),(21,'Overview',19,1),(23,'The Warp Drive',28,1),(24,'Reap the rewards',31,1),(27,'Aura : Being pod-killed',NULL,1),(28,'Attack the Pirate!',24,1),(31,'Activating Acceleration Gate',34,1),(32,'Assets',48,1),(33,'Corporations and applying',45,1),(34,'Engage more dangerous enemies',35,1),(35,'Mining',36,1),(36,'Attain the prize container',39,1),(37,'The Control Console',18,1),(38,'Lock/unlock & Concord',15,1),(39,'Returning home',40,1),(40,'Reprocess veldspar',32,1),(41,'Aura : Insurance',NULL,1),(42,'Aura : Cloning',NULL,1),(43,'Aura : Losing a ship',NULL,1),(44,'Agents',47,1),(45,'Help',44,1),(46,'Repairshop',33,1),(47,'Revealing the full UI',NULL,1),(48,'Map & travel planning',49,1),(49,'Use Assets to set destination',46,1),(50,'Aura : Creating a chat channel',NULL,1),(51,'Aura : Insufficient skill to fit a module',NULL,1);
/*!40000 ALTER TABLE `tutorials` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:54

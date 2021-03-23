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
-- Table structure for table `chrSkins`
--

DROP TABLE IF EXISTS `chrSkins`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrSkins` (
  `skinID` int(10) unsigned NOT NULL DEFAULT '0',
  `skinName` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`skinID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrSkins`
--

LOCK TABLES `chrSkins` WRITE;
/*!40000 ALTER TABLE `chrSkins` DISABLE KEYS */;
INSERT INTO `chrSkins` VALUES (1,'1'),(2,'2'),(3,'3'),(4,'4'),(5,'5'),(6,'6'),(7,'7'),(8,'8'),(9,'10'),(10,'11'),(11,'9'),(12,'Normal'),(13,'Bright'),(14,'Pale'),(15,'Smooth'),(16,'Tan'),(17,'Ancient'),(18,'Contrasted'),(19,'Old'),(20,'Golden'),(21,'regular'),(22,'Sick'),(23,'Dark'),(24,'Caldari'),(25,'12'),(26,'glossy'),(27,'oily'),(28,'veins'),(29,'redveins'),(30,'Asian 1'),(31,'Brown smooth'),(32,'Brown'),(33,'Fair asian'),(34,'Fair'),(35,'Fairest'),(36,'Normal shiny'),(37,'Very bright'),(38,'Smooth pale'),(39,'Smooth asian'),(40,'Fair shiny 2'),(41,'Fair shiny'),(42,'Brown shiny'),(43,'Asian 3'),(44,'Asian 2'),(45,'Soft pale'),(46,'Soft dark asian'),(47,'Soft asian'),(48,'Reynir'),(49,'Japanes'),(50,'Normal smooth'),(51,'Normal glossy'),(52,'Glossy asian'),(53,'Asian glossy 2'),(54,'Smooth lowgloss'),(55,'Smooth glossy'),(56,'Lowgloss'),(57,'Hi contrast gloss'),(58,'Glossy'),(59,'Dark tone'),(60,'Smooth contrast'),(61,'Middle east dark'),(62,'Glossy 2'),(63,'Asian light'),(64,'Asian dark'),(65,'Asian'),(66,'Hicontrast'),(67,'Tanned'),(68,'Nocturnal'),(69,'Light asian'),(70,'Dark asian'),(71,'Casual');
/*!40000 ALTER TABLE `chrSkins` ENABLE KEYS */;
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

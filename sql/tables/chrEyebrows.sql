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
-- Table structure for table `chrEyebrows`
--

DROP TABLE IF EXISTS `chrEyebrows`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrEyebrows` (
  `eyebrowsID` int(10) unsigned NOT NULL DEFAULT '0',
  `eyebrowsName` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`eyebrowsID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrEyebrows`
--

LOCK TABLES `chrEyebrows` WRITE;
/*!40000 ALTER TABLE `chrEyebrows` DISABLE KEYS */;
INSERT INTO `chrEyebrows` VALUES (1,'1'),(2,'10'),(3,'11'),(4,'2'),(5,'3'),(6,'4'),(7,'5'),(8,'6'),(9,'7'),(10,'8'),(11,'9'),(12,'Normal'),(13,'Strong'),(14,'13'),(15,'14'),(16,'12'),(17,'Light'),(18,'None'),(19,'Blonde Thin'),(20,'Delicate brown'),(21,'Evil'),(22,'Evil brown'),(23,'Small black curve'),(24,'Thin black curve'),(25,'Thin white'),(26,'Wicked blond'),(27,'Hairy'),(28,'Heavy'),(29,'07'),(30,'08'),(31,'09'),(32,'Black heavy'),(33,'Normal heavy'),(34,'Thin'),(35,'Thin black'),(36,'15'),(37,'16'),(38,'Med black'),(39,'Black straight'),(40,'Thin straight 2'),(41,'Thin black 2'),(42,'Med curve'),(43,'Thin straight'),(44,'Thin dark'),(45,'Thin black2'),(46,'Med curve 2'),(47,'Pearl strong'),(48,'Pearl medium'),(49,'Pearl'),(50,'none'),(51,'Grey Ruffled'),(52,'Grey Medium'),(53,'Dark Thin Stern'),(54,'Dark Thin Long'),(55,'Dark Thin'),(56,'Dark Thick'),(57,'Dark Stern'),(58,'Dark Small Thin'),(59,'Dark Short Thick'),(60,'Dark Ruffled'),(61,'Dark Medium 2'),(62,'Dark Medium'),(63,'Dark Grey Thick'),(64,'Brown Medium'),(65,'Thin Grey'),(66,'Thin Dark'),(67,'Thin Brown'),(68,'Thick Dark'),(69,'Thick Brown'),(70,'Short Dark'),(71,'Ruffled Grey'),(72,'Ruffled Dark'),(73,'Medium Dark'),(74,'Arched Dark'),(75,'Arched Brown'),(76,'Angled Dark'),(77,'Grey Thin'),(78,'Dark Very Thin'),(79,'Dark Thin Cunning'),(80,'Dark Fuzzy'),(81,'Brown Thin'),(82,'Brown Thick');
/*!40000 ALTER TABLE `chrEyebrows` ENABLE KEYS */;
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

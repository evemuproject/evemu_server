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
-- Table structure for table `chrEyes`
--

DROP TABLE IF EXISTS `chrEyes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrEyes` (
  `eyesID` int(10) unsigned NOT NULL DEFAULT '0',
  `eyesName` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`eyesID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrEyes`
--

LOCK TABLES `chrEyes` WRITE;
/*!40000 ALTER TABLE `chrEyes` DISABLE KEYS */;
INSERT INTO `chrEyes` VALUES (1,'BlueV2'),(2,'Brightgrey'),(3,'BrownV2'),(4,'Darkgreen'),(5,'Darkgrey'),(6,'Deep brown'),(7,'Deep ocean'),(8,'GoldenV2'),(9,'Greengraybright'),(10,'Moss'),(11,'Redbrown'),(12,'Reptile'),(13,'Stinging blue'),(14,'Stinging green'),(15,'Stinging grey'),(16,'Stinging greyblue'),(17,'Natural green'),(18,'Gold'),(19,'Grey'),(20,'Greyblue'),(21,'Orange'),(22,'Yellow'),(23,'Moss brown'),(24,'Friendly deep brown'),(25,'Dark grey'),(26,'Stinging beige'),(27,'Moss friendly'),(28,'Lightbrown'),(29,'Deepbrown'),(30,'Browngreen'),(31,'Very dark hirefract 2'),(32,'Very dark hirefract'),(33,'Light grey hirefract'),(34,'Greyish'),(35,'Grey brown'),(36,'Golden grey'),(37,'Brownred hirefract'),(38,'Brown'),(39,'Bright yellow'),(40,'Bright grey'),(41,'Standard'),(42,'Small pupil brown'),(43,'Serpent'),(44,'Orange brown'),(45,'Dark brown');
/*!40000 ALTER TABLE `chrEyes` ENABLE KEYS */;
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

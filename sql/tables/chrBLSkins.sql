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
-- Table structure for table `chrBLSkins`
--

DROP TABLE IF EXISTS `chrBLSkins`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrBLSkins` (
  `bloodlineID` int(10) unsigned NOT NULL DEFAULT '0',
  `gender` int(10) unsigned NOT NULL DEFAULT '0',
  `skinID` int(10) unsigned NOT NULL DEFAULT '0',
  `npc` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`bloodlineID`,`gender`,`skinID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrBLSkins`
--

LOCK TABLES `chrBLSkins` WRITE;
/*!40000 ALTER TABLE `chrBLSkins` DISABLE KEYS */;
INSERT INTO `chrBLSkins` VALUES (1,0,1,0),(1,0,2,0),(1,0,3,0),(1,0,4,0),(1,0,5,0),(1,0,6,0),(1,0,7,0),(1,1,1,0),(1,1,2,0),(1,1,3,0),(1,1,4,0),(1,1,5,0),(1,1,7,0),(1,1,8,0),(1,1,11,0),(2,0,1,0),(2,0,2,0),(2,0,3,0),(2,0,4,0),(2,0,5,0),(2,0,6,0),(2,0,7,0),(2,0,8,0),(2,0,11,0),(2,1,1,0),(2,1,2,0),(2,1,3,0),(2,1,4,0),(2,1,5,0),(2,1,6,0),(2,1,7,0),(2,1,8,0),(3,0,1,0),(3,0,2,0),(3,0,3,0),(3,0,4,0),(3,0,5,0),(3,0,6,0),(3,0,7,0),(3,0,8,0),(3,0,12,0),(3,0,13,0),(3,0,14,0),(3,0,15,0),(3,0,16,0),(3,1,1,0),(3,1,2,0),(3,1,3,0),(3,1,4,0),(3,1,5,0),(3,1,12,0),(3,1,14,0),(3,1,17,0),(3,1,18,0),(3,1,19,0),(4,0,1,0),(4,0,2,0),(4,0,3,0),(4,0,4,0),(4,0,5,0),(4,0,6,0),(4,0,7,0),(4,0,8,0),(4,1,1,0),(4,1,2,0),(4,1,3,0),(4,1,4,0),(4,1,5,0),(4,1,7,0),(4,1,8,0),(4,1,9,0),(4,1,10,0),(4,1,11,0),(4,1,12,0),(5,0,1,0),(5,0,2,0),(5,0,3,0),(5,0,4,0),(5,0,5,0),(5,0,6,0),(5,1,1,0),(5,1,2,0),(5,1,3,0),(5,1,4,0),(5,1,5,0),(5,1,12,0),(5,1,20,0),(5,1,21,0),(5,1,22,0),(6,0,1,0),(6,0,2,0),(6,0,3,0),(6,0,4,0),(6,0,5,0),(6,0,6,0),(6,0,7,0),(6,0,8,0),(6,1,1,0),(6,1,2,0),(6,1,3,0),(6,1,4,0),(6,1,5,0),(6,1,6,0),(6,1,12,0),(6,1,13,0),(6,1,14,0),(6,1,22,0),(6,1,23,0),(6,1,24,0),(7,0,1,0),(7,0,2,0),(7,0,3,0),(7,0,4,0),(7,0,5,0),(7,0,6,0),(7,0,7,0),(7,0,8,0),(7,0,9,0),(7,0,11,0),(7,1,1,0),(7,1,2,0),(7,1,3,0),(7,1,4,0),(7,1,5,0),(7,1,7,0),(7,1,8,0),(7,1,9,0),(7,1,10,0),(7,1,11,0),(7,1,25,0),(8,0,1,0),(8,0,2,0),(8,0,3,0),(8,0,4,0),(8,0,5,0),(8,0,6,0),(8,1,1,0),(8,1,2,0),(8,1,3,0),(8,1,4,0),(8,1,5,0),(8,1,6,0),(8,1,7,0),(8,1,26,0),(8,1,27,0),(10,1,28,0),(10,1,29,0),(11,0,50,0),(11,0,51,0),(11,0,52,0),(11,0,53,0),(11,1,12,0),(11,1,22,0),(11,1,52,0),(11,1,54,0),(11,1,55,0),(11,1,56,0),(11,1,57,0),(11,1,58,0),(11,1,59,0),(12,0,14,0),(12,0,45,0),(12,0,46,0),(12,0,47,0),(12,0,48,0),(12,0,49,0),(12,1,12,0),(12,1,13,0),(12,1,15,0),(12,1,22,0),(12,1,58,0),(12,1,60,0),(12,1,65,0),(12,1,66,0),(13,0,14,0),(13,0,30,0),(13,0,31,0),(13,0,32,0),(13,0,33,0),(13,0,34,0),(13,0,35,0),(13,0,36,0),(13,0,44,0),(13,1,13,0),(13,1,14,0),(13,1,67,0),(13,1,68,0),(13,1,69,0),(13,1,70,0),(13,1,71,0),(14,0,37,0),(14,0,38,0),(14,0,39,0),(14,0,40,0),(14,0,41,0),(14,0,42,0),(14,0,43,0),(14,0,44,0),(14,1,12,0),(14,1,58,0),(14,1,60,0),(14,1,61,0),(14,1,62,0),(14,1,63,0),(14,1,64,0),(14,1,65,0);
/*!40000 ALTER TABLE `chrBLSkins` ENABLE KEYS */;
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

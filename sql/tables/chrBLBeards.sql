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
-- Table structure for table `chrBLBeards`
--

DROP TABLE IF EXISTS `chrBLBeards`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrBLBeards` (
  `bloodlineID` int(10) unsigned NOT NULL DEFAULT '0',
  `gender` int(10) unsigned NOT NULL DEFAULT '0',
  `beardID` int(10) unsigned NOT NULL DEFAULT '0',
  `npc` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`bloodlineID`,`gender`,`beardID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrBLBeards`
--

LOCK TABLES `chrBLBeards` WRITE;
/*!40000 ALTER TABLE `chrBLBeards` DISABLE KEYS */;
INSERT INTO `chrBLBeards` VALUES (1,1,2,0),(1,1,3,0),(1,1,10,0),(1,1,12,0),(1,1,13,0),(1,1,14,0),(1,1,15,0),(1,1,16,0),(1,1,19,0),(1,1,20,0),(1,1,21,0),(1,1,22,0),(1,1,23,0),(2,1,1,0),(2,1,2,0),(2,1,3,0),(2,1,4,0),(2,1,5,0),(2,1,6,0),(2,1,7,0),(2,1,8,0),(2,1,9,0),(2,1,10,0),(2,1,12,0),(2,1,13,0),(2,1,14,0),(2,1,15,0),(2,1,16,0),(2,1,17,0),(2,1,18,0),(2,1,19,0),(2,1,20,0),(4,1,1,0),(4,1,2,0),(4,1,3,0),(4,1,4,0),(4,1,5,0),(4,1,6,0),(4,1,7,0),(4,1,8,0),(4,1,9,0),(4,1,10,0),(4,1,11,0),(4,1,12,0),(4,1,13,0),(4,1,14,0),(4,1,15,0),(4,1,16,0),(7,1,1,0),(7,1,3,0),(7,1,6,0),(7,1,8,0),(7,1,9,0),(7,1,10,0),(7,1,11,0),(7,1,12,0),(7,1,13,0),(7,1,14,0),(7,1,15,0),(7,1,16,0),(7,1,18,0),(7,1,19,0),(7,1,20,0),(7,1,24,0),(7,1,25,0),(7,1,26,0),(7,1,27,0),(7,1,28,0),(7,1,29,0),(8,1,1,0),(8,1,2,0),(8,1,6,0),(8,1,7,0),(8,1,8,0),(8,1,9,0),(8,1,10,0),(8,1,12,0),(8,1,15,0),(8,1,16,0),(8,1,18,0),(8,1,26,0),(8,1,30,0),(11,1,16,0),(11,1,31,0),(12,1,16,0),(12,1,33,0),(12,1,34,0),(13,1,31,0),(13,1,35,0),(13,1,36,0),(13,1,37,0),(14,1,16,0),(14,1,31,0),(14,1,32,0);
/*!40000 ALTER TABLE `chrBLBeards` ENABLE KEYS */;
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

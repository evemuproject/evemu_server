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
-- Table structure for table `chrBLLipsticks`
--

DROP TABLE IF EXISTS `chrBLLipsticks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrBLLipsticks` (
  `bloodlineID` int(10) unsigned NOT NULL DEFAULT '0',
  `gender` int(10) unsigned NOT NULL DEFAULT '0',
  `lipstickID` int(10) unsigned NOT NULL DEFAULT '0',
  `npc` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`bloodlineID`,`gender`,`lipstickID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrBLLipsticks`
--

LOCK TABLES `chrBLLipsticks` WRITE;
/*!40000 ALTER TABLE `chrBLLipsticks` DISABLE KEYS */;
INSERT INTO `chrBLLipsticks` VALUES (1,0,1,0),(1,0,2,0),(1,0,3,0),(1,0,4,0),(1,0,5,0),(1,0,6,0),(1,0,9,0),(1,0,12,0),(1,0,14,0),(1,0,17,0),(1,0,24,0),(1,0,25,0),(1,0,26,0),(1,0,37,0),(1,0,38,0),(1,0,40,0),(1,0,41,0),(2,0,1,0),(2,0,2,0),(2,0,3,0),(2,0,4,0),(2,0,5,0),(2,0,6,0),(2,0,9,0),(2,0,12,0),(2,0,14,0),(2,0,17,0),(2,0,24,0),(2,0,25,0),(2,0,26,0),(2,0,37,0),(2,0,38,0),(2,0,39,0),(2,0,40,0),(2,0,41,0),(3,0,7,0),(3,0,8,0),(3,0,9,0),(3,0,10,0),(3,0,11,0),(3,0,12,0),(3,0,13,0),(3,0,14,0),(3,0,15,0),(3,0,16,0),(3,0,17,0),(3,0,18,0),(3,0,20,0),(3,0,21,0),(3,0,22,0),(3,0,23,0),(3,0,24,0),(3,0,25,0),(3,0,26,0),(3,0,27,0),(4,0,1,0),(4,0,2,0),(4,0,3,0),(4,0,4,0),(4,0,5,0),(4,0,6,0),(4,0,7,0),(4,0,8,0),(4,0,9,0),(4,0,10,0),(4,0,11,0),(4,0,12,0),(4,0,13,0),(4,0,14,0),(4,0,15,0),(4,0,16,0),(4,0,17,0),(4,0,18,0),(4,0,19,0),(4,0,20,0),(4,0,21,0),(5,0,17,0),(5,0,18,0),(5,0,28,0),(5,0,29,0),(5,0,30,0),(5,0,31,0),(5,0,32,0),(5,0,33,0),(5,0,34,0),(5,0,35,0),(5,0,36,0),(6,0,1,0),(6,0,2,0),(6,0,4,0),(6,0,5,0),(6,0,24,0),(6,0,25,0),(6,0,26,0),(6,0,37,0),(6,0,38,0),(7,0,1,0),(7,0,2,0),(7,0,3,0),(7,0,4,0),(7,0,5,0),(7,0,6,0),(7,0,7,0),(7,0,9,0),(7,0,12,0),(7,0,14,0),(7,0,17,0),(7,0,18,0),(7,0,22,0),(7,0,23,0),(7,0,24,0),(7,0,25,0),(7,0,26,0),(7,0,27,0),(7,0,37,0),(7,0,38,0),(7,0,42,0),(7,0,43,0),(7,0,44,0),(7,0,45,0),(7,0,46,0),(7,0,47,0),(8,0,1,0),(8,0,2,0),(8,0,3,0),(8,0,4,0),(8,0,5,0),(8,0,6,0),(8,0,7,0),(8,0,9,0),(8,0,12,0),(8,0,14,0),(8,0,17,0),(8,0,18,0),(8,0,22,0),(8,0,23,0),(8,0,24,0),(8,0,25,0),(8,0,26,0),(8,0,27,0),(8,0,37,0),(8,0,38,0),(8,0,42,0),(8,0,43,0),(8,0,44,0),(8,0,45,0),(8,0,46,0),(8,0,47,0),(11,0,55,0),(11,0,56,0),(11,0,57,0),(11,0,58,0),(11,0,59,0),(11,0,60,0),(12,0,12,0),(12,0,17,0),(12,0,48,0),(12,0,49,0),(12,0,50,0),(12,0,51,0),(12,0,52,0),(12,0,53,0),(12,0,54,0),(13,0,17,0),(13,0,55,0),(13,0,61,0),(13,0,62,0),(13,0,63,0),(13,0,64,0),(13,0,65,0),(13,0,66,0),(13,0,67,0),(13,0,68,0),(14,0,17,0),(14,0,18,0),(14,0,28,0),(14,0,29,0),(14,0,30,0),(14,0,31,0),(14,0,32,0),(14,0,33,0),(14,0,34,0),(14,0,36,0);
/*!40000 ALTER TABLE `chrBLLipsticks` ENABLE KEYS */;
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

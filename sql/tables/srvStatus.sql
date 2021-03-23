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
-- Table structure for table `srvStatus`
--

DROP TABLE IF EXISTS `srvStatus`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `srvStatus` (
  `AI` int(10) NOT NULL AUTO_INCREMENT,
  `srvName` varchar(60) NOT NULL,
  `Online` bit(1) NOT NULL DEFAULT b'0',
  `startTime` bigint(20) NOT NULL,
  `ClientSeed` int(10) NOT NULL,
  `Connections` smallint(6) NOT NULL,
  `threads` tinyint(4) NOT NULL,
  `rss` decimal(6,3) NOT NULL,
  `vm` decimal(6,3) NOT NULL,
  `user` decimal(4,2) NOT NULL,
  `kernel` decimal(4,2) NOT NULL,
  `items` int(10) NOT NULL,
  `systems` int(10) NOT NULL,
  `bubbles` int(10) NOT NULL,
  `updateTime` int(10) NOT NULL,
  `npcs` int(10) NOT NULL,
  PRIMARY KEY (`AI`),
  UNIQUE KEY `AI` (`AI`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `srvStatus`
--

LOCK TABLES `srvStatus` WRITE;
/*!40000 ALTER TABLE `srvStatus` DISABLE KEYS */;
INSERT INTO `srvStatus` VALUES (1,'Test',1,1562794810,1,1,5,195.801,18.862,5.94,8.25,123,1,16,1562800496,0);
/*!40000 ALTER TABLE `srvStatus` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:52

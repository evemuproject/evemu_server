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
-- Table structure for table `qstMining`
--

DROP TABLE IF EXISTS `qstMining`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `qstMining` (
  `id` int(5) NOT NULL DEFAULT '0',
  `briefingID` int(5) NOT NULL DEFAULT '0',
  `name` text,
  `level` tinyint(1) NOT NULL DEFAULT '0',
  `typeID` tinyint(1) NOT NULL DEFAULT '0',
  `sysRange` tinyint(2) NOT NULL DEFAULT '1',
  `important` bit(1) NOT NULL DEFAULT b'0',
  `storyline` bit(1) NOT NULL DEFAULT b'0',
  `raceID` tinyint(2) NOT NULL DEFAULT '0',
  `itemTypeID` int(6) NOT NULL DEFAULT '0',
  `itemQty` int(10) NOT NULL DEFAULT '0',
  `rewardISK` int(10) NOT NULL DEFAULT '0',
  `rewardItemID` int(11) NOT NULL DEFAULT '0',
  `rewardItemQty` int(11) NOT NULL DEFAULT '0',
  `bonusISK` int(11) NOT NULL DEFAULT '0',
  `bonusTime` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `qstMining`
--

LOCK TABLES `qstMining` WRITE;
/*!40000 ALTER TABLE `qstMining` DISABLE KEYS */;
INSERT INTO `qstMining` VALUES (56752,135338,'Like Drones to a Cloud',4,5,1,'\0','\0',0,0,4250,0,0,0,0,0),(56871,0,'Starting Simple',1,5,1,'\0','\0',0,0,2000,0,0,0,0,0),(56873,134531,'Asteroid Catastrophe',1,5,1,'\0','\0',0,0,1080,0,0,0,0,0),(56874,134551,'Burnt Traces',1,5,1,'\0','\0',0,0,1080,29000,0,0,29000,0),(56875,0,'Down and Dirty',2,5,1,'\0','\0',0,0,2250,0,0,0,0,0),(56878,0,'Mercium Belt',2,5,1,'\0','\0',0,0,6000,0,0,0,0,0),(56879,0,'Mercium Belt',2,5,1,'\0','\0',0,0,6000,0,0,0,0,0),(56880,0,'Mercium Belt',2,5,1,'\0','\0',0,0,6000,0,0,0,0,0),(56881,0,'Unknown Events',2,5,1,'\0','\0',0,0,6000,0,0,0,0,0),(56883,134630,'Mercium Experiments',1,5,1,'\0','\0',0,0,1080,0,0,0,0,0),(56913,0,'Persistent Pests',3,5,1,'\0','\0',0,0,4000,0,0,0,0,0),(56915,0,'Drone Distribution',3,5,1,'\0','\0',0,0,4000,0,0,0,0,0),(56916,0,'Coming \'Round the Mountain',3,5,1,'\0','\0',0,0,6000,0,0,0,0,0),(56919,0,'Beware They Live',3,5,1,'\0','\0',0,0,9000,0,0,0,0,0),(56920,0,'Pile of Pithix',3,5,1,'\0','\0',0,0,9000,0,0,0,0,0),(56923,0,'Ice Installation',4,5,1,'\0','\0',0,0,20000,0,0,0,0,0),(56924,0,'Cheap Chills',4,5,1,'\0','\0',0,0,20000,0,0,0,0,0),(56925,144468,'Like Drones to a Cloud',4,5,1,'\0','\0',0,0,4250,0,0,0,0,0),(56926,144501,'Like Drones to a Cloud',4,5,1,'\0','\0',0,0,4250,0,0,0,0,0),(56927,0,'Mother Lode',4,5,1,'\0','\0',0,0,44800,0,0,0,0,0),(56928,0,'Geodite and Gemology',4,5,1,'\0','\0',0,0,44800,0,0,0,0,0),(56929,0,'Feeding the Giant',4,5,1,'\0','\0',0,0,44800,0,0,0,0,0),(56930,135325,'Arisite Envy',4,5,1,'\0','\0',0,0,45000,0,0,0,0,0),(56931,135325,'Not Gneiss at All',4,5,1,'\0','\0',0,0,45000,0,0,0,0,0),(56934,0,'Gas Injections',4,5,1,'\0','\0',0,0,4250,0,0,0,0,0),(57062,0,'Data Mining',2,5,1,'\0','\0',4,0,299,0,0,0,0,0),(57063,0,'Data Mining',2,5,1,'\0','\0',4,0,299,0,0,0,0,0),(57095,144657,'Like Drones to a Cloud',4,5,1,'\0','\0',0,0,4250,0,0,0,0,0),(57174,0,'Stay Frosty',3,5,1,'\0','\0',0,0,10000,0,0,0,0,0),(57288,0,'Claimjumpers',2,5,1,'\0','\0',0,0,1800,0,0,0,0,0),(58553,0,'Mercium Belt',2,5,1,'\0','\0',0,0,6000,0,0,0,0,0),(58555,144663,'Like Drones to a Cloud',4,5,1,'\0','\0',0,0,4250,0,0,0,0,0);
/*!40000 ALTER TABLE `qstMining` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:48

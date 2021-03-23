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
-- Table structure for table `crpAdTypeData`
--

DROP TABLE IF EXISTS `crpAdTypeData`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crpAdTypeData` (
  `typeMask` int(10) NOT NULL,
  `typeName` text NOT NULL,
  `typeNameID` int(10) NOT NULL,
  `groupID` int(10) NOT NULL,
  `description` text NOT NULL,
  `descriptionID` int(10) NOT NULL,
  PRIMARY KEY (`typeMask`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Corporate Advert Type Data';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crpAdTypeData`
--

LOCK TABLES `crpAdTypeData` WRITE;
/*!40000 ALTER TABLE `crpAdTypeData` DISABLE KEYS */;
INSERT INTO `crpAdTypeData` VALUES (1,'Mining',59682,11,'Corp is involved with mining',59682),(2,'Mission Runners',59679,11,'Corp is mission running',59679),(4,'New Pilot Friendly',59695,11,'Corp is involved with fleet operations',59695),(8,'Pirating',59684,11,'Corp is involved with pirating',59684),(16,'Exploration',59681,11,'Corp is involved with research and development',59681),(32,'Skirmish Warfare',59685,11,'Corp is involved with small roaming gangs',59685),(64,'Trade',59678,11,'Trade is our main function',59678),(128,'Alliance Warfare',59680,11,'Corp participates in Alliance Warfare',59680),(256,'Militia Force',59683,11,'Corp participates in Factional Warfare',59683),(512,'Amarr High Security',59688,6,'Corp Operates mainly in HiSec',59688),(1024,'Caldari High Security',59689,6,'Corp Operates mainly in HiSec',59689),(2048,'Gallente High Security',59690,6,'Corp Operates mainly in NullSec',59690),(4096,'Minmatar High Security',59691,6,'Corp Operates mainly in HiSec',59691),(8192,'Low Security',59692,6,'Corp Operates mainly in LoSec',59692),(16384,'Outlaw Space',59693,6,'Corp Operates mainly in NullSec',59693),(32768,'Wormhole Space',59694,6,'Corp Operates mainly in WormHoles',59694),(65536,'12:00 - 18:00',59697,8,'Timezone in UTC',59670),(131072,'18:00 - 00:00',59698,8,'Timezone in UTC',59672),(262144,'00:00 - 06:00',59696,8,'Timezone in UTC',59669),(524288,'06:00 - 11:00',59699,8,'Timezone in UTC',59671),(1048576,'Primary Language - English',59673,10,'Corp Uses mostly English',59673),(2097152,'Primary Language - German',59674,10,'Corp Uses mostly German',59674),(4194304,'Primary Language - Spanish',59675,10,'Corp Uses mostly Spanish',59675),(8388608,'Primary Language - Russian',59676,10,'Corp Uses mostly Russian',59676),(16777216,'Primary Language - French',59677,10,'Corp Uses mostly French',59677),(33554432,'PlayStyle - Casual',59686,12,'Typically up to 5 hours per week.',59667),(67108864,'PlayStyle - Hardcore',59687,12,'Typically over 5 hours per week.',59668);
/*!40000 ALTER TABLE `crpAdTypeData` ENABLE KEYS */;
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

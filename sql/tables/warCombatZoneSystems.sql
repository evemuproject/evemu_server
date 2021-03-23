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
-- Table structure for table `warCombatZoneSystems`
--

DROP TABLE IF EXISTS `warCombatZoneSystems`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `warCombatZoneSystems` (
  `solarSystemID` int(11) NOT NULL,
  `combatZoneID` int(11) DEFAULT NULL,
  PRIMARY KEY (`solarSystemID`),
  KEY `combatZoneID` (`combatZoneID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `warCombatZoneSystems`
--

LOCK TABLES `warCombatZoneSystems` WRITE;
/*!40000 ALTER TABLE `warCombatZoneSystems` DISABLE KEYS */;
INSERT INTO `warCombatZoneSystems` VALUES (30002056,6),(30002057,6),(30002058,6),(30002059,6),(30002060,6),(30002061,6),(30002062,6),(30002063,6),(30002064,6),(30002065,6),(30002066,6),(30002067,6),(30002082,6),(30002083,6),(30002084,6),(30002085,6),(30002086,6),(30002087,6),(30002088,6),(30002089,6),(30002090,6),(30002091,6),(30002092,6),(30002093,6),(30002094,6),(30002095,6),(30002096,6),(30002097,6),(30002098,6),(30002099,6),(30002100,6),(30002101,6),(30002102,6),(30002514,6),(30002516,6),(30002517,6),(30002537,6),(30002538,6),(30002539,6),(30002540,6),(30002541,6),(30002542,6),(30002756,4),(30002757,4),(30002758,4),(30002759,4),(30002760,4),(30002796,4),(30002806,4),(30002807,4),(30002808,4),(30002809,4),(30002810,4),(30002811,4),(30002812,4),(30002813,4),(30002957,3),(30002958,3),(30002959,3),(30002960,3),(30002961,3),(30002962,3),(30002975,3),(30002976,3),(30002977,3),(30002978,3),(30002979,3),(30002980,3),(30002981,3),(30003063,3),(30003067,3),(30003068,3),(30003069,3),(30003070,3),(30003071,3),(30003072,3),(30003077,3),(30003079,3),(30003086,3),(30003087,3),(30003088,3),(30003089,3),(30003090,3),(30003091,3),(30003787,5),(30003788,5),(30003789,5),(30003790,5),(30003791,5),(30003792,5),(30003793,5),(30003795,5),(30003796,5),(30003797,5),(30003799,5),(30003825,5),(30003826,5),(30003827,5),(30003828,5),(30003829,5),(30003836,5),(30003837,5),(30003838,5),(30003839,5),(30003840,5),(30003841,5),(30003842,5),(30003850,5),(30003851,5),(30003852,5),(30003853,5),(30003854,5),(30003855,5),(30003856,5),(30003857,5),(30004979,5),(30004980,5),(30004982,5),(30004984,5),(30004985,5),(30004997,5),(30004999,5),(30005000,5),(30005295,5),(30005296,5),(30005297,5),(30005298,5),(30005299,5),(30005300,5),(30005320,5),(30005321,5),(30045306,4),(30045307,4),(30045308,4),(30045309,4),(30045310,4),(30045311,4),(30045312,4),(30045313,4),(30045314,4),(30045315,4),(30045316,4),(30045317,4),(30045318,4),(30045319,4),(30045320,4),(30045330,4),(30045331,4),(30045332,4),(30045333,4),(30045334,4),(30045335,4),(30045336,4),(30045337,4),(30045338,4),(30045339,4),(30045340,4),(30045341,4),(30045342,4),(30045343,4),(30045344,4),(30045345,4),(30045346,4),(30045347,4),(30045348,4),(30045349,4),(30045350,4),(30045351,4),(30045352,4),(30045353,4),(30045354,4);
/*!40000 ALTER TABLE `warCombatZoneSystems` ENABLE KEYS */;
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

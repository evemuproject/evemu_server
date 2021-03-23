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
-- Table structure for table `staStationTypes`
--

DROP TABLE IF EXISTS `staStationTypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `staStationTypes` (
  `stationTypeID` int(11) NOT NULL,
  `dockEntryX` double DEFAULT NULL,
  `dockEntryY` double DEFAULT NULL,
  `dockEntryZ` double DEFAULT NULL,
  `dockOrientationX` double DEFAULT NULL,
  `dockOrientationY` double DEFAULT NULL,
  `dockOrientationZ` double DEFAULT NULL,
  `operationID` tinyint(3) unsigned DEFAULT NULL,
  `reprocessingEfficiency` double DEFAULT NULL,
  `conquerable` tinyint(1) DEFAULT NULL,
  `hangarGraphicID` int(10) DEFAULT NULL,
  PRIMARY KEY (`stationTypeID`),
  KEY `operationID` (`operationID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `staStationTypes`
--

LOCK TABLES `staStationTypes` WRITE;
/*!40000 ALTER TABLE `staStationTypes` DISABLE KEYS */;
INSERT INTO `staStationTypes` VALUES (16,101,0,1498,0,0,1351,NULL,NULL,0,NULL),(17,0,0,2300,0,0,1015,NULL,NULL,0,NULL),(54,36,6854.26220703,7948.46679688,0,0.0000000596046518808,1,NULL,NULL,0,241),(56,0,-5000,-4800,0,-1,0,NULL,NULL,0,1210),(57,-0.00000000419215595571,6143.52929688,3100.00708008,0.0000107482665044,0.107010781765,-0.994257867336,NULL,NULL,0,244),(58,0,0,0,0,0,1,NULL,NULL,0,241),(59,0,0,0,0,0,1,NULL,NULL,0,242),(1529,-170,3217,12112.1542969,0,0.0000000596046447754,0.999999940395,NULL,NULL,0,241),(1530,11384.4287109,7499.12792969,270.25189209,0.981180846691,0.193091094494,-0.0000000137698270564,NULL,NULL,0,241),(1531,2447.21484375,-3841,2988,0.95105612278,0.30901825428,0,NULL,NULL,0,241),(1926,0,11158.4707031,0,0,0.999999940395,0,NULL,NULL,0,1075),(1927,0,-21987.5253906,0,0,-0.999999940395,0,NULL,NULL,0,1075),(1928,0,-21316.4511719,0,0,-1.00000011921,0,NULL,NULL,0,1075),(1929,199.788482666,-12936.9394531,-51.9939537048,0,-1,0,NULL,NULL,0,1075),(1930,-10709,-9721,2069,0,-1,0,NULL,NULL,0,1075),(1931,-13,-5689.26806641,0,0,-0.999999940395,0,NULL,NULL,0,1075),(1932,-1749.89038086,-9967.82910156,-27,0,-1,0,NULL,NULL,0,1075),(2071,9956.19238281,1058.91113281,0,0.999796926975,0.0201505292207,0,NULL,NULL,0,NULL),(2252,9956.19238281,1058.91113281,0,0.999796926975,0.0201505292207,0,NULL,NULL,0,NULL),(2496,-2909,-1437.88049316,-20657,0,0.0000000596046447754,-1,NULL,NULL,0,242),(2497,6299,2654.04418945,11165.6542969,0,0.00626164721325,0.999980449677,NULL,NULL,0,242),(2498,30416.3066406,-1172,-3099.96264648,0.999999940395,0.0000000596046518808,0,NULL,NULL,0,242),(2499,11903.6494141,8452.42285156,9744.41503906,0.999980449677,0.00626146793365,0,NULL,NULL,0,242),(2500,1390.30151367,27,-28047.0371094,0.0313382260501,0.00616767024621,-0.999489784241,NULL,NULL,0,242),(2501,17,3115,-18255.1972656,0,0.0000000596046518808,-1,NULL,NULL,0,242),(2502,17,10096,-12607.2060547,0,0.0000000596046447754,-1,NULL,NULL,0,242),(3864,370.617919922,8566,390,-1,-0.000000119209289551,0,NULL,NULL,0,1075),(3865,-1004.37133789,4872.74853516,-5903.59863281,0.350109219551,0.00000631068269286,-0.93670886755,NULL,NULL,0,244),(3866,9264.68457031,884,0,0.999999940395,0.0000000596046412227,0,NULL,NULL,0,244),(3867,7933.66796875,208.236450195,18212.3496094,0.280802875757,-0.00825552735478,0.959729969501,NULL,NULL,0,1210),(3868,9956.19238281,1058.91113281,0,0.999796926975,0.0201505292207,0,NULL,NULL,0,1210),(3869,10679.8837891,1006.77294922,-14350.2353516,0.999426364899,0.0338653326035,-0.00000000808496025684,NULL,NULL,0,244),(3870,9788.60546875,938,0,0.999713182449,-0.0120400795713,-0.0207010973245,NULL,NULL,0,1210),(3871,123.39453125,-4043.97363281,-17010.3242188,-0.00000231896729019,-0.239630699158,-0.970864117146,NULL,NULL,0,241),(3872,-28557.8710938,-1158.93261719,-2436.08154297,-1,0.0000000596046447754,0,NULL,NULL,0,241),(3873,-6,-335,-3201,0,0,-1015,NULL,NULL,0,NULL),(3874,0,-33,-2923,0,-351,-483,NULL,NULL,0,NULL),(3875,0,-32,276,0,-0.587930262089,-0.808911621571,NULL,NULL,0,NULL),(3876,0,0,47,0,-2,-892,NULL,NULL,0,NULL),(3877,0,0,0,0,0,1948,NULL,NULL,0,NULL),(4023,-27844.5488281,-1354.30688477,-2399,-1,0.0000000596046518808,0,NULL,NULL,0,241),(4024,-33431.2070313,-2574,-2477,-1,-0.000000119209332183,0,NULL,NULL,0,241),(9856,-176,-11789.0810547,-4116.49902344,0,-0.000000119209332183,-1,NULL,NULL,0,1075),(9857,2804,8566,390,-5178,0,0,NULL,NULL,0,1075),(9866,-1500,405,1800,-1602,885,2205,NULL,NULL,0,242),(9867,-896,-26555,-4800,0,-21214,0,NULL,NULL,0,2303),(9868,-3152.70874023,-39840.2539063,8244.79785156,-0.00000218674836105,-0.0000539330758329,1,NULL,NULL,0,2067),(9873,-1449,-10148,-24,-1645,-4313,10,NULL,NULL,0,242),(9874,0,-9631,0,0,-14338,0,NULL,NULL,0,242),(10795,-1203,-18300,-5400,0,-4616,0,NULL,NULL,0,1075),(12242,0,5079.0859375,5337.78466797,0,0.195177391171,-0.980767965317,NULL,NULL,1,2067),(12294,0,-6001.50634766,-4509.06787109,0,-1,0,NULL,NULL,1,2067),(12295,-1297.71374512,4860.29541016,-6949.29296875,0.110589414835,-0.0197495371103,-0.99366992712,NULL,NULL,1,2067),(19757,3454.38549805,-103,-1666.26000977,1,0.0000000596046518808,0.0000000592971076685,NULL,NULL,0,2067),(21642,330.967285156,-837.971984863,-12616.8886719,0,0.0000000596046518808,-1,48,NULL,1,2067),(21644,-13208.5742188,88,-237,-0.999999940395,0.0000000596046412227,0,49,NULL,1,2067),(21645,68.9013824463,-15087.7041016,-2996.0324707,0.000366347376257,0.0782493054867,-0.996933698654,50,NULL,1,2067),(21646,3454.38549805,-103,-1666.26000977,1,0.0000000596046518808,0.0000000592971076685,51,0.35,1,2067),(22296,4674,14278,650,-3327,0,0,NULL,NULL,0,1075),(22297,64,-1249,-1261,0,0,3948,NULL,NULL,0,1075),(22298,-294,-20500,-2504,0,0,-5255,NULL,NULL,0,1075),(29286,370.617919922,8566,390,-1,-0.000000119209289551,0,NULL,NULL,0,1075),(29323,875.929870605,4958.72900391,1991.92980957,0.921267271042,0.12210547924,-0.369265168905,NULL,NULL,0,241),(29387,0,11158.4707031,0,0,0.999999940395,0,NULL,NULL,0,1075),(29388,0,-21946.9589844,0,0,-1,0,NULL,NULL,0,1075),(29389,-1749.89038086,-9967.82910156,-27,0,-1,0,NULL,NULL,0,1075),(29390,-3078.81445313,-39928.6796875,8394.49511719,-0.00000187754687886,-0.0000502995826537,1,NULL,NULL,0,2067);
/*!40000 ALTER TABLE `staStationTypes` ENABLE KEYS */;
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

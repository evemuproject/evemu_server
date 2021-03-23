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
-- Table structure for table `staOperations`
--

DROP TABLE IF EXISTS `staOperations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `staOperations` (
  `activityID` tinyint(3) unsigned DEFAULT NULL,
  `operationID` tinyint(3) unsigned NOT NULL,
  `operationName` varchar(100) DEFAULT NULL,
  `operationNameID` int(6) NOT NULL,
  `description` varchar(1000) DEFAULT NULL,
  `descriptionID` int(3) DEFAULT NULL,
  `fringe` tinyint(4) DEFAULT NULL,
  `corridor` tinyint(4) DEFAULT NULL,
  `hub` tinyint(4) DEFAULT NULL,
  `border` tinyint(4) DEFAULT NULL,
  `ratio` tinyint(4) DEFAULT NULL,
  `caldariStationTypeID` int(11) DEFAULT NULL,
  `minmatarStationTypeID` int(11) DEFAULT NULL,
  `amarrStationTypeID` int(11) DEFAULT NULL,
  `gallenteStationTypeID` int(11) DEFAULT NULL,
  `joveStationTypeID` int(11) DEFAULT NULL,
  PRIMARY KEY (`operationID`),
  KEY `activityID` (`activityID`),
  KEY `caldariStationTypeID` (`caldariStationTypeID`),
  KEY `minmatarStationTypeID` (`minmatarStationTypeID`),
  KEY `amarrStationTypeID` (`amarrStationTypeID`),
  KEY `gallenteStationTypeID` (`gallenteStationTypeID`),
  KEY `joveStationTypeID` (`joveStationTypeID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `staOperations`
--

LOCK TABLES `staOperations` WRITE;
/*!40000 ALTER TABLE `staOperations` DISABLE KEYS */;
INSERT INTO `staOperations` VALUES (1,1,'Plantation',61443,'Makes livestock and grain that is shipped to food processing units.',61402,70,20,10,0,65,1531,2499,1930,3866,3865),(1,2,'Food Packaging',61444,'Makes food that is shipped to warehouses.',61403,0,20,50,30,20,4024,2497,1928,3866,3865),(1,3,'Warehouse',61445,'Stores products and shifts goods to external retailers or production corporations.',61404,0,50,0,50,15,1531,2501,1929,3870,3865),(2,4,'Foundry',61446,'Mines minerals from asteroid belts/clouds.',61405,90,10,0,0,30,1529,2499,1930,3867,3865),(2,5,'Production Plant',61447,'Molds finished construction pieces.',61406,25,15,50,10,50,1529,2497,1928,3867,3865),(2,6,'Warehouse',61448,'Stores product and freights goods to production corps.',61407,0,50,0,50,20,1531,2501,1929,3870,3865),(3,7,'Mining Outpost',61449,'Mines minerals from asteroid belts/clouds.',61408,90,10,0,0,65,4023,2499,1930,3865,3865),(3,8,'Refinery',61450,'Refines the minerals, making purified ingots and rock materials.',61409,0,10,45,45,15,4024,2497,1928,3867,3865),(3,9,'Mineral Reserve',61451,'Stores product and freights goods to production corps.',61410,0,50,0,50,20,4023,2501,1929,3865,3865),(4,10,'Reprocessing Facility',61452,'Extracts chemicals from asteroid belts/clouds.',61411,90,10,0,0,10,4023,2499,1930,3867,3865),(4,11,'Chemical Refinery',61453,'Refines the harvested chemicals, making bottled products.',61412,0,10,90,0,80,1529,2497,1928,3867,3865),(4,12,'Chemical Storage',61454,'Stores products and shifts goods to production corporations.',61413,0,50,0,50,10,1531,2501,1929,3870,3865),(5,13,'Testing Facilities',61455,'Makes plans and blueprints that are shipped to Assembly Plant.',61414,90,10,0,0,20,54,2500,1931,3869,3865),(5,14,'Assembly Plant',61456,'Produces weapons and ammunition that are shipped for storage.',61415,0,10,60,30,55,1529,2498,1927,3867,3865),(5,15,'Logistic Support',61457,'Stores product and freights goods to external retailers.',61416,0,50,0,50,25,1530,2501,1929,3868,3865),(6,16,'Biotech Research Center',61458,'Harvests resources from a planet.',61417,70,30,0,0,20,54,2499,1930,3869,3865),(6,17,'Biotech Production',61459,'Produces Biotech products.',61418,0,10,45,45,70,1529,2497,1928,3867,3865),(6,18,'Biohazard Containment Facility',61460,'Stores and recycles materials classified as biohazards.',61419,50,50,0,0,10,54,2501,1929,3869,3865),(7,19,'Research Center',61461,'Makes plans and blueprints that are shipped to Factory.',61420,70,30,0,0,10,54,2500,1931,3869,3865),(7,20,'Factory',61462,'Produces finished hi-tech products.',61421,0,10,50,40,80,1529,2497,1928,3867,3865),(7,21,'Warehouse',61463,'Stores product and freights goods to external retailers.',61422,0,50,0,50,10,1531,2501,1929,3870,3865),(8,22,'Development Studio',61464,'Produces entertainment material that is shipped to Publisher.',61423,0,10,45,45,80,1531,2496,1931,56,3865),(8,23,'Publisher',61465,'Stores and multiplies the entertainment material and ships it to retailers.',61424,0,10,80,10,20,3872,2496,1926,57,3865),(9,24,'Shipyard',61466,'Produces starships that are shipped for storage in Storage Bay.',61425,0,10,90,0,80,1530,2498,1927,3868,3865),(9,25,'Storage Bay',61467,'Stores ships before freighting them to retailers.',61426,0,50,0,50,20,3872,2502,1929,3870,3865),(10,26,'Storage',61468,'Stores cargo for other corps before shipping it to retailers.',61427,25,25,25,25,100,1531,2501,1929,3870,3865),(11,27,'Warehouse',61469,'Stores products and freights goods to retail center.',61428,40,25,10,25,70,1531,2501,1929,3870,3865),(11,28,'Retail Center',61470,'Sells goods from warehouses to consumers, and to service stations.',61429,0,10,45,45,30,1531,2496,1926,57,3865),(12,29,'Warehouse',61471,'Stores products and freights goods to Trading Post.',61430,50,25,0,25,50,1531,2501,1929,3870,3865),(12,30,'Trading Post',61472,'Sells wares received from production corps.',61431,0,15,35,50,50,1531,2502,1932,3868,3865),(13,31,'Bureau Offices',61473,'Delivers reports and provides information concerning the Bureau\'s field.',61432,0,10,45,45,40,1529,2496,1926,56,3865),(14,32,'Academy',61474,'Studies issues within the administration system and produces personnel.',61433,50,50,0,0,20,1529,2502,9857,57,3865),(14,33,'Bureau',61475,'Delivers reports and publishes rules and manifestos concerning the Bureau\'s field.',61434,0,15,40,45,70,1531,2502,1932,56,3865),(14,34,'Treasury',61476,'Stores data and kredit sheets for the Bureau to work with.',61435,100,0,0,0,10,1530,2498,1927,3868,3865),(17,35,'Depository',61477,'Works as a bank.',61436,0,10,85,5,70,1529,2502,1932,57,3865),(17,36,'Vault',61478,'Stores data and kredit sheets for the Bank to work with.',61437,100,0,0,0,30,1530,2501,1927,3868,3865),(18,37,'School',61479,'Produces personnel and sells skill packages.',61438,0,0,50,50,100,1529,2500,1931,57,3865),(19,38,'Factory',61480,'Produces finished hi-tech products.',61421,0,10,45,45,80,4024,2497,1928,3867,3865),(19,39,'Warehouse',61481,'Stores products and freights goods to Trading Post.',61430,0,50,0,50,20,1531,2501,1929,3870,3865),(15,40,'Tribunal',61482,'Courts where judicial matters are judged',61439,0,0,50,50,40,1530,2496,9857,3868,3865),(15,41,'Accounting',61483,'Accounting and audit firms',61440,30,30,20,20,30,1529,2500,1931,57,3865),(15,42,'Law School',61484,'Does weird shit with words',61484,50,30,10,10,30,3871,2502,1929,56,3865),(13,43,'Archives',61485,'Stores administrative documents and data.',61441,70,30,0,0,30,1529,2500,1931,57,3865),(13,44,'Information Center',61486,'Distributes administrative information to the public.',61442,0,0,50,50,30,3872,2502,1926,57,3865),(20,45,'Manufacturing',61487,'Manufacturing',61487,0,0,0,0,0,NULL,NULL,NULL,NULL,NULL),(20,46,'Refining',61488,'Refining',61488,0,0,0,0,0,NULL,NULL,NULL,NULL,NULL),(20,47,'Cloning',61489,'Cloning',61489,0,0,0,0,0,NULL,NULL,NULL,NULL,NULL),(20,48,'Caldari Research Outpost',61490,'Research',61490,0,0,0,0,0,NULL,NULL,NULL,NULL,NULL),(20,49,'Amarr Factory Outpost',61491,'Produces Goods',61491,0,0,0,0,0,NULL,NULL,NULL,NULL,NULL),(20,50,'Gallente Administrative Outpost',61492,'Administration',61492,0,0,0,0,0,NULL,NULL,NULL,NULL,NULL),(20,51,'Minmatar Service Outpost',61493,'Services',61493,0,0,0,0,0,NULL,NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `staOperations` ENABLE KEYS */;
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

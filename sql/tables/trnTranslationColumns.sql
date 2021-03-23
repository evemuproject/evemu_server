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
-- Table structure for table `trnTranslationColumns`
--

DROP TABLE IF EXISTS `trnTranslationColumns`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trnTranslationColumns` (
  `tcGroupID` smallint(6) DEFAULT NULL,
  `tcID` smallint(6) NOT NULL,
  `tableName` varchar(256) NOT NULL,
  `columnName` varchar(128) NOT NULL,
  `masterID` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`tcID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trnTranslationColumns`
--

LOCK TABLES `trnTranslationColumns` WRITE;
/*!40000 ALTER TABLE `trnTranslationColumns` DISABLE KEYS */;
INSERT INTO `trnTranslationColumns` VALUES (4,6,'dbo.invCategories','categoryName','categoryID'),(5,7,'dbo.invGroups','groupName','groupID'),(5,8,'dbo.invTypes','typeName','typeID'),(7,9,'dbo.chrRaces','raceName','raceID'),(7,10,'dbo.chrRaces','description','raceID'),(8,11,'dbo.chrBloodlines','bloodlineName','bloodlineID'),(8,12,'dbo.chrBloodlines','description','bloodlineID'),(9,15,'dbo.chrAncestries','ancestryName','ancestryID'),(9,16,'dbo.chrAncestries','description','ancestryID'),(16,29,'dbo.chrFactions','description','factionID'),(5,33,'dbo.invTypes','description','typeID'),(6,34,'dbo.invMetaGroups','metaGroupName','metaGroupID'),(6,35,'dbo.invMetaGroups','description','metaGroupID'),(28,36,'dbo.invMarketGroups','marketGroupName','marketGroupID'),(28,37,'dbo.invMarketGroups','description','marketGroupID'),(33,45,'dbo.crpActivities','activityName','activityID'),(34,46,'dbo.staOperations','operationName','operationID'),(34,47,'dbo.staOperations','description','operationID'),(35,48,'dbo.staServices','serviceName','serviceID'),(35,49,'dbo.staServices','description','serviceID'),(41,58,'dbo.eveUnits','displayName','unitID'),(42,59,'dbo.dgmAttributeTypes','displayName','attributeID'),(46,63,'dbo.mapLandmarks','landmarkName','landmarkID'),(46,64,'dbo.mapLandmarks','description','landmarkID'),(47,65,'dbo.crpNPCDivisions','divisionName','divisionID'),(47,66,'dbo.crpNPCDivisions','leaderType','divisionID'),(48,68,'dbo.crtCategories','categoryName','categoryID'),(48,69,'dbo.crtClasses','className','classID'),(49,70,'dbo.crtCertificates','description','certificateID'),(53,74,'dbo.dgmEffects','displayName','effectID'),(53,75,'dbo.dgmEffects','description','effectID'),(65,100,'dbo.ramActivities','activityName','activityID'),(65,101,'dbo.ramActivities','description','activityID'),(84,119,'dbo.planetSchematics','schematicName','schematicID'),(41,122,'dbo.eveUnits','description','unitID'),(16,127,'dbo.chrFactions','factionName','factionID'),(64,138,'dbo.crpNPCCorporations','description','corporationID');
/*!40000 ALTER TABLE `trnTranslationColumns` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:53

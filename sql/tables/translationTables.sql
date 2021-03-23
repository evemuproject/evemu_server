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
-- Table structure for table `translationTables`
--

DROP TABLE IF EXISTS `translationTables`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `translationTables` (
  `sourceTable` varchar(100) NOT NULL,
  `destinationTable` varchar(200) DEFAULT NULL,
  `translatedKey` varchar(100) NOT NULL,
  `tcGroupID` int(11) DEFAULT NULL,
  `tcID` int(11) DEFAULT NULL,
  PRIMARY KEY (`sourceTable`,`translatedKey`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `translationTables`
--

LOCK TABLES `translationTables` WRITE;
/*!40000 ALTER TABLE `translationTables` DISABLE KEYS */;
INSERT INTO `translationTables` VALUES ('cert.categoriesTx','dbo.crtCategories','categoryName',48,68),('cert.certificatesTx','dbo.crtCertificates','description',49,70),('cert.classesTx','dbo.crtClasses','className',48,69),('character.ancestriesTx','dbo.chrAncestries','ancestryName',9,15),('character.ancestriesTx','dbo.chrAncestries','description',9,16),('character.bloodlinesTx','dbo.chrBloodlines','bloodlineName',8,11),('character.bloodlinesTx','dbo.chrBloodlines','description',8,12),('character.factionsTx','dbo.chrFactions','description',16,29),('character.factionsTx','dbo.chrFactions','factionName',16,127),('character.racesTx','dbo.chrRaces','description',7,10),('character.racesTx','dbo.chrRaces','raceName',7,9),('corporation.activitiesTx','dbo.crpActivities','activityName',33,45),('corporation.npcCorporationsTx','dbo.crpNPCCorporations','description',64,138),('dbo.crpNPCDivisions','dbo.crpNPCDivisions','divisionName',47,65),('dbo.crpNPCDivisions','dbo.crpNPCDivisions','leaderType',47,66),('dbo.staOperations','dbo.staOperations','description',34,47),('dbo.staOperations','dbo.staOperations','operationName',34,46),('dbo.staServices','dbo.staServices','description',35,49),('dbo.staServices','dbo.staServices','serviceName',35,48),('dogma.attributesTx','dbo.dgmAttributeTypes','displayName',42,59),('dogma.effectsTx','dbo.dgmEffects','description',53,75),('dogma.effectsTx','dbo.dgmEffects','displayName',53,74),('dogma.unitsTx','dbo.eveUnits','description',41,122),('dogma.unitsTx','dbo.eveUnits','displayName',41,58),('inventory.categoriesTx','dbo.invCategories','categoryName',4,6),('inventory.groupsTx','dbo.invGroups','groupName',5,7),('inventory.marketGroupsTx','dbo.invMarketGroups','description',28,37),('inventory.marketGroupsTx','dbo.invMarketGroups','marketGroupName',28,36),('inventory.metaGroupsTx','dbo.invMetaGroups','description',6,35),('inventory.metaGroupsTx','dbo.invMetaGroups','metaGroupName',6,34),('inventory.typesTx','dbo.invTypes','description',5,33),('inventory.typesTx','dbo.invTypes','typeName',5,8),('map.landmarksTx','dbo.mapLandmarks','description',46,64),('map.landmarksTx','dbo.mapLandmarks','landmarkName',46,63),('planet.schematicsTx','dbo.planetSchematics','schematicName',84,119),('ram.activitiesTx','dbo.ramActivities','activityName',65,100),('ram.activitiesTx','dbo.ramActivities','description',65,101);
/*!40000 ALTER TABLE `translationTables` ENABLE KEYS */;
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

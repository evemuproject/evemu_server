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
-- Table structure for table `invCategories`
--

DROP TABLE IF EXISTS `invCategories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `invCategories` (
  `categoryID` int(10) NOT NULL,
  `categoryName` varchar(100) DEFAULT NULL,
  `description` varchar(3000) DEFAULT NULL,
  `published` bit(1) NOT NULL DEFAULT b'0',
  `iconID` smallint(6) NOT NULL DEFAULT '0',
  `categoryNameID` int(8) NOT NULL DEFAULT '0',
  `dataID` int(8) NOT NULL DEFAULT '0',
  PRIMARY KEY (`categoryID`),
  UNIQUE KEY `categoryID` (`categoryID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `invCategories`
--

LOCK TABLES `invCategories` WRITE;
/*!40000 ALTER TABLE `invCategories` DISABLE KEYS */;
INSERT INTO `invCategories` VALUES (0,'#System','','\0',0,63539,16545519),(1,'Owner','','\0',0,63540,16545520),(2,'Celestial','','',0,63541,16545521),(3,'Station','','\0',0,63542,16545522),(4,'Material','','',22,63543,16545523),(5,'Accessories','','',33,63560,16545540),(6,'Ship','','',0,63544,16545524),(7,'Module','','',67,63545,16545525),(8,'Charge','','',0,63546,16545526),(9,'Blueprint','','',21,63547,16545527),(10,'Trading','','\0',0,63548,16545528),(11,'Entity','','\0',0,63549,16545529),(14,'Bonus','Character creation bonuses. Like innate skills but genetic rather than learned.','\0',0,63550,16545530),(16,'Skill','Where all the skills go under.','',33,63551,16545531),(17,'Commodity','','',0,63552,16545532),(18,'Drone','Player owned and controlled drones.','',0,63553,16545533),(20,'Implant','Implant','',0,63554,16545534),(22,'Deployable','','',0,63555,16545535),(23,'Structure','Player owned structure related objects','',0,63556,16545536),(24,'Reaction','','',0,63557,16545537),(25,'Asteroid','','',0,63558,16545538),(26,'WorldSpace','Worldspaces and related stuff','\0',0,63568,16545548),(29,'Abstract','Abstract grouping, global types and groups for the UI, such as Ranks, Ribbons and Medals.','\0',0,63559,16545539),(30,'Apparel','1. clothing, especially outerwear; garments; attire; raiment.\n2. anything that decorates or covers.\n3. superficial appearance; aspect; guise. ','',0,63572,16545551),(32,'Subsystem','Subsystems for tech 3 ships','',0,63562,16545542),(34,'Ancient Relics','','',0,63561,16545541),(35,'Decryptors','','',0,63563,16545543),(39,'Infrastructure Upgrades','','',0,63565,16545545),(40,'Sovereignty Structures','','',0,63564,16545544),(41,'Planetary Interaction','Stuff for planetary interaction','',0,63569,16545549),(42,'Planetary Resources','These are Items that can be extracted from a planet. ','',0,63566,16545546),(43,'Planetary Commodities','','',0,63567,16545547),(46,'Orbitals','Anchorable/Onlinable objects that operate similar to POS/SOV structures, but do not link to towers or sovereignty. Each class of orbital defines its own valid anchoring locations via Python code.','',0,63570,16545555),(49,'Placeables','Placeables are things you can put into rooms. ','\0',0,63571,16545550),(53,'Effects','','\0',0,63573,16545552),(54,'Lights','','\0',0,63574,22244434),(59,'Cells','','\0',0,235965,16545554),(350001,'Catma','','\0',0,267649,60304602);
/*!40000 ALTER TABLE `invCategories` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:54

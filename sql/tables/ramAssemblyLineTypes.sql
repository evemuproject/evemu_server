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
-- Table structure for table `ramAssemblyLineTypes`
--

DROP TABLE IF EXISTS `ramAssemblyLineTypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ramAssemblyLineTypes` (
  `assemblyLineTypeID` tinyint(3) unsigned NOT NULL,
  `assemblyLineTypeName` varchar(100) DEFAULT NULL,
  `description` varchar(1000) DEFAULT NULL,
  `baseTimeMultiplier` double DEFAULT NULL,
  `baseMaterialMultiplier` double DEFAULT NULL,
  `volume` double DEFAULT NULL,
  `activityID` tinyint(3) unsigned DEFAULT NULL,
  `minCostPerHour` double DEFAULT NULL,
  PRIMARY KEY (`assemblyLineTypeID`),
  KEY `activityID` (`activityID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ramAssemblyLineTypes`
--

LOCK TABLES `ramAssemblyLineTypes` WRITE;
/*!40000 ALTER TABLE `ramAssemblyLineTypes` DISABLE KEYS */;
INSERT INTO `ramAssemblyLineTypes` VALUES (2,'Lab Slot','Copying',1,1,1,5,NULL),(3,'Reverse Engineering','Reverse Engineering',1,1,1,7,NULL),(5,'STATION copying','STATION copying',1,1,1,5,8.333333),(6,'STATION manufacturing','STATION manufacturing',1,1,1,1,333),(7,'STATION material productivity','STATION material productivity',1,1,1,4,8.333333),(8,'STATION productivity time','STATION productivity time',1,1,1,3,8.333333),(10,'Capital Ship Assembly','Capital Ship Assembly',1,1,1,1,NULL),(11,'ME Research','ME Research',1,1,1,4,NULL),(12,'PE Research','PE Research',1,1,1,3,NULL),(13,'Manufacturing','Manufacturing',1,1,1,1,NULL),(17,'Small Ship Assembly Array','Small Ship Assembly Array\n',0.75,1,1,1,NULL),(18,'Advanced Small Ship Assembly Array','Advanced Small Ship Assembly Array\n',0.75,1.1,1,1,NULL),(19,'Medium Ship Assembly Array','Medium Ship Assembly Array\n',0.75,1,1,1,NULL),(20,'Advanced Medium Ship Assembly Array','Advanced Medium Ship Assembly Array\n',0.75,1.1,1,1,NULL),(21,'X Large Ship Assembly Array','X Large Ship Assembly Array\n',0.75,1,1,1,NULL),(22,'Advanced Large Ship Assembly Array','Advanced Large Ship Assembly Array\n',0.75,1.1,1,1,NULL),(23,'Rapid Equipment Assembly Array','Rapid Equipment Assembly Array\n',0.65,1.2,1,1,NULL),(24,'Equipment Assembly Array','Equipment Assembly Array\n',0.75,1,1,1,NULL),(25,'Ammunition Assembly Array','Ammunition Assembly Array',0.75,1,1,1,NULL),(26,'Drone Assembly Array','Drone Assembly Array',0.75,1,1,1,NULL),(27,'Component Assembly Array','Component Assembly Array',0.75,1,1,1,NULL),(28,'Mobile Laboratory ME','Mobile Laboratory ME',0.75,1,1,4,NULL),(29,'Mobile Laboratory PE','Mobile Laboratory PE',0.75,1,1,3,NULL),(30,'Mobile Laboratory Copying','Mobile Laboratory Copying',0.75,1,1,5,NULL),(31,'Amarr Outpost Manufacturing','Amarr Outpost Manufacturing',0.7,1,1,1,NULL),(32,'Caldari Outpost ME Research','Caldari Outpost ME Research',0.7,1,1,4,NULL),(33,'Caldari Outpost PE Research','Caldari Outpost PE Research',0.7,1,1,3,NULL),(34,'Caldari Outpost Copying','Caldari Outpost Copying',0.7,1,1,5,NULL),(35,'STATION 0.5+ Manufacturing','STATION 0.5+ Manufacturing',1,1,1,1,333),(36,'Invention','',1,1,1,8,NULL),(37,'Booster Manufacturing','Booster Manufacturing',1,1,1,1,NULL),(38,'STATION Invention','STATION Invention',1,1,1,8,NULL),(39,'Mobile Laboratory Invention','Mobile Laboratory Invention',0.5,1,1,8,NULL),(40,'Caldari Outpost Invention','Caldari Outpost Invention',1,1,1,8,NULL),(43,'Amarr Outpost Factory1 Tier1','Amarr Outpost w/ Type 1 Tier 1',0.7,1,1,1,NULL),(45,'Amarr Outpost Factory1(2) Tier 1(1)','Amarr Outpost w/ Type 1 Tier 1, Type 2 Tier 1',0.7,1,1,1,NULL),(46,'Minmatar Outpost Factory1 Tier1','',1,1,1,1,NULL),(47,'Amarr Outpost Factory1(2) Tier 1(2)','Amarr Outpost w/ Type 1 Tier 1, Type 2 Tier 2',0.7,1,1,1,NULL),(48,'Amarr Outpost Factory1(2) Tier 1(3)','Amarr Outpost w/ Type 1 Tier 1, Type 2 Tier 3',0.7,1,1,1,NULL),(52,'Minmatar Outpost Factory1 Tier2','',1,1,1,1,NULL),(54,'Amarr Outpost Factory1 Tier2','Amarr Outpost w/ Type 1 Tier 2',0.7,1,1,1,NULL),(56,'Amarr Outpost Factory1(2) Tier2(1)','Amarr Outpost w/ Type 1 Tier 2, Type 2 Tier 1',0.7,1,1,1,NULL),(57,'Amarr Outpost Factory1(2) Tier2(2)','Amarr Outpost w/ Type 1 Tier 2, Type 2 Tier 2',0.7,1,1,1,NULL),(58,'Amarr Outpost Factory1(2) Tier2(3)','Amarr Outpost w/ Type 1 Tier 2, Type 2 Tier 3',0.7,1,1,1,NULL),(59,'Amarr Outpost Factory1 Tier 3','Amarr Outpost w/ Type 1 Tier 3',0.7,1,1,1,NULL),(60,'Amarr Outpost Factory1(2) Tier3(1)','Amarr Outpost w/ Type 1 Tier 3, Type 2 Tier 1',0.7,1,1,1,NULL),(61,'Amarr Outpost Factory1(2) Tier3(2)','Amarr Outpost w/ Type 1 Tier 3, Type 2 Tier 2',0.7,1,1,1,NULL),(62,'Minmatar Outpost Factory1 Tier3','',1,1,1,1,NULL),(63,'Minmatar Oupost Research ME Tier1','',0.8,1,1,4,NULL),(66,'Amarr Outpost Factory2 Tier1','Amarr Outpost w/ Type 2 Tier 1',0.7,1,1,1,NULL),(67,'Amarr Outpost Factory2 Tier 2','Amarr Outpost w/ Type 2 Tier 2',0.7,1,1,1,NULL),(68,'Amarr Outpost Factory2 Tier3','Amarr Outpost w/ Type 2 Tier 3',0.7,1,1,1,NULL),(69,'Amarr Outpost Research ME Tier 1','Amarr Outpost Tier 1 ME',1,1,1,4,NULL),(70,'Caldari Outpost Factory Tier1','Caldari Outpost Tier 1 Factory',1,1,1,1,NULL),(71,'Amarr Outpost Research PE Tier 1','',0.8,1,1,3,NULL),(72,'Amarr Outpost Research Copy Tier1','',1,1,1,5,NULL),(73,'Amarr Outpost Research ME Tier2','',1,1,1,4,NULL),(74,'Amarr Outpost Research PE Tier2','',0.6,1,1,3,NULL),(75,'Amarr Outpost Research Copy Tier2','',1,1,1,5,NULL),(76,'Amarr Outpost Research ME Tier3','',1,1,1,4,NULL),(77,'Amarr Outpost Research PE Tier3','',0.4,1,1,3,NULL),(78,'Amarr Outpost Research Copy Tier3','',1,1,1,5,NULL),(79,'Caldari Outpost Factory Tier2','',1,1,1,1,NULL),(80,'Caldari Outpost Factory Tier3','',1,1,1,1,NULL),(81,'Caldari Outpost Research1 ME Tier1','',0.7,1,1,4,NULL),(82,'Caldari Outpost Research1 PE Tier1','',0.7,1,1,3,NULL),(83,'Caldari Outpost Research1 Copy Tier1','',0.7,1,1,5,NULL),(84,'Caldari Outpost Research1 ME Tier2','',0.6,1,1,4,NULL),(85,'Caldari Outpost Research1 PE Tier2','',0.6,1,1,3,NULL),(86,'Caldari Outpost Research1 Copy Tier2','',0.6,1,1,5,NULL),(87,'Caldari Outpost Research1 ME Tier3','',0.5,1,1,4,NULL),(88,'Caldari Outpost Research1 PE Tier3','',0.5,1,1,3,NULL),(89,'Caldari Outpost Research1 Copy Tier3','',0.5,1,1,5,NULL),(90,'Caldari Outpost Research2 Tier1','',0.8,1,1,8,NULL),(91,'Caldari Outpost Research2 Tier2','',0.6,1,1,8,NULL),(92,'Caldari Outpost Research2 Tier3','',0.4,1,1,8,NULL),(93,'Gallente Outpost Factory1 Tier1','',1,1,1,1,NULL),(94,'Gallente Outpost Factory1(2) Tier1(1)','',1,1,1,1,NULL),(95,'Gallente Outpost Factory1(2) Tier1(2)','',1,1,1,1,NULL),(96,'Gallente Outpost Factory 1(2) Tier1(3)','',1,1,1,1,NULL),(98,'Gallente Outpost Factory1(2) Tier2(1)','',1,1,1,1,NULL),(99,'Gallente Outpost Factory1(2) Tier2(2)','',1,1,1,1,NULL),(100,'Gallente Outpost Factory1(2) Tier2(3)','',1,1,1,1,NULL),(102,'Gallente Outpost Factory1(2) Tier3(1)','',1,1,1,1,NULL),(103,'Gallente Outpost Factory1(2) Tier3(2)','',1,1,1,1,NULL),(104,'Gallente Outpost Factory2 Tier1','',1,1,1,1,NULL),(105,'Gallente Outpost Factory2 Tier2','',1,1,1,1,NULL),(106,'Gallente Outpost Factory2 Tier3','',1,1,1,1,NULL),(107,'Gallente Outpost Research ME Tier1','',1,1,1,4,NULL),(108,'Gallente Outpost Research PE Tier1','',1,1,1,3,NULL),(109,'Gallente Outpost Research Copy Tier1','',0.8,1,1,5,NULL),(110,'Gallente Outpost Research ME Tier2','',1,1,1,4,NULL),(111,'Gallente Outpost Research PE Tier2','',1,1,1,3,NULL),(112,'Gallente Outpost Research Copy Tier2','',0.6,1,1,5,NULL),(113,'Gallente Outpost Research ME Tier3','',1,1,1,4,NULL),(114,'Gallente Outpost Research PE Tier3','',1,1,1,3,NULL),(115,'Gallente Outpost Research Copy Tier3','',0.4,1,1,5,NULL),(116,'Minmatar Outpost Factory1(2) Tier1(1)','',1,1,1,1,NULL),(117,'Minmatar Outpost Factory1(2) Tier1(2)','',1,1,1,1,NULL),(118,'Minmatar Outpost Factory1(2) Tier1(3)','',1,1,1,1,NULL),(119,'Minmatar Outpost Factory1(2) Tier2(1)','',1,1,1,1,NULL),(120,'Minmatar Outpost Factory1(2) Tier2(2)','',1,1,1,1,NULL),(121,'Minmatar Outpost Factory1(2) Tier2(3)','',1,1,1,1,NULL),(122,'Minmatar Outpost Factory1(2) Tier3(1)','',1,1,1,1,NULL),(123,'Minmatar Outpost Factory1(2) Tier3(2)','',1,1,1,1,NULL),(124,'Minmatar Outpost Factory2 Tier1','',1,1,1,1,NULL),(125,'Minmatar Outpost Factory2 Tier2','',1,1,1,1,NULL),(126,'Minmatar Outpost Factory2 Tier3','',1,1,1,1,NULL),(127,'Minmatar Outpost Research PE Tier1','',1,1,1,3,NULL),(128,'Minmatar Outpost Research Copy Tier1','',1,1,1,5,NULL),(129,'Minmatar Outpost Research ME Tier2','',0.6,1,1,4,NULL),(130,'Minmatar Outpost Research PE Tier2','',1,1,1,3,NULL),(131,'Minmatar Outpost Research Copy Tier2','',1,1,1,5,NULL),(132,'Minmatar Outpost Research ME Tier3','',0.4,1,1,4,NULL),(133,'Minmatar Outpost Research PE Tier3','',1,1,1,3,NULL),(134,'Minmatar Outpost Research Copy Tier3','',1,1,1,5,NULL),(136,'Gallente Outpost Factory1 Tier3','',1,1,1,1,NULL),(137,'Gallente Outpost Factory1 Tier2','',1,1,1,1,NULL),(138,'Minmatar Outpost Research ME Tier1','',0.8,1,1,4,NULL),(145,'Ore Capital Ship','ore cap ship asteroid line',1,1,1,1,NULL),(146,'Efficient Mobile Lab Copy','efficient mobile lab copy',0.65,1,1,5,NULL),(147,'Efficient Mobile Lab ME','efficient mobile lab ME',0.75,1,1,4,NULL),(148,'Efficient Mobile Lab PE','efficient mobile lab TE',0.85,1,1,3,NULL),(149,'Efficient Mobile Lab invention','efficient mobile lab invention',0.5,1,1,8,NULL),(150,'Ore Cap Ship Manufacturing','ore cap ship manufacture lines',0.8,1,1,1,NULL),(155,'Large Ship Assembly Array','Large ship assembly array for manufacture of battleships, freighters ',0.75,1,1,1,NULL),(158,'experimental laboratory (reverse engineering)','experimental lab',1,1,NULL,7,NULL),(159,'Advanced Subsystem Assembly Array','Advanced Subsystem Assembly Array',1,1,1,1,NULL),(161,'Subsystem Manufacturing','Subsystem Manufacturing',1,1,1,1,NULL);
/*!40000 ALTER TABLE `ramAssemblyLineTypes` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:49

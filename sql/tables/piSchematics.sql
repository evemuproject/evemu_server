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
-- Table structure for table `piSchematics`
--

DROP TABLE IF EXISTS `piSchematics`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `piSchematics` (
  `schematicID` smallint(6) NOT NULL,
  `schematicName` varchar(255) DEFAULT NULL,
  `cycleTime` int(11) DEFAULT NULL,
  PRIMARY KEY (`schematicID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `piSchematics`
--

LOCK TABLES `piSchematics` WRITE;
/*!40000 ALTER TABLE `piSchematics` DISABLE KEYS */;
INSERT INTO `piSchematics` VALUES (65,'Super Conductors',3600),(66,'Coolant',3600),(67,'Rocket Fuel',3600),(68,'Synthetic Oil',3600),(69,'Oxides',3600),(70,'Silicate Glass',3600),(71,'Transmitter',3600),(72,'Water-Cooled CPU',3600),(73,'Mechanical Parts',3600),(74,'Construction Blocks',3600),(75,'Enriched Uranium',3600),(76,'Consumer Electronics',3600),(77,'Miniature Electronics',3600),(78,'Nanites',3600),(79,'Biocells',3600),(80,'Microfiber Shielding',3600),(81,'Viral Agent',3600),(82,'Fertilizer',3600),(83,'Genetically Enhanced Livestock',3600),(84,'Livestock',3600),(85,'Polytextiles',3600),(86,'Test Cultures',3600),(87,'Supertensile Plastics',3600),(88,'Polyaramids',3600),(89,'Ukomi Super Conductor',3600),(90,'Condensates',3600),(91,'Camera Drones',3600),(92,'Synthetic Synapses',3600),(94,'High-Tech Transmitter',3600),(95,'Gel-Matrix Biopaste',3600),(96,'Supercomputers',3600),(97,'Robotics',3600),(98,'Smartfab Units',3600),(99,'Nuclear Reactors',3600),(100,'Guidance Systems',3600),(102,'Neocoms',3600),(103,'Planetary Vehicles',3600),(104,'Biotech Research Reports',3600),(105,'Vaccines',3600),(106,'Industrial Explosives',3600),(107,'Hermetic Membranes',3600),(108,'Transcranial Microcontroller',3600),(109,'Data Chips',3600),(110,'Hazmat Detection Systems',3600),(111,'Cryoprotectant Solution',3600),(112,'Organic Mortar Applicators',3600),(113,'Sterile Conduits',3600),(114,'Nano-Factory',3600),(115,'Self-Harmonizing Power Core',3600),(116,'Recursive Computing Module',3600),(117,'Broadcast Node',3600),(118,'Integrity Response Drones',3600),(119,'Wetware Mainframe',3600),(121,'Water',1800),(122,'Plasmoids',1800),(123,'Electrolytes',1800),(124,'Oxygen',1800),(125,'Oxidizing Compound',1800),(126,'Reactive Metals',1800),(127,'Precious Metals',1800),(128,'Toxic Metals',1800),(129,'Chiral Structures',1800),(130,'Silicon',1800),(131,'Bacteria',1800),(132,'Biomass',1800),(133,'Proteins',1800),(134,'Biofuels',1800),(135,'Industrial Fibers',1800),(137,'Augmented Stem Cells',1800);
/*!40000 ALTER TABLE `piSchematics` ENABLE KEYS */;
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

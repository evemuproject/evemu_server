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
-- Table structure for table `schematics`
--

DROP TABLE IF EXISTS `schematics`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schematics` (
  `schematicID` int(11) NOT NULL DEFAULT '0',
  `schematicName` text COLLATE utf8_unicode_ci,
  `cycleTime` int(11) DEFAULT NULL,
  `dataID` int(11) DEFAULT NULL,
  PRIMARY KEY (`schematicID`),
  KEY `dataID` (`dataID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `schematics`
--

LOCK TABLES `schematics` WRITE;
/*!40000 ALTER TABLE `schematics` DISABLE KEYS */;
INSERT INTO `schematics` VALUES (65,'Super Conductors',3600,8810795),(66,'Coolant',3600,8810753),(67,'Rocket Fuel',3600,8810791),(68,'Synthetic Oil',3600,8810798),(69,'Oxides',3600,8810779),(70,'Silicate Glass',3600,8810792),(71,'Transmitter',3600,8810803),(72,'Water-Cooled CPU',3600,8810808),(73,'Mechanical Parts',3600,8810769),(74,'Construction Blocks',3600,8810751),(75,'Enriched Uranium',3600,8810758),(76,'Consumer Electronics',3600,8810752),(77,'Miniature Electronics',3600,8810772),(78,'Nanites',3600,8810773),(79,'Biocells',3600,8810742),(80,'Microfiber Shielding',3600,8810771),(81,'Viral Agent',3600,8810806),(82,'Fertilizer',3600,8810759),(83,'Genetically Enhanced Livestock',3600,8810761),(84,'Livestock',3600,8810768),(85,'Polytextiles',3600,8810785),(86,'Test Cultures',3600,8810800),(87,'Supertensile Plastics',3600,8810797),(88,'Polyaramids',3600,8810784),(89,'Ukomi Super Conductor',3600,8810804),(90,'Condensates',3600,8810750),(91,'Camera Drones',3600,8810747),(92,'Synthetic Synapses',3600,8810799),(94,'High-Tech Transmitter',3600,8810765),(95,'Gel-Matrix Biopaste',3600,8810760),(96,'Supercomputers',3600,8810796),(97,'Robotics',3600,8810790),(98,'Smartfab Units',3600,8810794),(99,'Nuclear Reactors',3600,8810778),(100,'Guidance Systems',3600,8810762),(102,'Neocoms',3600,8810775),(103,'Planetary Vehicles',3600,8810782),(104,'Biotech Research Reports',3600,8810746),(105,'Vaccines',3600,8810805),(106,'Industrial Explosives',3600,8810766),(107,'Hermetic Membranes',3600,8810764),(108,'Transcranial Microcontroller',3600,8810802),(109,'Data Chips',3600,8810756),(110,'Hazmat Detection Systems',3600,8810763),(111,'Cryoprotectant Solution',3600,8810754),(112,'Organic Mortar Applicators',3600,8838284),(113,'Sterile Conduits',3600,8838287),(114,'Nano-Factory',3600,8810774),(115,'Self-Harmonizing Power Core',3600,8838286),(116,'Recursive Computing Module',3600,8838285),(117,'Broadcast Node',3600,8838282),(118,'Integrity Response Drones',3600,8838283),(119,'Wetware Mainframe',3600,8810809),(121,'Water',1800,8810807),(122,'Plasmoids',1800,8810783),(123,'Electrolytes',1800,8810757),(124,'Oxygen',1800,8810781),(125,'Oxidizing Compound',1800,8810780),(126,'Reactive Metals',1800,8810789),(127,'Precious Metals',1800,8810786),(128,'Toxic Metals',1800,8810801),(129,'Chiral Structures',1800,8810749),(130,'Silicon',1800,8810793),(131,'Bacteria',1800,8810741),(132,'Biomass',1800,8810744),(133,'Proteins',1800,8810787),(134,'Biofuels',1800,8810743),(135,'Industrial Fibers',1800,8810767);
/*!40000 ALTER TABLE `schematics` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:51

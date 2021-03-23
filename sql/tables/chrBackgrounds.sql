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
-- Table structure for table `chrBackgrounds`
--

DROP TABLE IF EXISTS `chrBackgrounds`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrBackgrounds` (
  `backgroundID` int(10) unsigned NOT NULL DEFAULT '0',
  `backgroundName` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`backgroundID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrBackgrounds`
--

LOCK TABLES `chrBackgrounds` WRITE;
/*!40000 ALTER TABLE `chrBackgrounds` DISABLE KEYS */;
INSERT INTO `chrBackgrounds` VALUES (1,'AthleticFIST'),(2,'Banner'),(3,'Boilerroom'),(4,'Bones'),(5,'Brickwall'),(6,'Caution'),(7,'City'),(8,'Cloudy halo'),(9,'Concord'),(10,'Darkmetal'),(11,'Dirty iron'),(12,'Graffiti'),(13,'Hallway'),(14,'Hangardoor'),(15,'Interbus'),(16,'Pirate'),(17,'Rabbitskull'),(18,'Refraction'),(19,'Rocky halo'),(20,'Rustball'),(21,'Ruststripe'),(22,'RustyMech'),(23,'Statues'),(24,'Tribal'),(25,'Tribaltech'),(26,'Whirlpool'),(27,'Zoom'),(28,'aliens'),(29,'amarrchapel'),(30,'amarrdoors'),(31,'amarrmec'),(32,'boilerroombackdrop'),(33,'breasts'),(34,'cell-298'),(35,'crazyface'),(36,'dirt'),(37,'door'),(38,'doorbackrop'),(39,'doorish'),(40,'doorstraight'),(41,'doublefist'),(42,'factory'),(43,'fistpower'),(44,'garagedoor'),(45,'garbagedoor'),(46,'gigerbackdrop'),(47,'hangar'),(48,'jovemech'),(49,'lights'),(50,'lightsnowindow'),(51,'mec'),(52,'mechyhall'),(53,'metalplate'),(54,'neon01'),(55,'neon02'),(56,'neon3'),(57,'neon4'),(58,'neon5'),(59,'rusty_metalheads'),(60,'sheetmetal_blue'),(61,'sheetmetal_green'),(62,'ship'),(63,'skins_n_metal'),(64,'sphinx'),(65,'sphinx_deco'),(66,'sphinxsofthe6threich'),(67,'steel'),(68,'tech_tribal'),(69,'tiles_green'),(70,'tiles_yellow'),(71,'tunnel'),(72,'window'),(73,'wood'),(74,'Asian Metal Ornament'),(75,'Asian Pattern Plate'),(76,'Asian Royal Glass'),(77,'Asian Space Window'),(78,'Asian Tiger Painting'),(79,'Asian Wood Ornament'),(80,'Asian wood ornaments'),(81,'AsianDragons');
/*!40000 ALTER TABLE `chrBackgrounds` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:47

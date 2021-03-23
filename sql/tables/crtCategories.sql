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
-- Table structure for table `crtCategories`
--

DROP TABLE IF EXISTS `crtCategories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crtCategories` (
  `categoryID` tinyint(3) unsigned NOT NULL,
  `description` varchar(500) DEFAULT NULL,
  `categoryName` varchar(256) DEFAULT NULL,
  `categoryNameID` int(10) unsigned DEFAULT '0',
  `dataID` int(10) unsigned DEFAULT '0',
  PRIMARY KEY (`categoryID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crtCategories`
--

LOCK TABLES `crtCategories` WRITE;
/*!40000 ALTER TABLE `crtCategories` DISABLE KEYS */;
INSERT INTO `crtCategories` VALUES (3,'Core Certificates','Core',16,22250862),(4,'Starter Professions','Starter Professions',15,16559510),(5,'Defense','Defense',7,34288261),(6,'Gunnery','Gunnery',8,16559503),(7,'Missiles','Missiles',9,16559504),(8,'Drones','Drones',10,16559505),(9,'Electronic Warfare','Electronic Warfare',11,16559506),(10,'Navigation','Navigation',12,16559507),(11,'Leadership','Leadership',17,22250878),(12,'Harvesting','Harvesting',13,16559508),(13,'Business and Industry','Business and Industry',14,16559509),(18,'Colony Management','Planetary Interaction',19,16559511);
/*!40000 ALTER TABLE `crtCategories` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:50

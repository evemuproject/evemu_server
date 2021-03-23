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
-- Table structure for table `paperdollModifierLocations`
--

DROP TABLE IF EXISTS `paperdollModifierLocations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `paperdollModifierLocations` (
  `modifierLocationID` int(11) NOT NULL DEFAULT '0',
  `modifierKey` text COLLATE utf8_unicode_ci,
  `variationKey` text COLLATE utf8_unicode_ci,
  PRIMARY KEY (`modifierLocationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `paperdollModifierLocations`
--

LOCK TABLES `paperdollModifierLocations` WRITE;
/*!40000 ALTER TABLE `paperdollModifierLocations` DISABLE KEYS */;
INSERT INTO `paperdollModifierLocations` VALUES (2,'topouter','dependants/drape'),(3,'makeup/implants',''),(4,'accessories/earslow',''),(5,'hair',''),(6,'makeup/eyes',''),(7,'makeup/lipstick',''),(8,'makeup/blush',''),(9,'makeup/eyeshadow',''),(10,'outer','dependants/hood'),(11,'makeup/freckles',''),(12,'accessories/nose',''),(13,'accessories/nostril',''),(14,'accessories/lips',''),(15,'makeup/aging',''),(16,'beard',''),(17,'makeup/eyeliner',''),(18,'makeup/eyelashes',''),(19,'accessories/earshigh',''),(20,'makeup/eyebrows',''),(21,'accessories/glasses',''),(22,'feet',''),(23,'bottominner',''),(24,'makeup/scarring',''),(25,'bottomouter','dependants/boottucking'),(26,'topmiddle','dependants/drape'),(27,'topinner',''),(28,'scars/head',''),(29,'accessories/brow',''),(30,'tattoo/head',''),(31,'archetypes',''),(32,'accessories/chin',''),(33,'accessories',''),(34,'accessories/piercings','');
/*!40000 ALTER TABLE `paperdollModifierLocations` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:47

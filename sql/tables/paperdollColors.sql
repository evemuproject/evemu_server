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
-- Table structure for table `paperdollColors`
--

DROP TABLE IF EXISTS `paperdollColors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `paperdollColors` (
  `colorID` int(11) NOT NULL DEFAULT '0',
  `colorKey` text COLLATE utf8_unicode_ci,
  `hasSecondary` bit(1) NOT NULL DEFAULT b'0',
  `hasWeight` bit(1) NOT NULL DEFAULT b'0',
  `hasGloss` bit(1) NOT NULL DEFAULT b'0',
  PRIMARY KEY (`colorID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `paperdollColors`
--

LOCK TABLES `paperdollColors` WRITE;
/*!40000 ALTER TABLE `paperdollColors` DISABLE KEYS */;
INSERT INTO `paperdollColors` VALUES (2,'topouter','\0','\0','\0'),(3,'makeup/implants','\0','\0','\0'),(4,'accessories/earslow','\0','\0','\0'),(5,'skintone','\0','\0','\0'),(6,'hair','','\0','\0'),(7,'makeup/eyes','\0','\0','\0'),(8,'makeup/lipstick','\0','',''),(9,'makeup/blush','\0','','\0'),(10,'makeup/eyeshadow','','','\0'),(11,'outer','\0','\0','\0'),(12,'accessories/nose','\0','\0','\0'),(13,'accessories/nostril','\0','\0','\0'),(14,'accessories/lips','\0','\0','\0'),(15,'beard','\0','\0','\0'),(16,'makeup/eyeliner','\0','','\0'),(17,'topmiddle','\0','\0','\0'),(18,'accessories/earshigh','\0','\0','\0'),(19,'makeup/eyebrows','\0','\0','\0'),(20,'accessories/glasses','\0','\0','\0'),(21,'feet','\0','\0','\0'),(22,'bottominner','\0','\0','\0'),(23,'bottomouter','\0','\0','\0'),(24,'accessories/brow','\0','\0','\0'),(25,'topinner','\0','\0','\0'),(26,'tattoo/head','\0','',''),(27,'accessories/piercings','\0','\0','\0');
/*!40000 ALTER TABLE `paperdollColors` ENABLE KEYS */;
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

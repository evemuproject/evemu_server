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
-- Table structure for table `chrLipsticks`
--

DROP TABLE IF EXISTS `chrLipsticks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrLipsticks` (
  `lipstickID` int(10) unsigned NOT NULL DEFAULT '0',
  `lipstickName` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`lipstickID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrLipsticks`
--

LOCK TABLES `chrLipsticks` WRITE;
/*!40000 ALTER TABLE `chrLipsticks` DISABLE KEYS */;
INSERT INTO `chrLipsticks` VALUES (1,'1'),(2,'2'),(3,'3'),(4,'4'),(5,'5'),(6,'6'),(7,'Black gloss'),(8,'Blue punk'),(9,'Copperred'),(10,'Crimson'),(11,'Flaming lips'),(12,'Gloss'),(13,'Gold'),(14,'Golden gloss'),(15,'Luminant blue'),(16,'Metallic diffused'),(17,'None'),(18,'Red gloss'),(19,'Soft darkred'),(20,'Soft purple'),(21,'Taste of blood'),(22,'14'),(23,'15'),(24,'7'),(25,'8'),(26,'9'),(27,'Rose metal'),(28,'Bourgogne gloss'),(29,'Dark purple'),(30,'Glossy'),(31,'Pale rose'),(32,'Purple gloss'),(33,'Rose'),(34,'Rust'),(35,'Velvet light'),(36,'White dot'),(37,'10'),(38,'12'),(39,'-none'),(40,'Grey gloss'),(41,'Lead'),(42,'11'),(43,'13'),(44,'16'),(45,'17'),(46,'Bright purple'),(47,'Purple glossy'),(48,'Subtle glossy purple'),(49,'Subtle glossy pink'),(50,'Subtle'),(51,'Softgloss'),(52,'Soft Rose'),(53,'Glossy rose'),(54,'Glossy pink'),(55,'Subtle gloss'),(56,'pink gloss'),(57,'Heavy glossy'),(58,'grey'),(59,'Glossy red'),(60,'Fiery red'),(61,'Supergloss'),(62,'Subtle pink'),(63,'subtle bronzy'),(64,'Pink superglossy'),(65,'Pink glossy'),(66,'Pink'),(67,'Dark brown glossy'),(68,'Crimson supergloss');
/*!40000 ALTER TABLE `chrLipsticks` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:48

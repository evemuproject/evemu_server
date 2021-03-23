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
-- Table structure for table `chrMakeups`
--

DROP TABLE IF EXISTS `chrMakeups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrMakeups` (
  `makeupID` int(10) unsigned NOT NULL DEFAULT '0',
  `makeupName` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`makeupID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrMakeups`
--

LOCK TABLES `chrMakeups` WRITE;
/*!40000 ALTER TABLE `chrMakeups` DISABLE KEYS */;
INSERT INTO `chrMakeups` VALUES (1,'1'),(2,'10'),(3,'11'),(4,'2'),(5,'3'),(6,'4'),(7,'5'),(8,'7'),(9,'9'),(10,'Black jester'),(11,'Dark jester'),(12,'Feline'),(13,'Mercury'),(14,'Mercury black'),(15,'Metal feline'),(16,'None'),(17,'Redmetal feline'),(18,'Silver stripes'),(19,'Subtle bronze'),(20,'6'),(21,'8'),(22,'Blue shade'),(23,'Crimson pins'),(24,'Decorative grand red'),(25,'Decorative red'),(26,'Golden vail'),(27,'Mad purple'),(28,'Mad red'),(29,'Mad rust'),(30,'rust'),(31,'Silver feline'),(32,'Silvershade'),(33,'Subtle shade'),(34,'Velvet'),(35,'13'),(36,'-none'),(37,'12'),(38,'14'),(39,'15'),(40,'20'),(41,'21'),(42,'22'),(43,'23'),(44,'Black beams'),(45,'Dark mercury'),(46,'Green beams'),(47,'16'),(48,'17'),(49,'18'),(50,'19'),(51,'Green beams'),(52,'Aqua stripes'),(53,'Blue shine'),(54,'Blue stripes'),(55,'Golden stripes'),(56,'Greenshade'),(57,'Purple metal'),(58,'Red metal stripes'),(59,'Red shade'),(60,'Brownl high'),(61,'Dark high'),(62,'Dark lashes'),(63,'Eyeliner'),(64,'Metal high'),(65,'Strong feline'),(66,'Subtle feline'),(67,'Subtle flame'),(68,'Dark overcast'),(69,'Subtle green'),(70,'Shade'),(71,'Heavy bronze'),(72,'Dark moss'),(73,'Dark feline'),(74,'BlueShade'),(75,'Black feline'),(76,'Brown lashes');
/*!40000 ALTER TABLE `chrMakeups` ENABLE KEYS */;
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

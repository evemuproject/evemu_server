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
-- Table structure for table `chrDecos`
--

DROP TABLE IF EXISTS `chrDecos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrDecos` (
  `decoID` int(10) unsigned NOT NULL DEFAULT '0',
  `decoName` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`decoID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrDecos`
--

LOCK TABLES `chrDecos` WRITE;
/*!40000 ALTER TABLE `chrDecos` DISABLE KEYS */;
INSERT INTO `chrDecos` VALUES (1,'1'),(2,'10'),(3,'11'),(4,'14'),(5,'15'),(6,'16'),(7,'2'),(8,'3'),(9,'4'),(10,'5'),(11,'6'),(12,'7'),(13,'8'),(14,'9'),(15,'Cheeks dark'),(16,'Cheeks metal'),(17,'Forehead'),(18,'none'),(19,'Red dragon'),(20,'Red flowers'),(21,'Silverdragon'),(22,'12'),(23,'13'),(24,'17'),(25,'18'),(26,'19'),(27,'20'),(28,'21'),(29,'22'),(30,'23'),(31,'Black tribe'),(32,'Chrome'),(33,'Copper'),(34,'Gold chin'),(35,'Spike tattoo'),(36,'Spikes gold'),(37,'White chin'),(38,'Jester bloodred'),(39,'Jester Gold'),(40,'Jester lead'),(41,'Lead singleside'),(42,'Singleside blood'),(43,'Singleside white'),(44,'Star transparent'),(45,'Unnamed'),(46,'Crimson shell'),(47,'Crimson tears'),(48,'Crimson vail'),(49,'Gold emblem'),(50,'Gold pins'),(51,'Golden shell'),(52,'Platininum'),(53,'Silverstream'),(54,'Wing front'),(55,'Wings of gold'),(56,'Emblem'),(57,'Forehead gold'),(58,'Forehead titanium'),(59,'Gold implant'),(60,'Gold knobs'),(61,'Gold point'),(62,'Gold trim'),(63,'wings'),(64,'claw'),(65,'delecate'),(66,'hulin'),(67,'Shell'),(68,'Tigris'),(69,'Twin'),(70,'widow'),(71,'Bronze implant'),(72,'Bronze sting'),(73,'Dark emblem'),(74,'Dark wings'),(75,'Metal implant'),(76,'-none'),(77,'Black spikes'),(78,'Cheek spikes'),(79,'Cheek stripes'),(80,'Golden star'),(81,'Implant'),(82,'Silver star'),(83,'24'),(84,'25'),(85,'26'),(86,'27'),(87,'28'),(88,'29'),(89,'30'),(90,'31'),(91,'32'),(92,'34'),(93,'35'),(94,'36'),(95,'37'),(96,'Dark flare'),(97,'Flare'),(98,'Sidechrome'),(99,'White dots'),(100,'i3'),(101,'i5'),(102,'Tattoo Strips 2'),(103,'Tattoo Strips'),(104,'Tattoo 2'),(105,'Tattoo 1'),(106,'None'),(107,'Forehead Symbol'),(108,'Cheek Symbol'),(109,'Water Tattoo'),(110,'Water red'),(111,'Water dark'),(112,'Warrior Tattoo'),(113,'Warrior 2'),(114,'War Paint'),(115,'Side tatto mirror'),(116,'Side tatto'),(117,'Shaman Tattoo'),(118,'Fangs Tattoo 2'),(119,'Fangs Tattoo'),(120,'Facial Scars'),(121,'Eye Scar'),(122,'Blood side mirror'),(123,'Blood side'),(124,'Forehead Tattoo Right'),(125,'Forehead Tattoo Left'),(126,'Cheek Tattoo Right'),(127,'Cheek Tattoo Left'),(128,'Warrior Tatto mirrored'),(129,'Scar Eye'),(130,'Scar Cheek'),(131,'Implant2'),(132,'Implant1'),(133,'Implant 2 mirror'),(134,'Grim Tattoo'),(135,'Golden tattoo mirror'),(136,'Golden tattoo');
/*!40000 ALTER TABLE `chrDecos` ENABLE KEYS */;
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

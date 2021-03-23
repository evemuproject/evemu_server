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
-- Table structure for table `paperdollSculptingLocations`
--

DROP TABLE IF EXISTS `paperdollSculptingLocations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `paperdollSculptingLocations` (
  `sculptLocationID` int(11) NOT NULL DEFAULT '0',
  `weightKeyCategory` text COLLATE utf8_unicode_ci,
  `weightKeyPrefix` text COLLATE utf8_unicode_ci,
  PRIMARY KEY (`sculptLocationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `paperdollSculptingLocations`
--

LOCK TABLES `paperdollSculptingLocations` WRITE;
/*!40000 ALTER TABLE `paperdollSculptingLocations` DISABLE KEYS */;
INSERT INTO `paperdollSculptingLocations` VALUES (2,'bodyShapes','shoulders'),(3,'bodyShapes','neck'),(4,'bodyShapes','muscular'),(5,'bodyShapes','fat'),(6,'bodyShapes','feet'),(7,'bodyShapes','pinchchest'),(8,'bodyShapes','chest'),(9,'bodyShapes','abs'),(10,'bodyShapes','thin'),(11,'bodyShapes','pelvis'),(12,'bodyShapes','legs'),(13,'faceModifiers','eyes'),(14,'faceModifiers','nosebone'),(15,'faceModifiers','jawcheek'),(16,'faceModifiers','upperlip'),(17,'faceModifiers','nostrils'),(18,'faceModifiers','jaw'),(19,'faceModifiers','outerbrow'),(20,'faceModifiers','eyesouter'),(21,'faceModifiers','eyesinner'),(22,'faceModifiers','nosetip'),(23,'faceModifiers','chin'),(24,'faceModifiers','lowerlip'),(25,'faceModifiers','innerbrow'),(26,'faceModifiers','cheeksupper'),(27,'faceModifiers','nose'),(28,'faceModifiers','mouthcorner'),(29,'faceModifiers','cheeksmiddle'),(30,'faceModifiers','ears'),(31,'utilityShapes','pinchhem'),(32,'utilityShapes','pinchchest'),(33,'utilityShapes','pinchdrapehide'),(34,'utilityShapes','pinchforearmhigh'),(35,'utilityShapes','pinchdrapefull'),(36,'utilityShapes','pincharmhigh'),(37,'utilityShapes','pinchbootankle'),(38,'utilityShapes','pantstuckknee'),(39,'utilityShapes','pinchdrape'),(40,'utilityShapes','pinchforearmlow'),(41,'utilityShapes','pantstuckmedium'),(42,'utilityShapes','pinchboothighshin'),(43,'utilityShapes','pinchbootknee'),(44,'utilityShapes','pinchtuck'),(45,'utilityShapes','pincharmlow'),(46,'utilityShapes','pantstuckshin'),(47,'utilityShapes','pinchhips'),(48,'utilityShapes','pantstucklow'),(49,'utilityShapes','pinchdfull'),(50,'utilityShapes','pantstuckhigh'),(51,'utilityShapes','pinchinner'),(52,'utilityShapes','pantstuckxhigh'),(53,'utilityShapes','pinchbootlowshin');
/*!40000 ALTER TABLE `paperdollSculptingLocations` ENABLE KEYS */;
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

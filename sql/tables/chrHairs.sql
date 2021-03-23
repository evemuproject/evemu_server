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
-- Table structure for table `chrHairs`
--

DROP TABLE IF EXISTS `chrHairs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrHairs` (
  `hairID` int(10) unsigned NOT NULL DEFAULT '0',
  `hairName` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`hairID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrHairs`
--

LOCK TABLES `chrHairs` WRITE;
/*!40000 ALTER TABLE `chrHairs` DISABLE KEYS */;
INSERT INTO `chrHairs` VALUES (1,'1'),(2,'2'),(3,'3'),(4,'4'),(5,'5'),(6,'Dreadlocks'),(7,'Dreads golden'),(8,'Read dreads'),(9,'Short dreads'),(10,'10'),(11,'6'),(12,'7'),(13,'8'),(14,'9'),(15,'Backwards bone'),(16,'None'),(17,'Snakes'),(18,'Tail with bones'),(19,'Wild'),(20,'11'),(21,'Brown snake'),(22,'Dark brown swoosh'),(23,'Mohawk'),(24,'Purple snake'),(25,'Red snake'),(26,'Ritual'),(27,'Short blonde'),(28,'Silvergray'),(29,'Silvery'),(30,'Tribal'),(31,'Albino metal'),(32,'Black mohawk'),(33,'Golden shaved'),(34,'Jester'),(35,'Long tail'),(36,'Red mohawk'),(37,'Short black spikes'),(38,'3rd eye red'),(39,'Basic blonde'),(40,'Basic umber'),(41,'Blonde tails'),(42,'Dark'),(43,'Dark gold'),(44,'Golden studs'),(45,'Gray tails'),(46,'Long'),(47,'Ornamental'),(48,'Traditional dark'),(49,'Traditional gray'),(50,'High'),(51,'Point'),(52,'sides'),(53,'Slick knot'),(54,'Wild sides'),(55,'Black'),(56,'Crimson Hijab'),(57,'Dark long'),(58,'Dark ornamental'),(59,'Darker'),(60,'Darker gold'),(61,'Tail gold'),(62,'Tail metal'),(63,'Traditional gold'),(64,'Traditional metal'),(65,'Velvet'),(66,'Wild elegance'),(67,'Dark wild'),(68,'Knot'),(69,'Short black'),(70,'Short silver'),(71,'Sticks'),(72,'Subtle sides'),(73,'Blonde loose'),(74,'Copper'),(75,'Golden'),(76,'Pink loose'),(77,'Red dreads'),(78,'Red loose'),(79,'Shaven'),(80,'Short brown'),(81,'Short red'),(82,'12'),(83,'13'),(84,'Blackjack'),(85,'Bleached'),(86,'Darkjack'),(87,'Greybrown'),(88,'Shave'),(89,'White'),(90,'14'),(91,'15'),(92,'Luminant'),(93,'Rose'),(94,'Black slick'),(95,'Blonde'),(96,'Brown slick'),(97,'Grey slick'),(98,'Light brown'),(99,'Aqua dark'),(100,'Blue'),(101,'Blue sides'),(102,'Flame Flamboyance'),(103,'Golden feathers'),(104,'Red feathers'),(105,'Silver feathers'),(106,'wild flame'),(107,'aurantium'),(108,'caldaristyle1'),(109,'caldaristyle2'),(110,'caldaristyle3'),(111,'caldaristyle4'),(112,'caldaristyle5'),(113,'flimtop'),(114,'fuchsin'),(115,'fuzztop'),(116,'Mr brunette'),(117,'Pink fuzztop'),(118,'redtop'),(119,'silver'),(120,'Toxic egghead'),(121,'toxic trauma'),(122,'viridian front'),(123,'16'),(124,'blond_sidemetals'),(125,'brunette _sidegold'),(126,'chromefront'),(127,'dark_oceano'),(128,'unigold_rouge'),(129,'Dark and long'),(130,'Long blonde'),(131,'Medium'),(132,'joveHair'),(133,'01'),(134,'02'),(135,'03'),(136,'04'),(137,'05'),(138,'06'),(139,'07'),(140,'08'),(141,'09'),(142,'10'),(143,'11'),(144,'12'),(145,'13'),(146,'14'),(147,'15'),(148,'16'),(149,'17'),(150,'18'),(151,'19'),(152,'20'),(153,'21'),(154,'22'),(155,'23'),(156,'24'),(157,'25'),(158,'26'),(159,'27'),(160,'28'),(161,'29'),(162,'30'),(163,'Pitch black'),(164,'Red knots'),(165,'Red plastic ornament'),(166,'Red sideways'),(167,'Red straight'),(168,'Ornamental hair'),(169,'Ornamental black hair'),(170,'hipurple'),(171,'Black blown'),(172,'Golden brown'),(173,'Black glossy'),(174,'ImplantHair2'),(175,'ImplantHair'),(176,'Greybrown straight'),(177,'Grey'),(178,'Dark straight'),(179,'Brown straight'),(180,'Black straight'),(181,'Pitch black sideways'),(182,'Pitch black knots'),(183,'Golden brown sideways'),(184,'Golden Brown no ornament'),(185,'Golden brown knots'),(186,'Golden Brown'),(187,'Brown with copper ornaments'),(188,'Brown plastic ornament'),(189,'Brown'),(190,'Greybrown shiny'),(191,'Grey shiny 2'),(192,'Grey shiny'),(193,'Dark matte'),(194,'Dark Grey Combed Hair'),(195,'Brown high'),(196,'Black matte 2'),(197,'Black matte'),(198,'Black Combed Hair'),(199,'Bald'),(200,'Long ultrashine'),(201,'Long lowshine'),(202,'Long grey lowshine'),(203,'Long dark shiny'),(204,'High Dark Shiny'),(205,'Dark high'),(206,'White Warrior Headpiece 2'),(207,'White Warrior Headpiece'),(208,'Superbright Helmet'),(209,'Shiny bronze hairpiece'),(210,'Red Warrior Headpiece'),(211,'Helmet 1'),(212,'Grey Hair'),(213,'Darklight Warrior Headpiece'),(214,'Dark brown fan'),(215,'Bronze helmet'),(216,'Black hair'),(217,'Silver Hood'),(218,'Nocturnal Hood'),(219,'Long Grey Golden'),(220,'Long Dark Silver'),(221,'Long Dark Sidehair'),(222,'Long Dark Golden'),(223,'Long Black Silver'),(224,'Gold Hood'),(225,'Dark Rim Hood'),(226,'Dark Border Hood'),(227,'Bronze Hood'),(228,'Bald Grey'),(229,'Bald dark');
/*!40000 ALTER TABLE `chrHairs` ENABLE KEYS */;
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

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
-- Table structure for table `paperdollColorNames`
--

DROP TABLE IF EXISTS `paperdollColorNames`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `paperdollColorNames` (
  `colorNameID` int(11) NOT NULL DEFAULT '0',
  `colorName` text COLLATE utf8_unicode_ci,
  PRIMARY KEY (`colorNameID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `paperdollColorNames`
--

LOCK TABLES `paperdollColorNames` WRITE;
/*!40000 ALTER TABLE `paperdollColorNames` DISABLE KEYS */;
INSERT INTO `paperdollColorNames` VALUES (2,'gold'),(3,'03_a'),(4,'intaki_dark'),(5,'vherokior_default'),(6,'generic02'),(7,'pink_medium'),(8,'yellow'),(9,'generic01'),(10,'13_a'),(11,'aqua_a'),(12,'greenblue_abc'),(13,'red_matte'),(14,'20_a'),(15,'08_bc'),(16,'gallente'),(17,'orange_a'),(18,'amarr_dark'),(19,'rosered_a'),(20,'green_abc'),(21,'16_bc'),(22,'28_bc'),(23,'14_bc'),(24,'black'),(25,'05_a'),(26,'nikunni_light'),(27,'silver_light_medium'),(28,'orange'),(29,'22_a'),(30,'24_bc'),(31,'gallente_dark'),(32,'warmgray_bc'),(33,'goldgreen_a'),(34,'brown'),(35,'silver_a'),(36,'deteis'),(37,'09_a'),(38,'amarr'),(39,'blue_medium'),(40,'circlewhite'),(41,'warmgray_a'),(42,'civire_light'),(43,'intaki_midlight'),(44,'07_a'),(45,'vherockior'),(46,'silver'),(47,'gold_bc'),(48,'aqua_bc'),(49,'hazel_abc'),(50,'darkgreen_abc'),(51,'03_bc'),(52,'01_a'),(53,'vherokior_light'),(54,'sebiestor_default'),(55,'goldengraved'),(56,'gallente_middark'),(57,'deteis_midlight'),(58,'purple_bc'),(59,'silver_dark_glossy'),(60,'07_bc'),(61,'turkish_bc'),(62,'blue_a'),(63,'green_bc'),(64,'brown_bc'),(65,'26_bc'),(66,'deteis_default'),(67,'11_bc'),(68,'turkish_a'),(69,'green_matte'),(70,'jinmei_midlight'),(71,'achura_dark'),(72,'19_a'),(73,'mossgreen_bc'),(74,'jinmei_dark'),(75,'khanid_midlight'),(76,'jinmei'),(77,'rustred_bc'),(78,'02_a'),(79,'nikunni_midlight'),(80,'extra02'),(81,'extra01'),(82,'redbrown_abc'),(83,'extra03'),(84,'04_bc'),(85,'sebiestor_middark'),(86,'blue'),(87,'deteis_light'),(88,'06_a'),(89,'silver_light_glossy'),(90,'purple'),(91,'amarr_midlight'),(92,'gold_a'),(93,'silver_bc'),(94,'silver_light_matte'),(95,'goldgreen_bc'),(96,'darkgray_abc'),(97,'purplish'),(98,'04_a'),(99,'red'),(100,'pink_glossy'),(101,'brutor_dark'),(102,'darkred_glossy'),(103,'black_a'),(104,'rosie'),(105,'rosered_bc'),(106,'black_glossy'),(107,'khanid_middark'),(108,'olivegreen_a'),(109,'yellow_bc'),(110,'08_a'),(111,'silver_dark_medium'),(112,'purple_a'),(113,'amarr_middark'),(114,'achura'),(115,'27_bc'),(116,'achura_midlight'),(117,'civire_middark'),(118,'brutor_default'),(119,'darkbrown_abc'),(120,'achura_default'),(121,'25_bc'),(122,'gallente_light'),(123,'civire_default'),(124,'olivegreen_bc'),(125,'09_bc'),(126,'mossgreen_a'),(127,'deteis_middark'),(128,'21_bc'),(129,'gray_abc'),(130,'intaki_light'),(131,'yellow_a'),(132,'coldgray_a'),(133,'nikunni_default'),(134,'lightgreen_bc'),(135,'brutor_midlight'),(136,'civire_dark'),(137,'15_bc'),(138,'orange_bc'),(139,'bluish'),(140,'blue_matte'),(141,'gold_matte'),(142,'22_bc'),(143,'14_a'),(144,'red_a'),(145,'brown_a'),(146,'green_medium'),(147,'10_bc'),(148,'nikunni'),(149,'lightblue_bc'),(150,'sebiestor_midlight'),(151,'grayblue_abc'),(152,'gallente_default'),(153,'blue_abc'),(154,'red_medium'),(155,'khanid'),(156,'white'),(157,'jinmei_middark'),(158,'navyblue_bc'),(159,'khanid_dark'),(160,'nikunni_dark'),(161,'vherokior_midlight'),(162,'rustred_a'),(163,'sebiestor'),(164,'vherokior_dark'),(165,'06_bc'),(166,'vherokior_middark'),(167,'11_a'),(168,'brutor_middark'),(169,'jinmei_default'),(170,'navyblue_a'),(171,'17_bc'),(172,'olive'),(173,'deteis_dark'),(174,'sebiestor_light'),(175,'silver_dark_matte'),(176,'15_a'),(177,'12_bc'),(178,'reddish'),(179,'default'),(180,'gold_medium'),(181,'intaki'),(182,'05_bc'),(183,'nikunni_middark'),(184,'khanid_light'),(185,'intaki_default'),(186,'17_a'),(187,'gold_glossy'),(188,'blue_bc'),(189,'white_a'),(190,'red_glossy'),(191,'green_a'),(192,'intaki_middark'),(193,'green_glossy'),(194,'18_bc'),(195,'iceblue_abc'),(196,'gallente_midlight'),(197,'brutor'),(198,'brown_abc'),(199,'pink_bc'),(200,'blond'),(201,'civire'),(202,'achura_light'),(203,'lightgreen_a'),(204,'redish'),(205,'darkred_medium'),(206,'amarr_default'),(207,'sebiestor_dark'),(208,'01_bc'),(209,'19_bc'),(210,'khanid_default'),(211,'red_bc'),(212,'amarr_light'),(213,'bloodred_bc'),(214,'black_bc'),(215,'13_bc'),(216,'02_bc'),(217,'pink_a'),(218,'blue_glossy'),(219,'black_matte'),(220,'vherokior'),(221,'bloodred_a'),(222,'10_a'),(223,'20_bc'),(224,'darkblue_abc'),(225,'12_a'),(226,'darkred_matte'),(227,'achura_middark'),(228,'pink_matte'),(229,'21_a'),(230,'civire_midlight'),(231,'lightblue_a'),(232,'dark'),(233,'jinmei_light'),(234,'white_bc'),(235,'black_medium'),(236,'23_bc'),(237,'green'),(238,'16_a'),(239,'coldgray_bc'),(240,'brutor_light'),(241,'18_a'),(242,'generic03'),(243,'default_a');
/*!40000 ALTER TABLE `paperdollColorNames` ENABLE KEYS */;
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

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
-- Table structure for table `chrCostumes`
--

DROP TABLE IF EXISTS `chrCostumes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrCostumes` (
  `costumeID` int(10) unsigned NOT NULL DEFAULT '0',
  `costumeName` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`costumeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrCostumes`
--

LOCK TABLES `chrCostumes` WRITE;
/*!40000 ALTER TABLE `chrCostumes` DISABLE KEYS */;
INSERT INTO `chrCostumes` VALUES (1,'1'),(2,'10'),(3,'11'),(4,'12'),(5,'13'),(6,'14'),(7,'15'),(8,'16'),(9,'17'),(10,'18'),(11,'19'),(12,'2'),(13,'21'),(14,'22'),(15,'23'),(16,'24'),(17,'25'),(18,'3'),(19,'4'),(20,'8'),(21,'9'),(22,'blackLeather'),(23,'brownleather'),(24,'20'),(25,'7'),(26,'Armor 1'),(27,'Armor 2'),(28,'Armor 4'),(29,'Armor 6'),(30,'26'),(31,'27'),(32,'5'),(33,'6'),(34,'costume 2'),(35,'costume1'),(36,'Classic gown'),(37,'countess'),(38,'deep blue'),(39,'GoreTex Jacket'),(40,'Grand royal'),(41,'Grey cloak'),(42,'marquis'),(43,'Metal poncho'),(44,'night'),(45,'Purple cloak'),(46,'royal collar'),(47,'Royal collar gold'),(48,'Royal collar rouge'),(49,'Silver gown'),(50,'standard midday gown'),(51,'White cloak'),(52,'Chromearound'),(53,'Crimson abito royal'),(54,'crimson tunic'),(55,'Darkaround'),(56,'Golden robe'),(57,'Negro abito royal'),(58,'tunica'),(59,'Velvet abito royal'),(60,'Blood'),(61,'Velvet'),(62,'Black'),(63,'Bronze cura'),(64,'Bronze tyrant'),(65,'Dark cura'),(66,'gown'),(67,'Metal tinna'),(68,'sterling'),(69,'Battlearmor'),(70,'Cybertech'),(71,'Desert'),(72,'Heavy marine'),(73,'Jungle'),(74,'Special ops'),(75,'Wintercamo'),(76,'29'),(77,'30'),(78,'golden officer'),(79,'Officer'),(80,'officer green'),(81,'police'),(82,'basic metal'),(83,'Black plastic'),(84,'Blue plastic'),(85,'fly cobalt'),(86,'fly crimson'),(87,'Ice'),(88,'Leather'),(89,'metalneck'),(90,'pink as hell'),(91,'Pink plastic'),(92,'plastic'),(93,'plastic copper'),(94,'Plastic gold'),(95,'plastic ivy'),(96,'Shiny plastic'),(97,'silver'),(98,'smooth basic'),(99,'toxic'),(100,'turquoise dream'),(101,'White plastic'),(102,'2nd symmetry'),(103,'B eye plasticote'),(104,'basic T'),(105,'bronze'),(106,'centerpiece basic'),(107,'Collar turq'),(108,'crimson collar'),(109,'crimson T'),(110,'dark shine'),(111,'glam'),(112,'golden boy'),(113,'greenishplastic'),(114,'iceheart'),(115,'plasticovercote'),(116,'Purple plasticote'),(117,'sidecut flame'),(118,'sidecut swing'),(119,'symmetry sting'),(120,'twocote'),(121,'whiteplastic'),(122,'beige'),(123,'blood robe'),(124,'blue ice'),(125,'blue silk'),(126,'cloth cloth'),(127,'dark metal'),(128,'di rame verde'),(129,'elegant'),(130,'elegant colour'),(131,'elegant silver'),(132,'grey stone'),(133,'leather vest'),(134,'nature'),(135,'symmetry basic'),(136,'tin shine'),(137,'velvet basic'),(138,'verde rosso'),(139,'alchemist'),(140,'B-man'),(141,'B-man alloy'),(142,'beige B-man'),(143,'black robe'),(144,'crimson robe'),(145,'fresco'),(146,'gold extravaganza'),(147,'grendeur robe'),(148,'leisure suit'),(149,'shoulder toca'),(150,'standard robe'),(151,'suit01'),(152,'suit02'),(153,'suit03'),(154,'suit04'),(155,'01'),(156,'02'),(157,'03'),(158,'04'),(159,'05'),(160,'06'),(161,'07'),(162,'08'),(163,'09'),(164,'10'),(165,'11'),(166,'12'),(167,'13'),(168,'14'),(169,'15'),(170,'16'),(171,'17'),(172,'18'),(173,'19'),(174,'20'),(175,'21'),(176,'22'),(177,'23'),(178,'24'),(179,'25'),(180,'26'),(181,'27'),(182,'28'),(183,'29'),(184,'30'),(185,'Brown bone'),(186,'Brown transparent'),(187,'Dark golden'),(188,'Dark grey bone'),(189,'Dark grey red sleeves'),(190,'Darker grey bone'),(191,'Gray Bone Collar'),(192,'Light Gray'),(193,'R9'),(194,'R8'),(195,'R7'),(196,'R6'),(197,'R5'),(198,'R4'),(199,'R3'),(200,'R2'),(201,'R14'),(202,'R13'),(203,'R12'),(204,'R11'),(205,'R10'),(206,'R1'),(207,'Shiny nylon'),(208,'Lightgtey coat'),(209,'Grey coat'),(210,'Gray nylon'),(211,'Dark brown'),(212,'Brown shiny'),(213,'Brown nylon'),(214,'Blue nylon'),(215,'Army green'),(216,'03 better position'),(217,'02 better position'),(218,'01 right place'),(219,'White transparent sleeves'),(220,'White transparent gold'),(221,'White shirt'),(222,'Transparent sleeves smooth'),(223,'Transparent sleeves'),(224,'Red white gold'),(225,'Red silk and bronze'),(226,'Red ornaments no collar'),(227,'Red ornaments'),(228,'Red orange silk no collar'),(229,'Red orange silk'),(230,'Red and gold bone'),(231,'Purple transparent sleeves'),(232,'Dark and bronze'),(233,'Brown'),(234,'Silvery Ribbon Uniform'),(235,'Shiny leather'),(236,'Olive Ribbon Uniform'),(237,'Labcoat no headset'),(238,'Labcoat'),(239,'Grey Trenchcoat'),(240,'Grey Ribbon Uniform Headset'),(241,'Grey Ribbon Uniform'),(242,'Brown Trenchcoat'),(243,'Brown Ribbon Uniform'),(244,'Blue grey leather'),(245,'BlackTrenchcoat'),(246,'Black leather'),(247,'Shiny Cloak'),(248,'Red cloak'),(249,'Mystic Vest'),(250,'Herder Vest'),(251,'Grey leather'),(252,'Desert Vest'),(253,'Desert Cloak'),(254,'Dark Shaman Vest'),(255,'Dark Leather Vest'),(256,'Dark leather'),(257,'White Warrior Garb'),(258,'White Patrician'),(259,'White Glowing Robe'),(260,'Shiny warrior 4'),(261,'Shiny Warrior 3'),(262,'Shiny warrior 2'),(263,'Shiny warrior'),(264,'Red Warrior Garb'),(265,'Red Glowing Robe'),(266,'Light Collar 2 R'),(267,'Grey not shiny 3'),(268,'Grey not shiny 2'),(269,'Grey not shiny'),(270,'Darklight Warrior Garb'),(271,'Dark Patrician'),(272,'Tungsten'),(273,'Temp'),(274,'Silver Robe'),(275,'Silver buttons'),(276,'Royal Buttons'),(277,'Regal'),(278,'Golden buttons'),(279,'Gold Robe'),(280,'Dark Rim Robe'),(281,'Dark brushed metal'),(282,'Bronze robe'),(283,'Bronze cape');
/*!40000 ALTER TABLE `chrCostumes` ENABLE KEYS */;
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

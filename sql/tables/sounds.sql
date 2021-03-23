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
-- Table structure for table `sounds`
--

DROP TABLE IF EXISTS `sounds`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sounds` (
  `soundID` int(11) NOT NULL DEFAULT '0',
  `soundFile` text COLLATE utf8_unicode_ci,
  `description` text COLLATE utf8_unicode_ci,
  `obsolete` bit(1) NOT NULL DEFAULT b'0',
  PRIMARY KEY (`soundID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sounds`
--

LOCK TABLES `sounds` WRITE;
/*!40000 ALTER TABLE `sounds` DISABLE KEYS */;
INSERT INTO `sounds` VALUES (8,'wise:/ship_mining_barge1_play','','\0'),(9,'wise:/worldobject_asteroidbelt_wind_play','','\0'),(10,'wise:/worldobject_harvester_play','','\0'),(11,'wise:/worldobject_infestedwreck_play','','\0'),(12,'wise:/worldobject_sleeper_drones_atmo_play','','\0'),(13,'wise:/worldobject_station_01_play','','\0'),(14,'wise:/worldobject_station_02_play','','\0'),(15,'wise:/worldobject_station_03_play','','\0'),(16,'wise:/worldobject_station_04_play','','\0'),(17,'wise:/worldobject_station_05_play','','\0'),(18,'wise:/worldobject_station_07_play','','\0'),(19,'wise:/worldobject_station_08_play','','\0'),(20,'wise:/worldobject_station_09_play','','\0'),(21,'wise:/worldobject_station_11_play','','\0'),(22,'wise:/worldobject_station_12_play','','\0'),(23,'wise:/worldobject_station_13_play','','\0'),(24,'wise:/worldobject_station_15_play','','\0'),(25,'wise:/worldobject_station_16_play','','\0'),(26,'wise:/worldobject_station_17_play','','\0'),(27,'wise:/worldobject_station_19_play','','\0'),(28,'wise:/worldobject_stationflame_play','','\0'),(30,'wise:/worldobject_police_chatter_play','A random selection of crossfades police chatter atmos sounds.','\0'),(31,'wise:/worldobject_pirates_chatter_play','A random selection of crossfades pirate chatter atmos','\0'),(32,'wise:/worldobject_jumpgate_atmo_play','the atmospheric buzzing sound around stargates.','\0'),(33,'wise:/worldobject_sov_disruptor_play','suttle humming sound for sovereignity disruptors.','\0'),(34,'wise:/worldobject_sov_flag_play','a subtle hum and a gentle beacon sound for sovereignity flags.','\0'),(35,'wise:/worldobject_sov_hub_play','A humming atmos for sovereignity hub','\0'),(10001,'','','\0'),(10002,'wise:/worldobject_sansha_capital_ship_play','Specific sound atmos for shansha capital ships.','\0'),(10003,'wise:/worldobject_sansha_asteroidbelt_play','A special asteroid belt atmos sound for sanshas nation region.','\0'),(10004,'wise:/hangar_sansha_play','a special sound Sanshas invasion hangars.','\0'),(10005,'wise:/worldobject_sansha_system_enter_play','A special one shot sound that plays when you enter a system.','\0'),(10007,'wise:/worldobject_station_sansha_play','a special sound which will override default space station (outside) sound.','\0');
/*!40000 ALTER TABLE `sounds` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:52

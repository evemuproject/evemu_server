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
-- Table structure for table `crtClasses`
--

DROP TABLE IF EXISTS `crtClasses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crtClasses` (
  `classID` int(3) unsigned NOT NULL DEFAULT '0',
  `className` varchar(150) COLLATE utf8_unicode_ci DEFAULT NULL,
  `description` text COLLATE utf8_unicode_ci,
  `classNameID` int(6) unsigned DEFAULT '0',
  `dataID` int(6) unsigned DEFAULT '0',
  PRIMARY KEY (`classID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crtClasses`
--

LOCK TABLES `crtClasses` WRITE;
/*!40000 ALTER TABLE `crtClasses` DISABLE KEYS */;
INSERT INTO `crtClasses` VALUES (2,'Core Fitting','Core Fitting',59287,0),(3,'Core Capacitor','Core Capacitor',59288,0),(4,'Core Targeting','Core Targeting',59289,0),(5,'Core Navigation','Core Navigation',59290,0),(6,'Core Competency','Core Competency',59291,0),(7,'Core Integrity','Core Integrity',59292,0),(8,'Amarr Military - Soldier','Amarr Military - Soldier',59372,0),(9,'Amarr Military - Special Forces','Amarr Military - Special Forces',59374,0),(10,'Amarr Industry - Engineer','Amarr Industry - Engineer',59375,0),(11,'Amarr Industry - Prospector','Amarr Industry - Prospector',59376,0),(12,'Amarr Business - Entrepreneur','Amarr Business - Entrepreneur',59377,0),(13,'Amarr Business - Executive Commander','Amarr Business - Executive Commander',59378,0),(14,'Caldari Military - Soldier','Caldari Military - Soldier',59379,0),(15,'Caldari Military - Special Forces','Caldari Military - Special Forces',59380,0),(16,'Caldari Industry - Engineer','Caldari Industry - Engineer',59381,0),(17,'Caldari Industry - Prospector','Caldari Industry - Prospector',59382,0),(18,'Caldari Business - Entrepreneur','Caldari Business - Entrepreneur',59383,0),(19,'Caldari Business - Executive Commander','Caldari Business - Executive Commander',59384,0),(20,'Gallente Military - Soldier','Gallente Military - Soldier',59385,0),(21,'Gallente Military - Special Forces','Gallente Military - Special Forces',59386,0),(22,'Gallente Industry - Engineer','Gallente Industry - Engineer',59387,0),(23,'Gallente Industry - Prospector','Gallente Industry - Prospector',59388,0),(24,'Gallente Business - Entrepreneur','Gallente Business - Entrepreneur',59389,0),(25,'Gallente Business - Executive Commander','Gallente Business - Executive Commander',59390,0),(26,'Minmatar Military - Soldier','Minmatar Military - Soldier',59391,0),(27,'Minmatar Military - Special Forces','Minmatar Military - Special Forces',59392,0),(28,'Minmatar Industry - Engineer','Minmatar Industry - Engineer',59393,0),(29,'Minmatar Industry - Prospector','Minmatar Industry - Prospector',59394,0),(30,'Minmatar Business - Entrepreneur','Minmatar Business - Entrepreneur',59395,0),(31,'Minmatar Business - Executive Commander','Minmatar Business - Executive Commander',59373,0),(32,'Armor Tanking','Armor Tanking',59293,0),(33,'Armor Reinforcement','Armor Reinforcement',59294,0),(34,'Active Shield Tanking','Active Shield Tanking',59295,0),(35,'Passive Shield Tanking','Passive Shield Tanking',59296,0),(36,'Shield Reinforcement','Shield Reinforcement',59297,0),(37,'Hull Tanking','Hull Tanking',59298,0),(38,'Logistics Chief','Logistics Chief',59299,0),(39,'Turret Control','Turret Control',59300,0),(40,'Frigate Energy Turrets','Frigate Energy Turrets',59301,0),(41,'Frigate Advanced Pulse Turrets','Frigate Advanced Pulse Turrets',59302,0),(42,'Frigate Advanced Beam Turrets','Frigate Advanced Beam Turrets',59303,0),(43,'Cruiser Energy Turrets','Cruiser Energy Turrets',59304,0),(44,'Cruiser Advanced Pulse Turrets','Cruiser Advanced Pulse Turrets',59305,0),(45,'Cruiser Advanced Beam Turrets','Cruiser Advanced Beam Turrets',59306,0),(46,'Battleship Energy Turrets','Battleship Energy Turrets',59307,0),(47,'Battleship Advanced Pulse Turrets','Battleship Advanced Pulse Turrets',59308,0),(48,'Battleship Advanced Beam Turrets','Battleship Advanced Beam Turrets',59309,0),(49,'Frigate Hybrid Turrets','Frigate Hybrid Turrets',59310,0),(50,'Frigate Advanced Blaster Turrets','Frigate Advanced Blaster Turrets',59311,0),(51,'Frigate Advanced Rail Turrets','Frigate Advanced Rail Turrets',59312,0),(52,'Cruiser Hybrid Turrets','Cruiser Hybrid Turrets',59400,0),(53,'Cruiser Advanced Blaster Turrets','Cruiser Advanced Blaster Turrets',59313,0),(54,'Cruiser Advanced Rail Turrets','Cruiser Advanced Rail Turrets',59314,0),(55,'Battleship Hybrid Turrets','Battleship Hybrid Turrets',59315,0),(56,'Battleship Advanced Blaster Turrets','Battleship Advanced Blaster Turrets',59316,0),(57,'Battleship Advanced Rail Turrets','Battleship Advanced Rail Turrets',59317,0),(58,'Frigate Projectile Turrets','Frigate Projectile Turrets',59318,0),(59,'Frigate Advanced Autocannon Turrets','Frigate Advanced Autocannon Turrets',59319,0),(60,'Frigate Advanced Artillery Turrets','Frigate Advanced Artillery Turrets',59320,0),(61,'Cruiser Projectile Turrets','Cruiser Projectile Turrets',59321,0),(62,'Cruiser Advanced Autocannon Turrets','Cruiser Advanced Autocannon Turrets',59322,0),(63,'Cruiser Advanced Artillery Turrets','Cruiser Advanced Artillery Turrets',59323,0),(64,'Battleship Projectile Turrets','Battleship Projectile Turrets',59324,0),(65,'Battleship Advanced Autocannon Turrets','Battleship Advanced Autocannon Turrets',59325,0),(66,'Battleship Advanced Artillery Turrets','Battleship Advanced Artillery Turrets',59326,0),(67,'Missile Control','Missile Control',59327,0),(68,'Frigate Launcher Control','Frigate Launcher Control',59328,0),(69,'Frigate Advanced Standard Launchers','Frigate Advanced Standard Launchers',59329,0),(70,'Frigate Advanced Rocket Launchers','Frigate Advanced Rocket Launchers',59330,0),(71,'Cruiser Launcher Control','Cruiser Launcher Control',59331,0),(72,'Cruiser Advanced Heavy Launchers','Cruiser Advanced Heavy Launchers',59332,0),(73,'Cruiser Advanced Heavy Assault Launchers','Cruiser Advanced Heavy Assault Launchers',59333,0),(74,'Battleship Launcher Control','Battleship Launcher Control',59334,0),(75,'Battleship Advanced Cruise Launchers','Battleship Advanced Cruise Launchers',59335,0),(76,'Battleship Advanced Siege Launchers','Battleship Advanced Siege Launchers',59336,0),(77,'Drone Control','Drone Control',59337,0),(78,'Combat Drone Control','Combat Drone Control',59338,0),(79,'Heavy Drone Control','Heavy Drone Control',59339,0),(80,'Specialist Drone Operator','Specialist Drone Operator',59340,0),(81,'Elite Drone Operator','Elite Drone Operator',59341,0),(82,'EWAR Operator','EWAR Operator',59342,0),(83,'Cloak Operator','Cloak Operator',59343,0),(84,'Target Painter Operator','Target Painter Operator',59344,0),(85,'ECM Operator','ECM Operator',59345,0),(86,'Sensor Dampener Operator','Sensor Dampener Operator',59346,0),(87,'Tracking Disruptor Operator','Tracking Disruptor Operator',59347,0),(88,'Propulsion Jammer Operator','Propulsion Jammer Operator',59348,0),(89,'Interdiction Maneuvers','Interdiction Maneuvers',59349,0),(90,'High-Velocity Helmsman','High-Velocity Helmsman',59350,0),(91,'Cartographer','Cartographer',59351,0),(92,'Wormhole Generation','Wormhole Generation',59423,0),(93,'Unit Leader','Unit Leader',59352,0),(94,'Tactical Commander','Tactical Commander',59353,0),(95,'Battlespace Technician','Battlespace Technician',59354,0),(96,'Armored Warfare Chief','Armored Warfare Chief',59355,0),(97,'Information Warfare Chief','Information Warfare Chief',59356,0),(98,'Siege Warfare Chief','Siege Warfare Chief',59357,0),(99,'Skirmish Warfare Chief','Skirmish Warfare Chief',59358,0),(100,'Fleet Co-Ordinator','Fleet Co-Ordinator',59359,0),(101,'Harvesting Comptroller','Harvesting Comptroller',59360,0),(102,'Resource Harvester','Resource Harvester',59361,0),(103,'Mercoxit Specialist','Mercoxit Specialist',59362,0),(104,'Industrial Harvesting','Industrial Harvesting',59363,0),(105,'Ice Specialist','Ice Specialist',59364,0),(106,'Automated Mining','Automated Mining',59365,0),(108,'Refinery Foreman','Refinery Foreman',59396,0),(109,'Common Ore Refiner','Common Ore Refiner',59397,0),(110,'Rare Ore Refiner','Rare Ore Refiner',59398,0),(111,'Production Intern','Production Intern',59366,0),(112,'Production Manager','Production Manager',59367,0),(113,'Research Manager','Research Manager',59368,0),(114,'Field Technician','Field Technician',59399,0),(115,'Business Mogul','Business Mogul',59369,0),(116,'Business Tycoon','Business Tycoon',59370,0),(117,'Remote Demolitions','Remote Demolitions',59371,0),(140,'Colony Management','Colony Management',59424,0),(141,'Planetology','Planetology',59425,0);
/*!40000 ALTER TABLE `crtClasses` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:50

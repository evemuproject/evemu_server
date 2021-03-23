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
-- Table structure for table `eveUnits`
--

DROP TABLE IF EXISTS `eveUnits`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `eveUnits` (
  `unitID` tinyint(3) unsigned NOT NULL,
  `unitName` varchar(100) DEFAULT NULL,
  `displayName` varchar(50) DEFAULT NULL,
  `description` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`unitID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `eveUnits`
--

LOCK TABLES `eveUnits` WRITE;
/*!40000 ALTER TABLE `eveUnits` DISABLE KEYS */;
INSERT INTO `eveUnits` VALUES (1,'Length','m','Meter'),(2,'Mass','kg','Kilogram'),(3,'Time','sec','Second'),(4,'Electric Current','A','Ampere'),(5,'Temperature','K','Kelvin'),(6,'Amount Of Substance','mol','Mole'),(7,'Luminous Intensity','cd','Candela'),(8,'Area','m2','Square meter'),(9,'Volume','m3','Cubic meter'),(10,'Speed','m/sec','Meter per second'),(11,'Acceleration','m/sec','Meter per second squared'),(12,'Wave Number','m-1','Reciprocal meter'),(13,'Mass Density','kg/m3','Kilogram per cubic meter'),(14,'Specific Volume','m3/kg','Cubic meter per kilogram'),(15,'Current Density','A/m2','Ampere per square meter'),(16,'Magnetic Field Strength','A/m','Ampere per meter'),(17,'Amount-Of-Substance Concentration','mol/m3','Mole per cubic meter'),(18,'Luminance','cd/m2','Candela per square meter'),(19,'Mass Fraction','kg/kg = 1','Kilogram per kilogram, which may be represented by the number 1'),(101,'Milliseconds','s',NULL),(102,'Millimeters','mm',NULL),(103,'MegaPascals',NULL,NULL),(104,'Multiplier','x','Indicates that the unit is a multiplier.'),(105,'Percentage','%',NULL),(106,'Teraflops','tf',NULL),(107,'MegaWatts','MW',NULL),(108,'Inverse Absolute Percent','%','Used for resistance.\n0.0 = 100% 1.0 = 0%\n'),(109,'Modifier Percent','%','Used for multipliers displayed as %\n1.1 = +10%\n0.9 = -10%'),(111,'Inversed Modifier Percent','%','Used to modify damage resistance. Damage resistance bonus.\n0.1 = 90%\n0.9 = 10%'),(112,'Radians/Second','rad/sec','Rotation speed.'),(113,'Hitpoints','HP',NULL),(114,'capacitor units','GJ','Giga Joule'),(115,'groupID','groupID',NULL),(116,'typeID','typeID',NULL),(117,'Sizeclass','1=small 2=medium 3=l',NULL),(118,'Ore units','Ore units',NULL),(119,'attributeID','attributeID',NULL),(120,'attributePoints','points',NULL),(121,'realPercent','%','Used for real percentages, i.e. the number 5 is 5%'),(122,'Fitting slots',NULL,NULL),(123,'trueTime','sec','Shows seconds directly'),(124,'Modifier Relative Percent','%','Used for relative percentages displayed as %'),(125,'Newton','N',NULL),(126,'Light Year','ly',NULL),(127,'Absolute Percent','%','0.0 = 0% 1.0 = 100%'),(128,'Drone bandwidth','Mbit/sec','Mega bits per second'),(129,'Hours',NULL,'Hours'),(133,'Money','ISK','ISK'),(134,'Logistical Capacity','m3/hour','Bandwidth for PI'),(135,'Astronomical Unit','AU','Used to denote distance, 1AU = The distance from the Earth to the Sun.'),(136,'Slot','Slot','Slot number prefix for various purposes'),(137,'Boolean','1=True 0=False','For displaying boolean flags'),(138,'Units','units','Units of something, for example fuel'),(139,'Bonus','+','Forces a plus sign for positive values'),(140,'Level','Level','For anything which is divided by levels'),(141,'Hardpoints','hardpoints','For various counts to do with turret, launcher and rig hardpoints'),(142,'Sex','1=Male 2=Unisex 3=Female',NULL);
/*!40000 ALTER TABLE `eveUnits` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:54

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
-- Table structure for table `dgmUnits`
--

DROP TABLE IF EXISTS `dgmUnits`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dgmUnits` (
  `unitID` tinyint(3) unsigned NOT NULL,
  `unitName` varchar(100) DEFAULT NULL,
  `displayName` varchar(50) DEFAULT NULL,
  `description` varchar(1000) DEFAULT NULL,
  `displayNameID` mediumint(7) NOT NULL DEFAULT '0',
  `descriptionID` mediumint(7) NOT NULL DEFAULT '0',
  `dataID` int(8) NOT NULL DEFAULT '0',
  PRIMARY KEY (`unitID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dgmUnits`
--

LOCK TABLES `dgmUnits` WRITE;
/*!40000 ALTER TABLE `dgmUnits` DISABLE KEYS */;
INSERT INTO `dgmUnits` VALUES (1,'Length','m','Meter',78005,77965,16545434),(2,'Mass','kg','Kilogram',78006,77966,16545435),(3,'Time','sec','Second',78007,77967,16545436),(4,'Electric Current','A','Ampere',78008,77968,16545437),(5,'Temperature','K','Kelvin',78009,77969,16545438),(6,'Amount Of Substance','mol','Mole',78010,77970,16545439),(7,'Luminous Intensity','cd','Candela',78011,77971,16545440),(8,'Area','m2','Square meter',78012,77972,16545441),(9,'Volume','m3','Cubic meter',78013,77973,16545442),(10,'Speed','m/sec','Meter per second',78014,77974,16545443),(11,'Acceleration','m/sec','Meter per second squared',78015,77975,16545444),(12,'Wave Number','m-1','Reciprocal meter',78016,77976,16545445),(13,'Mass Density','kg/m3','Kilogram per cubic meter',78017,77977,16545446),(14,'Specific Volume','m3/kg','Cubic meter per kilogram',78018,77978,16545447),(15,'Current Density','A/m2','Ampere per square meter',78019,77979,16545448),(16,'Magnetic Field Strength','A/m','Ampere per meter',78020,77980,16545449),(17,'Amount-Of-Substance Concentration','mol/m3','Mole per cubic meter',78021,77981,16545450),(18,'Luminance','cd/m2','Candela per square meter',78022,77982,16545451),(19,'Mass Fraction','kg/kg = 1','Kilogram per kilogram, which may be represented by the number 1',78023,77983,16545452),(101,'Milliseconds','s',NULL,78024,0,16545453),(102,'Millimeters','mm',NULL,78025,0,16545454),(103,'MegaPascals','mPa',NULL,0,0,13353825),(104,'Multiplier','x','Indicates that the unit is a multiplier.',78026,77984,16545455),(105,'Percentage','%',NULL,78027,0,16545456),(106,'Teraflops','tf',NULL,78028,0,16545457),(107,'MegaWatts','MW',NULL,78029,0,16545458),(108,'Inverse Absolute Percent','%','Used for resistance.\n0.0 = 100% 1.0 = 0%\n',78030,77985,16545459),(109,'Modifier Percent','%','Used for multipliers displayed as %\n1.1 = +10%\n0.9 = -10%',78031,77986,16545460),(111,'Inversed Modifier Percent','%','Used to modify damage resistance. Damage resistance bonus.\n0.1 = 90%\n0.9 = 10%',78032,77987,16545461),(112,'Radians/Second','rad/sec','Rotation speed.',78033,77988,16545462),(113,'Hitpoints','HP',NULL,78034,0,16545463),(114,'capacitor units','GJ','Giga Joule',78035,77989,16545464),(115,'groupID','groupID',NULL,78036,0,16545465),(116,'typeID','typeID',NULL,78037,0,16545466),(117,'Sizeclass','1=small 2=medium 3=l',NULL,78038,0,16545467),(118,'Ore units','Ore units',NULL,78039,0,16545468),(119,'attributeID','attributeID',NULL,78040,0,16545469),(120,'attributePoints','points',NULL,78041,0,16545470),(121,'realPercent','%','Used for real percentages, i.e. the number 5 is 5%',78042,77990,16545471),(122,'Fitting slots',NULL,NULL,0,0,13353933),(123,'trueTime','sec','Shows seconds directly',78043,77991,16545472),(124,'Modifier Relative Percent','%','Used for relative percentages displayed as %',78044,77992,16545473),(125,'Newton','N',NULL,78045,0,16545474),(126,'Light Year','ly',NULL,78046,0,16545475),(127,'Absolute Percent','%','0.0 = 0% 1.0 = 100%',78047,77993,16545476),(128,'Drone bandwidth','Mbit/sec','Mega bits per second',78048,77994,16545477),(129,'Hours',NULL,'Hours',0,77995,16545488),(133,'Money','ISK','ISK',78049,77996,16545478),(134,'Logistical Capacity','m3/hour','Bandwidth for PI',78050,77997,16545479),(135,'Astronomical Unit','AU','Used to denote distance, 1AU = The distance from the Earth to the Sun.',78051,77998,16545480),(136,'Slot','Slot','Slot number prefix for various purposes',78052,77999,16545481),(137,'Boolean','1=True 0=False','For displaying boolean flags',78053,78000,16545482),(138,'Units','units','Units of something, for example fuel',78054,78001,16545483),(139,'Bonus','+','Forces a plus sign for positive values',78055,78002,16545484),(140,'Level','Level','For anything which is divided by levels',78056,78003,16545485),(141,'Hardpoints','hardpoints','For various counts to do with turret, launcher and rig hardpoints',78057,78004,16545486),(142,'Sex','1=Male 2=Unisex 3=Female',NULL,78058,0,16545487);
/*!40000 ALTER TABLE `dgmUnits` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:52

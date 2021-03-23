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
-- Table structure for table `ramInstallationTypeDefaultContents`
--

DROP TABLE IF EXISTS `ramInstallationTypeDefaultContents`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ramInstallationTypeDefaultContents` (
  `installationTypeID` int(11) NOT NULL DEFAULT '0',
  `assemblyLineTypeID` int(11) NOT NULL DEFAULT '0',
  `UIGroupingID` int(11) NOT NULL DEFAULT '0',
  `quantity` int(11) NOT NULL DEFAULT '0',
  `costInstall` float NOT NULL DEFAULT '0',
  `costPerHour` float NOT NULL DEFAULT '0',
  `restrictionMask` int(11) NOT NULL DEFAULT '0',
  `discountPerGoodStandingPoint` float NOT NULL DEFAULT '0',
  `surchargePerBadStandingPoint` float NOT NULL DEFAULT '0',
  `minimumStanding` float NOT NULL DEFAULT '0',
  `minimumCharSecurity` float NOT NULL DEFAULT '0',
  `minimumCorpSecurity` float NOT NULL DEFAULT '0',
  `maximumCharSecurity` float NOT NULL DEFAULT '0',
  `maximumCorpSecurity` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`installationTypeID`),
  KEY `assemblyLineTypeID` (`assemblyLineTypeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ramInstallationTypeDefaultContents`
--

LOCK TABLES `ramInstallationTypeDefaultContents` WRITE;
/*!40000 ALTER TABLE `ramInstallationTypeDefaultContents` DISABLE KEYS */;
/*!40000 ALTER TABLE `ramInstallationTypeDefaultContents` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:51

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
-- Table structure for table `agtOffers`
--

DROP TABLE IF EXISTS `agtOffers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `agtOffers` (
  `offerID` int(10) NOT NULL AUTO_INCREMENT,
  `agentID` int(10) NOT NULL DEFAULT '0',
  `characterID` int(10) NOT NULL DEFAULT '0',
  `missionID` int(10) NOT NULL DEFAULT '0',
  `stateID` tinyint(1) NOT NULL DEFAULT '0',
  `expiryTime` bigint(20) NOT NULL DEFAULT '0',
  `rewardLP` int(10) NOT NULL DEFAULT '0',
  `rewardISK` int(10) NOT NULL DEFAULT '0',
  `rewardItemID` int(10) NOT NULL DEFAULT '0',
  `rewardItemQty` smallint(6) NOT NULL DEFAULT '0',
  `originID` int(10) NOT NULL DEFAULT '0',
  `originOwnerID` int(10) NOT NULL DEFAULT '0',
  `originSystemID` int(10) NOT NULL DEFAULT '0',
  `destinationID` int(10) NOT NULL DEFAULT '0',
  `destinationTypeID` int(10) NOT NULL DEFAULT '0',
  `destinationOwnerID` int(10) NOT NULL DEFAULT '0',
  `destinationSystemID` int(10) NOT NULL DEFAULT '0',
  `dungeonLocationID` int(10) NOT NULL DEFAULT '0',
  `dungeonSolarSystemID` int(10) NOT NULL DEFAULT '0',
  `acceptFee` float NOT NULL DEFAULT '0',
  `courierTypeID` int(5) NOT NULL DEFAULT '0',
  `courierAmount` smallint(6) NOT NULL DEFAULT '0',
  `courierVolume` float NOT NULL DEFAULT '0.1',
  `dateIssued` bigint(20) unsigned NOT NULL DEFAULT '0',
  `dateAccepted` bigint(20) unsigned NOT NULL DEFAULT '0',
  `dateCompleted` bigint(20) unsigned NOT NULL DEFAULT '0',
  `important` bit(1) NOT NULL DEFAULT b'0',
  `name` text NOT NULL,
  `remoteCompletable` bit(1) NOT NULL DEFAULT b'0',
  `remoteOfferable` bit(1) NOT NULL DEFAULT b'0',
  `typeID` smallint(6) NOT NULL DEFAULT '0',
  `bonusISK` int(10) NOT NULL DEFAULT '0',
  `bonusTime` bigint(20) NOT NULL DEFAULT '0',
  `briefingID` int(11) NOT NULL DEFAULT '0',
  `storyline` bit(1) NOT NULL DEFAULT b'0',
  PRIMARY KEY (`offerID`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8 COMMENT='char missions - current offers and history';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `agtOffers`
--

LOCK TABLES `agtOffers` WRITE;
/*!40000 ALTER TABLE `agtOffers` DISABLE KEYS */;

/*!40000 ALTER TABLE `agtOffers` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:45

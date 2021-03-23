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
-- Table structure for table `chrCharacters`
--

DROP TABLE IF EXISTS `chrCharacters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrCharacters` (
  `characterID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `accountID` int(10) unsigned DEFAULT NULL,
  `characterName` text NOT NULL,
  `title` text NOT NULL,
  `description` text NOT NULL,
  `typeID` int(6) NOT NULL DEFAULT '0',
  `flag` smallint(3) NOT NULL DEFAULT '0',
  `bounty` double NOT NULL DEFAULT '0',
  `balance` double NOT NULL DEFAULT '0',
  `aurBalance` double NOT NULL DEFAULT '0',
  `securityRating` float NOT NULL DEFAULT '0',
  `locationID` int(10) NOT NULL DEFAULT '0',
  `petitionMessage` text NOT NULL,
  `logonDateTime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `logoffDateTime` bigint(20) NOT NULL DEFAULT '0',
  `logonMinutes` int(10) unsigned NOT NULL DEFAULT '0',
  `skillPoints` BIGINT(20) NOT NULL DEFAULT '0',
  `skillQueueEndTime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `corporationID` int(10) unsigned NOT NULL DEFAULT '0',
  `baseID` int(10) NOT NULL DEFAULT '0',
  `corpAccountKey` smallint(4) NOT NULL DEFAULT '0',
  `corpRole` bigint(20) unsigned NOT NULL DEFAULT '0',
  `rolesAtAll` bigint(20) unsigned NOT NULL DEFAULT '0',
  `rolesAtHQ` bigint(20) unsigned NOT NULL DEFAULT '0',
  `rolesAtBase` bigint(20) unsigned NOT NULL DEFAULT '0',
  `rolesAtOther` bigint(20) unsigned NOT NULL DEFAULT '0',
  `grantableRoles` bigint(20) NOT NULL DEFAULT '0',
  `grantableRolesAtHQ` bigint(20) NOT NULL DEFAULT '0',
  `grantableRolesAtBase` bigint(20) NOT NULL DEFAULT '0',
  `grantableRolesAtOther` bigint(20) NOT NULL DEFAULT '0',
  `titleMask` bigint(20) NOT NULL DEFAULT '0',
  `blockRoles` bit(1) NOT NULL DEFAULT b'0',
  `startDateTime` bigint(20) NOT NULL DEFAULT '0',
  `createDateTime` bigint(20) NOT NULL DEFAULT '0',
  `ancestryID` int(10) unsigned NOT NULL DEFAULT '0',
  `bloodlineID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `raceID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `careerID` int(10) unsigned NOT NULL DEFAULT '0',
  `schoolID` int(10) unsigned NOT NULL DEFAULT '0',
  `careerSpecialityID` int(10) unsigned NOT NULL DEFAULT '0',
  `gender` tinyint(1) NOT NULL DEFAULT '0',
  `stationID` int(10) unsigned NOT NULL DEFAULT '0',
  `solarSystemID` int(10) unsigned NOT NULL DEFAULT '0',
  `constellationID` int(10) unsigned NOT NULL DEFAULT '0',
  `regionID` int(10) unsigned NOT NULL DEFAULT '0',
  `online` tinyint(1) NOT NULL DEFAULT '0',
  `freeRespecs` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `lastRespecDateTime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `nextRespecDateTime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `deletePrepareDateTime` bigint(20) unsigned DEFAULT '0',
  `shipID` int(10) unsigned NOT NULL DEFAULT '0',
  `capsuleID` int(10) NOT NULL DEFAULT '0',
  `age` int(10) NOT NULL DEFAULT '0',
  `paperDollState` tinyint(2) NOT NULL DEFAULT '0',
  PRIMARY KEY (`characterID`),
  KEY `FK_CHARACTER__ACCOUNTS` (`accountID`),
  KEY `FK_CHARACTER__CHRANCESTRIES` (`ancestryID`),
  KEY `FK_CHARACTER__CHRCAREERS` (`careerID`),
  KEY `FK_CHARACTER__CHRCAREERSPECIALITIES` (`careerSpecialityID`),
  KEY `FK_CHARACTER__CHRSCHOOLS` (`schoolID`),
  KEY `characterID` (`characterID`,`accountID`)
) ENGINE=InnoDB AUTO_INCREMENT=90000000 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrCharacters`
--

LOCK TABLES `chrCharacters` WRITE;
/*!40000 ALTER TABLE `chrCharacters` DISABLE KEYS */;
/*!40000 ALTER TABLE `chrCharacters` ENABLE KEYS */;
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

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
-- Table structure for table `crpVoteItems`
--

DROP TABLE IF EXISTS `crpVoteItems`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crpVoteItems` (
  `voteCaseID` int(11) NOT NULL AUTO_INCREMENT,
  `corporationID` int(10) unsigned NOT NULL,
  `voteType` int(10) unsigned NOT NULL DEFAULT '0',
  `voteCaseText` varchar(50) NOT NULL DEFAULT 'No Label',
  `description` varchar(150) NOT NULL DEFAULT 'No Description',
  `inEffect` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `status` tinyint(2) NOT NULL DEFAULT '2',
  `startDateTime` bigint(20) NOT NULL,
  `endDateTime` bigint(20) NOT NULL DEFAULT '0',
  `actedUpon` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `timeActedUpon` bigint(20) NOT NULL DEFAULT '0',
  `rescended` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `timeRescended` bigint(20) NOT NULL DEFAULT '0',
  `votesMade` smallint(5) NOT NULL DEFAULT '0',
  `votesProxied` smallint(5) NOT NULL DEFAULT '0',
  PRIMARY KEY (`voteCaseID`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8 COMMENT='GetVoteCasesByCorporation';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crpVoteItems`
--

LOCK TABLES `crpVoteItems` WRITE;
/*!40000 ALTER TABLE `crpVoteItems` DISABLE KEYS */;
/*!40000 ALTER TABLE `crpVoteItems` ENABLE KEYS */;
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

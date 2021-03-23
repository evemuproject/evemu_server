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
-- Table structure for table `jnlCorporations`
--

DROP TABLE IF EXISTS `jnlCorporations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jnlCorporations` (
  `transactionID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ownerID` int(10) unsigned NOT NULL DEFAULT '0',
  `entryTypeID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `accountKey` smallint(5) unsigned NOT NULL DEFAULT '0',
  `transactionDate` bigint(20) DEFAULT NULL,
  `ownerID1` int(10) unsigned NOT NULL DEFAULT '0',
  `ownerID2` int(10) unsigned NOT NULL DEFAULT '0',
  `referenceID` int(10) unsigned NOT NULL DEFAULT '0',
  `currency` tinyint(1) NOT NULL DEFAULT '1',
  `amount` double NOT NULL DEFAULT '0',
  `balance` double NOT NULL DEFAULT '0',
  `description` text,
  PRIMARY KEY (`transactionID`),
  KEY `ownerID` (`ownerID`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8 COMMENT='Corporation Journal Data';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jnlCorporations`
--

LOCK TABLES `jnlCorporations` WRITE;
/*!40000 ALTER TABLE `jnlCorporations` DISABLE KEYS */;
/*!40000 ALTER TABLE `jnlCorporations` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:55

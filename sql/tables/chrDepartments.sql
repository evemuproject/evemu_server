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
-- Table structure for table `chrDepartments`
--

DROP TABLE IF EXISTS `chrDepartments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrDepartments` (
  `schoolID` int(10) unsigned NOT NULL DEFAULT '0',
  `departmentID` int(10) unsigned NOT NULL DEFAULT '0',
  `departmentName` varchar(100) NOT NULL DEFAULT '',
  `description` mediumtext NOT NULL,
  `skillTypeID1` int(10) unsigned NOT NULL DEFAULT '0',
  `skillTypeID2` int(10) unsigned NOT NULL DEFAULT '0',
  `skillTypeID3` int(10) unsigned NOT NULL DEFAULT '0',
  `graphicID` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`departmentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrDepartments`
--

LOCK TABLES `chrDepartments` WRITE;
/*!40000 ALTER TABLE `chrDepartments` DISABLE KEYS */;
INSERT INTO `chrDepartments` VALUES (11,1,'Gunnery','(Buffer)',3429,3300,3426,1432),(11,2,'Operations','(Buffer)',3331,3348,3375,1433),(12,3,'Science','(Buffer)',3402,3377,3403,1434),(12,4,'Business','Might makes right and in this day and age money is where the might lies. Acute businessmen abound and the only way to beat them is at their own game. Once you understand what drives the market you\'re halfway home to earning your first million.',3443,3376,3355,1435),(13,5,'Engineering','(Buffer)',3413,3426,3402,1436),(13,6,'Industry','(Buffer)',3380,3378,3385,1437),(14,7,'Gunnery','(Buffer)',3300,3426,3429,1432),(14,8,'Operations','(Buffer)',3329,3348,3327,1433),(15,9,'Science','(Buffer)',3402,3377,3403,1434),(15,10,'Business','Might makes right and in this day and age money is where the might lies. Acute businessmen abound and the only way to beat them is at their own game. Once you understand what drives the market you\'re halfway home to earning your first million.',3443,3376,3355,1435),(16,11,'Engineering','(Buffer)',3413,3378,3402,1436),(16,12,'Industry','(Buffer)',3380,3392,3386,1437),(17,13,'Gunnery','(Buffer)',3300,3429,3426,1432),(17,14,'Operations','(Buffer)',3330,3348,3375,1433),(18,15,'Science','(Buffer)',3402,3377,3403,1434),(18,16,'Business','Might makes right and in this day and age money is where the might lies. Acute businessmen abound and the only way to beat them is at their own game. Once you understand what drives the market you\'re halfway home to earning your first million.',3443,3355,3376,1435),(19,17,'Engineering','(Buffer)',3413,3402,3426,1436),(19,18,'Industry','(Buffer)',3386,3392,3380,1437),(20,19,'Gunnery','(Buffer)',3300,3429,3426,1432),(20,20,'Operations','(Buffer)',3328,3348,3375,1433),(21,21,'Science','(Buffer)',3402,3403,3377,1434),(21,22,'Business','Might makes right and in this day and age money is where the might lies. Acute businessmen abound and the only way to beat them is at their own game. Once you understand what drives the market you are halfway home to earning your first million.',3443,3376,3355,1435),(22,23,'Engineering','(Buffer)',3413,3402,3426,1436),(22,24,'Industry','(Buffer)',3380,3392,3386,1437),(23,25,'Business','Might makes right and in this day and age money is where the might lies. Acute businessmen abound and the only way to beat them is at their own game. Once you understand what drives the market you\'re halfway home to earning your first million.',3443,3355,3376,1435),(23,26,'Science','(Buffer)',3377,3402,3403,1434),(24,27,'Engineering','(Buffer)',3413,3426,3402,1436),(24,28,'Industry','(Buffer)',3380,3385,3378,1437),(25,29,'Gunnery','(Buffer)',3300,3429,3426,1432),(25,30,'Operations','(Buffer)',3755,3348,3375,1433);
/*!40000 ALTER TABLE `chrDepartments` ENABLE KEYS */;
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

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
-- Table structure for table `actKeyTypes`
--

DROP TABLE IF EXISTS `actKeyTypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `actKeyTypes` (
  `keyID` int(10) unsigned NOT NULL DEFAULT '0',
  `keyType` varchar(100) NOT NULL DEFAULT '',
  `keyName` varchar(100) NOT NULL DEFAULT '',
  `keyNameID` int(11) NOT NULL DEFAULT '0',
  `description` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`keyID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `actKeyTypes`
--

LOCK TABLES `actKeyTypes` WRITE;
/*!40000 ALTER TABLE `actKeyTypes` DISABLE KEYS */;
INSERT INTO `actKeyTypes` VALUES (1000,'A','cash',59917,''),(1001,'A','cash2',59918,''),(1002,'A','cash3',59919,''),(1003,'A','cash4',59920,''),(1004,'A','cash5',59921,''),(1005,'A','cash6',59922,''),(1006,'A','cash7',59923,''),(1100,'A','property',59924,''),(1200,'A','aurum',59925,''),(1201,'A','aurum2',59926,''),(1202,'A','aurum3',59927,''),(1203,'A','aurum4',59928,''),(1204,'A','aurum5',59929,''),(1205,'A','aurum6',59930,''),(1206,'A','aurum7',59931,''),(1500,'A','escrow',59932,''),(1800,'A','receivables',59933,''),(2000,'L','payables',59934,''),(2010,'L','gold',59935,''),(2900,'L','equity',59936,''),(3000,'R','sales',59937,''),(4000,'C','purchases',59938,'');
/*!40000 ALTER TABLE `actKeyTypes` ENABLE KEYS */;
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

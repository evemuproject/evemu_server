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
-- Table structure for table `crpNPCDivisions`
--

DROP TABLE IF EXISTS `crpNPCDivisions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crpNPCDivisions` (
  `divisionID` tinyint(3) unsigned NOT NULL,
  `divisionName` varchar(100) DEFAULT NULL,
  `divisionNameID` int(10) DEFAULT NULL,
  `description` varchar(1000) DEFAULT NULL,
  `leaderType` varchar(100) DEFAULT NULL,
  `leaderTypeID` int(10) DEFAULT NULL,
  PRIMARY KEY (`divisionID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crpNPCDivisions`
--

LOCK TABLES `crpNPCDivisions` WRITE;
/*!40000 ALTER TABLE `crpNPCDivisions` DISABLE KEYS */;
INSERT INTO `crpNPCDivisions` VALUES (1,'Accounting',60092,'','CFO',60068),(2,'Administration',60093,'','CFO',60068),(3,'Advisory',60094,'','Chief Advisor',60070),(4,'Archives',60095,'','Chief Archivist',60071),(5,'Astrosurveying',60096,'','Survey Manager',60072),(6,'Command',60097,'','COO',60073),(7,'Distribution',60098,'','Distribution Manager',60074),(8,'Financial',60099,'','CFO',60068),(9,'Intelligence',60100,'','Chief Operative',60076),(10,'Internal Security',60101,'','Commander',60077),(11,'Legal',60102,'','Principal Clerk',60078),(12,'Manufacturing',60103,'','Assembly Manager',60079),(13,'Marketing',60104,'','Market Manager',60080),(14,'Mining',60105,'','Mining Coordinator',60081),(15,'Personnel',60106,'','Chief of Staff',60082),(16,'Production',60107,'','Production Manager',60083),(17,'Public Relations',60108,'','Chief Coordinator',60084),(18,'R&D',60109,'','Chief Researcher',60085),(19,'Security',60110,'','Commander',60077),(20,'Storage',60111,'','Storage Facilitator',60087),(21,'Surveillance',60112,'','Chief Scout',60088),(22,'Distribution',60113,'New distribution division','Distribution Manager',60074),(23,'Mining',60114,'New mining division','Mining Coordinator',60090),(24,'Security',60115,'New security division','Commander',60086);
/*!40000 ALTER TABLE `crpNPCDivisions` ENABLE KEYS */;
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

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
-- Table structure for table `crpRoleGroups`
--

DROP TABLE IF EXISTS `crpRoleGroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crpRoleGroups` (
  `roleGroupID` tinyint(2) NOT NULL,
  `roleGroupName` varchar(130) COLLATE utf8_unicode_ci NOT NULL,
  `roleMask` bigint(20) NOT NULL,
  `appliesTo` varchar(130) COLLATE utf8_unicode_ci NOT NULL,
  `appliesToGrantable` varchar(130) COLLATE utf8_unicode_ci NOT NULL,
  `isLocational` bit(1) NOT NULL DEFAULT b'0',
  `isDivisional` bit(1) NOT NULL DEFAULT b'0',
  `roleGroupNameID` mediumint(6) NOT NULL,
  PRIMARY KEY (`roleGroupID`),
  UNIQUE KEY `roleGroupID` (`roleGroupID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crpRoleGroups`
--

LOCK TABLES `crpRoleGroups` WRITE;
/*!40000 ALTER TABLE `crpRoleGroups` DISABLE KEYS */;
INSERT INTO `crpRoleGroups` VALUES (1,'General',1130405722673123713,'roles','grantableRoles','\0','\0',60117),(2,'Station Service',21955048183434752,'roles','grantableRoles','\0','\0',60118),(3,'Accounting (Divisional)',2181709168640,'roles','grantableRoles','\0','',60119),(4,'Hangar Access (Headquarters)',134209536,'rolesAtHQ','grantableRolesAtHQ','','',60120),(5,'Container Access (Headquarters)',558551906910208,'rolesAtHQ','grantableRolesAtHQ','','',60121),(6,'Hangar Access (Based at)',134209536,'rolesAtBase','grantableRolesAtBase','','',60122),(7,'Container Access (Based at)',558551906910208,'rolesAtBase','grantableRolesAtBase','','',60123),(8,'Hangar Access (Other)',134209536,'rolesAtOther','grantableRolesAtOther','','',60124),(9,'Container Access (Other)',558551906910208,'rolesAtOther','grantableRolesAtOther','','',60125);
/*!40000 ALTER TABLE `crpRoleGroups` ENABLE KEYS */;
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

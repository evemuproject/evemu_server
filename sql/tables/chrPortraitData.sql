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
-- Table structure for table `chrPortraitData`
--

DROP TABLE IF EXISTS `chrPortraitData`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrPortraitData` (
  `charID` int(10) NOT NULL DEFAULT '0',
  `backgroundID` int(10) NOT NULL DEFAULT '0',
  `lightID` int(10) NOT NULL DEFAULT '0',
  `lightColorID` int(10) NOT NULL DEFAULT '0',
  `cameraX` float NOT NULL DEFAULT '0',
  `cameraY` float NOT NULL DEFAULT '0',
  `cameraZ` float NOT NULL DEFAULT '0',
  `cameraPoiX` float NOT NULL DEFAULT '0',
  `cameraPoiY` float NOT NULL DEFAULT '0',
  `cameraPoiZ` float NOT NULL DEFAULT '0',
  `headLookTargetX` float NOT NULL DEFAULT '0',
  `headLookTargetY` float NOT NULL DEFAULT '0',
  `headLookTargetZ` float NOT NULL DEFAULT '0',
  `lightIntensity` float NOT NULL DEFAULT '0',
  `headTilt` float NOT NULL DEFAULT '0',
  `orientChar` float NOT NULL DEFAULT '0',
  `browLeftCurl` float NOT NULL DEFAULT '0',
  `browLeftTighten` float NOT NULL DEFAULT '0',
  `browLeftUpDown` float NOT NULL DEFAULT '0',
  `browRightCurl` float NOT NULL DEFAULT '0',
  `browRightTighten` float NOT NULL DEFAULT '0',
  `browRightUpDown` float NOT NULL DEFAULT '0',
  `eyeClose` float NOT NULL DEFAULT '0',
  `eyesLookVertical` float NOT NULL DEFAULT '0',
  `eyesLookHorizontal` float NOT NULL DEFAULT '0',
  `squintLeft` float NOT NULL DEFAULT '0',
  `squintRight` float NOT NULL DEFAULT '0',
  `jawSideways` float NOT NULL DEFAULT '0',
  `jawUp` float NOT NULL DEFAULT '0',
  `puckerLips` float NOT NULL DEFAULT '0',
  `frownLeft` float NOT NULL DEFAULT '0',
  `frownRight` float NOT NULL DEFAULT '0',
  `smileLeft` float NOT NULL DEFAULT '0',
  `smileRight` float NOT NULL DEFAULT '0',
  `cameraFieldOfView` float NOT NULL DEFAULT '0',
  `portraitPoseNumber` float NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Portrait Data for Characters';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrPortraitData`
--

LOCK TABLES `chrPortraitData` WRITE;
/*!40000 ALTER TABLE `chrPortraitData` DISABLE KEYS */;
/*!40000 ALTER TABLE `chrPortraitData` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:49

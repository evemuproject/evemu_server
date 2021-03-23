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
-- Table structure for table `intro`
--

DROP TABLE IF EXISTS `intro`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `intro` (
  `langID` varchar(2) NOT NULL,
  `textgroup` int(10) unsigned NOT NULL,
  `textLabel` varchar(10) NOT NULL,
  `text` text NOT NULL,
  KEY `textLabel` (`textLabel`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `intro`
--

LOCK TABLES `intro` WRITE;
/*!40000 ALTER TABLE `intro` DISABLE KEYS */;
INSERT INTO `intro` VALUES ('EN',4,'G_EI_01_01','Earth'),('EN',4,'G_EI_01_02','A world outgrown'),('EN',4,'G_EI_01_03','scarred by war and burdened with the advance of our ancestors'),('EN',4,'G_EI_01_04','compelled the first voyages across space'),('EN',4,'G_EI_01_05','in a desperate quest to colonize other worlds'),('EN',4,'G_EI_02_01','Space.'),('EN',4,'G_EI_02_02','Its timeless boundaries and infinite horizons'),('EN',4,'G_EI_02_03','forged the creation of stargates'),('EN',4,'G_EI_02_04','that could bridge the immense distances between the stars'),('EN',4,'G_EI_03_01','Through mastery of this technology'),('EN',4,'G_EI_03_02','mankind ventured deeper into the cosmos'),('EN',4,'G_EI_03_03','Ruthless corporations rose to power'),('EN',4,'G_EI_03_04','seizing every world within their grasp'),('EN',4,'G_EI_03_05','When the stargates could take them no further'),('EN',4,'G_EI_03_06','they turned against each other'),('EN',4,'G_EI_03_07','igniting conflicts that would last for centuries'),('EN',4,'G_EI_04_01','The battles raged until the historic discovery of a natural wormhole'),('EN',4,'G_EI_04_02','A celestial womb through which civilization would be reborn'),('EN',4,'G_EI_04_03','The first brave pioneers to enter this portal emerged unscathed'),('EN',4,'G_EI_04_04','transported instantly across the universe'),('EN',4,'G_EI_04_05','to a virgin system they called New Eden'),('EN',4,'G_EI_04_06','Millions of colonists soon followed in their wake'),('EN',4,'G_EI_04_07','lured by the vision of paradise'),('EN',4,'G_EI_04_08','through the astral gateway known as EVE'),('EN',4,'G_EI_05_01','Spreading outwards among the stars'),('EN',4,'G_EI_05_02','they embraced EVE with the greatest of expectations'),('EN',4,'G_EI_05_03','the highest of hopes and the boldest of dreams'),('EN',4,'G_EI_05_04','When one day...'),('EN',4,'G_EI_05_05','Nature conspired with fate...'),('EN',4,'G_EI_05_06','to breed the cruelest nightmare of all'),('EN',4,'G_EI_06_01','The wormhole leading to New Eden collapsed'),('EN',4,'G_EI_06_02','severing young colonies from the home worlds which sustained them'),('EN',4,'G_EI_06_03','It was the beginning of a dark age'),('EN',4,'G_EI_06_04','that would erase civilization as it was known to be'),('EN',4,'G_EI_07_01','As the accumulated knowledge of millennia slowly eroded'),('EN',4,'G_EI_07_02','the unfinished worlds of EVE became the graveyards of millions'),('EN',4,'G_EI_07_03','On the few planets that could sustain life'),('EN',4,'G_EI_07_04','the last remnants of our race struggled to adapt and survive'),('EN',4,'G_EI_08_01','In time, society was reborn'),('EN',4,'G_EI_08_02','and the memories of our past transformed into legend and myth'),('EN',4,'G_EI_09_01','The first to emerge from the darkness were the Amarr'),('EN',4,'G_EI_09_02','a monotheistic race fervently committed to their faith'),('EN',4,'G_EI_09_03','They reinvented space flight and soon discovered they were not alone'),('EN',4,'G_EI_10_01','The Amarrians encountered the Minmatar race'),('EN',4,'G_EI_10_02','dismissing them as primitive barbarians destined for a life of slavery'),('EN',4,'G_EI_10_03','Moving quickly to subjugate them'),('EN',4,'G_EI_10_04','they launched a merciless crusade against the Minmatar worlds'),('EN',4,'G_EI_11_01','At the same time, the Gallente race flourished nearby'),('EN',4,'G_EI_11_02','They created the first democratic republic of the new era'),('EN',4,'G_EI_11_03','and established a regional federation of independent states'),('EN',4,'G_EI_12_01','The Caldari emerged as the strongest state among them'),('EN',4,'G_EI_12_02','driven by the relentless pursuit of economic and military might'),('EN',4,'G_EI_12_03','Their nationalist ideals soon clashed with Gallente liberalism'),('EN',4,'G_EI_13_01','Destruction and suffering once again'),('EN',4,'G_EI_13_02','became the defining essence of our civilization'),('EN',4,'G_EI_13_03','Four races... '),('EN',4,'G_EI_13_04','torn apart by two horrific wars'),('EN',4,'G_EI_13_05','When all that remained were the smoldering\nruins'),('EN',4,'G_EI_13_06','of lost cities and shattered lives'),('EN',4,'G_EI_13_07','a universal truce was declared to end the despair'),('EN',4,'G_EI_14_01','For more than a century the races of EVE have coexisted in relative peace'),('EN',4,'G_EI_14_02','Prosperity and the pursuit of wealth govern the mission of mankind'),('EN',4,'G_EI_15_01','We have a destiny to meet...'),('EN',4,'G_EI_15_02','and the courage of our pilots will show us the path'),('EN',4,'G_EI_15_03','On the strength of your wings the fate of empires'),('EN',4,'G_EI_15_04','and the hopes of worlds will be decided'),('EN',4,'G_EI_15_05','Take control of the destiny that is rightfully yours');
/*!40000 ALTER TABLE `intro` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:54

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
-- Table structure for table `chrRaces`
--

DROP TABLE IF EXISTS `chrRaces`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrRaces` (
  `raceID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `raceName` varchar(100) DEFAULT NULL,
  `description` varchar(1000) DEFAULT NULL,
  `iconID` smallint(6) NOT NULL DEFAULT '0',
  `shortDescription` varchar(500) DEFAULT NULL,
  `raceNameID` int(10) NOT NULL DEFAULT '0',
  `descriptionID` int(10) NOT NULL DEFAULT '0',
  `dataID` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`raceID`),
  KEY `iconID` (`iconID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrRaces`
--

LOCK TABLES `chrRaces` WRITE;
/*!40000 ALTER TABLE `chrRaces` DISABLE KEYS */;
INSERT INTO `chrRaces` VALUES (1,'Caldari','Founded on the tenets of patriotism and hard work that carried its ancestors through hardships on an inhospitable homeworld, the Caldari State is today a corporate dictatorship, led by rulers who are determined to see it return to the meritocratic ideals of old. Ruthless and efficient in the boardroom as well as on the battlefield, the Caldari are living emblems of strength, persistence, and dignity.',1439,'The Caldari State is the epitome of civic duty and ruthless efficiency.',59592,59586,16544347),(2,'Minmatar','Once a thriving tribal civilization, the Minmatar were enslaved by the Amarr Empire for more than 700 years until a massive rebellion freed most, but not all, of those held in servitude. The Minmatar people today are resilient, ingenious, and hard-working. Many of them believe that democracy, though it has served them well for a long time, can never restore what was taken from them so long ago. For this reason they have formed a government truly reflective of their tribal roots. They will forever resent the Amarrians, and yearn for the days before the Empire’s accursed ships ever reached their home skies.',1440,'Breaking free of Amarrian subjugation, the Minmatar Republic is a nation of resilient, ingenious, hard-working people who thrive in a tribal culture.',59593,59587,16544348),(4,'Amarr','The Amarr Empire is the largest and oldest of the four empires. Ruled by a mighty God-Emperor, this vast theocratic society is supported by a broad foundation of slave labor. Amarrian citizens tend to be highly educated and fervent individuals, and as a culture Amarr adheres to the basic tenet that what others call slavery is in fact one step on a indentured person’s spiritual path toward fully embracing their faith. Despite several setbacks in recent history, the Empire remains arguably the most stable and militarily powerful nation-state in New Eden',1442,'Amarr is the largest empire in New Eden, solely devoted to God, Emperor, and the spread of their faith.',59594,59588,16544349),(8,'Gallente','Champions of liberty and defenders of the downtrodden, the Gallente play host to the only true democracy in New Eden. Some of the most progressive leaders, scientists, and businessmen of the era have emerged from its diverse peoples. A pioneer of artificial intelligence, the Federation relies heavily on drones and other automated systems. This is not to detract from the skill of their pilots, though: the Gallente Federation is known for producing some of the best and bravest the universe has to offer.',1441,'Championing freedom and liberty across the universe, the Gallente Federation is the only true democracy of New Eden.',59595,59589,16544350),(16,'Jove','The most mysterious and elusive of all the universe\'s peoples, the Jovians number only a fraction of any of their neighbors, but their technological superiority makes them powerful beyond all proportion.',0,'',59590,59585,16544345),(32,'Pirate','',0,'',59591,0,16544346),(64,'Sleepers','',0,'',234419,0,16544351),(128,'ORE','',0,'ORE',277200,277201,52615708);
/*!40000 ALTER TABLE `chrRaces` ENABLE KEYS */;
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

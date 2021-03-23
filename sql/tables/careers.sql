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
-- Table structure for table `careers`
--

DROP TABLE IF EXISTS `careers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `careers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `raceID` tinyint(3) unsigned DEFAULT NULL,
  `careerID` int(11) DEFAULT NULL,
  `careerName` text COLLATE utf8_unicode_ci,
  `description` text COLLATE utf8_unicode_ci,
  `shortDescription` text COLLATE utf8_unicode_ci,
  `graphicID` int(11) DEFAULT NULL,
  `schoolID` tinyint(3) unsigned DEFAULT NULL,
  `iconID` int(11) DEFAULT NULL,
  `dataID` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `careerID` (`careerID`),
  KEY `graphicID` (`graphicID`),
  KEY `schoolID` (`schoolID`),
  KEY `iconID` (`iconID`),
  KEY `dataID` (`dataID`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `careers`
--

LOCK TABLES `careers` WRITE;
/*!40000 ALTER TABLE `careers` DISABLE KEYS */;
INSERT INTO `careers` VALUES (1,1,11,'Military','A career in the military means learning what you need to know about how to dispose of enemy vessels as fast and securely as possible, without them disposing of you. Military academies educate enlist cadets thoroughly in combat related skills.','Focuses mainly on combat training.',3178,17,3178,2397248),(2,1,14,'Business','Business is all about dealing with people, solving problems or finding compromises in quarrels and servicing trade routes. And of course, all in the name of financial success. Business careers can be roughly divided into two categories. One revolves entirely around buying and selling, dealing with business contacts and playing the market with the sole purpose of maximizing the profit margin. The other catergory is all about preparing the pilot to lead a group or a crowd of people, form and run a corporation and to supply leadership.','Focuses mainly on practical studies.',3175,18,3175,2397251),(3,1,17,'Industry','A career in industry is a career that spells not only wealth for those that choose to follow that path, but it also opens the door to potential popularity. In the war torn reaches of space, everyone loves a provider. Serious industrialists need to learn how to harvest precious ore, refine it and either produce something from it or haul it around and sell where prices are high. Eventually, a successful industrialist often ends up with a lot of cash on his hands to spend on some other line of work.','Focuses mainly on technical studies.',3172,19,3172,2519356),(4,2,21,'Military','A career in the military means learning what you need to know about how to dispose of enemy vessels as fast and securely as possible, without them disposing of you. Military academies educate enlist cadets thoroughly in combat related skills.','An up-and-coming military training institution.',3178,14,3178,2397257),(5,2,24,'Business','Business is all about dealing with people, solving problems or finding compromises in quarrels and servicing trade routes. And of course, all in the name of financial success. Business careers can be roughly divided into two categories. One revolves entirely around buying and selling, dealing with business contacts and playing the market with the sole purpose of maximizing the profit margin. The other catergory is all about preparing the pilot to lead a group or a crowd of people, form and run a corporation and to supply leadership.','Founded to help gifted children reach their potential.',3175,16,3175,2397260),(6,2,27,'Industry','A career in industry is a career that spells not only wealth for those that choose to follow that path, but it also opens the door to potential popularity. In the war torn reaches of space, everyone loves a provider. Serious industrialists need to learn how to harvest precious ore, refine it and either produce something from it or haul it around and sell where prices are high. Eventually, a successful industrialist often ends up with a lot of cash on his hands to spend on some other line of work.','A forward-thinking house of higher learning.',3172,15,3172,2519353),(7,4,41,'Military','A career in the military means learning what you need to know about how to dispose of enemy vessels as fast and securely as possible, without them disposing of you. Military academies educate enlist cadets thoroughly in combat related skills.','The Empire\'s breeding grounds for military might.',3178,11,3178,2397266),(8,4,44,'Business','Business is all about dealing with people, solving problems or finding compromises in quarrels and servicing trade routes. And of course, all in the name of financial success. Business careers can be roughly divided into two categories. One revolves entirely around buying and selling, dealing with business contacts and playing the market with the sole purpose of maximizing the profit margin. The other catergory is all about preparing the pilot to lead a group or a crowd of people, form and run a corporation and to supply leadership.','A bastion of liberalism and free thought.',3175,12,3175,2397269),(9,4,47,'Industry','A career in industry is a career that spells not only wealth for those that choose to follow that path, but it also opens the door to potential popularity. In the war torn reaches of space, everyone loves a provider. Serious industrialists need to learn how to harvest precious ore, refine it and either produce something from it or haul it around and sell where prices are high. Eventually, a successful industrialist often ends up with a lot of cash on his hands to spend on some other line of work.','One of the most venerable educational facilities in the universe.',3172,13,3172,2519358),(10,8,81,'Military','A career in the military means learning what you need to know how about to dispose of enemy vessels as fast and securely as possible, without them disposing of you. Military academies educate enlist cadets thoroughly in combat related skills.','An extremely strict but effective military academy.',3178,20,3178,2397275),(11,8,84,'Business','Business is all about dealing with people, solving problems or finding compromises in quarrels and servicing trade routes. And of course, all in the name of financial success. Business careers can be roughly divided into two categories. One revolves entirely around buying and selling, dealing with business contacts and playing the market with the sole purpose of maximizing the profit margin. The other catergory is all about preparing the pilot to lead a group or a crowd of people, form and run a corporation and to supply leadership.','The largest school in the universe.',3175,21,3175,2397278),(12,8,87,'Industry','A career in industry is a career that spells not only wealth for those that choose to follow that path, but it also opens the door to potential popularity. In the war torn reaches of space, everyone loves a provider. Serious industrialists need to learn how to harvest precious ore, refine it and either produce something from it or haul it around and sell where prices are high. Eventually, a successful industrialist often ends up with a lot of cash on his hands to spend on some other line of work.','One of the very best technical schools in the universe.',3172,22,3172,2456343),(13,16,161,'Business','','',3175,23,3175,2397284),(14,16,164,'Industry','','',3172,24,3172,2397287),(15,16,167,'Military','','',3178,25,3178,2397290);
/*!40000 ALTER TABLE `careers` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:46

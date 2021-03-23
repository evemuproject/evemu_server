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
-- Table structure for table `chrAttributes`
--

DROP TABLE IF EXISTS `chrAttributes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chrAttributes` (
  `attributeID` tinyint(3) unsigned NOT NULL,
  `attributeName` varchar(100) DEFAULT NULL,
  `description` varchar(1000) DEFAULT NULL,
  `iconID` smallint(6) DEFAULT NULL,
  `shortDescription` varchar(500) DEFAULT NULL,
  `notes` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`attributeID`),
  KEY `iconID` (`iconID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chrAttributes`
--

LOCK TABLES `chrAttributes` WRITE;
/*!40000 ALTER TABLE `chrAttributes` DISABLE KEYS */;
INSERT INTO `chrAttributes` VALUES (1,'Intelligence','<b>Intelligence is a measure of a pilot\'s capacity for learning, reasoning, and understanding.</b> It is also an aptitude indicator for cognitive abilities such as logical reasoning and abstract thinking. In the EVE universe, pilots with a high intelligence score possess an innate mastery of core academic disciplines such as mathematics and physics.\n\n<b>Skill categories</b> such as <b>Electronics, Engineering, Navigation, and Science all require direct application of these disciplines</b> and build extensively on them throughout the pilot\'s skill advancement, irrespective of career choice. Additionally, advanced starship technologies such as <b>Electronic Warfare, Shield Operation, and Cloaking</b> will require a high Intelligence score to master quickly.\n\nThis attribute is secondary for numerous <b>social and industrial skills</b> as well. ',1380,'A measure of individual capacity for learning, reasoning, abstract thinking, and overall cognitive aptitude.','Intelligence does not increase the chance of achieving success during the application of skills, only how quickly the skills that depend on it are trained.'),(2,'Charisma','<b>Charisma is personal attractiveness or magnetism that promotes individual influence on others</b>. Great leaders across the ages who were able to motivate and inspire great numbers of people are said to have had high charisma attributes. The power of persuasion and the ability to lead are invaluable resources for engaging in social interactions, regardless of career path. In the universe of EVE, this attribute is <b>essential for maintaining positive standings with political entities</b> such as factions, corporations and police forces.\n\nAlthough it influences fewer skills than any other attribute, Charisma is essential for aspiring CEOs, fleet commanders and business tycoons. <b>Skills that require Charisma</b> as a primary attribute <b>include Leadership, Social and Trade</b>.\n\nThe main <b>secondary attribute skill is Corporation Management</b>.',1378,'Personal attractiveness or magnetism that promotes the ability to influence others.','Charisma does not increase the chances of achieving success during the application of skills, only how quickly the skills that depend on it are trained.'),(3,'Perception','<b>Perception measures a pilot\'s ability to assimilate sensory information from the surrounding environment and formulate effective actions in response</b>. Intuitively determining the orientation of objects in three-dimensional space relative to fixed or moving reference points, and measuring object motion characteristics such as vector, speed, and trajectory within this space; both of these are functions of Perception. Assessing the temporo-spatial relationship between two or more objects is a critical component of battlefield tactical awareness, and the speed with which this data can be processed thus determines overall reaction time and effectiveness in combat.\n\n<b>Perception is the primary attribute in the training of Gunnery, Missile Launcher Operation, and Spaceship Command skills</b>.\n\nIt is also a secondary attribute for <b>Spaceship Command, Drones, and Navigation skills</b>.',1382,'A pilot\'s ability to assimilate information from the ship\'s surrounding environment and formulate a response action.','Perception does not increase the chances of achieving success during the application of skills, only how quickly the skills that depend on it are trained.'),(4,'Memory','<b>Memory is the mental capacity to retain and recall facts derived from prior learning experiences and apply them during situational circumstances</b>. The speed with which a pilot can recall and apply data while subject to duress is a critical component</b> of effective reflex development in combat training. In EVE, the memory attribute is a composite measure of both long and short-term memory variants, both of which apply to a broad set of abilities ranging from industrial and scientific disciplines to battlefield tactical awareness.\n\n<b>Memory is a primary attribute for skills such as Corporation Management and Drones</b>.\n\nIt is also a <b>secondary attribute for</b> numerous others, including <b>Engineering, Mechanic, Electronics, and Trade.</b>',1381,'The mental capacity to retain and recall facts derived from prior learning experiences and apply them in situational circumstances.','Memory does not increase the chances of achieving success during the application of skills, only how quickly the skills that depend on it are trained.'),(5,'Willpower','<b>Willpower is resolute control over one\'s own actions, impulses, and behavior.</b> It embodies the capability of focusing on the achievement of personal goals, irrespective of setbacks or adversity. In combat, the ability to concentrate on dynamic battlefield conditions and exercise patience when determining the timing of active defenses or attacks is also a function of willpower. This attribute is the consummate survival gauge: The higher the score, the more likely the pilot will be able to persevere in difficult circumstances.\n\nA crucial component for success in all forms of command, <b>Willpower is a primary attribute for Trade, Leadership, and Advanced Spaceship skills</b>.\n\nIt is also a key <b>secondary attribute for</b> many combat skills, such as <b>Gunnery, Spaceship Command, and Missile Launcher Operation</b>.',1379,'Rigid self-control over personal actions, impulses and behavior. The ability to focus irrespective of setbacks or adversity.','Willpower does not increase the chances of achieving success during the application of skills, only how quickly the skills that depend on it are trained.');
/*!40000 ALTER TABLE `chrAttributes` ENABLE KEYS */;
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

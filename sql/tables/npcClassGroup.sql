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
-- Table structure for table `npcClassGroup`
--

DROP TABLE IF EXISTS `npcClassGroup`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `npcClassGroup` (
  `shipClass` int(11) NOT NULL,
  `groupID` int(11) NOT NULL,
  `factionID` int(11) NOT NULL,
  `groupName` varchar(50) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `npcClassGroup`
--

LOCK TABLES `npcClassGroup` WRITE;
/*!40000 ALTER TABLE `npcClassGroup` DISABLE KEYS */;
INSERT INTO `npcClassGroup` VALUES (1,550,500011,'Asteroid Angel Cartel Frigate'),(2,550,500011,'Asteroid Angel Cartel Advanced Frigate'),(3,575,500011,'Asteroid Angel Cartel Destroyer'),(4,551,500011,'Asteroid Angel Cartel Cruiser'),(5,551,500011,'Asteroid Angel Cartel Advanced Cruiser'),(6,576,500011,'Asteroid Angel Cartel BattleCruiser'),(7,552,500011,'Asteroid Angel Cartel Battleship'),(8,554,500011,'Asteroid Angel Cartel Hauler'),(9,553,500011,'Asteroid Angel Cartel Officer'),(10,789,500011,'Asteroid Angel Cartel Commander Frigate'),(11,794,500011,'Asteroid Angel Cartel Commander Destroyer'),(12,790,500011,'Asteroid Angel Cartel Commander Cruiser'),(13,793,500011,'Asteroid Angel Cartel Commander BattleCruiser'),(14,848,500011,'Asteroid Angel Cartel Commander Battleship'),(15,597,500011,'Deadspace Angel Cartel Frigate'),(16,597,500011,'Deadspace Angel Cartel Advanced Frigate'),(17,596,500011,'Deadspace Angel Cartel Destroyer'),(18,595,500011,'Deadspace Angel Cartel Cruiser'),(19,595,500011,'Deadspace Angel Cartel Advanced Cruiser'),(20,594,500011,'Deadspace Angel Cartel BattleCruiser'),(21,593,500011,'Deadspace Angel Cartel Battleship'),(1,557,500012,'Asteroid Blood Raiders Frigate'),(2,557,500012,'Asteroid Blood Raiders Advanced Frigate'),(3,577,500012,'Asteroid Blood Raiders Destroyer'),(4,555,500012,'Asteroid Blood Raiders Cruiser'),(5,555,500012,'Asteroid Blood Raiders Advanced Cruiser'),(6,578,500012,'Asteroid Blood Raiders BattleCruiser'),(7,556,500012,'Asteroid Blood Raiders Battleship'),(8,558,500012,'Asteroid Blood Raiders Hauler'),(9,559,500012,'Asteroid Blood Raiders Officer'),(10,792,500012,'Asteroid Blood Raiders Commander Frigate'),(11,796,500012,'Asteroid Blood Raiders Commander Destroyer'),(12,791,500012,'Asteroid Blood Raiders Commander Cruiser'),(13,795,500012,'Asteroid Blood Raiders Commander BattleCruiser'),(14,849,500012,'Asteroid Blood Raiders Commander Battleship'),(15,606,500012,'Deadspace Blood Raiders Frigate'),(16,606,500012,'Deadspace Blood Raiders Advanced Frigate'),(17,605,500012,'Deadspace Blood Raiders Destroyer'),(18,604,500012,'Deadspace Blood Raiders Cruiser'),(19,604,500012,'Deadspace Blood Raiders Advanced Cruiser'),(20,602,500012,'Deadspace Blood Raiders BattleCruiser'),(21,603,500012,'Deadspace Blood Raiders Battleship'),(1,562,500010,'Asteroid Guristas Frigate'),(2,562,500010,'Asteroid Guristas Advanced Frigate'),(3,579,500010,'Asteroid Guristas Destroyer'),(4,561,500010,'Asteroid Guristas Cruiser'),(5,561,500010,'Asteroid Guristas Advanced Cruiser'),(6,580,500010,'Asteroid Guristas BattleCruiser'),(7,560,500010,'Asteroid Guristas Battleship'),(8,563,500010,'Asteroid Guristas Hauler'),(9,564,500010,'Asteroid Guristas Officer'),(10,800,500010,'Asteroid Guristas Commander Frigate'),(11,799,500010,'Asteroid Guristas Commander Destroyer'),(12,798,500010,'Asteroid Guristas Commander Cruiser'),(13,797,500010,'Asteroid Guristas Commander BattleCruiser'),(14,850,500010,'Asteroid Guristas Commander Battleship'),(15,615,500010,'Deadspace Guristas Frigate'),(16,615,500010,'Deadspace Guristas Advanced Frigate'),(17,614,500010,'Deadspace Guristas Destroyer'),(18,613,500010,'Deadspace Guristas Cruiser'),(19,613,500010,'Deadspace Guristas Advanced Cruiser'),(20,611,500010,'Deadspace Guristas BattleCruiser'),(21,612,500010,'Deadspace Guristas Battleship'),(1,567,500019,'Asteroid Sansha\'s Nation Frigate'),(2,567,500019,'Asteroid Sansha\'s Nation Advanced Frigate'),(3,581,500019,'Asteroid Sansha\'s Nation Destroyer'),(4,566,500019,'Asteroid Sansha\'s Nation Cruiser'),(5,566,500019,'Asteroid Sansha\'s Nation Advanced Cruiser'),(6,582,500019,'Asteroid Sansha\'s Nation BattleCruiser'),(7,565,500019,'Asteroid Sansha\'s Nation Battleship'),(8,568,500019,'Asteroid Sansha\'s Nation Hauler'),(9,569,500019,'Asteroid Sansha\'s Nation Officer'),(10,810,500019,'Asteroid Sansha\'s Nation Commander Frigate'),(11,809,500019,'Asteroid Sansha\'s Nation Commander Destroyer'),(12,808,500019,'Asteroid Sansha\'s Nation Commander Cruiser'),(13,807,500019,'Asteroid Sansha\'s Nation Commander BattleCruiser'),(14,851,500019,'Asteroid Sansha\'s Nation Commander Battleship'),(15,624,500019,'Deadspace Sansha\'s Nation Frigate'),(16,624,500019,'Deadspace Sansha\'s Nation Advanced Frigate'),(17,623,500019,'Deadspace Sansha\'s Nation Destroyer'),(18,622,500019,'Deadspace Sansha\'s Nation Cruiser'),(19,622,500019,'Deadspace Sansha\'s Nation Advanced Cruiser'),(20,620,500019,'Deadspace Sansha\'s Nation BattleCruiser'),(21,621,500019,'Deadspace Sansha\'s Nation Battleship'),(1,572,500020,'Asteroid Serpentis Frigate'),(2,572,500020,'Asteroid Serpentis Advanced Frigate'),(3,583,500020,'Asteroid Serpentis Destroyer'),(4,571,500020,'Asteroid Serpentis Cruiser'),(5,571,500020,'Asteroid Serpentis Advanced Cruiser'),(6,584,500020,'Asteroid Serpentis BattleCruiser'),(7,570,500020,'Asteroid Serpentis Battleship'),(8,573,500020,'Asteroid Serpentis Hauler'),(9,574,500020,'Asteroid Serpentis Officer'),(10,814,500020,'Asteroid Serpentis Commander Frigate'),(11,813,500020,'Asteroid Serpentis Commander Destroyer'),(12,812,500020,'Asteroid Serpentis Commander Cruiser'),(13,811,500020,'Asteroid Serpentis Commander BattleCruiser'),(14,852,500020,'Asteroid Serpentis Commander Battleship'),(15,633,500020,'Deadspace Serpentis Frigate'),(16,633,500020,'Deadspace Serpentis Advanced Frigate'),(17,632,500020,'Deadspace Serpentis Destroyer'),(18,631,500020,'Deadspace Serpentis Cruiser'),(19,631,500020,'Deadspace Serpentis Advanced Cruiser'),(20,629,500020,'Deadspace Serpentis BattleCruiser'),(21,630,500020,'Deadspace Serpentis Battleship'),(1,759,500022,'Asteroid Rogue Drone Frigate'),(2,759,500022,'Asteroid Rogue Drone Advanced Frigate'),(3,758,500022,'Asteroid Rogue Drone Destroyer'),(4,757,500022,'Asteroid Rogue Drone Cruiser'),(5,757,500022,'Asteroid Rogue Drone Advanced Cruiser'),(6,755,500022,'Asteroid Rogue Drone BattleCruiser'),(7,756,500022,'Asteroid Rogue Drone Battleship'),(8,760,500022,'Asteroid Rogue Drone Hauler'),(9,761,500022,'Asteroid Rogue Drone Swarm'),(10,847,500022,'Asteroid Rogue Drone Commander Frigate'),(11,846,500022,'Asteroid Rogue Drone Commander Destroyer'),(12,845,500022,'Asteroid Rogue Drone Commander Cruiser'),(13,843,500022,'Asteroid Rogue Drone Commander BattleCruiser'),(14,844,500022,'Asteroid Rogue Drone Commander Battleship'),(15,805,500022,'Deadspace Rogue Drone Frigate'),(16,805,500022,'Deadspace Rogue Drone Advanced Frigate'),(17,804,500022,'Deadspace Rogue Drone Destroyer'),(18,803,500022,'Deadspace Rogue Drone Cruiser'),(19,803,500022,'Deadspace Rogue Drone Advanced Cruiser'),(20,801,500022,'Deadspace Rogue Drone BattleCruiser'),(21,802,500022,'Deadspace Rogue Drone Battleship'),(22,806,500022,'Deadspace Rogue Drone Swarm');
/*!40000 ALTER TABLE `npcClassGroup` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:29:47

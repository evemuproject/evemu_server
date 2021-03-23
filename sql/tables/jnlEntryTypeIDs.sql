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
-- Table structure for table `jnlEntryTypeIDs`
--

DROP TABLE IF EXISTS `jnlEntryTypeIDs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jnlEntryTypeIDs` (
  `entryTypeID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `entryTypeName` varchar(100) NOT NULL DEFAULT '',
  `entryTypeNameID` mediumint(6) NOT NULL DEFAULT '0',
  `description` mediumtext NOT NULL,
  PRIMARY KEY (`entryTypeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jnlEntryTypeIDs`
--

LOCK TABLES `jnlEntryTypeIDs` WRITE;
/*!40000 ALTER TABLE `jnlEntryTypeIDs` DISABLE KEYS */;
INSERT INTO `jnlEntryTypeIDs` VALUES (0,'Undefined',59792,''),(1,'Player Trading',59793,''),(2,'Market Transaction',59794,''),(3,'GM Cash Transfer',59795,''),(4,'ATM Withdraw',59796,''),(5,'ATM Deposit',59797,''),(6,'Backward Compatible',59798,''),(7,'Mission Reward',59799,''),(8,'Clone Activation',59800,''),(9,'Inheritance',59801,''),(10,'Player Donation',59802,'Player gave cash to another owner'),(11,'Corporation Payment',59803,'CEO or Accountant transferred cash  from corp. account'),(12,'Docking Fee',59804,''),(13,'Office Rental Fee',59805,''),(14,'Factory Slot Rental Fee',59806,''),(15,'Repair Bill',59807,''),(16,'Bounty',59808,'Player gave cash to someone\'s  bounty pool'),(17,'Bounty Prize',59809,'Player got bounty prize for killing someone'),(18,'Agents_temporary',59810,'TEMP'),(19,'Insurance',59811,''),(20,'Mission Expiration',59812,''),(21,'Mission Completion',59813,''),(22,'Shares',59814,''),(23,'Courier Mission Escrow',59815,''),(24,'Mission Cost',59815,''),(25,'Agent Miscellaneous',59817,'Agent paid you'),(26,'Miscellaneous Payment To Agent',59818,'You paid agent'),(27,'Agent Location Services',59819,'You paid agent to locate somebody'),(28,'Agent Donation',59820,'You donated/bribed the agent'),(29,'Agent Security Services',59821,'You paid agent to clean your rep'),(30,'Agent Mission Collateral Paid',59822,'You gave agent collateral for a mission'),(31,'Agent Mission Collateral Refunded',59823,'The agent returned collateral to you'),(32,'Agents_preward',59824,'The agent gave you this when you accepted the mission'),(33,'Agent Mission Reward',59825,'The agent gave you this as a reward'),(34,'Agent Mission Time Bonus Reward',59826,'The agent gave you this as a special reward for fast mission completion'),(35,'CSPA',59827,'CONCORD Spam Prevention Act'),(36,'CSPAOfflineRefund',59828,'Refunded CSPA charge because the other party was not online'),(37,'Corporation Account Withdrawal',59829,'Withdrawal from corporation account'),(38,'Corporation Dividend Payment',59830,''),(39,'Corporation Registration Fee',59831,''),(40,'Corporation Logo Change Cost',59832,''),(41,'Release Of Impounded Property',59833,'Charge for the receipt of goods from a corporation hangar that is no longer rented'),(42,'Market Escrow',59834,''),(43,'Agent Services Rendered',59835,'For miscellaneous services rendered by the agent'),(44,'Market Fine Paid',59836,''),(45,'Corporation Liquidation',59837,'Funds from the liquidation of a corporation to a shareholder'),(46,'Broker fee',59838,''),(47,'Corporation Bulk Payment',59839,'A payment from a corporation'),(48,'Alliance Registration Fee',59840,''),(49,'War Fee',59841,''),(50,'Alliance Maintainance Fee',59842,''),(51,'Contraband Fine',59843,''),(52,'Clone Transfer',59844,''),(53,'Acceleration Gate Fee',59845,''),(54,'Transaction Tax',59846,'Sales tax paid to the SCC for any transaction'),(55,'Jump Clone Installation Fee',59847,''),(56,'Manufacturing',59848,'Installation and runtime cost for a manufacturing job'),(57,'Researching Technology',59849,'Installation and runtime cost for a technological research job'),(58,'Researching Time Productivity',59850,'Installation and runtime cost for a time productivity research job'),(59,'Researching Material Productivity',59851,'Installation and runtime cost for a material productivity research job'),(60,'Copying',59852,'Installation and runtime cost for a blueprint copying job'),(61,'Duplicating',59853,'Installation and runtime cost for an item duplication job'),(62,'Reverse Engineering',59854,'Installation and runtime cost for a reverse engineering job'),(63,'Reverse Engineering',59854,''),(64,'Contract Auction Bid',59855,''),(65,'Contract Auction Bid Refund',59856,''),(66,'Contract Collateral',59857,''),(67,'Contract Reward Refund',59858,''),(68,'Contract Auction Sold',59859,''),(69,'Contract Reward',59860,''),(70,'Contract Collateral Refund',59861,''),(71,'Contract Collateral Payout',59862,''),(72,'Contract Price',59863,''),(73,'Contract Brokers Fee',59864,''),(74,'Contract Sales Tax',59865,''),(75,'Contract Deposit',59866,''),(76,'Contract Deposit Sales Tax',59867,''),(77,'Contract Auction Bid (corp)',59869,''),(78,'Contract Collateral Deposited (corp)',59870,''),(79,'Contract Price Payment (corp)',59871,''),(80,'Contract Brokers Fee (corp)',59872,''),(81,'Contract Deposit (corp)',59873,''),(82,'Contract Deposit Refund',59874,''),(83,'Contract Reward Deposited',59875,''),(84,'Contract Reward Deposited (corp)',59876,''),(85,'Bounty Prizes',59877,''),(86,'Advertisement Listing Fee',59878,''),(87,'Medal Creation',59879,''),(88,'Medal Issued',59880,''),(90,'DNA Modification Fee',59882,''),(91,'Sovereignty bill',59883,''),(92,'Bounty Prize Corporation Tax',59884,''),(93,'Agent Mission Reward Corporation Tax',59885,''),(94,'Agent Mission Time Bonus Reward Corporation Tax',59886,''),(95,'Upkeep adjustment fee',59887,''),(96,'Planetary Import Tax',59888,''),(97,'Planetary Export Tax',59889,''),(98,'Planetary Construction',59890,''),(99,'Corporate Reward Payout',59891,''),(101,'Bounty Surcharge',59893,''),(102,'Contract Reversal',59894,''),(103,'Corporate Reward Tax',59895,''),(106,'Store Purchase',59898,''),(107,'Store Purchase Refund',59899,''),(108,'PLEX sold for Aurum',59900,''),(10003,'Battle Reward',59903,''),(10004,'New Character Starting Funds',59904,''),(10005,'Corporation Account Withdrawal',59905,''),(10006,'Corporation Account Deposit',59906,''),(10007,'Battle WP Win Reward',59907,''),(10008,'Battle WP Loss Reward',59908,''),(10009,'Battle Win Reward',59909,''),(10010,'Battle Loss Reward',59910,''),(11001,'Modify AUR',59911,''),(11002,'Respec payment',59912,'');
/*!40000 ALTER TABLE `jnlEntryTypeIDs` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:55

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
-- Table structure for table `dunTemplates`
--

DROP TABLE IF EXISTS `dunTemplates`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dunTemplates` (
  `dunTemplateID` int(11) NOT NULL,
  `dunTemplateName` varchar(85) COLLATE utf8_bin NOT NULL,
  `dunEntryID` int(11) NOT NULL DEFAULT '0',
  `dunSpawnID` int(11) NOT NULL DEFAULT '0',
  `dunRoomID` int(11) NOT NULL DEFAULT '0',
  UNIQUE KEY `dunTemplateID_2` (`dunTemplateID`),
  KEY `dunTemplateID` (`dunTemplateID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dunTemplates`
--

LOCK TABLES `dunTemplates` WRITE;
/*!40000 ALTER TABLE `dunTemplates` DISABLE KEYS */;
INSERT INTO `dunTemplates` VALUES (11110,'Mission Space',0,0,1),(21018,'Small Omber Deposit',0,0,7111),(21118,'Small Kernite and Omber Deposit',0,0,7112),(21218,'Small Jaspet, Kernite and Omber Deposit',0,0,7113),(21318,'Small Hemorphite, Jaspet and Kernite Deposit',0,0,7211),(21418,'Small Hedbergite, Hemorphite and Jaspet Deposit',0,0,7212),(21518,'Small Hedbergite and Hemorphite Deposit',0,0,7213),(21028,'Average Omber Deposit',0,0,7121),(21128,'Average Kernite and Omber Deposit',0,0,7122),(21228,'Average Jaspet, Kernite and Omber Deposit',0,0,7123),(21328,'Average Hemorphite, Jaspet and Kernite Deposit',0,0,7221),(21428,'Average Hedbergite, Hemorphite and Jaspet Deposit',0,0,7222),(21528,'Average Hedbergite and Hemorphite Deposit',0,0,7223),(21038,'Large Omber Deposit',0,0,7131),(21138,'Large Kernite and Omber Deposit',0,0,7132),(21238,'Large Jaspet, Kernite and Omber Deposit',0,0,7133),(21338,'Large Hemorphite, Jaspet and Kernite Deposit',0,0,7231),(21438,'Large Hedbergite, Hemorphite and Jaspet Deposit',0,0,7232),(21538,'Large Hedbergite and Hemorphite Deposit',0,0,7233),(22018,'Small Gneiss Deposit',0,0,7214),(22118,'Small Dark Ochre and Gneiss Deposit',0,0,7311),(22218,'Small Crokite, Dark Ochre and Gneiss Deposit',0,0,7312),(22318,'Small Spodumain, Crokite and Dark Ochre Deposit',0,0,7313),(22028,'Average Gneiss Deposit',0,0,7224),(22128,'Average Dark Ochre and Gneiss Deposit',0,0,7321),(22228,'Average Crokite, Dark Ochre and Gneiss Deposit',0,0,7322),(22328,'Average Spodumain, Crokite and Dark Ochre Deposit',0,0,7323),(22038,'Large Gneiss Deposit',0,0,7234),(22138,'Large Dark Ochre and Gneiss Deposit',0,0,7331),(22238,'Large Crokite, Dark Ochre and Gneiss Deposit',0,0,7332),(22338,'Large Spodumain, Crokite and Dark Ochre Deposit',0,0,7333),(23018,'Small Bistot Deposit',0,0,7511),(23118,'Small Arkanor and Bistot Deposit',0,0,7512),(23218,'Small Mercoxit, Arkonor and Bistot Deposit',0,0,7513),(23028,'Average Bistot Deposit',0,0,7521),(23128,'Average Arkanor and Bistot Deposit',0,0,7522),(23228,'Average Mercoxit, Arkonor and Bistot Deposit',0,0,7523),(23038,'Large Bistot Deposit',0,0,7531),(23138,'Large Arkanor and Bistot Deposit',0,0,7532),(23238,'Large Mercoxit, Arkonor and Bistot Deposit',0,0,7533),(23518,'Small Asteroid Cluster',0,0,7110),(23528,'Moderate Asteroid Cluster',0,0,7220),(23538,'Large Asteroid Cluster',0,0,7330),(23548,'Enormous Asteroid Cluster',0,0,7540),(23558,'Colossal Asteroid Cluster',0,0,7750),(21608,'White Glaze Belt',0,0,7066),(21708,'Blue Ice Belt',0,0,7067),(21808,'Glacial Mass Belt',0,0,7068),(21908,'Glare Crust Belt',0,0,7069),(22608,'White Glaze Belt',0,0,7076),(22708,'Blue Ice Belt',0,0,7077),(22808,'Glacial Mass Belt',0,0,7078),(22908,'Glare Crust Belt',0,0,7079),(23608,'Enriched White Glaze Belt',0,0,7086),(23708,'Thick Blue Ice Belt',0,0,7087),(23808,'Smooth Glacial Mass Belt',0,0,7088),(23908,'Pristine Glare Crust Belt',0,0,7089),(31111,'Crumbling Serpentis Antiquated Outpost',0,0,5111),(31211,'Crumbling Serpentis Crystal Quarry',0,0,5211),(31311,'Crumbling Serpentis Explosive Debris',0,0,5311),(31411,'Crumbling Serpentis Abandoned Colony',0,0,5411),(31511,'Crumbling Serpentis Excavation',0,0,5511),(31611,'Crumbling Serpentis Solar Harvesters',0,0,5611),(31711,'Crumbling Serpentis Stone Formation',0,0,5711),(31811,'Crumbling Serpentis Mining Installation',0,0,5811),(32111,'Decayed Serpentis Excavation',0,0,5121),(32211,'Decayed Serpentis Collision Site',0,0,5221),(32311,'Decayed Serpentis Lone Vessel',0,0,5321),(32411,'Decayed Serpentis Mining Installation',0,0,5421),(32511,'Decayed Serpentis Particle Accelerator',0,0,5521),(32611,'Decayed Serpentis Mass Grave',0,0,5621),(32711,'Decayed Serpentis Rock Formations',0,0,5721),(32811,'Decayed Serpentis Quarry',0,0,5821),(33111,'Pristine Serpentis Ship Remnants',0,0,5131),(33211,'Pristine Serpentis Pod Cluster',0,0,5231),(33311,'Pristine Serpentis Dumped Cargo',0,0,5331),(33411,'Pristine Serpentis Ship Graveyard',0,0,5431),(33511,'Pristine Serpentis Battle Remnants',0,0,5531),(33611,'Pristine Serpentis Abandoned Colony',0,0,5631),(33711,'Pristine Serpentis Collision Site',0,0,5731),(33811,'Pristine Serpentis Explosive Debris',0,0,5831),(31121,'Looted Serpentis Collision Site',0,0,4111),(31221,'Looted Serpentis Abandoned Station',0,0,4211),(31321,'Looted Serpentis Lone Vessel',0,0,4311),(31421,'Looted Serpentis Ruined Station',0,0,4411),(31521,'Looted Serpentis Explosive Debris',0,0,4511),(31621,'Looted Serpentis Battle Remnants',0,0,4611),(31721,'Looted Serpentis Pod Cluster',0,0,4711),(31821,'Looted Serpentis Ship Graveyard',0,0,4811),(32121,'Ransacked Serpentis Explosive Debris',0,0,4121),(32221,'Ransacked Serpentis Abandoned Station',0,0,4221),(32321,'Ransacked Serpentis Collision Site',0,0,4321),(32421,'Ransacked Serpentis Ruined Station',0,0,4421),(32521,'Ransacked Serpentis Ship Remnants',0,0,4521),(32621,'Ransacked Serpentis Dumped Cargo',0,0,4621),(32721,'Ransacked Serpentis Demolished Station',0,0,4721),(32821,'Ransacked Serpentis Ship Graveyard',0,0,4821),(33121,'Ruined Serpentis Monument Site',0,0,4231),(33221,'Ruined Serpentis Temple Site',0,0,4431),(33321,'Ruined Serpentis Science Outpost',0,0,4631),(33421,'Ruined Serpentis Crystal Quarry',0,0,4831),(31112,'Crumbling Angel Antiquated Outpost',0,0,5112),(31212,'Crumbling Angel Crystal Quarry',0,0,5212),(31312,'Crumbling Angel Explosive Debris',0,0,5312),(31412,'Crumbling Angel Abandoned Colony',0,0,5412),(31512,'Crumbling Angel Excavation',0,0,5512),(31612,'Crumbling Angel Solar Harvesters',0,0,5612),(31712,'Crumbling Angel Stone Formation',0,0,5712),(31812,'Crumbling Angel Mining Installation',0,0,5812),(32112,'Decayed Angel Excavation',0,0,5122),(32212,'Decayed Angel Collision Site',0,0,5222),(32312,'Decayed Angel Lone Vessel',0,0,5322),(32412,'Decayed Angel Mining Installation',0,0,5422),(32512,'Decayed Angel Particle Accelerator',0,0,5522),(32612,'Decayed Angel Mass Grave',0,0,5622),(32712,'Decayed Angel Rock Formations',0,0,5722),(32812,'Decayed Angel Quarry',0,0,5822),(33112,'Pristine Angel Ship Remnants',0,0,5132),(33212,'Pristine Angel Pod Cluster',0,0,5232),(33312,'Pristine Angel Dumped Cargo',0,0,5332),(33412,'Pristine Angel Ship Graveyard',0,0,5432),(33512,'Pristine Angel Battle Remnants',0,0,5532),(33612,'Pristine Angel Abandoned Colony',0,0,5632),(33712,'Pristine Angel Collision Site',0,0,5732),(33812,'Pristine Angel Explosive Debris',0,0,5832),(31122,'Looted Angel Collision Site',0,0,4112),(31222,'Looted Angel Abandoned Station',0,0,4212),(31322,'Looted Angel Lone Vessel',0,0,4312),(31422,'Looted Angel Ruined Station',0,0,4412),(31522,'Looted Angel Explosive Debris',0,0,4512),(31622,'Looted Angel Battle Remnants',0,0,4612),(31722,'Looted Angel Pod Cluster',0,0,4712),(31822,'Looted Angel Ship Graveyard',0,0,4812),(32122,'Ransacked Angel Explosive Debris',0,0,4122),(32222,'Ransacked Angel Abandoned Station',0,0,4222),(32322,'Ransacked Angel Collision Site',0,0,4322),(32422,'Ransacked Angel Ruined Station',0,0,4422),(32522,'Ransacked Angel Ship Remnants',0,0,4522),(32622,'Ransacked Angel Dumped Cargo',0,0,4622),(32722,'Ransacked Angel Demolished Station',0,0,4722),(32822,'Ransacked Angel Ship Graveyard',0,0,4822),(33122,'Ruined Angel Monument Site',0,0,4232),(33222,'Ruined Angel Temple Site',0,0,4432),(33322,'Ruined Angel Science Outpost',0,0,4632),(33422,'Ruined Angel Crystal Quarry',0,0,4832),(31113,'Crumbling Blood Antiquated Outpost',0,0,5113),(31213,'Crumbling Blood Crystal Quarry',0,0,5213),(31313,'Crumbling Blood Explosive Debris',0,0,5313),(31413,'Crumbling Blood Abandoned Colony',0,0,5413),(31513,'Crumbling Blood Excavation',0,0,5513),(31613,'Crumbling Blood Solar Harvesters',0,0,5613),(31713,'Crumbling Blood Stone Formation',0,0,5713),(31813,'Crumbling Blood Mining Installation',0,0,5813),(32113,'Decayed Blood Excavation',0,0,5123),(32213,'Decayed Blood Collision Site',0,0,5223),(32313,'Decayed Blood Lone Vessel',0,0,5323),(32413,'Decayed Blood Mining Installation',0,0,5423),(32513,'Decayed Blood Particle Accelerator',0,0,5523),(32613,'Decayed Blood Mass Grave',0,0,5623),(32713,'Decayed Blood Rock Formations',0,0,5723),(32813,'Decayed Blood Quarry',0,0,5823),(33113,'Pristine Blood Ship Remnants',0,0,5133),(33213,'Pristine Blood Pod Cluster',0,0,5233),(33313,'Pristine Blood Dumped Cargo',0,0,5333),(33413,'Pristine Blood Ship Graveyard',0,0,5433),(33513,'Pristine Blood Battle Remnants',0,0,5533),(33613,'Pristine Blood Abandoned Colony',0,0,5633),(33713,'Pristine Blood Collision Site',0,0,5733),(33813,'Pristine Blood Explosive Debris',0,0,5833),(31123,'Looted Blood Collision Site',0,0,4113),(31223,'Looted Blood Abandoned Station',0,0,4213),(31323,'Looted Blood Lone Vessel',0,0,4313),(31423,'Looted Blood Ruined Station',0,0,4413),(31523,'Looted Blood Explosive Debris',0,0,4513),(31623,'Looted Blood Battle Remnants',0,0,4613),(31723,'Looted Blood Pod Cluster',0,0,4713),(31823,'Looted Blood Ship Graveyard',0,0,4813),(32123,'Ransacked Blood Explosive Debris',0,0,4123),(32223,'Ransacked Blood Abandoned Station',0,0,4223),(32323,'Ransacked Blood Collision Site',0,0,4323),(32423,'Ransacked Blood Ruined Station',0,0,4423),(32523,'Ransacked Blood Ship Remnants',0,0,4523),(32623,'Ransacked Blood Dumped Cargo',0,0,4623),(32723,'Ransacked Blood Demolished Station',0,0,4723),(32823,'Ransacked Blood Ship Graveyard',0,0,4823),(33123,'Ruined Blood Monument Site',0,0,4233),(33223,'Ruined Blood Temple Site',0,0,4433),(33323,'Ruined Blood Science Outpost',0,0,4633),(33423,'Ruined Blood Crystal Quarry',0,0,4833),(31114,'Crumbling Guristas Antiquated Outpost',0,0,5114),(31214,'Crumbling Guristas Crystal Quarry',0,0,5214),(31314,'Crumbling Guristas Explosive Debris',0,0,5314),(31414,'Crumbling Guristas Abandoned Colony',0,0,5414),(31514,'Crumbling Guristas Excavation',0,0,5514),(31614,'Crumbling Guristas Solar Harvesters',0,0,5614),(31714,'Crumbling Guristas Stone Formation',0,0,5714),(31814,'Crumbling Guristas Mining Installation',0,0,5814),(32114,'Decayed Guristas Excavation',0,0,5124),(32214,'Decayed Guristas Collision Site',0,0,5224),(32314,'Decayed Guristas Lone Vessel',0,0,5324),(32414,'Decayed Guristas Mining Installation',0,0,5424),(32514,'Decayed Guristas Particle Accelerator',0,0,5524),(32614,'Decayed Guristas Mass Grave',0,0,5624),(32714,'Decayed Guristas Rock Formations',0,0,5724),(32814,'Decayed Guristas Quarry',0,0,5824),(33114,'Pristine Guristas Ship Remnants',0,0,5134),(33214,'Pristine Guristas Pod Cluster',0,0,5234),(33314,'Pristine Guristas Dumped Cargo',0,0,5334),(33414,'Pristine Guristas Ship Graveyard',0,0,5434),(33514,'Pristine Guristas Battle Remnants',0,0,5534),(33614,'Pristine Guristas Abandoned Colony',0,0,5634),(33714,'Pristine Guristas Collision Site',0,0,5734),(33814,'Pristine Guristas Explosive Debris',0,0,5834),(31124,'Looted Guristas Collision Site',0,0,4114),(31224,'Looted Guristas Abandoned Station',0,0,4214),(31324,'Looted Guristas Lone Vessel',0,0,4314),(31424,'Looted Guristas Ruined Station',0,0,4414),(31524,'Looted Guristas Explosive Debris',0,0,4514),(31624,'Looted Guristas Battle Remnants',0,0,4614),(31724,'Looted Guristas Pod Cluster',0,0,4714),(31824,'Looted Guristas Ship Graveyard',0,0,4814),(32124,'Ransacked Guristas Explosive Debris',0,0,4124),(32224,'Ransacked Guristas Abandoned Station',0,0,4224),(32324,'Ransacked Guristas Collision Site',0,0,4324),(32424,'Ransacked Guristas Ruined Station',0,0,4424),(32524,'Ransacked Guristas Ship Remnants',0,0,4524),(32624,'Ransacked Guristas Dumped Cargo',0,0,4624),(32724,'Ransacked Guristas Demolished Station',0,0,4724),(32824,'Ransacked Guristas Ship Graveyard',0,0,4824),(33124,'Ruined Guristas Monument Site',0,0,4234),(33224,'Ruined Guristas Temple Site',0,0,4434),(33324,'Ruined Guristas Science Outpost',0,0,4634),(33424,'Ruined Guristas Crystal Quarry',0,0,4834),(31115,'Crumbling Sansha Antiquated Outpost',0,0,5115),(31215,'Crumbling Sansha Crystal Quarry',0,0,5215),(31315,'Crumbling Sansha Explosive Debris',0,0,5315),(31415,'Crumbling Sansha Abandoned Colony',0,0,5415),(31515,'Crumbling Sansha Excavation',0,0,5515),(31615,'Crumbling Sansha Solar Harvesters',0,0,5615),(31715,'Crumbling Sansha Stone Formation',0,0,5715),(31815,'Crumbling Sansha Mining Installation',0,0,5815),(32115,'Decayed Sansha Excavation',0,0,5125),(32215,'Decayed Sansha Collision Site',0,0,5225),(32315,'Decayed Sansha Lone Vessel',0,0,5325),(32415,'Decayed Sansha Mining Installation',0,0,5425),(32515,'Decayed Sansha Particle Accelerator',0,0,5525),(32615,'Decayed Sansha Mass Grave',0,0,5625),(32715,'Decayed Sansha Rock Formations',0,0,5725),(32815,'Decayed Sansha Quarry',0,0,5825),(33115,'Pristine Sansha Ship Remnants',0,0,5135),(33215,'Pristine Sansha Pod Cluster',0,0,5235),(33315,'Pristine Sansha Dumped Cargo',0,0,5335),(33415,'Pristine Sansha Ship Graveyard',0,0,5435),(33515,'Pristine Sansha Battle Remnants',0,0,5535),(33615,'Pristine Sansha Abandoned Colony',0,0,5635),(33715,'Pristine Sansha Collision Site',0,0,5735),(33815,'Pristine Sansha Explosive Debris',0,0,5835),(31125,'Looted Sansha Collision Site',0,0,4115),(31225,'Looted Sansha Abandoned Station',0,0,4215),(31325,'Looted Sansha Lone Vessel',0,0,4315),(31425,'Looted Sansha Ruined Station',0,0,4415),(31525,'Looted Sansha Explosive Debris',0,0,4515),(31625,'Looted Sansha Battle Remnants',0,0,4615),(31725,'Looted Sansha Pod Cluster',0,0,4715),(31825,'Looted Sansha Ship Graveyard',0,0,4815),(32125,'Ransacked Sansha Explosive Debris',0,0,4125),(32225,'Ransacked Sansha Abandoned Station',0,0,4225),(32325,'Ransacked Sansha Collision Site',0,0,4325),(32425,'Ransacked Sansha Ruined Station',0,0,4425),(32525,'Ransacked Sansha Ship Remnants',0,0,4525),(32625,'Ransacked Sansha Dumped Cargo',0,0,4625),(32725,'Ransacked Sansha Demolished Station',0,0,4725),(32825,'Ransacked Sansha Ship Graveyard',0,0,4825),(33125,'Ruined Sansha Monument Site',0,0,4235),(33225,'Ruined Sansha Temple Site',0,0,4435),(33325,'Ruined Sansha Science Outpost',0,0,4635),(33425,'Ruined Sansha Crystal Quarry',0,0,4835),(33136,'Bloated Ruins',0,0,1),(33236,'Whispy Ruins',0,0,1),(33336,'Forgotten Ruins',0,0,1),(33436,'Crumbling Ruins',0,0,1),(33536,'Ancient Ruins',0,0,1),(33636,'Festering Ruins',0,0,1),(33736,'Hidden Ruins',0,0,1),(41111,'Local Serpentis Mainframe',0,0,6111),(41211,'Local Serpentis Data Processing Center',0,0,6211),(41311,'Local Serpentis Data Terminal',0,0,6311),(41411,'Local Serpentis Backup Server',0,0,6411),(41511,'Local Serpentis Virus Test Site',0,0,6511),(41611,'Local Serpentis Shattered Life-Support Unit',0,0,6611),(41711,'Local Serpentis Production Installation',0,0,6711),(41811,'Local Serpentis Minor Shipyard',0,0,6811),(42111,'Regional Serpentis Data Fortress',0,0,6121),(42211,'Regional Serpentis Command Center',0,0,6221),(42311,'Regional Serpentis Data Mining Site',0,0,6321),(42411,'Regional Serpentis Backup Server',0,0,6421),(42511,'Regional Serpentis Mainframe',0,0,6521),(42611,'Regional Serpentis Data Processing Center',0,0,6621),(42711,'Regional Serpentis Data Terminal',0,0,6721),(42811,'Regional Serpentis Secure Server',0,0,6821),(43111,'Central Serpentis Sparking Transmitter',0,0,6131),(43211,'Central Serpentis Survey Site',0,0,6231),(43311,'Central Serpentis Command Center',0,0,6331),(43411,'Central Serpentis Data Mining Site',0,0,6431),(43511,'Central Serpentis Mainframe',0,0,6531),(43611,'Central Serpentis Data Processing Center',0,0,6631),(43711,'Central Serpentis Data Terminal',0,0,6731),(43811,'Central Serpentis Secure Server',0,0,6831),(41112,'Local Angel Mainframe',0,0,6112),(41212,'Local Angel Data Processing Center',0,0,6212),(41312,'Local Angel Data Terminal',0,0,6312),(41412,'Local Angel Backup Server',0,0,6412),(41512,'Local Angel Virus Test Site',0,0,6512),(41612,'Local Angel Shattered Life-Support Unit',0,0,6612),(41712,'Local Angel Production Installation',0,0,6712),(41812,'Local Angel Minor Shipyard',0,0,6812),(42112,'Regional Angel Data Fortress',0,0,6122),(42212,'Regional Angel Command Center',0,0,6222),(42312,'Regional Angel Data Mining Site',0,0,6322),(42412,'Regional Angel Backup Server',0,0,6422),(42512,'Regional Angel Mainframe',0,0,6522),(42612,'Regional Angel Data Processing Center',0,0,6622),(42712,'Regional Angel Data Terminal',0,0,6722),(42812,'Regional Angel Secure Server',0,0,6822),(43112,'Central Angel Sparking Transmitter',0,0,6132),(43212,'Central Angel Survey Site',0,0,6232),(43312,'Central Angel Command Center',0,0,6332),(43412,'Central Angel Data Mining Site',0,0,6432),(43512,'Central Angel Mainframe',0,0,6532),(43612,'Central Angel Data Processing Center',0,0,6632),(43712,'Central Angel Data Terminal',0,0,6732),(43812,'Central Angel Secure Server',0,0,6832),(41113,'Local Blood Mainframe',0,0,6113),(41213,'Local Blood Data Processing Center',0,0,6213),(41313,'Local Blood Data Terminal',0,0,6313),(41413,'Local Blood Backup Server',0,0,6413),(41513,'Local Blood Virus Test Site',0,0,6513),(41613,'Local Blood Shattered Life-Support Unit',0,0,6613),(41713,'Local Blood Production Installation',0,0,6713),(41813,'Local Blood Minor Shipyard',0,0,6813),(42113,'Regional Blood Data Fortress',0,0,6123),(42213,'Regional Blood Command Center',0,0,6223),(42313,'Regional Blood Data Mining Site',0,0,6323),(42413,'Regional Blood Backup Server',0,0,6423),(42513,'Regional Blood Mainframe',0,0,6523),(42613,'Regional Blood Data Processing Center',0,0,6623),(42713,'Regional Blood Data Terminal',0,0,6723),(42813,'Regional Blood Secure Server',0,0,6823),(43113,'Central Blood Sparking Transmitter',0,0,6133),(43213,'Central Blood Survey Site',0,0,6233),(43313,'Central Blood Command Center',0,0,6333),(43413,'Central Blood Data Mining Site',0,0,6433),(43513,'Central Blood Mainframe',0,0,6533),(43613,'Central Blood Data Processing Center',0,0,6633),(43713,'Central Blood Data Terminal',0,0,6733),(43813,'Central Blood Secure Server',0,0,6833),(41114,'Local Guristas Mainframe',0,0,6114),(41214,'Local Guristas Data Processing Center',0,0,6214),(41314,'Local Guristas Data Terminal',0,0,6314),(41414,'Local Guristas Backup Server',0,0,6414),(41514,'Local Guristas Virus Test Site',0,0,6514),(41614,'Local Guristas Shattered Life-Support Unit',0,0,6614),(41714,'Local Guristas Production Installation',0,0,6714),(41814,'Local Guristas Minor Shipyard',0,0,6814),(42114,'Regional Guristas Data Fortress',0,0,6124),(42214,'Regional Guristas Command Center',0,0,6224),(42314,'Regional Guristas Data Mining Site',0,0,6324),(42414,'Regional Guristas Backup Server',0,0,6424),(42514,'Regional Guristas Mainframe',0,0,6524),(42614,'Regional Guristas Data Processing Center',0,0,6624),(42714,'Regional Guristas Data Terminal',0,0,6724),(42814,'Regional Guristas Secure Server',0,0,6824),(43114,'Central Guristas Sparking Transmitter',0,0,6134),(43214,'Central Guristas Survey Site',0,0,6234),(43314,'Central Guristas Command Center',0,0,6334),(43414,'Central Guristas Data Mining Site',0,0,6434),(43514,'Central Guristas Mainframe',0,0,6534),(43614,'Central Guristas Data Processing Center',0,0,6634),(43714,'Central Guristas Data Terminal',0,0,6734),(43814,'Central Guristas Secure Server',0,0,6834),(41115,'Local Sansha Mainframe',0,0,6115),(41215,'Local Sansha Data Processing Center',0,0,6215),(41315,'Local Sansha Data Terminal',0,0,6315),(41415,'Local Sansha Backup Server',0,0,6415),(41515,'Local Sansha Virus Test Site',0,0,6515),(41615,'Local Sansha Shattered Life-Support Unit',0,0,6615),(41715,'Local Sansha Production Installation',0,0,6715),(41815,'Local Sansha Minor Shipyard',0,0,6815),(42115,'Regional Sansha Data Fortress',0,0,6125),(42215,'Regional Sansha Command Center',0,0,6225),(42315,'Regional Sansha Data Mining Site',0,0,6325),(42415,'Regional Sansha Backup Server',0,0,6425),(42515,'Regional Sansha Mainframe',0,0,6525),(42615,'Regional Sansha Data Processing Center',0,0,6625),(42715,'Regional Sansha Data Terminal',0,0,6725),(42815,'Regional Sansha Secure Server',0,0,6825),(43115,'Central Sansha Sparking Transmitter',0,0,6135),(43215,'Central Sansha Survey Site',0,0,6235),(43315,'Central Sansha Command Center',0,0,6335),(43415,'Central Sansha Data Mining Site',0,0,6435),(43515,'Central Sansha Mainframe',0,0,6535),(43615,'Central Sansha Data Processing Center',0,0,6635),(43715,'Central Sansha Data Terminal',0,0,6735),(43815,'Central Sansha Secure Server',0,0,6835),(41110,'Covert Research Facility',0,0,1),(42110,'Covert Research Facility',0,0,1),(43110,'Covert Research Facility',0,0,1),(43120,'Digital Network',0,0,1),(43220,'Digital Matrix',0,0,1),(43320,'Digital Complex',0,0,1),(43420,'Digital Convolution',0,0,1),(43520,'Digital Plexus',0,0,1),(43620,'Digital Circuitry',0,0,1),(43720,'Digital Compound',0,0,1),(43820,'Digital Tessellation',0,0,1),(51110,'Wild Nebula',0,0,1),(51210,'Pipe Nebula',0,0,1),(51310,'Calabash Nebula',0,0,1),(51410,'Blackeye Nebula',0,0,1),(51510,'Smoking Nebula',0,0,1),(51610,'Glass Nebula',0,0,1),(51710,'Flame Nebula',0,0,1),(51810,'Ghost Nebula ',0,0,1),(52110,'Sister Nebula',0,0,1),(52210,'Bright Nebula',0,0,1),(52310,'Crimson Nebula',0,0,1),(52410,'Phoenix Nebula',0,0,1),(52510,'Eagle Nebula',0,0,1),(52610,'Rapture Nebula',0,0,1),(52710,'Ring Nebula',0,0,1),(52810,'Sparkling Nebula',0,0,1),(53110,'Forgotten Nebula',0,0,1),(53210,'Diabolo Nebula',0,0,1),(53310,'Saintly Nebula',0,0,1),(53410,'Sunspark Nebula',0,0,1),(53510,'Emerald Nebula',0,0,1),(53610,'Swarm Nebula',0,0,1),(53710,'Boisterous Nebula',0,0,1),(53810,'Thick Nebula',0,0,1),(60000,'DED Space',0,0,1),(71118,' Hideaway',0,20,1100),(71128,' Hidden Hideaway',0,20,1200),(71138,' Forsaken Hideaway',0,20,1300),(71148,' Forlorn Hideaway',0,20,1400),(71218,' Burrow',0,21,1200),(71318,' Refuge',0,22,1300),(71418,' Den',0,23,1400),(71518,' Yard',0,24,1500),(72118,' Refuge',0,22,1300),(72218,' Den',0,23,1400),(72228,' Hidden Den',0,23,1500),(72238,' Forsaken Den',0,23,1500),(72248,' Forlorn Den',0,23,1600),(72318,' Yard',0,24,1500),(72418,' Rally Point',0,25,1600),(72428,' Hidden Rally Point',0,25,1600),(72438,' Forsaken Rally Point',0,25,1700),(72448,' Forlorn Rally Point',0,25,1800),(72518,' Port',0,26,1500),(73118,' Rally Point',0,25,1600),(73128,' Hidden Rally Point',0,25,1600),(73138,' Forsaken Rally Point',0,25,1700),(73148,' Forlorn Rally Point',0,25,1800),(73218,' Port',0,26,1500),(73318,' Hub',0,27,1600),(73328,' Hidden Hub',0,27,1600),(73338,' Forsaken Hub',0,27,1700),(73348,' Forlorn Hub',0,27,1700),(73418,' Haven',0,28,1800),(73518,' Sanctum',0,29,1900),(71116,'Drone Cluster',0,30,1010),(71216,'Drone Collection',0,31,1110),(71316,'Drone Assembly',0,32,1210),(71416,'Drone Gathering',0,33,1310),(72116,'Drone Assembly',0,32,1210),(72216,'Drone Gathering',0,33,1310),(72316,'Drone Surveillance',0,34,1410),(72416,'Drone Menagerie',0,35,1510),(72516,'Drone Herd',0,36,1610),(73116,'Drone Menagerie',35,0,1510),(73216,'Drone Herd',0,36,1610),(73316,'Drone Squad',0,37,1710),(73416,'Drone Patrol',0,38,1810),(73516,'Drone Horde',0,39,1910),(81110,' Hideout',0,0,1000),(81210,' Lookout',0,0,1100),(81310,' Watch',0,0,1100),(81410,' Vigil',0,0,1200),(81510,' Outpost',0,0,1200),(82110,' Vigil',0,0,1300),(82210,' Outpost',0,0,1300),(82310,' Annex',0,0,1400),(82410,' Base',0,0,1400),(82510,' Fortress',0,0,1500),(83110,' Base',0,0,1600),(83210,' Fortress',0,0,1600),(83310,' Complex',0,0,1700),(83410,' Headquarters',0,0,1800),(83510,' Staging Point',0,0,1900),(81116,'Drone Haunted Yard',0,0,1120),(81216,'Drone Desolate Site',0,0,1220),(81316,'Drone Chemical Yard',0,0,1320),(82116,'Drone Trial Yard',0,0,1420),(82216,'Drone Dirty Site',0,0,1520),(82316,'Drone Ruins',0,0,1620),(83116,'Drone Independence',0,0,1720),(83216,'Drone Radiance',0,0,1820),(83316,'Drone Hierarchy',0,0,1920),(90000,'Escalation Space',0,0,1),(71516,'Drone Surveillance',0,34,1410);
/*!40000 ALTER TABLE `dunTemplates` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:52

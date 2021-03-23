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
-- Table structure for table `dgmOperands`
--

DROP TABLE IF EXISTS `dgmOperands`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dgmOperands` (
  `operandID` tinyint(3) unsigned NOT NULL,
  `operandKey` varchar(50) NOT NULL,
  `description` varchar(100) NOT NULL,
  `format` varchar(100) NOT NULL,
  `arg1categoryID` smallint(6) NOT NULL,
  `arg2categoryID` smallint(6) NOT NULL,
  `resultCategoryID` smallint(6) NOT NULL,
  `pythonFormat` varchar(100) NOT NULL,
  PRIMARY KEY (`operandID`),
  KEY `arg1categoryID` (`arg1categoryID`),
  KEY `arg2categoryID` (`arg2categoryID`),
  KEY `resultCategoryID` (`resultCategoryID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dgmOperands`
--

LOCK TABLES `dgmOperands` WRITE;
/*!40000 ALTER TABLE `dgmOperands` DISABLE KEYS */;
INSERT INTO `dgmOperands` VALUES (1,'ADD','add two numbers','(%(arg1)s)+(%(arg2)s)',4,4,4,'(%(arg1)s)+(%(arg2)s)'),(2,'AGGM','add gang groupl modifier','[%(arg1)s].AGGM(%(arg2)s)',5,2,4,'dogma.AddGangGroupModifier(env,%(arg1)s, %(arg2)s)'),(3,'AGIM','add gang shipl modifier','[%(arg1)s].AGIM(%(arg2)s)',5,2,4,'dogma.AddGangShipModifier(env,%(arg1)s, %(arg2)s)'),(4,'AGORSM','add gang owner required skill modifier','[%(arg1)s].AGORSM(%(arg2)s)',5,2,4,'dogma.AddGangOwnerRequiredSkillModifier(env,%(arg1)s, %(arg2)s)'),(5,'AGRSM','add gang required skill modifier','[%(arg1)s].AGRSM(%(arg2)s)',5,2,4,'dogma.AddGangRequiredSkillModifier(env,%(arg1)s, %(arg2)s)'),(6,'AIM','add item modifier','(%(arg1)s).AddItemModifier (%(arg2)s)',5,2,4,'dogma.AddItemModifier(env,%(arg1)s, %(arg2)s)'),(7,'ALGM','add location group modifier','(%(arg1)s).AddLocationGroupModifier (%(arg2)s)',5,2,4,'dogma.AddLocationGroupModifier(env,%(arg1)s, %(arg2)s)'),(8,'ALM','add location modifier','(%(arg1)s).AddLocationModifier (%(arg2)s)',5,2,4,'dogma.AddLocationModifier(env,%(arg1)s, %(arg2)s)'),(9,'ALRSM','add location required skill modifier','(%(arg1)s).ALRSM(%(arg2)s)',5,2,4,'dogma.AddLocationRequiredSkillModifier(env,%(arg1)s, %(arg2)s)'),(10,'AND','logical and operation','(%(arg1)s) AND (%(arg2)s)',4,4,4,'(%(arg1)s and %(arg2)s)'),(11,'AORSM','add owner required skill modifier','(%(arg1)s).AORSM(%(arg2)s)',5,2,4,'dogma.AddOwnerRequiredSkillModifier(env,%(arg1)s, %(arg2)s)'),(12,'ATT','attribute','%(arg1)s->%(arg2)s',6,2,3,'(%(arg1)s, %(arg2)s)'),(13,'ATTACK','attack given ship','Attack',2,0,4,'Attack(env, %(arg1)s, %(arg2)s)'),(14,'CARGOSCAN','Scans the cargo of the targeted ship.','CargoScan',0,0,4,'CargoScan(env, None, None)'),(15,'CHEATTELEDOCK','Instantly enter a station.','CheatTeleDock()',0,0,4,'CheatTeleDock(env, None, None)'),(16,'CHEATTELEGATE','Automatically invoke a stargate destination from remote distances.','CheatTeleGate()',0,0,4,'dogma.CheatTeleGate(env, None, None)'),(17,'COMBINE','executes two statements','%(arg1)s);     (%(arg2)s',4,4,4,'%(arg1)s\r\n%(arg2)s'),(18,'DEC','decreases an item-attribute by the value of another attribute','%(arg1)s-=self.%(arg2)s',3,2,4,' '),(19,'DECLOAKWAVE','broadcasts a decloaking wave','DecloakWave',0,0,4,'DecloakWave(env, None, None)'),(20,'DECN','decreases an item-attribute by number','%(arg1)s-=%(arg2)s',3,4,4,' '),(21,'DEFASSOCIATION','define attribute association type','%(value)s',0,0,1,'const.dgmAss%(value)s'),(22,'DEFATTRIBUTE','define attribute','%(value)s',0,0,2,'%(value)s'),(23,'DEFBOOL','define bool constant','Bool(%(value)s)',0,0,4,'%(value)s'),(24,'DEFENVIDX','define environment index','Current%(value)s',0,0,6,'env[const.dgmEnv%(value)s]'),(25,'DEFFLOAT','defines a float constant','Float(%(value)s)',0,0,4,' '),(26,'DEFGROUP','define group','%(value)s',0,0,8,' '),(27,'DEFINT','defines an int constant','Int(%(value)s)',0,0,4,'%(value)s'),(28,'DEFSTRING','defines a string constant','\"%(value)s\"',0,0,4,'\"%(value)s\"'),(29,'DEFTYPEID','define a type ID','Type(%(value)s)',0,0,9,' '),(30,'ECMBURST','Clears all targets on all ships(excluding self) wihin range. ','ECMBurst()',0,0,4,'dogma.ECMBurst(env, None, None)'),(31,'EFF','define association type','(%(arg2)s).(%(arg1)s)',1,3,5,'(%(arg1)s, %(arg2)s)'),(32,'EMPWAVE','broadcasts an EMP wave','EMPWave',0,0,4,'EMPWave(env, None, None)'),(33,'EQ','checks for equality','%(arg1)s == %(arg2)s',4,4,4,'(%(arg1)s == %(arg2)s)'),(34,'GA','attribute on a module group','%(arg1)s.%(arg2)s',8,2,3,'(%(arg1)s, %(arg2)s)'),(35,'GET','calculate attribute','%(arg1)s.%(arg2)s()',6,2,4,'dogmaLM.GetAttributeValue(%(arg1)s, %(arg2)s)'),(36,'GETTYPE','gets type of item','%(arg1)s.GetTypeID()',6,0,9,'env.itemTypeID'),(37,'GM','get a module of a given groupID from a given location (ship or player)','%(arg1)s.%(arg2)s',6,8,6,'dogma.GetModule(env,%(arg1)s,%(arg2)s)'),(38,'GT','checks whether expression 1  is greater than expression 2','%(arg1)s> %(arg2)s',4,4,4,'(%(arg1)s > %(arg2)s)'),(39,'GTE','checks whether an expression is greater than or equal to another','%(arg1)s>=%(arg2)s',4,4,4,'(%(arg1)s >= %(arg2)s)'),(40,'IA','generic attribute','%(arg1)s',2,0,3,'%(arg1)s'),(41,'IF','if construct','If(%(arg1)s), Then (%(arg2)s)',4,4,4,'if %(arg1)s:\r\n    %(arg2)s'),(42,'INC','increases an item-attribute by the value of another attribute','%(arg1)s+=self.%(arg2)s',3,2,4,'<handled in code>'),(43,'INCN','increases an item-attribute by a number','%(arg1)s+=%(arg2)s',3,4,4,' '),(44,'LAUNCH','launches a missile','LaunchMissile()',0,0,4,'dogma.Launch(env, None, None)'),(45,'LAUNCHDEFENDERMISSILE','launches a defender missile','LaunchDefenderMissile()',0,0,4,'dogma.LaunchDefenderMissile(env, None, None)'),(46,'LAUNCHDRONE','launches a drone.','LaunchDrone()',0,0,4,'dogma.Launch(env, None, None)'),(47,'LAUNCHFOFMISSILE','launches an FOF missile','LaunchFOFMissile()',0,0,4,'dogma.LaunchFOFMissile(env, None, None)'),(48,'LG','specify a group in a location','%(arg1)s..%(arg2)s',6,8,6,'(%(arg1)s, %(arg2)s)'),(49,'LS','location - skill required item group','%(arg1)s[%(arg2)s]',6,9,6,'(%(arg1)s, %(arg2)s)'),(50,'MINE','mines an asteroid','Mine',0,0,4,'Mine(env, None, None)'),(51,'MUL','multiplies two numbers','(%(arg1)s)*(%(arg2)s)',4,4,4,'(%(arg1)s * %(arg2)s)'),(52,'OR','logical or operation','%(arg1)s OR %(arg2)s',4,4,4,'(%(arg1)s or %(arg2)s)'),(53,'POWERBOOST','','PowerBoost',0,0,4,'dogma.PowerBoost(env, None, None)'),(54,'RGGM','remove gang groupl modifier','[%(arg1)s].RGGM(%(arg2)s)',5,2,4,'dogma.RemoveGangGroupModifier(env,%(arg1)s, %(arg2)s)'),(55,'RGIM','remove gang shipl modifier','[%(arg1)s].RGIM(%(arg2)s)',5,2,4,'dogma.RemoveGangShipModifier(env,%(arg1)s, %(arg2)s)'),(56,'RGORSM','remove a gang owner required skill modifier','[%(arg1)s].RGORSM(%(arg2)s)',5,2,4,'dogma.RemoveGangOwnerRequiredSkillModifier(env,%(arg1)s, %(arg2)s)'),(57,'RGRSM','remove a gang required skill modifier','[%(arg1)s].RGRSM(%(arg2)s)',5,2,4,'dogma.RemoveGangRequiredSkillModifier(env,%(arg1)s, %(arg2)s)'),(58,'RIM','remove  item modifier','(%(arg1)s).RemoveItemModifier (%(arg2)s)',5,2,4,'dogma.RemoveItemModifier(env,%(arg1)s, %(arg2)s)'),(59,'RLGM','remove location group modifier','(%(arg1)s).RemoveLocationGroupModifier (%(arg2)s)',5,2,4,'dogma.RemoveLocationGroupModifier(env,%(arg1)s, %(arg2)s)'),(60,'RLM','remove location modifier','(%(arg1)s).RemoveLocationModifier (%(arg2)s)',5,2,4,'dogma.RemoveLocationModifier(env,%(arg1)s, %(arg2)s)'),(61,'RLRSM','remove a  required skill modifier','(%(arg1)s).RLRSM(%(arg2)s)',5,2,4,'dogma.RemoveLocationRequiredSkillModifier(env,%(arg1)s, %(arg2)s)'),(62,'RORSM','remove an owner required skill modifier','(%(arg1)s).RORSM(%(arg2)s)',5,2,4,'dogma.RemoveOwnerRequiredSkillModifier(env,%(arg1)s, %(arg2)s)'),(63,'RS','true if arg1 requires arg2','%(arg1)s.Requires(%(arg2)s)',6,9,4,'dogma.RequireSkill(env, %(arg1)s, %(arg2)s)'),(64,'RSA','attribute on modules that have required skill','%(arg1)s.%(arg2)s',9,2,3,'(%(arg1)s, %(arg2)s)'),(65,'SET','sets an item attribute','%(arg1)s := %(arg2)s',3,4,4,'<handled in code>'),(66,'SHIPSCAN','scans a ship','ShipScan()',0,0,4,'ShipScan(env, None, None)'),(67,'SKILLCHECK','','SkillCheck(%(arg1)s)',4,0,4,'dogma.SkillCheck(env, %(arg1)s, %(arg2)s)'),(68,'SUB','subtracts a number from another one','%(arg1)s-%(arg2)s',4,4,4,' '),(69,'SURVEYSCAN','scans an asteroid for information','SurveyScan()',0,0,4,'SurveyScan(env, None, None)'),(70,'TARGETHOSTILES','Targets any hostile ships within range (assuming electronics have capability).','TargetHostiles()',0,0,4,'dogma.TargetHostiles(env, None, None)'),(71,'TARGETSILENTLY','','TargetSilently()',0,0,4,'dogmaLM.AddTargetEx(shipID,targetID, silent=1, tasklet=1)'),(72,'TOOLTARGETSKILLS',' ','CheckToolTargetSkills',0,0,4,'dogma.CheckToolTargetSkills(env,None,None)'),(73,'UE','raises an user error','UserError(%(arg1)s)',4,0,4,'raise UserError(%(arg1)s)'),(74,'VERIFYTARGETGROUP','raises a user error if incorrect target group','VerifyTargetGroup()',0,0,4,'dogma.VerifyTargetGroup(env, None, None)'),(75,'SPEEDBOOST','applies speed booster to ship','SpeedBoost()',0,0,0,'dogma.SpeedBoost(env, none, none)');
/*!40000 ALTER TABLE `dgmOperands` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-10 18:28:51

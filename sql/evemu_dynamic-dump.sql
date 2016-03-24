/*
SQLyog Community Edition- MySQL GUI v7.11
MySQL - 5.0.67-community-nt : Database - eve_evemu_dynamic
*********************************************************************
*/


/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- No longer needed
DROP TABLE IF EXISTS entityStatic;

/*Table structure for table `srvAccount` */

DROP TABLE IF EXISTS `srvAccount`;

-- ----------------------------
-- Table structure for `srvAccount`
-- ----------------------------
DROP TABLE IF EXISTS `srvAccount`;
CREATE TABLE `srvAccount` (
  `accountID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `accountName` varchar(43) NOT NULL DEFAULT '',
  `password` varchar(43) NOT NULL DEFAULT '',
  `hash` tinyblob,
  `role` bigint(20) unsigned NOT NULL DEFAULT '0',
  `online` tinyint(1) NOT NULL DEFAULT '0',
  `banned` tinyint(1) NOT NULL DEFAULT '0',
  `logonCount` int(10) unsigned NOT NULL DEFAULT '0',
  `lastLogin` timestamp NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE CURRENT_TIMESTAMP,
  `lastLogout` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`accountID`),
  UNIQUE KEY `accountName` (`accountName`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

/*Data for the table `srvAccount` */

/*Table structure for table `srvAlliance_ShortNames` */

DROP TABLE IF EXISTS `srvAlliance_ShortNames`;

CREATE TABLE `srvAlliance_ShortNames` (
  `allianceID` int(10) unsigned NOT NULL default '0',
  `shortName` text NOT NULL,
  PRIMARY KEY  (`allianceID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvAlliance_ShortNames` */

/*Table structure for table `srvBillsPayable` */

DROP TABLE IF EXISTS `srvBillsPayable`;

CREATE TABLE `srvBillsPayable` (
  `billID` int(10) unsigned NOT NULL default '0',
  `billTypeID` int(10) unsigned default NULL,
  `debtorID` int(10) unsigned default NULL,
  `creditorID` int(10) unsigned default NULL,
  `amount` text NOT NULL,
  `dueDateTime` text NOT NULL,
  `interest` text NOT NULL,
  `externalID` int(10) unsigned default NULL,
  `paid` text NOT NULL,
  `externalID2` text NOT NULL,
  PRIMARY KEY  (`billID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvBillsPayable` */

/*Table structure for table `srvBillsReceivable` */

DROP TABLE IF EXISTS `srvBillsReceivable`;

CREATE TABLE `srvBillsReceivable` (
  `billID` int(10) unsigned NOT NULL default '0',
  `billTypeID` int(10) unsigned default NULL,
  `debtorID` int(10) unsigned default NULL,
  `creditorID` int(10) unsigned default NULL,
  `amount` text NOT NULL,
  `dueDateTime` text NOT NULL,
  `interest` text NOT NULL,
  `externalID` int(10) unsigned default NULL,
  `paid` text NOT NULL,
  `externalID2` text NOT NULL,
  PRIMARY KEY  (`billID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvBillsReceivable` */

/*Table structure for table `srvBookmarks` */

DROP TABLE IF EXISTS `srvBookmarks`;

CREATE TABLE `srvBookmarks` (
  `bookmarkID` int(10) unsigned NOT NULL default '0',
  `ownerID` int(10) unsigned NOT NULL default '0',
  `itemID` bigint(20) unsigned NOT NULL default '0',
  `typeID` int(10) unsigned NOT NULL default '0',
  `flag` int(10) unsigned NOT NULL default '0',
  `memo` varchar(85) NOT NULL default '',
  `created` bigint(20) unsigned NOT NULL default '0',
  `x` double NOT NULL default '0',
  `y` double NOT NULL default '0',
  `z` double NOT NULL default '0',
  `locationID` int(10) unsigned NOT NULL default '0',
  `note` varchar(85) NOT NULL default '',
  `creatorID` int(10) unsigned NOT NULL default '0',
  `folderID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`bookmarkID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvBookmarks` */

DROP TABLE IF EXISTS `srvBookmarkFolders`;

CREATE TABLE `srvBookmarkFolders` (
	`folderID` int (10),
	`folderName` varchar (255),
	`ownerID` int (10),
	`creatorID` int (10),
	PRIMARY KEY (`folderID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `srvCacheLocations` */

DROP TABLE IF EXISTS `srvCacheLocations`;

CREATE TABLE `srvCacheLocations` (
  `locationID` int(10) unsigned NOT NULL default '0',
  `locationName` varchar(100) NOT NULL default '',
  `x` double NOT NULL default '0',
  `y` double NOT NULL default '0',
  `z` double NOT NULL default '0',
  PRIMARY KEY  (`locationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvCacheLocations` */

/*Table structure for table `srvCacheOwners` */

DROP TABLE IF EXISTS `srvCacheOwners`;

CREATE TABLE `srvCacheOwners` (
  `ownerID` int(10) unsigned NOT NULL default '0',
  `ownerName` varchar(100) NOT NULL default '',
  `typeID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`ownerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvCacheOwners` */

/*Table structure for table `srvChannelChars` */

DROP TABLE IF EXISTS `srvChannelChars`;

CREATE TABLE `srvChannelChars` (
  `channelID` int(10) unsigned NOT NULL default '0',
  `corpID` int(10) unsigned NOT NULL default '0',
  `charID` int(10) unsigned NOT NULL default '0',
  `allianceID` int(10) unsigned NOT NULL default '0',
  `role` int(10) unsigned NOT NULL default '0',
  `extra` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`channelID`,`charID`),
  KEY `FK_CHANNELCHARS_CHARACTER` (`charID`),
  KEY `FK_CHANNELCHARS_CORPORATIONS` (`corpID`),
  KEY `FK_CHANNELCHARS_ALLIANCES` (`allianceID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvChannelChars` */

/*Table structure for table `srvChannelMods` */

DROP TABLE IF EXISTS `srvChannelMods`;

CREATE TABLE `srvChannelMods` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `channelID` int(10) unsigned NOT NULL default '0',
  `accessor` int(10) unsigned default NULL,
  `mode` int(10) unsigned NOT NULL default '0',
  `untilWhen` bigint(20) unsigned default NULL,
  `originalMode` int(10) unsigned default NULL,
  `admin` varchar(85) default NULL,
  `reason` text,
  PRIMARY KEY  (`id`),
  KEY `FK_CHANNELMODS_CHANNELS` (`channelID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvChannelMods` */

/*Table structure for table `srvCharacter` */

DROP TABLE IF EXISTS `srvCharacter`;

CREATE TABLE `srvCharacter` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `accountID` int(10) unsigned default NULL,
  `title` varchar(85) NOT NULL default '',
  `description` text NOT NULL,
  `bounty` double NOT NULL default '0',
  `balance` double NOT NULL default '0',
  `aurBalance` double NOT NULL default '0',
  `securityRating` double NOT NULL default '0',
  `petitionMessage` varchar(85) NOT NULL default '',
  `logonMinutes` int(10) unsigned NOT NULL default '0',
  `skillPoints` double NOT NULL default '0',
  `skillQueueEndTime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `corporationID` int(10) unsigned NOT NULL default '0',
  `corpRole` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `rolesAtAll` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `rolesAtBase` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `rolesAtHQ` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `rolesAtOther` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `corporationDateTime` bigint(20) unsigned NOT NULL default '0',
  `startDateTime` bigint(20) unsigned NOT NULL default '0',
  `createDateTime` bigint(20) unsigned NOT NULL default '0',
  `ancestryID` int(10) unsigned NOT NULL default '0',
  `careerID` int(10) unsigned NOT NULL default '0',
  `schoolID` int(10) unsigned NOT NULL default '0',
  `careerSpecialityID` int(10) unsigned NOT NULL default '0',
  `gender` tinyint(4) NOT NULL default '0',
  `stationID` int(10) unsigned NOT NULL default '0',
  `solarSystemID` int(10) unsigned NOT NULL default '0',
  `constellationID` int(10) unsigned NOT NULL default '0',
  `regionID` int(10) unsigned NOT NULL default '0',
  `online` tinyint(1) NOT NULL default '0',
  `freeRespecs` tinyint(1) unsigned NOT NULL default '0',
  `lastRespecDateTime` bigint(20) unsigned NOT NULL default '0',
  `nextRespecDateTime` bigint(20) unsigned NOT NULL default '0',
  `deletePrepareDateTime` BIGINT(20) UNSIGNED NULL DEFAULT '0',
  `shipID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`characterID`),
  KEY `FK_CHARACTER__ACCOUNTS` (`accountID`),
  KEY `FK_CHARACTER__CHRANCESTRIES` (`ancestryID`),
  KEY `FK_CHARACTER__CHRCAREERS` (`careerID`),
  KEY `FK_CHARACTER__CHRCAREERSPECIALITIES` (`careerSpecialityID`),
  KEY `FK_CHARACTER__CHRSCHOOLS` (`schoolID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvCharacter` */

/*Table structure for table `srvChrApplications` */

DROP TABLE IF EXISTS `srvChrApplications`;

CREATE TABLE `srvChrApplications` (
  `corporationID` int(10) unsigned NOT NULL,
  `characterID` int(10) unsigned NOT NULL,
  `applicationText` text NOT NULL,
  `roles` bigint(20) unsigned NOT NULL,
  `grantableRoles` bigint(20) unsigned NOT NULL,
  `status` int(10) unsigned NOT NULL,
  `applicationDateTime` bigint(20) unsigned NOT NULL,
  `deleted` tinyint(3) unsigned NOT NULL,
  `lastCorpUpdaterID` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`corporationID`,`characterID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvChrApplications` */

/*Table structure for table `srvChrCertificates` */
DROP TABLE IF EXISTS `srvChrCertificates`;

CREATE TABLE IF NOT EXISTS `srvChrCertificates` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `characterID` int(10) NOT NULL,
  `certificateID` int(10) NOT NULL,
  `grantDate` bigint(20) NOT NULL,
  `visibilityFlags` int(10) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

/*Table structure for table `srvChrEmployment` */

DROP TABLE IF EXISTS `srvChrEmployment`;

CREATE TABLE `srvChrEmployment` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `corporationID` int(10) unsigned NOT NULL default '0',
  `startDate` bigint(20) unsigned NOT NULL default '0',
  `deleted` tinyint(4) NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`corporationID`,`startDate`),
  KEY `corporationID` (`corporationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvChrEmployment` */

/*Table structure for table `srvChrMissionState` */

DROP TABLE IF EXISTS `srvChrMissionState`;

CREATE TABLE `srvChrMissionState` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `missionID` int(10) unsigned NOT NULL default '0',
  `missionState` tinyint(3) unsigned NOT NULL default '0',
  `expirationTime` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`missionID`),
  KEY `missionID` (`missionID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvChrMissionState` */

/*Table structure for table `srvChrNotes` */

DROP TABLE IF EXISTS `srvChrNotes`;

CREATE TABLE `srvChrNotes` (
  `itemID` int(10) unsigned NOT NULL default '0',
  `ownerID` int(10) unsigned default NULL,
  `note` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvChrNotes` */

/*Table structure for table `srvChrNPCStandings` */

DROP TABLE IF EXISTS `srvChrNPCStandings`;

CREATE TABLE `srvChrNPCStandings` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `fromID` int(10) unsigned NOT NULL default '0',
  `standing` double NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`fromID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvChrNPCStandings` */

/*Table structure for table `srvChrOffers` */

DROP TABLE IF EXISTS `srvChrOffers`;

CREATE TABLE `srvChrOffers` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `offerID` int(10) unsigned NOT NULL default '0',
  `expirationTime` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`offerID`),
  KEY `offerID` (`offerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvChrOffers` */

/*Table structure for table `srvChrOwnerNote` */

DROP TABLE IF EXISTS `srvChrOwnerNote`;

CREATE TABLE `srvChrOwnerNote` (
  `noteID` int(10) unsigned NOT NULL auto_increment,
  `ownerID` int(10) unsigned NOT NULL,
  `label` text,
  `note` text,
  UNIQUE KEY `noteID` (`noteID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvChrOwnerNote` */

/*Table structure for table `srvChrStandings` */

DROP TABLE IF EXISTS `srvChrStandings`;

CREATE TABLE `srvChrStandings` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `toID` int(10) unsigned NOT NULL default '0',
  `standing` double NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`toID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvChrStandings` */

/*Table structure for table `srvCorporation` */

DROP TABLE IF EXISTS `srvCorporation`;

CREATE TABLE `srvCorporation` (
  `corporationID` int(10) unsigned NOT NULL auto_increment,
  `corporationName` varchar(100) NOT NULL default '',
  `description` mediumtext NOT NULL,
  `tickerName` varchar(8) NOT NULL default '',
  `url` mediumtext NOT NULL,
  `taxRate` double NOT NULL default '0',
  `minimumJoinStanding` double NOT NULL default '0',
  `corporationType` int(10) unsigned NOT NULL default '0',
  `hasPlayerPersonnelManager` tinyint(3) unsigned NOT NULL default '0',
  `sendCharTerminationMessage` tinyint(3) unsigned NOT NULL default '1',
  `creatorID` int(10) unsigned NOT NULL default '0',
  `ceoID` int(10) unsigned NOT NULL default '0',
  `stationID` int(10) unsigned NOT NULL default '0',
  `raceID` int(10) unsigned default NULL,
  `allianceID` int(10) unsigned NOT NULL default '0',
  `shares` bigint(20) unsigned NOT NULL default '1000',
  `memberCount` int(10) unsigned NOT NULL default '0',
  `memberLimit` int(10) unsigned NOT NULL default '10',
  `allowedMemberRaceIDs` int(10) unsigned NOT NULL default '0',
  `graphicID` int(10) unsigned NOT NULL default '0',
  `shape1` int(10) unsigned default NULL,
  `shape2` int(10) unsigned default NULL,
  `shape3` int(10) unsigned default NULL,
  `color1` int(10) unsigned default NULL,
  `color2` int(10) unsigned default NULL,
  `color3` int(10) unsigned default NULL,
  `typeface` varchar(11) default NULL,
  `division1` varchar(100) default '1st division',
  `division2` varchar(100) default '2nd division',
  `division3` varchar(100) default '3rd division',
  `division4` varchar(100) default '4th division',
  `division5` varchar(100) default '5th division',
  `division6` varchar(100) default '6th division',
  `division7` varchar(100) default '7th division',
  `walletDivision1` varchar(100) default '1st wallet division',
  `walletDivision2` varchar(100) default '2nd wallet division',
  `walletDivision3` varchar(100) default '3rd wallet division',
  `walletDivision4` varchar(100) default '4th wallet division',
  `walletDivision5` varchar(100) default '5th wallet division',
  `walletDivision6` varchar(100) default '6th wallet division',
  `walletDivision7` varchar(100) default '7th wallet division',
  `balance` double NOT NULL default '0',
  `deleted` tinyint(4) NOT NULL default '0',
  `isRecruiting` tinyint(1) unsigned NOT NULL default '0',
  `warFactionID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`corporationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvCorporation` */

/*Table structure for table `srvCourierMissions` */

DROP TABLE IF EXISTS `srvCourierMissions`;

CREATE TABLE `srvCourierMissions` (
  `missionID` int(10) unsigned NOT NULL auto_increment,
  `kind` tinyint(3) unsigned NOT NULL default '0',
  `state` tinyint(3) unsigned NOT NULL default '0',
  `availabilityID` int(10) unsigned default NULL,
  `inOrder` tinyint(3) unsigned NOT NULL default '0',
  `description` text NOT NULL,
  `issuerID` int(10) unsigned default NULL,
  `assigneeID` int(10) unsigned default NULL,
  `acceptFee` double NOT NULL default '0',
  `acceptorID` int(10) unsigned default NULL,
  `dateIssued` int(10) unsigned NOT NULL default '0',
  `dateExpires` int(10) unsigned NOT NULL default '0',
  `dateAccepted` int(10) unsigned NOT NULL default '0',
  `dateCompleted` int(10) unsigned NOT NULL default '0',
  `totalReward` double NOT NULL default '0',
  `tracking` tinyint(3) unsigned NOT NULL default '0',
  `pickupStationID` int(10) unsigned default NULL,
  `craterID` int(10) unsigned default NULL,
  `dropStationID` int(10) unsigned default NULL,
  `volume` double NOT NULL default '0',
  `pickupSolarSystemID` int(10) unsigned default NULL,
  `pickupRegionID` int(10) unsigned default NULL,
  `dropSolarSystemID` int(10) unsigned default NULL,
  `dropRegionID` int(10) unsigned default NULL,
  PRIMARY KEY  (`missionID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvCourierMissions` */

/*Table structure for table `srvCrpCharShares` */

DROP TABLE IF EXISTS `srvCrpCharShares`;

CREATE TABLE `srvCrpCharShares` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `corporationID` int(10) unsigned NOT NULL default '0',
  `shares` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`corporationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvCrpCharShares` */

/*Table structure for table `srvCrpOffices` */

DROP TABLE IF EXISTS `srvCrpOffices`;

CREATE TABLE `srvCrpOffices` (
  `corporationID` int(10) unsigned NOT NULL default '0',
  `stationID` int(10) unsigned NOT NULL default '0',
  `itemID` int(10) unsigned NOT NULL default '0',
  `typeID` int(10) unsigned NOT NULL default '0',
  `officeFolderID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`corporationID`,`officeFolderID`),
  KEY `itemID` (`itemID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvCrpOffices` */

/*Table structure for table `srvDroneState` */

DROP TABLE IF EXISTS `srvDroneState`;

CREATE TABLE `srvDroneState` (
  `droneID` int(10) unsigned NOT NULL default '0',
  `solarSystemID` int(10) unsigned NOT NULL default '0',
  `ownerID` int(10) unsigned NOT NULL default '0',
  `controllerID` int(10) unsigned NOT NULL default '0',
  `activityState` int(10) unsigned NOT NULL default '0',
  `typeID` int(10) unsigned NOT NULL default '0',
  `controllerOwnerID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`droneID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvDroneState` */

/*Table structure for table `srvEntity` */

DROP TABLE IF EXISTS `srvEntity`;

CREATE TABLE `srvEntity` (
  `itemID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `itemName` varchar(85) NOT NULL default '',
  `typeID` int(10) unsigned NOT NULL default '0',
  `ownerID` int(10) unsigned NOT NULL default '0',
  `locationID` int(10) unsigned NOT NULL default '0',
  `flag` int(10) unsigned NOT NULL default '0',
  `contraband` int(10) unsigned NOT NULL default '0',
  `singleton` int(10) unsigned NOT NULL default '0',
  `quantity` int(10) unsigned NOT NULL default '0',
  `x` double NOT NULL default '0',
  `y` double NOT NULL default '0',
  `z` double NOT NULL default '0',
  `customInfo` text,
  PRIMARY KEY  (`itemID`),
  KEY `typeID` (`typeID`)
) ENGINE=InnoDB AUTO_INCREMENT=14000000 DEFAULT CHARSET=utf8;

/*Data for the table `srvEntity` */

/*Table structure for table `srvEntity_attributes` */

DROP TABLE IF EXISTS `srvEntity_attributes`;

CREATE TABLE `srvEntity_attributes` (
  `itemID` int(10) unsigned NOT NULL default '0',
  `attributeID` int(10) unsigned NOT NULL default '0',
  `valueInt` int(10) default NULL,
  `valueFloat` double default NULL,
  PRIMARY KEY  (`itemID`,`attributeID`),
  KEY `attributeID` (`attributeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvEntity_attributes` */

/*Table structure for table `srvEntity_default_attributes` */

DROP TABLE IF EXISTS `srvEntity_default_attributes`;

CREATE TABLE `srvEntity_default_attributes` (
  `itemID` int(10) unsigned NOT NULL default '0',
  `attributeID` int(10) unsigned NOT NULL default '0',
  `valueInt` int(10) default NULL,
  `valueFloat` double default NULL,
  PRIMARY KEY  (`itemID`,`attributeID`),
  KEY `attributeID` (`attributeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvEntity_default_attributes` */

/*Table structure for table `srvEveMail` */

DROP TABLE IF EXISTS `srvEveMail`;

CREATE TABLE `srvEveMail` (
  `channelID` int(10) unsigned NOT NULL default '0',
  `messageID` int(10) unsigned NOT NULL auto_increment,
  `senderID` int(10) unsigned NOT NULL default '0',
  `subject` varchar(255) NOT NULL default '',
  `created` bigint(20) unsigned NOT NULL default '0',
  `read` tinyint(3) unsigned NOT NULL default '0',
  PRIMARY KEY  (`messageID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvEveMail` */

/*Table structure for table `srvEveMailDetails` */

DROP TABLE IF EXISTS `srvEveMailDetails`;

CREATE TABLE `srvEveMailDetails` (
  `attachmentID` int(10) unsigned NOT NULL auto_increment,
  `messageID` int(10) unsigned NOT NULL default '0',
  `mimeTypeID` int(10) unsigned NOT NULL default '0',
  `attachment` longtext NOT NULL,
  PRIMARY KEY  (`attachmentID`),
  KEY `messageID` (`messageID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvEveMailDetails` */

/*Table structure for table `srvInvBlueprints` */

DROP TABLE IF EXISTS `srvInvBlueprints`;

CREATE TABLE `srvInvBlueprints` (
  `blueprintID` int(10) unsigned NOT NULL,
  `copy` tinyint(1) unsigned NOT NULL default '0',
  `materialLevel` int(10) unsigned NOT NULL default '0',
  `productivityLevel` int(10) unsigned NOT NULL default '0',
  `licensedProductionRunsRemaining` int(10) NOT NULL default '-1',
  PRIMARY KEY  (`blueprintID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvInvBlueprints` */

/*Table structure for table `srvMarket_history_old` */

DROP TABLE IF EXISTS `srvMarket_history_old`;

CREATE TABLE `srvMarket_history_old` (
  `regionID` int(10) unsigned NOT NULL,
  `typeID` int(10) unsigned NOT NULL,
  `historyDate` bigint(20) unsigned NOT NULL,
  `lowPrice` double NOT NULL,
  `highPrice` double NOT NULL,
  `avgPrice` double NOT NULL,
  `volume` int(10) unsigned NOT NULL,
  `orders` int(10) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvMarket_history_old` */

/*Table structure for table `srvMarket_journal` */

DROP TABLE IF EXISTS `srvMarket_journal`;

CREATE TABLE `srvMarket_journal` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `refID` int(10) unsigned NOT NULL auto_increment,
  `transDate` bigint(20) default NULL,
  `refTypeID` int(10) unsigned NOT NULL default '0',
  `ownerID1` int(10) unsigned NOT NULL default '0',
  `ownerID2` int(10) unsigned NOT NULL default '0',
  `argID1` varchar(255) default NULL,
  `accountID` int(10) unsigned NOT NULL default '0',
  `amount` double NOT NULL default '0',
  `balance` double NOT NULL default '0',
  `reason` varchar(43) default NULL,
  `accountKey` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`refID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvMarket_journal` */

/*Table structure for table `srvMarket_orders` */

DROP TABLE IF EXISTS `srvMarket_orders`;

CREATE TABLE `srvMarket_orders` (
  `orderID` int(10) unsigned NOT NULL auto_increment,
  `typeID` int(10) unsigned NOT NULL default '0',
  `charID` int(10) unsigned NOT NULL default '0',
  `regionID` int(10) unsigned NOT NULL default '0',
  `stationID` int(10) unsigned NOT NULL default '0',
  `range` int(10) unsigned NOT NULL default '0',
  `bid` tinyint(3) unsigned NOT NULL default '0',
  `price` double NOT NULL default '0',
  `volEntered` int(10) unsigned NOT NULL default '0',
  `volRemaining` int(10) unsigned NOT NULL default '0',
  `issued` bigint(20) unsigned NOT NULL default '0',
  `orderState` int(10) unsigned NOT NULL default '0',
  `minVolume` int(10) unsigned NOT NULL default '0',
  `contraband` tinyint(3) unsigned NOT NULL default '0',
  `accountID` int(10) unsigned NOT NULL default '0',
  `duration` int(10) unsigned NOT NULL default '0',
  `isCorp` tinyint(3) unsigned NOT NULL default '0',
  `solarSystemID` int(11) NOT NULL default '0',
  `escrow` tinyint(3) unsigned NOT NULL default '0',
  `jumps` tinyint(4) NOT NULL default '1',
  PRIMARY KEY  (`orderID`),
  KEY `typeID` (`typeID`),
  KEY `regionID` (`regionID`),
  KEY `stationID` (`stationID`),
  KEY `solarSystemID` (`solarSystemID`),
  KEY `regionID_2` (`regionID`),
  KEY `typeID_2` (`typeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvMarket_orders` */

/*Table structure for table `srvMarket_transactions` */

DROP TABLE IF EXISTS `srvMarket_transactions`;

CREATE TABLE `srvMarket_transactions` (
  `transactionID` int(10) unsigned NOT NULL auto_increment,
  `transactionDateTime` bigint(20) unsigned NOT NULL default '0',
  `typeID` int(10) unsigned NOT NULL default '0',
  `quantity` int(10) unsigned NOT NULL default '0',
  `price` double NOT NULL default '0',
  `transactionType` int(10) unsigned NOT NULL default '0',
  `clientID` int(10) unsigned NOT NULL default '0',
  `regionID` int(10) unsigned NOT NULL default '0',
  `stationID` int(10) unsigned NOT NULL default '0',
  `corpTransaction` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`transactionID`),
  KEY `regionID` (`regionID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvMarket_transactions` */

/*Table structure for table `srvRamAssemblyLineStationCostLogs` */

DROP TABLE IF EXISTS `srvRamAssemblyLineStationCostLogs`;

CREATE TABLE `srvRamAssemblyLineStationCostLogs` (
  `assemblyLineTypeID` int(11) NOT NULL default '0',
  `stationID` int(11) NOT NULL default '0',
  `logDateTime` char(20) NOT NULL default '',
  `_usage` double NOT NULL default '0',
  `costPerHour` float NOT NULL default '0',
  PRIMARY KEY  (`assemblyLineTypeID`),
  KEY `stationID` (`stationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvRamAssemblyLineStationCostLogs` */

/*Table structure for table `srvRamJobs` */

DROP TABLE IF EXISTS `srvRamJobs`;

CREATE TABLE `srvRamJobs` (
  `jobID` int(10) unsigned NOT NULL auto_increment,
  `ownerID` int(10) unsigned NOT NULL,
  `installerID` int(10) unsigned NOT NULL,
  `assemblyLineID` int(10) unsigned NOT NULL,
  `installedItemID` int(10) unsigned NOT NULL,
  `installTime` bigint(20) unsigned NOT NULL,
  `beginProductionTime` bigint(20) unsigned NOT NULL,
  `pauseProductionTime` bigint(20) unsigned default NULL,
  `endProductionTime` bigint(20) unsigned NOT NULL,
  `description` varchar(250) NOT NULL default 'blah',
  `runs` int(10) unsigned NOT NULL,
  `outputFlag` int(10) unsigned NOT NULL,
  `completedStatusID` int(10) unsigned NOT NULL,
  `installedInSolarSystemID` int(10) unsigned NOT NULL,
  `licensedProductionRuns` int(10) default NULL,
  PRIMARY KEY  (`jobID`),
  KEY `RAMJOBS_ASSEMBLYLINES` (`assemblyLineID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvRamJobs` */

/*Table structure for table `srvRentalInfo` */

DROP TABLE IF EXISTS `srvRentalInfo`;

CREATE TABLE `srvRentalInfo` (
  `stationID` int(10) unsigned NOT NULL default '0',
  `slotNumber` int(10) unsigned NOT NULL default '0',
  `renterID` int(10) unsigned NOT NULL default '0',
  `typeID` int(10) unsigned NOT NULL default '0',
  `rentPeriodInDays` int(10) unsigned NOT NULL default '0',
  `periodCost` double NOT NULL default '0',
  `billID` int(10) unsigned NOT NULL default '0',
  `balanceDueDate` int(10) unsigned NOT NULL default '0',
  `discontinue` tinyint(3) unsigned NOT NULL default '0',
  `publiclyAvailable` tinyint(3) unsigned NOT NULL default '0',
  PRIMARY KEY  (`stationID`,`slotNumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvRentalInfo` */

/*Table structure for table `srvStatus` */

DROP TABLE IF EXISTS `srvStatus`;

CREATE TABLE `srvStatus` (
  `config_name` varchar(32) NOT NULL,
  `config_value` varchar(64) NOT NULL,
  UNIQUE KEY `config_name` (`config_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvStatus` */

/*Table structure for table `srvAccountApi` */

DROP TABLE IF EXISTS `srvAccountApi`;

CREATE TABLE `srvAccountApi` (
  `userID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `accountID` int(10) unsigned NOT NULL default '0',
  `fullKey` varchar(64) NOT NULL default '',
  `limitedKey` varchar(64) NOT NULL default '',
  `apiRole` int(10) NOT NULL default '0',
  PRIMARY KEY  (`userID`)
) ENGINE=InnoDB AUTO_INCREMENT=1000000 DEFAULT CHARSET=utf8;

/*Table structure for table `srvCrpStandings` */

DROP TABLE IF EXISTS `srvCrpStandings`;

CREATE TABLE `srvCrpStandings` (
  `corporationID` int(10) unsigned NOT NULL default '0',
  `fromID` int(10) unsigned NOT NULL default '0',
  `standing` double NOT NULL default '0',
  PRIMARY KEY  (`corporationID`,`fromID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `srvChrSkillQueue`;

CREATE TABLE `srvChrSkillQueue` (
	`characterID` INT(10) UNSIGNED NOT NULL,
	`orderIndex` INT(10) UNSIGNED NOT NULL,
	`typeID` INT(10) UNSIGNED NOT NULL,
	`level` INT(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- Mail subsystem
DROP TABLE IF EXISTS `srvMailLabel`;
CREATE TABLE `srvMailLabel` (
	`id` INT(10) NOT NULL AUTO_INCREMENT,
	`bit` INT(10) NOT NULL DEFAULT '0',
	`name` VARCHAR(100) NULL DEFAULT '0',
	`color` INT(11) NULL DEFAULT '0',
	`ownerID` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
	PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS srvMailMessage;

CREATE TABLE srvMailMessage
(
  messageID INT NOT NULL AUTO_INCREMENT,
  senderID BIGINT,
  toCharacterIDs TEXT,
  toListID INT,
  toCorpOrAllianceID INT,
  title TEXT,
  body BLOB,
  sentDate BIGINT,
  statusMask TINYINT,
  labelMask INT,
  unread TINYINT,
  PRIMARY KEY (messageID)
);

--
-- Table structure for table `srvAvatarColors`
--
DROP TABLE IF EXISTS `avatar_colors`;
DROP TABLE IF EXISTS `srvAvatarColors`;
CREATE TABLE IF NOT EXISTS `srvAvatarColors` (
	`charID` int(11) NOT NULL,
	`colorID` int(5) NOT NULL,
	`colorNameA` int(5) NOT NULL,
	`colorNameBC` int(5) NOT NULL,
	`weight` float(10) NOT NULL,
	`gloss` float(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Table structure for table `srvAvatarModifiers`
--
DROP TABLE IF EXISTS `avatar_modifiers`;
DROP TABLE IF EXISTS `srvAvatarModifiers`;
CREATE TABLE IF NOT EXISTS `srvAvatarModifiers` (
	`charID` int(11) NOT NULL,
	`modifierLocationID` int(5) NOT NULL,
	`paperdollResourceID` int(5) NOT NULL,
	`paperdollResourceVariation` int(5)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Table structure for table `srvAvatarSculpts`
--
DROP TABLE IF EXISTS `avatar_sculpts`;
DROP TABLE IF EXISTS `srvAvatarSculpts`;
CREATE TABLE IF NOT EXISTS `srvAvatarSculpts` (
	`charID` int(11) NOT NULL,
	`sculptLocationID` int(5) NOT NULL,
	`weightUpDown` float(5),
	`weightLeftRight` float(5),
	`weightForwardBack` float(5)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Table structure for table `srvAvatars`
--

DROP TABLE IF EXISTS `avatars`;
DROP TABLE IF EXISTS `srvAvatars`;
CREATE TABLE IF NOT EXISTS `srvAvatars` (
	`charID` int(11) NOT NULL,
	`hairDarkness` float(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Table structure for table `srvChrSkillHistory`
--

DROP TABLE IF EXISTS `chrSkillHistory`;
DROP TABLE IF EXISTS `srvChrSkillHistory`;

CREATE TABLE `srvChrSkillHistory` (
  `characterID` INT(10) UNSIGNED NOT NULL,
  `typeID` INT(10) UNSIGNED NOT NULL,
  `level` INT(10) UNSIGNED NOT NULL,
  `points` DOUBLE UNSIGNED NOT NULL,
  `spPerMin` DOUBLE UNSIGNED NOT NULL DEFAULT '0',
  `eventID` INT(10) UNSIGNED NOT NULL,
  `eventTime` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`characterID`, `typeID`, `level`, `eventTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

/*Table structure for table `srvChannels` */

DROP TABLE IF EXISTS `srvChannels`;

CREATE TABLE `srvChannels` (
  `channelID` int(10) unsigned NOT NULL auto_increment,
  `ownerID` int(10) unsigned NOT NULL default '0',
  `displayName` varchar(85) default NULL,
  `motd` text,
  `comparisonKey` varchar(11) default NULL,
  `memberless` tinyint(4) NOT NULL default '0',
  `password` varchar(100) default NULL,
  `mailingList` tinyint(4) NOT NULL default '0',
  `cspa` tinyint(4) NOT NULL default '0',
  `temporary` tinyint(4) NOT NULL default '0',
  `mode` tinyint(4) NOT NULL default '0',
  `subscribed` tinyint(4) NOT NULL default '0',
  `estimatedMemberCount` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`channelID`)
) ENGINE=InnoDB AUTO_INCREMENT=30001408 DEFAULT CHARSET=utf8;

/*Data for the table `srvChannels` */

insert  into `srvChannels`(`channelID`,`ownerID`,`displayName`,`motd`,`comparisonKey`,`memberless`,`password`,`mailingList`,`cspa`,`temporary`,`mode`,`subscribed`,`estimatedMemberCount`) VALUES
(1,1,'Help\\Rookie Help','rookie MOTD','rookiehelp',1,NULL,0,100,0,3,0,7777),
(2,1,'Help\\Help','help MOTD','help',1,NULL,0,100,0,3,0,6666),
(1000044,1000044,NULL,NULL,NULL,1,NULL,1,127,0,1,1,1252),
(1000115,1000115,NULL,NULL,NULL,1,NULL,1,127,0,1,1,1252),
(30001407,30001407,NULL,NULL,NULL,1,NULL,1,127,0,1,1,1252);

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;

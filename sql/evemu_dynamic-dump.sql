/*
SQLyog Community Edition- MySQL GUI v7.11
MySQL - 5.0.67-community-nt : Database - eve_evemu_dynamic
*********************************************************************
*/


/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

/*Table structure for table `account` */

DROP TABLE IF EXISTS `account`;

-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `accountID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `accountName` varchar(43) NOT NULL DEFAULT '',
  `password` varchar(43) NOT NULL DEFAULT '',
  `hash` tinyblob,
  `role` bigint(20) unsigned NOT NULL DEFAULT '0',
  `online` tinyint(1) NOT NULL DEFAULT '0',
  `banned` tinyint(1) NOT NULL DEFAULT '0',
  `logonCount` int(10) unsigned NOT NULL DEFAULT '0',
  `lastLogin` timestamp NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`accountID`),
  UNIQUE KEY `accountName` (`accountName`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

/*Data for the table `account` */

/*Table structure for table `alliance_ShortNames` */

DROP TABLE IF EXISTS `alliance_ShortNames`;

CREATE TABLE `alliance_ShortNames` (
  `allianceID` int(10) unsigned NOT NULL default '0',
  `shortName` text NOT NULL,
  PRIMARY KEY  (`allianceID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `alliance_ShortNames` */

/*Table structure for table `billsPayable` */

DROP TABLE IF EXISTS `billsPayable`;

CREATE TABLE `billsPayable` (
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

/*Data for the table `billsPayable` */

/*Table structure for table `billsReceivable` */

DROP TABLE IF EXISTS `billsReceivable`;

CREATE TABLE `billsReceivable` (
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

/*Data for the table `billsReceivable` */

/*Table structure for table `bookmarks` */

DROP TABLE IF EXISTS `bookmarks`;

CREATE TABLE `bookmarks` (
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

/*Data for the table `bookmarks` */

DROP TABLE IF EXISTS `bookmarkFolders`;

CREATE TABLE `bookmarkFolders` (
	`folderID` int (10),
	`folderName` varchar (255),
	`ownerID` int (10),
	`creatorID` int (10),
	PRIMARY KEY (`folderID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `cacheLocations` */

DROP TABLE IF EXISTS `cacheLocations`;

CREATE TABLE `cacheLocations` (
  `locationID` int(10) unsigned NOT NULL default '0',
  `locationName` varchar(100) NOT NULL default '',
  `x` double NOT NULL default '0',
  `y` double NOT NULL default '0',
  `z` double NOT NULL default '0',
  PRIMARY KEY  (`locationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `cacheLocations` */

/*Table structure for table `cacheOwners` */

DROP TABLE IF EXISTS `cacheOwners`;

CREATE TABLE `cacheOwners` (
  `ownerID` int(10) unsigned NOT NULL default '0',
  `ownerName` varchar(100) NOT NULL default '',
  `typeID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`ownerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `cacheOwners` */

/*Table structure for table `channelChars` */

DROP TABLE IF EXISTS `channelChars`;

CREATE TABLE `channelChars` (
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

/*Data for the table `channelChars` */

/*Table structure for table `channelMods` */

DROP TABLE IF EXISTS `channelMods`;

CREATE TABLE `channelMods` (
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

/*Data for the table `channelMods` */

/*Table structure for table `character_` */

DROP TABLE IF EXISTS `character_`;

CREATE TABLE `character_` (
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

/*Data for the table `character_` */

/*Table structure for table `chrApplications` */

DROP TABLE IF EXISTS `chrApplications`;

CREATE TABLE `chrApplications` (
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

/*Data for the table `chrApplications` */

/*Table structure for table `chrCertificates` */
DROP TABLE IF EXISTS `chrCertificates`;

CREATE TABLE IF NOT EXISTS `chrCertificates` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `characterID` int(10) NOT NULL,
  `certificateID` int(10) NOT NULL,
  `grantDate` bigint(20) NOT NULL,
  `visibilityFlags` int(10) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

/*Table structure for table `chrEmployment` */

DROP TABLE IF EXISTS `chrEmployment`;

CREATE TABLE `chrEmployment` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `corporationID` int(10) unsigned NOT NULL default '0',
  `startDate` bigint(20) unsigned NOT NULL default '0',
  `deleted` tinyint(4) NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`corporationID`,`startDate`),
  KEY `corporationID` (`corporationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `chrEmployment` */

/*Table structure for table `chrMissionState` */

DROP TABLE IF EXISTS `chrMissionState`;

CREATE TABLE `chrMissionState` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `missionID` int(10) unsigned NOT NULL default '0',
  `missionState` tinyint(3) unsigned NOT NULL default '0',
  `expirationTime` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`missionID`),
  KEY `missionID` (`missionID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `chrMissionState` */

/*Table structure for table `chrNotes` */

DROP TABLE IF EXISTS `chrNotes`;

CREATE TABLE `chrNotes` (
  `itemID` int(10) unsigned NOT NULL default '0',
  `ownerID` int(10) unsigned default NULL,
  `note` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `chrNotes` */

/*Table structure for table `chrNPCStandings` */

DROP TABLE IF EXISTS `chrNPCStandings`;

CREATE TABLE `chrNPCStandings` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `fromID` int(10) unsigned NOT NULL default '0',
  `standing` double NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`fromID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `chrNPCStandings` */

/*Table structure for table `chrOffers` */

DROP TABLE IF EXISTS `chrOffers`;

CREATE TABLE `chrOffers` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `offerID` int(10) unsigned NOT NULL default '0',
  `expirationTime` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`offerID`),
  KEY `offerID` (`offerID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `chrOffers` */

/*Table structure for table `chrOwnerNote` */

DROP TABLE IF EXISTS `chrOwnerNote`;

CREATE TABLE `chrOwnerNote` (
  `noteID` int(10) unsigned NOT NULL auto_increment,
  `ownerID` int(10) unsigned NOT NULL,
  `label` text,
  `note` text,
  UNIQUE KEY `noteID` (`noteID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `chrOwnerNote` */

/*Table structure for table `chrStandings` */

DROP TABLE IF EXISTS `chrStandings`;

CREATE TABLE `chrStandings` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `toID` int(10) unsigned NOT NULL default '0',
  `standing` double NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`toID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `chrStandings` */

/*Table structure for table `corporation` */

DROP TABLE IF EXISTS `corporation`;

CREATE TABLE `corporation` (
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

/*Data for the table `corporation` */

/*Table structure for table `courierMissions` */

DROP TABLE IF EXISTS `courierMissions`;

CREATE TABLE `courierMissions` (
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

/*Data for the table `courierMissions` */

/*Table structure for table `crpCharShares` */

DROP TABLE IF EXISTS `crpCharShares`;

CREATE TABLE `crpCharShares` (
  `characterID` int(10) unsigned NOT NULL default '0',
  `corporationID` int(10) unsigned NOT NULL default '0',
  `shares` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`characterID`,`corporationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `crpCharShares` */

/*Table structure for table `crpOffices` */

DROP TABLE IF EXISTS `crpOffices`;

CREATE TABLE `crpOffices` (
  `corporationID` int(10) unsigned NOT NULL default '0',
  `stationID` int(10) unsigned NOT NULL default '0',
  `itemID` int(10) unsigned NOT NULL default '0',
  `typeID` int(10) unsigned NOT NULL default '0',
  `officeFolderID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`corporationID`,`officeFolderID`),
  KEY `itemID` (`itemID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `crpOffices` */

/*Table structure for table `droneState` */

DROP TABLE IF EXISTS `droneState`;

CREATE TABLE `droneState` (
  `droneID` int(10) unsigned NOT NULL default '0',
  `solarSystemID` int(10) unsigned NOT NULL default '0',
  `ownerID` int(10) unsigned NOT NULL default '0',
  `controllerID` int(10) unsigned NOT NULL default '0',
  `activityState` int(10) unsigned NOT NULL default '0',
  `typeID` int(10) unsigned NOT NULL default '0',
  `controllerOwnerID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`droneID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `droneState` */

/*Table structure for table `entity` */

DROP TABLE IF EXISTS `entity`;

CREATE TABLE `entity` (
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

/*Data for the table `entity` */

/*Table structure for table `entity_attributes` */

DROP TABLE IF EXISTS `entity_attributes`;

CREATE TABLE `entity_attributes` (
  `itemID` int(10) unsigned NOT NULL default '0',
  `attributeID` int(10) unsigned NOT NULL default '0',
  `valueInt` int(10) default NULL,
  `valueFloat` double default NULL,
  PRIMARY KEY  (`itemID`,`attributeID`),
  KEY `attributeID` (`attributeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `entity_attributes` */

/*Table structure for table `entity_default_attributes` */

DROP TABLE IF EXISTS `entity_default_attributes`;

CREATE TABLE `entity_default_attributes` (
  `itemID` int(10) unsigned NOT NULL default '0',
  `attributeID` int(10) unsigned NOT NULL default '0',
  `valueInt` int(10) default NULL,
  `valueFloat` double default NULL,
  PRIMARY KEY  (`itemID`,`attributeID`),
  KEY `attributeID` (`attributeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `entity_default_attributes` */

/*Table structure for table `eveMail` */

DROP TABLE IF EXISTS `eveMail`;

CREATE TABLE `eveMail` (
  `channelID` int(10) unsigned NOT NULL default '0',
  `messageID` int(10) unsigned NOT NULL auto_increment,
  `senderID` int(10) unsigned NOT NULL default '0',
  `subject` varchar(255) NOT NULL default '',
  `created` bigint(20) unsigned NOT NULL default '0',
  `read` tinyint(3) unsigned NOT NULL default '0',
  PRIMARY KEY  (`messageID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `eveMail` */

/*Table structure for table `eveMailDetails` */

DROP TABLE IF EXISTS `eveMailDetails`;

CREATE TABLE `eveMailDetails` (
  `attachmentID` int(10) unsigned NOT NULL auto_increment,
  `messageID` int(10) unsigned NOT NULL default '0',
  `mimeTypeID` int(10) unsigned NOT NULL default '0',
  `attachment` longtext NOT NULL,
  PRIMARY KEY  (`attachmentID`),
  KEY `messageID` (`messageID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `eveMailDetails` */

/*Table structure for table `invBlueprints` */

DROP TABLE IF EXISTS `invBlueprints`;

CREATE TABLE `invBlueprints` (
  `blueprintID` int(10) unsigned NOT NULL,
  `copy` tinyint(1) unsigned NOT NULL default '0',
  `materialLevel` int(10) unsigned NOT NULL default '0',
  `productivityLevel` int(10) unsigned NOT NULL default '0',
  `licensedProductionRunsRemaining` int(10) NOT NULL default '-1',
  PRIMARY KEY  (`blueprintID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `invBlueprints` */

/*Table structure for table `market_history_old` */

DROP TABLE IF EXISTS `market_history_old`;

CREATE TABLE `market_history_old` (
  `regionID` int(10) unsigned NOT NULL,
  `typeID` int(10) unsigned NOT NULL,
  `historyDate` bigint(20) unsigned NOT NULL,
  `lowPrice` double NOT NULL,
  `highPrice` double NOT NULL,
  `avgPrice` double NOT NULL,
  `volume` int(10) unsigned NOT NULL,
  `orders` int(10) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `market_history_old` */

/*Table structure for table `market_journal` */

DROP TABLE IF EXISTS `market_journal`;

CREATE TABLE `market_journal` (
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

/*Data for the table `market_journal` */

/*Table structure for table `market_orders` */

DROP TABLE IF EXISTS `market_orders`;

CREATE TABLE `market_orders` (
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

/*Data for the table `market_orders` */

/*Table structure for table `market_transactions` */

DROP TABLE IF EXISTS `market_transactions`;

CREATE TABLE `market_transactions` (
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

/*Data for the table `market_transactions` */

/*Table structure for table `ramAssemblyLineStationCostLogs` */

DROP TABLE IF EXISTS `ramAssemblyLineStationCostLogs`;

CREATE TABLE `ramAssemblyLineStationCostLogs` (
  `assemblyLineTypeID` int(11) NOT NULL default '0',
  `stationID` int(11) NOT NULL default '0',
  `logDateTime` char(20) NOT NULL default '',
  `_usage` double NOT NULL default '0',
  `costPerHour` float NOT NULL default '0',
  PRIMARY KEY  (`assemblyLineTypeID`),
  KEY `stationID` (`stationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `ramAssemblyLineStationCostLogs` */

/*Table structure for table `ramJobs` */

DROP TABLE IF EXISTS `ramJobs`;

CREATE TABLE `ramJobs` (
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

/*Data for the table `ramJobs` */

/*Table structure for table `rentalInfo` */

DROP TABLE IF EXISTS `rentalInfo`;

CREATE TABLE `rentalInfo` (
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

/*Data for the table `rentalInfo` */

/*Table structure for table `srvStatus` */

DROP TABLE IF EXISTS `srvStatus`;

CREATE TABLE `srvStatus` (
  `config_name` varchar(32) NOT NULL,
  `config_value` varchar(64) NOT NULL,
  UNIQUE KEY `config_name` (`config_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `srvStatus` */

/*Table structure for table `accountApi` */

DROP TABLE IF EXISTS `accountApi`;

CREATE TABLE `accountApi` (
  `userID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `accountID` int(10) unsigned NOT NULL default '0',
  `fullKey` varchar(64) NOT NULL default '',
  `limitedKey` varchar(64) NOT NULL default '',
  `apiRole` int(10) NOT NULL default '0',
  PRIMARY KEY  (`userID`)
) ENGINE=InnoDB AUTO_INCREMENT=1000000 DEFAULT CHARSET=utf8;

/*Table structure for table `crpStandings` */

DROP TABLE IF EXISTS `crpStandings`;

CREATE TABLE `crpStandings` (
  `corporationID` int(10) unsigned NOT NULL default '0',
  `fromID` int(10) unsigned NOT NULL default '0',
  `standing` double NOT NULL default '0',
  PRIMARY KEY  (`corporationID`,`fromID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- No longer needed
DROP TABLE IF EXISTS entityStatic;

DROP TABLE IF EXISTS `chrSkillQueue`;

CREATE TABLE `chrSkillQueue` (
	`characterID` INT(10) UNSIGNED NOT NULL,
	`orderIndex` INT(10) UNSIGNED NOT NULL,
	`typeID` INT(10) UNSIGNED NOT NULL,
	`level` INT(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Mail subsystem
DROP TABLE IF EXISTS `mailLabel`;
CREATE TABLE `mailLabel` (
	`id` INT(10) NOT NULL AUTO_INCREMENT,
	`bit` INT(10) NOT NULL DEFAULT '0',
	`name` VARCHAR(100) NULL DEFAULT '0',
	`color` INT(11) NULL DEFAULT '0',
	`ownerID` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
	PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;

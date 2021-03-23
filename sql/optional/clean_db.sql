/* clean_db.sql
 *
 * this will erase all player-created data in db, and *SHOULD* result in a clean install.
 *  NOTE:  this WILL NOT delete accounts.  un-comment first 2 lines to delete accounts also.
 */

-- TRUNCATE TABLE `account`;
-- ALTER TABLE `account` auto_increment = 1;
TRUNCATE TABLE `agtOffers`;
ALTER TABLE `agtOffers` auto_increment = 1;
TRUNCATE TABLE `alnAlliance`;
TRUNCATE TABLE `alnApplications`;
TRUNCATE TABLE `alnContacts`;
TRUNCATE TABLE `alnLabels`;
TRUNCATE TABLE `avatars`;
TRUNCATE TABLE `avatar_colors`;
TRUNCATE TABLE `avatar_modifiers`;
TRUNCATE TABLE `avatar_sculpts`;
TRUNCATE TABLE `billsPayable`;
TRUNCATE TABLE `billsReceivable`;
TRUNCATE TABLE `bookmarks`;
ALTER TABLE `bookmarks` auto_increment = 1;
TRUNCATE TABLE `bookmarkFolders`;
TRUNCATE TABLE `cacheOwners`;
TRUNCATE TABLE `channelChars`;
TRUNCATE TABLE `channelMods`;
TRUNCATE TABLE `channels`;
TRUNCATE TABLE `chrCertificates`;
ALTER TABLE `chrCertificates` auto_increment = 1;
TRUNCATE TABLE `chrCharacters`;
ALTER TABLE `chrCharacters` auto_increment = 90000000;
TRUNCATE TABLE `chrCharacterAttributes`;
TRUNCATE TABLE `chrContacts`;
TRUNCATE TABLE `chrEmployment`;
TRUNCATE TABLE `chrKillTable`;
ALTER TABLE `chrKillTable` auto_increment = 1;
TRUNCATE TABLE `chrLabels`;
TRUNCATE TABLE `chrMedals`;
TRUNCATE TABLE `chrNotes`;
TRUNCATE TABLE `chrOwnerNote`;
TRUNCATE TABLE `chrPausedSkillQueue`;
TRUNCATE TABLE `chrPortraitData`;
TRUNCATE TABLE `chrShipFittings`;
TRUNCATE TABLE `chrSkillHistory`;
ALTER TABLE `chrSkillHistory` auto_increment = 1;
TRUNCATE TABLE `chrSkillQueue`;
TRUNCATE TABLE `chrVisitedSystems`;
TRUNCATE TABLE `crpAdRegistry`;
ALTER TABLE `crpAdRegistry` auto_increment = 1;
TRUNCATE TABLE `crpApplications`;
ALTER TABLE `crpApplications` auto_increment = 1;
TRUNCATE TABLE `crpBulletins`;
TRUNCATE TABLE `crpContacts`;
DELETE FROM `crpCorporation` WHERE `corporationID` > 90000000;
ALTER TABLE `crpCorporation` auto_increment = 98000000;
TRUNCATE TABLE `crpLabels`;
TRUNCATE TABLE `crpLockedItems`;
TRUNCATE TABLE `crpItemEvent`;
ALTER TABLE `crpItemEvent` auto_increment = 1;
TRUNCATE TABLE `crpMedals`;
ALTER TABLE `crpMedals` auto_increment = 1;
TRUNCATE TABLE `crpRecruiters`;
TRUNCATE TABLE `crpRoleHistroy`;
TRUNCATE TABLE `crpRoleTitles`;
TRUNCATE TABLE `crpShares`;
ALTER TABLE `crpShares` auto_increment = 1;
TRUNCATE TABLE `crpVoteItems`;
ALTER TABLE `crpVoteItems` auto_increment = 1;
TRUNCATE TABLE `crpVoteOptions`;
ALTER TABLE `crpVoteOptions` auto_increment = 1;
TRUNCATE TABLE `crpWalletDivisons`;
TRUNCATE TABLE `droneState`;
TRUNCATE TABLE `dunActive`;
TRUNCATE TABLE `entity`;
ALTER TABLE `entity` auto_increment = 140000000;
TRUNCATE TABLE `entity_attributes`;
TRUNCATE TABLE `eveMail`;
ALTER TABLE `eveMail` auto_increment = 1;
TRUNCATE TABLE `eveMailDetails`;
ALTER TABLE `eveMailDetails` auto_increment = 1;
DELETE FROM `eveStaticOwners` WHERE `ownerID`> 90000000;
TRUNCATE TABLE `invBlueprints`;
TRUNCATE TABLE `jnlCharacters`;
ALTER TABLE `jnlCharacters` auto_increment = 1;
TRUNCATE TABLE `jnlCorporations`;
ALTER TABLE `jnlCorporations` auto_increment = 1;
TRUNCATE TABLE `mailLabel`;
TRUNCATE TABLE `mailList`;
TRUNCATE TABLE `mailListUsers`;
TRUNCATE TABLE `mailMessage`;
TRUNCATE TABLE `mailStatus`;
TRUNCATE TABLE `mapDynamicData`;
TRUNCATE TABLE `mktData`;
TRUNCATE TABLE `mktHistory`;
TRUNCATE TABLE `mktOrders`;
ALTER TABLE `mktOrders` auto_increment = 1;
TRUNCATE TABLE `mktTransactions`;
ALTER TABLE `mktTransactions` auto_increment = 1;
TRUNCATE TABLE `mktUpdates`;
TRUNCATE TABLE `piCCPin`;
TRUNCATE TABLE `piECUHeads`;
TRUNCATE TABLE `piLaunches`;
TRUNCATE TABLE `piLinks`;
TRUNCATE TABLE `piPinContents`;
TRUNCATE TABLE `piPins`;
TRUNCATE TABLE `piPlanets`;
TRUNCATE TABLE `piRoutes`;
TRUNCATE TABLE `posCustomsOfficeData`;
TRUNCATE TABLE `posJumpBridgeData`;
TRUNCATE TABLE `posStructureData`;
TRUNCATE TABLE `posTowerData`;
TRUNCATE TABLE `ramJobs`;
TRUNCATE TABLE `rentalInfo`;
TRUNCATE TABLE `repStandingChanges`;
DELETE FROM `repStandings` WHERE toID > 90000000;
DELETE FROM `repStandings` WHERE fromID > 90000000;
TRUNCATE TABLE `shipInsurance`;
TRUNCATE TABLE `srvStatisticData`;
TRUNCATE TABLE `srvStatisticHistory`;
TRUNCATE TABLE `staOffices`;
ALTER TABLE `staOffices` auto_increment = 100000000;
TRUNCATE TABLE `sysAsteroids`;
ALTER TABLE `sysAsteroids` auto_increment = 450000000;
TRUNCATE TABLE `sysSignatures`;
TRUNCATE TABLE `webBounties`;
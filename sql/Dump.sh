#/bin/bash
MYSQL_USER=nick
MYSQL_PASS=none
DB_NAME=evemu

unset blacklist

_() { blacklist="${blacklist}${blacklist+}${*}"; }

# Add any tables that should be dumped with no data.
_ "agtOffers alnAlliance alnContacts alnLabels avatars avatar_colors"
_ "avatar_modifiers avatar_sculpts billsPayable billsReceivable bookmarks"
_ "bookmarkFolders cacheOwners channelChars channelMods channels"
_ "chrCertificates chrCharacters chrCharacterAttributes chrContacts chrEmployment"
_ "chrKillTable chrLabels chrNotes chrOwnerNote chrPausedSkillQueue"
_ "chrShipFittings chrSkillHistory chrSkillQueue chrVisitedSystems crpAdRegistry"
_ "crpApplications crpBulletins crpContacts crpLabels crpLockedItems"
_ "crpItemEvent crpRecruiters crpRoleHistroy crpRoleTitles crpShares"
_ "crpVoteItems crpWalletDivisons droneState dunActive entity"
_ "entity_attributes eveMail eveMailDetails invBlueprints jnlCharacters"
_ "jnlCorporations mailLabel mailList mailListUsers mailMessage"
_ "mailStatus mapDynamicData mktHistory mktOrders mktTransactions"
_ "piCCPin piECUHeads piLaunches piLinks piPinContents"
_ "piPins piPlanets piRoutes posCustomOfficeData posJumpBridgeData"
_ "posStructureData posTowerData ramJobs rentalInfo repStandingChanges"
_ "shipInsurance srvStatisticData srvStatisticHistory staOffices sysAsteroids"
_ "sysSignatures webBounties"

SQL_STRING="SHOW TABLES;"
# Pipe the SQL into mysql
TABLES=$(echo $SQL_STRING | mysql -u$MYSQL_USER -p$MYSQL_PASS $DB_NAME -Bs)

#mkdir tables

#echo $TABLES

for i in ${TABLES} ; do
	if [[ ${blacklist} == *${i}* ]]; then
		echo "Dumping $i without data"
		mysqldump --add-drop-table -d -u $MYSQL_USER -p$MYSQL_PASS $DB_NAME $i > "tables/${i}.sql"
	else
		echo "Dumping $i"
		mysqldump --add-drop-table -u $MYSQL_USER -p$MYSQL_PASS $DB_NAME $i > "tables/${i}.sql"
	fi
done

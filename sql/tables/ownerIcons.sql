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
-- Table structure for table `ownerIcons`
--

DROP TABLE IF EXISTS `ownerIcons`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ownerIcons` (
  `ownerID` int(11) NOT NULL DEFAULT '0',
  `iconID` int(11) DEFAULT NULL,
  PRIMARY KEY (`ownerID`),
  KEY `iconID` (`iconID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ownerIcons`
--

LOCK TABLES `ownerIcons` WRITE;
/*!40000 ALTER TABLE `ownerIcons` DISABLE KEYS */;
INSERT INTO `ownerIcons` VALUES (500021,0),(500013,96),(500016,1004),(500006,1434),(500009,1437),(500001,1439),(500002,1440),(500004,1441),(500012,1441),(500003,1442),(1000077,1449),(1000045,1453),(1000044,1455),(1000115,1456),(1000002,1465),(1000050,1466),(1000051,1467),(1000052,1468),(1000053,1469),(1000054,1470),(1000055,1471),(1000056,1472),(1000057,1473),(1000058,1474),(1000059,1475),(1000060,1476),(1000061,1477),(1000062,1478),(1000063,1479),(1000064,1480),(1000065,1481),(1000066,1482),(1000067,1483),(1000068,1484),(1000069,1485),(1000070,1486),(1000071,1487),(1000072,1488),(1000073,1489),(1000074,1490),(1000075,1491),(1000076,1492),(1000078,1494),(1000079,1495),(1000080,1496),(1000081,1497),(1000082,1498),(1000083,1499),(1000084,1500),(1000085,1501),(1000086,1502),(1000087,1503),(1000088,1504),(1000089,1505),(1000090,1506),(1000091,1507),(1000092,1508),(1000093,1509),(1000094,1510),(1000095,1511),(1000096,1512),(1000097,1513),(1000098,1514),(1000099,1515),(1000100,1516),(1000101,1517),(1000102,1518),(1000103,1519),(1000104,1520),(1000105,1521),(1000106,1522),(1000107,1523),(1000108,1524),(1000109,1525),(1000110,1526),(1000111,1527),(1000112,1528),(1000113,1529),(1000114,1530),(1000116,1532),(1000117,1533),(1000118,1534),(1000119,1535),(1000120,1536),(1000025,1537),(1000121,1537),(1000122,1538),(1000123,1539),(1000124,1540),(1000125,1541),(1000126,1542),(1000127,1543),(1000128,1544),(1000129,1545),(1000130,1546),(1000131,1547),(1000132,1548),(1000133,1549),(1000134,1550),(1000135,1551),(1000136,1552),(1000137,1553),(1000138,1554),(1000139,1555),(1000140,1556),(1000141,1557),(1000142,1558),(1000143,1559),(1000144,1560),(1000145,1561),(1000146,1562),(1000147,1563),(1000148,1564),(1000149,1565),(1000150,1566),(1000151,1567),(1000152,1568),(1000153,1569),(1000154,1570),(1000155,1571),(1000156,1572),(1000157,1573),(1000158,1574),(1000159,1575),(1000160,1576),(1000161,1577),(1000162,1578),(1000163,1579),(1000164,1580),(1000003,1581),(1000004,1582),(1000005,1583),(1000006,1584),(1000007,1585),(1000008,1586),(1000009,1587),(1000010,1588),(1000011,1589),(1000012,1590),(1000013,1591),(1000014,1592),(1000015,1593),(1000016,1594),(1000017,1595),(1000018,1596),(1000019,1597),(1000020,1598),(1000021,1599),(1000022,1600),(1000023,1601),(1000024,1602),(1000026,1604),(1000027,1605),(1000028,1606),(1000029,1607),(1000030,1608),(1000031,1609),(1000032,1610),(1000033,1611),(1000034,1612),(1000035,1613),(1000036,1614),(1000037,1615),(1000038,1616),(1000039,1617),(1000040,1618),(1000041,1619),(1000042,1620),(1000043,1621),(1000046,1624),(1000047,1625),(1000048,1626),(1000049,1627),(500010,1630),(500014,1720),(500018,1722),(500005,2195),(1000179,3369),(1000180,3370),(1000181,3371),(1000182,3372),(500007,10172),(500008,10173),(500011,10174),(500015,10175),(500017,10176),(500019,10177),(500020,10178),(1000165,10180),(1000166,10181),(1000167,10182),(1000168,10183),(1000169,10184),(1000170,10185),(1000171,10186),(1000172,10187),(1000178,10191),(1000177,10192);
/*!40000 ALTER TABLE `ownerIcons` ENABLE KEYS */;
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

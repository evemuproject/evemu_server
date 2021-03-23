-- phpMyAdmin SQL Dump
-- version 4.4.15.10
-- https://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 10, 2019 at 09:17 PM
-- Server version: 10.0.36-MariaDB
-- PHP Version: 5.6.36

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `EVE_Crucible`
--

-- --------------------------------------------------------

--
-- Table structure for table `srvStatisticData`
--

CREATE TABLE IF NOT EXISTS `srvStatisticData` (
  `timeStamp` bigint(20) NOT NULL DEFAULT '0' COMMENT 'filetime',
  `timeSpan` mediumint(6) unsigned NOT NULL DEFAULT '0' COMMENT 'in minutes',
  `pcShots` int(10) unsigned NOT NULL DEFAULT '0',
  `pcMissiles` int(10) unsigned NOT NULL DEFAULT '0',
  `ramJobs` int(11) NOT NULL DEFAULT '0',
  `shipsSalvaged` smallint(5) unsigned NOT NULL DEFAULT '0',
  `pcBounties` float NOT NULL DEFAULT '0',
  `npcBounties` float NOT NULL DEFAULT '0',
  `oreMined` float NOT NULL DEFAULT '0',
  `iskMarket` float NOT NULL DEFAULT '0',
  `probesLaunched` mediumint(5) unsigned NOT NULL DEFAULT '0',
  `sitesScanned` mediumint(5) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Current Data for graphing player activity over period of time';

--
-- Indexes for dumped tables
--

--
-- Indexes for table `srvStatisticData`
--
ALTER TABLE `srvStatisticData`
  ADD PRIMARY KEY (`timeStamp`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

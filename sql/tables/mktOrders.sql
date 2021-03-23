-- phpMyAdmin SQL Dump
-- version 4.4.15.10
-- https://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 10, 2019 at 09:06 PM
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
-- Table structure for table `mktOrders`
--

CREATE TABLE IF NOT EXISTS `mktOrders` (
  `orderID` int(10) unsigned NOT NULL,
  `typeID` int(10) unsigned NOT NULL DEFAULT '0',
  `ownerID` int(10) unsigned NOT NULL DEFAULT '0',
  `regionID` int(10) unsigned NOT NULL DEFAULT '0',
  `stationID` int(10) unsigned NOT NULL DEFAULT '0',
  `orderRange` int(5) unsigned NOT NULL DEFAULT '0',
  `bid` tinyint(1) NOT NULL DEFAULT '0',
  `price` double NOT NULL DEFAULT '0',
  `volEntered` int(10) unsigned NOT NULL DEFAULT '0',
  `volRemaining` int(10) unsigned NOT NULL DEFAULT '0',
  `issued` bigint(20) unsigned NOT NULL DEFAULT '0',
  `orderState` int(10) unsigned NOT NULL DEFAULT '0',
  `minVolume` int(10) unsigned NOT NULL DEFAULT '0',
  `contraband` bit(1) NOT NULL DEFAULT b'0',
  `accountID` int(10) unsigned NOT NULL DEFAULT '0',
  `duration` int(5) unsigned NOT NULL DEFAULT '0',
  `isCorp` bit(1) NOT NULL DEFAULT b'0',
  `solarSystemID` int(11) NOT NULL DEFAULT '0',
  `escrow` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `jumps` smallint(4) NOT NULL DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `mktOrders`
--
ALTER TABLE `mktOrders`
  ADD PRIMARY KEY (`orderID`),
  ADD KEY `typeID` (`typeID`),
  ADD KEY `regionID` (`regionID`),
  ADD KEY `stationID` (`stationID`),
  ADD KEY `solarSystemID` (`solarSystemID`),
  ADD KEY `regionID_2` (`regionID`),
  ADD KEY `typeID_2` (`typeID`),
  ADD KEY `regionID_3` (`regionID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `mktOrders`
--
ALTER TABLE `mktOrders`
  MODIFY `orderID` int(10) unsigned NOT NULL AUTO_INCREMENT;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

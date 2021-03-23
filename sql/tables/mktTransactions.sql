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
-- Table structure for table `mktTransactions`
--

CREATE TABLE IF NOT EXISTS `mktTransactions` (
  `transactionID` int(10) unsigned NOT NULL,
  `transactionDate` bigint(20) unsigned NOT NULL DEFAULT '0',
  `typeID` int(10) unsigned NOT NULL DEFAULT '0',
  `keyID` smallint(4) NOT NULL DEFAULT '1000',
  `quantity` mediumint(10) unsigned NOT NULL DEFAULT '0',
  `price` double NOT NULL DEFAULT '0',
  `transactionType` bit(1) NOT NULL DEFAULT b'0',
  `clientID` int(10) unsigned NOT NULL DEFAULT '0',
  `regionID` int(10) unsigned NOT NULL DEFAULT '0',
  `stationID` int(10) unsigned NOT NULL DEFAULT '0',
  `corpTransaction` bit(1) NOT NULL DEFAULT b'0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `mktTransactions`
--
ALTER TABLE `mktTransactions`
  ADD PRIMARY KEY (`transactionID`),
  ADD KEY `regionID` (`regionID`),
  ADD KEY `transactionID` (`transactionID`),
  ADD KEY `regionID_2` (`regionID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `mktTransactions`
--
ALTER TABLE `mktTransactions`
  MODIFY `transactionID` int(10) unsigned NOT NULL AUTO_INCREMENT;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

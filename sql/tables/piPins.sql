-- phpMyAdmin SQL Dump
-- version 4.4.15.10
-- https://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 26, 2019 at 02:43 PM
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
-- Table structure for table `piPins`
--

CREATE TABLE IF NOT EXISTS `piPins` (
  `ccPinID` int(10) NOT NULL DEFAULT '0',
  `pinID` int(10) NOT NULL DEFAULT '0',
  `typeID` smallint(6) NOT NULL DEFAULT '0',
  `ownerID` int(10) NOT NULL DEFAULT '0',
  `state` tinyint(1) NOT NULL DEFAULT '1',
  `level` smallint(3) NOT NULL DEFAULT '0',
  `latitude` float NOT NULL DEFAULT '0',
  `longitude` float NOT NULL DEFAULT '0',
  `isCommandCenter` bit(1) NOT NULL DEFAULT b'0',
  `isLaunchable` bit(1) NOT NULL DEFAULT b'0',
  `isProcess` bit(1) NOT NULL DEFAULT b'0',
  `isStorage` bit(1) NOT NULL DEFAULT b'0',
  `isECU` bit(1) NOT NULL DEFAULT b'0',
  `hasReceivedInputs` bit(1) NOT NULL DEFAULT b'0',
  `receivedInputsLastCycle` bit(1) NOT NULL DEFAULT b'0',
  `schematicID` smallint(3) NOT NULL DEFAULT '0',
  `programType` smallint(3) NOT NULL DEFAULT '0',
  `cycleTime` bigint(20) NOT NULL DEFAULT '0',
  `launchTime` bigint(20) NOT NULL DEFAULT '0',
  `expiryTime` bigint(20) NOT NULL DEFAULT '0',
  `installTime` bigint(20) NOT NULL DEFAULT '0',
  `lastRunTime` bigint(20) NOT NULL DEFAULT '0',
  `headRadius` float NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Colony pin data';

--
-- Indexes for dumped tables
--

--
-- Indexes for table `piPins`
--
ALTER TABLE `piPins`
  ADD PRIMARY KEY (`pinID`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

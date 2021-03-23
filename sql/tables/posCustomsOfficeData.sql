-- phpMyAdmin SQL Dump
-- version 4.4.15.10
-- https://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 18, 2019 at 12:43 AM
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
-- Table structure for table `posCustomsOfficeData`
--

CREATE TABLE IF NOT EXISTS `posCustomsOfficeData` (
  `itemID` int(11) NOT NULL DEFAULT '0',
  `ownerID` int(11) NOT NULL DEFAULT '0',
  `level` tinyint(2) NOT NULL DEFAULT '1',
  `state` tinyint(2) NOT NULL DEFAULT '0',
  `status` tinyint(2) NOT NULL DEFAULT '0',
  `orbitalHackerProgress` float NOT NULL DEFAULT '0',
  `orbitalHackerID` int(11) NOT NULL DEFAULT '0',
  `allowAlly` bit(1) NOT NULL DEFAULT b'0',
  `allowStandings` bit(1) NOT NULL DEFAULT b'0',
  `selectedHour` tinyint(2) NOT NULL DEFAULT '0',
  `standingValue` tinyint(2) NOT NULL DEFAULT '0',
  `corpTax` float NOT NULL DEFAULT '0',
  `allyTax` float NOT NULL DEFAULT '0',
  `highTax` float NOT NULL DEFAULT '0',
  `neutTax` float NOT NULL DEFAULT '0',
  `goodTax` float NOT NULL DEFAULT '0',
  `badTax` float NOT NULL DEFAULT '0',
  `horribleTax` float NOT NULL DEFAULT '0',
  `timestamp` bigint(20) NOT NULL DEFAULT '0',
  `rotX` float NOT NULL DEFAULT '0',
  `rotY` float NOT NULL DEFAULT '0',
  `rotZ` float NOT NULL DEFAULT '0',
  `rotW` float NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='POS Customs Office Data';

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

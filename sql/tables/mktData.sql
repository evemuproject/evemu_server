-- phpMyAdmin SQL Dump
-- version 4.4.15.10
-- https://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 10, 2019 at 09:05 PM
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
-- Table structure for table `mktData`
--

CREATE TABLE IF NOT EXISTS `mktData` (
  `ownerID` int(11) unsigned NOT NULL,
  `typeID` int(11) NOT NULL,
  `date` datetime NOT NULL,
  `isBid` bit(1) NOT NULL,
  `amtLeft` int(8) NOT NULL,
  `amtEntered` int(8) NOT NULL,
  `minVol` tinyint(2) NOT NULL,
  `price` double NOT NULL,
  `stationID` int(11) NOT NULL,
  `range` text NOT NULL,
  `days` int(5) NOT NULL,
  `regionID` int(11) NOT NULL,
  `orderSet` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

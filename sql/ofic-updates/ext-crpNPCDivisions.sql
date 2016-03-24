/*
Navicat MySQL Data Transfer

Source Server         : MySQL (local)
Source Server Version : 50525
Source Host           : localhost:3306
Source Database       : evemu

Target Server Type    : MYSQL
Target Server Version : 50525
File Encoding         : 65001

Date: 2012-12-09 20:32:12
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `extCrpNPCDivisions`
-- ----------------------------
DROP TABLE IF EXISTS `extCrpNPCDivisions`;
CREATE TABLE `extCrpNPCDivisions` (
  `divisionID` tinyint(3) unsigned NOT NULL,
  `divisionNameID` int(11) DEFAULT NULL,
  `leaderTypeID` int(11) DEFAULT NULL,
  PRIMARY KEY (`divisionID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of extCrpNPCDivisions
-- ----------------------------
INSERT INTO `extCrpNPCDivisions` VALUES
('1', '1', '1'),
('2', '2', '2'),
('3', '3', '3'),
('4', '4', '4'),
('5', '5', '5'),
('6', '6', '6'),
('7', '7', '7'),
('8', '8', '8'),
('9', '9', '9'),
('10', '10', '10'),
('11', '11', '11'),
('12', '12', '12'),
('13', '13', '13'),
('14', '14', '14'),
('15', '15', '15'),
('16', '16', '16'),
('17', '17', '17'),
('18', '18', '18'),
('19', '19', '19'),
('20', '20', '20'),
('21', '21', '21'),
('22', '22', '22'),
('23', '23', '23'),
('24', '24', '24');

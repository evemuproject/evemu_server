# Generated by CacheToSQL 2 on 12/12/2011 7:56:28 AM (UTC)
# Source: cacheShipTypes
# File: 2000001.cache2

DROP TABLE IF EXISTS shipTypes;
DROP TABLE IF EXISTS blkShipTypes;
CREATE TABLE blkShipTypes (
    shipTypeID INT,
    weaponTypeID INT,
    miningTypeID INT,
    skillTypeID INT,
    PRIMARY KEY (shipTypeID),
    INDEX weaponTypeID (weaponTypeID),
    INDEX miningTypeID (miningTypeID),
    INDEX skillTypeID (skillTypeID)
);

INSERT INTO blkShipTypes (shipTypeID, weaponTypeID, miningTypeID, skillTypeID) VALUES
(582, 0, 0, 3330),
(583, 0, 0, 3330),
(584, 0, 0, 3330),
(585, 0, 0, 3329),
(586, 0, 0, 3329),
(587, 0, 0, 3329),
(588, 3636, 3651, 3329),
(589, 0, 0, 3331),
(590, 0, 0, 3331),
(591, 0, 0, 3331),
(592, 0, 0, 3328),
(593, 0, 0, 3328),
(594, 0, 0, 3328),
(595, 0, 0, 3328),
(596, 3634, 3651, 3331),
(597, 0, 0, 3331),
(598, 0, 0, 3329),
(599, 0, 0, 3329),
(600, 0, 0, 3329),
(601, 3638, 3651, 3330),
(602, 0, 0, 3330),
(603, 0, 0, 3330),
(604, 0, 0, 3330),
(605, 0, 0, 3330),
(606, 3640, 3651, 3328),
(607, 0, 0, 3328),
(608, 0, 0, 3328),
(609, 0, 0, 3328),
(610, 0, 0, 3452),
(611, 0, 0, 0),
(612, 0, 0, 3452),
(613, 0, 0, 3452),
(614, 0, 0, 3452),
(615, 0, 0, 0),
(616, 0, 0, 3452),
(617, 0, 0, 3328),
(618, 0, 0, 0),
(619, 0, 0, 0),
(620, 0, 0, 3334),
(621, 0, 0, 3334),
(622, 0, 0, 3333),
(623, 0, 0, 3334),
(624, 0, 0, 3335),
(625, 0, 0, 3335),
(626, 0, 0, 3332),
(627, 0, 0, 3332),
(628, 0, 0, 3335),
(629, 0, 0, 3333),
(630, 0, 0, 3333),
(631, 0, 0, 3333),
(632, 0, 0, 3334),
(633, 0, 0, 3332),
(634, 0, 0, 3332),
(635, 0, 0, 3328),
(636, 0, 0, 0),
(637, 0, 0, 0),
(638, 0, 0, 3338),
(639, 0, 0, 3337),
(640, 0, 0, 3338),
(641, 0, 0, 3336),
(642, 0, 0, 3339),
(643, 0, 0, 3339),
(644, 0, 0, 3337),
(645, 0, 0, 3336),
(647, 0, 0, 0),
(648, 0, 0, 3342),
(649, 0, 0, 3342),
(650, 0, 0, 3340),
(651, 0, 0, 3341),
(652, 0, 0, 3341),
(653, 0, 0, 3341),
(654, 0, 0, 3340),
(655, 0, 0, 3340),
(656, 0, 0, 3340),
(657, 0, 0, 3340),
(658, 0, 0, 3452),
(659, 0, 0, 0),
(660, 0, 0, 0),
(661, 0, 0, 0),
(662, 0, 0, 0),
(663, 0, 0, 0),
(664, 0, 0, 0),
(665, 0, 0, 0),
(666, 0, 0, 0),
(667, 0, 0, 0),
(668, 0, 0, 0),
(669, 0, 0, 0),
(670, 0, 0, 0),
(671, 0, 0, 3344),
(672, 0, 0, 3330),
(1233, 0, 0, 3328),
(1896, 0, 0, 9955),
(1898, 0, 0, 3328),
(1900, 0, 0, 3328),
(1902, 0, 0, 3328),
(1904, 0, 0, 3334),
(1906, 0, 0, 3334),
(1908, 0, 0, 3334),
(1910, 0, 0, 3334),
(1912, 0, 0, 3338),
(1914, 0, 0, 3338),
(1916, 0, 0, 3338),
(1918, 0, 0, 3338),
(1944, 0, 0, 3343),
(2006, 0, 0, 3335),
(2078, 2083, 0, 3330),
(2161, 0, 0, 3331),
(2164, 0, 0, 3335),
(2166, 0, 0, 3335),
(2168, 0, 0, 3335),
(2834, 0, 0, 3328),
(2836, 0, 0, 3332),
(2863, 0, 0, 3452),
(2998, 0, 0, 3452),
(3514, 0, 0, 3341),
(3516, 0, 0, 3331),
(3518, 0, 0, 3333),
(3532, 0, 0, 3331),
(3628, 0, 0, 3341),
(3751, 0, 0, 3331),
(3753, 0, 0, 3331),
(3756, 0, 0, 3335),
(3764, 0, 0, 3345),
(3766, 0, 0, 3329),
(3768, 0, 0, 3331),
(3878, 0, 0, 3758),
(4005, 0, 0, 3338),
(4302, 0, 0, 3335),
(4306, 0, 0, 3335),
(4308, 0, 0, 3335),
(4310, 0, 0, 3335),
(9854, 0, 0, 9955),
(9858, 0, 0, 9955),
(9860, 0, 0, 9955),
(9862, 0, 0, 9955),
(10254, 0, 0, 0),
(11011, 0, 0, 3332),
(11019, 0, 0, 3328),
(11129, 0, 0, 3330),
(11132, 0, 0, 3330),
(11134, 0, 0, 3330),
(11172, 0, 0, 3328),
(11174, 0, 0, 3328),
(11176, 0, 0, 3330),
(11178, 0, 0, 3330),
(11180, 0, 0, 3329),
(11182, 0, 0, 3329),
(11184, 0, 0, 3331),
(11186, 0, 0, 3331),
(11188, 0, 0, 3331),
(11190, 0, 0, 3331),
(11192, 0, 0, 3330),
(11194, 0, 0, 3330),
(11196, 0, 0, 3329),
(11198, 0, 0, 3329),
(11200, 0, 0, 3328),
(11202, 0, 0, 3328),
(11365, 0, 0, 3331),
(11371, 0, 0, 3331),
(11373, 0, 0, 3331),
(11375, 0, 0, 3331),
(11377, 0, 0, 3331),
(11379, 0, 0, 3331),
(11381, 0, 0, 3331),
(11383, 0, 0, 3331),
(11385, 0, 0, 3331),
(11387, 0, 0, 3331),
(11389, 0, 0, 3331),
(11393, 0, 0, 3331),
(11400, 0, 0, 3331),
(11567, 0, 0, 3345),
(11591, 0, 0, 3329),
(11936, 0, 0, 3339),
(11938, 0, 0, 3339),
(11940, 0, 0, 3331),
(11942, 0, 0, 3331),
(11957, 0, 0, 3333),
(11959, 0, 0, 3333),
(11961, 0, 0, 3333),
(11963, 0, 0, 3333),
(11965, 0, 0, 3333),
(11969, 0, 0, 3333),
(11971, 0, 0, 3333),
(11973, 0, 0, 3333),
(11978, 0, 0, 3333),
(11980, 0, 0, 3333),
(11982, 0, 0, 3333),
(11985, 0, 0, 3333),
(11987, 0, 0, 3333),
(11989, 0, 0, 3333),
(11991, 0, 0, 3333),
(11993, 0, 0, 3333),
(11995, 0, 0, 3333),
(11997, 0, 0, 3333),
(11999, 0, 0, 3333),
(12003, 0, 0, 3333),
(12005, 0, 0, 3333),
(12007, 0, 0, 3333),
(12009, 0, 0, 3333),
(12011, 0, 0, 3333),
(12013, 0, 0, 3333),
(12015, 0, 0, 3333),
(12017, 0, 0, 3333),
(12019, 0, 0, 3333),
(12021, 0, 0, 3333),
(12023, 0, 0, 3333),
(12030, 0, 0, 3331),
(12032, 0, 0, 3331),
(12034, 0, 0, 3331),
(12036, 0, 0, 3331),
(12038, 0, 0, 3331),
(12040, 0, 0, 3331),
(12042, 0, 0, 3331),
(12044, 0, 0, 3331),
(12403, 0, 0, 3328),
(12729, 0, 0, 3342),
(12731, 0, 0, 3342),
(12733, 0, 0, 3343),
(12735, 0, 0, 3341),
(12743, 0, 0, 3340),
(12745, 0, 0, 3340),
(12747, 0, 0, 3341),
(12753, 0, 0, 3343),
(13202, 0, 0, 3336),
(16227, 0, 0, 3335),
(16229, 0, 0, 3335),
(16231, 0, 0, 3335),
(16233, 0, 0, 3335),
(16236, 0, 0, 3335),
(16238, 0, 0, 3335),
(16240, 0, 0, 3335),
(16242, 0, 0, 3335),
(17360, 0, 0, 3328),
(17476, 0, 0, 3329),
(17478, 0, 0, 3329),
(17480, 0, 0, 3329),
(17619, 0, 0, 3330),
(17634, 0, 0, 3334),
(17636, 0, 0, 3338),
(17703, 0, 0, 3330),
(17705, 0, 0, 3330),
(17707, 0, 0, 3330),
(17709, 0, 0, 3334),
(17711, 0, 0, 3334),
(17713, 0, 0, 3334),
(17715, 0, 0, 3334),
(17718, 0, 0, 3334),
(17720, 0, 0, 3334),
(17722, 0, 0, 3334),
(17724, 0, 0, 3334),
(17726, 0, 0, 3338),
(17728, 0, 0, 3338),
(17730, 0, 0, 3338),
(17732, 0, 0, 3338),
(17734, 0, 0, 3338),
(17736, 0, 0, 3338),
(17738, 0, 0, 3338),
(17740, 0, 0, 3338),
(17812, 0, 0, 3330),
(17841, 0, 0, 3328),
(17843, 0, 0, 3332),
(17918, 0, 0, 3338),
(17920, 0, 0, 3339),
(17922, 0, 0, 3335),
(17924, 0, 0, 3331),
(17926, 0, 0, 3331),
(17928, 0, 0, 3328),
(17930, 0, 0, 3330),
(17932, 0, 0, 3329),
(19720, 0, 0, 3339),
(19722, 0, 0, 3339),
(19724, 0, 0, 3339),
(19726, 0, 0, 3339),
(19744, 0, 0, 3343),
(19770, 0, 0, 3329),
(20067, 0, 0, 3333),
(20122, 0, 0, 3335),
(20125, 0, 0, 3333),
(20183, 0, 0, 3341),
(20185, 0, 0, 3341),
(20187, 0, 0, 3341),
(20189, 0, 0, 3341),
(21097, 0, 0, 3330),
(21628, 0, 0, 3330),
(22426, 0, 0, 3339),
(22428, 0, 0, 3339),
(22430, 0, 0, 3336),
(22432, 0, 0, 3336),
(22434, 0, 0, 3338),
(22436, 0, 0, 3338),
(22438, 0, 0, 3337),
(22440, 0, 0, 3337),
(22442, 0, 0, 3335),
(22444, 0, 0, 3335),
(22446, 0, 0, 3335),
(22448, 0, 0, 3335),
(22450, 0, 0, 3335),
(22452, 0, 0, 3335),
(22454, 0, 0, 3335),
(22456, 0, 0, 3335),
(22458, 0, 0, 3335),
(22460, 0, 0, 3335),
(22462, 0, 0, 3335),
(22464, 0, 0, 3335),
(22466, 0, 0, 3335),
(22468, 0, 0, 3335),
(22470, 0, 0, 3335),
(22472, 0, 0, 3335),
(22474, 0, 0, 3335),
(22544, 0, 0, 3329),
(22546, 0, 0, 3329),
(22548, 0, 0, 3329),
(22579, 0, 0, 3329),
(22852, 0, 0, 3341),
(23693, 0, 0, 3341),
(23757, 0, 0, 3341),
(23773, 0, 0, 3341),
(23911, 0, 0, 3341),
(23913, 0, 0, 3341),
(23915, 0, 0, 3341),
(23917, 0, 0, 3341),
(23919, 0, 0, 3341),
(24448, 0, 0, 3335),
(24483, 0, 0, 3341),
(24688, 0, 0, 3338),
(24690, 0, 0, 3336),
(24692, 0, 0, 3339),
(24694, 0, 0, 3337),
(24696, 0, 0, 3335),
(24698, 0, 0, 3335),
(24700, 0, 0, 3335),
(24702, 0, 0, 3335),
(25426, 0, 0, 3331),
(25560, 0, 0, 3328),
(26840, 0, 0, 3338),
(26842, 0, 0, 3338),
(26872, 0, 0, 3329),
(26874, 0, 0, 3329),
(26876, 0, 0, 3329),
(27299, 0, 0, 3330),
(27301, 0, 0, 3330),
(27303, 0, 0, 3330),
(27305, 0, 0, 3330),
(28310, 0, 0, 3329),
(28352, 0, 0, 3341),
(28606, 0, 0, 3341),
(28659, 0, 0, 3339),
(28661, 0, 0, 3336),
(28665, 0, 0, 3337),
(28710, 0, 0, 3338),
(28824, 0, 0, 3332),
(28844, 0, 0, 3341),
(28846, 0, 0, 3341),
(28848, 0, 0, 3341),
(28850, 0, 0, 3341),
(29248, 0, 0, 3331),
(29266, 0, 0, 3330),
(29328, 0, 0, 3330),
(29330, 0, 0, 3330),
(29332, 0, 0, 3330),
(29334, 0, 0, 3330),
(29336, 0, 0, 3333),
(29337, 0, 0, 3334),
(29340, 0, 0, 3334),
(29344, 0, 0, 3332),
(29984, 0, 0, 3334),
(29986, 0, 0, 3335),
(29988, 0, 0, 3332),
(29990, 0, 0, 3333),
(30842, 0, 0, 3330),
(32207, 0, 0, 3331),
(32209, 0, 0, 3333),
(32305, 0, 0, 3339),
(32307, 0, 0, 3336),
(32309, 0, 0, 3338),
(32311, 0, 0, 3337);

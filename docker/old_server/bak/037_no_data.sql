-- MySQL dump 10.13  Distrib 5.6.28, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: dayz037
-- ------------------------------------------------------
-- Server version	5.6.28-0ubuntu0.15.10.1

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
-- Table structure for table `bag_invent`
--

DROP TABLE IF EXISTS `bag_invent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bag_invent` (
  `object_id` int(11) NOT NULL,
  `inv1` int(11) NOT NULL DEFAULT '-1',
  `inv2` int(11) NOT NULL DEFAULT '-1',
  `inv3` int(11) NOT NULL DEFAULT '-1',
  `inv4` int(11) NOT NULL DEFAULT '-1',
  `inv5` int(11) NOT NULL DEFAULT '-1',
  `inv6` int(11) NOT NULL DEFAULT '-1',
  `inv7` int(11) NOT NULL DEFAULT '-1',
  `inv8` int(11) NOT NULL DEFAULT '-1',
  `inv9` int(11) NOT NULL DEFAULT '-1',
  `inv10` int(11) NOT NULL DEFAULT '-1',
  `inv11` int(11) NOT NULL DEFAULT '-1',
  `inv12` int(11) NOT NULL DEFAULT '-1',
  `inv13` int(11) NOT NULL DEFAULT '-1',
  `inv14` int(11) NOT NULL DEFAULT '-1',
  `inv15` int(11) NOT NULL DEFAULT '-1',
  `inv16` int(11) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`object_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ban_ip`
--

DROP TABLE IF EXISTS `ban_ip`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ban_ip` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ip` varchar(15) NOT NULL,
  `ban_date` datetime NOT NULL,
  `ban_until` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=92 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ban_list`
--

DROP TABLE IF EXISTS `ban_list`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ban_list` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `player_id` int(11) NOT NULL,
  `ban_mask` int(11) NOT NULL,
  `ban_until` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=133 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `characters`
--

DROP TABLE IF EXISTS `characters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `characters` (
  `player_id` int(11) NOT NULL DEFAULT '0',
  `temperature` int(11) NOT NULL DEFAULT '3660',
  `health` int(11) NOT NULL DEFAULT '12000',
  `hunger` int(11) NOT NULL DEFAULT '1000',
  `thirst` int(11) NOT NULL DEFAULT '1000',
  `wound` int(11) NOT NULL DEFAULT '0',
  `placex` float NOT NULL DEFAULT '-1420.64',
  `placey` float NOT NULL DEFAULT '-2897.94',
  `placez` float NOT NULL DEFAULT '48.0911',
  `angle` float NOT NULL DEFAULT '38.8824',
  `skin` int(11) NOT NULL DEFAULT '188',
  `killer_id` int(11) DEFAULT NULL,
  `c_killer` int(11) DEFAULT NULL,
  `scores` int(11) NOT NULL DEFAULT '0',
  `bplacex` float NOT NULL DEFAULT '-1420.64',
  `bplacey` float NOT NULL DEFAULT '-2897.94',
  `bplacez` float NOT NULL DEFAULT '48.0911',
  `bangle` float NOT NULL DEFAULT '38.8824',
  `cheater` int(11) NOT NULL DEFAULT '0',
  `mute_count` int(11) NOT NULL DEFAULT '0',
  `kick_count` int(11) NOT NULL DEFAULT '0',
  `ban_count` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`player_id`),
  KEY `player_id` (`player_id`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dot_type`
--

DROP TABLE IF EXISTS `dot_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dot_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `dot_id` int(11) NOT NULL DEFAULT '0',
  `type_id` int(11) NOT NULL DEFAULT '0',
  UNIQUE KEY `dot_id` (`dot_id`,`type_id`),
  KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=8891 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `inventory`
--

DROP TABLE IF EXISTS `inventory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `inventory` (
  `player_id` int(11) NOT NULL DEFAULT '0',
  `inv1` int(11) NOT NULL DEFAULT '-1',
  `inv2` int(11) NOT NULL DEFAULT '-1',
  `inv3` int(11) NOT NULL DEFAULT '-1',
  `inv4` int(11) NOT NULL DEFAULT '-1',
  `inv5` int(11) NOT NULL DEFAULT '-1',
  `inv6` int(11) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`player_id`),
  KEY `id` (`player_id`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `key_data`
--

DROP TABLE IF EXISTS `key_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `key_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `key_id` int(11) NOT NULL,
  `object_id` int(11) NOT NULL,
  PRIMARY KEY (`key_id`,`object_id`),
  KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=8166 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `key_icon`
--

DROP TABLE IF EXISTS `key_icon`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `key_icon` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `key_id` int(11) NOT NULL,
  `player_id` int(11) NOT NULL,
  `icon_id` int(11) NOT NULL,
  `object_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`player_id`,`icon_id`),
  KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=577258 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `object_dot`
--

DROP TABLE IF EXISTS `object_dot`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `object_dot` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `placex` float NOT NULL DEFAULT '0',
  `placey` float NOT NULL DEFAULT '0',
  `placez` float NOT NULL DEFAULT '0',
  `object_id` int(11) DEFAULT NULL,
  `last_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3803 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `objects`
--

DROP TABLE IF EXISTS `objects`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `objects` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `thing_id` int(11) NOT NULL DEFAULT '0',
  `next_id` int(11) NOT NULL DEFAULT '0',
  `prev_id` int(11) DEFAULT NULL,
  `placex` float DEFAULT NULL,
  `placey` float DEFAULT NULL,
  `placez` float DEFAULT NULL,
  `add_rotx` float NOT NULL DEFAULT '0',
  `add_roty` float NOT NULL DEFAULT '0',
  `add_rotz` float NOT NULL DEFAULT '0',
  `pl_owner_id` int(11) DEFAULT NULL,
  `th_owner_id` int(11) DEFAULT NULL,
  `obj_id` int(11) DEFAULT NULL,
  `dot_id` int(11) DEFAULT NULL,
  `owner` int(11) DEFAULT NULL,
  `is_dropped` int(11) DEFAULT NULL,
  `last_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `view_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `unused` int(11) NOT NULL DEFAULT '0',
  `value` int(11) NOT NULL DEFAULT '0',
  `vector` float DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id` (`id`),
  KEY `thing_id` (`thing_id`)
) ENGINE=MyISAM AUTO_INCREMENT=37889 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ok`
--

DROP TABLE IF EXISTS `ok`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ok` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `players`
--

DROP TABLE IF EXISTS `players`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `players` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) CHARACTER SET latin1 NOT NULL DEFAULT '',
  `passwd` varchar(32) CHARACTER SET latin1 NOT NULL DEFAULT '',
  `txtpass` varchar(32) NOT NULL DEFAULT '',
  `admin` int(11) NOT NULL DEFAULT '0',
  `reg_ip` varchar(15) NOT NULL DEFAULT '',
  `last_ip` varchar(15) NOT NULL DEFAULT '',
  `reg_ip_mask` varchar(15) NOT NULL DEFAULT '',
  `last_ip_mask` varchar(15) NOT NULL DEFAULT '',
  `reg_date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `last_date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `reg_country` varchar(64) NOT NULL DEFAULT 'Unknown',
  `city` varchar(64) NOT NULL DEFAULT 'Unknown',
  `country` varchar(64) NOT NULL DEFAULT 'Unknown',
  `land` varchar(2) NOT NULL DEFAULT 'en',
  `lang` varchar(2) NOT NULL DEFAULT 'en',
  `mute` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `time_count` time NOT NULL DEFAULT '00:00:00',
  `ban` int(11) NOT NULL DEFAULT '0',
  `ban_date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `is_zombie` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`name`),
  KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=9544 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `spawns`
--

DROP TABLE IF EXISTS `spawns`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `spawns` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `placex` float NOT NULL DEFAULT '0',
  `placey` float NOT NULL DEFAULT '0',
  `placez` float NOT NULL DEFAULT '0',
  `angle` float NOT NULL DEFAULT '0',
  `is_zombie` int(11) NOT NULL DEFAULT '0',
  `last_time` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=97 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `thing_type`
--

DROP TABLE IF EXISTS `thing_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `thing_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) CHARACTER SET latin1 NOT NULL DEFAULT '',
  `about` varchar(64) CHARACTER SET latin1 DEFAULT NULL,
  PRIMARY KEY (`name`),
  KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=21 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `things`
--

DROP TABLE IF EXISTS `things`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `things` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) CHARACTER SET latin1 NOT NULL DEFAULT '',
  `is_inventory` int(11) NOT NULL DEFAULT '0',
  `is_auto` int(11) NOT NULL DEFAULT '0',
  `is_vehicle` int(11) NOT NULL DEFAULT '0',
  `rotx` int(11) NOT NULL DEFAULT '0',
  `roty` int(11) NOT NULL DEFAULT '0',
  `rotz` int(11) NOT NULL DEFAULT '0',
  `inventx` float NOT NULL DEFAULT '0',
  `inventy` float NOT NULL DEFAULT '0',
  `inventz` float NOT NULL DEFAULT '0',
  `zoom` float NOT NULL DEFAULT '1',
  `posx` float NOT NULL DEFAULT '0',
  `posy` float NOT NULL DEFAULT '0',
  `posz` float NOT NULL DEFAULT '0',
  `height` float NOT NULL DEFAULT '0',
  `invent_id` int(11) NOT NULL DEFAULT '0',
  `inworld_id` int(11) NOT NULL DEFAULT '0',
  `rotatable` int(11) NOT NULL DEFAULT '0',
  `def_value` int(11) NOT NULL DEFAULT '0',
  `max_value` int(11) NOT NULL DEFAULT '0',
  `type_id` int(11) NOT NULL DEFAULT '1',
  `is_consumble` int(11) NOT NULL DEFAULT '0',
  `is_disappeared` int(11) NOT NULL DEFAULT '0',
  `is_catalyst` int(11) NOT NULL DEFAULT '0',
  `extra` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`name`),
  KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=10423 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `veh_data`
--

DROP TABLE IF EXISTS `veh_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `veh_data` (
  `object_id` int(11) NOT NULL DEFAULT '0',
  `color1` int(11) NOT NULL DEFAULT '1',
  `color2` int(11) NOT NULL DEFAULT '1',
  `panels` int(11) NOT NULL DEFAULT '0',
  `doors` int(11) NOT NULL DEFAULT '0',
  `light` int(11) NOT NULL DEFAULT '0',
  `tires` int(11) NOT NULL DEFAULT '0',
  `patrol` int(11) NOT NULL DEFAULT '0',
  `accumul` int(11) NOT NULL DEFAULT '0',
  `is_working` int(11) NOT NULL DEFAULT '0',
  `engine_id` int(11) NOT NULL DEFAULT '0',
  `accum_id` int(11) NOT NULL DEFAULT '0',
  `is_lights` int(11) NOT NULL DEFAULT '0',
  `is_alarm` int(11) NOT NULL DEFAULT '0',
  `is_locked` int(11) NOT NULL DEFAULT '0',
  `is_bonnet` int(11) NOT NULL DEFAULT '0',
  `is_boot` int(11) NOT NULL DEFAULT '0',
  `is_objective` int(11) NOT NULL DEFAULT '0',
  `health` float NOT NULL DEFAULT '1000',
  PRIMARY KEY (`object_id`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `veh_invent`
--

DROP TABLE IF EXISTS `veh_invent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `veh_invent` (
  `object_id` int(11) NOT NULL AUTO_INCREMENT,
  `inv1` int(11) NOT NULL DEFAULT '-1',
  `inv2` int(11) NOT NULL DEFAULT '-1',
  `inv3` int(11) NOT NULL DEFAULT '-1',
  `inv4` int(11) NOT NULL DEFAULT '-1',
  `inv5` int(11) NOT NULL DEFAULT '-1',
  `inv6` int(11) NOT NULL DEFAULT '-1',
  `inv7` int(11) NOT NULL DEFAULT '-1',
  `inv8` int(11) NOT NULL DEFAULT '-1',
  `inv9` int(11) NOT NULL DEFAULT '-1',
  `inv10` int(11) NOT NULL DEFAULT '-1',
  `inv11` int(11) NOT NULL DEFAULT '-1',
  `inv12` int(11) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`object_id`)
) ENGINE=MyISAM AUTO_INCREMENT=65536 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `vehicles`
--

DROP TABLE IF EXISTS `vehicles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vehicles` (
  `thing_id` int(11) NOT NULL DEFAULT '0',
  `cells` int(11) NOT NULL DEFAULT '4',
  `wheels` int(11) NOT NULL DEFAULT '4',
  `def_panels` int(11) NOT NULL DEFAULT '0',
  `def_doors` int(11) NOT NULL DEFAULT '0',
  `def_light` int(11) NOT NULL DEFAULT '0',
  `def_tires` int(11) NOT NULL DEFAULT '0',
  `def_patrol` int(11) NOT NULL DEFAULT '0',
  `patrol_cons` int(11) NOT NULL DEFAULT '10',
  `accumul_cons` int(11) NOT NULL DEFAULT '10',
  `max_patrol` int(11) NOT NULL DEFAULT '1000',
  `max_accumul` int(11) NOT NULL DEFAULT '1000',
  PRIMARY KEY (`thing_id`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-11-13 14:48:54

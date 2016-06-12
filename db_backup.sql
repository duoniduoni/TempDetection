-- MySQL dump 10.13  Distrib 5.7.12, for Win64 (x86_64)
--
-- Host: localhost    Database: sawdb2
-- ------------------------------------------------------
-- Server version	5.7.12-log

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
-- Table structure for table `db_data`
--

DROP TABLE IF EXISTS `db_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `db_data` (
  `DataID` int(11) NOT NULL,
  `Notes` text NOT NULL,
  `RecordTime` int(11) NOT NULL,
  `ReaderID` int(11) NOT NULL,
  `AntID` int(11) NOT NULL,
  `SensorID` int(11) NOT NULL,
  `Temperature` text NOT NULL,
  `RFPower` text NOT NULL,
  `Frequency` text NOT NULL,
  `RecordID` int(11) NOT NULL,
  PRIMARY KEY (`DataID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `db_data`
--

LOCK TABLES `db_data` WRITE;
/*!40000 ALTER TABLE `db_data` DISABLE KEYS */;
/*!40000 ALTER TABLE `db_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `db_reader_position`
--

DROP TABLE IF EXISTS `db_reader_position`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `db_reader_position` (
  `ID` int(11) NOT NULL,
  `Position` text NOT NULL,
  `HighTemp` tinyint(4) NOT NULL,
  `LowTemp` tinyint(4) NOT NULL,
  `ReaderID` int(11) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `db_reader_position`
--

LOCK TABLES `db_reader_position` WRITE;
/*!40000 ALTER TABLE `db_reader_position` DISABLE KEYS */;
/*!40000 ALTER TABLE `db_reader_position` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `db_record`
--

DROP TABLE IF EXISTS `db_record`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `db_record` (
  `RecordID` int(11) NOT NULL AUTO_INCREMENT,
  `StartTime` datetime DEFAULT NULL,
  `EndTime` datetime DEFAULT NULL,
  PRIMARY KEY (`RecordID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `db_record`
--

LOCK TABLES `db_record` WRITE;
/*!40000 ALTER TABLE `db_record` DISABLE KEYS */;
/*!40000 ALTER TABLE `db_record` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `db_sensor_position`
--

DROP TABLE IF EXISTS `db_sensor_position`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `db_sensor_position` (
  `ID` int(11) NOT NULL,
  `Position` text NOT NULL,
  `Power` tinyint(4) NOT NULL,
  `ReaderID` int(11) NOT NULL,
  `AntID` int(11) NOT NULL,
  `SensorID` int(11) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `db_sensor_position`
--

LOCK TABLES `db_sensor_position` WRITE;
/*!40000 ALTER TABLE `db_sensor_position` DISABLE KEYS */;
/*!40000 ALTER TABLE `db_sensor_position` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `db_user`
--

DROP TABLE IF EXISTS `db_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `db_user` (
  `UserName` varchar(30) DEFAULT NULL,
  `UserPassword` varchar(30) DEFAULT NULL,
  `Domain` tinyint(4) NOT NULL,
  UNIQUE KEY `UserName` (`UserName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `db_user`
--

LOCK TABLES `db_user` WRITE;
/*!40000 ALTER TABLE `db_user` DISABLE KEYS */;
INSERT INTO `db_user` VALUES ('zhangsong','1',1);
/*!40000 ALTER TABLE `db_user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-06-10 10:58:37

-- MariaDB dump 10.19  Distrib 10.4.27-MariaDB, for Win64 (AMD64)
--
-- Host: 127.0.0.1    Database: test
-- ------------------------------------------------------
-- Server version	10.4.27-MariaDB

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
-- Table structure for table `entity_user_votes`
--

DROP TABLE IF EXISTS `entity_user_votes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entity_user_votes` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `first_name` varchar(50) DEFAULT NULL,
  `email` varchar(50) DEFAULT NULL,
  `password` varchar(50) DEFAULT NULL,
  `votes0` int(10) DEFAULT NULL,
  `votes1` int(10) DEFAULT NULL,
  `votes2` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `entity_user_votes`
--

LOCK TABLES `entity_user_votes` WRITE;
/*!40000 ALTER TABLE `entity_user_votes` DISABLE KEYS */;
INSERT INTO `entity_user_votes` VALUES (1,'Homer','homer@simp.com','Homer!23',2,2,2),(2,'Marge','marge@simp.com','Marge!23',1,1,1),(3,'Lisa','lisa@simp.com','Lisa!234',2,2,2),(4,'Bart','bart@simp.com','Bart!234',1,2,2),(5,'Maggie','maggie@simp.com','Maggie!23',1,1,1),(6,'name1','name1@email.com','Password!23',3,3,3),(7,'name1','name1@email.com','Password!23',3,3,3),(8,'Krusty','krusty@simp.com','Krusty!23',1,1,2),(9,'Krusty','krusty@simp.com','Krusty!23',1,1,2),(10,'Name1','name1@gmail.com','Password!1622',1,3,3),(11,'Name2','name2@gmail.com','Password!8815',2,2,0),(12,'Name3','name3@gmail.com','Password!3114',3,2,1),(13,'Name4','name4@gmail.com','Password!6823',0,3,2),(14,'Name5','name5@gmail.com','Password!81016',1,0,1),(15,'Name1','name1@gmail.com','Password!7421',0,2,0),(16,'Name2','name2@gmail.com','Password!8527',0,2,0),(17,'Name3','name3@gmail.com','Password!2224',0,2,0),(18,'Name4','name4@gmail.com','Password!1921',1,3,1),(19,'Name5','name5@gmail.com','Password!01215',0,1,2);
/*!40000 ALTER TABLE `entity_user_votes` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-06-02 14:46:34

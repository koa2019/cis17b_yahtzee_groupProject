<?php
	//Dr. Mark E. Lehr
	//Create a connection to the database
	//DB, UN, Pass, DB
        //require_once ('..\..\ConnectOutOfRootLocal.php'); // Connect to the db if this file is outside of xampp>htdocs
        require_once ('ConnectTest.php'); // Connect to the db locally via localhost
          
	//Query the database
        // YOU can get this query from openOffice.createQuery>editQuery>copy and paste it here. See screenshots
        
        // Dr Lehr's DBConnect>DBSelect.php > OpenOffice Query for movie = "Martian"
        //$sql = "SELECT `movie_id`, `name`, `studio`, `release_date`, `rating_id`, `duration` 
        //        FROM `test`.`ml1150258_entity_movie` 
        //        AS `ml1150258_entity_movie` 
        //        WHERE `name` = 'Martian' AND `duration` > 1.75";
        
        // Dr. Lehr's query
//        //        $sql="SELECT `movie_id`, `name`, `studio`, `release_date`, 
//		               `rating_id`, `duration` FROM 		
//					   `ml1150258_entity_movie`
//                                            WHERE `duration` >= 1.75;";
        // OpenOffice Query for all movies in DB
        $sql = "SELECT `movie_id`, `name`, `studio`, `release_date`, `rating_id`, `duration` FROM `test`.`ml1150258_entity_movie` AS `ml1150258_entity_movie` WHERE `duration` > 1.75";
        
        $result=$conn->query($sql);
        echo "<table border='1'>";
		    echo "<tr><th>".'name'."</th>";
            echo "<th>".'studio'."</th>";
            echo "<th>".'release_date'."</th>";
            echo "<th>".'duration'."</th></tr>";
        while($re = $result->fetch_assoc()){
                  echo "<tr><td>".$re['name']."</td>";
                  echo "<td>".$re['studio']."</td>";
                  echo "<td>".$re['release_date']."</td>";
                  echo "<td>".$re['duration']."</td></tr>";
        }
        echo "</table>";
?>
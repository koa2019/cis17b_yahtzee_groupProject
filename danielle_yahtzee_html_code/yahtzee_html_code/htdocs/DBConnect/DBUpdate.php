<?php
	//Dr. Mark E. Lehr
	//Create a connection to the database
	//DB, UN, Pass, DB
        //require_once ('..\..\ConnectOutOfRootLocal.php'); // Connect to the db. if this file is outside of xampp>htdocs
        require_once ('ConnectTest.php'); // Connect to the db locally via localhost
        
	//Query the database
        // update any movies after 2010 by adding 1.3 hours to it
        $sql="UPDATE `ml1150258_entity_movie` 
                SET duration=duration+1.3
                WHERE release_date >'2010-02-08' 
                AND studio like '%Amblin%'";
        echo $sql."<br/>";
        $result=$conn->query($sql);
?>
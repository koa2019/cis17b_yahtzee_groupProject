<?php
	//Dr. Mark E. Lehr
	//Create a connection to the database
	//DB, UN, Pass, DB
        //require_once ('..\..\ConnectOutOfRootLocal.php'); // Connect to the db. if this file is outside of xampp>htdocs
        require_once ('ConnectTest.php'); // Connect to the db locally via localhost
        
	//Query the database
        $query="INSERT INTO `ml1150258_entity_movie`
                       (`name`,`studio`,`release_date`,
                        `rating_id`,`duration`) VALUES ";
        
        // Created a string and appended a bunch of records to it to fill DB
        $records=1000;
        for($i=1;$i<=$records;$i++){
          $query.="('Movie".$i."',";
          $query.=" 'Studio".rand(1,50)."',";
          $query.="'".rand(1950,2010)."-".rand(1,12)."-".rand(1,28)."',";
          $query.=rand(1,4).",";
          $query.=(rand(1,2)+rand(0,99)/100.0).")";
          if($i!=$records)$query.=",";
        }
        echo $query."<br/>";
        $result=$conn->query($query);
?>
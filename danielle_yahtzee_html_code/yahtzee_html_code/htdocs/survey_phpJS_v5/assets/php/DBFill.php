<?php
	//Dr. Mark E. Lehr
	//Create a connection to the database
	//DB, UN, Pass, DB
        //require_once ('..\..\ConnectOutOfRootLocal.php');  // Move this file outside of xampp>htdocs to protect DB when remote and NOT localhost
        require_once ('ConnectTest.php'); // Connect to the db locally via localhost
        
        
        // Dr Lehr's DBConnect>DBSelect.php > OpenOffice Query DBFill.php with users
        // $query="INSERT INTO `ml1150258_entity_movie`
                       // (`name`,`studio`,`release_date`,
                       // `rating_id`,`duration`) VALUES ";
                       
                       
        // Select All Query for user_votes_4 from surveyDB2.odb OpenOffice
        //SELECT `id`, `first_name`, `email`, `password`, `votes0`, `votes1`, `votes2` 
        //FROM `test`.`entity_user_votes` AS `entity_user_votes`
        
        
//         //THIS QUERY WILL INSERT 1 NEW RECORD IN DB. Note: placement of VALUES.
//        $query = "INSERT INTO `test`.`entity_user_votes`
//                  VALUES (NULL, 'Mom', 'mom@email.com' , 'Mom!23', 0,0,1)";
        
        
        $query = "INSERT INTO `test`.`entity_user_votes`
                 (`first_name`, `email`, `password`, `votes0`, `votes1`, `votes2`) VALUES ";
                
        // Created a string and appended a bunch of records to it to fill DB
        $records=5;
        for($i=1;$i<=$records;$i++){
          //$query.="('NULL', ";  
          $query.="('Name".$i."', "; //$query.="'Name".$i."', ";
          $query.="'name".$i."@gmail.com', ";
          $query.="'Password"."!".rand(0,9).rand(1,12).rand(13,28)."', ";//."')";
          $query.=rand(0,3).", "; // vote1
          $query.=rand(0,3).", "; // vote2
          $query.=rand(0,3).") "; // vote3
          if($i!=$records){$query.=",";}
        }
        echo $query."<br/>";
        $result=$conn->query($query);
?>
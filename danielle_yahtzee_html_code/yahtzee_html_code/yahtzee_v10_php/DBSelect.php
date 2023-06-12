<?php
    //Dr. Mark E. Lehr
    //Create a connection to the database
    //DB, UN, Pass, DB
    require_once ('ConnectTest.php'); // Connect to the db.
    
    //Query the database
    $sql= "SELECT `id`, `first_name`, `email`, `password`, `hiScore` FROM `test`.`entity_user_yahtzee_2` AS `entity_user_yahtzee_2`";

    $result=$conn->query($sql);

    $data = [];
    while($re = $result->fetch_assoc()){
        $data[] = $re;
    }

    // Convert the array into a string format
    $dataStr = json_encode($data);

    // Set a cookie named "databaseinfo" with the data. The cookie will expire in one hour.
    setcookie("databaseinfo", $dataStr, time()+3600);
?>




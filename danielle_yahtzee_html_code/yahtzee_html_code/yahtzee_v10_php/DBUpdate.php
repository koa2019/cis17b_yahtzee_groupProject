<?php
	//Dr. Mark E. Lehr
	//Create a connection to the database
	//DB, UN, Pass, DB
    require_once ('ConnectTest.php'); // Connect to the db.

    //Check if the UserData cookie is set
    if(isset($_COOKIE['UserData'])) {
        $cookieData = $_COOKIE['UserData'];
    } 
    else {
        echo "UserData cookie is not set.";
        exit();
    }

    //Decode the UserData cookie
    $userData = json_decode($cookieData, true);
    //Extract user data from the decoded cookie
    $name = $userData['Name'];
    $hiScore = $userData['hiScore'];
    
    echo "<script type ='text/JavaScript'>";  
    echo "alert('$name')";  
    echo "</script>"; 
    
    // Update the hiScore for the given user in the database
    $sql = "UPDATE `entity_user_yahtzee_2` 
            SET `hiScore` = $hiScore
            WHERE `first_name` = '$name'";

    echo $sql."<br/>";
    $result=$conn->query($sql);
?>


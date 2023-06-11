<?php
	//Dr. Mark E. Lehr
	//Create a connection to the database
	//DB, UN, Pass, DB
        require_once ('ConnectTest.php'); // Connect to the db.

	//Query the database
        //$query="INSERT INTO `entity_users`
         //              (`name`,`email`,`password`,
        //                `chekpass`,`hiscore`) VALUES ";
        
        if(isset($_COOKIE['UserData'])) {
            $cookieData = $_COOKIE['UserData'];
        } 
        else {
            echo "UserData cookie is not set.";
            exit();
        }
        
        $userData = json_decode($cookieData, true);
        
        $name = $userData['Name'];
        $email = $userData['Email'];
        $password = $userData['Password'];
        $hiScore = $userData['hiScore'];
        
        
       $query = "INSERT INTO `entity_user_yahtzee_2`
              VALUES (NULL, '$name', '$email' , '$password', $hiScore)";

        //$records=5;
        //for($i=1;$i<=$records;$i++){
        //  $query.="('Name".$i."', "; //$query.="'Name".$i."', ";
       //   $query.="'name".$i."@gmail.com', ";
        //  $query.="'Password"."!".rand(0,9).rand(1,12).rand(13,28)."', ";//."')";
        //  $query.="'CheckPass"."!".rand(0,9).rand(1,12).rand(13,28)."', ";//."')";
        //$query.=rand(10,200).", "; // vote2
        //  if($i!=$records){$query.=",";}
        //}
        
        echo $query."<br/>";
        $result=$conn->query($query);
?>

<?php

// This code is based off Dr. Lehr's JSON_Cookies > cookieTransferObject.php
//echo "</br>Gotta Read the cookie </br>";
//$text = $_COOKIE["object"];
//echo $text . "</br>";      // prints the entire cookie object
//$cookieObj = json_decode($text);
//echo '<pre>';
//var_dump($cookieObj);  // Confirm votes is added to the object by printing it
//echo '</pre></br>';
////print_r($cookieObj);  // Confirm votes is added to the object by printing it
//echo '</br></br>';


// Create an Object         https://www.geeksforgeeks.org/how-to-create-an-object-without-class-in-php/
$cookieObj = new stdClass();
// Added property to the object
$cookieObj->id = '1';
$cookieObj->name = 'Homer';
$cookieObj->email = 'homer@simp.com';
$cookieObj->password = 'Homer!23';
$cookieObj->vote0 = rand(0, 2);
$cookieObj->vote1 = rand(0, 2);
$cookieObj->vote2 = rand(0, 2);
print_r($cookieObj);// Print the object
echo "</br></br>";

// Create a connection to the database. This code is based off Dr. Lehr's DBConnect > DBSelect.php
require_once ('ConnectTest.php'); // Connect to the db locally via localhost


//  Query database.  This query is from surveyDB2.odb OpenOffice Query for user_votes_4
$sql = " UPDATE `test`.`entity_user_votes` 
                 SET votes0='" . $cookieObj->vote0 . "',votes1='" . $cookieObj->vote1 . "', votes2='" . $cookieObj->vote2 . "'
                  WHERE `id` = '" . $cookieObj->id . "' ";

echo $sql . "<br/>";
$result = $conn->query($sql);
?>
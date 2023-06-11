<?php

//Dr. Mark E. Lehr
//Create a connection to the database
//DB, UN, Pass, DB
//require_once ('..\..\ConnectOutOfRootLocal.php');  // Move this file outside of xampp>htdocs to protect DB when remote and NOT localhost
require_once ('ConnectTest.php'); // Connect to the db locally via localhost

// Create an Object         https://www.geeksforgeeks.org/how-to-create-an-object-without-class-in-php/
$cookieObj = new stdClass();

// Added property to the object
$cookieObj->name = 'Batman';
$cookieObj->email = 'bruce@batman.com';
$cookieObj->password = 'Batman!23';
$cookieObj->vote0 = rand(0, 2);
$cookieObj->vote1 = rand(0, 2);
$cookieObj->vote2 = rand(0, 2);

// Print the object
//print_r($cookieObj);

//THIS QUERY WILL INSERT 1 NEW RECORD IN DB. Note: placement of VALUES.
//$query = " INSERT INTO `test`.`entity_user_votes`
         //VALUES (NULL, 'Mom', 'mom@email.com' , 'Mom!23', 0,0,1)";

// Query database.  This query is from surveyDB2.odb OpenOffice Query for user_votes_4
// SQL Primary key: id is set to AUTO_INCREAMENT
$query = " INSERT INTO `test`.`entity_user_votes`
          (`first_name`, `email`, `password`, `votes0`, `votes1`, `votes2`) VALUES ";


// IDK why it's inserting the query twice, but it is.
// Created a string and appended a bunch of records to it to fill DB
$records = 1;
for ($i = 1; $i <= $records; $i++) {
    $query .= "('".$cookieObj->name."', "; 
    $query .= "'".$cookieObj->email."', ";
    $query .= "'".$cookieObj->password."', ";
    $query .= "'".$cookieObj->vote0."', ";
    $query .= "'".$cookieObj->vote1."', ";
    $query .= "'".$cookieObj->vote2."') ";
    if ($i != $records){$query .= ",";}
}
echo $query . "<br/>";
$result = $conn->query($query);
?>
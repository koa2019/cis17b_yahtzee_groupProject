<?php

//Dr. Mark E. Lehr
//Create a connection to the database
//DB, UN, Pass, DB
//require_once ('..\..\ConnectOutOfRootLocal.php'); // Move this file outside of xampp>htdocs to protect DB when remote and NOT localhost
require_once ('ConnectTest.php'); // Connect to the db locally via localhost

// Create an Object         https://www.geeksforgeeks.org/how-to-create-an-object-without-class-in-php/
$cookieObj = new stdClass();

// Added property to the object
$cookieObj->id = '';
$cookieObj->name = '';
$cookieObj->email = 'homer@simp.com';
$cookieObj->password = 'Homer!23';
$cookieObj->vote0 = '';
$cookieObj->vote1 = '';
$cookieObj->vote2 = '';

// Print the object
//print_r($cookieObj);


// Query database.  This query is from surveyDB2.odb OpenOffice Query for user_votes_4
// YOU can get this query from openOffice.createQuery>editQuery>copy and paste it here. See screenshots in mySQL_openOffice>lecture>05-22-23
$sql = " SELECT `id`, 
                `first_name`, 
                `email`, 
                `password`, 
                `votes0`, `votes1`, `votes2` 
                FROM `test`.`entity_user_votes` AS `entity_user_votes`
                WHERE `email` = '".$cookieObj->email."' ";

    $result = $conn->query($sql);
    echo "<table border='1'>";
    echo "<tr><th>" . 'id' . "</th>";
    echo "<th>" . 'name' . "</th>";
    echo "<th>" . 'email' . "</th>";
    echo "<th>" . 'password' . "</th>";
    echo "<th>" . 'votes0' . "</th>";
    echo "<th>" . 'votes1' . "</th>";
    echo "<th>" . 'votes2' . "</th></tr>";
    while ($re = $result->fetch_assoc()) {
        echo "<tr><td>" . $re['id'] . "</td>";
        echo "<td>" . $re['first_name'] . "</td>";
        echo "<td>" . $re['email'] . "</td>";
        echo "<td>" . $re['password'] . "</td>";
        echo "<td>" . $re['votes0'] . "</td>";
        echo "<td>" . $re['votes1'] . "</td>";
        echo "<td>" . $re['votes2'] . "</td></tr>";
    }
    echo "</table>";
?>
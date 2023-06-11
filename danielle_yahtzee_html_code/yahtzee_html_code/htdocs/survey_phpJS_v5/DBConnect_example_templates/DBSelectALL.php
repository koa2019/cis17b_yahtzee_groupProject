

<?php
// Create a connection to the database. Dr. Mark E. Lehr
// require_once ('..\..\ConnectOutOfRootLocal.php'); // Move this file outside of xampp>htdocs to protect DB when remote and NOT localhost
require_once ('ConnectTest.php'); // Connect to the db locally via localhost


//  Query database.  This query is from surveyDB2.odb OpenOffice Query for user_votes_4
// YOU can get this query from openOffice.createQuery>editQuery>copy and paste it here. See screenshots
$sql = " SELECT `id`, `first_name`, `email`, `password`, `votes0`, `votes1`, `votes2`
         FROM `test`.`entity_user_votes` AS `entity_user_votes` ";

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
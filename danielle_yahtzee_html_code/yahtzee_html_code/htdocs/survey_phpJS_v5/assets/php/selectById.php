<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Find by Email</title>
        <link rel="stylesheet" href="../css/styles.css" type="text/css" /> 
        <script type= "text/javascript" src="./assets/javascript/adminMenu.js"></script>
        <script type= "text/javascript" src="./assets/javascript/cookies.js"></script>
    </head>
    <body>
        <div id="selectById-div"></div>
        <script type="text/javascript">
            console.log("Hit selectById.php");  
        </script>

        <?php
        // Create an Object         https://www.geeksforgeeks.org/how-to-create-an-object-without-class-in-php/
        $cookieObj = new stdClass();
        $cookieObj->id ='2';// Added property to the object
        //print_r($cookieObj);// Print the object

//        // This code is based off Dr. Lehr's JSON_Cookies > cookieTransferObject.php
//        echo "</br>Gotta Read the cookie </br>";
//        $text = $_COOKIE["object"];
//        echo $text . "</br>";      // prints the entire cookie object
//        $cookieObj = json_decode($text);
//        echo '<pre>';
//        var_dump($cookieObj);  // Confirm votes is added to the object by printing it
//        echo '</pre></br>';
//        //print_r($cookieObj);  // Confirm votes is added to the object by printing it
//        echo '</br></br>';


        // Create a connection to the database
        // This code is based off Dr. Lehr's DBConnect > DBSelect.php
        require_once ('ConnectTest.php'); // Connect to the db locally via localhost
        
        
        // Query database.  This query is from surveyDB2.odb OpenOffice Query for user_votes_4
        // YOU can get this query from openOffice.createQuery>editQuery>copy and paste it here. See screenshots in mySQL_openOffice>lecture>05-22-23
        $sql = " SELECT `id`,`first_name`,`email`, `password`, `votes0`, `votes1`, `votes2` 
                FROM `test`.`entity_user_votes` WHERE `id` = '" . $cookieObj->id . "' ";

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
        <br><button onclick="window.location.assign('../../adminMenu.html')">Admin Menu</button>
    </body>
</html>

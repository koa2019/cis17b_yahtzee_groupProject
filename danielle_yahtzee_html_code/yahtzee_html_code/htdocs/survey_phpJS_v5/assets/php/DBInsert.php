<!DOCTYPE html>
<!--
For DBInsert.php: 
Flowchart for DBInsert.php: login.html > signUpForm > getForm.html > DBInsert.php > login.html
I combined Dr. Lehr's code and tweaked it to fit mine.
Dr. Lehr's github project's for cis17b_spring2023:
    DBConnect > DBFill.php
    JSON_Cookies > getform.html
    JSON_Cookies > cookieTransferObject.php
On DBSelectAll.php, right click 'run file' to confirm the record was added to DB.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title>Insert User to Database</title>
        <link rel="stylesheet" href="../css/styles.css" type="text/css" />
        <script type= "text/javascript" src="./assets/javascript/cookies.js"></script>         
    </head>
    <body>
        <div id="DBInsertMessage-div"></div>
        <script type="text/javascript">
            console.log("Hit DBInsert.php");           
            //var cookie = readCookie();  // reads cookie passed from login.html and returns object with cookies key:value pairs
            //console.log('Hit DBInsert.php. cookie\nname='+cookie.name+'\nemail='+cookie.email+'\npassword='+cookie.password);     
        </script>
        
        
        <?php
        // This code is based off Dr. Lehr's DBConnect > DBFill.php
        echo "Gotta Read the cookie </br>";
        $text = $_COOKIE["object"];
        echo $text . "</br>";      // prints the entire cookie object
        $cookieObj = json_decode($text);  
        $cookieObj->vote0 = rand(0, 2); // adding votes to object before building the SQL query
        $cookieObj->vote1 = rand(0, 2);
        $cookieObj->vote2 = rand(0, 2);    
        echo '<pre>';
        var_dump($cookieObj);  // Confirm votes is added to the object by printing it
        echo '</pre></br>';
        //print_r($cookieObj);  // Confirm votes is added to the object by printing it
        echo '</br></br>';
        
        
        // Create a connection to the database
        // This code is based off Dr. Lehr's DBConnect > DBSelect.php
        require_once ('ConnectTest.php'); // Connect to the db locally via localhost

        
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
        <br><button onclick="window.location.assign('../../login.html')">Login</button>
    </body>
</html>

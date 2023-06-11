<?php
        // Netbeans > properties > run configuration > Project URL > http://localhost/folderName/ i.e. http://localhost/survey_phpJS_v4/
	//Dr. Mark E. Lehr's DBConnect
	//Straight out of W3Schools
	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "test";

	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	} 
	echo "Connected successfully";
?>
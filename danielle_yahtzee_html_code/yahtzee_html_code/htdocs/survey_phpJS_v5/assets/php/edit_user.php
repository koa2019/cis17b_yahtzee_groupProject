<!DOCTYPE html>
<!--
This code is based off of Dr. Lehr's ShopLogin>user>edit_user.php. 
I combined it with my selectAll.php.
Needs code to update this record in database
Look @Lehr's ShopLogin>user>edit_user.php for the code to POST 
--> 
<html>
    <head>
        <meta charset="UTF-8">
        <title>Edit User</title>
        <!-- <link rel="stylesheet" href="../css/styles.css" type="text/css" />  -->
    </head>
    <body>
        <?php
        # Script 10.3 - edit_user.php
        // This page is for editing a user record.
        // This page is accessed through view_users.php.

        $page_title = 'Edit a User';
        //include ('includes/header.html');
        echo '<h1>Edit a User</h1>';

        // Check for a valid user ID, through GET or POST:
        if ((isset($_GET['id'])) && (is_numeric($_GET['id']))) { // id passed from view_users.php
            $id = $_GET['id'];
            //echo '<script>alert("id=' . $id . '")</script>';
        } elseif ((isset($_POST['id'])) && (is_numeric($_POST['id']))) { // Form submission.
            $id = $_POST['id'];
        } else { // No valid ID, kill the script.
            echo '<p class="error">This page has been accessed in error.</p>';
            //include ('includes/footer.html'); 
            exit();
        }

        require ('ConnectTest.php');

        $sql = " SELECT `id`,`first_name`,`email`, `password`, `votes0`, `votes1`, `votes2` 
                FROM `test`.`entity_user_votes` WHERE `id` = '".$id."' ";

        $result = $conn->query($sql);
        while ($re = $result->fetch_assoc()) {
            // Create the form: look at Lehr's ShopLogin>user>edit_user.php for the code to POST 
            echo '<form action="edit_user.php" method="post"> 
            <p>First Name: <input type="text" name="first_name" size="15" maxlength="15" value="' . $re['first_name'] . '" /></p>
            <p>Last Name: <input type="text" name="last_name" size="15" maxlength="30" value="' . $re['email'] . '" /></p>
            <p>Email Address: <input type="text" name="email" size="20" maxlength="60" value="' . $re['password'] . '"  /> </p>
            <p>votes0: <input type="text" name="votes0" size="20" maxlength="5" value="' . $re['votes0'] . '"  /> </p>
            <p>votes1: <input type="text" name="votes1" size="20" maxlength="5" value="' . $re['votes1'] . '"  /> </p>
            <p>votes2: <input type="text" name="votes2" size="20" maxlength="5" value="' . $re['votes2'] . '"  /> </p>
            <p><input type="submit" name="submit" value="Submit" /></p>
            <input type="hidden" name="id" value="' . $id . '" />
            </form>';
        }

        //include ('includes/footer.html');
        ?>
        <br><button onclick="window.location.assign('../../AdminMenu.html')">Admin Menu</button>
    </body>
</html>
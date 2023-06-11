<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Read Cookie from Javascript and Translate into PHP</title>
         <script type= "text/javascript" src="./assets/javascript/cookies.js"></script>
    </head>
    <body>
        <script type="text/javascript">
            console.log("Hit cookieTransferObject.php");  
            // reads cookie passed from login.html and returns object with cookies key:value pairs
            //var cookie = readCookie();
            //console.log('Hit cookieTransferObject.php. cookie = ' + cookie);
            //console.log('Hit cookieTransferObject.php. cookie\nname='+cookie.name+'\nemail='+cookie.email+'\npassword='+cookie.password);
        </script>
        <?php
            echo "Gotta Read the cookie </br>";
            $text=$_COOKIE["object"];
            echo $text."</br>";
            $myObj = json_decode($text);
            echo '<pre>';
            var_dump($myObj);
            echo '</pre>';
        ?>
    </body>
</html>

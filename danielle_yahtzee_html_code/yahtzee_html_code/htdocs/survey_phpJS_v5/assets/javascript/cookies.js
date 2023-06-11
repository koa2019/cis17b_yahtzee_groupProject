
//********************************************************
// This code is based off Dr. Lehr's JSON_Cookies > CookieFunctions.js
//      https://www.w3schools.com/js/js_cookies.asp
//******************************************************** 
function setCookie(cname, value, expiredays) {
    var d = new Date();
    d.setTime(d.getTime() + (expiredays * 86400)); // 86400 = 1 day
    var expires = "expires=" + d.toUTCString();
    document.cookie = cname + "=" + value + ";" + expires + ";path=/";
    console.log("Hit setCookie(). cookie = " + document.cookie + "\n");
}


//********************************************************
// This code is based off Dr. Lehr's JSON_Cookies > CookieFunctions.js
//      https://www.w3schools.com/js/js_cookies.asp
//********************************************************          
function getCookie(cname) {
    console.log('Hit getCookie()');
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for (var i = 0; i < ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) === ' ') {
            c = c.substring(1);
            ///console.log('Hit getCookie().  c.substring(1) = ' + c + "\n");
        }
        if (c.indexOf(name) === 0) {
            //console.log('Hit getCookie().  c.substring(name.length, c.length) = ' + c.substring(name.length, c.length) + "\n");
            return c.substring(name.length, c.length);
        }
    }
    return "";
}



//********************************************************
// This code is based off Dr. Lehr's JSON_Cookies > CookieFunctions.js
//      https://www.w3schools.com/js/js_cookies.asp
//******************************************************** 
function checkCookie(cname) {
    var value = getCookie(cname);
    if (value !== "") {
        console.log("Hit checkCookie(). Cookie Name = " + cname + "Value = " + value);
        //alert("Cookie Name = " + cname + "Value = " + value);
    } else {
        value = prompt("Please enter your cookie :" + cname + " Value", "");
        if (value !== "" && value !== null) {
            setCookie(cname, value, 365);
        }
    }
    //console.log("Hit checkCookie(). cname = " + cname + ".  Value = " + value + "\n");
}

function getLoginForm(url) {
    console.log('Hit getLoginForm()');//\n url = ' + url);
    // signUp url: http://localhost/survey_phpJS_v4/getSignUpForm.html?name=user1113&email=user1113%40email.com&password=user1113%21&chekPass=user1113%21&Submit=
    // login url:  http://localhost/survey_phpJS_v4/getLoginForm.html?email=marge%40simp.com&password=Marge%2123
    var info = url.split("?");
    //console.log('info = ' + info);
    var nameValuePairs = info[1].split("&");
    //console.log('nameValuePairs = '+ nameValuePairs + '  nameValuePairs.length=' + nameValuePairs.length);
    var $_GET = new Object;
    for (var i = 0; i < nameValuePairs.length; i++) {
        var map = nameValuePairs[i].split("=");
        //console.log('map = ' + map);
        var name = map[0];
        //console.log('name = ' + name);
        var value = map[1];
        //console.log('value = ' + value);
        $_GET[name] = value;
        //console.log('$_GET[' + name + '] = ' + $_GET[name]);        
    }
    return $_GET;
}


function setLoginQueryCookie(url) {

    console.log('Hit setLoginQueryCookie()');
    $_GET = getLoginForm(url);
    var counter = 0;
    var answers = [];
    for (property in $_GET) {
        //console.log("(property in $_GET). " + property + "=" + decodeURIComponent($_GET[property]) + "\n");
        var str = $_GET[property];          //Place property value in string
        var dec = decodeURIComponent(str);  //Convert to ascii
        //https://regex101.com/
        //https://www.cheatography.com/davechild/cheat-sheets/regular-expressions/
        //http://www.mkyong.com/regular-expressions/10-java-regular-expression-examples-you-should-know/
        var clean = dec.replace(/\++/g, ' ');//Remove + and replace by space
        $_GET[property] = clean;            //Cleaned values
        counter++;
        if (counter > 2 && clean !== "")
            answers.push(clean); //Place answers int their own array
    }

    // Use JSON to turn the parsed URL into a string  ???
    var text = JSON.stringify($_GET);
    console.log("UserData JSON.stringify() = " + text + "\n");

    //Write the cookie and check it out
    setCookie("object", text, 1);
    checkCookie("object");
    document.write(getCookie("object"));

    // Print message to html
    var string = (text.length > 0) ? 'Cookie Set.'//(dataArray.length >0)
            : 'Uh-Oh Cookie Not Set. Please try again... ';
    var fileName = (text.length > 0) ? "'./assets/php/selectByEmail.php'" : "'login.html'";

    var msgDiv = document.getElementById('getLoginForm-div');
    var h1 = document.createElement("h1");
    h1.innerHTML = string;
    var btn = document.createElement("button");
    btn.setAttribute('onclick', "location.href=" + fileName);
    btn.innerHTML = 'Query SQL';
    msgDiv.appendChild(h1);
    msgDiv.append(btn);
}

// Function which retrieves the information in a form
// Danielle using Dr. Mark E. Lehr's Example for CSC/CIS 17B
// $_GET object as implemented in PHP
function getForm(url){
    console.log('Hit getForm().\n url = ' + url);
    // signUp url: http://localhost/survey_phpJS_v4/getSignUpForm.html?name=user1113&email=user1113%40email.com&password=user1113%21&chekPass=user1113%21&Submit=
    // login url:  http://localhost/survey_phpJS_v4/getLoginForm.html?email=marge%40simp.com&password=Marge%2123
    var info=url.split("?");
    console.log('info = ' + info);
    var nameValuePairs=info[1].split("&");
    console.log('nameValuePairs = '+ nameValuePairs + '  nameValuePairs.length=' + nameValuePairs.length);
    var $_GET = new Object;
    for(var i=0;i<nameValuePairs.length-1;i++){
        var map=nameValuePairs[i].split("=");
        console.log('map = ' + map);
        var name=map[0];
        console.log('name = ' + name);
        var value=map[1];
        console.log('value = ' + value);
        $_GET[name]=value;
        console.log('$_GET[' + name + '] = ' + $_GET[name]);
        
    }
    return $_GET;
}

//*************************************************************************
//                      Tutorialspoint's cookies      
// https://www.tutorialspoint.com/javascript/javascript_cookies.htm 
//*************************************************************************
function setNewUserCookie(url) {
    console.log("Hit setNewUserCookie()");
    // Grab the info from the form and parse URL 
    // This code is based off Dr. Lehr's JSON_Cookies > getform.html
    //var url = document.location.href;
    $_GET = getForm(url);
    var counter = 0;
    var answers = [];
    for (property in $_GET) {
        console.log("(property in $_GET). " + property + "=" + decodeURIComponent($_GET[property]) + "\n");
        var str = $_GET[property];          //Place property value in string
        var dec = decodeURIComponent(str);  //Convert to ascii
        //https://regex101.com/
        //https://www.cheatography.com/davechild/cheat-sheets/regular-expressions/
        //http://www.mkyong.com/regular-expressions/10-java-regular-expression-examples-you-should-know/
        var clean = dec.replace(/\++/g, ' ');//Remove + and replace by space
        $_GET[property] = clean;            //Cleaned values
        counter++;
        if (counter > 2 && clean !== "")
            answers.push(clean); //Place answers int their own array
    }

    // Use JSON to turn the parsed URL into a string  ???
    var text = JSON.stringify($_GET);
    console.log("UserData JSON.stringify() = " + text + "\n");

    //Write the cookie and check it out
    setCookie("object", text, 1);
    checkCookie("object");
    document.write(getCookie("object"));

    // Print message to html
    var string = (text.length > 0) ? 'Profile Created.\nPlease Login.'//(dataArray.length >0)
            : 'Uh-Oh Profile not created. Please try again... ';
    var fileName = (text.length > 0) ? "'./assets/php/DBInsert.php'" : "'login.html'";

    var msgDiv = document.getElementById('message-div');
    var h1 = document.createElement("h1");
    h1.innerHTML = string;
    var btn = document.createElement("button");
    btn.setAttribute('onclick', "location.href=" + fileName);
    btn.setAttribute('value', 'Click Me');
    btn.innerHTML = 'Click Me';
    msgDiv.appendChild(h1);
    msgDiv.append(btn);
}

// set cookie with id for SQL query
function setIdCookie(cname, value, expiredays) {
    var d = new Date();
    d.setTime(d.getTime() + (expiredays * 86400)); // 86400 = 1 day
    var expires = "expires=" + d.toUTCString();
    document.cookie = cname + "=" + value + ";" + expires + ";path=/";
    alert("Hit setCookie(). cookie = { " + document.cookie + "  }");
    console.log("Hit setCookie(). cookie = " + document.cookie + "\n");
}


function makeButton(id,h1Text,href,val) {
    alert("Hit makeButton()");
    var msgDiv = document.getElementById(id);
    var h1 = document.createElement("h1");
    h1.innerHTML = h1Text;
    var btn = document.createElement("button");
    btn.setAttribute('onclick', "location.href='" + href +"'");
    btn.setAttribute('value', val);
    btn.innerHTML = val;
    msgDiv.append(h1);
    msgDiv.append(btn);
}



//*************************************************************************
//                      Tutorialspoint's cookies      
// https://www.tutorialspoint.com/javascript/javascript_cookies.htm 
// document.cookie string will keep a list of name=value pairs separated by semicolons, 
// where name is the name of a cookie and value is its string value.
// You can use strings' split() function to break a string into key and values as follows 
//*************************************************************************
function readCookie() { // get cookie and returns a object with cookie key:value pairs

    var allcookies = document.cookie;
    console.log("Hit readCookie().  All Cookies : " + allcookies);

    // Get all the cookies pairs in an array
    cookiearray = allcookies.split(';');
    //console.log("All Cookies length : " + cookiearray.length + " Key:Value;\n");

    if (cookiearray.length > 0) {

        var name = [cookiearray.length - 1];
        var value = [cookiearray.length - 1]; // i dont want  to save the expiry date
        var cookieObj = {name: "", email: "", password: "", chekPass: ""};


        // Now take key value pair out of this array
        for (var i = 0; i < cookiearray.length; i++) {

            name[i] = unescape(cookiearray[i].split('=')[0]);
            value[i] = unescape(cookiearray[i].split('=')[1]);

            // Set object key value pairs
            if (i === 0) {        // name
                cookieObj.name = value[0];
            } else if (i === 1) { // email
                cookieObj.email = value[1];
            } else if (i === 2) { // password   
                cookieObj.password = value[2];
            } else if (i === 3) {
                cookieObj.password = value[3];
            }
        }
        //console.log('Hit readCookie()'); console.log(cookieObj);
        return cookieObj;
    }
    return "";
}

//*************************************************************************
//                      Tutorialspoint's cookies      
// https://www.tutorialspoint.com/javascript/javascript_cookies.htm 
//*************************************************************************
function readAllCookies() {
    var allcookies = document.cookie;
    document.write("All Cookies : " + allcookies);

    // Get all the cookies pairs in an array
    cookiearray = allcookies.split(';');

    // Now take key value pair out of this array
    for (var i = 0; i < cookiearray.length; i++) {
        name = cookiearray[i].split('=')[0];
        value = cookiearray[i].split('=')[1];
        document.write("Key is : " + name + " and Value is : " + value);
    }
}

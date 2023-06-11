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
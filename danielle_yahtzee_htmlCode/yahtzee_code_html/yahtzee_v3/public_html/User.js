/* 
 
*/

function User(){   
    //readNumRec();  
    this.namSiz=0;
    this.name="first name";
    this.emaiSiz=0;
    this.email="email@email.com";
    this.pwrdSiz=0;
    this.password="password";  
    this.hiScore=0;
    //alert("Hit User Default constructor");
}

//To String function of the ScoreCard Class
User.prototype.printUser=function(){
    document.write("name = " + this.name + "<br/>");
    document.write("email = " + this.email + "<br/>");
    document.write("password = " + this.password + "<br/>");
};

User.prototype.setName=function(str){
    this.name = str;
};
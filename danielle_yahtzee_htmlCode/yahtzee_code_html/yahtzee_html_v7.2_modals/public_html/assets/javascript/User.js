/* 
 
*/

// Default constructor  Called in Yahtzee.html
function User(){   
    //this.readNumRec();  
    this.id = 0;
    this.name="Guest";
    this.email="email@email.com";
    this.password="password";  
    //console.log("Hit User Default constructor");
}

User.prototype.setUser=function(id, fname, score){
    this.setId(id);
    this.setName(fname);
    this.setHiScore(score);
};

User.prototype.setUser2=function(id, fname){
    this.setId(id);
    this.setName(fname);
};


//To String function of the ScoreCard Class
User.prototype.printUser=function(){
    document.write("id = " + this.getId + "<br/>");
    document.write("name = " + this.getName + "<br/>");
    document.write("email = " + this.getEmail + "<br/>");
    document.write("password = " + this.getPassword + "<br/>");
    document.write("hiScore = " + this.getHiScore + "<br/>");
};

User.prototype.setId=function(num) { 
    this.id = num; 
};

User.prototype.setName=function(str){
    this.name = str;
};

User.prototype.setEmail=function(str){
    this.email = str;
};

User.prototype.setPassword=function(str){
    this.password = str;
};

User.prototype.setHiScore=function(s) {
    this.hiScore = s; 
};

User.prototype.getId=function(){
    return this.id;
};

User.prototype.getName=function(){
    return this.name;
};

User.prototype.getEmail=function(){
    return this.email;
};

User.prototype.getPassword=function(){
    return this.name;
};

User.prototype.getHiScore=function(){
    return this.hiScore;
};

//******************************************************************************
//            Checks if current score is greater than hiScore 
//******************************************************************************
User.prototype.isHiScore=function(score){
    
    if((score > 999 || score < 0)){ return false; }
    // hiScore is formatted for max of 3 digits 
    
    else if(score >= this.hiScore && score > 0) { return true; }
    
    else { return false;}
};


/******************************************************************/              
//                  REWRITE 1 RECORD TO BINARY FILE     
/*****************************************************************/

User.prototype.reWrtRecord=function(){
    console.log("Hit User.reWrtRecord()");
    alert("Hit User.reWrtRecord()");
};
/* 
 
*/

// Default constructor  Called in Yahtzee.html
function User(){   
    //this.readNumRec();  
    this.numRec = 0;
    this.namSiz=0;
    this.name="Guest";
    this.emaiSiz=0;
    this.email="email@email.com";
    this.pwrdSiz=0;
    this.password="password";  
    this.hiScore=0;
    //alert("Hit User Default constructor");
}


// Constructor #2. Called in Yahtzee.js
function User(i){   
    //this.readNumRec(); 
    this.numRec = 0;
    this.namSiz=0;
    this.name="Player "+i;
    this.emaiSiz=0;
    this.email="email@email.com";
    this.pwrdSiz=0;
    this.password="password";  
    this.hiScore=0;
    //alert("Hit User constructor#2");
}

//To String function of the ScoreCard Class
User.prototype.printUser=function(){
    document.write("numRec = " + this.getNumRec + "<br/>");
    document.write("name = " + this.getName + "<br/>");
    document.write("email = " + this.getEmail + "<br/>");
    document.write("password = " + this.getPassword + "<br/>");
    document.write("hiScore = " + this.getHiScore + "<br/>");
};

User.prototype.setNumRec=function(num) { 
    this.numRec = num; 
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

User.prototype.getNumRec=function(){
    return this.numRec;
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

User.prototype.reWrtBin=function(){
    console.log("Hit User.reWrtBin()");
};
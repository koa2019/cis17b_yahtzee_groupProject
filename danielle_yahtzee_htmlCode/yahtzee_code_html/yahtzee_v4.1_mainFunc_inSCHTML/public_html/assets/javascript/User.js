/* 
 
*/

// Default constructor  Called in Yahtzee.html
function User(){   
    //this.readNumRec();  
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
    document.write("name = " + this.name + "<br/>");
    document.write("email = " + this.email + "<br/>");
    document.write("password = " + this.password + "<br/>");
};

User.prototype.setName=function(str){
    this.name = str;
};


User.prototype.setHiScore=function(s) {
    this.hiScore = s; 
};

User.prototype.getName=function(){
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
    console.log("Hit reWrtBin()");
};
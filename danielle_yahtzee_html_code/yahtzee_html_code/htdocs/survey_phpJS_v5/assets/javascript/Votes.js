// Votes Variables
var NUMQQ = 3;
var VOTESIZE = NUMQQ + 1;

//*********************************************************
//                    Default Constructor
//*********************************************************
function Votes() {
    //console.log('Hit Votes Constructor');
    this.numVote = 0;
    this.votes = [NUMQQ];
    for (var i = 0; i < NUMQQ; i++) {
        this.votes[i] = 0;
    }
}

//*********************************************************
//                  Set index in votes array and 
//                  increase numVote by 1
//*********************************************************
Votes.prototype.setVoteIndx = function (i, value){ 
    this.votes[i] = value; 
    this.increNumVote();
};


//*********************************************************
//              Set all elements in votes array
//*********************************************************
Votes.prototype.setVoteArr = function (a, b, c){
    //cout<<"\n\tHit setVotArr()\n";
    this.votes[0] = a;
    this.votes[1] = b;
    this.votes[2] = c;
    this.increNumVote();
    this.increNumVote();
    this.increNumVote();
};

 
//*********************************************************
//              Sets votes[] elements to random numbers
//*********************************************************
Votes.prototype.setRandVotesArr = function (){
    var num = 0;
    for(var i=0; i < NUMQQ; i++){
        num = (rand()%NUMQQ)+1;
        this.votes[i] = num;
        this.increNumVote();                           
    }
};


Votes.prototype.increNumVote = function () {
    this.numVote++;
};


Votes.prototype.increVoteIndx = function (i) {
    this.votes[i]++;
    this.numVote++;
};


//******************************************************************************
//                              Accessors
//******************************************************************************
Votes.prototype.getVote = function (i) {
    return this.votes[i];
};


Votes.prototype.getNumVote = function () {
    return this.numVote;
};  

//*********************************************************
//                  Print votes array 
//*********************************************************  
Votes.prototype.prntVotes = function (){      
    console.log('prntVotes().  votes = [' + this.votes + ' ]');
    var div = document.getElementById('votes-div');
    div.append(this.votes);
};

Votes.prototype.prntNumVotes = function (){  
    console.log(this.getNumVote + " total votes."); 
};

Votes.prototype.consoleVotes = function (){  
    console.log('votes = [ ' + this.votes + ' ]');
};

Votes.prototype.consoleNumVotes = function (){  
    console.log(this.getNumVote() + " total votes."); 
};
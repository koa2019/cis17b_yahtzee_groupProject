// Global constants for Yahtzee Class
const MINSIZE  = 2;
const MAXRND   = 3;
const MAXROLLS = 3;

// Sets up game. Creates 2 player's, 2 possible points scorecards, and final scorecards
function Yahtzee() {

    //alert("Begin of Yahtzee()");    

    // Public properties of Yahtzee class    
    this.setP1Winner(false);
    this.setNPlayer(MINSIZE);
    this.setIndex(0);

    var player    = new Array(MINSIZE);  //User **player = nullptr;   // Aggregates instance of User Class. Array of User's
    var scorecard = new Array(MINSIZE);  //ScoreCard scorecard[2];// Aggregates instance of ScoreCard class
    var finalSC   = new Array(MINSIZE);   //ScoreCard finalSC[2];// Aggregates instance of ScoreCard class

    for (var i = 0; i < scorecard.length; i++) {

        player[i]    = new User();
        scorecard[i] = new ScoreCard();
        finalSC[i]   = new ScoreCard();
    }

    player[0].setName("Homer");
    //document.write(player[0].name + "'s Possible ScoreCard...<br/>");
    //scorecard[0].printScoreCard();
    
    document.write(player[0].name + "'s Final ScoreCard<br/>");
    //finalSC[0].printFinalSC();     
    finalSC[0].printScoreCard(); // prints player1's final entire scores array
    
    document.write("scores[0] = ");
    finalSC[0].getScoreIndex(0); // Prints one element in scores array
    
    //document.write("Starting game...<br/>");
    //this.printYahtzee();
    //this.startGame();
    //startGame();

    // Game runs for 13 rounds. 1 round per category
    for (var rnd = 0; rnd < MAXRND; rnd++) {

        document.write("<br/><br/>Round " + (rnd+1) + "<br/><br/>");         
        finalSC[0].setRound(rnd+1);        
        this.play(0, rnd); 

        if(this.nPlayer > 1 && rnd < MAXRND) {             
            finalSC[1].setRound(rnd+1);
            this.play(1, rnd); 
        }   

    } // ends round for(rnd < 13 )   

    
    console.log("End of Yahtzee()<br/>");
};



//**********************************************************
//              This player's turn
//              a = player's index
//**********************************************************
Yahtzee.prototype.play = function (a, rnd) {

    //alert("Hit play()<br/>");
    //document.write("play()<br/>");
    var resp = 0, 
        numRolls = 0;
    var name = "Player ";
    //var name = this.player[a].name;


    /**********************  START THIS PLAYER'S TURN  *************************/

//    numRolls = 0; // Reset for each player's turn        
//
//    // loop as long as numRolls does NOT equal 3
//    while(!(numRolls === MAXROLLS)){
//
//        
        document.write("<br/>   " + name + "s turn. Round " + (rnd+1) + " Roll " + (numRolls+1) + "<br/>");
//        //pause('r');               // Pause to mimic rolling dice
//        //scorecard[a].setDice();  // Re-Roll Dice
//        numRolls++;             // increment numRolls every time dice are rolled       
//
//
//        // Set & print scorecard with possible points based on dice values
//        //scorecard[a].fillScoreCard();
//        document.write("<br/>      " + name + "'s Possible Points: <br/>");
//        //scorecard[a].printScoreCard();           
//
//
//        resp = 0;
//
//        //if(numRolls == 3){ resp = 2; } // if last roll, force switch case 2 to run
//        //else { displayOptions(resp); } // else offer them options to choose from
//
//        
//        switch(resp){ // choose dice to keep, pick a category, re-roll or exit game
//
//            case 1:  // Select dice you want to keep in between rolls
//            {
//                //selectDice(a);
//                break;
//            }
//            case 2: // Keep points from 1 category and end their turn
//            {
//                numRolls = MAXROLLS; // reassign it, so while(numRolls<maxRolls) stops
//                //selectCategory(a, name, rnd);    
//                break;
//            }
//            case 3: 
//            {    // Roll dice again by breaking out of switch()                 
//                break;
//            }
//            default: // if they exit early, then reset values to break out of 
//            {        // all the loops & print final scorecards
//                
//                document.write("<br/>       <Leaving program><br/>");
//                rnd = MAXRND; 
//                numRolls = MAXROLLS; 
//                //return null;
//            }
//        } // ends switch(resp)  
//    } // ends while(!(numRoll == MAXROLLS))      
};


// Set p1Winner true/false
Yahtzee.prototype.setP1Winner = function (bool) {
    this.p1Winner = bool;
};

// Set number of players
Yahtzee.prototype.setNPlayer = function (num) {
    this.nPlayer = num;
};

// Set index for which player it is in player array
Yahtzee.prototype.setIndex = function (i) {
    this.index = i;
};

//To String function of the ScoreCard Class
Yahtzee.prototype.printYahtzee = function () {
    //alert("Hit printYahtzee()<br/>");
    document.write("p1Winner: " + this.p1Winner + "<br/>");
    document.write("nPlayer " + this.nPlayer + "<br/>");
    document.write("indx " + this.index + "<br/><br/><br/>");
};


//**********************************************************
//              Controls rounds
//**********************************************************
Yahtzee.prototype.startGame = function () {
//function startGame() {

    alert("Hit startGame()");
    document.write("<br/>Hit startGame()<br/>");
    // Reset player 1's name with user's name
    //player[indx[0]]->setName(user.getName());    

    // Create array for player's name
    //string name[nPlayer] = {player[indx[0]]->getName(), player[indx[1]]->getName() };

    //setNPlayer();  // Get number of players
    //getRules(); // Print rules    


    // if more than 1 player, then print message 
    //if(nPlayer > 1){  cout << endl << setw(20) << name[0] << setw(4) << " vs " << name[1] << endl; } 
    //pause();


    // Game runs for 13 rounds. 1 round per category
    //for (var rnd = 0; rnd < 13; rnd++) {


    //prntRound(rnd);  
    //this.finalSC[indx[0]].toString();
    //finalSC[indx[0]].setRound(rnd+1);
    //play(indx[0], rnd); 

    //if(this.nPlayer > 1 && rnd < MAXRND) {             
    //finalSC[indx[1]].setRound(rnd+1);
    //play(indx[1], rnd); 
    //}   

    //} // ends round for(rnd < 13 )            

    //setP1Winner(finalSC, name);  // Print player's final scorecards

    //    if(!this.p1Winner){ // if player 1 is NOT winner
    //        
    //        document.write("<br/><br/>Good Game!<br/>"; 
    //        //return false; 
    //        
    //    } else {
    //        alert("check hiScore");
    //        //return isNewHiScore(user,recordLoc); // return whether or not p1 has new hiScor
    //    }
};


//******************************************
//              Print round
//******************************************
//Yahtzee.prototype.printRound=function(i){
//    
//    i = (i < 0 ) ? 0 : i;    
//    document.write("<br/><br/>Round " + (i+1) + "<br/><br/>");
//};


//To do: selectDice(a), selectCategory(a, name, rnd), setFinalSC(), setHiScore()

// Global constants for Yahtzee Class
const MINSIZE = 2;
const MAXROLLS = 3;
const MAXRND = 13; //NUM_CATGRY;


// Event listener for scorecard categories
function handleClick(){
    
    // get the value you want to assign to the button
    var value = 2;

    // set the button's value to the value entered by the user
    this.value = value;

    // display the value on the button
    this.innerHTML = value;

    // remove the event listener so that the button becomes static
    this.removeEventListener("click", handleClick);

    const buttons = document.querySelectorAll('button'); // select all button elements

    for (const button of buttons) {
        button.addEventListener('click', () => {
            button.style.backgroundColor = 'transparent'; // remove the hover effect by setting the background color to transparent
        });
    }
}


// Sets up game. Creates 2 player's, 2 possible points scorecards, and final scorecards
function Yahtzee() {
    // Public properties of Yahtzee class    
    console.log("Hit Yahtzee()");   
    this.setP1Winner(false);
    this.setNPlayer(MINSIZE);
    this.setIndex(0);   
    //document.getElementById("nPlayerSubmit").addEventListener("click", this.getNPlayer);
}


//**********************************************************
//              Controls rounds
//**********************************************************
Yahtzee.prototype.startGame = function (user) {

    console.log("Hit startGame()");
    var player = new Array(MINSIZE);  //User **player = nullptr;   // Aggregates instance of User Class. Array of User's
    var scorecard = new Array(MINSIZE);  //ScoreCard scorecard[2];// Aggregates instance of ScoreCard class
    var finalSC = new Array(MINSIZE);   //ScoreCard finalSC[2];// Aggregates instance of ScoreCard class

    for (var i = 0; i < scorecard.length; i++) {

        player[i] = new User(i + 1);
        scorecard[i] = new ScoreCard();
        finalSC[i] = new ScoreCard();
    }
    
    // Reset player 1's name with user's name
    player[0].setName(user.getName());//player[indx[0]]->setName(user.getName());    


    // Create array for player's name
    var name = [player[0].getName(), player[1].getName()];

    //****BUG: addEventListener isn't working******
    // write html div for getNPlayers() to ScoreCard.html
    //var nPlayDiv = document.getElementById("nPlayersDiv");
    //var string = '<label><br/><br/>How many players?<br/></label>';
    //string += '<select name="nPlayers" id="nPlayers-select">';
    //string += '<option value="1">1</option><option value="2">2</option></select>';
    //string += '<button type="submit" id="nPlayerSubmit">Submit</button>';
    //nPlayDiv.innerHTML = string;                    
    //document.getElementById("nPlayerSubmit").addEventListener("click", this.getNPlayer);
    this.getNPlayer();  // Get number of players
    
    
    //******** MOVE THIS TO getNPlayer() after getNPlayer() alert works ****************
    var numPlay = 1;//2
    //numPlay = document.getElementById("nPlayers-select").value; //cin>>num;
    //console.log("nPlay = " + numPlay);     
    this.setNPlayer(numPlay);
    //*******************************************************************
    
    console.log("this.nPlayer=" + this.nPlayer);
    //this.getRules();   // Print rules    



    // if more than 1 player, then print welcome message 
    if (this.nPlayer > 1) {
        var string = name[0] + " vs " + name[1];
        alert(string);
    }
    
    //this.pause();


    // Game runs for MAXRND = 13 rounds. 1 round per category
    for (var rnd = 1; rnd <= 1; rnd++) {

        finalSC[0].setRound(rnd); // set round in final ScoreCard
        string = "Round " + finalSC[0].getRound();
        document.getElementById("roundDiv").innerHTML = string;//.append(string);
        
        this.play(player, scorecard, finalSC, 0);

        //if there's 2 players and round is less than or equal to MAXRND
        if (this.nPlayer > 1 && (finalSC[0].getRound() <= MAXRND)) {
            finalSC[1].setRound(rnd); // set round in final ScoreCard
            this.play(player, scorecard, finalSC, 1);
        }
    } // ends round for(rnd < 13 )            

    console.log("Outside of rounds loop");
//    //this.p1Winner = this.getP1Winner(player, finalSC);  // Print player's final scorecards
//    //var isTrue = this.getP1Winner(player, finalSC);  // Print player's final scorecards
//    this.getP1Winner(player, finalSC, 0);  // Print player's final scorecards
//    
//    
//    finalSC[0].setRound(finalSC.NUM_CATGRY);               // Set round to last round for each player, so it'll 
//    finalSC[1].setRound(finalSC.NUM_CATGRY);               // check if they hit upperScore bonus in printFinalSC()
//    finalSC[0].printFinalSC( player[0].getName() );// Print player 1's final scorecard 
//    
//    // if 2 players, then print player 2's final scorecard
//    if(this.nPlayer > 1) { finalSC[1].printFinalSC( player[1].getName() ); }  // Print player 2's final scorecard 
//    
//    document.write("<br/><br/>   Game Over!<br/>");
//    
//    // if nPlayer === 1, then p1 automatically winner
//    if(this.nPlayer === 1) { this.p1Winner = true; } 
//    
//    else { // If there is more than 1 player
//    
//        document.write("<br/>"+ player[0].getName() + " vs " + player[1].getName() + "<br/>");
//        document.write(player[0].getHiScore() + "     vs " + player[1].getHiScore());
//        
//        var msg = "";
//        
//        // Check is p1 is winner, tie or loser
//        if( player[0].getHiScore() > player[1].getHiScore() )
//        {
//           msg = player[0].getName() + " won!\n"; 
//           this.p1Winner = true;
//            
//        } else if(player[0].getHiScore() === player[1].getHiScore()){
//        
//            msg ="Tie Game!\n";
//            this.p1Winner = true;
//            
//        } else { 
//            
//            this.p1Winner = false; 
//            msg = "Uh-Oh..." + player[1].getName() + " won!\n";
//        }
//        
//        document.write("<br/>"+ msg +"<br/>");        
//    }
//
//
//    if (!this.p1Winner) { // if player 1 is NOT winner
//
//        //alert("p1Winner===false"); 
//        document.write("<br/><br/>Good Game!<br/>");
//        return false;
//
//    } else {
//        return this.isNewHiScore(user, player[0].getHiScore()); // return whether or not p1 has new hiScor
//    }
//
    console.log("End of startGame()");
};



//*****************************************************************
//          Get winner and Print player's final scorecard 
//*****************************************************************
//Yahtzee.prototype.isNewHiScore = function (user, p1HiScore) {
//
//    console.log("Hit isNewHiScore()");
//
//    /* Player 1 represents the user object. ONLY change their values if p1 wins.
//     Check is p1's score from this game is larger than their hiScore stored in binary file */
//    if (user.isHiScore(p1HiScore)) {
//
//        // Reset user's hiSCore and update binary & text file            
//        user.setHiScore(p1HiScore);
//
//        document.write("<br/>New High Score of " + user.getHiScore() + "!<br/>");
//        console.log("user New hiScore = " + user.getHiScore());
//
//        // Certain printout depending on if User is logged in or not
//        //if(user.getName() === "Guest"){ document.write("<br/>Sign up or Login to save your score.<br/>");
//
//        return true; // player 1 HAS new high score                
//    }
//
//    return false; // player 1 does NOT have new high score 
//};


//**********************************************************
//              This player's turn
//              a = player's index
//**********************************************************
Yahtzee.prototype.play = function (player, scorecard, finalSC, pIndx) {

    console.log("Hit play()");
    var resp = 0,
            numRolls = 0,
            rnd = finalSC[pIndx].getRound(),
            name = player[pIndx].getName();

    /**********************  START THIS PLAYER'S TURN  *************************/

    numRolls = 0; // Reset for each player's turn   

    // loop as long as numRolls does NOT equal 3
    while (!(numRolls === MAXROLLS)) {


        var string = name + "s turn. Roll " + (numRolls + 1);
        document.getElementById("rollDiv").innerHTML = string;//.append(string);
        //pause('r');          //replace with addEventListener to mimic rolling dice
        scorecard[pIndx].setDice();   // Re-Roll dice     
        numRolls++;                  // increment numRolls every time dice are rolled       


        // Set & print scorecard with possible points based on dice values
        scorecard[pIndx].fillScoreCard();
//
//        resp = 0;
//
//        // if it is last roll, force switch case 2 to run
//        if (numRolls === MAXROLLS) {
//            resp = 2;
//        }
//
//        // else offer them options to choose from
//        else {
//            resp = this.displayOptions();
//        }
//        //console.log("resp = " + resp);
//        
//        
//        switch (resp) { // choose dice to keep, pick a category, re-roll or exit game
//
//            case 1:  // Select dice you want to keep in between rolls
//            {
//                this.selectDice(scorecard, pIndx);
//                break;
//            }
//            case 2: // Keep points from 1 category and end their turn
//            {
//                numRolls = MAXROLLS; // reassign it, so while(numRolls<maxRolls) stops
//
//
//                // Ask player to pick category & set player's final scorecard's points each time they choose a category         
//                finalSC[pIndx].setFinalSC(scorecard[pIndx]); //selectCategory(a, name, rnd); 
//
//
//                // reset player's hiScore each time finalSC is changed
//                finalSC[pIndx].setUpLowSums();
//                player[pIndx].setHiScore(finalSC[pIndx].getTotalScore());
//                //console.log("<br/>" + name + "'s hiScore = " + player[pIndx].getHiScore() + "<br/>");
//
//
//                // if it is NOT the last round, then print player's final scorecard
//                if (!(rnd === MAXRND)) {
//                    finalSC[pIndx].printFinalSC(name);
//
//                } else { // If it IS the last round AND there are 2 players,
//                        // AND it's player 1's turn, then print their final scorecard
//
//                    if ((this.nPlayer > 1) && (pIndx === 0)) {
//                        finalSC[pIndx].printFinalSC(name);
//
//                    } else {
//                        document.write("<br/>  Tallying final score...<br/>");
//                        this.pause();
//                    }
//                }
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
//                finalSC[0].setRound(finalSC.NUM_CATGRY); // set round in final ScoreCard to end game
//                numRolls = MAXROLLS;
//                return;
//            }
//        } // ends switch(resp)  
    } // ends while(!(numRoll == MAXROLLS))    
};

    
//*****************************************************************
//              Select dice player wants to keep
//*****************************************************************
//Yahtzee.prototype.selectDice=function(scorecard, pIndx) {
//
//    console.log("Hit selectDice()");
//    
//    pIndx = (pIndx<0) ? 0 : pIndx;
//    
//    var choice = 0;
//    
//    document.write("<br/><br/>Enter the dice numbers (1-5) to keep, separated by spaces,<br/>or -1 to stop: <br/>");
//
//    // Validate user's input
//    //while (!(cin >> choice) || (choice !== -1 && (choice < 1 || choice > NUM_DICE))) {
//        //cout << "Invalid choice. Please enter a number between 1 and " << NUM_DICE << ", or -1 to stop: ";
//        //cin.clear();
//        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    //}
//
//    choice = 1;
//    // Push the dice they WANT OR DON'T into vector? 
//    while (!(choice === -1)) {       
//        scorecard[pIndx].pushThisDice(choice);
//        document.write("<br/>Keeping Dice" + choice + ": " + scorecard[pIndx].getDice(choice-1)+"   ");
//        //cin >> choice;  
//        
//        choice = -1;
//    }
//};
//
//
//
////*****************************************************************
////          Get winner and Print player's final scorecard 
////*****************************************************************
//
//Yahtzee.prototype.getP1Winner = function (player, finalSC, indx) {
//
//    alert("Hit getP1Winner()"+indx);
//    document.write("<br/>####### Hit getP1Winner()<br/>");
//    console.log("<br/>####### Hit getP1Winner()<br/>");
//    finalSC[indx].setRound(13);            // Set round to last round for each player, so it'll 
////    finalSC[1].setRound(NUM_CATGRY);            // check if they hit upperScore bonus in printFinalSC()
////    finalSC[0].printFinalSC(player[0].getName());    // Print player 1's final scorecard 
////
////    if (this.nPlayer > 1) {
////        finalSC[1].printFinalSC(player[1].getName());
////    }  // Print player 2's final scorecard 
////
////    document.write("<br/><br/>   Game Over!<br/>");
////
////    // if nPlayer == 1, then p1 automatically winner
////    if (this.nPlayer === 1) {
////        return true;
////    } else { // If there is more than 1 player
////
////        document.write("<br/>" + player[0].getName() + " vs " + player[1].getName() + "<br/>");
////        document.write(player[0].getHiScore() + "     vs " + player[1].getHiScore());
////
////        var msg = "";
////
////        // Check is p1 is winner, tie or loser
////        if (player[0].getHiScore() > player[1].getHiScore())
////        {
////            msg = player[0].getName() + " won!\n";
////            document.write("<br/>" + msg + "<br/>");
////            return true;
////
////        } else if (player[0].getHiScore() === player[1].getHiScore()) {
////
////            msg = "Tie Game!\n";
////            document.write("<br/>" + msg + "<br/>");
////            return true;
////
////        } else {
////
////            msg = "Uh-Oh..." + player[1].getName() + " won!\n";
////            document.write("<br/>" + msg + "<br/>");
////            return false;
////        }       
////    }
//};
//
//
////*****************************************************************
////        Print player's options and return their choice
////*****************************************************************
//Yahtzee.prototype.displayOptions = function () {
//
//    document.write("\nOptions:<br/>");
//    document.write("1: Select which dice you want to keep\n   before rolling again.<br/>");
//    document.write("2: Pick category and end your turn<br/>");
//    document.write("3: Roll again.<br/>");
//    document.write("4: Exit<br/>");
//    document.write("Enter a number: ");
//    document.write('<input type="text" id="choice" name="name" required size="10">');
//    document.write('<button type="submit">Enter</button>');
//    //cin>>resp;
//    resp = 1;
////    resp = document.getElementById("choice").value;
////
////    while (!(resp < 1 || resp > 4)) {
////        document.write("Invalid choice. Please enter a number between 1 and 3: ");
////        //cin.clear();
////        resp = document.getElementById("choice").value;
////    }
//    return resp;
//};


//****************************************************
//              Get # of player & validate input
//****************************************************
Yahtzee.prototype.getNPlayer = function () {

    console.log("Hit getNPlayer()");
    
//    var numPlay = 1;
//    numPlay = document.getElementById("nPlayers-select").value; //cin>>num;
//    console.log("nPlay = " + numPlay);     
//    this.setNPlayer(numPlay);
//    document.getElementById("nPlayersDiv").style.visibility = "hidden"; // "visible";
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

// Get p1Winner true/false
Yahtzee.prototype.getP1Winner = function () {
    return this.p1Winner;
};


// Get number of players
Yahtzee.prototype.getNPlayer = function () {
    return this.nPlayer;
};


// Get index for which player it is in player array
Yahtzee.prototype.getIndex = function () {
    return this.index;
};


// To String function of the ScoreCard Class
//Yahtzee.prototype.printYahtzee = function () {
//    //alert("Hit printYahtzee()<br/>");
//    document.write("p1Winner: " + this.getP1Winner() + "<br/>");
//    document.write("nPlayer " + this.getNPlayer() + "<br/>");
//    document.write("indx " + this.getIndex() + "<br/><br/><br/>");
//};

//*****************************************************************
//              Select category to save to final scorecard
//*****************************************************************
//Yahtzee.prototype.selectCategory = function (a, name, rnd) {
//
//    a = (a < 0) ? 0 : a;
//    rnd = (rnd < 0) ? 0 : rnd;
//};


//******************************************
//      pause screen before continuing
//******************************************
//Yahtzee.prototype.pause = function (ch) {
//
//    var msg = (ch === 'r') ? "roll." : "continue.";
//    document.write("<br/>Press enter to " + msg + "<br/>");
//    //cin.get(); // captures enter from keyboard
//};


//******************************************
//          Print Yahtzee rules
//******************************************
Yahtzee.prototype.getRules = function () {
//
////    cout << "WELCOME TO YAHTZEE!!" << endl << endl;
////    cout << "RULES: " << endl << endl << endl;
////    cout << "Yahtzee is a game played with five dice, where the objective is to score as many points as possible in 13 rounds." << endl;
////    cout << "Each player takes turns rolling the dice up to three times per turn, trying to achieve certain combinations." << endl;
////    cout << "After each turn, the player must choose a category to score their points in, and that category cannot be used again." << endl << endl;
////    cout << endl;
////    cout << "______________________________________________________________________________________________________________________" << endl;
////    cout << "The categories are as follows:" << endl;
////    cout << "1. Ones: Score the sum of all dice showing the number 1." << endl;
////    cout << "2. Twos: Score the sum of all dice showing the number 2." << endl;
////    cout << "3. Threes: Score the sum of all dice showing the number 3." << endl;
////    cout << "4. Fours: Score the sum of all dice showing the number 4." << endl;
////    cout << "5. Fives: Score the sum of all dice showing the number 5." << endl;
////    cout << "6. Sixes: Score the sum of all dice showing the number 6." << endl;
////    cout << "7. Three of a Kind: If at least three dice show the same number, score the sum of all dice." << endl;
////    cout << "8. Four of a Kind: If at least four dice show the same number, score the sum of all dice." << endl;
////    cout << "9. Full House: If three dice show one number and the other two dice show another number, score 25 points." << endl;
////    
////    // Categories 10-13 are only available after the first six rounds:
////    cout << "10. Small Straight: If the dice show any sequence of four numbers, score 30 points." << endl;
////    cout << "11. Large Straight: If the dice show any sequence of five numbers, score 40 points." << endl;
////    cout << "12. Yahtzee: If all five dice show the same number, score 50 points." << endl;
////    cout << "13. Chance: Score the sum of all dice, regardless of category." << endl;
////    cout << "______________________________________________________________________________________________________________________" << endl;
};
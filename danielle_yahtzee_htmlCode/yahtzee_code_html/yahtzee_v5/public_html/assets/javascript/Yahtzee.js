//To do: selectDice(a), selectCategory(a, name, rnd), setFinalSC(), setHiScore()

// Global constants for Yahtzee Class
const MINSIZE = 2;
const MAXROLLS = 3;
const MAXRND = 13;

// Load this function's elements first
function main(user) {

    // Create Yahtzee object and start game
    var yahtzee = new Array();
    yahtzee = new Yahtzee();
    
    // Aggregate Array of User Class
    var player = new Array(MINSIZE);
    player[0] = new User(1);
    player[1] = new User(2);   
    
    // Aggregate Array of ScoreCard Class
    var scorecard = new Array(MINSIZE);
    var finalSC = new Array(MINSIZE);

    for (var i = 0; i < MINSIZE; i++) {
        scorecard[i] = new ScoreCard();  // possible scorecard points. Aggregates Array of ScoreCard class
        finalSC[i] = new ScoreCard();   // final scorecard. Aggregates Array of ScoreCard class
    }
    
    const SCobj = {player, scorecard, finalSC}; // combine objects


    // add event listeners to all buttons with class "category-button"
    var buttons = document.getElementsByClassName("category-button");
    for (var i = 0; i < buttons.length; i++) {
        buttons[i].addEventListener("click", this.catgyOnClick2);
    }    
      
    
    // start Game
    var isHiScore = false;
    isHiScore = yahtzee.startGame(user,SCobj);
    console.log("main(). p1 isHiScore === " + isHiScore);
    if (isHiScore === true) {
        user.reWrtBin();// rewrites this record in database
        //alert("Updating binary...."); 
        console.log("Updating binary....");
    }
}


//*****************************************************************
//  Yahtzee Constructor. Public properties of Yahtzee class 
//*****************************************************************

function Yahtzee() {
    //console.log("Hit Yahtzee()");   
    this.setP1Winner(false);
    this.setNPlayer(1);//MINSIZE
    this.setIndex(0);
    this.menuChoice = 0; // User menuChoice made during play()  
    this.printNPlayrDiv();     
    //this.printMenu(); // write to ScoreCard.html
    //this.printSelectDiceDiv(); 
}




//**********************************************************
//              Controls rounds
//**********************************************************
Yahtzee.prototype.startGame = function (user, SCobj) {
    
    console.log("Hit startGame().  this.nPlayer=" + this.nPlayer);   
    document.getElementById("diceCol").style.visibility = "visible";//"hidden"; 
    document.getElementById("scorecardCol").style.visibility = "visible";//"hidden"; 
    
    SCobj.player[this.index].setName(user.getName());// Reset player 1's name with user's name
    var name = [SCobj.player[this.index].getName(), SCobj.player[1].getName()];// Create array for player's name
    this.getRules();   
    this.welcomeMsg(name);          // print welcome message depending on num players


    // Game runs for MAXRND = 13 rounds. 1 round per category
    for (var rnd = 1; rnd <= 1; rnd++) {

        SCobj.finalSC[this.index].setRound(rnd); // set & write round to ScoreCard.html
        this.play(SCobj.player[this.index], SCobj.scorecard[this.index], SCobj.finalSC[this.index]);

        //if there's 2 players and round is less than or equal to MAXRND
        if (this.nPlayer > 1 && (SCobj.finalSC[this.index].getRound() <= MAXRND)) {
            this.setIndex(1);
            SCobj.finalSC[this.index].setRound(rnd); // set round in final ScoreCard
            this.play(SCobj.player[this.index], SCobj.scorecard[this.index], SCobj.finalSC[this.index]);
        }
        this.setIndex(0);
    } // ends round for(rnd < 13 )           


//    SCobj.finalSC[0].setRound(13);       // Set round to last round for each player, so it'll 
//    SCobj.finalSC[1].setRound(13);       // check if they hit upperScore bonus in printFinalSC()
//    SCobj.finalSC[0].printFinalSC(SCobj.player[0].getName());// Print player 1's final scorecard 
//    
//    // if 2 players, then print player 2's final scorecard
//    if(this.nPlayer > 1) { SCobj.finalSC[1].printFinalSC( SCobj.player[1].getName() ); }  // Print player 2's final scorecard 
//    
//    console.log("Game Over!<br/>");
//    
//    // if nPlayer === 1, then p1 automatically winner
//    if(this.nPlayer === 1) { this.p1Winner = true; } 
//    
//    else { // If there is more than 1 player
//    
//        console.log("<br/>"+ SCobj.player[0].getName() + " vs " + SCobj.player[1].getName() + "<br/>");
//        console.log(SCobj.player[0].getHiScore() + "     vs " + SCobj.player[1].getHiScore());
//        
//        var msg = "";
//        
//        // Check is p1 is winner, tie or loser
//        if( SCobj.player[0].getHiScore() > SCobj.player[1].getHiScore() )
//        {
//           msg = SCobj.player[0].getName() + " won!<br>"; 
//           this.p1Winner = true;
//            
//        } else if(SCobj.player[0].getHiScore() === SCobj.player[1].getHiScore()){
//        
//            msg ="Tie Game!\n";
//            this.p1Winner = true;
//            
//        } else { 
//            
//            this.p1Winner = false; 
//            msg = "Uh-Oh..." + SCobj.player[1].getName() + " won!\n";
//        }
//        
//        SCobj.console.log("<br/>"+ msg +"<br/>");        
//    }
//
//
//    if (!this.p1Winner) { // if player 1 is NOT winner
//
//        //alert("p1Winner===false"); 
//        console.log("<br/><br/>Good Game!<br/>");
//        return false;
//
//    } else {
//        return this.isNewHiScore(user, SCobj.player[0].getHiScore()); // return whether or not p1 has new hiScor
//    }

    console.log("End of startGame()");
};


//**********************************************************
//              This player's turn
//              a = player's index
//**********************************************************
Yahtzee.prototype.play = function (player, scorecard, finalSC) {

    var numRolls = 0,
            rnd = finalSC.getRound(),
            name = player.getName();
    console.log("Hit play().  "+name+"'s turn");

    /**********************  START THIS PLAYER'S TURN  *************************/

    numRolls = 0; // Reset for each player's turn   

    // loop as long as numRolls does NOT equal 3
    while (!(numRolls === MAXROLLS)) {


        var string = name + "'s turn. Roll " + (numRolls+1);
        console.log("                                       "+string);
        document.getElementById("rollDiv").innerHTML = string;//.append(string);
        //this.pause('r');          //replace with addEventListener to mimic rolling dice
        scorecard.reRoll();   // Re-Roll dice   
        numRolls++;                  // increment numRolls every time dice are rolled       


        // Set & print scorecard with possible points based on dice values
        scorecard.fillScoreCard();
        
    
        // if it is last roll, force switch case 2 to run
        if (numRolls === MAXROLLS) {
            this.menuChoice = 2;
            resp =  this.menuChoice;
            console.log("Hit numRolls === MAXROLLS.  menuChoice = " + resp);
        } else {            
            this.menuChoice = 1;
            resp =  this.menuChoice;
            //var resp = this.checkMenuChoice();
            console.log("Hit numRolls < MAXROLLS.  menuChoice = " + resp);
        }        
        //console.log("In play()  resp = " + resp);


        switch (resp) { // choose dice to keep, pick a category, re-roll or exit game

            case 1:  // Select dice you want to keep in between rolls
            {
                console.log("Hit switch case 1");
                this.selectDice(scorecard, this.index); 
                break;
            }
            case 2: // Keep points from 1 category and end their turn
            {
                console.log("Hit switch case 2");
                numRolls = MAXROLLS; // reassign it, so while(numRolls<maxRolls) stops


                // Ask player to pick category & set player's final scorecard's points each time they choose a category         
                finalSC.setFinalSC(scorecard); //selectCategory(a, name, rnd); 


                // reset player's hiScore each time finalSC is changed
                finalSC.setUpLowSums();
                player.setHiScore(finalSC.getTotalScore());
                console.log(name + "'s hiScore = " + player.getHiScore());


                // if it is NOT the last round, then print player's final scorecard
                if (!(rnd === MAXRND)) {
                    //finalSC.printFinalSC(name);

                } else { // If it IS the last round AND there are 2 players,
                     // AND it's player 1's turn, then print their final scorecard

                    if ((this.nPlayer > 1) && (this.index === 0)) {
                        //finalSC.printFinalSC(name);

                    } else {
                        alert("Tallying final score...");
                        console.log("Tallying final score...");
                        this.pause();
                    }
                }
                break;
            }
            case 3:  // Roll dice again by breaking out of switch()
            {
                console.log("Hit switch case 3. Reroll");                          
                break;
            }
            default: // if they exit early, then reset values to break out of 
            {        // all the loops & print final scorecards

                alert("Hit switch default...<Leaving program>");
                console.log("           Hit switch default...Leaving program");
                finalSC[0].setRound(finalSC.NUM_CATGRY); // set round in final ScoreCard to end game
                numRolls = MAXROLLS;
                //return;
            }
        } // ends switch(this.menuChoice)  
        console.log("Hit end of switch. numRolls = "+numRolls); console.log("");
    } // ends while(!(numRoll == MAXROLLS))  
    console.log(""); console.log("");
};

//*****************************************************************
//          Write menu for play() on html
//          Return player's input and set this.menuChoice
//*****************************************************************
Yahtzee.prototype.checkMenuChoice = function () {

    this.printMenu();
    //document.getElementById("menuDiv").style.visibility = "visible";
    //this.menuChoice = 1;
    this.setMenuChoice(1 + (Math.floor(Math.random() * 3)));
    console.log("Hit checkMenuChoice() this.menuChoice = " + this.getMenuChoice());
    return this.getMenuChoice();
};



//*****************************************************************
//              Select dice player wants to keep
//*****************************************************************
Yahtzee.prototype.selectDice = function (scorecard) {

    console.log("Hit selectDice()");  
    
    //document.getElementById("selectDiceDiv").style.visibility = "visible";//"hidden"; 
    var ans = (1 + (Math.floor(Math.random() * 5)));
    var string = "Select the dice numbers (1-5) to keep, or Click button to stop:";
        
    // Push the dice they WANT OR DON'T into vector? 
    do {
        ans = this.printSelectDiceDiv(scorecard);
        console.log("ans="+ans);
        //ans = prompt(string); //cin >> menuChoice; 
        //console.log("  selectDice().  ans="+ans); 
        
        // THIS SHOULD BE IN diceOnClick(), BUT IT WONT WORK IN THERE
        scorecard.pushThisDice(ans - 1);
        console.log("      In selectDice().  ans="+(ans-1)+"  Keeping Dice" + (ans-1) + ": " + scorecard.getDice(ans - 1));
        ans=0;
    } while ((ans === 1) || (ans === 2) || (ans === 3) || (ans === 4) || (ans === 5));
    //} while ((ans === '1') || (ans === '2') || (ans === '3') || (ans === '4') || (ans === '5'));
};


//*****************************************************************
//                   Writes prompt to get User's input
//*****************************************************************
Yahtzee.prototype.printSelectDiceDiv = function (scorecard) {
    
    console.log("   Hit printSelectDiceDiv()");   
            
        
    var div = document.getElementById('selectDiceDiv');
    var string = "<br><p>Select the dice numbers (1-5) to keep, or Click button to stop:</p>";
    //string += '<input type="text" id="selectDiceInput" name="selectDiceInput" min="1" max="1" required size="1">';
    string += '<button type="submit" id="selectOnClick">Stop</button><br>'; //onclick="menuOnClick()"
    div.innerHTML = string;
    
    
    // add event listeners to all buttons with class "category-button"
    var diceBtn = document.getElementsByClassName("dice");
    for (var i = 0; i < diceBtn.length; i++) {
        diceBtn[i].addEventListener("click", this.diceOnClick);//this.diceOnClick(scorecard));
    }
    
    
    // add event listener to select button in id=selectDiceDiv
    var selectBtn = document.getElementById("selectOnClick");
    selectBtn.addEventListener("click", this.selectOnClick);    
    
    var ans = -66;
    //var ans = prompt(string); //cin >> menuChoice; 
    //console.log("  selectDice().  ans="+ans); 
    return ans;
    
};

//*****************************************************************
//              Handle Event listener for each dice button
//*****************************************************************

Yahtzee.prototype.diceOnClick = function (scorecard) {
    
    console.log("Hit diceOnClick()");
    var temp_indx = 0;
    temp_indx = this.name;
    temp_indx *=1;    
   
    var keep = [];
    keep.push(temp_indx);
    alert("Hit diceOnClick().  dice.name=" + temp_indx + "  dice.value=" + this.value+"  keep="+keep);
    console.log("Hit diceOnClick().  dice.name=" + temp_indx + "  dice.value=" + this.value+"  keep="+keep);
    console.log("keep="+keep );
    
    //  I NEED THIS TO WORK. IT WORKS IN selectDice()
    //scorecard.pushThisDice(temp_indx);
    
    
    //this.removeEventListener("click", diceOnClick);  // remove the event listener so that the button becomes static
    //this.setKeepDice(keep);
};

//*****************************************************************
//            
//*****************************************************************
Yahtzee.prototype.setKeepDice = function (keep) {
    for(var i=0;i<5;i++){
        this.keepDice[i] = keep[i];
    }
    alert("Hit setKeepDice(). keepDice="+this.keepDice);
};

//*****************************************************************
//    Handle Event listener to stop selecting dice you want to save
//*****************************************************************

Yahtzee.prototype.selectOnClick = function () {
    console.log("Hit selectOnClick()");
    var stop = true;    
    //alert("Hit selectOnClick().  this.value=" + this.value);
    //this.removeEventListener("click", diceOnClick);  // remove the event listener so that the button becomes static
    return stop;
};



//*****************************************************************
//      Handle Event listener for each scorecard categories' button
//*****************************************************************
Yahtzee.prototype.catgyOnClick1 = function () {
      
    alert("Hit yaht catgyOnClick().  this.value=" + this.value);
    //alert("this.name=" + this.name);

    // remove the event listener so that the button becomes static
    this.removeEventListener("click", this.catgyOnClick);

    // select all button elements
    const buttons = document.querySelectorAll('button'); 
    // remove the hover effect by setting the background color to transparent
    for (const button of buttons) {
        button.addEventListener('click', () => {
            button.style.backgroundColor = 'transparent'; 
        });
    }
};
//*****************************************************************
//        Handle Event Listener for each scorecard categories' button
//*****************************************************************
Yahtzee.prototype.catgyOnClick2 = function () {    
   
    var input = this.value;
    var i = 0;
    i = this.name;
    
    //resp = document.getElementById('catgyInput').value; //cin>>resp;
    console.log("Hit catgyOnClick2() value="+input+"  this.name=" + i);
    input *= 1;
    i *= 1;
    var num = Number(i);//parseInt(i);
    
    console.log("Hit SC catgyOnClick().   typeof i = "+ typeof i + " = "+i);
    console.log("Hit SC catgyOnClick().   typeof num = "+ typeof num + " = "+num);    
    console.log("          Hit catgyOnClick().  this.wasPicked[ "+this.wasPicked);
     
     
    // Conditional stops a category from being overwritten on final scorecard
    if (this.wasPicked[num] === true) {
        alert("Category " + i + " has already been selected.<br/>Choose another category:  ");
    }

    // Set points in player's final scoreboard
    this.scores[num] = input;

    // set flag so this category, so it can't be selected anymore
    this.wasPicked[num] = true;
    this.wasPicked[num] = true;


    console.log("finalSC.scores[" + num + "] = " + this.scores[num] + "<br/>");
    console.log("finalSC.wasPicked[" + num + "]   = " + this.wasPicked[num]);
    console.log("scorecard.wasPicked[" + num + "] = " + scorecard.wasPicked[num]);
};




//*****************************************************************
//                   Writes menu for play() 
//*****************************************************************
Yahtzee.prototype.printMenu = function () {
    var msgDiv = document.getElementById('menuDiv');
    var string = "<br> Options: <br>";
    string += "1: Select which dice you want to keep before rolling again.<br>";
    string += "2: Pick category and end your turn<br>";
    string += "3: Roll again.<br>";
    string += "4: Exit<br>";
    string += "Enter a number: ";
    string += '<input type="text" id="menuChoiceInput" name="menuChoiceInput" min="1" max="4" required size="1">';
    string += '<button type="submit" id="menuBtn">Enter</button>'; //onclick="menuOnClick()"
    msgDiv.innerHTML = string;
    document.getElementById("menuBtn").addEventListener("click", this.menuOnClick);
};


//*****************************************************************
//        Handle Event Listener for player's menuChoice 
//*****************************************************************
Yahtzee.prototype.menuOnClick = function () {
    alert("Hit menuOnClick(). this.value = "+this.value);
    console.log("Hit menuOnClick(). this.value = "+this.value);
    var resp = 1;
    //resp = this.value;
    //resp = document.getElementById('menuChoiceInput').value; //cin>>resp;
    this.menuChoice = resp;//this.setMenuChoice(resp); //
    console.log("Hit menuOnClick(). resp=" + resp + "  this.menuChoice=" + this.menuChoice);
};



//*****************************************************************
//              Write to nPlayers div
//*****************************************************************
Yahtzee.prototype.printNPlayrDiv = function () {

    var nPlayrDiv = document.getElementById('nPlayrDiv');
    var string = "Enter 1 or 2 players?";
    string += '<input type="text" id="nPlayrInput" name="nPlayrInput" min="1" max="4" required size="1">';
    string += '<button type="submit" id="nPlayrBtn">Enter</button>'; //onclick="menuOnClick()"
    nPlayrDiv.innerHTML = string;
    document.getElementById("nPlayrBtn").addEventListener("click", this.nPlayrOnClick);
};


//*****************************************************************
//              Handle Event listener for nPlayrDiv
//*****************************************************************
Yahtzee.prototype.nPlayrOnClick = function () {
    
    console.log("Hit nPlayrOnClick()");
    var num = this.value;
    alert("nPlayrInput =" + num);
    //num = (num == null ) ? 1 : num;
    this.nPlayer = num;         //this.setNPlayer(num);
    console.log("Hit nPlayrOnClick().  num =" + num + "  this.nPlayer=" + this.nPlayer);
};



//*****************************************************************
//              Write message depending on num players
//*****************************************************************
Yahtzee.prototype.welcomeMsg = function (name) {
    //console.log("Hit welcomeMsg().  this.nPlayer=" + this.nPlayer);
    if (this.nPlayer > 1) {
        var string = name[0] + " vs " + name[1];
    } else {
        string = "Welcome " + name[0];
    }
    document.getElementById("nameDiv").innerHTML = string;
};



//******************************************
//      pause screen before continuing
//******************************************
Yahtzee.prototype.pause = function (ch) {

    console.log("Hit pause()");
    var msg = (ch === 'r') ? "roll." : "continue.";
    var msg2 = "Press enter to " + msg;
    if (confirm(msg2) === true) { //cin.get(); // captures enter from keyboard
        return true;
    }
    return false;
};


//*****************************************************************
//          Get winner and Print player's final scorecard 
//*****************************************************************
Yahtzee.prototype.isNewHiScore = function (user, p1HiScore) {

    console.log("Hit isNewHiScore()");

    /* Player 1 represents the user object. ONLY change their values if p1 wins.
     Check is p1's score from this game is larger than their hiScore stored in binary file */
    if (user.isHiScore(p1HiScore)) {

        // Reset user's hiSCore and update binary & text file            
        user.setHiScore(p1HiScore);

        console.log("<br/>New High Score of " + user.getHiScore() + "!<br/>");
        console.log("user New hiScore = " + user.getHiScore());

        // Certain printout depending on if User is logged in or not
        //if(user.getName() === "Guest"){ console.log("<br/>Sign up or Login to save your score.<br/>");

        return true; // player 1 HAS new high score                
    }
    console.log("user.hiScore " + user.getHiScore() + " > "+ p1HiScore+" player1's hiScore");
    return false; // player 1 does NOT have new high score 
};


//*****************************************************************
//              Set Yahtzee object variable        
//*****************************************************************
Yahtzee.prototype.setMenuChoice = function (num) {
    this.menuChoice = num;
};


//*****************************************************************
//              Set p1Winner true/false
//*****************************************************************
Yahtzee.prototype.setP1Winner = function (bool) {
    this.p1Winner = bool;
};


//*****************************************************************
//              Set number of players
//*****************************************************************
Yahtzee.prototype.setNPlayer = function (num) {
    this.nPlayer = num;
};


//*****************************************************************
//          Set index for which player it is in player array
//*****************************************************************
Yahtzee.prototype.setIndex = function (i) {
    this.index = i;
};


//*****************************************************************
//              Get Yahtzee object variable 
//*****************************************************************
Yahtzee.prototype.getMenuChoice = function () {
    return this.menuChoice;
};


//*****************************************************************
//              Get p1Winner true/false
//*****************************************************************
Yahtzee.prototype.getP1Winner = function () {
    return this.p1Winner;
};


//*****************************************************************
//              Get number of players
//*****************************************************************
Yahtzee.prototype.getNPlayer = function () {
    return this.nPlayer;
};


//*****************************************************************
//      Get index for which player it is in player array
//*****************************************************************
Yahtzee.prototype.getIndex = function () {
    return this.index;
};


//******************************************
//          Print Yahtzee rules
//******************************************
Yahtzee.prototype.getRules = function () {
    var string = "WELCOME TO YAHTZEE!! <br><br>";
    string += "RULES: <br><br>";
    string += "Yahtzee is a game played with five dice, where the objective is to score as many points as possible in 13 rounds. <br>";
    string += "Each player takes turns rolling the dice up to three times per turn, trying to achieve certain combinations. <br>";
    string += "After each turn, the player must choose a category to score their points in, and that category cannot be used again. <br><br><br><br>";
    //confirm(string);
    document.getElementById("msgDiv").innerHTML = string;
};
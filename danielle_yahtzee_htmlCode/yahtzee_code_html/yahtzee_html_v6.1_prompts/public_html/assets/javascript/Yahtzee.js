//To do: selectDice(a), selectCategory(a, name, rnd), setFinalSC(), setHiScore()

// Global constants for Yahtzee Class
const MINSIZE = 2;
const MAXROLLS = 3;
const MAXRND = 2; //13


//*****************************************************************
//  Yahtzee Constructor. Public properties of Yahtzee class 
//*****************************************************************

function Yahtzee(user) {
    //console.log("Hit Yahtzee()"); 
    this.showScorecard();
    this.setP1Winner(false);
    this.setNPlayer(MINSIZE);
    this.setIndex(0); // player index. Who's turn it is when there's 2 players
    this.menuChoice = 0; // User menuChoice made during play()
   

    this.player = new Array(); // Aggregate instance of User Class to create player(s) for the game
    this.scorecard = new Array(); // Aggregate new instance ScoreCard Class for possible points
    this.finalSC = new Array();// Aggregate new instance ScoreCard Class for final points

    for (var i = 0; i < this.getNPlayer(); i++) {
        this.player[i] = new User(i + 1);
        this.scorecard[i] = new ScoreCard();  // possible scorecard points. Aggregates Array of ScoreCard class
        this.finalSC[i] = new ScoreCard();   // final scorecard. Aggregates Array of ScoreCard class
    }

    // Print to html now because prompts in game are running before it prints the first roll
    //this.scorecard[this.index].reRoll();        // Re-Roll dice   
    //this.scorecard[this.index].fillScoreCard(); // Set & print scorecard with possible points based on dice values  
    this.player[this.index].setName(user.getName());// Reset player 1's name with user's name
}




//**********************************************************
//              Controls rounds
//**********************************************************
Yahtzee.prototype.startGame = function (user) {
    
    var num = this.promptNPlayer();// var num = 1; // 
    this.setNPlayer(num);
    console.log("Hit startGame()");
    var name = [this.player[0].getName(), this.player[1].getName()]; // Create array for player's name
    this.getRules();
    this.welcomeMsg(name);          // print welcome message depending on num players
    var isContinue = false;

    // Game runs for MAXRND = 13 rounds. 1 round per category
    for (var rnd = 1; rnd <= MAXRND; rnd++) {

        this.finalSC[this.index].setRound(rnd); // set & write round to ScoreCard.html
        isContinue = this.play();
        console.log('player1 isContinue = ' + isContinue);

        //if there's 2 players and round is less than or equal to MAXRND
        if ((isContinue === true) && (this.nPlayer > 1 && (this.finalSC[this.index].getRound() <= MAXRND))) {
            this.setIndex(1);
            this.finalSC[this.index].setRound(rnd); // set round in final ScoreCard
            isContinue = this.play();
            this.setIndex(0);
        }
    } // ends round for(rnd < 13 )           


    //*****************************************************************************************
    //                   CALCULATE SCORES, CHECK FOR WINNER AND HISCORE
    //*****************************************************************************************
    this.finalSC[0].setRound(13);       // Set round to last round for each player, so it'll 
    this.finalSC[1].setRound(13);       // check if they hit upperScore bonus in printFinalSC()
    this.finalSC[0].printFinalSC(this.player[0].getName());// Print player 1's final scorecard 

    // if 2 players, then print player 2's final scorecard
    if (this.getNPlayer() > 1) {
        this.finalSC[1].printFinalSC(this.player[1].getName());
    }      
    
    // if nPlayer === 1, then p1 automatically winner
    if (this.getNPlayer()=== '1') {
        return this.isNewHiScore(user, this.player[0].getHiScore()); // return whether or not p1 has new hiScor
        
    } else { // If there is more than 1 player

        console.log('this.getNPlayer() = '+ this.getNPlayer());
        console.log("\n" + this.player[0].getName() + " vs " + this.player[1].getName() + "\n");
        console.log(this.player[0].getHiScore() + "     vs " + this.player[1].getHiScore());

        var msg = "";

        // Check is p1 is winner, tie or loser
        if (this.player[0].getHiScore() > this.player[1].getHiScore())
        {
            msg = this.player[0].getName() + " won!\n";
            this.p1Winner = true;

        } else if (this.player[0].getHiScore() === this.player[1].getHiScore()) {

            msg = "Tie Game!\n";
            this.p1Winner = true;

        } else {

            this.p1Winner = false;
            msg = "Uh-Oh..." + this.player[1].getName() + " won!\n";
        }
        alert("\n" + msg + "\n");
        console.log("\n" + msg + "\n");
    }
    console.log("End of startGame()");
    return false;
};


//**********************************************************
//              This player's turn
//              a = player's index
//**********************************************************
Yahtzee.prototype.play = function () {   //(player, scorecard, finalSC) {

    var continueGame = false;
    var numRolls = 0,
            resp = 0;
    plyrIndx = this.index,
            rnd = this.finalSC[plyrIndx].getRound(),
            name = this.player[plyrIndx].getName();
    console.log("Hit play().  " + name + "'s turn");

    /**********************  START THIS PLAYER'S TURN  *************************/

    numRolls = 0; // Reset at the beginning of each player's turn  
   
    while (!(numRolls === MAXROLLS)) {  // loop as long as numRolls does NOT equal 3

        var string = this.printRounds(name,rnd,numRolls);        
        this.scorecard[plyrIndx].reRoll();   // Re-Roll dice   
        numRolls++;  // increment numRolls every time dice are rolled       


        // Set & print scorecard with possible points based on dice values
        this.scorecard[plyrIndx].fillScoreCard();

        // if it is last roll, force switch case 2 to run
        if (numRolls === MAXROLLS) {
            this.menuChoice = 2;
            resp = this.menuChoice;
            console.log("Hit numRolls === MAXROLLS.  menuChoice = " + resp);

        } else {
            console.log('calling printMenu()');
            resp = this.printMenu(string);
            this.setMenuChoice(resp);
            console.log("Hit numRolls < MAXROLLS.  menu response = " + resp);
        }


        switch (resp * 1) { // choose dice to keep, pick a category, re-roll or exit game

            case 1:  // Select dice you want to keep in between rolls
            {
                console.log("Hit switch case 1");
                continueGame = this.selectDice(this.scorecard[plyrIndx], plyrIndx);
                break;
            }
            case 2: // Keep points from 1 category and end their turn
            {
                console.log("Hit switch case 2");
                numRolls = MAXROLLS; // reassign it, so while(numRolls<maxRolls) stops

                // Ask player to pick category & set player's final scorecard's points each time they choose a category         
                continueGame = this.finalSC[plyrIndx].setFinalSC(this.scorecard[plyrIndx]); //selectCategory(a, name, rnd); 
 
                if (continueGame) {
                    // reset player's hiScore each time finalSC is changed
                    this.finalSC[plyrIndx].setUpLowSums();
                    this.player[plyrIndx].setHiScore(this.finalSC[plyrIndx].getTotalScore());
                    console.log(name + "'s hiScore = " + this.player[plyrIndx].getHiScore());


                    // if it is NOT the last round, then print player's final scorecard
                    if (!(rnd === MAXRND)) {
                        this.finalSC[plyrIndx].printFinalSC(name);

                    } else { // If it IS the last round AND there are 2 players,
                             // AND it's player 1's turn, then print their final scorecard

                        if ((this.nPlayer > 1) && (plyrIndx === 0)) {
                            this.finalSC[plyrIndx].printFinalSC(name);

                        } else {
                            alert("Tallying final score...");
                            console.log("Tallying final score...");
                        }
                    }
                }
                break;
            }
            case 3:  // Roll dice again by breaking out of switch()
            {
                console.log("Hit switch case 3. Reroll");
                continueGame = true;
                break;
            }
            default: // if they exit early, then reset values to break out of 
            {        // all the loops & print final scorecards

                alert("Hit switch default...<Leaving program>");
                console.log("           Hit switch default...Leaving program");
                this.finalSC[0].setRound(this.finalSC[0].NUM_CATGRY); // set round in final ScoreCard to end game
                numRolls = MAXROLLS;
                return;
            }
        } // ends switch(resp)         
        console.log("Hit end of switch. numRolls = " + numRolls + " continueGame = " + continueGame);
        console.log("");
    } // ends while(!(numRoll == MAXROLLS))  
    console.log("\n");
    return true;
};


//*****************************************************************
//              Select dice player wants to keep
//*****************************************************************
Yahtzee.prototype.selectDice = function (scorecard) {

    console.log("Hit selectDice()");

    //document.getElementById("selectDiceDiv").style.visibility = "visible";//"hidden"; 
    var ans = (1 + (Math.floor(Math.random() * 5)));
    var string = "Select the dice numbers (1-5) to keep.";

    
    do {

        ans = prompt(string);        
        //console.log("  selectDice().  ans="+ans + " ans typeof=" + typeof ans); 

        // add event listeners to all buttons with class "category-button"
        var diceBtn = document.getElementsByClassName("dice");
        for (var i = 0; i < diceBtn.length; i++) {
            diceBtn[i].addEventListener("click", this.diceOnClick);//this.diceOnClick(scorecard));
        }

        // THIS SHOULD BE IN diceOnClick(), BUT IT WONT WORK IN THERE
        if(ans !== null && (ans>=1 && ans<=5)){ //click on prompt's cancel button sets ans=null, so don't push it.
            scorecard.pushThisDice(ans-1);
            console.log("      In selectDice().  ans=" + (ans-1) + "  Keeping Dice" + (ans - 1) + ": " + scorecard.getDice(ans - 1));
        }
    } while (  (ans === '1') || (ans === '2') || (ans === '3') || (ans === '4') || (ans === '5'));

    return true;
};


//*****************************************************************
//              Handle Event listener for each dice button
//*****************************************************************

Yahtzee.prototype.diceOnClick = function (scorecard) {

    console.log("Hit diceOnClick()");
    alert("Hit diceOnClick()");
    var temp_indx = 0;
    temp_indx = this.name;
    temp_indx *= 1;

    var keep = [];
    keep.push(temp_indx);
    alert("Hit diceOnClick().  dice.name=" + temp_indx + "  dice.value=" + this.value + "  keep=" + keep);
    console.log("Hit diceOnClick().  dice.name=" + temp_indx + "  dice.value=" + this.value + "  keep=" + keep);
    console.log("keep=" + keep);

    //  I NEED THIS TO WORK. IT WORKS IN selectDice()
    //scorecard.pushThisDice(temp_indx);


    //this.removeEventListener("click", diceOnClick);  // remove the event listener so that the button becomes static
    //this.setKeepDice(keep);
};

//*****************************************************************
//            
//*****************************************************************
Yahtzee.prototype.setKeepDice = function (keep) {
    for (var i = 0; i < 5; i++) {
        this.keepDice[i] = keep[i];
    }
    alert("Hit setKeepDice(). keepDice=" + this.keepDice);
};

//*****************************************************************
//    Handle Event listener to stop selecting dice you want to save
//*****************************************************************

Yahtzee.prototype.stopDiceOnClick = function () {
    console.log("Hit stopDiceOnClick()");
    alert("Hit stopDiceOnClick()");
    var stop = true;
    //alert("Hit stopDiceOnClick().  this.value=" + this.value);
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
    input *= 1; // make it an integer
    var i = 0;
    i = this.name;
    i *= 1;

    //resp = document.getElementById('catgyInput').value; //cin>>resp;
    alert("Hit catgyOnClick2() value = " + input);//+ "  this.name=" + i);
    console.log("Hit catgyOnClick2() value = " + input);// + "  this.name=" + i);
    console.log('scores[' + input + '] = ' + this.scorecard[this.index].getScoreIndex(input));

    //var num = Number(i);//parseInt(i);
    //console.log("Hit SC catgyOnClick2().   typeof i = " + typeof i + " = " + i);
    //console.log("Hit SC catgyOnClick2().   typeof num = " + typeof num + " = " + num);
    //console.log("          Hit catgyOnClick2().  this.isCatgryPicked[ " + this.isCatgryPicked);


    // Conditional stops a category from being overwritten on final scorecard
//    if (this.isCatgryPicked[num] === true) {
//        alert("Category " + i + " has already been selected.<br/>Choose another category:  ");
//    }
//
//    // Set points in player's final scoreboard
//    this.scores[num] = input;
//
//    // set flag so this category, so it can't be selected anymore
//    this.isCatgryPicked[num] = true;
//    this.isCatgryPicked[num] = true;
//
//
//    console.log("finalSC.scores[" + num + "] = " + this.scores[num] + "<br/>");
//    console.log("finalSC.isCatgryPicked[" + num + "]   = " + this.isCatgryPicked[num]);
//    console.log("scorecard.isCatgryPicked[" + num + "] = " + this.scorecard.isCatgryPicked[num]);
};




//*****************************************************************
//                   Writes menu for play() 
//*****************************************************************
Yahtzee.prototype.printMenu = function (rndRollString) {

    var string = "\nPlay Options: \n";
    string += "1: Select which dice you want to keep before rolling again.\n";
    string += "2: Pick category and end your turn\n";
    string += "3: Roll again.\n";
    string += "4: Exit\n";
    var ans = prompt(rndRollString + string);

    console.log("Hit printMenu(). ans = " + ans);
    return ans;
};


//*****************************************************************
//        Handle Event Listener for player's menuChoice 
//*****************************************************************
Yahtzee.prototype.menuOnClick = function () {
    alert("Hit menuOnClick(). this.value = " + this.value);
    console.log("Hit menuOnClick(). this.value = " + this.value);
    var resp = 1;
    //resp = this.value;
    //resp = document.getElementById('menuChoiceInput').value; //cin>>resp;
    this.menuChoice = resp;//this.setMenuChoice(resp); //
    console.log("Hit menuOnClick(). resp=" + resp + "  this.menuChoice=" + this.menuChoice);
};



//*****************************************************************
//              Write to nPlayers div
//*****************************************************************
Yahtzee.prototype.promptNPlayer = function () {

    console.log('Hit promptNPlayer()');
    var string = "Enter 1 or 2 players?";
    var numPlayers = prompt(string);
    return numPlayers;
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
    if (this.getNPlayer() > 1) {
        var string = name[0] + " vs " + name[1];
    } else {
        string = "Welcome " + name[0];
    }
    document.getElementById("nameDiv").innerHTML = string;
    console.log("Hit welcomeMsg().  " + string);
    //alert(string);
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

        console.log("\nNew High Score of " + user.getHiScore() + "!\n");
        alert("\nNew High Score of " + user.getHiScore() + "!\n");  
        return true; // player 1 HAS new high score                
    }
    alert('Good Game!\nTotal Points: ' + p1HiScore + "\nYour Current HiScore: "+ user.getHiScore() + " points");
    console.log('Good Game!\n' + p1HiScore + " Points!\nuser.hiScore " + user.getHiScore() + " > " + p1HiScore + " player1's hiScore");
    return false; // player 1 does NOT have new high score 
};

//*****************************************************************
//          Print player, current round and current roll
//        Return a string for printMenu() to use in its prompt
//*****************************************************************
Yahtzee.prototype.printRounds=function(name,rnd,numRolls){
    var string = name + "'s turn. Round " + rnd + "  Roll " + (numRolls + 1);
    console.log("                                       " + string);
    document.getElementById("rollDiv").innerHTML = string;
    return string;
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


// Load this function's elements first
Yahtzee.prototype.showScorecard = function () {

    var catgry = ['Aces', 'Twos', 'Threes', 'Fours', 'Fives', 'Sixes',
        'Three of a Kind', 'Four of a Kind', 'Three of Kind', 'Full House',
        'Small Straight', 'Large Straight', 'Yahtzee', 'Chance',
        'Upper Total', 'Bonus', 'Lower Total', 'Grand Total'];

    var div = document.getElementById('scorecard-div');
    var table = document.createElement('table');
    div.append(table);
    var thead = document.createElement('thead');
    table.append(thead);
    var tr0 = document.createElement('tr');
    thead.append(tr0);
    var th1 = document.createElement('th');
    th1.innerHTML = 'Category';
    tr0.append(th1);
    var th2 = document.createElement('th');
    th2.innerHTML = 'Score';
    tr0.append(th2);

    var tbody = document.createElement('tbody');
    table.append(tbody);

    for (var i = 0; i < 18; i++) {

        var tr = document.createElement('tr');
        var td_catgry = document.createElement('td');
        td_catgry.innerHTML = catgry[i];
        var td_btn = document.createElement('td');
        var btn = document.createElement('button');
        btn.setAttribute('id', 'catgy' + i);
        btn.setAttribute('class', 'category-button');
        btn.setAttribute('value', i);
        btn.setAttribute('onclick', 'yahtzee.catgyOnClick2()');
        btn.innerHTML = '-';

        tbody.append(tr);
        tr.append(td_catgry);
        td_btn.append(btn);
        tr.append(td_btn);

    }
};
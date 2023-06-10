//To do: selectDice(a), selectCategory(a, name, rnd), showPickCategory(), setHiScore()

// Global constants for Yahtzee Class
var MINSIZE = 2;
var MAXROLLS = 3;
var MAXRND = 13; //13


//*****************************************************************
//  Yahtzee Constructor. Public properties of Yahtzee class 
//*****************************************************************

function Yahtzee(user) {
    console.log("Hit Yahtzee() Constructor");
    //this.showScorecard(); // prints scorecard dynamically
    this.setP1Winner(false);
    this.setNPlayer(MINSIZE);
    this.setIndex(0); // player index. Who's turn it is when there's 2 players
    this.menuChoice = 0; // User menuChoice made during play()
    this.printMenu();
    //document.getElementById("menuDiv").style.visibility = "hidden";//"visible" 

    this.player = new Array(); // Aggregate instance of User Class to create player(s) for the game
    this.scorecard = new Array(); // Aggregate new instance ScoreCard Class for possible points
    this.finalSC = new Array();// Aggregate new instance ScoreCard Class for final points

    for (var i = 0; i < this.getNPlayer(); i++) {
        this.player[i] = new User(i + 1);
        this.scorecard[i] = new ScoreCard();  // possible scorecard points. Aggregates Array of ScoreCard class
        this.finalSC[i] = new ScoreCard();   // final scorecard. Aggregates Array of ScoreCard class
    }

    console.log(this.finalSC[0]);
    this.player[this.index].setName(user.getName());// Reset player 1's name with user's name    
}




//**********************************************************
//              Controls rounds
//**********************************************************
Yahtzee.prototype.startGame = function (user) {

    console.log("Hit startGame()");
    var num = 1; //var num = this.promptNPlayer();
    this.setNPlayer(num);
    var name = [this.player[0].getName(), this.player[1].getName()]; // Create array for player's name
    this.getRules();
    this.welcomeMsg(name);          // print welcome message depending on num players
    var isContinue = false;


    // Game runs for MAXRND = 13 rounds. 1 round per category
    for (var rnd = 1; rnd <= MAXRND; rnd++) {
        
        this.play(rnd);
        

        // if there's 2 players and round is less than or equal to MAXRND
        if (this.nPlayer > 1 && (rnd <= MAXRND)) {
            this.setIndex(1); // signals it's player 2's turn    
            this.play(rnd);
            this.setIndex(0); // signals it's player 1's turn
        }
    } // ends round for(rnd <= 13 )           

    this.isP1Winner();  // Print player's final scorecards    

    if (!this.getP1Winner()) { // if player 1 is NOT winner
        return false;
    } else { // if player 1 is winner, then check if they have a new hiScore
        return this.isNewHiScore(user); // return whether or not p1 has new hiScor
    }
    console.log("End of startGame()");
    return false;
};


//**********************************************************
//              This player's turn
//              a = player's index
//**********************************************************
Yahtzee.prototype.play = function (rnd) {   //(player, scorecard, finalSC) {

    console.log("Hit play()");
    this.finalSC[this.index].setRound(rnd); // set round for finalSC. scorecard.getUpLowSums() uses it.
    this.scorecard[this.index].setRound(rnd);// set round for possible scorecard. scorecard.recordSCore() uses it.
    var numRolls = 0,
            response = 0,
            plyrIndx = this.index, // player index. Holds index of who's turn it is.
            rnd = this.finalSC[plyrIndx].getRound(),
            name = this.player[plyrIndx].getName();


    // loop as long as numRolls does NOT equal 3
    while (!(numRolls === MAXROLLS)) {


        var string = name + "'s turn. Roll " + (numRolls + 1) + " Round " + rnd;
        console.log("                                       " + string);
        document.getElementById("rollDiv").innerHTML = string;
        this.scorecard[plyrIndx].reRoll(); // Re-Roll dice   
        numRolls++; // increment numRolls every time dice are rolled       


        // Set & print scorecard with possible points based on dice values
        this.scorecard[plyrIndx].fillScoreCard(name);

        // if it is last roll, force switch case 2 to run
        if (numRolls === MAXROLLS) {
            this.setMenuChoice(2);
            response = this.getMenuChoice();
            console.log("Hit numRolls === MAXROLLS.  menuChoice = " + response);
            //document.getElementById("menuDiv").style.visibility = "hidden";//"visible"

        } else {
            //document.getElementById("menuDiv").style.visibility = "visible";//"hidden"
            //this.printMenu();
            response = this.checkMenuChoice();
            console.log("Hit numRolls < MAXROLLS.  menuChoice = " + response);
        }


        switch (response * 1) { // choose dice to keep, pick a category, re-roll or exit game

            case 1:  // Select dice you want to keep in between rolls
            {
                console.log("Hit switch case 1");
                this.selectDice(this.scorecard[plyrIndx], plyrIndx);
                break;
            }
            case 2: // Keep points from 1 category and end their turn
            {
                console.log("Hit switch case 2");
                numRolls = MAXROLLS; // reassign it, so while(numRolls<maxRolls) stops


                // Ask player to pick category & set player's final scorecard's points each time they choose a category         
                this.showPickCategory();
                

                // reassign player's hiScore each time their finalScoreCard's hiScore is updated
                this.finalSC[plyrIndx].setUpLowSums();
                this.player[plyrIndx].setHiScore(this.finalSC[plyrIndx].getTotalScore());
                //console.log(name + "'s hiScore = " + this.player[plyrIndx].getHiScore());


                // if it is NOT the last round, then print player's final scorecard
                if (rnd === MAXRND) {                   
                    alert("Tallying final score...\n");
                    console.log("\nTallying final score...\n");
                } else { this.finalSC[this.index].printFinalSC(name); } 
                break;
            }
            case 3:  // Roll dice again by breaking out of switch()
            {
                console.log("Hit switch case 3. Reroll");
                break;
            }
            default: // if they exit early, then reset values to break out of 
            {        // all the loops & print final scorecards
                numRolls = MAXROLLS;
                rnd = MAXRND+1;
                console.log("           Hit switch default...Leaving program");
            }
        } // ends switch(response)         
        console.log("Hit end of switch. \n");
    } // ends while(!(numRoll == MAXROLLS))  
    console.log("Hit end of play().\n");
    return true;
};

//*****************************************************************************       
//        Show html div that asks player to enter a category on their possible 
//        scorecard that they want to save on their final scorecard.
//*****************************************************************************
Yahtzee.prototype.showPickCategory = function () {
    
    console.log("Hit showPickCategory()");
    var msgDiv = document.getElementById('categoryDiv');
    var string = "<br>Pick a Category between 1 and 13.<br/>";
    string += "Enter a category: ";
    string += '<input type="text" id="catgyInput" name="catgyInput" min="1" max="4" required size="1">';
    string += '<button type="submit" id="catgyBtn" onclick="yahtzee.categoryClick()">Enter</button>';
    msgDiv.innerHTML = string;

    var category = ((Math.floor(Math.random() * 13)) +1); // random number [1,13]
    
    do {
        
        if ((this.finalSC[this.index].isCatgryPicked[category-1]) === true) {
            var str1 = "Pick a category between 1 and 13.";
            var str2 = "Category " + category + " has already been selected. ";
            category = ((Math.floor(Math.random()*13)) +1);// random number [1,13]
            //alert(str2 + str1 + '   picked category = ' + category);
        }
    } while ((this.finalSC[this.index].isCatgryPicked[category-1]) === true);
    this.setFinalSC(category-1);
    return true;
};



//*****************************************************************
//        Handle Event Listener for each scorecard categories' button
//*****************************************************************
Yahtzee.prototype.categoryClick = function () {

    var category = document.getElementById('catgyInput').value;
    category *= 1; // make it an integer
    alert("Hit categoryClick() picked category = " + category);    

    do {
        var str1 = "Pick a category between 1 and 13.";
        category -= 1; // subtract 1 because array range is [0,12]
        
        // Conditional stops a set category from being overwritten
        if ((this.finalSC[this.index].isCatgryPicked[category]) === true) {
            var str2 = "Category " + category + " has already been selected.\n";
            //category = prompt(str2 + str1);
            console.log(str2 + str1);
            alert(str2 + str1);
        }

    } while ((this.finalSC[this.index].isCatgryPicked[category]) === true);
    this.setFinalSC(category);
};


// Set points in player's final scoreboard
Yahtzee.prototype.setFinalSC = function (category) {
    
    this.finalSC[this.index].scores[category] = this.scorecard[this.index].scores[category];

    // set flag so this category on finalSC and scorecard, so it can't be selected anymore
    this.finalSC[this.index].isCatgryPicked[category] = true;
    this.scorecard[this.index].isCatgryPicked[category] = true;
    
    //alert('\n\nHit setFinalSC().  picked category ' + category + "="+this.scorecard[this.index].scores[category]    
                  //+".   finalSC.scores[" + category + "] = " + this.finalSC[this.index].scores[category] + "\n\n");
    console.log('\nHit setFinalSC().  picked category ' + category + "="+this.scorecard[this.index].scores[category]    
                  +".   finalSC.scores[" + category + "]=" + this.finalSC[this.index].scores[category] + "\n");
    //console.log("finalSC.isCatgryPicked[" + category + "]   = " + this.finalSC[this.index].isCatgryPicked[category]);
    //console.log("scorecard.isCatgryPicked[" + category + "] = " + this.scorecard[this.index].isCatgryPicked[category]);
};



//*****************************************************************************************
//                   CALCULATE SCORES, CHECK FOR WINNER AND HISCORE
//*****************************************************************************************
Yahtzee.prototype.isP1Winner = function () {

    console.log('Hit isP1Winner()');
    //alert('Hit isP1Winner()');
    // Print player 1's final scorecard 
    this.finalSC[0].setRound(13);  // rnd 13 will check if they hit upperScore bonus in printFinalSC() 
    this.scorecard[0].setRound(13);
    this.finalSC[0].printFinalSC(this.player[0].getName());

    var msgDiv = document.getElementById('rollDiv');
    var msg1 = "\nGame Over!\n";
    msgDiv.innerHTML = msg1;
    console.log(msg1);


    // if nPlayer === 1, then player1 is automatically winner
    if (this.getNPlayer() === 1) {
        this.setP1Winner(true);
        return;
    }

    // If there is more than 1 player, then print player 2's final scorecard
    else{ //(this.getNPlayer() > 1) {
        this.finalSC[1].setRound(13); // rnd 13 will check if they hit upperScore bonus in printFinalSC()
        this.scorecard[1].setRound(13);
        this.finalSC[1].printFinalSC(this.player[1].getName());
    

        //console.log('this.getNPlayer() = '+ this.getNPlayer());
        console.log("\n" + this.player[0].getName() + " vs " + this.player[1].getName() + "\n");
        console.log(this.player[0].getHiScore() + "     vs " + this.player[1].getHiScore());

        var msg2 = "";

        // Check is p1 is winner, tie or loser
        if (this.player[0].getHiScore() > this.player[1].getHiScore())
        {
            msg2 = this.player[0].getName() + " won!\n";
            this.setP1Winner(true);        

        } else if (this.player[0].getHiScore() === this.player[1].getHiScore()) {

            msg2 = "Tie Game!\n";
            this.setP1Winner(true);

        } else {

            this.setP1Winner(false);
            msg2 = "Uh-Oh..." + this.player[1].getName() + " won!\n";
        }
        console.log("\n" + msg2 + "\n");
        msgDiv.append(msg2);
    }
};

//*****************************************************************
//              Select dice player wants to keep
//*****************************************************************
Yahtzee.prototype.selectDice = function (scorecard) {

    console.log("Hit selectDice()");
    //document.getElementById("selectDiceDiv").style.visibility = "visible";//"hidden"; 
    var ans = (1 + (Math.floor(Math.random() * 5)));
    
    do { // Push the dice they WANT OR DON'T into vector? 

        var div = document.getElementById('selectDiceDiv');
        var string = "<br><p>Click on the dice you want to keep, or Click button to stop:</p>";
        string += '<input type="text" id="selectDiceInput" name="selectDiceInput" min="1" max="1" required size="1">';
        string += '<button type="submit" id="stopDiceOnClick" onclick="yahtzee.stopDiceOnClick()">Stop</button><br>'; //onclick="menuOnClick()"
        div.innerHTML = string;


        // add event listeners to all scorecard buttons with class "category-button"
        var diceBtn = document.getElementsByClassName("dice");
        for (var i = 0; i < diceBtn.length; i++) {
            diceBtn[i].addEventListener("click", this.diceOnClick);//this.diceOnClick(scorecard));
        }

        // THIS SHOULD BE IN diceOnClick(), BUT THE GAME WONT STOP AND GET VALUE FROM onclick 
        scorecard.pushThisDice(ans - 1);
        console.log("      Hit selectDice().  ans=" + (ans - 1) + "  Keeping Dice" + (ans - 1) + "=" + scorecard.getDice(ans - 1));
        ans = 0;
    } while ((ans === 1) || (ans === 2) || (ans === 3) || (ans === 4) || (ans === 5));
    return true;
};


//*****************************************************************
//              Handle Event listener for each dice button
//*****************************************************************

Yahtzee.prototype.diceOnClick = function (scorecard) {

    var temp_indx = 0;
    temp_indx = this.name;
    temp_indx *= 1;

    var keep = [];
    keep.push(temp_indx);
    alert("Hit diceOnClick().  dice index=" + temp_indx + "  dice.value=" + this.value + "  keep=" + keep);
    console.log("Hit diceOnClick().  dice.name=" + temp_indx + "  dice.value=" + this.value + "  keep=" + keep);
    console.log("keep=" + keep);

    //  I NEED THIS TO WORK. IT WORKS IN selectDice()
    //scorecard.pushThisDice(temp_indx);
    //this.removeEventListener("click", diceOnClick);  // remove the event listener so that the button becomes static
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


Yahtzee.prototype.checkMenuChoice = function () {
    var randNum = (1 + (Math.floor(Math.random() * 3))); //[1,4]
    var choice = (this.getMenuChoice() < 1) ? randNum : this.getMenuChoice();
    console.log('Hit checkMenuChoice(). choice = ' + choice);
    return choice;
};


//*****************************************************************
//                   Writes menu for play() 
//*****************************************************************
Yahtzee.prototype.printMenu = function () {

    var msgDiv = document.getElementById('menuDiv');
    //var dialog = document.createElement('dialog');
    //msgDiv.append(dialog);

    var p = document.createElement('p');
    var string = "<br> Options: <br>";
    string += "1: Select which dice you want to keep before rolling again.<br>";
    string += "2: Pick category and end your turn<br>";
    string += "3: Roll again.<br>";
    string += "4: Exit<br>";
    p.innerHTML = string;
    msgDiv.append(p);

    var label = document.createElement('label');
    label.setAttribute('for', 'menuChoiceInput');
    label.innerHTML = "Enter a number: ";
    msgDiv.append(label);

    var input = document.createElement('input');
    input.setAttribute('type', 'text');
    input.setAttribute('name', 'menuChoiceInput');
    input.setAttribute('min', 1);
    input.setAttribute('max', 4);
    //input.setAttribute('required', 1); 
    input.setAttribute('id', 'menuChoiceInput');
    input.setAttribute('value', "");
    msgDiv.append(input);


    var btn = document.createElement('button');
    btn.setAttribute('type', 'submit');
    btn.setAttribute('id', 'menuBtn');
    btn.setAttribute('onclick', 'yahtzee.menuOnClick()');
    btn.setAttribute('value', 'submit');
    btn.innerHTML = 'submit';
    msgDiv.append(btn);
    //dialog.showModal();
    console.log("Hit printMenu().");
};


//*****************************************************************
//        Handle Event Listener for player's menuChoice 
//*****************************************************************
Yahtzee.prototype.menuOnClick = function () {

    var response = document.getElementById('menuChoiceInput').value; //cin>>response;
    this.setMenuChoice(response);
    alert("Hit menuOnClick(). value = " + response + "  menuChoice=" + this.getMenuChoice());
    console.log("Hit menuOnClick(). response=" + response + "  menuChoice=" + this.getMenuChoice());

};



//*****************************************************************
//              Write to nPlayers div
//*****************************************************************
Yahtzee.prototype.promptNPlayer = function () {

    console.log('Hit promptNPlayer()');
    var nPlayrDiv = document.getElementById('nPlayrDiv');
    var string = "Enter 1 or 2 players?";
    string += '<input type="text" id="nPlayrInput" name="nPlayrInput" min="1" max="4" required size="1">';
    string += '<button type="submit" id="nPlayrBtn" onclick="yahtzee.menuOnClick()">Enter</button>'; //
    nPlayrDiv.innerHTML = string;
    document.getElementById("nPlayrBtn").addEventListener("click", this.nPlayrOnClick);
};


//*****************************************************************
//              Handle Event listener for nPlayrDiv
//*****************************************************************
Yahtzee.prototype.nPlayrOnClick = function () {

    console.log("Hit nPlayrOnClick()");
    alert("Hit nPlayrOnClick()");
    var num = this.value;
    alert("nPlayrInput =" + num);
    //num = (num == null ) ? 1 : num;
    this.nPlayer = num;         //this.setNPlayer(num);
    console.log("Hit nPlayrOnClick().  num =" + num + "  this.nPlayer=" + this.nPlayer);
    alert("Hit nPlayrOnClick().  num =" + num + "  this.nPlayer=" + this.nPlayer);
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



//*****************************************************************
//          Get winner and Print player's final scorecard 
//*****************************************************************
Yahtzee.prototype.isNewHiScore = function (user) {

    console.log("Hit isNewHiScore(). player1.hiScore=" + this.player[0].getHiScore() + " > user.hiScore=" + user.getHiScore() + " ?");

    /* Player 1 represents the user object. ONLY change user's hiScore if player1 wins AND
     player1 has a higher score than the user's hiScore that is currently stored in database */
    if (user.isHiScore(this.player[0].getHiScore())) {
        user.setHiScore(this.player[0].getHiScore()); // Reset user's hiSCore and update this record in the database     
        console.log("\nUser has a New High Score of " + user.getHiScore() + "!\n");
        alert("New High Score of " + user.getHiScore() + "!\n");
        return true; // player 1 HAS new high score                
    }
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


// Write scorecard dynamicallys
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
        btn.setAttribute('onclick', 'yahtzee.setFinalSC()');
        btn.innerHTML = '-';

        tbody.append(tr);
        tr.append(td_catgry);
        td_btn.append(btn);
        tr.append(td_btn);

    }
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
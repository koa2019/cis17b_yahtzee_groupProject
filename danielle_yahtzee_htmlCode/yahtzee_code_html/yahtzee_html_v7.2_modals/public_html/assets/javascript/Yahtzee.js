//To do: showDiceDivOnClick(a), selectCategory(a, name, rnd), showPickCategory(), setHiScore()

// Global constants for Yahtzee Class
var MINSIZE = 1;
var MAXROLLS = 3;
var MAXRND = 13; //13


//*****************************************************************
//  Yahtzee Constructor. Public properties of Yahtzee class 
//*****************************************************************

function Yahtzee(user) {
    console.log("Hit Yahtzee() Constructor");
    this.setP1Winner(false);
    this.setNPlayer(MINSIZE);
    this.setIndex(0); // player index. Who's turn it is when there's 2 players
    this.menuChoice = 0; // User menuChoice made during play()    
    this.numRolls = 0;

    this.player = new Array(); // Aggregate instance of User Class to create player(s) for the game
    this.scorecard = new Array(); // Aggregate new instance ScoreCard Class for possible points
    this.finalSC = new Array();// Aggregate new instance ScoreCard Class for final points

    for (var i = 0; i < this.getNPlayer(); i++) {
        this.player[i] = new User(i + 1);
        this.scorecard[i] = new ScoreCard(this.player[i].getName());  // possible scorecard points. Aggregates Array of ScoreCard class
        this.finalSC[i] = new ScoreCard(this.player[i].getName());   // final scorecard. Aggregates Array of ScoreCard class       
    }

    this.player[this.index].setName(user.getName());// Reset player 1's name with user's name   
    this.scorecard[this.index].setFName(user.getName());
    this.scorecard[this.index].fillScoreCard();
    console.log(this.finalSC[this.index]);
    this.setHTML();
}


Yahtzee.prototype.setHTML = function () {

    console.log('Hit setHTML');
    this.printDice();

    for (var i = 0; i < 5; i++) {
        var diceBtn = document.getElementById('dice' + i);
        diceBtn.setAttribute('onclick', 'yahtzee.diceOnClick(yahtzee)');
    }
    this.printMenu();
    document.getElementById("diceDiv").style.visibility = "hidden";//"visible"; 
    document.getElementById("scorecard-div").style.visibility = "hidden";//"visible";
    document.getElementById("menu-div").style.visibility = "hidden";//"visible";
    //this.showScorecard(); // prints scorecard dynamically
    //document.getElementById("show-menu-btn").style.visibility = "hidden";//"visible" 


    var menuDiv = document.getElementById('show-menu-div');
    var menuBtn = this.makeBtn('submit', 'Show Menu', 'show-menu-btn');
    menuBtn.setAttribute('onclick', 'yahtzee.showMenuOnClick()');
    menuDiv.append(menuBtn);


    //var rollDiv = document.getElementById('diceCol');
    //var rollBtn = this.makeBtn('submit', 'Show Dice', 'show-menu-btn');
    //rollBtn.setAttribute('onclick', 'yahtzee.showDiceDivOnClick()');
    //rollDiv.append(rollBtn);

//    var startDiv = document.getElementById('startDiv');
//    var startBtn = this.makeBtn('submit', 'Start', 'start');
//    startBtn.setAttribute('onclick', 'yahtzee.rollOnClick()');
//    startDiv.append(startBtn);
};


//**********************************************************
//              Controls rounds
//**********************************************************
Yahtzee.prototype.startGame = function (user) {

    console.log("Hit startGame()");
    //document.getElementById("row2").style.visibility = "visible";// "hidden";//
    this.getRules();
    this.welcomeMsg(this.player[this.index].getName());   // print welcome message depending on num players
    this.numRolls++;
    this.scorecard[this.index].writeRollRound(this.numRolls);
    this.play();
    //return this.isNewHiScore();};
};

//**********************************************************
//              This player's turn
//**********************************************************
Yahtzee.prototype.play = function () {

    console.log("Hit play()");
    var rnd=this.finalSC[this.index].getRound();
    if (rnd <= MAXRND) {

        this.scorecard[this.index].reRoll(); // Re-Roll dice       
        this.scorecard[this.index].fillScoreCard(); // Set & print scorecard with possible points based on dice values

        while (!(this.numRolls === MAXROLLS)) {

            this.scorecard[this.index].writeRollRound(this.numRolls);

            // if it is last roll, force switch case 2 to run
            if (this.numRolls === MAXROLLS) {
                this.setMenuChoice(2);
                response = this.getMenuChoice();
                console.log("Hit numRolls === MAXROLLS.  menuChoice = " + response);
                //document.getElementById("menu-div").style.visibility = "hidden";//"visible"
            }
        //else {
            //document.getElementById("menu-div").style.visibility = "visible";//"hidden"
            //response = this.checkMenuChoice();
            //console.log("Hit numRolls < MAXROLLS.  menuChoice = " + response);
        //}
            this.callSwitch();
        } // ends while(!(numRoll == MAXROLLS))  
        rnd++;
        this.finalSC[this.index].setRound(rnd); // set round for finalSC. scorecard.getUpLowSums() uses it.
        this.scorecard[this.index].setRound(rnd);// set round for possible scorecard. scorecard.recordSCore() uses it.
        //console.log('round = ' + this.finalSC[this.index].increRound());
    } // ends if rnd<=MAXRND

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

    var category = ((Math.floor(Math.random() * 13)) + 1); // random number [1,13]

    do {

        if ((this.finalSC[this.index].isCatgryPicked[category - 1]) === true) {
            var str1 = "Pick a category between 1 and 13.";
            var str2 = "Category " + category + " has already been selected. ";
            category = ((Math.floor(Math.random() * 13)) + 1);// random number [1,13]
            //alert(str2 + str1 + '   picked category = ' + category);
        }
    } while ((this.finalSC[this.index].isCatgryPicked[category - 1]) === true);
    this.setFinalSC(category - 1);
    return true;
};


//*****************************************************************
//              EVENT HANDLERS DEFINTIONS
//*****************************************************************

Yahtzee.prototype.diceOnClick = function () {

    var id = event.srcElement.id; //https://stackoverflow.com/questions/4825295/onclick-to-get-the-id-of-the-clicked-button  
    var num = parseInt(id.charAt(4));
    console.log('Hit diceOnClick().  dice' + num + '=' + this.scorecard[this.index].dice[num]);

    this.scorecard[this.index].pushThisDice(num);
    this.scorecard[this.index].getSelectedDice();
};


//    Handles Event listener to stop selecting dice you want to save
Yahtzee.prototype.stopDiceOnClick = function () {
    //document.getElementById("diceCol").style.visibility = "visible";//
    document.getElementById("diceDiv").style.visibility = "hidden";//diceDiv
    this.showMenuOnClick();
    console.log("Hit stopDiceOnClick().");
    this.play();
    //this.scorecard[this.index].reRoll(); // Re-Roll dice       
    //this.scorecard[this.index].fillScoreCard(); // Set & print scorecard with possible points based on dice value 
};


// Handles Event Listener for each scorecard categories' button
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


// Set points in player's final scoreboard. categoryClick() calls it.
Yahtzee.prototype.setFinalSC = function (category) {

    this.finalSC[this.index].scores[category] = this.scorecard[this.index].scores[category];

    // set flag so this category on finalSC and scorecard, so it can't be selected anymore
    this.finalSC[this.index].isCatgryPicked[category] = true;
    this.scorecard[this.index].isCatgryPicked[category] = true;

    //alert('\n\nHit setFinalSC().  picked category ' + category + "="+this.scorecard[this.index].scores[category]    
    //+".   finalSC.scores[" + category + "] = " + this.finalSC[this.index].scores[category] + "\n\n");
    console.log('\nHit setFinalSC().  picked category ' + category + "=" + this.scorecard[this.index].scores[category]
            + ".   finalSC.scores[" + category + "]=" + this.finalSC[this.index].scores[category] + "\n");
    //console.log("finalSC.isCatgryPicked[" + category + "]   = " + this.finalSC[this.index].isCatgryPicked[category]);
    //console.log("scorecard.isCatgryPicked[" + category + "] = " + this.scorecard[this.index].isCatgryPicked[category]);
};



//*****************************************************************************************
//                   CALCULATE SCORES, CHECK FOR WINNER AND HISCORE
//*****************************************************************************************
Yahtzee.prototype.isP1Winner = function () {

    console.log('Hit isP1Winner()');
    // Print player 1's final scorecard 
    this.finalSC[0].setRound(13);  // rnd 13 will check if they hit upperScore bonus in printFinalSC() 
    this.scorecard[0].setRound(13);
    this.finalSC[0].printFinalSC(this.player[0].getName());

    var msgDiv = document.getElementById('rollDiv');
    var msg1 = "\nGame Over!\n";
    var msg2 = this.player[0].getName() + " won!\n";
    msgDiv.append(msg1);
    console.log(msg1);


    // if nPlayer === 1, then player1 is automatically winner
    if (this.getNPlayer() === 1) {
        this.setP1Winner(true);
    }

    // If there is more than 1 player, then print player 2's final scorecard
    else { //(this.getNPlayer() > 1) {
        this.finalSC[1].setRound(13); // rnd 13 will check if they hit upperScore bonus in printFinalSC()
        this.scorecard[1].setRound(13);
        this.finalSC[1].printFinalSC(this.player[1].getName());


        //console.log('this.getNPlayer() = '+ this.getNPlayer());
        console.log("\n" + this.player[0].getName() + " vs " + this.player[1].getName() + "\n");
        console.log(this.player[0].getHiScore() + "     vs " + this.player[1].getHiScore());


        // Check is p1 is winner, tie or loser
        if (this.player[0].getHiScore() > this.player[1].getHiScore()) {
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
    return this.getP1Winner();
};


Yahtzee.prototype.checkMenuChoice = function () {
    var randNum = (1 + (Math.floor(Math.random() * 3))); //[1,4]
    var choice = (this.getMenuChoice() < 1) ? randNum : this.getMenuChoice();
    console.log('Hit checkMenuChoice(). choice = ' + choice);
    return choice;
};


//*****************************************************************
//        Handle Event Listener for player's menuChoice 
//*****************************************************************
Yahtzee.prototype.menuOnClick = function () {


    var response = document.getElementById('menu-select').value; //cin>>response;
    this.setMenuChoice(response);
    alert("Hit menuOnClick(). value = " + response + "  menuChoice=" + this.getMenuChoice());
    console.log("Hit menuOnClick(). response=" + response + "  menuChoice=" + this.getMenuChoice());
    this.callSwitch();

    //document.getElementById("show-menu-btn").style.visibility = "visible";//"hidden";//
    document.getElementById("show-menu-btn").style.visibility = "hidden";//"visible";//
};



Yahtzee.prototype.callSwitch = function () {

    console.log("Hit callSwitch().  menuChoice=" + this.getMenuChoice());

    switch (1*this.getMenuChoice()) { // choose dice to keep, pick a category, re-roll or exit game

        case 1:  // Select dice you want to keep in between rolls
        {
            console.log("Hit switch case 1");
            this.numRolls++;
            document.getElementById("scorecard-div").style.visibility = "hidden";//"visible";           
            break;
        }
        case 2: // Keep points from 1 category and end their turn
        {
            console.log("Hit switch case 2");
            numRolls = MAXROLLS; // reassign it, so while(numRolls<maxRolls) stops

            // Ask player to pick category & set player's final scorecard's points each time they choose a category         
            this.showPickCategory();


            // reassign player's hiScore each time their finalScoreCard's hiScore is updated
            this.finalSC[this.index].setUpLowSums();
            this.player[this.index].setHiScore(this.finalSC[this.index].getTotalScore());
            //console.log(name + "'s hiScore = " + this.player[this.index].getHiScore());


            // if it is NOT the last round, then print player's final scorecard
            if (this.player[this.index].getRound() === MAXRND) {
                //alert("Tallying final score...\n");
                console.log("\nTallying final score...\n");
            } else {
                this.finalSC[this.index].printFinalSC(name);
            }
            break;
        }
        case 3:
        {   // Roll dice again by breaking out of switch()
            console.log("Hit switch case 3. Reroll");
            this.scorecard[this.index].reRoll(); // Re-Roll dice       
            this.scorecard[this.index].fillScoreCard(); // Set & print scorecard with possible points based on dice values
            this.numRolls++; // increment numRolls every time dice are rolled    
            break;
        }
        default: // if they exit early, then reset values to break out of 
        {        // all the loops & print final scorecards
            numRolls = MAXROLLS;
            this.finalSC[0].setRound(MAXRND); // stops the for loop in startGame()
            console.log("           Hit switch default...Leaving program");
        }
    } // ends switch(response)    
    console.log("Hit end of switch. numRolls = " + this.numRolls +"\n");
};

Yahtzee.prototype.showMenuOnClick = function () {
   
    document.getElementById("show-menu-btn").style.visibility = "hidden";//"visible";
    document.getElementById("diceDiv").style.visibility = "visible";//"hidden";//
    document.getElementById("scorecard-div").style.visibility = "visible"; //"hidden";//
    document.getElementById("msgDiv").innerHTML = ""; //"hidden";//
    document.getElementById("menu-div").style.visibility = "visible"; //"hidden";//
};


//*****************************************************************
//                   Writes menu for play() 
//*****************************************************************
Yahtzee.prototype.printMenu = function () {

    var msgDiv = document.getElementById('menu-div');
    var select = document.createElement('select');
    select.setAttribute('id','menu-select');
    
    var option1 = document.createElement('option');
    option1.setAttribute('value',1);
    option1.innerHTML = 'Select Dice';
    
    var option2 = document.createElement('option');
    option2.setAttribute('value',2);
    option2.innerHTML = 'Pick a Scorecard Category';    
    
    var option3 = document.createElement('option');
    option3.setAttribute('value',3);
    option3.innerHTML = 'Roll';
    
    var option4 = document.createElement('option');
    option4.setAttribute('value',4);
    option4.innerHTML = 'Exit';
   
    msgDiv.append(select);
    select.append(option1);
    select.append(option2);
    select.append(option3);
    select.append(option4);

    var btn = this.makeBtn('submit', 'Pick Category', 'menuBtn');
    btn.setAttribute('onclick', 'yahtzee.menuOnClick(yahtzee)');
    msgDiv.append(btn);
    console.log("Hit printMenu().");
};

//*********************************************************
//              Make a button   
//*********************************************************
Yahtzee.prototype.makeBtn = function (type, val, id) {
    var input = document.createElement('button');
    input.setAttribute('type', type);
    input.setAttribute('id', id);
    input.setAttribute('value', val);
    input.innerHTML = val;
    return input;
};

//*****************************************************************
//              Write to nPlayers div
//*****************************************************************
Yahtzee.prototype.promptNPlayer = function () {

    console.log('Hit promptNPlayer()');
    var nPlayrDiv = document.getElementById('nPlayrDiv');
    var string = "Enter 1 or 2 players?";
    string += '<input type="text" id="nPlayrInput" name="nPlayrInput" min="1" max="4" required size="1">';
    string += '<button type="submit" id="nPlayrBtn" onclick="yahtzee.menuOnClick(yahtzee)">Enter</button>'; //
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
        //alert("New High Score of " + user.getHiScore() + "!\n");
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

//************************************************************
//              Write 1 dice's value to html
//************************************************************
Yahtzee.prototype.makeDice = function (i, id, val) {

    //console.log("Hit makeDice()");     
    var btn = document.createElement('button');
    btn.setAttribute('type', 'submit');
    btn.setAttribute('class', 'dice-class');
    btn.setAttribute('id', id);
    btn.setAttribute('value', val);
    btn.innerHTML = val;
    return btn;
};

//**********************************************************
//                  Write all dice to html
//**********************************************************
Yahtzee.prototype.printDice = function () {

    console.log("Hit printDice()");
    var diceDiv = document.getElementById('diceDiv');
    var diceBtn = [5];

    for (var i = 0; i < 5; i++) {
        var id = 'dice' + i;
        diceBtn[i] = this.makeDice(i, id, this.scorecard[this.index].getDice(i));
        diceDiv.append(diceBtn[i]);
    }

    var row = document.createElement('div');
    row.setAttribute('class', "row");
    var p = document.createElement('p');
    p.innerHTML = 'dice1   dice2   dice3   dice4   dice5   ';
    var div = document.createElement('div');
    div.setAttribute('id', "selectDiceDiv");

    diceDiv.append(row);
    row.append(p);
    row.append(div);

    //document.getElementById("diceDiv").style.visibility = "visible";//diceCol  
    //document.getElementById("diceCol").style.visibility = "hidden";//diceDiv
    //document.getElementById("selectDiceDiv").style.visibility = "visible";//"hidden"; 

    // Put random ans because the game isn't stopping and waiting for the user's input from the html page
    //var ans = (1 + (Math.floor(Math.random() * 5)));

    var div = document.getElementById('selectDiceDiv');
    var string = "<br><p>Click on the dice you want to keep or stop:</p>";
    //string += '<input type="text" id="selectDiceInput" name="selectDiceInput" min="1" max="1" required size="1">';
    string += '<button type="submit" id="stopDiceOnClick" onclick="yahtzee.stopDiceOnClick()">Stop</button><br>';
    div.innerHTML = string;
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
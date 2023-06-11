//To do: 
// change setAttribute(onclick) to .addEventListeners() -> cant because I need to pass yahtzee  buttons[i].setAttribute("click", 'yahtzee.categoryClick(yahtzee)');
//Add 2 players back after it works with 1 player 
// FYI: var ans = (1 + (Math.floor(Math.random() * 5)));


// Global constants for Yahtzee Class
var MINSIZE = 1;
var MAXROLLS = 3;
var MAXRND = 13;


//*****************************************************************
//  Yahtzee Constructor. Public properties of Yahtzee class 
//*****************************************************************

function Yahtzee(user) {

    //console.log("Hit Yahtzee() Constructor");
    this.userCurrentHiScore = user.getHiScore();
    this.setP1Winner(false);
    this.setNPlayer(MINSIZE);
    this.setIndex(0); // player index. Who's turn it is when there's 2 players
    this.menuChoice = 0; // User menuChoice made during play()    
    this.setNumRolls(0);
    this.round = 1;

    this.player = new Array(); // Aggregate instance of User Class to create player(s) for the game
    this.scorecard = new Array(); // Aggregate new instance of ScoreCard Class for possible points
    this.finalSC = new Array();// Aggregate new instance of ScoreCard Class for final points

    for (var i = 0; i < this.getNPlayer(); i++) {
        this.player[i] = new User(i + 1);
        this.scorecard[i] = new ScoreCard(this.player[i].getName());  // possible scorecard points. Aggregates Array of ScoreCard class
        this.finalSC[i] = new ScoreCard(this.player[i].getName());   // final scorecard. Aggregates Array of ScoreCard class       
    }

    this.player[this.index].setUser2(user.getId(), user.getName());// Reset player 1's name with user's name  
    this.finalSC[this.index].setFName(user.getName());
    this.scorecard[this.index].setFName(user.getName());
    this.scorecard[this.index].fillScoreCard();
    console.log(this.finalSC[this.index]);
    this.setHTML();
}


//****************** Write and hide html nodes to Scorecard.html ***************
Yahtzee.prototype.setHTML = function () {

    //console.log('Hit setHTML');    
    this.printDice();
    this.printMenu();
    //this.showScorecard(); // prints scorecard dynamically
    document.getElementById("dice-div").style.visibility = "hidden";//"visible"; // 
    document.getElementById("scorecard-col").style.visibility = "hidden";//"visible"; //
    document.getElementById("menu-div").style.visibility = "hidden";//"visible"; //
    document.getElementById("rnd-roll-col").style.visibility = "hidden";// show current round and roll

    // Event handler to start game
    var menuDiv = document.getElementById('show-menu-div');
    var menuBtn = this.makeBtn('submit', 'Roll', 'start-btn');
    menuBtn.setAttribute('onclick', 'yahtzee.showMenuModal()');
    menuDiv.append(menuBtn);
    this.increNumRolls();
    this.writeRollRnd();
    this.getRules();
    this.welcomeMsg();   // print welcome message depending on num players
};


Yahtzee.prototype.showMenuModal = function () {
    console.log("Hit showMenuModal()");
    document.getElementById("start-btn").style.visibility = "hidden";
    document.getElementById("stop-dice-div").style.visibility = "hidden";
    document.getElementById("dice-div").style.visibility = "visible";
    document.getElementById("scorecard-col").style.visibility = "visible";
    document.getElementById("menu-div").style.visibility = "visible";
    document.getElementById("rnd-roll-col").style.visibility = "visible";// show current round and roll
    document.getElementById("msg-div").innerHTML = "";

    // Remove event listener on all dice
    for (var i = 0; i < 5; i++) {
        var diceBtn = document.getElementById('dice' + i);
        diceBtn.setAttribute('onclick', '');
    }
    // Remove event listener to each points category on scorecard
    var buttons = document.getElementsByClassName("category-button");
    for (var i = 0; i < buttons.length; i++) {
        buttons[i].setAttribute("onclick", '');
    }
};

Yahtzee.prototype.pause = function () {
    console.log("Hit pause() to view final scorcard.   round=" + this.getRound());
    this.setNumRolls(0);
    // Write a message and stop button to user
    var msgDiv = document.getElementById('msg-div');
    var string = '<button type="submit" id="catgyBtn" onclick="yahtzee.checkRound()">Continue</button>';
    msgDiv.innerHTML = string;
    document.getElementById("category-div").innerHTML = " ";
    document.getElementById("dice-div").style.visibility = "hidden";
};

//*****************  check numRolls   *****************
Yahtzee.prototype.checkRound = function () {
    
    console.log("Hit checkRound().  numRolls=" + this.getNumRolls() + "  round=" + this.getRound()); 
        
    if (this.getRound() <= MAXRND) {
        this.rerollScorecard();
        this.checkNumRolls();
    } else { // if last round
        document.getElementById('msg-div').innerHTML = "Tallying final score...";
        console.log("\nTallying final score...\n");
        this.isP1Winner();
    }
};
//*****************  check numRolls   *****************
Yahtzee.prototype.checkNumRolls = function () {

    console.log("Hit checkNumRolls().  numRolls=" + this.getNumRolls() + "  round=" + this.getRound());
    if (this.numRolls === MAXROLLS) {  // if it is last roll, force switch case 2 to run        
        this.setMenuChoice(2);
        console.log("Hit numRolls === MAXROLLS.  menuChoice = " + this.getMenuChoice());
        this.callSwitch();
    } else { // if this.numRolls<MAXROLLS
        this.showMenuModal();
    }
};


//*********  Handles Event listener to stop selecting dice  ******************  
Yahtzee.prototype.rerollScorecard = function () {
    this.increNumRolls();
    this.writeRollRnd();
    console.log("\nHit rerollScorecard()    numRolls=" + this.getNumRolls());
    this.scorecard[this.index].reRoll(); // Re-Roll dice       
    this.scorecard[this.index].fillScoreCard(); // Set & print scorecard with possible points based on dice values
    this.checkNumRolls();
};

//*****************  Handles player's menu choice   *****************
Yahtzee.prototype.callSwitch = function () {

    console.log("Hit callSwitch().  menuChoice=" + this.getMenuChoice() + "  round=" + this.getRound() + "  roll=" + this.getNumRolls());

    switch (1 * this.getMenuChoice()) { // 1.choose dice to keep, 2.pick a category, 3.re-roll or exit game

        case 1:  // Select dice you want to keep in between rolls
        {
            console.log("   Hit switch case 1. Select Dice.  numRoll=" + this.numRolls);
            document.getElementById("menu-div").style.visibility = "hidden";
            document.getElementById("scorecard-col").style.visibility = "hidden";
            document.getElementById("stop-dice-div").style.visibility = "visible";
            // Event listener for click on dice
            for (var i = 0; i < 5; i++) {
                var diceBtn = document.getElementById('dice' + i);
                diceBtn.setAttribute('onclick', 'yahtzee.diceClick(yahtzee)');
            }
            break;
        }
        case 2: // Keep points from 1 category and end their turn
        {
            console.log("   Hit switch case 2");
            this.showCatgryModal();
            break;
        }
        case 3:
        {   // Roll dice again by breaking out of switch()
            console.log("   Hit switch case 3. Reroll");
            this.rerollScorecard(); // reroll dice and reset possible scorecard with points               
            break;
        }
        default: // if they exit early, then reset values to break out of 
        {        // all the loops & print final scorecards
            console.log("   Hit switch default");
            document.getElementById("menu-div").style.visibility = "hidden";
            document.getElementById("dice-div").style.visibility = "hidden";
            this.setNumRolls(MAXROLLS); // reassign it, so while(numRolls<maxRolls) stops
            this.setRound(MAXRND);
            this.isP1Winner();
            console.log("           Hit switch default...Leaving program");
        }
    } // ends switch(response)    
    console.log("Hit end of switch. numRolls = " + this.numRolls + "\n");
};




//*****************  Set points in player's final scoreboard  *****************  
//                          categoryClick() calls it.
Yahtzee.prototype.setFinalSC = function (category) {

    // set final scorecard's score[category]
    this.finalSC[this.index].scores[category] = this.scorecard[this.index].scores[category];
    // set flag so this category on finalSC and scorecard, so it can't be selected anymore
    this.finalSC[this.index].isCatgryPicked[category] = true;
    this.scorecard[this.index].isCatgryPicked[category] = true;
    console.log('\nHit setFinalSC().  picked category ' + category + "=" + this.scorecard[this.index].scores[category]
            + ".   finalSC.scores[" + category + "]=" + this.finalSC[this.index].scores[category] + "\n");
    //console.log("finalSC.isCatgryPicked = ["+this.finalSC[this.index].isCatgryPicked);
    //console.log("scorecard.isCatgryPicked=["+this.scorecard[this.index].isCatgryPicked);
};



//*****************   CALCULATE SCORES, CHECK FOR WINNER AND HISCORE  *****************
Yahtzee.prototype.isP1Winner = function () {

    // Print player's final scorecard 
    this.finalSC[0].setRnd(13);  // round 13 will check if they hit upperScore bonus in printFinalSC() 
    console.log('Hit isP1Winner()');
    this.scorecard[0].setRnd(13);
    this.finalSC[0].printFinalSC(this.player[0].getName());   


    // if nPlayer === 1, then player1 is automatically winner
    if (this.getNPlayer() === 1) {
        this.setP1Winner(true);
    }

    // If there are more than 1 player, then print player 2's final scorecard
    else { //(this.getNPlayer() > 1) {
        this.finalSC[1].setRnd(13); // rnd 13 will check if they hit upperScore bonus in printFinalSC()
        this.scorecard[1].setRnd(13);
        this.finalSC[1].printFinalSC(this.player[1].getName());


        //console.log('this.getNPlayer() = '+ this.getNPlayer());
        console.log("\n" + this.player[0].getName() + " vs " + this.player[1].getName() + "\n");
        console.log(this.player[0].getHiScore() + "     vs " + this.player[1].getHiScore());

        var msgDiv = document.getElementById('msg-div');
        var msg1 = "\n\nGame Over!\n";

        // Check is p1 is winner, tie or loser
        if (this.player[0].getHiScore() > this.player[1].getHiScore()) {
            this.setP1Winner(true);
            var msg2 = this.player[0].getName() + " won!\n";
            
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

    if (this.getP1Winner()) {
        this.isNewHiScore();
    }
};


//*********** Check if user has new hiScore  *****************
// Player 1 represents the user object. ONLY change user's hiScore if player1 wins AND
// player1 has a higher score than the user's hiScore that is currently stored in database 
Yahtzee.prototype.isNewHiScore = function () {
    
    console.log("Hit isNewHiScore(). p1.hiScore=" + this.player[0].getHiScore() + " > user.hiScore=" + this.userCurrentHiScore+"?");
    var name = this.player[0].getName();
    var msg1 = "<br><br>Game Over<br>"+this.player[0].getName() + " won!<br>";
    var msg2 = "<br><p>"+this.player[0].getHiScore()+" Points!</p>";
    
    if (this.player[0].getHiScore() > this.userCurrentHiScore) {
        msg2 = "<br><p>New High Score of " +this.player[0].getHiScore() + "!</p>";
        console.log(msg2);
        this.player[0].reWrtRecord(); //update this record in the database                 
    }   
   var msgDiv = document.getElementById('msg-div');
   msgDiv.innerHTML=msg1+msg2;
};


//*****************************************************************
//                      EVENT HANDLERS Section
//*****************************************************************


//************  Handles player's menuChoice  ************
Yahtzee.prototype.menuClick = function () {
    var choice = document.getElementById('menu-select').value; //cin>>choice;
    this.setMenuChoice(choice);
    //alert("Hit menuClick(). value = " + choice + "  menuChoice=" + this.getMenuChoice());
    console.log("Hit menuClick(). value=" + choice + "  menuChoice=" + this.getMenuChoice());
    this.callSwitch();
};


Yahtzee.prototype.diceClick = function () {
    var id = event.srcElement.id;       // https://stackoverflow.com/questions/4825295/onclick-to-get-the-id-of-the-clicked-button  
    var num = parseInt(id.charAt(4));
    console.log('Hit diceClick().  dice' + num + '=' + this.scorecard[this.index].dice[num]);
    this.scorecard[this.index].pushThisDice(num);
    this.scorecard[this.index].getSelectedDice();
};


//********* Handles event when any scorecard category buttons clicked **********
Yahtzee.prototype.categoryClick = function () {

    var str = event.srcElement.id;       // https://stackoverflow.com/questions/4825295/onclick-to-get-the-id-of-the-clicked-button  
    var id = str.slice(5,7);
    var category = parseInt(id);//(id.charAt(5));
    console.log('Hit categoryClick().  isCatgryPicked['+category+"]="+this.finalSC[this.index].isCatgryPicked[category]);

    // Conditional stops a set category from being overwritten
    if ((this.finalSC[this.index].isCatgryPicked[category]) === true) {

        var str1 = "Pick a category between 1 and 13.";
        var str2 = "Category " + category + " has already been selected.\n";
        console.log(str2 + str1);
        alert(str2 + str1);

    } else { // set final scorecard and continue playing

        this.setFinalSC(category); // Set player's final scorecard   
        this.finalSC[this.index].setUpLowSums();  // recalculate player's hiScore each time their finalScoreCard's hiScore is updated
        this.player[this.index].setHiScore(this.finalSC[this.index].getTotalScore());           
        //console.log(name + "'s hiScore = " + this.player[this.index].getHiScore()); 
        this.finalSC[this.index].printFinalSC(this.player[this.index].getName());
        this.increRound(); 
        //this.writeRollRnd();
        this.pause();
    }
};



//*****************************************************************
//                   Mutator Functions
//*****************************************************************
Yahtzee.prototype.increRound = function () {
    this.round++;
    this.scorecard[this.index].setRnd(this.getRound());
    this.finalSC[this.index].setRnd(this.getRound());
    console.log('Hit increRound().  round=' + this.getRound());
};

Yahtzee.prototype.setRound = function (r) {
    this.round = r;
    this.scorecard[this.index].setRnd(this.getRound());
    this.finalSC[this.index].setRnd(this.getRound());
    console.log('Hit setRound().  round=' + this.getRound());
};

Yahtzee.prototype.increNumRolls = function () {
    this.numRolls++;
    console.log('Hit increNumRolls().  numRolls=' + this.getNumRolls());
};

Yahtzee.prototype.setNumRolls = function (r) {
    this.numRolls = r;
};

Yahtzee.prototype.setMenuChoice = function (num) {
    this.menuChoice = num;
};

Yahtzee.prototype.setP1Winner = function (bool) {
    this.p1Winner = bool;
};

Yahtzee.prototype.setNPlayer = function (num) {
    this.nPlayer = num;
};

Yahtzee.prototype.setIndex = function (i) {
    this.index = i;
};


//*****************************************************************
//                Accessor Functions
//*****************************************************************

Yahtzee.prototype.writeRollRnd = function () {
    var string = this.player[this.index].getName()+"'s turn.<br>Round "+this.getRound()+"<br>Roll "+this.getNumRolls()+"<br>";
    var div = document.getElementById('rnd-roll-col');
    div.innerHTML = string;
};

Yahtzee.prototype.getRound = function () {
    return this.round;
};

Yahtzee.prototype.getNumRolls = function () {
    return this.numRolls;
};

Yahtzee.prototype.getMenuChoice = function () {
    return this.menuChoice;
};

Yahtzee.prototype.getP1Winner = function () {
    return this.p1Winner;
};

Yahtzee.prototype.getNPlayer = function () {
    return this.nPlayer;
};

Yahtzee.prototype.getIndex = function () {
    return this.index;
};



//******************************************************************************
//               Dynamically write objects to Scorecard.html Section
//******************************************************************************


//   Set pick category div to allow player to pick points from possible scorecard
Yahtzee.prototype.showCatgryModal = function () {

    console.log("Hit showCatgryModal()");
    document.getElementById("stop-dice-div").style.visibility = "hidden"; //"visible";// 
    document.getElementById("menu-div").style.visibility = "hidden";
    document.getElementById("scorecard-col").style.visibility = "visible";

    // Add event listener to each points category on scorecard
    var buttons = document.getElementsByClassName("category-button");
    for (var i = 0; i < buttons.length; i++) {
        buttons[i].setAttribute("onclick", 'yahtzee.categoryClick(yahtzee)');
    }
    
    this.setNumRolls(MAXROLLS); // reassign it, so while(numRolls<maxRolls) stops  
    this.writeRollRnd(); 
         
    // Write a message to user
    var msgDiv = document.getElementById('category-div');
    var string = "<br>Click on a points category.<br/>";
    msgDiv.innerHTML = string;

    if (this.getNumRolls() === MAXROLLS) { // if last roll, then show dice, but don't let them pick any
        
        document.getElementById("dice-div").style.visibility = "visible";
        // Remove event listener on all dice
        for (var i = 0; i < 5; i++) {
            var diceBtn = document.getElementById('dice' + i);
            diceBtn.setAttribute('onclick', '');
        }

    } else {
        document.getElementById("dice-div").style.visibility = "hidden";
    }
};


//*****************  Make a button  *****************  
Yahtzee.prototype.makeBtn = function (type, val, id) {
    var input = document.createElement('button');
    input.setAttribute('type', type);
    input.setAttribute('id', id);
    input.setAttribute('value', val);
    input.innerHTML = val;
    return input;
};


//*****************   Writes menu for play() *****************
Yahtzee.prototype.printMenu = function () {
    //console.log("Hit printMenu().");
    var msgDiv = document.getElementById('menu-div');
    var p = document.createElement('p');
    var string = "<br> Play Options: <br>";
    string += "1: Select Dice.<br>";
    string += "2: Pick Category and End Your Turn.<br>";
    string += "3: Reroll.<br>";
    string += "4: Exit<br>";
    p.innerHTML = string;
    msgDiv.append(p);

    var select = document.createElement('select');
    select.setAttribute('id', 'menu-select');

    var option1 = document.createElement('option');
    option1.setAttribute('value', 1);
    option1.innerHTML = '1. Select Dice';

    var option2 = document.createElement('option');
    option2.setAttribute('value', 2);
    option2.innerHTML = '2. Pick a Scorecard Category';

    var option3 = document.createElement('option');
    option3.setAttribute('value', 3);
    option3.innerHTML = '3. Reroll';

    var option4 = document.createElement('option');
    option4.setAttribute('value', 4);
    option4.innerHTML = '4. Exit';

    msgDiv.append(select);
    select.append(option1);
    select.append(option2);
    select.append(option3);
    select.append(option4);

    var btn = this.makeBtn('submit', 'Enter', 'menuBtn');
    btn.setAttribute('onclick', 'yahtzee.menuClick(yahtzee)');
    msgDiv.append(btn);
};


//*****************  Write 1 dice's value to html  *****************
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


//*****************  Write all dice to html  *****************
Yahtzee.prototype.printDice = function () {

    //console.log("Hit printDice()");
    var diceDiv = document.getElementById('dice-div');
    diceDiv.setAttribute('style', 'background-color:white');
    var diceBtn = [5];
    for (var i = 0; i < 5; i++) {
        var id = 'dice' + i;
        diceBtn[i] = this.makeDice(i, id, this.scorecard[this.index].getDice(i));
        diceDiv.append(diceBtn[i]);
    }

    // Print dice labels
    var row = document.createElement('div');
    row.setAttribute('class', "row");
    var p = document.createElement('p');
    p.innerHTML = 'dice1   dice2   dice3   dice4   dice5   ';
    diceDiv.append(row);
    row.append(p);

    // Print button to stop selecting dice
    var div = document.createElement('div');
    div.setAttribute('id', "stop-dice-div");
    row.append(div);

    var div = document.getElementById('stop-dice-div');
    var string = "<br><p>Click on the dice you want to keep or stop:</p>";
    string += '<button type="submit" id="rerollScorecard" onclick="yahtzee.rerollScorecard()">Stop</button><br>';
    div.innerHTML = string;
};


//*****************  Write message depending on num players  *****************
Yahtzee.prototype.welcomeMsg = function () {
    if (this.getNPlayer() > 1) {
        var string = this.player[this.index].getName() + " vs " + this.player[1].getName();
    } else {
        string = "Welcome " + this.player[this.index].getName();
    }
    document.getElementById("msg-div").append(string);
    //console.log("Hit welcomeMsg().  " + string);
};


//*****************  Print Yahtzee rules  *****************
Yahtzee.prototype.getRules = function () {
    var string = "WELCOME TO YAHTZEE!! <br><br>";
    string += "RULES: <br><br>";
    string += "Yahtzee is a game played with five dice.<br>Objective is to score as many points as possible in 13 rounds. <br>";
    string += "Each player has up to three rolls per turn to achieve the most points possible. <br>";
    string += "At the end of each player's turn, they must choose a category to score their points in. <br><br><br><br>";
    document.getElementById("msg-div").innerHTML = string;
};


//*****************  Write scorecard  *****************
Yahtzee.prototype.showScorecard = function () {

    var catgry = ['Aces', 'Twos', 'Threes', 'Fours', 'Fives', 'Sixes',
        'Three of a Kind', 'Four of a Kind', 'Three of Kind', 'Full House',
        'Small Straight', 'Large Straight', 'Yahtzee', 'Chance',
        'Upper Total', 'Bonus', 'Lower Total', 'Grand Total'];

    var div = document.getElementById('scorecard-col');
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


// ***************** Write to nPlayers div  *****************
Yahtzee.prototype.promptNPlayer = function () {

    console.log('Hit promptNPlayer()');
    var nPlayrDiv = document.getElementById('nPlayrDiv');
    var string = "Enter 1 or 2 players?";
    string += '<input type="text" id="nPlayrInput" name="nPlayrInput" min="1" max="4" required size="1">';
    string += '<button type="submit" id="nPlayrBtn" onclick="yahtzee.menuClick(yahtzee)">Enter</button>'; //
    nPlayrDiv.innerHTML = string;
    document.getElementById("nPlayrBtn").addEventListener("click", this.nPlayrClick);
};


//***************** Handle Event listener for nPlayrDiv  *****************
Yahtzee.prototype.nPlayrClick = function () {
    console.log("Hit nPlayrClick()");
    alert("Hit nPlayrClick()");
    var num = this.value;
    alert("nPlayrInput =" + num);
    //num = (num == null ) ? 1 : num;
    this.nPlayer = num;         //this.setNPlayer(num);
    console.log("Hit nPlayrClick().  num =" + num + "  this.nPlayer=" + this.nPlayer);
    alert("Hit nPlayrClick().  num =" + num + "  this.nPlayer=" + this.nPlayer);
};
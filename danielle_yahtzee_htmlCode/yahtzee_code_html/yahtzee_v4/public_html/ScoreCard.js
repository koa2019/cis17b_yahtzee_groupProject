// Global constants for ScoreCard Class
const NUM_DICE = 5;
const NUM_CATGRY = 13; // number of scoring categories

function ScoreCard() {

    // Public properties of ScoreCard class
    //console.log("Hit ScoreCard()");
    this.round = 0;
    this.upperScore = 0;
    this.lowerScore = 0;
    this.isSelected = [NUM_CATGRY]; // Stops categories from being overwritten or displayed twice
    this.scores = [NUM_CATGRY];     // points for each of 13 categories in scorecard
    this.dice = [NUM_DICE]; // ? Are we using this cuz we have a local one in play() or do we need to connect it with local in play()
    this.selected = [];  // Create vector for the this.dice we're keeping for final points

    // Initialize arrays
    for (var c = 0; c < NUM_CATGRY; c++) {
        this.scores[c] = -1;
        this.setScoreCard(c);
        this.isSelected[c] = false;
    }

   // Initialize array of Dice class object
    for (var i = 0; i < NUM_DICE; i++) {
        this.dice[i] = 0;
    }
    //console.log("End of ScoreCard()");
};


// Write one scores element to ScoreCard.html
ScoreCard.prototype.setScoreCard = function (indx) {
    
    //console.log("Hit setScoreCard()");    
    var button = document.getElementById("catgy"+indx);
   
    // set the button's value to the value entered by the user
    button.value = this.scores[indx];
    //console.log("setScoreCard().  scores["+indx+"] = "+button.value);

    // display the value on the button
    button.innerHTML = button.value;  
};


//************************************************************
//               Fill scorecard with possible points
//************************************************************

ScoreCard.prototype.fillScoreCard = function () {

    var NUM_DICE_SIDES = 6;
    var temp_scores = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]; // vector<int> scores(NUM_CATGRY, 0);   
    var counts = [0, 0, 0, 0, 0, 0];              // vector<int> counts(6, 0);   
    //alert("scores[1] = " + scores[1] + "  counts[1] = " + counts[1]);


    // Sort array in ascending order ?
    this.dice.sort(); // sort(dice, dice + NUM_DICE);
    //console.log("Sorted this.dice...");
    //this.printDice();    


    // Loops 5 times and is Accumulating how many dice are the same and their total pts
    for (var i = 0; i < NUM_DICE; i++) {
        var index = this.getDice(i) - 1;
        counts[index]++;                     // Counting how many of dice have same value
        temp_scores[index] += this.dice[i]; //  Setting points in upper section of scorecard
        //console.log("index = " + index + "  this.dice[" + i + "] = " + this.dice[i]);
    }


    // Set possible points to scorecard's upper section
    for (var i = 0; i < NUM_DICE_SIDES; i++) {
        this.recordScore(i + 1, temp_scores[i]);
    }

    //  Check Lower section of scorecard  starts here  
    var three_of_a_kind = false;
    var four_of_a_kind = false;
    var full_house = false;
    var small_straight = false;
    var large_straight = false;
    var isYahtzee = true;

    // Check for Three and four of a kind
    for (var count in counts) {
        if (count >= 3) {
            three_of_a_kind = true;
            //console.log("three_of_a_kind = true");
            if (count >= 4) {
                four_of_a_kind = true;
                //console.log("four_of_a_kind = true");
                break;
            }
        }
    }

    // if 3 or 4 of kind is true, then set pts in scores[]
    //this.recordScore(7, three_of_a_kind ? accumulate(this.dice, this.dice + NUM_DICE, 0) : 0);
    //this.recordScore(8, four_of_a_kind ? accumulate(this.dice, this.dice + NUM_DICE, 0) : 0);


    // Check if full house
    if ((((this.dice[0] === this.dice[1]) && (this.dice[1] === this.dice[2])) &&
            (this.dice[3] === this.dice[4]) &&
            (this.dice[2] !== this.dice[3])) ||
            ((this.dice[0] === this.dice[1]) &&
                    ((this.dice[2] === this.dice[3]) && (this.dice[3] === this.dice[4])) &&
                    (this.dice[1] !== this.dice[2])))
    {
        full_house = true;
    }

    // if Full house, then set pts in scores[]
    if (full_house) {
        this.recordScore(9, 25);
    } else {
        this.recordScore(9, 0);
    }


    // Check for Small and large straight
    for (var i = 0; i < 2; i++) {
        if (counts[i] && counts[i + 1] && counts[i + 2] && counts[i + 3]) {
            small_straight = true;
            if (counts[i + 4]) {
                large_straight = true;
                break;
            }
        }
    }

    // if small or large straight, then set pts in scores[]
    this.recordScore(10, small_straight ? 30 : 0);
    this.recordScore(11, large_straight ? 40 : 0);

    // if Yahtzee, then set pts in scores[]    
    //isYahtzee = all_of(counts.begin(), counts.end(), [&](int count) { return count === NUM_DICE; });
    this.recordScore(12, isYahtzee ? 50 : 0);

    // Chance set pts in scores[]
    //this.recordScore(NUM_CATGRY, accumulate(this.dice, this.dice + NUM_DICE, 0));    

    //console.log("<br/>Inside fillScorecard(). Points Possible...<br/>"); 
    //this.printScoreCard();     
};


//************************************************************
//              Set points in scores array           
//************************************************************

ScoreCard.prototype.recordScore = function (category, score) {

    //console.log("Inside recordScore()");
    //this.get_isSelected();   
    //console.log("round = " + this.round);
    var indx = category - 1; //ScoreCard's range [0,12]
    
    // if it's not last round, then set scores array in Yahtzee object
    if (this.round >= 0 && this.round <= 12) {
        this.scores[indx] = score;
        this.setScoreCard(indx); // rewrite points on ScoreCard.html
    }

    // if it is last round AND this category has NOT be selected then set scores array
    else if (this.round > 12 && (this.isSelected[category - 1] === false)) {
        this.scores[indx] = score;
        this.setScoreCard(indx); // rewrite points on ScoreCard.html
        
    } else { // -1 sets this category to null value
        this.scores[indx] = -1;
        this.setScoreCard(indx); // rewrite points on ScoreCard.html
    } 
};


//*****************************************************************************
//        FIGURE OUT WHAT TO REPLACE CIN >> CHOICE WITH IN JS.
//        
//        Set player's scorecard using values from possible scorecard
//*****************************************************************************

ScoreCard.prototype.setFinalSC = function (scorecard) {

    var choice = 0;
    console.log("******INSIDE setFinalSC()**************");
    console.log("Pick a Category between 0 and 12.<br/>");

    //cin >> choice;
    //choice -= 1; // subtract one because array range [0,12] 
    console.log("Choice = " + choice + "<br/>");  // View choice

    // Conditional stops a category from being overwritten on final scorecard
    if (this.isSelected[choice] === true) {
        console.log("Category " + choice + " has already been selected.<br/>Choose another category:  ");
    }

    // Set points in player's final scoreboard
    this.scores[choice] = scorecard.scores[choice];

    // set flag so this category, so it can't be selected anymore
    this.isSelected[choice] = true;
    scorecard.isSelected[choice] = true;


    console.log("finalSC.scores[" + choice + "] = " + this.scores[choice] + "<br/>");
    //console.log("finalSC.isSelected[" + choice + "]   = " + this.isSelected[choice] + "<br/>");
    //console.log("scorecard.isSelected[" + choice + "] = " + scorecard.isSelected[choice] + "<br/>");
    console.log("******END OF setFinalSC()**************<br/><br/>");
};


// Roll a single this.dice
ScoreCard.prototype.roll = function (i) {

    this.dice[i] = (1 + (Math.floor(Math.random() * 6)));
    //console.log("Hit roll(). this.dice["+i+"] = " + this.dice[i]);
};


// Set which round it is
ScoreCard.prototype.setRound = function (r) {
    //console.log("Hit setRound()<br/>");
    this.round = r;
};


//*****************************************************************
//               Set Dice class array
//*****************************************************************
ScoreCard.prototype.setDice = function () {

    console.log("Hit setDice()");

    // Re-Roll Dice. loops through selected vector, and checks which this.dice # to re-roll ?
    for (var j = 0; j < NUM_DICE; j++) {

        // https://www.w3schools.com/jsref/jsref_find.asp
        // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/find
        // syntax: array.find(function(currentValue, index, arr),thisValue)
        var n = 0;
        n = this.selected.find(this.isFound);
        console.log("keeping dice" + (n));
        if (n === undefined) {
            //if(this.selected.find(this.selected.begin(), this.selected.end(), j) === this.selected.end()) {

            console.log("...Re-Rolling Dice");
            this.roll(j); // re-roll this this.dice
        }
    }
    this.dice.sort();
    this.printDice(); // Print dice
};


ScoreCard.prototype.isFound = function (indx) {
    console.log("   Hit isFound(). indx = " + indx + "<br/>");
    //var i = (indx === isSelected[indx]) ? indx : undefined;
    return indx >= 0;
};

//*****************************************************************
//             Keep this dice in selected vector
//*****************************************************************
ScoreCard.prototype.pushThisDice = function (choice) {

    choice -= 1;
    this.selected.push(choice); //selected.push_back(choice - 1);        
    //console.log("<br/>selected dice" + this.selected + "<br/>");
};


//************************************************************
//          Calculate totals for upper, lower scorecard sections            
//************************************************************

ScoreCard.prototype.setUpLowSums = function () {

    //console.log("<br/>Hit setUpLowSums()<br/>");
    // Calculate upper section total points
    var total = 0;
    for (var i = 0; i < 6; i++) {

        if (this.scores[i] >= 0) {
            total += this.scores[i];
        }

        if (i === 5) {
            this.upperScore = total;
            //alert("Hit i==5. upperScore=" + this.upperScore +" total="+total);
        }
    }

    // Calculate lower section total points
    total = 0;
    for (var i = 6; i < NUM_CATGRY; i++) {

        if (this.scores[i] >= 0) { // only add values over zero
            total += this.scores[i];
        }
        if (i === 12) { // if it is the last element in scores array, set lowerScore
            this.lowerScore = total;
            //alert("Hit i==12. lowerScore="+ this.lowerScore +" total="+total);
        }
    }
    //console.log("upperScore = " + upperScore + "  lowerScore = " + lowerScore);
    //console.log("End of setUpLowSums()<br/>");
};

//************************************************************
//          Add upper and lower sections of scorecard  
//      Check if upper section qualifies for bonus points          
//************************************************************

ScoreCard.prototype.getTotalScore = function () {

    var total = 0;

    // if upper section is 63 or more than add 25 pts to total
    if (this.upperScore >= 63) {
        total += 25;
    }
    total = this.upperScore + this.lowerScore;

    return total;
};


// Prints this player's final ScoreCard Class members
ScoreCard.prototype.printFinalSC = function (name) {

    //console.log("<br/>Hit printFinalSC()"); 
    var bonusMin = 63;
    console.log("<br/><br/>" + name + "'s Final ScoreCard<br/>");
    this.printScoreCard();
    this.setUpLowSums();

    console.log("upperScore:   " + this.getUpperScore() + "<br/>");
    console.log("Bonus:        " + ((this.round === NUM_CATGRY && this.upperScore >= bonusMin) ? 25 : 0) + "<br/>");
    console.log("lowerScore:   " + this.getLowerScore() + "<br/>");
    console.log("Total points: " + this.getTotalScore() + "<br/>");
    //console.log("*****End of printFinalSC()*****<br/><br/>");
};


// Print one element in scores array
ScoreCard.prototype.getScoreIndex = function (i) {
    console.log("Hit getScoreIndex(). score[] = "+ this.scores[i]);
    return this.scores[i];
};


ScoreCard.prototype.getDice = function (i) {
    return this.dice[i];
};

// Print round
ScoreCard.prototype.getRound = function () {
    return this.round;
};


// Print upperScore
ScoreCard.prototype.getUpperScore = function () {
    return this.upperScore;
};


// Print upperScore
ScoreCard.prototype.getLowerScore = function () {
    return this.lowerScore;
};


// Print scores array. Each element represents 1 points category on ScoreCard
ScoreCard.prototype.printScoreCard = function () {

    for (var i = 0; i < NUM_CATGRY; i++) {
        console.log("["+i+"]   ");
        this.getScoreIndex(i);
    }
};


// Print bool isSelected[13]
ScoreCard.prototype.printIsSelected = function () {
    console.log("isSelected = { ");
    for (var i = 0; i < NUM_CATGRY; i++) {
        console.log(this.isSelected[i] + ", ");
    }
    console.log(" }<br/>");
};


// Print this.dice[5]
ScoreCard.prototype.printDice = function () {

    console.log("Hit printDice()");
    for (var i = 0; i < NUM_DICE; i++) {
        document.getElementById("dice-"+(i+1)).innerHTML = this.getDice(i);
        console.log("Dice[" +i+ "]="+this.getDice(i));
    }
    
};

// Global constants for ScoreCard Class
var NUM_DICE = 5;
var NUM_CATGRY = 13; // number of scoring categories

// ScoreCard object constructor. Public properties of ScoreCard class
function ScoreCard(name) {

    //console.log("Hit ScoreCard() Constructor");
    this.setFName(name);
    this.rnd = 1; //this.setRnd(0);
    this.upperScore = 0;
    this.lowerScore = 0;
    this.isCatgryPicked = [NUM_CATGRY]; // Stops categories from being overwritten or displayed twice
    this.scores = [NUM_CATGRY];     // points for each of 13 categories in scorecard
    this.dice = [NUM_DICE]; // ? Are we using this cuz we have a local one in play() or do we need to connect it with local in play()
    this.selectedDice = [];  // Create vector for the this.dice we're keeping for final points

    // Initialize array of Dice class object
    for (var i = 0; i < NUM_DICE; i++) {
        this.roll(i);//this.dice[i] = 0;
        //this.printDice(i); 
        //console.log("ScoreCard() dice["+i+"]="+this.dice[i]);
    }
    //this.printDice();

    // Initialize arrays
    for (var c = 0; c < NUM_CATGRY; c++) {
        this.scores[c] = -1;
        this.writeAScore(c); // Writes element to ScoreCard.html
        this.isCatgryPicked[c] = false;
    }
}
;


//************************************************************
//               Fill scorecard with possible points
//************************************************************
ScoreCard.prototype.fillScoreCard = function () {


    var NUM_DICE_SIDES = 6;
    var temp_scores = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    var counts = [0, 0, 0, 0, 0, 0];
    this.dice.sort(); // Sort array in ascending order  

    // Loops 5 times and is Accumulating how many dice are the same and their total pts
    for (var i = 0; i < NUM_DICE; i++) {
        var index = this.dice[i] - 1;
        counts[index]++;
        temp_scores[index] += this.dice[i];
        //console.log("index = " + index + "  this.dice[" + i + "] = " + this.dice[i]);
    }

    // Set & write possible points to scorecard's upper section
    for (var i = 0; i < NUM_DICE_SIDES; i++) {
        this.recordScore(i + 1, temp_scores[i]);
    }

    //  Set flags for checking Lower section of scorecard starts here 
    var three_of_a_kind = false;
    var four_of_a_kind = false;
    var full_house = false;
    var small_straight = false;
    var large_straight = false;
    var yahtzee = false;
    var chance = 0;

    // Check for Three and four of a kind
    for (var i = 0; i < NUM_DICE_SIDES; i++) {
        if (counts[i] >= 3) {
            three_of_a_kind = true;
            //console.log("three_of_a_kind = true");
            if (counts[i] >= 4) {
                four_of_a_kind = true;
                //console.log("four_of_a_kind = true");
                if (counts[i] === NUM_DICE) {
                    yahtzee = true;
                }
            }
        }
        chance += i + 1 * counts[i]; // Each die contributes its face value multiplied by its count to the chance score
    }

    // 3 or 4 of kind is true, then set pts in scores[] 
    this.recordScore(7, three_of_a_kind ? chance : 0); // Assuming score categories are 1-indexed
    this.recordScore(8, four_of_a_kind ? chance : 0);

    // Full house, then set pts in scores[]
    if ((counts.includes(2) && counts.includes(3)) || yahtzee) {
        full_house = true;
    }
    this.recordScore(9, full_house ? 25 : 0);

    // Small and Large straight
    for (var i = 0; i < 3; i++) {
        if (counts[i] && counts[i + 1] && counts[i + 2] && counts[i + 3]) {
            small_straight = true;
            if (counts[i + 4]) {
                large_straight = true;
                break;
            }
        }
    }

    // Small or Large straight, then set pts in scores[]
    this.recordScore(10, small_straight ? 30 : 0);
    this.recordScore(11, large_straight ? 40 : 0);

    // Yahtzee, then set pts in scores[]
    this.recordScore(12, yahtzee ? 50 : 0);

    // Chance set pts in scores[]
    this.recordScore(13, chance);
    this.writeTotals();
    //console.log("Hit fillScorecard().\nPoints Possible...[ " + this.scores + " ]\ndice =" + this.dice);
};


//************************************************************
//     Set scores in the possible points scorecard        
//************************************************************

ScoreCard.prototype.recordScore = function (category, score) {
    //console.log("Inside recordScore().  scorecard.round = " + this.getRnd());
    //console.log("scorecard.isCatgryPicked=[" + this.isCatgryPicked);

    var string1 = this.fName + "'s Possible ScoreCard ";
    document.getElementById('finalSCDiv').innerHTML = string1;

    var indx = category - 1; //ScoreCard's range [0,12]

    // if it's not last round & score hasn't already been picked, then set the scores array with possible points
    if (this.getRnd() >= 0 && this.getRnd() <= 12 && (this.isCatgryPicked[category - 1] === false)) {     
        this.scores[indx] = score;
        this.writeAScore(indx); // rewrite points on ScoreCard.html        
    }

    // if it is last round AND this category has NOT be picked, then set scores array with possible points
    else if (this.getRnd() > 12 && (this.isCatgryPicked[category - 1] === false)) {
        this.scores[indx] = score; // on the last round, it will set the unpicked category to zero instead of -1. Every category has to be picked.
        this.writeAScore(indx); // rewrite points on ScoreCard.html

    } else { // -1 sets this category to null value, so they can't choose it from possible scorecard
        this.scores[indx] = -1;
        this.writeAScore(indx); // rewrite points on ScoreCard.html
    }
};



//*****************************************************************
//             Keep this dice in selectedDice vector
//*****************************************************************
ScoreCard.prototype.pushThisDice = function (choice) {
    //choice -= 1;
    this.selectedDice.push(choice);
    console.log("      Hit  ScoreCard.pushThisDice().  this.selectedDice = " + this.selectedDice);
};



//*****************************************************************
//               Set Dice class array
//*****************************************************************
ScoreCard.prototype.reRoll = function () {

    console.log("Hit reRoll().  this.selectedDice = " + this.selectedDice);

    // Re-Roll Dice. loops through selectedDice vector, and checks which this.dice # to re-roll ?
    for (var j = 0; j < NUM_DICE; j++) {

        // https://www.w3schools.com/jsref/jsref_find.asp
        // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/find
        // syntax: array.find(function(currentValue, index, arr),thisValue)
        //var n = this.selectedDice.find(this.isFound(j), j);
        //console.log("Hit reRoll()...keeping dice" + (n));


        //if(this.selectedDice.find(this.selectedDice.begin(), this.selectedDice.end(), j) === this.selectedDice.end()) {

        //console.log("...Re-Rolling Dice"+j);
        this.roll(j); // re-roll this this.dice
        //}
    }
    this.dice.sort();
    //this.printDice();      // Write all dice to html
    this.writeDice();
    this.consoleLogDice();
};


//************************************************************
//           Called in reRoll()
//************************************************************
ScoreCard.prototype.isFound = function (indx) {
    console.log("   Hit isFound(). dice " + indx + " is in this.isCatgryPicked[ ]");
    //var i = (indx === isCatgryPicked[indx]) ? indx : undefined;
    return indx >= 0;
};


//************************************************************
//              Roll & set a single dice
//************************************************************
ScoreCard.prototype.roll = function (i) {
    this.dice[i] = (1 + (Math.floor(Math.random() * 6)));
};



//**********************************************************
//          console log all dice 
//**********************************************************
ScoreCard.prototype.consoleLogDice = function () {
    console.log("Hit consoleLogDice().   Rerolled Dice[ " + this.dice + " ]");
};



//************************************************************
//          Calculate totals for upper, lower scorecard sections            
//************************************************************

ScoreCard.prototype.setUpLowSums = function () {

    //console.log("Hit setUpLowSums()");
    // Calculate upper section total points
    var total = 0;
    for (var i = 0; i < 6; i++) {

        if (this.scores[i] >= 0) { // only add values over zero
            total += this.scores[i];
        }

        if (i === 5) { // last points category in upper section of scorecard
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
        if (i === 12) { // last points category in lower section of scorecard
            this.lowerScore = total;
            //alert("Hit i==12. lowerScore="+ this.lowerScore +" total="+total);
        }
    }
    //console.log("Hit setUpLowSums().  upperScore = " + this.upperScore + "  lowerScore = " + this.lowerScore);
};


//************************************************************
//          Add upper and lower sections of scorecard  
//      Check if upper section qualifies for bonus points          
//************************************************************

ScoreCard.prototype.getTotalScore = function () {

    var total = 0, bonus = 25;

    // if upper section is 63 or more than add 25 pts to total
    if (this.upperScore >= 63) {
        total += bonus;
    }
    total = this.upperScore + this.lowerScore;
    return total;
};




//************************************************************
//              Set bool wasPicked[13]
//************************************************************
ScoreCard.prototype.setWasPicked = function (i) {
    this.isCatgryPicked[i] = true;
    console.log("isCatgryPicked[" + i + "] = " + this.isCatgryPicked[i]);
};

ScoreCard.prototype.setRnd = function (r) {
    this.rnd = r;
    //console.log("Hit setRnd(). round = " + this.getRnd());
};

ScoreCard.prototype.increRnd = function () {
    this.rnd++;
    //console.log("Hit setRnd(). round = " + this.getRnd());
    this.setRnd();
};

ScoreCard.prototype.setFName = function (name) {
    this.fName = name;
};

ScoreCard.prototype.getSelectedDice = function () {
    console.log("      Hit  getSelectedDice().  selectedDice = " + this.selectedDice);
    //alert("      Hit  getSelectedDice().  selectedDice = " + this.selectedDice);
    return this.selectedDice;
};
ScoreCard.prototype.getScoreIndex = function (i) {
    console.log("Hit getScoreIndex(). score[] = " + this.scores[i]);
    return this.scores[i];
};

ScoreCard.prototype.getDice = function (i) {
    return this.dice[i];
};
ScoreCard.prototype.getDiceArr = function () {
    return this.dice;
};
ScoreCard.prototype.getRnd = function () {
    return this.rnd;
};

ScoreCard.prototype.getUpperScore = function () {
    return this.upperScore;
};

ScoreCard.prototype.getLowerScore = function () {
    return this.lowerScore;
};

//**********************************************************
//      Prints this player's final ScoreCard Class members
//**********************************************************
ScoreCard.prototype.printFinalSC = function (name) {
    var string1 = name + "'s Final ScoreCard ";
    document.getElementById('finalSCDiv').innerHTML = string1;
    this.writeScoreCard();
    this.writeTotals();
    console.log(this.scores);
};

ScoreCard.prototype.writeTotals = function () {
    var bonusMin = 63;
    var bonus = (this.getUpperScore() >= bonusMin) ? 25 : 0;
    this.setUpLowSums();

    document.getElementById('catgy13').innerHTML = this.getUpperScore();
    document.getElementById('catgy14').innerHTML = bonus;
    document.getElementById('catgy15').innerHTML = this.getLowerScore();
    document.getElementById('catgy16').innerHTML = this.getTotalScore();
    //console.log("Hit writeTotals().  scores[ "+this.scores+" ]\n"  
    //+ "upperScore="+this.getUpperScore() +"  lowerScore="+this.getLowerScore()+" total="+this.getTotalScore());

};

//************************************************************
// Print scores array. Each element represents 1 points category on ScoreCard
//************************************************************
ScoreCard.prototype.writeScoreCard = function () {
    //console.log("Hit writeScoreCard(). scores[ "+ this.scores+" ]"); 
    for (var i = 0; i < NUM_CATGRY; i++) {
        this.writeAScore(i); // Writes element to ScoreCard.html
    }
};

ScoreCard.prototype.writeAScore = function (indx) {
    //console.log("Hit writeAScore()");    
    document.getElementById('catgy' + indx).innerHTML = this.scores[indx]; // display the value on the button   
};


ScoreCard.prototype.writeDice = function () {
    //console.log("Hit writeScoreCard(). scores[ "+ this.scores+" ]"); 
    for (var i = 0; i < NUM_DICE; i++) {
        var dice = document.getElementById('dice' + i);
        dice.setAttribute('value', this.getDice(i));
        dice.innerHTML = this.getDice(i); // display the value on the button   
    }
};
// Global constants for ScoreCard Class
var NUM_DICE = 5;
var NUM_CATGRY = 13; // number of scoring categories
            
function ScoreCard() {
  
    // Public properties of ScoreCard class
    //alert("Begin of ScoreCard()");
    this.round = 0;
    this.upperScore = 0;
    this.lowerScore = 0;
    this.isSelected = [NUM_CATGRY]; // Stops categories from being overwritten or displayed twice
    this.scores = [NUM_CATGRY];     // points for each of 13 categories in scorecard
    this.dice = [NUM_DICE]; // ? Are we using this cuz we have a local one in play() or do we need to connect it with local in play()
    //vector<int> selected;  // Create vector for the dice we're keeping for final points
    
    // Initialize arrays
    for (var i = 0; i < NUM_CATGRY; i++) {
        this.scores[i] = -1;
        this.isSelected[i] = false;
    }


    // Initialize array of Dice class object
    for (var i = 0; i < NUM_DICE; i++){          
        this.dice[i] = 0;
    }
    //alert("End of ScoreCard()");
};




// Roll a single dice
 ScoreCard.prototype.roll=function(){
    this.value = (1 + (Math.floor(Math.random() * 6)));
    alert("Hit roll(). dice = " + value);
 };


// Set which round it is
ScoreCard.prototype.setRound=function(r){
    //alert("Hit setRound()<br/>");
    this.round = r;
};


//*****************************************************************
//               Set Dice class array
//*****************************************************************
ScoreCard.prototype.setDice=function(){
    
    // Re-Roll Dice. loops through selected vector, and checks which dice # to re-roll ?
    for (var j = 0; j < NUM_DICE; j++) {                                
        //if (find(selected.begin(), selected.end(), j) == selected.end()) {
            this.dice[j].roll(); // re-roll this dice
        //}
    }                    

    this.printDice();    
};


//************************************************************
//          Add upper and lower sections of scorecard  
//          Add bonus if upper section is 63 or more          
//************************************************************
ScoreCard.prototype.getTotalScore=function() {
    
    var total = 0;    
    for (var i = 0; i < NUM_CATGRY; i++) {        
        if (scores[i] >= 0) {
            
            // if upper section is 63 or more than add 25 pts to total
            if(i===5 && total >= 63){ total +=25; } 
            total += scores[i];
        }
    }
    return total;
};


// Prints this player's final ScoreCard Class members
ScoreCard.prototype.printFinalSC=function(){
    
    //alert("Hit toString()");  
    this.getRound();
    this.getUpperScore();
    this.getLowerScore();       
   
    // Prints possible scorecard points int scores[13]
    document.write("scores = { ");
    for (var i = 0; i < NUM_CATGRY; i++) {
        document.write(this.scores[i] + ", ");
    }
    document.write(" }<br/>");
    
    // Print bool isSelected[13]
    this.getIsSelected();
    
    // Print int dice[5]
    this.printDice();
};


// Print one element in scores array
ScoreCard.prototype.getScoreIndex=function(i){
    document.write(this.scores[i]);
    //return this.scores[i];
};


// Print round
ScoreCard.prototype.getRound=function(){
    document.write("round: " + this.round +"<br/>");
};


// Print upperScore
ScoreCard.prototype.getUpperScore=function(){
    document.write("upperScore: " + this.upperScore +"<br/>");
};


// Print upperScore
ScoreCard.prototype.getLowerScore=function(){
    document.write("lowerScore: " + this.lowerScore +"<br/>");
};


// Print scores array. Each element represents 1 points category on ScoreCard
ScoreCard.prototype.printScoreCard=function(){
    for (var i = 0; i < NUM_CATGRY; i++) {
        document.write("["+(i+1) + "]   ");
        this.getScoreIndex(i);
        document.write("<br/>");
    }
     document.write("<br/><br/>");
};


// Print bool isSelected[13]
ScoreCard.prototype.getIsSelected=function(){
    document.write("isSelected = { ");
    for (var i = 0; i < NUM_CATGRY; i++) {
        document.write(this.isSelected[i] + ", ");
    }
    document.write(" }<br/>");
};


// Print dice[5]
ScoreCard.prototype.printDice=function(){
    document.write("Dice values = {");
    for (var i = 0; i < NUM_DICE; i++){
        document.write(this.dice[i] + ", ");
    }
    document.write(" }<br/><br/>");
};

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


//To String function of the ScoreCard Class
ScoreCard.prototype.toString=function(){
    
    //alert("Hit toString()");  
    document.write("round: " + this.round +"<br/>");
    document.write("upperScore: " + this.upperScore +"<br/>");
    document.write("lowerScore: " + this.lowerScore +"<br/>");
   
    document.write("scores = { ");
    for (var i = 0; i < NUM_CATGRY; i++) {
        document.write(this.scores[i] + ", ");
    }
    document.write(" }<br/>");
    
    document.write("isSelected = { ")
    for (var i = 0; i < NUM_CATGRY; i++) {
        document.write(this.isSelected[i] + ", ");
    }
    document.write(" }<br/>");
    
    document.write("dice = {");
    for (var i = 0; i < NUM_DICE; i++){
        document.write(this.dice[i] + ", ");
    }
    document.write(" }<br/><br/>");
};


 ScoreCard.prototype.roll=function(){
    //alert("Hit roll()"); 
    this.value = (1 + (Math.floor(Math.random() * 6)));
    alert("Hit roll(). dice = " + value);
 };


//*****************************************************************
//               Set Dice class array
//*****************************************************************
//ScoreCard.prototype.setDice=function(){
//    
//     // Re-Roll Dice. loops through selected vector, and checks which dice # to re-roll ?
//        for (var j = 0; j < NUM_DICE; j++) {                                
////            if (find(selected.begin(), selected.end(), j) == selected.end()) {
////                dice[j].roll(); // re-roll this dice
////            }
//        }                    
//
//        //printDice(dice);
//        
//        // Setting vararray with Dice class object
//        for (var i = 0; i < NUM_DICE; i++) {
//            //diceArr[i] = dice[i].getValue();
//        }
//};

//*****************************************************************
//              Print Dice class object's values
//*****************************************************************
//ScoreCard.prototype.printDice=function(Dice dice[]) const {
    
//    cout << "\n\tDice values:" << endl;
//    for (var j = 0; j < NUM_DICE; j++) {
//        cout << setw(4) << dice[j].getValue() << "  ";
//    }
//    
//    cout << "\n";
//    
//    for (var j = 0; j < NUM_DICE; j++) {
//        cout << "Dice" << j + 1 << " ";
//    }
//    cout << "\n" << string(40, '-') << endl << endl;
 
//};



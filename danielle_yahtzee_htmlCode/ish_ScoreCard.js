/* 
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/ClientSide/javascript.js to edit this template
 */
const NUM_DICE = 5;

ScoreCard.prototype.fillScoreCard = function () {
    var NUM_DICE_SIDES = 6;
    var temp_scores = [0, 0, 0, 0, 0, 0];   
    var counts = [0, 0, 0, 0, 0, 0];

    this.dice.sort();   

    for (var i = 0; i < NUM_DICE; i++) {
        var index = this.dice[i] - 1;
        counts[index]++;                     
        temp_scores[index] += this.dice[i]; 
    }

    for (var i = 0; i < NUM_DICE_SIDES; i++) {
        this.recordScore(i + 1, temp_scores[i]);
    }

    var three_of_a_kind = false;
    var four_of_a_kind = false;
    var full_house = false;
    var small_straight = false;
    var large_straight = false;
    var yahtzee = false;
    var chance = 0;
    
    for (var i = 0; i < NUM_DICE_SIDES; i++) {
        if (counts[i] >= 3) {
            three_of_a_kind = true;
            if (counts[i] >= 4) {
                four_of_a_kind = true;
                if (counts[i] === NUM_DICE) {
                    yahtzee = true;
                }
            }
        }
        chance += i+1 * counts[i]; // Each die contributes its face value multiplied by its count to the chance score
    }

    this.recordScore(7, three_of_a_kind ? chance : 0); // Assuming score categories are 1-indexed
    this.recordScore(8, four_of_a_kind ? chance : 0);
    
    // Full house
    if ((counts.includes(2) && counts.includes(3)) || yahtzee) {
        full_house = true;
    }
    this.recordScore(9, full_house ? 25 : 0);
    
    // Small and Large straight
    for (var i = 0; i < 3; i++) {
        if (counts[i] && counts[i+1] && counts[i+2] && counts[i+3]) {
            small_straight = true;
            if (counts[i+4]) {
                large_straight = true;
                break;
            }
        }
    }
    this.recordScore(10, small_straight ? 30 : 0);
    this.recordScore(11, large_straight ? 40 : 0);
    
    // Yahtzee
    this.recordScore(12, yahtzee ? 50 : 0);
    
    // Chance
    this.recordScore(13, chance);
};

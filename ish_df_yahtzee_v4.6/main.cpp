/* File:   main.cpp
 * Author: Ismael
 * Created on April 14, 2023, 8:18 PM
*/

/* 
v4.5
 * I reorganized the flow of play().
 * Created prntRound() & rules() to clean up play()
 * Created a 2nd instance of ScoreCard to hold the player's actual scores.
 * Created setFinalSC() and passed scorecard to it.
 * Fixed BUG with numRolls by switching if with a while loop.
 * Added a conditional if numRolls==3, then force switch case 2 else displayOptions();
 * Added a pause(), so it makes the game more readable between rolls
 * 
 * 
 v4.6
 * Created bool isSelected[] to stop already selected categories from being
   displayed in possible points scoreboard. Used it inside of recordScore().
 * Reset isSelected() flags in setFinalSC() to stop categories from
   being overwrite.
 
  
 To Do:
 * Add updated Yahtzee classes to Admin & User Classes.
 * Make sure it runs with 2 players
 */
#include <iostream>
#include "Yahtzee.h"

using namespace std;
int main() {
    
    // random numeber generator
    srand(static_cast<unsigned int>(time(0))); 
    Yahtzee game;
    game.play();
    return 0;
}
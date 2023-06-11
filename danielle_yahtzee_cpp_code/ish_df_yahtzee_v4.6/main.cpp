/* File:   main.cpp
 * Author: Ismael
 * Created on April 14, 2023, 8:18 PM
 * Purpose:  ish_df_yahtzee_v4.6

 v4.6
 * Created bool isSelected[] to stop already selected categories from being
   displayed in possible points scoreboard. Used it inside of recordScore().
 * Reset isSelected() flags in setFinalSC() to stop categories from
   being overwrite.
 * Changed play() to return a bool and accepts a reference variable,
   that represents the player's current high Score.
   If player 1 is winner, then return true;
   If player 1 is winner AND their current score is larger than their high score, then
   reassign highScore's value.
  
 To Do:
 * Add updated Yahtzee classes to Admin & User Classes.
 * Make sure it runs with 2 players
 */
#include <iostream>
#include "Yahtzee.h"

using namespace std;
int main() {
    
    // random number generator
    srand(static_cast<unsigned int>(time(0))); 
    
    Yahtzee game1;
    int highScore = 0;
    
    if(game1.play(highScore)) {                         
        cout << "\nNew High Score of " << highScore << "!\n";         
        cout << "\nUpdating & reading binary....";
      
    }  
    return 0;
}
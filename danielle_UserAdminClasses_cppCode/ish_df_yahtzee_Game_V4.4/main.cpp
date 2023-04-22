/* File:   main.cpp
 * Author: Ismael
 * Created on March 23, 2023, 4:46 PM
 * Purpose: ish_df_yahtzee_Game_V4.4

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

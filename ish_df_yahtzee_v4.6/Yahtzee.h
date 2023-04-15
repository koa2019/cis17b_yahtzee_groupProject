/* File:   Yahtzee.h
 * Author: error
 * Created on April 9, 2023, 4:59 PM
*/

#ifndef YAHTZEE_H
#define YAHTZEE_H
#include "Dice.h"

class Yahtzee {
    
private:
    
    static const int NUM_DICE = 5;
    Dice dice[NUM_DICE];    // Aggregates instance of Dice Class
    int diceArr[NUM_DICE];  // ? do we need this. we have a local one in play()
    int score;
    
public:
    
    Yahtzee();  // Default Constructor
    
    // Mutators
    void play();
    
    // Accessors
    void getRules(); 
    void prntRound(int);
    void pause(char ch='c');
    void displayOptions(int &);
};
#endif /* YAHTZEE_H */


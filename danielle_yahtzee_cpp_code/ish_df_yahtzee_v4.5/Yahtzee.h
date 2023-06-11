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
    Dice dice[NUM_DICE];
    int diceArr[NUM_DICE];
    void displayOptions(int &);
    int highscore;
    
public:
    Yahtzee();
    void play();
    void rules();
    void prntRound(int);
    void pause(char ch='c');
};
#endif /* YAHTZEE_H */


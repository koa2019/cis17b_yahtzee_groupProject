/* File:   Yahtzee.h
 * Author: error
 * Created on April 9, 2023, 4:59 PM
*/

#ifndef YAHTZEE_H
#define YAHTZEE_H
#include "Dice.h" // aggregates instance of Dice class
#include "User.h" // aggregates instance of User class

class Yahtzee {
private:
    static const int NUM_DICE = 5;
    Dice dice[NUM_DICE];
    int diceArr[NUM_DICE];
    void displayOptions();
    int selectCategory();
    int highscore;
    User player;
    
public:
    Yahtzee();
    bool play(User &);
};
#endif /* YAHTZEE_H */


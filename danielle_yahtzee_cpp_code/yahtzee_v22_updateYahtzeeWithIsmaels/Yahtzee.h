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
    
    static const int NUM_DICE = 5;  // how do we create global const in class without static?
    int diceArr[NUM_DICE]; // ? Are we using this cuz we have a local one in play() or do we need to connect it with local in play()
    Dice dice[NUM_DICE];  // Aggregates instance of Dice Class
    User player;          // Aggregates instance of User Class
    
public:
    
    Yahtzee();  // Default Constructor
    
    // Mutators
    bool play(User &);
   
    // Accessors
    void getRules(); 
    void prntRound(int);
    void pause(char ch='c');
    void displayOptions(int &);
};
#endif /* YAHTZEE_H */


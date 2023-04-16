/* File:   Yahtzee.h
 * Author: error
 * Created on April 9, 2023, 4:59 PM
*/

#ifndef YAHTZEE_H
#define YAHTZEE_H
#include "Dice.h"         // aggregates Dice class
#include "ScoreCard.h"   // aggregates ScoreCard class
#include "User.h"       // aggregates User class

class Yahtzee {
    
private:
    static const int NUM_DICE = 5;
    int nPlayer;
    int numRounds;
    int *indx = nullptr;
    User **player = nullptr;   // Aggregates instance of User Class. Array of User's
    ScoreCard scorecard[2];   // Aggregates instance of ScoreCard class
    ScoreCard finalSC[2];     // Aggregates instance of ScoreCard class
    
    int diceArr[NUM_DICE]; // ? Are we using this cuz we have a local one in play() or do we need to connect it with local in play()
    Dice dice[NUM_DICE];  // Aggregates instance of Dice Class
    
public:
    
    Yahtzee();  // Default Constructor
    ~Yahtzee(){ cout << "\nAdd code to Destroy **player in Yahtzee\n"; }

    // Mutators
    bool getGame(User &);
    void getNPlayer();
    void play(int i,int);
    
    
    // Accessors
    void getRules(); 
    void prntRound(int);
    void pause(char ch='c');
    void displayOptions(int &);
    //void getPlay(int i, int rnd) { play(i,rnd); }
};
#endif /* YAHTZEE_H */


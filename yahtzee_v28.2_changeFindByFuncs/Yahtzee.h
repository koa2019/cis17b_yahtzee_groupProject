/* File:   Yahtzee.h
 * Author: error
 * Created on April 9, 2023, 4:59 PM
*/

#ifndef YAHTZEE_H
#define YAHTZEE_H
#include "Dice.h"         // aggregates Dice class
#include "ScoreCard.h"   // aggregates ScoreCard class
#include "User.h"       // aggregates User class

// Global constants for Yahtzee Class
const int MINSIZE = 2;
const int MAXRND = 2;
const int MAXROLLS = 3;

class Yahtzee {
    
private:
        
    bool p1Winner;        // does user winner and have new high score
    int nPlayer;         // Player inputs how many players
    int *indx = nullptr;
    User **player = nullptr;   // Aggregates instance of User Class. Array of User's
    ScoreCard scorecard[MINSIZE];   // Aggregates instance of ScoreCard class
    ScoreCard finalSC[MINSIZE];     // Aggregates instance of ScoreCard class
      
public:
    
    Yahtzee(); // Default Constructor
    ~Yahtzee(){ 
        //cout << "\nAdd code to Destroy **player in Yahtzee\n"; 
        delete [] player; 
    }

    // Mutators
    bool startGame(User &,const long);
    void play(int i,int &);
    void setNPlayer();
    void setP1Winner(ScoreCard [], string []);
    bool isNewHiScore(User &,const long);
    void selectDice(int);
    void selectCategory(int,string,int);
    
    // Accessors
    void getRules(); 
    void prntRound(int);
    void pause(char ch='c');
    void displayOptions(int &);    
};
#endif /* YAHTZEE_H */


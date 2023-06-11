/* File:   ScoreCard.h
 * Author: DanYell
 * Created on April 14, 2023, 9:29 PM
*/

#ifndef SCORECARD_H
#define SCORECARD_H
#include<vector>
#include <bits/stdc++.h>  // vectors
#include"Dice.h"
using namespace std;

const int NUM_DICE = 5;
const int NUM_CATGRY = 13; // number of scoring categories

class ScoreCard {
    
private:
    
    bool isSelected[NUM_CATGRY]; // Stops categories from being overwritten or displayed twice
    int scores[NUM_CATGRY];     // points for each of 13 categories in scorecard
    int round;         // Identifies which round player is currently in
    int upperScore;   // Holds total points for upper scorecard section
    int lowerScore;   // Holds total points for lower scorecard section
    Dice dice[NUM_DICE];  // Aggregates instance of Dice Class
    int diceArr[NUM_DICE]; // ? Are we using this cuz we have a local one in play() or do we need to connect it with local in play()
    vector<int> selected;  // Create vector for the dice we're keeping for final points
    
public:
    
    ScoreCard(); // Default Constructor
    
    // Mutators
    void recordScore(int category, int score); //category on scorecard
    void fillScoreCard();
    void get_isSelected() const;    
    int  getTotalScore();
    void getUpLowSums();
    void setFinalSC(ScoreCard &);
    void setRound(int r){round=r;}
    void setDice(); 
    void pushThisDice(int choice){  selected.push_back(choice - 1); }
    
    // Accessors
    void printScoreCard() const;
    void printFinalSC(string name="Player");
    void printDice(Dice []) const;
    int getDiceVal(int choice){ return dice[choice - 1].getValue(); }
    
};
#endif /* SCORECARD_H */
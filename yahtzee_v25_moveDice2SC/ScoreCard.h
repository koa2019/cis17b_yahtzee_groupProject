/* File:   ScoreCard.h
 * Author: DanYell
 * Created on April 14, 2023, 9:29 PM
*/

#ifndef SCORECARD_H
#define SCORECARD_H
#include"Dice.h"
#include<vector>
using namespace std;

class ScoreCard {
    
private:
    
    bool isSelected[13]; // Stops categories from being overwritten or displayed twice
    int scores[13];     // points for each of 13 categories in scorecard
    int round;         // Identifies which round player is currently in
    int upperScore;   // Holds total points for upper scorecard section
    int lowerScore;   // Holds total points for lower scorecard section
    
public:
    
    ScoreCard(); // Default Constructor
    
    // Mutators
    void recordScore(int category, int score); //category on scorecard
    void fillScoreCard(int diceArr[]);
    void fillScoreCard(Dice diceArr[]);
    void setFinalSC(ScoreCard &,int []);
    void setRound(int r){round=r;}
     
    // Accessors
    void printScoreCard() const;
    void printFinalSC(string name="Player");
    void get_isSelected() const;    
    int  getTotalScore();
    void getUpLowSums();
};
#endif /* SCORECARD_H */
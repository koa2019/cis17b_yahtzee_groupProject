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
    int scores[13];
    int upScore;
    int lowSum;
    int round;
    
public:
    
    ScoreCard(); // Default Constructor
    
    // Mutators
    void recordScore(int category, int score); //category on scorecard
    void fillScoreCard(int diceArr[]);
    void setFinalSC(ScoreCard &,int []);
    //void setFinalSC(ScoreCard *,int, int []);
    void setRound(int r){round=r;}
     
     
    // Accessors
    void printScoreCard() const;
    void printFinalSC(string name="Player");
    void get_isSelected() const;    
    int  getTotalScore();
    void getUpLowSums();
};
#endif /* SCORECARD_H */
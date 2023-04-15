/* File:   ScoreCard.h
 * Author: DanYell
 *
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
    
public:
    
    ScoreCard(); // Default Constructor
    
    // Mutators
    void recordScore(int category, int score); //category meaning the section
    void fillScoreCard(int diceArr[],bool clearance);
    void setFinalSC(ScoreCard &,int [] );
    
    // Accessors
    void printScoreCard() const;
    void getFinalSC();
    void get_isSelected() const;    
    int  getTotalScore();
};
#endif /* SCORECARD_H */


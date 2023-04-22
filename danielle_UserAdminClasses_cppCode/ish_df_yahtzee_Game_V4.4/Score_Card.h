/* File:   Score_Card.h
 * Author: Ismael
 * Created on March 23, 2023, 5:47 PM
*/

#ifndef SCORE_CARD_H
#define SCORE_CARD_H
#include"Dice.h"
#include<vector>
using namespace std;

class ScoreCard{
private:
    bool isSelected[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    int scores[13];
    int save13;
    int total; // total points from upper and lower sections
public:
    ScoreCard();
    void printScoreCard();
    void recordScore(int category, int score); //category meaning the section
    int getTotalScore();
    void fillScoreCard(int diceArr[],bool clearance);
    void setFinalSC(ScoreCard &,int [],bool );
};
#endif /* SCORE_CARD_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Score_Card.h"
#include "Dice.h"

using namespace std;

ScoreCard::ScoreCard() {
    for (int i = 0; i < 13; i++) {
        scores[i] = -1;
    }
}



void ScoreCard::printScoreCard() {
    cout << "Scorecard:\n";
    cout << "------------------------------\n";
    cout << "| Category          | Score   |\n";
    cout << "------------------------------\n";
    cout << left << setw(20) << "| 1. Ones" << " | " << right << setw(6) << (scores[0] >= 0 ? to_string(scores[0]) : "-") << " |\n";
    cout << left << setw(20) << "| 2. Twos" << " | " << right << setw(6) << (scores[1] >= 0 ? to_string(scores[1]) : "-") << " |\n";
    cout << left << setw(20) << "| 3. Threes" << " | " << right << setw(6) << (scores[2] >= 0 ? to_string(scores[2]) : "-") << " |\n";
    cout << left << setw(20) << "| 4. Fours" << " | " << right << setw(6) << (scores[3] >= 0 ? to_string(scores[3]) : "-") << " |\n";
    cout << left << setw(20) << "| 5. Fives" << " | " << right << setw(6) << (scores[4] >= 0 ? to_string(scores[4]) : "-") << " |\n";
    cout << left << setw(20) << "| 6. Sixes" << " | " << right << setw(6) << (scores[5] >= 0 ? to_string(scores[5]) : "-") << " |\n";
    cout << "------------------------------\n";
    cout << left << setw(20) << "| 7. Three of a Kind" << " | " << right << setw(6) << (scores[6] >= 0 ? to_string(scores[6]) : "-") << " |\n";
    cout << left << setw(20) << "| 8. Four of a Kind" << " | " << right << setw(6) << (scores[7] >= 0 ? to_string(scores[7]) : "-") << " |\n";
    cout << left << setw(20) << "| 9. Full House" << " | " << right << setw(6) << (scores[8] >= 0 ? to_string(scores[8]) : "-") << " |\n";
    cout << left << setw(20) << "| 10. Small Straight" << " | " << right << setw(6) << (scores[9] >= 0 ? to_string(scores[9]) : "-") << " |\n";
    cout << left << setw(20) << "| 11. Large Straight" << " | " << right << setw(6) << (scores[10] >= 0 ? to_string(scores[10]) : "-") << " |\n";
    cout << left << setw(20) << "| 12. Yahtzee" << " | " << right << setw(6) << (scores[11] >= 0 ? to_string(scores[11]) : "-") << " |\n";
    cout << left << setw(20) << "| 13. Chance" << " | " << right << setw(6) << (scores[12] >= 0 ? to_string(scores[12]) : "-") << " |\n";
    cout << "------------------------------\n";
    cout << "Total Score: " << getTotalScore() << "\n";
}

void ScoreCard::recordScore(int category, int score) {
    scores[category-1] = score;
}



int ScoreCard::getTotalScore() {
    int total = 0;
    for (int i = 0; i < 13; i++) {
        if (scores[i] >= 0) {
            total += scores[i];
        }
    }
    return total;
}


void ScoreCard::fillScoreCard(int diceArr[]){
    int NUM_DICE = 5;
    int score1=0,
        score2=0,
        score3=0,
        score4=0,
        score5=0,
        score6=0,
        score7=0,
        score8=0,
        chance=0;
    bool three_of_a_kind = false;
    bool four_of_a_kind = false;
    bool full_house = false;
    bool small_straight = false;
    bool large_straight = false;
    bool isYahtzee = true;
    
    
    
    
    //sorting the array
    sort(diceArr, diceArr+5);
    //checking the dice values to add the correct points to the score card
    for(int i=0; i<5;i++){
        if(diceArr[i]==1)score1+=1;
        if(diceArr[i]==2)score2+=2;
        if(diceArr[i]==3)score3+=3;
        if(diceArr[i]==4)score4+=4;
        if(diceArr[i]==5)score5+=5;
        if(diceArr[i]==6)score6+=6;
    }
    
    recordScore(1,score1);
    recordScore(2,score2);
    recordScore(3,score3);
    recordScore(4,score4);
    recordScore(5,score5);
    recordScore(6,score6);
    
    //checking for three of a kind, 4 of a kind, full house, small straight, large straight, yahtzee, or chance
    //three of a kind 
    for (int i = 0; i < 3; i++){
        int count = 1;
        for (int j = i+1; j < 5; j++){
            if (diceArr[i] == diceArr[j])
            count++;
        }
        if (count >= 3){
            three_of_a_kind = true;
        }
    }
    // Output the result
    if(three_of_a_kind){
        for(int i=0; i<5;i++){
            score7 += diceArr[i];
        }
        recordScore(7,score7);
    }
    if(!three_of_a_kind){
        recordScore(7,0);
    }
    
    //four of a kind
    for (int i = 0; i < 2; i++){
        int count = 1;
        for (int j = i+1; j < 5; j++){
            if (diceArr[i] == diceArr[j]){
                count++;
            }
            if (count >= 4){
                four_of_a_kind = true;
            }
        }
    }
    // Output the result
    if(four_of_a_kind){
        for(int i=0; i<5;i++){
            score8 += diceArr[i];
        }
        recordScore(8,score8);
    }
    if(!four_of_a_kind){
        recordScore(8,0);
    }
    
    //full house
    if (diceArr[0] == diceArr[1] && diceArr[1] == diceArr[2] && diceArr[3] == diceArr[4]) {
        full_house = true;
    }
    else if (diceArr[0] == diceArr[1] && diceArr[2] == diceArr[3] && diceArr[3] == diceArr[4]) {
        full_house = true;
    }
    if(full_house){
        recordScore(9,25);
    }
    else{
        recordScore(9,0);
    }
    
    //small straight
    for (int i = 0; i < 2; i++){
        if (diceArr[i+1] == diceArr[i]+1 && diceArr[i+2] == diceArr[i]+2 && diceArr[i+3] == diceArr[i]+3){
            small_straight = true;
        }
    }
    if(small_straight){
        recordScore(10,30);
    }
    else{
        recordScore(10,0);
    }
    
    //large straight
    if (diceArr[0] == 1 && diceArr[1] == 2 && diceArr[2] == 3 && diceArr[3] == 4 && diceArr[4] == 5) {
      large_straight = true;
    }
    else if (diceArr[0] == 2 && diceArr[1] == 3 && diceArr[2] == 4 && diceArr[3] == 5 && diceArr[4] == 6) {
      large_straight = true;
    }
    if(large_straight){
        recordScore(11,40);
    }
    else{
        recordScore(11,0);
    }
    
    //yahtzee
    for (int i = 1; i < 5; i++) {
      if (diceArr[i] != diceArr[0]) {
         isYahtzee = false;
      }
    }
    if(isYahtzee){
        recordScore(12,50);
    }
    else{
        recordScore(12,0);
    }
    
    //chance
    for(int i=0;i<5;i++){
        chance+=diceArr[i];
    }
    recordScore(13,chance);
}

   
   



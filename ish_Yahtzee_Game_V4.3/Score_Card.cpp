/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
#include "Score_Card.h"
#include "Dice.h"

using namespace std;

ScoreCard::ScoreCard() {
    for (int i = 0; i < 13; i++) {
        scores[i] = -1;
    }
    
    save13 = 0;

}



void ScoreCard::printScoreCard() {
    cout << endl;
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
    cout << endl;
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


void ScoreCard::fillScoreCard(int diceArr[], bool clearance) {
    int num_dice = 5;
    vector<int> scores(13, 0);
    vector<int> counts(6, 0);
    int choice =0;
    
    
    if(clearance){
        //choices
        cout << endl;
        cout << "Select a category:" << endl;
        cout << " 1: Ones" << endl;
        cout << " 2: Twos" << endl;
        cout << " 3: Threes" << endl;
        cout << " 4: Fours" << endl;
        cout << " 5: Fives" << endl;
        cout << " 6: Sixes" << endl;
        cout << " 7: Three-of-a-kind" << endl;
        cout << " 8: Four-of-a-kind" << endl;
        cout << " 9: Full house" << endl;
        cout << "10: Small straight" << endl;
        cout << "11: Large straight" << endl;
        cout << "12: Yahtzee" << endl;
        cout << "13: Chance" << endl;

        cin >> choice;

        // Check if the choice is valid and not already used.
        // You need to implement the logic to store the used categories and check for valid scoring.
        while (choice < 1 || choice > 13) {
            cout << "Invalid choice. Please select a category between 1 and 13." << endl;
            cin >> choice;
        }

        // Calculate the score for the chosen category and store it.
        // You need to implement the logic to calculate and store the scores for each category.
        cout << "Category " << choice << " selected." << endl;
        cout << endl;
    }
    
    
    sort(diceArr, diceArr + num_dice);

    for (int i = 0; i < num_dice; i++) {
        counts[diceArr[i] - 1]++;
        scores[diceArr[i] - 1] += diceArr[i];
    }

    for (int i = 0; i < 6; i++) {
        recordScore(i + 1, scores[i]);
    }

    bool three_of_a_kind = false;
    bool four_of_a_kind = false;
    bool full_house = false;
    bool small_straight = false;
    bool large_straight = false;
    bool isYahtzee = true;

    // Three and four of a kind
    for (int count : counts) {
        if (count >= 3) {
            three_of_a_kind = true;
            if (count >= 4) {
                four_of_a_kind = true;
                break;
            }
        }
    }

    recordScore(7, three_of_a_kind ? accumulate(diceArr, diceArr + num_dice, 0) : 0);
    recordScore(8, four_of_a_kind ? accumulate(diceArr, diceArr + num_dice, 0) : 0);

    // Full house
    full_house = (counts[0] == 3 && counts[1] == 2) || (counts[0] == 2 && counts[1] == 3);
    recordScore(9, full_house ? 25 : 0);

    // Small and large straight
    for (int i = 0; i < 2; i++) {
        if (counts[i] && counts[i + 1] && counts[i + 2] && counts[i + 3]) {
            small_straight = true;
            if (counts[i + 4]) {
                large_straight = true;
                break;
            }
        }
    }

    recordScore(10, small_straight ? 30 : 0);
    recordScore(11, large_straight ? 40 : 0);

    // Yahtzee
    isYahtzee = all_of(counts.begin(), counts.end(), [&](int count) { return count == num_dice; });
    recordScore(12, isYahtzee ? 50 : 0);

    // Chance
    recordScore(13, accumulate(diceArr, diceArr + num_dice, 0));
    
    
    //saves the value if choice 13 is picked
    if(choice == 13){
        save13 = accumulate(diceArr, diceArr + num_dice, 0);
        recordScore(13,save13);
    }
    
    //recordScore(13,save13);
}
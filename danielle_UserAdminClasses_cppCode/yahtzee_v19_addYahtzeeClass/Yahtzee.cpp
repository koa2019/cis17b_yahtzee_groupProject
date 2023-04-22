/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>

#include "Yahtzee.h"
#include "Dice.h"
#include "Score_Card.h"

using namespace std;

Yahtzee::Yahtzee() {
    highscore = 0;
}


void Yahtzee::play() {
    ScoreCard scorecard;
    Dice dice[NUM_DICE];
    int numRolls = 3;
    int diceArr[NUM_DICE];
    int resp;
    char resp1;

    
    do {
        
        
            vector<int> selected;

            for (int currRoll = 0; currRoll < numRolls; currRoll++) {
                // Roll the dice
                for (int j = 0; j < NUM_DICE; j++) {
                    if (find( selected.begin(), selected.end(), j) == selected.end()) {
                        dice[j].roll();
                    }
                }

                // Display the dice values
                cout << endl;
                cout << "Dice values:" << endl;

                for (int j = 0; j < NUM_DICE; j++) {
                    cout << setw(4) << dice[j].getValue() << "  ";
                }

                cout << endl;
                for (int j = 0; j < NUM_DICE; j++) {
                    cout << "Dice" << j + 1 << " ";
                }
                cout << endl << endl;

                // Store the dice values in an array
                for (int i = 0; i < NUM_DICE; i++) {
                    diceArr[i] = dice[i].getValue();
                }

                if (currRoll < numRolls - 1) {
                    cout << "Enter the dice numbers (1-5) to keep, separated by spaces, or -1 to stop: ";
                    int choice;
                    cin >> choice;

                    while (choice != -1) {
                        if (choice < 1 || choice > NUM_DICE) {
                            cout << "Invalid choice. Please enter a number between 1 and " << NUM_DICE << ", or -1 to stop: ";
                        } else {
                            selected.push_back(choice - 1);
                            cout << "Keeping Dice" << choice << ": " << dice[choice - 1].getValue() << endl;
                        }
                        cin >> choice;
                    }
                }
            }

            // Print selected dice
            cout << endl;
            cout << "Selected dice: " << endl;


            for (int idx : selected) {
                cout << setw(4) << dice[idx].getValue() << "  ";
            }

            cout << endl;
            for (int idx : selected) {
                cout << "Dice" << idx + 1 << " ";
            }
            cout << endl << endl;


            displayOptions();
            cin >> resp;

            while (resp < 1 || resp > 2) {
                cout << "Incorrect Response: Try Again" << endl;
                cin >> resp;
            }


            switch(resp) {
                case 1:
                    scorecard.fillScoreCard(diceArr);
                    scorecard.printScoreCard();
                    break;

                case 2:
                    cout << endl << endl;
                    cout << "Pick a Category 1-13, you can't pick a Category twice" << endl;
                    selectCategory();
                    break;
            }

            cout << endl << endl;
            cout << "Do you want to play again? (Y/N) ";
            cin >> resp1;
        } while (resp1 == 'y' || resp1 == 'Y');
}




void Yahtzee::displayOptions() {
    cout << "Options:" << endl;
    cout << "1: Pick dice to keep and reroll the rest" << endl;
    cout << "2: Pick category" << endl;
}


int Yahtzee::selectCategory() {
    //choices
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

    int choice;
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
    
    return choice;
}
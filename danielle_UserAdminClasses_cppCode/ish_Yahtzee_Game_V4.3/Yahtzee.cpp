/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include "Yahtzee.h"
#include "Dice.h"
#include "Score_Card.h"

using namespace std;

Yahtzee::Yahtzee() {
    highscore = 0;
}

void Yahtzee::rules(){
    cout << "Yahtzee is a game played with five dice, where the objective is to score as many points as possible in 13 rounds." << endl;
    cout << "Each player takes turns rolling the dice up to three times per turn, trying to achieve certain combinations." << endl;
    cout << "After each turn, the player must choose a category to score their points in, and that category cannot be used again." << endl << endl;
    cout << endl;
    cout << "______________________________________________________________________________________________________________________" << endl;
    cout << "The categories are as follows:" << endl;
    cout << "1. Ones: Score the sum of all dice showing the number 1." << endl;
    cout << "2. Twos: Score the sum of all dice showing the number 2." << endl;
    cout << "3. Threes: Score the sum of all dice showing the number 3." << endl;
    cout << "4. Fours: Score the sum of all dice showing the number 4." << endl;
    cout << "5. Fives: Score the sum of all dice showing the number 5." << endl;
    cout << "6. Sixes: Score the sum of all dice showing the number 6." << endl;
    cout << "7. Three of a Kind: If at least three dice show the same number, score the sum of all dice." << endl;
    cout << "8. Four of a Kind: If at least four dice show the same number, score the sum of all dice." << endl;
    cout << "9. Full House: If three dice show one number and the other two dice show another number, score 25 points." << endl;
    
    // Categories 10-13 are only available after the first six rounds:
    cout << "10. Small Straight: If the dice show any sequence of four numbers, score 30 points." << endl;
    cout << "11. Large Straight: If the dice show any sequence of five numbers, score 40 points." << endl;
    cout << "12. Yahtzee: If all five dice show the same number, score 50 points." << endl;
    cout << "13. Chance: Score the sum of all dice, regardless of category." << endl;
    cout << "______________________________________________________________________________________________________________________" << endl;
}



void Yahtzee::play() {
    ScoreCard scorecard;
    Dice dice[NUM_DICE];
    int numRounds = 13;
    int diceArr[NUM_DICE];
    int resp;
    char resp1;
    int catNum = 0;

    do {
        cout << "WELCOME TO YAHTZEE!!" << endl << endl;
        cout << "RULES: " << endl;
        rules();

        cout << endl << endl;
        for (int i = 0; i < numRounds; i++) {
            bool categorySelected = false;
            int numRolls = 3;
            cout << "|" << string(40, '-') << "|" << endl;
            cout << "|" << setw(20) << "Round " << i + 1 << setw(20) << "|" << endl;
            cout << "|" << string(40, '-') << "|" << endl;

            vector<int> selected;

            for (int currRoll = 0; currRoll < numRolls; currRoll++) {
                displayOptions();
                while (!(cin >> resp) || resp < 1 || resp > 3) {
                    cout << "Invalid choice. Please enter a number between 1 and 3: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                bool leave = false;
                bool clearance = false;
                switch (resp) {
                    case 1:
                        char resp2;
                        
                        do {
                            for (int j = 0; j < NUM_DICE; j++) {
                                if (find(selected.begin(), selected.end(), j) == selected.end()) {
                                    dice[j].roll();
                                }
                            }
                            
                            cout << "\nDice values:" << endl;
                            for (int j = 0; j < NUM_DICE; j++) {
                                cout << setw(4) << dice[j].getValue() << "  ";
                            }
                            cout << "\n";
                            for (int j = 0; j < NUM_DICE; j++) {
                                cout << "Dice" << j + 1 << " ";
                            }
                            cout << "\n" << string(40, '-') << endl;

                            for (int i = 0; i < NUM_DICE; i++) {
                                diceArr[i] = dice[i].getValue();
                            }
                            
                            char resp3;
                            //possible outcomes
                            scorecard.fillScoreCard(diceArr,clearance);
                            scorecard.printScoreCard();
                            cout << "Would you like to pick a category? Y/N" << endl;
                            cin >> resp3;
                            
                            switch(resp3){
                                case 'y':
                                case 'Y':
                                    clearance = true;
                                    scorecard.fillScoreCard(diceArr,clearance);
                                    numRolls = 1;
                                    leave = true;
                                    break;
                            }
                            
                            if (currRoll < numRolls - 1) {
                                cout << "Enter the dice numbers (1-5) to keep, separated by spaces, or -1 to stop: ";
                                int choice;
                                
                                while (!(cin >> choice) || (choice != -1 && (choice < 1 || choice > NUM_DICE))) {
                                    cout << "Invalid choice. Please enter a number between 1 and " << NUM_DICE << ", or -1 to stop: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }

                                while (choice != -1) {
                                    selected.push_back(choice - 1);
                                    cout << "Keeping Dice" << choice << ": " << dice[choice - 1].getValue() << endl;
                                    cin >> choice;
                                }

                            }
                            
                            numRolls--;
                            if (currRoll == numRolls) {
                                resp2 = 'n';
                            } else {
                                cout << "Do you want to pick another dice? Y/N" << endl;
                                while (!(cin >> resp2) || (toupper(resp2) != 'Y' && toupper(resp2) != 'N')) {
                                    cout << "Invalid choice. Please enter 'Y' or 'N': ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            }

                        } while (toupper(resp2) == 'Y');

                        if(!leave){
                            cout << endl << endl;
                            cout << "\nDice values:" << endl;
                            for (int j = 0; j < NUM_DICE; j++) {
                                cout << setw(4) << dice[j].getValue() << "  ";
                            }
                            cout << "\n";
                            for (int j = 0; j < NUM_DICE; j++) {
                                cout << "Dice" << j + 1 << " ";
                            }
                            cout << "\n" << string(40, '-') << endl;
                            scorecard.printScoreCard();
                            
                            clearance = true;
                            scorecard.fillScoreCard(diceArr,clearance);
                            scorecard.printScoreCard();
                            numRolls = 1;
                        }
                        break;

                    case 2:
                        clearance = true;
                        cout << "\n\nPick a Category 1-13, you can't pick a Category twice" << endl;
                        scorecard.fillScoreCard(diceArr,clearance);
                        numRolls = 1;
                        break;
                    case 3:
                        cout << "<Leaving program>" << endl;
                        exit(0);
                        break;
                }
                
            }
            
        }
        cout << "\n\nDo you want to play again? (Y/N) ";
        while (!(cin >> resp1) || (toupper(resp1) != 'Y' && toupper(resp1) != 'N')) {
            cout << "Invalid choice. Please enter 'Y' or 'N': ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (resp1 == 'y' || resp1 == 'Y');
}



void Yahtzee::displayOptions() {
    cout << "Options:" << endl;
    cout << "1: Get Dice, pick dice to keep ,and reroll the rest" << endl;
    cout << "2: Pick category" << endl;
    cout << "3: End the game" << endl;
}



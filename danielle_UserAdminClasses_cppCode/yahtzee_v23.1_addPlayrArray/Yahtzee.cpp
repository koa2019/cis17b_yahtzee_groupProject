#include <iostream>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>  // vectors
#include <sstream>  // stringstream -> convert int to string. 
#include "Yahtzee.h"
#include "Dice.h"       // aggregates instance of Dice class
#include "ScoreCard.h"   // aggregates instance of ScoreCard class
#include "User.h"       // aggregates instance of User class
using namespace std;


//**********************************************************
//                  Default Constructor
//**********************************************************
Yahtzee::Yahtzee() {
    
    nPlayer = 2; 
    
    // Initialize dice array
    for(int i=0; i < NUM_DICE; i++){
        diceArr[i] = 0;
    }   
    
    // Create array of index to keep track of each player
    indx = new int[nPlayer];
    
    // Initialize array
    for (int i=0; i < nPlayer; i++) {         
        indx[i] = i;
    }
  
    // creating double pointers. An array of Classes
    player = new User*[nPlayer]; 
    
    
    // Creating each individual player by calling User constructor 
    // Every player is initially set with a name of Player i
    // change player 1's name inside of startGame();    
    for (int i = 0; i < nPlayer; i++) {  
        
        int num = i+1;
        stringstream stream;  // convert int to string
        stream << num;
        string str2;
        stream >> str2;  // save converted int to a string variable
        string str1 = "Player " + str2;
        player[indx[i]] = new User(str1); 
    }
        
}

//**********************************************************
//              Play game
//**********************************************************

bool Yahtzee::play(User &user){
    
    bool p1Winner = false;
    
    // Reset player 1's name with user's name
    player[indx[0]]->setName(user.getName());    
    
    // Create array for player's name
    string name[nPlayer] = {player[indx[0]]->getName(), player[indx[1]]->getName() };
    
    getNPlayer();  // Get number of players
    //getRules(); // Print rules    
    
    
    // if more than 1 player, then print message 
    if(nPlayer > 1){ cout << "\n\t" << name[0] << " vs " << name[1]; } 
    pause();

    const int MAXROLLS = 3;
    int resp, 
        numRolls;    
    Dice dice[NUM_DICE];     // aggregate instance of Dice class. Dice array object    
    int diceArr[NUM_DICE];  // local dice int array
    vector<int> selected;  // Create vector for the dice we're keeping for final points
        
    

    // Game runs for 13 rounds. 1 round per category
    for (int rnd = 0; rnd < scorecard[0].getMAXRNDS() ; rnd++) {

        prntRound(rnd);
                
        for(int pIndx = 0; pIndx < nPlayer; pIndx++){            
           
            numRolls = 0; // Reset for each player's turn        
        
            // loop as long as numRolls does NOT equal 3
            while(!(numRolls == MAXROLLS)){

                cout << "\n   " << name[pIndx] << "'s turn. Round " << rnd+1 << " Roll " << numRolls+1 << endl;
                pause('r');  // Pause to mimic rolling dice

                //  I WANT TO CALL A FUNCTION FOR ALL THIS DICE CODE
                //rollDice(dice); 
                // loops through selected vector, and checks which dice to re-roll
                for (int j = 0; j < NUM_DICE; j++) {                                
                    if (find(selected.begin(), selected.end(), j) == selected.end()) {
                        dice[j].roll(); 
                    }
                }                    

                // Print Dice class object's values
                cout << "\n\tDice values:" << endl;
                for (int j = 0; j < NUM_DICE; j++) {
                    cout << setw(4) << dice[j].getValue() << "  ";
                }
                cout << "\n";
                for (int j = 0; j < NUM_DICE; j++) {
                    cout << "Dice" << j + 1 << " ";
                }
                cout << "\n" << string(40, '-') << endl << endl;

                // Setting local dice array with Dice class object
                for (int i = 0; i < NUM_DICE; i++) {
                    diceArr[i] = dice[i].getValue();
                }

                numRolls++; // increment numRolls every time dice are rolled       

                
                // Set scorecard with possible points based on dice values
                // Print scorecard with the categories they can choose from
                scorecard[indx[pIndx]].fillScoreCard(diceArr);
                cout << setw(6) << " " << name[pIndx] <<"'s Possible Points: \n";
                scorecard[indx[pIndx]].printScoreCard();           


                resp = 0;

                if(numRolls == 3){ resp = 2; } // if last roll, force switch case 2 to run
                else { displayOptions(resp); } // else offer them options to choose from


                // choose dice to keep, pick a category, re-roll or exit game
                switch(resp){

                    case 1: // Select dice you want to keep in between rolls
                    {
                        cout << "Enter the dice numbers (1-5) to keep, separated by spaces,\nor -1 to stop: ";
                        int choice;

                        // Validate user's input
                        while (!(cin >> choice) || (choice != -1 && (choice < 1 || choice > NUM_DICE))) {
                            cout << "Invalid choice. Please enter a number between 1 and " << NUM_DICE << ", or -1 to stop: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }


                        // Push the dice they want to keep to the selected vector
                        while (choice != -1) {
                            selected.push_back(choice - 1);
                            cout << "Keeping Dice" << choice << ": " << dice[choice - 1].getValue() << endl;
                            cin >> choice;  
                        }
                        break;
                    }
                    case 2: // Keep points from 1 category and end their turn
                    {
                        numRolls = MAXROLLS; // reassign it, so while(numRolls<maxRolls) stops

                        // set player's final scorecard object
                        finalSC[indx[pIndx]].setFinalSC(scorecard[indx[pIndx]], diceArr);  

                        // set player's total score each time finalSC is changed
                        player[indx[pIndx]]->setHiScore(finalSC[indx[pIndx]].getTotalScore());

                        // Only print finalSC when it's NOT the last round
                        // if it's NOT the last round, then print player's final scorecard
                        if(rnd != scorecard[0].getMAXRNDS()-1){ finalSC[pIndx].printFinalSC( name[pIndx]); }

                        else { // If it IS the last round AND there is 2 players,
                              // AND it's player 1's turn, then print their final scorecard

                            if((nPlayer > 1) && (pIndx == 0)){ finalSC[pIndx].printFinalSC( name[pIndx]); }

                            else { 
                                cout<<"Tallying your final score...\n"; 
                                pause();
                            }                    
                        }     
                        break;
                    }
                    case 3: // Rolls dice again
                    {    
                        // Break out of switch() to re-roll 
                        break;
                    }
                    default: // if they exit early, then print final scorecards
                    {
                        cout << "\n\t   " << "<Leaving program>" << endl;
                        numRolls = MAXROLLS; // reset values to break out all of the loops
                        pIndx = 2;
                        rnd = 13;
                        break;  
                    }
                } // ends switch(resp)       
            } // ends while(!(numRoll == MAXROLLS))  
            
            // Print this line for readable when more than 1 player
            if(nPlayer > 1 && pIndx == 0) { cout << "\n\n|" << string(40, '-') << "|" << endl; }
            
        } // ends for(pIndx <  nPlayer; pIndx++)
    } // ends round for loop i < 13              

    
    // Print player's final scorecard 
    finalSC[indx[0]].setRound(13);          // Set round to last round for each player, so it'll 
    finalSC[indx[1]].setRound(13);          //  check if they hit upperScore bonus in printFinalSC()
    finalSC[indx[0]].printFinalSC(name[0]); // Print player 1's final scorecard 
    if(nPlayer > 1) { finalSC[indx[1]].printFinalSC(name[indx[1]]); }  // Print player 2's final scorecard 
    cout << "\n\n\t\tGame Over!\n";

   
    if(nPlayer > 1) { // If there is more than 1 player
    
        cout << endl << setw(20) << name[0] << setw(4) << " vs " << name[1] << endl;
        cout << setw(20)  << player[indx[0]]->getHiScore() << setw(4) << " vs " << player[indx[1]]->getHiScore();
        
        
        // Check is p1 is winner, tie or loser
        if( player[indx[0]]->getHiScore() > player[indx[1]]->getHiScore() ){
            p1Winner = true;
            cout << "\n\n\t\t" << name[indx[0]] << " won!\n";

        } else if( player[indx[0]]->getHiScore() == player[indx[1]]->getHiScore() ){
            p1Winner = true;
            cout << "\n\n\t\t Tie Game!\n";

        } else { 
            p1Winner = false; 
            cout << "\n\n\t\tUh-Oh... " << name[indx[1]] << " won!\n";
        }
    
    } else { p1Winner = true; } 
    
    
    if(p1Winner){ // if player 1 is winner, then check if they have a new hiScore
         
        /* Player 1 represents the user object. ONLY change their values if p1 wins.
           Check is p1's score from this game is larger than their hiScore stored in binary file */
        if(user.isHiScore( player[indx[0]]->getHiScore() )){            
            
            // Reset user's hiSCore and update binary & text file
            
            user.setHiScore( player[indx[0]]->getHiScore() );
            cout << "\n\tNew High Score of " << user.getHiScore() << "!\n";
            //user.printUsr();
            
            // Certain printout depending on if User is logged in or not
            if(user.getName() == "Guest"){ cout<<"\n\tSign up or Login to save your score.\n"; }
            else { cout << "\nUpdating binary...."; }
            
            return p1Winner; // return true p1 has new high score  
            
        } else { cout<<"\n\nGood Game!\n"; }        
    }
    
    return false;
}

//*****************************************************************
//        Print player's options and return their choice
//*****************************************************************
void Yahtzee::displayOptions(int &resp) {
    
    cout << "\nOptions:" << endl;
    cout << "1: Select which dice you want to keep\n   before rolling again." << endl;
    cout << "2: Pick category and end your turn" << endl;
    cout << "3: Roll again." << endl;
    cout << "4: Exit" << endl;
    cout << "Enter a number: ";    
    
    while (!(cin >> resp) || resp < 1 || resp > 4) {
        cout << "Invalid choice. Please enter a number between 1 and 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


//****************************************************
//              Get # of player & validate input
//****************************************************
void Yahtzee::getNPlayer(){
    
    const int MAXPLYR = 2;
    int num = 1;
    do {
        cout<<"\n\nHow many players?\nEnter number between 1 and 2:  ";
        cin >> num;
    } while(!(num >= 1 && num <= MAXPLYR));
    nPlayer = num;
    cin.ignore();
}


//******************************************
//              Print round
//******************************************
void Yahtzee::prntRound(int i){
    
    i = (i < 0 ) ? 0 : i;
    
    cout << endl << endl;
    cout << "|" << string(40, '-') << "|" << endl;
    cout << "|" << setw(20) << "Round " << i + 1 << setw(20) << "|" << endl;
    cout << "|" << string(40, '-') << "|" << endl;
}


//******************************************
//      pause screen before continuing
//******************************************
void Yahtzee::pause(char ch) {
    
    string msg = ch=='r' ? "roll" : "continue";    
    cout<<endl<<setw(6)<<' '<<"Press enter to " << msg << ".";   
    cin.get();
}


//******************************************
//          Print rules
//******************************************
void Yahtzee::getRules(){
    
    cout << "WELCOME TO YAHTZEE!!" << endl << endl;
    cout << "RULES: " << endl << endl << endl;
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

#include "Score.h"
#include <iostream>   //Input/Output Library
#include <iomanip>  // fixed, setprecision()
//#include <cstring>  // char [] library
//#include <string>   // length() library
//#include <cctype>  //toupper()
using namespace std;

//***********************************************************
//     Default constructor 
//***********************************************************
Score::Score() : Player() {
    
    // 
    Player **player = new Player*[ getNumPlayrs() ];

    // Create new Player Class for each player
    for (int i = 0; i < getNumPlayrs(); i++) {
        player[i] = new Player(); //creating each individual player by calling Player constructor           
    }
    maxRolls = 3;
    ttlRolls = 0;
}

//***********************************************************
//    Constructor #2
//***********************************************************
Score::Score(string name) : Player() {
    setName(name);
    maxRolls = 3;
    ttlRolls = 0;
}

//***********************************************************
//    Constructor #3
//***********************************************************
Score::Score(int maxGam) : Player() {
    setName(name);
    maxRolls = maxGam;
    ttlRolls = 0;
}

//***********************************************************
//   Copy constructor
//***********************************************************
Score::Score(const Score &obj) {
    maxRolls = obj.maxRolls;
    ttlRolls = obj.ttlRolls;
}

//***********************************************************
//   set total games with try,catch, throw
//***********************************************************
void Score::setTtlRolls(int num){    
    if(num>=0) {ttlRolls = num; }      
    else {throw NegativeGames();}
}



//******************************************************************************
//   BUG: needs to prints Score structure. its not inheriting player[0] & [1] 
//      Displays game's name and instructions in a banner
//      or prints score Card. 
//******************************************************************************
void Score::getBanner(string title) {

    cout << "\n********************************\n" << setw(21) << title << endl;
    cout << "********************************\n";
//    cout << setw(10) << setfill(' ') << score->player[0].name
//         << setw(6) << setfill(' ') << right << "vs"
//         << setw(12) << score->player[1].name << endl;

    if(title=="SCORE CARD") {        
        cout<<endl<<setw(9)<<setfill(' ')<< getTtlRolls() <<" rolls left.\n";
        
        //cout << setw(8) << player[0].numWins
             //<< setw(14) << score->player[1].numWins << endl;
        
    } else {
        cout << "\n        13 rounds to score \n          as many points \n"
             << setw(5) << " " << "as many points as you can." << endl;
    }
}



//******************************************************************************
//  Display hit message when player guesses correctly
//******************************************************************************
void Score::hitMiss(int &pGuess, char &i, bool isHit) {

    if (isHit) {
        cout << setw(12) << pGuess << " == " << i << endl;
        //cout << setw(12) << pGuess << " == " << score->player[b].shipLoc << endl;
        //cout << setw(22) << "It\'s a HIT!\n\n" << endl;
        
    } else {
        cout << setw(15) << pGuess << endl << setw(22) << "It\'s a MISS!\n\n";
    }
}





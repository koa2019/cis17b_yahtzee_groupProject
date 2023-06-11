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
    nRolls = 3;
//    // 
//    Player **player = new Player*[ getNumPlayrs() ];
//
//    // Create new Player Class for each player
//    for (int i = 0; i < getNumPlayrs(); i++) {
//        player[i] = new Player(); //creating each individual player by calling Player constructor           
//    }
   
}

//***********************************************************
//    Constructor #2
//***********************************************************
Score::Score(string nme) {  
    Player player(nme);
    nRolls = 3;
}

//***********************************************************
//   Copy constructor
//***********************************************************
Score::Score(const Score &obj) {
    nRolls = obj.nRolls;
}

//***********************************************************
//   set total games with try,catch, throw
//***********************************************************
void Score::setNRolls(int num){    
    if(num>=0) {nRolls = num; }      
    else {throw NegativeGames();}
}


//******************************************************************************
//   BUG: needs to prints Score structure. its not inheriting player[0] & [1] 
//      Displays game's name and instructions in a banner
//      or prints score Card. 
//******************************************************************************
void Score::getBanner(string title) {

    cout<<"\n***************************************\n"<<setw(22)<< title << endl;
    cout<<"***************************************\n";
//    cout << setw(10) << setfill(' ') << score->player[0].name
//         << setw(6) << setfill(' ') << right << "vs"
//         << setw(12) << score->player[1].name << endl;

    if(title=="SCORE CARD") {        
        cout<<endl<<setw(9)<<setfill(' ')<< getNRolls() <<" rolls left.\n";
        
        //cout << setw(8) << player[0].numWins
             //<< setw(14) << score->player[1].numWins << endl;
        
    } else {
        cout<<"\n"<<setw(9)<<' '<<"13 rounds to score\n"<<setw(10)<<' '<<"as many points \n"
            <<setw(5)<<' '<< "as many points as you can.\n";
    }
}




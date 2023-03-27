#include "Player.h"
#include <iostream>   //Input/Output Library
#include <iomanip>  // fixed, setprecision()
#include <cmath>    // round()
#include <cstdlib>  // rand()
#include <fstream>  // fstream 
#include <cstring>  // char [] library
#include <string>   // length() library
#include <ctime>    // time library for rand()
#include <cctype>   // toupper()
using namespace std;  //STD Name-space where Library is compiled


//************************************************************
//    Default constructor
//************************************************************
Player::Player() {  
    //cout<<"Hit Player() Constructor\n"; 
    //Player score();// create new instances of Score class 
    nPlayrs=2;
    setName(); //name=fNames[rand()%6];
    isRight=false;
    numWins=0;
    guess=0;
    brdSize=13;
    
}

//************************************************************
//    Constructor#2
//************************************************************
Player::Player(string nme) {  
    //cout<<"Hit Player() Constructor #2\n";
    nPlayrs=2;
    setName(nme);
    isRight=false;
    numWins=0;
    guess=0;
    brdSize=13;
}

//************************************************************
//    set member variables in class
//************************************************************ 
void Player::setPlayer(int numPly,bool correct, int num,int gussIndx){
        setNumPlayrs(numPly);
        setName();
        setIsRight(correct);
        setWins(num);
        setGuess(gussIndx); 
}; 

//****************************************************************
//      sets a player's name
//      converts string to char array
//****************************************************************
void Player::setName(string nme){
    // loop through the length of name string
    for (int c=0; c<(nme.length()+1); c++) {        
        name[c] = nme[c];
    }
}
//****************************************************************
//      sets 1 player's name randomly.
//      converts string to char array
//****************************************************************
void Player::setName(){
   
    int indx1, // index for player 1's name
        indx2; // index for player 2's name
    
    // loop through number of players when player's is an array
    //for (int i=0; i<nPlayrs; i++) {

        // generate new random name for each player
        //if (i==0) {
            indx1 = rand()%6;           
            
//        } else { //makes sure the same 2 names are NOT picked from the names array
//
//            do {
//                indx2 = rand()%6; 
//                
//            } while (indx2 = indx1);
//
//            indx1 = indx2; //? resets something
//        }

        // set player name by creating new char[] the size of string +1
        //player[i].name = new char[fNames[indx1].length() + 1];
        name = new char[fNames[indx1].length() + 1];
        
        // loop through the length of name string
        for (int c=0;c<(fNames[indx1].length()+1); c++) {

            // convert string to c-string and to uppercase. static_cast as char           
            //score->player[i].name[c] = (char) toupper(fNames[indx1].c_str()[c]);           
            name[c] = (char)toupper(fNames[indx1].c_str()[c]);           
        }     
    //}
}

//****************************************************************
//          Randomly sets a player's guess to number between [0,13]
//****************************************************************
void Player::setGuess(int guesIndx){      
    guess = guesIndx;
}


//****************************************************************
//           calls Choices Accessor function
//****************************************************************
void Player::printGBoard()const {
    gboard.printBoard();
}
void Player::printTotals()const {
    gboard.printSums();
}




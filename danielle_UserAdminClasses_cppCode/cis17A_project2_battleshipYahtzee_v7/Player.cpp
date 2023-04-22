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
    cout<<"Hit Player() Default Constructor\n";
    setRandName(); 
    numWins=0;
    brdSize=13;
    
}

//************************************************************
//    Constructor#2
//************************************************************
Player::Player(string nme) {  
    cout<<"Hit Player() Constructor #2\n";
    setName(nme);
    numWins=0;
    brdSize=13;
}
 

//****************************************************************
//      sets a player's name
//      converts string to char array
//****************************************************************
void Player::setName(string nme){
    
    // set player name by creating new char[] the size of string +1
    name = new char[nme.length() + 1];
    
    // loop through the length of name string
    for (int c=0; c<(nme.length()+1); c++) {        
        
        // convert string to c-string and to uppercase. static_cast as char           
        //score->player[i].name[c] = (char) tolower(nme.c_str()[c]);           
        name[c] = (char)tolower(nme.c_str()[c]);
    }
}
//****************************************************************
//      sets 1 player's name randomly.
//      converts string to char array
//****************************************************************
void Player::setRandName(){
   
    string fNames[7] = {"Mom", "Bart", "Homer", "Jillian", "Ting", "Victor", "Cora"};
    
    int indx = (rand()%7); // index for player 1's name           

    // set player name by creating new char[] the size of string +1
    name = new char[fNames[indx].length() + 1];

    // loop through the length of name string
    for (int c=0;c<(fNames[indx].length()+1); c++) {

        // convert string to c-string and to uppercase. static_cast as char           
        //score->player[i].name[c] = (char) tolower(fNames[indx1].c_str()[c]);           
        name[c] = (char)tolower(fNames[indx].c_str()[c]);           
    }
}

//****************************************************************
//           calls Choices Accessor function
//****************************************************************
void Player::printGBoard(string n)const {
    gboard.printBoard(n);
}
void Player::printTotals()const {
    gboard.printSums();
}




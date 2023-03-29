/* File:   Player.h
 * Author: DanYell
 * Created on December 16, 2022, 10:37 PM
 * Player Class specifications
*/

#ifndef PLAYER_H
#define PLAYER_H
#include "Choices.h"  //Player aggregates 
//#include "Score.h"
#include <string>   //string
#include <cstring>  //char [] library
using namespace std;

//class Player : public Score {     // structure represents a single player
class Player {

protected:
   
    int nPlayrs;
    string fNames[7] = {"Mom", "Bart", "Homer", "Jillian", "Ting", "Victor", "Cora"};
    char *name;     //player's name
    bool isRight;   //player's guess is correct or not
    int numWins;    //a player's number of wins
    int guess;     //guessing index of opponent's ship on game board
    int brdSize;    //game board size 20
    Choices gboard; //Player will aggregate an instances of Choices class
    //char **guessArr; // player's guesses  --> guessP1[ROWS][COLS]={};   
 
public:    
    Player();        //Default constructor
    Player(string); //constructor #2
    
    virtual ~Player(){ //Destructor
        if (strlen(name)>0){
            delete [] name;            
        }
    }
    
    //Copy constructor
//    Player(const Player &obj){
//        name = obj.name;
//        nPlayrs=obj.nPlayrs;
//        isRight=obj.isRight;
//        numWins=obj.numWins;
//        guess=obj.guess;
//        brdSize=obj.brdSize;    
//    }
     
    //Mutators
    void setNumPlayrs(int num){nPlayrs=num;}
    void setName();
    void setName(string);
    void setIsRight(bool b){isRight=b;}
    void setWins(){numWins++;}
    void setWins(int n){numWins=n;}
    void setGuess(int);
    void setPlayer(int,bool,int,int);    
    
    //Accessors
    int getNumPlayrs() const{return nPlayrs;}
    string getName() const {return name;}
    int getIsRight() const {return isRight;}
    int getNumWins() const {return numWins;}
    int getGuess() const {return guess;}
  
    //calls Choices Accessor function
    const char get1gBrdElmnt(int i)const {return gboard.get1BrdElmnt(i);}
    void printGBoard()const; 
    void printTotals() const; // calls printSums()
    //returns reference to *board
    const char *getGBoard() const {return gboard.getBoard();}
    
    //Accessing inherited Score class
     //bool play(int a, int b, int &round);
//    void getBanner(string);    // print banner
//    void prntScore() ;    // prints Score structure 
//    void hitMiss(int guess=0, char i='-', bool isHit=true);     // print message after each player guesses

};

#endif /* PLAYER_H */


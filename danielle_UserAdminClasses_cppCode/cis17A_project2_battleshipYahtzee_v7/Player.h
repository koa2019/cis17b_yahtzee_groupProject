/* File:   Player.h
 * Author: DanYell
 * Created on December 16, 2022, 10:37 PM
 * Player Class specifications
*/

#ifndef PLAYER_H
#define PLAYER_H
#include "Choices.h"  //Player aggregates 
//#include "Score.h"
#include <string>   //string, .c_str()
#include <cstring>  //char [] library
using namespace std;

//class Player : public Score {     // structure represents a single player
class Player {

protected:
   
    //
    char *name;     //player's name
    int numWins;    //a player's number of wins
    int brdSize;    //game board size 13
    Choices gboard; //Player will aggregate an instances of Choices class  
 
public:    
    Player();        //Default constructor
    Player(string); //constructor #2
    
    virtual ~Player(){ //Destructor
        if(strlen(name)>0){
            delete [] name;            
        }
    }
         
    //Mutators
    void setRandName();
    void setName(string);
    void increWins(){numWins++;}
    void setWins(int n){numWins=n;}    
    void set1Category(int i, int pts){ gboard.set1Catgry(i, pts); }
    
    //Accessors
    string getName() const {return name;}
    int getBrdSize(){return brdSize;}
    int getNumWins() const {return numWins;}
  
    //calls Choices Accessor function
    const int get1Category(int i)const {return gboard.get1BrdElmnt(i);}
    void printGBoard(string n)const; 
    void printTotals() const; // calls printSums()
    
    //returns reference to *board
    const int *getGBoard() const {return gboard.getBoard();}
};
#endif /* PLAYER_H */


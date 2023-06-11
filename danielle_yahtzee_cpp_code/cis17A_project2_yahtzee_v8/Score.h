/* File:   Score.h
 * Author: DanYell
 * Created on December 16, 2022, 10:41 PM
 * Bug: Protected & public keywords aren't diff color
 */

#ifndef SCORE_H
#define SCORE_H
using namespace std;
#include <iostream>
#include "Player.h" 

// Score inherits Player class
class Score : public Player {

protected:
    int nRolls;

public:

    class NegativeGames {}; //Exception class. Empty class declaration
    Score();         //Default constructor 
    Score(string);  //constructor #2   
    Score(const Score &); // Copy constructor
    
 
    ~Score(){cout<<"\nHit Score Destructor.";}
    
    //Mutators    
    void setNRolls(int);
    void decreRolls(){ --nRolls; }


    //Accessors   
    int getNRolls()const {return nRolls;} 
    void getBanner(string); // print banner & prints Score structure    
};
#endif /* SCORE_H */


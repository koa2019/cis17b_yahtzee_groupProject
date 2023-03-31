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

//private:
protected:
    int maxRolls;
    int ttlRolls;
    int ttlRnds;

public:
         
    class NegativeGames {}; //Exception class. Empty class declaration
    const int SIZE17 = 17; //size of choices array 
    Score();         //Default constructor 
    Score(string);  //constructor #2
    Score(int);    //constructor #3 for passes maxRolls    
    Score(const Score &); // Copy constructor
    
    //  I THINK IM MISSING A DESTRUCTOR!
    ~Score(){cout<<"\nHit Score Destructor.";}
    
    //Mutators    
    void setMaxRoll(int num) {maxRolls = num;}
    void setTtlRolls(int);
    void decreRolls(){ ttlRolls--; }
    void setScore(int nPly, int rolls, int tRolls, int tRnds) {
        setMaxRoll(rolls);
        setTtlRolls(tRolls);
    }

    //Accessors   
    int getMaxRoll()const {return maxRolls; }
    int getTtlRolls()const {return ttlRolls;} 
    void getBanner(string); // print banner & prints Score structure 
    void hitMiss(int &guess, char &i, bool isHit); // print message after each player guesses
    //Score *fillScore(string [],char **);    // fill Score structure by playing game  
    //void setBoard(Score *score,char **ptr2D);   // sets 2D pointer with Score structure   
};

#endif /* SCORE_H */


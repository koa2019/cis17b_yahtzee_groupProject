/* File:   Score.h
 * Author: DanYell
 * Created on December 16, 2022, 10:41 PM
 * Bug: Protected & public keywords aren't diff color
 */

#ifndef SCORE_H
#define SCORE_H
using namespace std;
#include "Player.h" 

// Score is derived from Player class
class Score : public Player {
protected:
    int maxGmes;
    int ttlGmes;
    int ttlRnds;

public:
    
    //Exception class. Empty class declaration 
    class NegativeGames {};     
    const int SIZE17 = 17; //size of choices array 
    Score();//Default constructor 
    Score(string);//constructor #2
    Score(int);   //constructor #3 for passes maxGmes    
    Score(const Score &); // Copy constructor

    //Mutators    
    void setMaxGmes(int num) {maxGmes = num;}
    void setTtlGmes(int);
    void setScore(int nPly, int gmes, int tGmes, int tRnds) {
        setMaxGmes(gmes);
        setTtlGmes(tGmes);
    }

    //Accessors   
    int getMaxGmes()const {return maxGmes; }
    int getTtlGmes()const {return ttlGmes;} 
    void getBanner(string); // print banner & prints Score structure 
    void hitMiss(int &guess, char &i, bool isHit); // print message after each player guesses
    //Score *fillScore(string [],char **);    // fill Score structure by playing game  
    //void setBoard(Score *score,char **ptr2D);   // sets 2D pointer with Score structure   
};

#endif /* SCORE_H */


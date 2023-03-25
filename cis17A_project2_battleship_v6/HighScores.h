/* File:   HighScores.h
 * Author: DanYell
 * Created on December 18, 2022, 1:06 PM
*/

#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include "PlayScore.h"
using namespace std;  //STD Name-space where Library is compiled


class HighScores {
private:
    float totPrzMony;
public:
    //Default constructor
    HighScores(){ totPrzMony=0;}    
    friend class PlayScore; //friend class
    void setHSMony(float m){totPrzMony=m;}
    float getHSMoney() const {return totPrzMony;}    
    
    // Overloaded Postfix++
    HighScores operator++() {
        ++totPrzMony;   
        return *this;  
    }
    
    // Overloaded Postfix++
    HighScores operator--() {
        --totPrzMony;   
        return *this;  
    }
};

#endif /* HIGHSCORES_H */


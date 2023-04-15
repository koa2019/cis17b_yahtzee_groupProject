/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Yahtzee.h
 * Author: error
 *
 * Created on April 9, 2023, 4:59 PM
 */

#ifndef YAHTZEE_H
#define YAHTZEE_H
#include "Dice.h"

class Yahtzee {
private:
    static const int NUM_DICE = 5;
    Dice dice[NUM_DICE];
    int diceArr[NUM_DICE];
    void displayOptions();
    int highscore;
    
public:
    Yahtzee();
    void play();
    void rules();
};


#endif /* YAHTZEE_H */


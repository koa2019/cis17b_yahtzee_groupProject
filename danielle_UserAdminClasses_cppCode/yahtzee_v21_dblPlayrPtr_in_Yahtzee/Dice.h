/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dice.h
 * Author: Ismael
 *
 * Created on March 23, 2023, 4:48 PM
 */

#ifndef DICE_H
#define DICE_H

class Dice {
private:
    int value;
public:
    Dice();
    void roll();
    int getValue() const;
};


#endif /* DICE_H */


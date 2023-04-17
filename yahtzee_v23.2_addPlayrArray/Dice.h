/* File:   Dice.h
 * Author: Ismael
 * Created on March 23, 2023, 4:48 PM
*/

#ifndef DICE_H
#define DICE_H

class Dice {
protected:
    static const int NUM_DICE = 5; 
    int value;
public:
    Dice();
    void roll();
    int getValue() const;
};
#endif /* DICE_H */
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Dice.h"

#include <cstdlib>
#include <ctime>

Dice::Dice() {
    value = 0;
    srand(static_cast<unsigned int>(time(0))); // random numeber generator
}

void Dice::roll() {
    value = rand() % 6 + 1;
}

int Dice::getValue() const {
    return value;
}
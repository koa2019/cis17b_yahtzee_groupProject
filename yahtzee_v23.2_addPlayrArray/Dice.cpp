#include "Dice.h"
#include <cstdlib>
#include <ctime>
#include <iostream>  // cout
#include <iomanip>  // setw()
using namespace std;

Dice::Dice() {
    value = 0;    
}

void Dice::roll() {
    value = rand() % 6 + 1;
}

int Dice::getValue() const {
    return value;
}

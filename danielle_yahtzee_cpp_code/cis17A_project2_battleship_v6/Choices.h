/* File:   Choices.h
 * Author: DanYell
 * Created on December 16, 2022, 10:15 PM
*/

#ifndef CHOICES_H
#define CHOICES_H
#include <string>
using namespace std;  //STD Name-space where Library is compiled

class Choices {
protected:
    int size;
    char *board; // pointer to char array
    int *indx; //Index used in sorting the array
    char bChoice[18] = "S-SS-SS--S-S--SS-"; // S=ship  B=blank

public:
    const int SIZE17 = 17; // # of characters in choices array   
    Choices();      //Default constructor
    Choices(int s); //Constructor #2
    Choices(const Choices &);//copy constructor
    ~Choices();//Destructor
    
    //Mutator function
    void setBoard();
    
    // Accessor function
    int getBrdSize() const {return size;}
    char get1BrdElmnt(int i)const {return board[i];}
    char *getBoard() const {return board;}
    int *getIndx() const {return indx;}
    void printBoard() const;
    void printSums() const;
        
};
#endif /* CHOICES_H */


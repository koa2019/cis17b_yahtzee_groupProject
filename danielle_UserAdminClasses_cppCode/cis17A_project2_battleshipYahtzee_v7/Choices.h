/* File:   Choices.h
 * Author: Danielle
 * Created: 03-29-23 @7:15 PM
*/

#ifndef CHOICES_H
#define CHOICES_H
#include <string>
using namespace std;  //STD Name-space where Library is compiled

class Choices {
protected:
    int size;
    int *board; // pointer to int array
    int *indx; //Index used in sorting the array

public:
    Choices();      //Default constructor
    Choices(const Choices &);//copy constructor
    ~Choices();//Destructor
    
    //Mutator function
    void set1Catgry(int, int); // set points on scorecard
    
    // Accessor function
    int getBrdSize() const {return size;}
    int get1BrdElmnt(int i)const {return board[i];}
    int *getBoard() const {return board;} // returns pointer array
    int *getIndx() const {return indx;} // returns array of index
    void printBoard(string n) const;
    void printSums() const;
        
};
#endif /* CHOICES_H */


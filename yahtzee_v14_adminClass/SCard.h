/*File:   SCard.h
 * Author: DanYell
 * Created on March 30, 2023, 8:31 PM
*/

#ifndef SCARD_H
#define SCARD_H
#include <string>
using namespace std;  //STD Name-space where Library is compiled

class SCard {
protected:
    int size;
    int *board; // pointer to int array
    int *indx; //Index used in sorting the array

public:
    SCard();      //Default constructor
    SCard(const SCard &);//copy constructor
    ~SCard();//Destructor
    
    // Mutator function
    void set1Catgry(int, int); // set points on scorecard
    
    // Accessor function
    int getBrdSize() const {return size;}
    int get1BrdElmnt(int i)const {return board[i];}
    int *getBoard() const {return board;} // returns pointer array
    int *getIndx() const {return indx;} // returns array of index
    void printBoard(string n) const;
    void print2Board(int i)const;
    void printTotals() const;
    void printUpper() const;
    void printLower() const;
    void printGTotal() const;
    
};
#endif /* SCARD_H */


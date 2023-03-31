#include "SCard.h"
// System Libraries: 
#include <iostream> // cin, cout
#include <iomanip>  // fixed, setprecision()
#include <cstdlib>  // rand()
#include <ctime>    // time library for rand()
#include <cstring>  // char [] library
#include <string>   // length() library
#include <cctype>   // toupper()
using namespace std; 

//**************************************************************
//Default constructor
//**************************************************************
SCard::SCard() {
    
    int nCategory = 13;
    size = nCategory;
    board = new int[size];
    indx = new int[size];

    //Initialize both arrays 
    for (int i = 1; i <= size; i++) {            
        board[i] = 0; // rand()%(26+65) uppercase letters from alphabet            
        indx[i] = i;        
    }
}


//**************************************************************
//       copy constructor
//**************************************************************
SCard::SCard(const SCard &obj1) {
    size  = obj1.size;      
    board = new int[size];
    indx  = new int[size];
    for(int x=0; x<size; x++){
       board[x] = obj1.board[x];
       indx[x] = obj1.indx[x];
   }
}

//**************************************************************
//         Destructor
//**************************************************************
SCard::~SCard() {
    if(getBrdSize()>0) {
        delete [] board;
        delete [] indx;
    }
    board=nullptr;
    indx=nullptr;
}

//**************************************************************
//  reinitialize board with ships or blanks that are stored in 
//  a static array 
//**************************************************************
void SCard::set1Catgry(int indx, int nPts){
    board[indx] = nPts;
}

//**************************************************************
//                  Prints 1 scorecard
//**************************************************************
void SCard::printBoard(string pName) const {
    
    cout<<"\t"<<pName<<"'s Scorecard\n";
    for (int i = 1; i<=getBrdSize(); i++) {
        cout<<setw(13)<<indx[i]<<setw(3)<<board[i]<<endl;
    } 
    cout<<endl;
}

//**************************************************************
//                  Prints 2 scorecard
//**************************************************************
void SCard::print2Board(int i) const {
   cout<<setw(13)<<indx[i]<<setw(3)<<board[i];
}

void SCard::printTotals() const {
    int upperSum=1;
    int lowerSum=2;
    int gTotal=3; 
     
    cout<<"Upper section: "<< upperSum << endl;
    cout<<"Lower section: "<< lowerSum << endl;
    cout<<"Grand Total:   "<< gTotal << endl;
}

//**************************************************************
//              Prints upper section scores
//**************************************************************
void SCard::printUpper() const{
    int upperSum=1;
    cout<<"Upper section: "<< upperSum;
}

//**************************************************************
//              Prints lower section scores
//**************************************************************
void SCard::printLower() const{
    int lowerSum=2;
    cout<<"Lower section: "<< lowerSum;
}

//**************************************************************
//              Prints grand total. lower + upper sections
//**************************************************************
void SCard::printGTotal() const{
    int gTotal=3; 
    cout<<"Grand Total:   "<< gTotal;
}
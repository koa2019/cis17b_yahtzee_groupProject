#include "Choices.h"
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
Choices::Choices() {
    
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
Choices::Choices(const Choices &obj1) {
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
Choices::~Choices() {
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
void Choices::set1Catgry(int indx, int nPts){
    board[indx] = nPts;
}

//**************************************************************
// Prints scorecard
//**************************************************************
void Choices::printBoard(string pName) const {
    
    cout<<"\t"<<pName<<"'s Scorecard\n";
    for (int i = 1; i<=getBrdSize(); i++) {
        cout<<setw(13)<<indx[i]<<setw(3)<<board[i]<<endl;
    } 
    cout<<endl;
}

//**************************************************************
//              Prints upper and lower section scores
//**************************************************************
void Choices::printSums() const{
    int upperSum=0, lowerSum=0;
    cout<<"Upper section: "<< upperSum <<endl;
    cout<<"Lower section: "<< lowerSum <<endl;
    cout<<"Grand Total:   "<< (upperSum+lowerSum)<<endl<<endl;
}
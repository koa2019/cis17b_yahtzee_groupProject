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
    
    size = 13;
    board = new char[size];
    indx = new int[size];

    //Initialize both arrays 
    for(int shuffle=0;shuffle<2;shuffle++){ //randomized values 2 times
        for (int i = 0; i < size; i++) {            
            board[i] = '0'; // rand()%(26+65) uppercase letters from alphabet            
            indx[i] = i;
        }
    }
    //sets board with ships or blanks
    setBoard();
}

//**************************************************************
//Constructor #2
//**************************************************************
Choices::Choices(int s) {

    size = (s<2 && s>100) ? 13 : s;
    board = new char[size];
    indx = new int[size];

    //Initialize both arrays 
    for (int i=0; i<size; i++) {        
        board[i] = '0'; // rand() lowercase letters from alphabet            
        indx[i] = i;
    }
    //sets board with ships or blanks
    setBoard();
}

//**************************************************************
//       copy constructor
//**************************************************************
Choices::Choices(const Choices &obj1) {
    size=obj1.size;      
    board = new char[size];
    indx = new int[size];
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
void Choices::setBoard(){
    //reinitialize both pointer arrays 
    for(int shuffle=0;shuffle<2;shuffle++){ //randomized values 2xs
        for (int i=0; i<size; i++) {
            board[i] = bChoice[rand()%SIZE17]; // fills with S=ship or B=blank
            indx[i] = i;
        }
    }
}

//**************************************************************
// Prints game board
//**************************************************************
void Choices::printBoard() const {
    
    
    //cout<<"\n\t"<<name<<"'s Game Board\n";
    cout<<"'s Scorecard\n";
    for (int i = 0; i<getBrdSize(); i++) {
        cout<<setw(13)<<indx[i]+1<<setw(3)<<board[i]<<endl;
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
/* File:    main.cpp
 * Author:  Danielle F
 * Created: 12-16-2022 @ 10:13 PM
 * Purpose:  cis17A_project2_battleship_v6
 * 
 * v5: 
	Created 3 new classes: HighScores, PlayScore and ChoicesTemplate.
	PlayScore has a static member and prints its value in main().
	PlayScore has a copy constructor that copies parent1 object into parent2 object.
	I attempted to make HighScores a friend of PlayScore but kept getting an error in HighScore that “PlayScore was not declared”. I commented out the code in main.
	I couldn’t convert Choices.h to a template without messing up Player class because it aggregates it. I copied Choices to ChoicesTemplate and ran it as a class with a char pointer array. I converted it to a vector template, but the program kept crashing. I commented out its instances in main().
	Added overloaded operator++ and operator—to HighScore 
	Made a base class call a derived class. Score calls a function of Player

 * v6: converted my battleship_v6 to Yahtzee. 
 *    Changed the gameBoard's print out. Initialized gameBoard to zero.
 *    Printed out 5 random dice and the new gameBoard in the play().
 *    Added printSums() to Choices and a printTotals in Player. 
 *    Called printTotals() in the main when a winner is correct.
 *    Set numRolls in Score class. * 
 *    While loop isn't stopping at round 13;
 * 
 * v8: getting rid of Score class and using Player class instead

 * To do:

 * fix bug in Score.h Protected & public keywords aren't diff color
 * inherit a HighScore instance
*/

//System Libraries
#include <iostream>   //Input/Output Library
#include <iomanip>  // fixed, setprecision()
#include <cstdlib>  // rand()
#include <cstring>  // char [] library
#include <string>   // length() library
#include <ctime>    // time library for rand()
#include <cctype>   // toupper()
#include <vector>
using namespace std;  //STD Name-space where Library is compiled

//User Libraries
#include "Player.h"  // Player class aggregates an instance of Choices class
//#include "Score.h"  // Score inherits Player Class. Player aggregates Choices Class 
                    // and uses an instance of Choices class

//Global Constants not Variables


//Function Prototypes
bool play(Player**,int,int &);
void getBanner(string); // print banner & prints Player class
int *rBanner(int &);// print round banner
void pause();// pauses game to allow user to view results before proceeding


//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int> (time(0)));
    
    //Declare variables here                   
    bool    p1_crrt,     // player 1 correct
            p2_crrt;    // player 2 correct 
     
    int round = 0,  // round counter
        maxRnd = 2, // max round = 13
        numPlyr = 2; // number of players 

    
    //********************************************
    //         Yahtzee play starts here
    //********************************************
    
    // create a pointer to Player's structure and create array size of 2   
    Player **player;     
    
    // creating an array of Player pointers
    player = new Player*[numPlyr];
    
    //array of index to keep track of each player
    int *indx = new int[numPlyr];
    
    // creating each individual player by calling Player constructor
    for (int i=0; i<numPlyr; i++) {         
        indx[i]=i;
    }
    
    player[indx[0]] = new Player("Hercules");
    player[indx[1]] = new Player("Computer");
    
    // pointer for rounds
    int *rndPtr = nullptr;

    // display game's introduction message 
    getBanner("YAHTZEE");        
    cout<<"\n\t"<<player[indx[0]]->getName()<<" vs "<<player[indx[1]]->getName()<<endl;
      
    
    for(int r=0;r<maxRnd;r++){
       
        // sets variables to default starting values
        p1_crrt = p2_crrt = false;

        // display round number banner
        rndPtr = rBanner(round);

        pause();

        // Player 1's turn                       
        p1_crrt = play(player,indx[0],round);

        
        // Player 2's turn
        if(p1_crrt){ 
            
            cout<<"\n\n     Now it's "<<player[1]->getName()<<"'s turn.\n"; 
            pause();
            p2_crrt = play(player,indx[1],round); 
        }                           
          
    } // ends rounds loop
       
    // After 13 rounds print scorecards
    getBanner("SCORE CARD");
    
    // Print player 1's scorecard
    player[indx[0]]->printGBoard(player[indx[0]]->getName()); 
    player[indx[0]]->printTotals();
   
    // Print player 2's scorecard
    player[indx[1]]->printGBoard(player[indx[1]]->getName());  
    player[indx[1]]->printTotals();
    
    // de-allocate dynamic memory
    for (int p=0; p<numPlyr; p++) {       
        delete player[p]; //Deletes the Data row by row
    } 
    delete [] player;
    delete [] indx;    
    player=nullptr;
    indx=nullptr;
    
    return 0;
}


//****************************************************************
//              BUG! supposed to be in Player.h 
//
//              Each player has up to 3 rolls.
//      By the end of their turn they must chose 1 category
//      to set points in. If they can't score in any category,
//      then they must take a zero in a remaining category.
//****************************************************************

bool play(Player **player, int a, int &round){
   
    unsigned short ans;    
    int nRolls = 3,
        dSize = 5,          // number of dice
        rollCnt = 1,        // counts number of rolls
        nDiceRllng = dSize; // number of dice rolling at this moment
    int *dice = nullptr;     // array holds the number of dice we're rolling during each roll    
    int keep[]={0,0,0,0,0}; // Needs to accept MORE than 1 dice at a time 
    
    
    do {  // Loops up to 3 rolls
        
        cout << endl << setw(26) <<"***************************************\n";
        cout << setw(22) << "Roll " << rollCnt++ << endl;
        cout << setw(26) <<"***************************************\n";
    
        dice = new int[nDiceRllng]; // allocate dynamic array for dice
        
        for(int d=1;d<=nDiceRllng;d++){
            dice[d] = (1+rand()%6); // returns number 1-6
        }

        --nRolls; // decrease # of rolls
                
        // Print dice     
        cout<<setw(10)<<' '<<player[a]->getName()<<" Rolled: "<<endl;
        for(int d=1; d <= nDiceRllng; d++){
            cout<<setw(5)<<dice[d]<<setw(3)<<' ';      
        } 
        cout<<endl;
        for(int d=1; d <= nDiceRllng; d++){
            cout<<setw(7)<<"dice"<<d;      
        } 
        

        // Prints this player's possible points for this roll
        cout<<"\n\n\tPossible points.\n";
        player[a]->printGBoard(player[a]->getName());           
        
        
        cout<<setw(4)<<' '<<"Number of rolls left: "<< nRolls <<endl;
        
        
        //  if player has any rolls left, then print this menu.
        //  else make this player choose a category to set points in.
        
        if(!(nRolls == 0)){
            
            cout<<endl<<setw(13)<<" "<<player[a]->getName()<<endl
                <<" Press 1: to keep any of these dice:\n"
                <<" Press 2: to keep one of these scores & end your turn\n"
                <<" Press 3: to roll again\n";
            cout<<" Make a selection: ";
            cin>>ans; 
            cin.ignore();
            cout<<endl;

            switch(ans){
                
                case 1: { // Choose which dice you want to keep for this roll                     
                   
                    int cnt=0, stop = nDiceRllng, choice=1;
                    
                    cout<<" Which of these dice do you want to keep?\n"
                        <<" Enter which dice number you want to keep.\n";
                    cout<<" Enter a number one at a time between 1 and "<<nDiceRllng
                        <<"\n Or 9 to stop. "; 
                                       
                        
                    while( choice != 9 && (choice>=1 && choice<=nDiceRllng) && !(stop==0) ) 
                    {    
                        cin>>choice;

                        if(choice != 9) {
                            
                            keep[cnt] = dice[choice]; // BUG! It does NOT hold values 
                            dice[choice] = 0;         // in between rolls
                            cnt++;  // increase # of dice they are keeping                       
                            stop--; // used as a bounds check for nDiceRllng
                            //cout<<"\ncnt= "<<cnt<<" stop= "<<stop<<endl;

                            // Print message if it is NOT the last nDiceRllng
                            if(cnt != nDiceRllng){cout<<"\n\n    Choose a dice or 9 to stop.\n"; }
                            
                            // prints remaining dice they can choose
                            for(int d=1; d <= nDiceRllng; d++){
                                cout<<setw(5)<<dice[d]<<setw(3)<<' ';      
                            } 
                            cout<<endl;
                            for(int d=1; d <= nDiceRllng; d++){
                                cout<<setw(7)<<"dice"<<d;      
                            } 
                            cout<<endl;                            
                        }
                    } 
                    
                    nDiceRllng -= cnt; // Reassign how many dice are left to roll
                    cout<<"\n Number of dice left to roll = "<< nDiceRllng<<endl; 
                    cout<<"\n Keeping dice values ";
                    for(int i=0; i<cnt; i++){
                        cout<<keep[i]<<' ';
                    }
                    cout<<endl;
                    
                    // if # of dice is zero, then their turn ends
                    if(nDiceRllng<=0){ nRolls = 0; }
                    
                    break;
                }
                case 2: { //  Break out of switch() and make this player choose a 
                          //  category to set their points in & end their turn
                    nRolls = 0;   
                    break;
                }
                default: { // roll x number of dice                    
                    cout<<" Rolling "<<nDiceRllng<<" number of dice...\n"; 
                }
            }// ends switch()
        } // ends if roll !=0
                
    } while(nRolls>0);
    
    
    // Make player choose one category to add their points to
    // Save points in scorecard
    
    cout<<"\n It's over writting values after each roll.\n Keeping dice values ";
    for(int i=0; i<dSize; i++){
        cout<<keep[i]<<' ';
    }
    cout<<endl;
    int nPts = (rand()%101);
    cout<<" Points = "<<nPts<<endl;                
    
    do {
        cout<<"\n Which category do you want to save \n your points to?\n"
            <<" Enter a number 1 to 13\n ";
        //cin>>ans;
        //cin.ignore();       
        ans = (1+(rand()%13));
    } while(!(ans>=1 && ans <= player[a]->getBrdSize()));
    
    cout<<"\n Saving "<< nPts <<" points to category "<< ans <<endl;   
    player[a]->set1Category(ans, nPts);  // Set points in scorecard    
    player[a]->printGBoard(player[a]->getName()); // Print their scorecard       
    pause();   
     
    if(nRolls<=0){
        nRolls = 3;            
        return true;
    }
    return false;  
}

//******************************************
//      banner displays round number
//******************************************
int *rBanner(int &round) {    
    int *rndPtr = nullptr;
    round += 1;
    rndPtr = &round;
    cout << endl << setw(26) << "***************************************\n";
    cout << setw(22) << "Round " << *rndPtr << endl;
    cout << setw(26) <<"***************************************\n";
    return rndPtr;
}


//******************************************************************************
//   BUG: needs to prints Score structure. its not inheriting player[0] & [1] 
//      Displays game's name and instructions in a banner
//      or prints score Card. 
//******************************************************************************
//void getBanner(Player *player, string title) {
void getBanner(string title) {

    cout<<"\n***************************************\n"<<setw(22)<< title << endl;
    cout<<"***************************************\n";
//    cout << setw(10) << setfill(' ') << score->player[0].name
//         << setw(6) << setfill(' ') << right << "vs"
//         << setw(12) << score->player[1].name << endl;

    if(title=="SCORE CARD") {        
        
        //cout << setw(8) << player[0].numWins
             //<< setw(14) << score->player[1].numWins << endl;
        
    } else {
        cout<<"\n"<<setw(9)<<' '<<"13 rounds to score\n"<<setw(10)<<' '<<"as many points \n"
            <<setw(5)<<' '<< "as many points as you can.\n";
    }
}


//******************************************
// pause screen before game starts
//******************************************
void pause() {
    cout<<endl<<setw(5)<<' '<<"Press enter to continue.\n";   
    cin.get();
}
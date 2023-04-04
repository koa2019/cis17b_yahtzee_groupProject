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
#include "Score.h"  // Score inherits Player Class. Player aggregates Choices Class 
                    // and uses an instance of Choices class

//Global Constants not Variables


//Function Prototypes
bool play(Score *,Player **,int,int,int &);  //returns if player's guess was correct or not
int *rBanner(int &);// print round banner
void pause();// pauses game to allow user to view results before proceeding

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int> (time(0)));
    
    //Declare variables here
    const int SIZE17 = 17;  // # of characters in choices array
                   
    bool    p1_crrt,     // player 1 correct
            p2_crrt;    // player 2 correct 
    
    int     MAX=6,    // maximum number for rand()       
            indx1,       // index for player 1's name
            indx2,       // index for player 2's name
            maxRoll=3, // number of rolls
            numRolls = maxRoll,      // number of games left       
            round=0, // round
            maxRnd=13,
            numPlyr = 2;  

    
    //********************************************
    //         Battleship play starts here
    //********************************************
    
    // create new instances of Score class 
    Score score;  // Replaced Score *score = new Score;
    score.setTtlRolls(maxRoll);
    cout<<"Num rolls left: "<<score.getTtlRolls()<<endl;
    
    // create a pointer to Player's structure and create array size of 2
    //score->player = new Player[score->nPlayrs]; 
    Player **player;     
    
    //creating an array of Player pointers
    player = new Player*[score.getNumPlayrs()];
    
    //array of index to keep track of each player
    int *indx = new int[numPlyr];
    
    // creating each individual player by calling Player constructor
    for (int i=0; i<numPlyr; i++) {
        player[i] = new Player(); 
        indx[i]=i;
    }
  
    // pointer for rounds
    int *rndPtr = nullptr;

    
    while (round < maxRnd || score.getTtlRolls() > 0 ) {
       
        // sets variables to default starting values
        p1_crrt = p2_crrt = false;

        // display game's introduction message 
        score.getBanner("YAHTZEE");        
        cout<<"\n\t"<<player[indx[0]]->getName()<<" vs "<<player[indx[1]]->getName()<<endl;
        
        // loops until a player correctly guesses opponents ship location
        while ((!p1_crrt) && (!p2_crrt)) {

            // display round number banner
            rndPtr = rBanner(round);

            pause();
            
            // Player 1's Guess                       
            p1_crrt = play(&score,player,indx[0],indx[1],round);
            
            // If player1 is false, then it's player2 turn to guess
            if(!p1_crrt){                
                p2_crrt = play(&score,player,indx[1],indx[0],round);                            
            }           
            
        } // ends while((!p1_crrt) && (!p2_crrt))
        
        
        numRolls--; // Decrease # rolls left 
        
        try {score.setTtlRolls(numRolls);}           
        catch(Score::NegativeGames){ cout<<"Error. Negative rolls.\n"; }
        
        
        score.getBanner("SCORE CARD");
        //score.prntScore();
         
        // checks maximum number of rolls has NOT been played
        if(numRolls>0) { pause(); }          
           
        // reset variables for next game
        //*rndPtr=0;          
        p1_crrt = p2_crrt = false; 
        
    } // ends the while(numRolls> ZERO)
    
    // Game ends & Prints each player's game board
    cout<<endl<<endl<<setw(15)<<player[indx[0]]->getName();
    player[indx[0]]->printGBoard(); 
    player[indx[0]]->printTotals();
   
    cout<<setw(15)<<player[indx[1]]->getName();
    player[indx[1]]->printGBoard();  
    player[indx[1]]->printTotals();
    
    // de-allocate dynamic memory
    for (int p=0; p<numPlyr; p++) {       
        delete player[p]; //Deletes the Data row by row
    } 
    delete [] player;
    delete [] indx;    
    player=nullptr;
    indx=nullptr;
    //delete score;   
    //score = nullptr;
    
    return 0;
}


//****************************************************************
//  BUG! supposed to be in Player.h
//
//     Returns if player's guess is correct or not     
//****************************************************************

bool play(Score *score, Player **player, int a, int b, int &round){
   
    unsigned short ans;
    int dice1, dice2, dice3, dice4, dice5, dice6;
    dice1 = (1+rand()%6); // returns number 1-6
    dice2 = (1+rand()%6); // returns number 1-6
    dice3 = (1+rand()%6); // returns number 1-6
    dice4 = (1+rand()%6); // returns number 1-6
    dice5 = (1+rand()%6); // returns number 1-6
    dice6 = (1+rand()%6); // returns number 1-6
    
    cout<<setw(15)<<' '<<"You Rolled: "<<endl;
    cout<<setw(5)<<dice1<<setw(7)<<dice2<<setw(7)<<dice3
        <<setw(7)<<dice4<<setw(7)<<dice5<<setw(7)<<dice6<<endl;
    cout<<setw(2)<<' '<<"dice1  dice2  dice3  dice4  dice5  dice6\n";
            
    // Prints this player's score board
    cout<<endl<<endl<<"\t"<<player[a]->getName();
    player[a]->printGBoard(); 
    
    
    cout<<endl<<setw(13)<<" "<<player[a]->getName()<<endl
        <<" Press 1: to keep any of these dice:\n"
//        <<setw(10)<<dice1<<' '<<dice2<<' '<<dice3<<' '
//                  <<dice4<<' '<<dice5<<' '<<dice6<<endl
        <<" Press 2: to keep one of these scores\n"
        <<" Press 3: to roll again\n\n";
    cin>>ans;
    
    
    switch(ans){
        case 1: {
            // Add dice to an array or vector
            cout<<"\n Which of these dice do you want to keep?\n\n";
            cout<<setw(5)<<dice1<<setw(7)<<dice2<<setw(7)<<dice3
                <<setw(7)<<dice4<<setw(7)<<dice5<<setw(7)<<dice6<<endl;
            cout<<setw(2)<<' '<<"dice1  dice2  dice3  dice4  dice5  dice6\n";
            break;
        }
        case 2: {
            // Save score to score card
            cout<<"Saving points to score card\n";
            cout<<"Now it's "<<player[b]->getName()<<"'s turn.\n";
            //player[a]->setIsRight(true);            
            break;
        }
        default:
            // roll x number of dice
            cout<<"Roll 1 to 5 dice\n"; 
            cout<<"Decrement numRolls\n";
            score->decreRolls();
            cout<<"Num rolls left: "<<score->getTtlRolls()<<endl;
    }
           
        
    // set this player's guess
    player[a]->setGuess(dice1);
    
    // get this player's guess
    int guessIndx = player[a]->getGuess(); 
    
    // get other player's ship or blank from their game board
    char oppntPos = player[b]->get1gBrdElmnt(guessIndx);
    
    //cout<<player[a]->getName()<<" guesses "<< guessIndx<<"\n";   
    //cout<<player[b]->getName()<<"   ["<<guessIndx<<"] "<<oppntPos<<endl<<endl;

    // checks if player guess is correct
    //if (pGuess == score->player[b].shipLoc) {
    if(oppntPos=='S' || oppntPos=='s') { 
        player[a]->setWins();                             
        player[a]->setIsRight(true);        
        score->hitMiss(guessIndx,oppntPos,true);//(pGuess,i,isHit) 
        return true;      
    } 
    else{
        // if player guess is wrong display MISS message 
        player[a]->setIsRight(false);   
        score->hitMiss(guessIndx,oppntPos,false);//(pGuess,i,isHit)    
        return false;    
    }                
}

//******************************************
//      banner displays round number
//******************************************
int *rBanner(int &round) {    
    int *rndPtr = nullptr;
    round += 1;
    rndPtr = &round;
    cout << endl << setw(26) << "********************************" << endl;
    cout << setw(18) << "Round " << *rndPtr << endl;
    cout << setw(26) << "********************************" << endl;
    return rndPtr;
}

//******************************************
// pause screen before game starts
//******************************************
void pause() {
    cout<<endl<<setw(7)<<' '<<"Press enter to roll. \n\n";   
    cin.get();
}
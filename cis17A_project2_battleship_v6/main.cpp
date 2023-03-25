/* File:    main.cpp
 * Author:  Danielle F
 * Created: 12-16-2022 @ 10:13 PM
 * Purpose:  cis17A_project2_battleship_v5
 * 
 * v5: 
	Created 3 new classes: HighScores, PlayScore and ChoicesTemplate.
	PlayScore has a static member and prints its value in main().
	PlayScore has a copy constructor that copies parent1 object into parent2 object.
	I attempted to make HighScores a friend of PlayScore but kept getting an error in HighScore that “PlayScore was not declared”. I commented out the code in main.
	I couldn’t convert Choices.h to a template without messing up Player class because it aggregates it. I copied Choices to ChoicesTemplate and ran it as a class with a char pointer array. I converted it to a vector template, but the program kept crashing. I commented out its instances in main().
	Added overloaded operator++ and operator—to HighScore 
	Made a base class call a derived class. Score calls a function of Player

* To do:
 *fix ChoicesTemplate
 * fix bug in Score.h Protected & public keywords aren't diff color
 * add 3 ships to each player's profile
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
    
    int     MAX=13, // maximum number for rand()       
            indx1,       // index for player 1's name
            indx2,       // index for player 2's name
            maxGmes=3, // number of games
            nGmsLft,      // number of games left       
            round=0, // round
            maxRnd=13,
            numPlyr = 2;  

    
    //********************************************
    //         Battleship play starts here
    //********************************************
    
    // create new instances of Score class 
    Score score;  // Replaced Score *score = new Score;
    
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

    // read in maximum number of games that can be played from file
    nGmsLft = score.getMaxGmes(); // set numberOfGamesLeft to equal maxGames
    
    while (nGmsLft>0) {
       
        // sets variables to default starting values
        p1_crrt = p2_crrt = false;

        // display game's introduction message 
        score.getBanner("YAHTZEE");        
        cout<<"\n\t"<<player[indx[0]]->getName()<<" vs "<<player[indx[1]]->getName()<<endl;
        
        // loops until a player correctly guesses opponents ship location
        while ((!p1_crrt) && (!p2_crrt)) {

            // display round number banner
            rndPtr = rBanner(round);

            // Player 1's Guess                       
            p1_crrt = play(&score,player,indx[0],indx[1],round);
            
            // If player1 is false, then it's player2 turn
            if(!p1_crrt){ 
                // Player 2's Guess  
                p2_crrt = play(&score,player,indx[1],indx[0],round);                            
            }

            // if both players guess wrong, then display message 
            if ((!p1_crrt) && (!p2_crrt)) {
                cout << endl << "  You Both Missed. Try Again...\n\n";
            }
            
        } // ends while((!p1_crrt) && (!p2_crrt))
        
        // Decrease # games left 
        nGmsLft--;
        
        try {           
            score.setTtlGmes(nGmsLft);
            
        } catch(Score::NegativeGames){ 
            cout<<"Error. Negative games.\n";
        }
        
        score.getBanner("SCORE CARD");//score.prntScore();
         
        // checks maximum number of games has NOT been played
        if(nGmsLft>0) { pause(); }          
           
        // reset variables for next game
        *rndPtr=0;          
        p1_crrt = p2_crrt = false; 
        
    } // ends the while(nGmsLft> ZERO)
    
    // Game ends & Prints each player's game board
    cout<<"\n\n\t"<<player[indx[0]]->getName();
    player[indx[0]]->printGBoard(); 
    
   
    cout<<"\t"<<player[indx[1]]->getName();
    player[indx[1]]->printGBoard();   
    
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
// BUG! supposed to be in Player.h
//     Returns if player's guess is correct or not     
//****************************************************************

bool play(Score *score, Player **player, int a, int b, int &round){
   
    cout<<endl<<setw(1)<<" "<<player[a]->getName()
        <<" Guess a number between 0-13\n\n";
           
    int num = rand()%13;
    
    // set this player's guess
    player[a]->setGuess(num);
    
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
    cout << "\nPress enter to continue. \n\n";   
    cin.get();
}
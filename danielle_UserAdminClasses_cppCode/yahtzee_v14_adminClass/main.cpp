/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-24-2023 @ 1:36 PM
 * Purpose:  yahtzee_v14_adminClass
 
v14: 
 * I simplified cis17A_project2_yahtzee_v7 & v8 by eliminating Score class 
 * & only have Player class in main().
 * Adding Player class which aggregates an instance of SCard class to main().
 * Added yahtzee() in menu which uses the Player class to play the game.
 * Added print() in SCard class that write the upper, lower,
 * & grand totals. They're based on static variable that will need to be changed
 * when I added Ismael's scorecard class
 * Added get() in Player that call SCard class various print total functions.
 * It would be more efficient(less code) to have Player inherit SCard instead of
 * aggregating an instance of it.


 * To do:
 * BUG! Admin needs to edit member variable in binary.   
        User is appending the new hiScore to a new binary record instead 
        of inserting @its original spot. Does NOT rewrite binary inside of reWrtBin().
 * Solutions? use ios::ate and seekp().
 
 * Admin needs to delete record from binary --> passing record & cursor size?
 * Solutions? To delete binary copy files up to target record with email to  
 * a temp.dat, skip the target record, then continue writing to temp.dat. 
 * Then delete usrData.dat and rename temp.dat to usrData.dat;
 
 * Why aren't my class variables green after moving them to 
   their own cpp file?  
  
 * Is there a way to move play() from main() to inside of Player.cpp?    
 * Add Logan's Dice class to Play() 
 * Replace SCard with Ismael's ScoreCard class & then call it in Play()
 * Print actual sums for scorecard
 * Style scorecard print out   
 
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include <iomanip>    // setw()
#include <cstdlib>   // rand()
#include <ctime>    // time()
#include <string>   //string var
#include <cstring>  //c-strings
#include <cctype>  //c-string helper functions
#include <fstream> // input/output for files
using namespace std;  //STD Name-space where Library is compiled

//User Libraries
#include "Admin.h"
#include "User.h"  // User class inherits Admin class
#include "Player.h" // Player class aggregates an instance of SCard class

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

// Function Prototypes for Player class
void yahtzee();     // Starts a game of Yahtzee 
bool play(Player**, int, int&);
void getBanner(Player **, int, int, string); // print banner & prints Player class
int *rBanner(int &);// print round banner
void pause();       // pauses game to allow user to view results before proceeding


/*****  Code Begins Execution Here with function main  ****/
int main(int argc, char** argv) {
    
    // Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    // Variables    
    int choice = 0;
    
    //do {
    cout<<"\n\nMenu\n"
        <<"Press 1: Sign Up\n"
        <<"Press 2: Read file to set User database\n"
        <<"Press 3: User Login\n"
        <<"Press 4: Admin Login\n"
        <<"Press 5: Play Yahtzee\n"
        //<<"Press 5: \n"
        <<"Press 9: Logout\n";
        cin>>choice;
        cin.ignore();
        
        switch(choice){
            case 1:{ 
                User user;    // Create one instance of User class
                user.signUp();                 
                break;
            }
            case 2:{ 
                User user2;    // Create one instance of User class
                user2.readInputFile();                 
                break;
            }
            case 3:{ // I WANT TO SAVE THIS ADMIN TO A USER so i can play()
             
                Admin admin;  // Create one instance of Admin class
                if(admin.getUsrLogin()){
                    //admin.print1Record();
                    //Admin user2();// ? create new instances of User class 
                    User user3(admin.getTtlRec(), admin.getID(),admin.getName(),admin.getEmail(),admin.getPwrd());
                    user3.play();
                } else {cout<<"\nUnable to locate your email.\n";}
                break;
            } 
            case 4:{
                Admin admin2;  // Create one instance of Admin class
                admin2.getAdLogin();
                break;
            } 
            case 5:{  
                yahtzee();
                //User user4;    // Create one instance of User class
                //user4.play();                
                break;
            }
            default: {
                cout<<"\nLogged Out.\n";                
                exit(0);
            }
        }
        
        
    return 0;
}

/**********  Function Definitions  **************/
void yahtzee(){
    bool    p1_crrt,     // player 1 correct
            p2_crrt;    // player 2 correct 
     
    int p1=0, // player 1 index
        p2=1, // player 2 index
        round = 0,  // round counter
        maxRnd = 1, // max round = 13
        numPlyr = 2; // number of players 
    
    //********************************************
    //         Yahtzee play starts here
    //********************************************
    
    // create a pointer to Player's structure and create array size of 2   
    Player **player = new Player*[numPlyr];
    
    player[p1] = new Player("Guest Player");
    player[p2] = new Player("Computer");
    
    // pointer for rounds
    int *rndPtr = nullptr;

    // display game's introduction message 
    getBanner(player,p1,p2,"YAHTZEE");        
        
    
    for(int r=0;r<maxRnd;r++){
       
        // sets variables to default starting values
        p1_crrt = p2_crrt = false;

        // display round number banner
        rndPtr = rBanner(round);

        pause();

        // Player 1's turn                       
        p1_crrt = play(player,p1,round);

        
        // Player 2's turn
        if(p1_crrt){             
            cout<<"\n\n     Now it's "<<player[p2]->getName()<<"'s turn.\n"; 
            pause();
            p2_crrt = play(player,p2,round); 
        }                           
          
    } // ends rounds loop 
    
    // After 13 rounds print scorecards
    getBanner(player,p1,p2,"GAME OVER");
    
   
    // de-allocate dynamic memory
    for (int p=0; p<numPlyr; p++) {       
        delete player[p]; //Deletes the Data row by row
    } 
    delete [] player;   
    player=nullptr;  
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
    int dice []={0,0,0,0,0};     // array holds the number of dice we're rolling during each roll    
    int keep[]={0,0,0,0,0}; // Needs to accept MORE than 1 dice at a time 
    
    
    do {  // Loops up to 3 rolls
        
        cout << endl << setw(26) <<"***************************************\n";
        cout << setw(22) << "Roll " << rollCnt++ << endl;
        cout << setw(26) <<"***************************************\n";
    
        //dice = new int[nDiceRllng]; // allocate dynamic array for dice
        
        for(int d=0; d<nDiceRllng;d++){
            dice[d] = (1+(rand()%6)); // returns number 1-6
        }

        --nRolls; // decrease # of rolls
                
        // Print dice     
        cout<<setw(10)<<' '<<player[a]->getName()<<" Rolled: "<<endl;
        for(int d=0; d<nDiceRllng;d++){
            cout<<setw(5)<<dice[d]<<setw(3)<<' ';      
        } 
        cout<<endl;
        for(int d=0; d<nDiceRllng;d++){
            cout<<setw(7)<<"dice"<<d+1;      
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
                            
                            keep[cnt] = dice[choice-1]; // BUG! It does NOT hold values 
                            dice[choice-1] = 0;         // in between rolls
                            cnt++;  // increase # of dice they are keeping                       
                            stop--; // used as a bounds check for nDiceRllng
                            //cout<<"\ncnt= "<<cnt<<" stop= "<<stop<<endl;

                            // Print message if it is NOT the last nDiceRllng
                            if(cnt != nDiceRllng){cout<<"\n\n    Choose a dice or 9 to stop.\n"; }
                            
                            // prints remaining dice they can choose
                            for(int d=0; d<nDiceRllng;d++){                                
                                cout<<setw(5)<<dice[d]<<setw(3)<<' ';      
                            } 
                            cout<<endl;
                           for(int d=0; d<nDiceRllng;d++){
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
    int nPts = (rand()%31);
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
//          Displays game's name and instructions in a banner
//          or print each player's final score card. 
//******************************************************************************

void getBanner(Player **player, int p1, int p2, string title) {
 
    if(title=="YAHTZEE") {
        cout<<"\n\n\n\n***************************************\n";
        cout<<setw(22)<< title;
        cout<<"\n***************************************\n";
        cout<<"\n"<<setw(9)<<' '<<"13 rounds to score\n"
            <<setw(10)<<' '<<"as many points \n"
            <<setw(5)<<' '<< "as many points as you can.\n";        
        cout<<"\n\t"<<player[p1]->getName()<<" vs "<< player[p2]->getName()<<endl;
    
        
    } else {  // Print Game Over  
        cout<<"\n************************************************************\n";
        cout<<setw(38)<< title;
        cout<<"\n************************************************************\n";
        
        cout<<"\t"<<player[p1]->getName()<<"'s Scorecard";
        cout<<"\t"<<player[p2]->getName()<<"'s Scorecard\n";
        
        for (int i = 1; i <= player[p1]->getBrdSize(); i++) {            
            
            cout<<"\t";//setw(5)<<' ';
            player[p1]->printGBoard(i);  // Print player 1's scorecard  
            cout<<"\t   ";
            player[p2]->printGBoard(i);  // Print player 2's scorecard
            cout<<endl;
        } 
        cout<<endl;        
        cout<<"\t"; player[p1]->getUppr();
        cout<<"\t   "; player[p2]->getUppr(); cout<<endl;
        cout<<"\t"; player[p1]->getLow(); 
        cout<<"\t   "; player[p2]->getLow();  cout<<endl;
        cout<<"\t"; player[p1]->getGTtl();
        cout<<"\t   "; player[p2]->getGTtl(); cout<<endl;
        
    } 
}


//******************************************
//      pause screen before game starts
//******************************************
void pause() {
    cout<<endl<<setw(5)<<' '<<"Press enter to continue.\n";   
    cin.get();
}
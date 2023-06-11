/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 03-28-23 @10 PM
 * Purpose:  yahtzee_v23.1_addPlayrArray

Comments: 
 * If it's your first time running this code, select 5 from the menu
   that runs in main(). This reset's the code by resetting the User's binary file, 
   userdata.dat. This way you can start with fresh code that I haven't tested on.
 * Yahtzee default construct will always create an array of players with a minimum
   of 2 players. If player choose 1 player, then the code won't show the 2nd
   player's scorecard.
 * Play() accepts a User object from main() and will only alter their hiScore
   if player1 wins and has a higher score then user's object. Player 1 represents
   the User object that was passed to play(). It is essential a shell object that 
   allows User to play without alter any of their actual values unless they win.

 v23.1:
 * Added  getNPlayer();  Get number of players
 * Aggregated 2 instances of ScoreCard in Yahtzee's private members. Made them
   static arrays.
 * Moved int *indx to Yahtzee's private members
 * Created an array of players inside of Yahtzee's default constructor 
   instead of inside play(). This way I can access player[] in other functions
 * Added for( pIndx<nPlayer) to control each player's turn
 * Reset values inside switch() default so it could jump out of all the loops 
   and print final scorecards. 
 * Added getUpLowSums() & void printFinalSC(string name="Player")
 * Removed bool clearance, leave in Yatzee 
   
 
 Admin/User To Do:  
 * Make getAllUsr() print outside of its function  
 * Destroy double ptr in Yahtzee class & in Admin class? 
 * Make readInput() read inputs from file again 
 * Add a bool variable to Admin as a flag for deleted records? 
 * DRY. Clean up repetitive code.
 * Have destructors do something other than cout a message. Program fails without them.
 
Yahtzee To Do: 
 * Make play() work with 2 players instead of 1
 * how to pass Dice dice[] from Yahtzee to ScoreCard?
 * Decided if we still need bool clearance, leave in Yatzee
 * Is there a way to put the rolling and display of dice in a function & call it in play()?
 * wrap code for finalSC() in a function
 * After all testing is finished change bonusMin to 63 and numRounds to 13.
 * Add const int MAX_ROUNDS = 13 in one of the classes
 
 Ask Lehr:
 * base class global const
 * inBin.read(&binEmail[0]  ...better way?
 * Admin **usrArr getAllUsrs()
 * do we need User in yahtzee private members just because a function is passing it
 * What is aggregate a class and only thing you want to add is functions?
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <cstdlib> // rand()
#include <ctime>   // time()
#include <string>  //string
#include <cstring> //c-strings
#include <cctype> // tolower()
using namespace std;  //STD Name-space where Library is compiled

//User Libraries
#include "User.h"
#include "Admin.h"
#include "Yahtzee.h"

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Function Prototypes

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));

    int choice = 0;
          
    cout<<"\n\n\tMenu\n"
        <<"1: Admin Login\n"
        <<"2: Sign Up\n"
        <<"3: User Login\n"
        <<"4: Play Yahtzee as a guest\n"
        <<"5: ReadInputFile()\n"
        <<"9: Exit\n"
        <<"Enter a number: ";
        cin>>choice;
        cin.ignore();
        
        switch(choice){
            
            case 1: // Admin login
            {
                Admin admin;
                admin.adminLogin();
                break;
            } 
            case 2: // User sign up for new account
            {
                User user1;
                user1.signUp();                 
                //user1.printUsr();
                break;
            }
            case 3:  // User login. If successful, then play game          
            {       
                Admin admin1;
                if(admin1.isUsrLogin()){
                    
                    cout<<"\n\nUser login was successful.\n"; 
                    //cout<<"\n inside main()";
                    //admin.printAdUsr();                    
                    
                    
                    // Create new User & copy admin values to user
                    User user2;
                    admin1.copy2Usr(user2);    
                    cout << "\nWelcome " << user2.getName();
                    user2.printUsr(); 
                    
                    // Create new instance of Yahtzee class
                    Yahtzee game1;
                                 
                       
                    // if user is winner & has new hiScore, then print their update record
                    if(game1.play(user2)) {                         
                        
                        //user2.printUsr();
                        user2.reWrtBin(admin1.getBegnFile()); // rewrites this record in binary & text files    
                        cout << "\nReading binary....";
                        admin1.findByIndx(user2.getNumRec());
                        admin1.printAdUsr();   
                    }                                                    
                }
                break;
            }             
            case 4: // Play Yahtzee as a guest
            {          
                User guest("Guest");  
                cout << "\nWelcome " << guest.getName();
                guest.printUsr(); 
                Yahtzee game2;                                                  
                game2.play(guest);
                break;
            }
            case 5: // Erase binary & text file, then read inputs to fill
                    // User binary with records. Used after testing & altering records.
            {
                User user5;
                user5.readInputFile(); 
                break;
            }
            default: 
            {
                cout<<"\nGood Bye.\n";                
                exit(0);
            }
        }
    
    return 0;
}
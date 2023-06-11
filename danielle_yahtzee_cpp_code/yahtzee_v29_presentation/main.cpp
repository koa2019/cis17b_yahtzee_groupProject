/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 04-24-23 @7 PM
 * Purpose:  yahtzee_v29_presentation
  
Comments to User:
 * For ease of use, when you login in as a user or admin I have printed  
   their login info to the screen. Type it in when prompted.  
 * If it's your first time running this code, select 5 from the menu
   that runs in main(). This reset's the code by resetting the User's binary file 
   to 5 records. This way you can start with fresh code that I haven't tested on.
 * Yahtzee default construct will always create an array of players with a minimum
   of 2 players. If player choose 1 player, then the code won't show the 2nd
   player's scorecard.
 * Play() accepts a User object from main() and will only alter their hiScore
   if player 1 wins AND has a higher score then user object's hiScore. 
   Player 1 represents the User object that was passed to play().
   It is essential a shell object that allows User to play without
   alter any of their actual values unless they win.

 v28.2:
 * Deleted findByIndx(). Instead getIndx() returns a valid indx and prints the
   usrArr[indx]
 * Changed findByEmail(). It doesn't read binary file anymore. It loops through
   userArr and compares its email member variable to the string that was passed 
   to its arguments.  
 * isUsrLogin() returns an int. indx or -66 when email is NOT found
 * startGame() passes record's location to Yhatzee, so it can rewrite the record
   inside of it rather than in main().
 * Overloaded printAdUsr(user2.getNumRec(), so it passes numRec
 * Cleaned up adminPortal() by putting each case in its own function
 * Deleted read1bin()
 * Destroyed double ptr in Admin class
 * Updated Admin with survey_v5's Admin class
 
 Admin/User To Do:  
 * Make User::readInputFile() read inputs from file again. isStrEqual() returns false. 
 * Add a bool variable to Admin as a flag for deleted records? 
 * DRY. Clean up repetitive code.
 * Have ~User do something other than cout a message. Program fails without it.
 
Yahtzee To Do: 
 * Destroy double ptr in Yahtzee class
 * Simplify getRules() 
 * After all testing is finished change bonusMin to 63 and MAX_ROUNDS to 13.
  
 Ask Lehr:
 * inBin.read(&binEmail[0]  ...better way?
 * Do we need User in yahtzee private members just because a function is passing it
 * How to aggregate a class when u only thing you want to add functions?
 * Destructors? when there is no dynamic memory to destroy?
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
void getUserLogin();


//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));

    int choice = 0;
    Admin admin;
    User user; 
    
    
    cout<<"\n\n\tMenu\n"
        <<"1: Admin Login\n"
        <<"2: Sign Up\n"
        <<"3: User Login\n"
        <<"4: Play Yahtzee as a guest\n"
        <<"5: Reset binary and text files\n"
        <<"9: Exit\n"
        <<"Enter a number: ";
        cin>>choice;
        cin.ignore();
        
        switch(choice){
            
            case 1: // Admin login
            {               
                admin.adminLogin();
                break;
            } 
            case 2: // User sign up for new account
            {
               
                user.signUp();
                //cout<<"\ninside main() after signUp() object looks like: ";
                //user.printUsr();
                break;
            }
            case 3:  // User login. If successful, then play game          
            {      
                getUserLogin();                
                break;
            }             
            case 4: // Play Yahtzee as a guest
            {          
                User guest("Guest"); 
                //cout<<"\ninside main() guest user object looks like: ";
                guest.printUsr();
                Yahtzee game2;                                                  
                game2.startGame(guest,0);
                break;
            }
            case 5:   // Reset files by erasing binary & text file, then creates records in 
            {        // User binary with records. Use after testing & altering records.    
                user.readInputFile(); 
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

// ***************FUNCTION DEFINITIONS************************
void getUserLogin(){
    
    Admin admin;
    User user;
    
    int indx = admin.isUsrLogin();
    
    if(!(indx == -66)){

        cout<<"\n\nUser login was successful.\n"; 
        cout<<"\ninside main() admin1 object looks like: ";
        admin.printAdUsr(indx);                    


        // Create new User & copy admin values to user                    
        admin.copy2Usr(user,indx);    
        cout << "\nWelcome " << user.getName();
        user.printUsr(); 

        // Create new instance of Yahtzee class
        Yahtzee game1;

        long recordLoc = admin.getBegnFile(indx);

        if(recordLoc<0){ cout << "\nError finding record location\n"; return; }

        // if user is winner & has new hiScore, then print their update record
        if(game1.startGame(user, recordLoc)) {                         

            //cout<<"\n\ninside main() user object looks like: ";
            //user.printUsr();                       

            admin.readBin_setArray();
            cout << "\nAdmin is reading updated binary file....\n";
            admin.printAdUsr(user.getNumRec());   
        }                                                    
    }
}
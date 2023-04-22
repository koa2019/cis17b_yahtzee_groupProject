/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 03-28-23 @10 PM
 * Purpose:  yahtzee_v22_updateYahtzeeWithIsmaels
  
 NOTE: WHEN YOU FIRST RUNNING THIS CODE, SELECT 5 FROM MENU, SO IT RESETS THE
       USERDATA.DAT FILE. THIS WAY YOU CAN START FRESH.
 
 v22:
 * Added Ismael's updated classes from ismael_yahtzee_v4.6
 
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
  
 Ask Lehr:
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
/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 03-28-23 @10 PM
 * Purpose:  yahtzee_v21_dblPlayrPtr_in_Yahtzee
 
 NOTE: WHEN YOU FIRST RUNNING THIS CODE, SELECT 5 FROM MENU, SO IT RESETS THE
       USERDATA.DAT FILE. THIS WAY YOU CAN START FRESH.
 
 v21:
 * In User class changed numRec from a static int to a regular int because it was messing up
   ttlRec when it moved between other .cpp pages.
 * Removed id variable from User class and everywhere else because it
   wasn't needed.
 * Fixed bug in reWrtTxt() by changing the number of charCount. Removing id variable
   changed the number of bits
 * Yahtzee's play(): if player1 wins, then it'll compare their current score to
   their hiScore saved in their record and change it accordingly.
 * A new hiScore will only rewrite binary & text files when user is logged in,
   so a guest player's new hiScore will not be saved to any files.
 * Used if(admin4.user.getName().compare(0,6,"xxxxxxx")) to stop admin from 
   editing a deleted record.
 * Fixed BUG when you delete more than 1 record in a session
   by adding delUsr. object to begnFile in Admin::deleteUsr().
 * Read user binary & print all Users. 
 
 To Do:  
 * Make getAllUsr() print outside of its function  
 * destroy double ptr in Yahtzee class & in Admin class? 
 * Make readInput() read inputs from file again 
 * Add a bool variable to Admin as a flag for deleted records? 
 * DRY. Clean up repetitive code. 
 
 Ask Lehr:
 * inBin.read(&binEmail[0]  ...better way?
 * Admin **usrArr getAllUsrs()
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <cstdlib> // rand()
#include <ctime>   // time()
#include <string> //string
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
                    
                    // Play game
                    bool isP1HiScore = game1.play(user2);                    
                       
                    // if user is winner & has new hiScore, then print their update record
                    if(isP1HiScore) {                         
                        
                        //user2.printUsr();
                        user2.reWrtBin(admin1.getBegnFile()); // rewrites this record in binary & text files    
                        cout << "\nUpdating binary....";
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
            case 5: // Read inputs to fill User binary with records
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
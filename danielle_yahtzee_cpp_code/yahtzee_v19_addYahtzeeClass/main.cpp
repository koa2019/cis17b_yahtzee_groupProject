/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 03-28-23 @10 PM
 * Purpose:  yahtzee_v19_addYahtzeeClass
 
 v19:
 * Added Ismael's Yahtzee, Score_Card, and Dice classes to main().
 * Added setUsrHiScore(score) & called it main() so it rewrite
 * User's binary and text files.
 
 Bugs: 
 * I wasn't able to create a new instance of User after they logged in
 * without creating a bunch of getUsrName(), getUsr..() in the main().
 * I lost direct contact with User members when I aggregated User
 * instead of inheriting it. 
 
 To Do: 
 * DRY. Clean up repetitive code.
 
 Ask Lehr:
 * inBin.read(&binEmail[0]  ...better way?
 
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
void getMenu();

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    Admin admin;
    //admin.printAdUsr();
    
    
    int choice = 0;
   
    cout<<"\n\n\tMenu\n"
        <<"1: Sign Up\n"
        <<"2: User Login\n"
        <<"3: Admin Login\n"
        <<"4: Play Yahtzee\n"
        <<"5: ReadInputFile()\n"
        <<"9: Exit\n"
        <<"Enter a number: ";
        cin>>choice;
        cin.ignore();
        
        switch(choice){
            case 1: // User sign up for new account
            {
                User user1;
                user1.signUp();                 
                //user1.print1User();
                break;
            }
            case 2:  // User login. If successful, then play game          
            {           
                User user2;
                if(admin.isUsrLogin(user2)){
                    
                    cout<<"\n\nUser login was successful.\n"; 
                    //cout<<"\nAdmin view";
                    //admin.printAdUsr();
                    
                    cout<<"\nWelcome "<<user2.getName();
                    user2.print1User();
                    
                    Yahtzee game1;
                    //game1.play();
                    int score = 100;
                    if(user2.isHiScore(score)){
                        
                        admin.setUsrHiScore(score);
                                   
                    } else { cout<<"\n\nGood Game!\n"; }
                }
                break;
            } 
            case 3: // Admin login
            {
                admin.adminLogin();
                break;
            } 
            case 4: // Play Yahtzee as a guest
            {      
                Yahtzee game2;
                game2.play();                
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

/**********  Function Definitions  **************/
void getMenu(){
    
}
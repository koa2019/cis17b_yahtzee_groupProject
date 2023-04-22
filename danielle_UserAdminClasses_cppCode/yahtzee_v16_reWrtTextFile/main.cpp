/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 03-28-23 @10 PM
 * Purpose: yahtzee_v16_reWrtTextFile
 
 v16: 
 * Rewrites 1 record in User text file after it rewrites binary.
 * Fixed bug in readInput() by creating 4 instances of User.
 * Fixed bug in findByIndx() by subtracting thisSum from cursor 
 * 
 * To Do:
 * BUG! in Delete a binary record. I can reset the record's variables to nothing, 
 * but it doesn't actually delete. Lehr said to just set it to zeros. 
 * But if you change the size of the anything it messes up the binary & text files.
 * Needs some sort of flag or something
 * 
 * Have Admin aggregate an instance of User instead of inherit it.
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

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Function Prototypes
void getMenu();

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    //rand()%90+10;//2 digit numbers
    Admin admin;
    User user;
    
    int choice = 0;
    
    //do {
    cout<<"\n\n\tMenu\n"
        <<"1: Sign Up\n"
        <<"2: User Login\n"
        <<"3: Admin Login\n"
        <<"4: ReadInputFile()\n"
        //<<"Press 5: \n"
        <<"9: Logout\n"
        <<"Enter a number: ";
        cin>>choice;
        cin.ignore();
        
        switch(choice){
            case 1:{ // User sign up for new account
               
                user.signUp();                 
                //user.print1User();
                break;
            }
            case 2:{              
                //Admin admin;            // Create one instance of Admin class                
                if(admin.isUsrLogin()){
                    cout<<"\n\nUser login was successful."; 
                    //cout<<"\nAdmin view";
                    //admin.printAdUsr();
                    User user2(admin.getTtlRec(), admin.getID(),admin.getName(),admin.getEmail(),admin.getPwrd());
                    //cout<<"User view";
                    user2.print1User();
                }
                break;
            } 
            case 3:{ // Admin login
                //Admin admin2;  // Create one instance of Admin class
                admin.adminLogin();
                break;
            } 
            case 4:{ 
                          
                //User user; // Create one instance of User class
                user.readInputFile(); // NOT WORKING PROPERLY
                break;
            }
            default: {
                cout<<"\nGood Bye.\n";                
                exit(0);
            }
        }
    
    return 0;
}

/**********  Function Definitions  **************/
void getMenu(){
    
}
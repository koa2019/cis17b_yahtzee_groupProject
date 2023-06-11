/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-24-2023 @ 1:36 PM
 * Purpose: yahtzee_v13_makeParentUserClass_scratched
 
 v13:
 * Changed class heirarchy: Admin inherits User. 
 * Added reWrtBin(int sizeOfRecord, long cursorPosition of this email).
 * BUG! Does NOT rewrite binary inside of reWrtBin().
  
 * 
 * To do:
 *      * PROBLEM: Static variable doesn't hold in between runs. 
                  Maybe need to write it a file and read it each time?
        * Why aren't my class variables green after moving them to 
 *        their own cpp file? 
        * May need to Ask how many players are going to play and create an array of users. 
        * Need to add a variable that keeps it count of how many records 
          are written every time the program runs. We are appending the files every time the 
          program runs. Static variable doesn't work in main() or in User class.
        * Test setHiScore(). It'll have to rewrite the binary file 
          @specific location.         
        * Once User profile is complete, create Admin class 
          and either copy User class or inherit User class.
          Then cut the code that reads binary from the User class 
          and only allow Admin class to read the binary file.       
        * Create a input file to read in dummy info.
 *      * Add max retries in user validation functions
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include <cstdlib>   // rand()
#include <ctime>    // time()
#include <string>   //string var
#include <cstring>  //c-strings
#include <cctype>  //c-string helper functions
#include <fstream> // input/output for files
using namespace std;  //STD Name-space where Library is compiled

//User Libraries
#include "User.h"   // Base class
#include "Admin.h"  // Admin class inherits User class

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

// Function Prototypes


/*****  Code Begins Execution Here with function main  ****/
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    // Variables    
    int choice = 0;
    
    Admin admin;  // Create one instance of Admin class
    
    //User user;    // Create one instance of User class
    
    cout<<"\n\nMenu\n"
        <<"Press 1: Sign Up\n"
        <<"Press 2: User Login\n"
        <<"Press 3: Admin Login\n"
        //<<"Press 4: Find one index\n"
        //<<"Press 5: Update Admin\n"
        <<"Press 9: Logout\n";
        cin>>choice;
        cin.ignore();
        
        switch(choice){
            case 1:{                
                //User user;    // Create one instance of User class
                //user.signUp();                
                break;
            }
            case 2:{
                admin.usrLogin();
                break;
            } 
            case 3:{
                //admin.getAdLogin();
                admin.adminLogin();
                break;
            } 
            case 4:{                
                //admin.findByIndx();
                break;
            }
            case 5:{
                //admin.updateAdmin();
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
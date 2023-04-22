/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-10-2023 @ 12:36 PM
 * Purpose:  yahtzee_v0_adminClass_broken
  
 v1:    
 * Is based off userClass_v7.
 * Changed User to Admin and moved it into its own .h and .cpp files.
 * Created specific functions that set,write,read Admin's login profile.
 * In main() asked Admin to login and then checked if their input matched the values in the Admin.dat file. 
 * If login was successful, then a menu runs, else exits program.
 * Made checkHiScore() return a int instead of bool. 
 
To do:
* Might need to add a id number variable to User's class, so it's easier
 to search for someone.
* Create a input file to read in dummy info.
* Need to add a variable that keeps it count of how many records 
  are written. We are appending the files every time the 
  program runs. Static variable doesn't work in main() or in User class.
* Test setHiScore(). It'll need to rewrite the binary file 
  @specific location. Maybe reading in the entire binary file 
  and save to an array? Probably needs to inherit User class. 
* Need to inherit User class.
  Then cut the code that reads binary from the final User class 
  and only allow Admin class to read the binary file.
* checkHiSCore() WILL NEED TO LOCATE THIS PLAYER'S SCORE IN BINARY or HAVE PLAYER SEND IT
  WITH THEIR CURRENT SCORE              
*/

//System Libraries
#include <iostream>   //Input/Output Library
#include <cstdlib>   // rand()
#include <ctime>    // time()
#include <string>   //string variable
#include <cstring>  // c-strings
#include <cctype>  // helper functions for c-strings
#include <fstream> // input/output for files
using namespace std;  //STD Name-space where Library is compiled

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

// Function Prototypes


//User Libraries
#include "Admin.h"


/*****  Code Begins Execution Here with function main  ****/
int main(int argc, char** argv) {
    
    //Set random number seed once here
    //srand(static_cast<unsigned int>(time(0)));
    //(rand()%(0+7));
    
    
    int choice=9,
        idNum=0;   
            
    Admin admin;

    admin.adminLogin();

    cout<<"\n\tAdmin Menu\n"
        <<"Press 1: Get User Database\n"
        <<"Press 2: Get 1 User's profile\n"
        <<"Press 3: Update Admin's login info\n"
        <<"Press 9: Exit.\n";
    cin>>choice;

    switch(choice){
        case 1:{
            cout<<"Print contents of data.txt ?\n";
            break;
        }
        case 2:{
            cout<<"Enter user's id number: ";
            idNum=1;
            admin.get1Record(idNum);
            break;
        }
        case 3: {
            // Update Admin's login profile 
            admin.updateAdminProfile();
            break;
        }
        default: {
            cout<<"\nLogged Out.\n";            
            exit(0);
        }
    }
    
        
    return 0;
}

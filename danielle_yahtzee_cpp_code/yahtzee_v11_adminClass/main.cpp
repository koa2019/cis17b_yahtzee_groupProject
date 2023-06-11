/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-24-2023 @ 1:36 PM
 * Purpose:  yahtzee group project-adminLogin v11
  
 v11:   
 * Added Admin class & moved all of User class to it, so Admin is parent class. User class will inherit Admin and add hiScore to its class.
 
 To do:
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
#include "Admin.h"
//#include "User.h"

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
    
    cout<<"\n\nMenu\n"
        <<"Press 1: Sign Up\n"
        <<"Press 2: User Login\n"
        <<"Press 3: Admin Login\n"
        <<"Press 9: Logout\n";
        cin>>choice;
     
        switch(choice){
            case 1:{
                cout<<"Create Account\n";
                admin.signUp();
                break;
            }
            case 2:{
                cout<<"Login\n";
                admin.login();
                break;
            } 
            case 3:{
                cout<<"Admin Login\n";
                //Admin admin;
                //admin.adminLogin();
                break;
            } 
            default: {
                cout<<"\nLogged Out.\n";                
                exit(0);
            }
        }
    
    
    
    /*********   READ BINARY FILE & RETURN 1 RECORD   ********/
    
    int nRecords = 0; // This is will need to retrieve this number from database
    int oneRec = nRecords; //(rand()%(0+nRecords)); // As of now there's 13 records in data file
    
    Admin oneAdmin;
        
    oneAdmin.find1Record(oneRec);
    
    cout<<"Found record "<<oneRec<<endl;
    oneAdmin.print1Profile();       
    
    return 0;
}

/**********  Function Definitions  **************/
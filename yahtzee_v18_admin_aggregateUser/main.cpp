/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 03-28-23 @10 PM
 * Purpose:  survey project v1
 * 
 * v1:
 * Admin inherits User
 * Added admin readBin(), wrtAdminTxt() & wrtAdminBin()
 * Fixed bug: Admin is crashing. Added a cout inside ~Admin().
 * Added 3 constructors for User. 
 * Added recSize & begnFile variables to Admin so it could  
 * hold their info when handling a binary record.
 * Admin can rewrite the value for hiScore in userData.dat when 
 * it uses findByEmail() to set records size & beginning file location.
 * Admin can rewrite one full binary record instead of just hiScoore.
 * Copied this folder to yahtzee_v15
 * 
 v15: is a copy of survey_v1
 * 
 v16: 
 * Rewrites 1 record in User text file after it rewrites binary.
 * Fixed bug in readInput() by creating 4 instances of User.
 * Fixed bug in findByIndx() by subtracting thisSum from cursor 
 * 
 v17:
 * changed findByEmail to return bool.
 * Edit binary finds the record by index instead of by email
 * Added getAllUsrs() to print all users from within the function,
 * BUT I want it to return a double pointer.
 * 
 *
 v18:
 * Admin aggregate an instance of User instead of inheriting it. Awful.
 * Removed code for getAllUsrs()
 * 
 * To Do: 
 * Add something to destructors other than a cout
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
    
    Admin admin;
    User user;
    
    int choice = 0;
   
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
            case 1: // User sign up for new account
            {
                user.signUp();                 
                //user.print1User();
                break;
            }
            case 2:             
            {             
                if(admin.isUsrLogin()){
                    cout<<"\n\nUser login was successful."; 
                    //cout<<"\nAdmin view";
                    //admin.printAdUsr();
                    User user2(user.getTtlRec(), user.getID(),user.getName(),user.getEmail(),user.getPwrd());
                    //cout<<"User view";
                    user2.print1User();
                }
                break;
            } 
            case 3: // Admin login
            {
                admin.adminLogin();
                break;
            } 
            case 4:
            {              
                //User user; // Create one instance of User class
                user.readInputFile(); // NOT WORKING PROPERLY
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
/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 03-28-23 @10 PM
 * Purpose:  yahtzee_v17_boolFindByEmail

 v17:
 * Changed findByEmail to return bool.
 * AdminPortal() case 4: Edit binary finds the record by index instead of by email
 * Added getAllUsrs() to print all users from within the function,
 * BUT I want it to return a double pointer.
 * 
 * To Do:
 * BUG! in Delete a binary record. I can reset the record's variables to nothing, 
 * but it doesn't actually delete. Lehr said to just set it to zeros. 
 * But if you change the size of the anything it messes up the binary & text files.
 * Needs some sort of flag or something to say it's been deleted. 
 * Add something to destructors other than a cout.
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
                    User user2(admin.getTtlRec(), admin.getID(),admin.getName(),admin.getEmail(),admin.getPwrd());
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
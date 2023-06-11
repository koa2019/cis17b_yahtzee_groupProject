/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-24-2023 @ 1:36 PM
 * Purpose:  yahtzee_v13_adminClass
 * 
 v13:
 * added reWrtBin(int sizeOfRecord, long cursorPosition of this email).
 * Does NOT rewrite. Someone sugguested using ios::ate and seekp().
 * Delete binary sugguestion was to copy files up to email to a temp.dat, 
 * skip the target record, then continue writing to temp.dat. 
 * Then delete usrData.dat and rename temp.dat to usrData.dat;
 * 
 * To do:
 * BUG! User is appending the new hiScore record to file instead 
        of inserting @its original spot. 
   Solution? --> figure out cursor size of this record or readBin then rewrite?
 * Why aren't my class variables green after moving them to 
   their own cpp file? 
 * Admin needs to delete record from binary --> pass cursor size?
 * Admin needs to edit member variable in binary          
 
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
#include "User.h"  // User class inherits Admin class

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

// Function Prototypes
//void getUsrLogin(Admin);

/*****  Code Begins Execution Here with function main  ****/
int main(int argc, char** argv) {
    
    // Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    // Variables    
    int choice = 0;
    
    //do {
    cout<<"\n\nMenu\n"
        <<"Press 1: Sign Up\n"
        <<"Press 2: User Login\n"
        <<"Press 3: Admin Login\n"
        <<"Press 4: Play Yahtzee\n"
        //<<"Press 5: \n"
        <<"Press 9: Logout\n";
        cin>>choice;
        cin.ignore();
        
        switch(choice){
            case 1:{ 
                User user;    // Create one instance of User class
                user.readInputFile();
                //user.signUp();                 
                break;
            }
            case 2:{ // I WANT TO SAVE THIS ADMIN TO A USER so i can play()
             
                Admin admin;  // Create one instance of Admin class
                if(admin.getUsrLogin()){
                    //admin.print1Record();
                    User user2(admin.getTtlRec(), admin.getID(),admin.getName(),admin.getEmail(),admin.getPwrd());
                    user2.play();
                } else {cout<<"\nUnable to locate your email.\n";}
                break;
            } 
            case 3:{
                Admin admin2;  // Create one instance of Admin class
                admin2.getAdLogin();
                break;
            } 
            case 4:{  
                //User user3;    // Create one instance of User class
                //user3.play();
                break;
            }
            default: {
                cout<<"\nLogged Out.\n";                
                exit(0);
            }
        }
    //} while(choice==1 || choice==2 || choice==3 || choice==4);
    return 0;
}

/**********  Function Definitions  **************/
//void getUsrLogin(Admin ad){
//       
//    if( ad.isUsrLogin() ) {
//        
//        // copy this admin record to a User
//        //u.play(); 
//    }
//    return;
//}
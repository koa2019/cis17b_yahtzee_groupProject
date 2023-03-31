/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-24-2023 @ 1:36 PM
 * Purpose:  yahtzee group project-adminLogin v12
 * 
 * v1:  Reads inputs from user and confirms them in main().
 *      If all inputs are valid, then it prints inputs.
 * 
 * v2:  Creates one name string, one email string, one password string.
 *      Adds functions that confirm each input meets certain criteria.
 *      Prints one name, one email, one password    
 * 
 * v3:  Writes & appends to text and binary file:
 *      size of name string, one name string,
 *      size of email string, one email string,
 *      size of password string, one password string.
 * 
 *      Reads first three strings in from binary file.
 * 
 * v4:  Reads in third record in from binary file
 *      by accumulating the size of each string.  
 *      Stops at the beginning of record 3.
 * 
 * v5:  At this point program can read in three strings and validate
 *      they meet certain requirements, saves the three variables, then
 *      it writes these 3 strings and their lengths to a text & binary file.
 *      The program opens binary file and looks for the third record in it.
 *      Once it finds the record it reads and saves the length of each string
 *      as well as the actual string. Since this is all working 
 *      I added a User class. It took a LOT of adjustments to get this working again.
 *      This version now does everything it was doing in version 4, 
 *      but now it saves the strings and their lengths inside of class.
 * 
 *      Writing and reading files runs in main(). I will them into functions 
 *      once I add a rand() to randRec.
 * 
 * v6:  Added a rand() to randRec, BUT I eventually need to figure out how many 
 *      records are in data.txt because Admin class will be the only one who has 
 *      permission to read the binary file, and they'll be looking for a specific  
 *      user rather than a random user.
 * 
 *      Added int hiScore=0 to class. Added getHiScore(), and
 *      added setHiScore(int score) that accepts a int and checks if is greater
 *      than the current hiScore.
 * 
 *      Wrote hiScore to text and binary.
 *      Confirmed hiScore is being read from binary file. 
 *      Created 1 instance of User class and saved the contents of 1 file that 
 *      was located in from the binary file. But I had to change how the 
 *      mutator member functions set the variables.
 * 
 * v7:  Sets a max number of user someone can add during 1 session.
 *    * Added a while loop to add 1-4 user's. 
 *    * Added a record count & used iy when writing to text file.
 *    * Changed password minSize to 7.
 *    * Put writing and reading to files in their own functions.
 *    * Fixed a bug when reading in ans by adding cin.ignore();
 *    * Add private member function that converts name & email to lowercase.
 *  
 * v8:  * Put v7 User class in a User.h and User.cpp.
 *      
 * v9:  * Clean up this version, so it's read for the group meeting on 3/24/23.
 *      * Added createProfile() to simplify code. Changed print1User().
 * 
 * v10: * Added unique id variable to class.
 *      * Added id to wrtTxt(), wrtBin() & readBin().
 *      * Created a menu with login or sign up options.
 *      * Added constructor #2 that passes a random number to set id with.
 *      * login() compares two strings, but NEEDS to search binary for an email.
 * 
 * v11:   Added Admin class & moved all of User class to it, so Admin is parent
 *        class. User class will inherit Admin and add hiScore to its class.
 
 v12:   
 * Adding a static member and static member() to fix 
   number of records counter. Added static void addTtlRec() to increment.
 * Fixed ttlRecs to hold in between runs by adding a text file that reads 
   total # records in & initiates it every time ADMIN constructor runs.
 * Added ttlRec to wrtTxt(),wrtBin(), readBin().
 * Added readInputFile() cause I was tired of doing it manually.
 * Moved signUp() & readInputFile() to User class.
 * Created adminPortal with a Admin Menu inside of the admin.cpp 
   so it could call private functions. You can only access this menu
   if you sign in correctly.
 * Add max retries in user validation functions
 * Added overloaded readBin() that accepts an email.
 * Added wrt1Record() and called it in both readBin()
 * Added wrtAdminTxt() & wrtAdminBin() as private Admin members
 * Added char arguments to wrtTxt()
 * Added a switch menu in main() with options to sign up, user login, admin login
 * Added number of rolls to User class
 * Fixed User overwriting ttlRec & ID by passing the values from Admin to
   User in  main().
 * Changed bool readBin() to long findEmail(), so I can pass the cursor
   when i need to rewrite a file in binary. If email is not found in
   binary, then it sets cursor to -99.
 
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
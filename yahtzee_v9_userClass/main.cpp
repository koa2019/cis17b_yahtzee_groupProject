/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-10-2023 @ 12:36 PM
 * Purpose:  yahtzee group project-userLogin v9
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
 * v8: Put v7 User class in a User.h and User.cpp.
 *      
 * v9:  Clean up this version, so it's read for the group meeting on 3/24/23.
 *      * Added createProfile() to simplify code. Changed print1User().
 * 
 * To do:
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
#include "User.h"


//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

// Function Prototypes


/*****  Code Begins Execution Here with function main  ****/
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    // Variables
    const int MAXACCTS=4; // Don't want a site to crash if someone created a bunch of profiles @once
    bool isAgain=true;
    char ans='n';
    int usrCount=0;  // counts number of profiles created in a single session
    
    User user;  // Create one instance of User class
    
    // Loop until user is finished entering number of players
    while(isAgain){
        
        user.createProfile();  // Create 1 profile with default constructor         
        
        // Conditional only allows a max number of profiles to be created
        cout<<"\nNumber of Accounts Created: "<<usrCount+1;
        
        if(usrCount+1 >= MAXACCTS) {
            
            cout<<"\nYou've reached maximum number of players you can create in 1 session.\n";
            isAgain=false;
            
        } else {
            
            cout<<"\nWould you like to create another user profile?\nY for yes or N for no.\n";
            cin>>ans;
            cin.ignore();
            
            // Checks if user wants to create another profile
            if(ans == 'y' || ans == 'Y'){                
                isAgain=true; 
                usrCount++;                            
            }                   
            else { isAgain=false; } 
        }
    } // Ends while loop
    
    
    /*********   READ BINARY FILE & RETURN 1 RECORD   ********/
    
    int nRecords = 17; // This is will need to retrieve this number from database
    int oneRec = nRecords; //(rand()%(0+nRecords)); // As of now there's 13 records in data file
    
    User oneUser;
        
    oneUser.find1Record(oneRec);
    
    cout<<"Found record "<<oneRec<<endl;
    oneUser.print1User();       
    
    return 0;
}

/**********  Function Definitions  **************/
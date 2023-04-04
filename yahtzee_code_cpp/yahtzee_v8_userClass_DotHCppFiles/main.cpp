/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-10-2023 @ 12:36 PM
 * Purpose:  yahtzee group project-userLogin v8
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

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

// Function Prototypes


//User Libraries
#include "User.h"




/*****  Code Begins Execution Here with function main  ****/
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    bool isNameGood, 
         isEmailGood,
         isPwrdGood;
      
    // Create 1 profile with default constructor 
    //User user; 
    //isNameGood  = user.setName();
    //isEmailGood = user.setEmail();
    //isPwrdGood  = user.setPwrd();
    //user.print1User(isNameGood, isEmailGood, isPwrdGood);
    
    
    // Create an multiply User's
    const int MAXPLYR = 4;
    bool isAgain = true;
    char ans = 'n';
    int recCnt = 0;
    
    // Loop until user is finished entering number of players
    User user;
    
    while(isAgain){
        
        isNameGood  = user.setName();
        isEmailGood = user.setEmail();
        isPwrdGood  = user.setPwrd();
        
        // Print 1 profile
        cout<<"\nrecCount "<<recCnt;
        user.print1User(isNameGood, isEmailGood, isPwrdGood);
        
         /********* START WRITING TO TEXT AND BINARY FILES  ********/
        user.wrtTxt(recCnt);
        user.wrtBin();                
        
        // Conditional only allows a max number of profiles to be created
        if(recCnt+1 >= MAXPLYR) {
            cout<<"\nYou've reached maximum number of players you can create in 1 session.\n";
            isAgain=false;
        } 
        else {
            cout<<"\nWould you like to create another user profile?\nY for yes or N for no.\n";
            cin>>ans;
            cin.ignore();
            
            // Checks if user wants to create another User
            if(ans == 'y' || ans == 'Y'){                
                isAgain=true; 
                recCnt++;                            
            }                   
            else { isAgain=false; } 
        }
    } // Ends while loop
    
    /*********   READ BINARY FILE & RETURN 1 RECORD   ********/
    int oneRec = 12; //(rand()%(0+7)); // As of now there's 8 records in data.txt
    
    User oneUser;
        
    oneUser.get1Record(oneRec);
    
    cout<<"\ninside main() "; 
    oneUser.print1User(true,true,true);
        
    //ifstream inTxt;
    //inTxt.open("data.txt",ios::in); // appends content to the current content of the file.
    //if(!inTxt.is_open()){ cout<<"\nError opening inTxt.txt\n";} 
    //inTxt.close();
    
    return 0;
}

/**********  Function Definitions  **************/
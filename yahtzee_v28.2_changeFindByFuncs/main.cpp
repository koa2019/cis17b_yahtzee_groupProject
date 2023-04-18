/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 04-16-23 @7 PM
 * Purpose:  survey project v28.2
 * 
Comments: 
 * If it's your first time running this code, select 5 from the menu
   that runs in main(). This reset's the code by resetting the User's binary file, 
   userdata.dat. This way you can start with fresh code that I haven't tested on.
 * Yahtzee default construct will always create an array of players with a minimum
   of 2 players. If player choose 1 player, then the code won't show the 2nd
   player's scorecard.
 * Play() accepts a User object from main() and will only alter their hiScore
   if player1 wins and has a higher score then user's object. Player 1 represents
   the User object that was passed to play(). It is essential a shell object that 
   allows User to play without alter any of their actual values unless they win.

 
survey v1:
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
 yahtzee v15: is a copy of survey_v1
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
 * 
 v19:
 * Added Ismael's Yahtzee, Score_Card, and Dice classes to main().
 
 * I wasn't able to create a new instance of User after they logged in
 * without creating a bunch of getUsrName(), getUsr..() in the main().
 * I lost direct contact with User members when I aggregated User
 * instead of inheriting it.
 * 
 * Added setUsrHiScore(score) & called it main() so it rewrite
 * User's binary and text files.
 * 
 * 
 v20:
 * Moved reWrtBin() and reWrtTxt() to User.cpp and passed beginFile to them.
 * Fixed bug in isUserLogin(). Forgot to reset hiScore in the obj.
 * Added conditional in AdminPortal() checks if a record is deleted,
   then don't allow them to edit hiScore.
 * Created an array of Users, so the game can run with 2 players. 
 * Altered play() in Yahtzee, so it accepts a double pointer, pointer and number of players.
   Play() also returns if player 1 is the winner or not.
 * In main() I made User rewrite their hiScore directly instead of having admin do it.
   
 v21:
 * In User class changed numRec from a static int to a regular int because it was messing up
   ttlRec when it moved between other .cpp pages.
 * Removed id variable from User class and everywhere else because it
   wasn't needed.
 * Fixed bug in reWrtTxt() by changing the number of charCount. Removing id variable
   changed the number of bits
 * Yahtzee's play(): if player1 wins, then it'll compare their current score to
   their hiScore saved in their record and change it accordingly.
 * A new hiScore will only rewrite binary & text files when user is logged in,
   so a guest player's new hiScore will not be saved to any files.
 * Used if(admin4.user.getName().compare(0,6,"xxxxxxx")) to stop admin from 
   editing a deleted record.
 * Fixed BUG when you delete more than 1 record in a session
   by adding delUsr. object to begnFile in Admin::deleteUsr().
 * Read user binary & print all Users.
 
 v22:
 * Added Ismael's updated classes from ismael_yahtzee_v4.6
   
 v23.1:
 * Added  getNPlayer();  Get number of players
 * Aggregated 2 instances of ScoreCard in Yahtzee's private members. Made them
   static arrays.
 * Moved int *indx to Yahtzee's private members
 * Created an array of players inside of Yahtzee's default constructor 
   instead of inside play(). This way I can access player[] in other functions
 * Added for( pIndx<nPlayer) to control each player's turn
 * Reset values inside switch() default so it could jump out of all the loops 
   and print final scorecards. 
 * Added getUpLowSums() & void printFinalSC(string name="Player")
 
 
 v23.2
 * Added isP1Winner(), printDice(), finalSC() so i could clean up play()
  
 v24:
 * Separated play() by creating startGame() to handle the number of rounds loop
   and play() can handle each player's turn individually.  
 * Tested this version as guest and 2 players. Works except for BUG1 listed below. 
 * Tested this version as guest and 1 player. Works except for BUG1 listed below. 
 * Added getUpLowSums() and printed them in printFinalSC()
 * readInput() reads inputs from file again 
 
 v25:
 * Fixed BUG in full_house conditional, by adding extra conditionals in it.
 
 v26:
 * Moved the creation of Dice dice[] and int diceArr[] from Yahtzee to ScorCard
   and then moved their code to their own functions: setDice() & pushThisDice().
 * Fixed BUG when exiting the game early by adding extra conditional with the
   rounds loop.  if(nPlayer > 1 && rnd < MAXRNDS).
 * Added selectDice() & selectCategory(), bool isNewHiScore() in Yahzee 
   to clean up the play().
 * Moved constant variables to the top of Classes h file
 * BUG: admin getAllUsr() not showing updating hiScore
 * fixed BUG: reWRtTxt() not working when indx is greater than 0 by
   not reading inputs from input.txt in readInputFile()?
 
 
 v27:
 * getAllUsr() returns a double pointer array with all the user's read from binary file
  
 v28.1:
 * Added Admin double ptr in private member & allocated memory for it in default
 * constructor. Set its values in readAllUsrs(). Now there's an array Admin can
 * reference anywhere in the class without having to read binary to look for a
 * record by index or email.
 * 
 v28.2:
 * Deleted findByIndx(). Instead getIndx() returns a valid indx and prints the
   usrArr[indx]
 * Changed findByEmail(). It doesn't read binary file anymore. It loops through
   userArr and compares its email member variable to the string that was passed 
   to its arguments.  
 * isUsrLogin() returns an int. indx or -66 when email is NOT found
 * startGame() passes record's location to Yhatzee, so it can rewrite the record
   inside of it rather than in main().
 * Overloaded printAdUsr(user2.getNumRec(), so it passes numRec
 * Cleaned up adminPortal() by putting each case in its own function
 * Deleted read1bin()
 * Destroyed double ptr in Admin class
 
 
 Admin/User To Do:  

 * Make readInput() read inputs from file again. isStrEqual() returns false. 
 * Add a bool variable to Admin as a flag for deleted records? 
 * DRY. Clean up repetitive code.
 * Have ~User do something other than cout a message. Program fails without it.
 
Yahtzee To Do: 
 * Destroy double ptr in Yahtzee class
 * Simplify getRules() 
 * After all testing is finished change bonusMin to 63 and MAX_ROUNDS to 13.
 
 
 Ask Lehr:
 * inBin.read(&binEmail[0]  ...better way?
 * Do we need User in yahtzee private members just because a function is passing it
 * How to aggregate a class when u only thing you want to add functions?
 * Destructors? when there is no dynamic memory to destroy?
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <cstdlib> // rand()
#include <ctime>   // time()
#include <string>  //string
#include <cstring> //c-strings
#include <cctype> // tolower()
using namespace std;  //STD Name-space where Library is compiled

//User Libraries
#include "User.h"
#include "Admin.h"
#include "Yahtzee.h"

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Function Prototypes

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));

    int choice = 0;
    Admin admin;
     
    cout<<"\n\n\tMenu\n"
        <<"1: Admin Login\n"
        <<"2: Sign Up\n"
        <<"3: User Login\n"
        <<"4: Play Yahtzee as a guest\n"
        <<"5: ReadInputFile()\n"
        <<"9: Exit\n"
        <<"Enter a number: ";
        cin>>choice;
        cin.ignore();
        
        switch(choice){
            
            case 1: // Admin login
            {
               
                admin.adminLogin();
                break;
            } 
            case 2: // User sign up for new account
            {
                User user1;
                user1.signUp();
                //cout<<"\ninside main() user1 object looks like: ";
                //user1.printUsr();
                break;
            }
            case 3:  // User login. If successful, then play game          
            {       
                //Admin admin1;
                int indx = admin.isUsrLogin();
                if(!(indx == -66)){
                    
                    cout<<"\n\nUser login was successful.\n"; 
                    cout<<"\ninside main() admin1 object looks like: ";
                    admin.printAdUsr(indx);                    
                    
                    
                    // Create new User & copy admin values to user
                    User user2;
                    admin.copy2Usr(user2,indx);    
                    cout << "\nWelcome " << user2.getName();
                    user2.printUsr(); 
                    
                    // Create new instance of Yahtzee class
                    Yahtzee game1;
                                 
                    long recordLoc = admin.getBegnFile(indx);
                    
                    if(recordLoc<0){ cout << "\nError finding record location\n"; break; }
                    
                    // if user is winner & has new hiScore, then print their update record
                    if(game1.startGame(user2, recordLoc)) {                         
                        
                        //cout<<"\n\ninside main() user2 object looks like: ";
                        //user2.printUsr();                       
                          
                        admin.readAllUsrs();
                        cout << "\nAdmin is reading binary file....\n";
                        admin.printAdUsr(user2.getNumRec());   
                    }                                                    
                }
                break;
            }             
            case 4: // Play Yahtzee as a guest
            {          
                User guest("Guest"); 
                //cout<<"\ninside main() guest user object looks like: ";
                guest.printUsr();
                Yahtzee game2;                                                  
                game2.startGame(guest,0);
                break;
            }
            case 5:   // Reset files by erasing binary & text file, then creates records in 
            {        // User binary with records. Use after testing & altering records.    
                User user5;
                user5.readInputFile(); 
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
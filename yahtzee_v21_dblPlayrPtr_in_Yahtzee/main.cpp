/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 03-28-23 @10 PM
 * Purpose:  survey project v1
 * 
 * survey v1:
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
 
 
 To Do: 
 
 * Make getAllUsr() print outside of its function
  
 * destroy double ptr in Yahtzee class & in Admin class?
 
 * Make readInput() read inputs from file again
 
 * Add a bool variable to Admin as a flag for deleted records?
 
 * DRY. Clean up repetitive code.
 
 
 Ask Lehr:
 * inBin.read(&binEmail[0]  ...better way?
 * Admin **usrArr getAllUsrs()
 * 
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
#include "Yahtzee.h"

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Function Prototypes

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));

    int choice = 0;
          
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
                Admin admin;
                admin.adminLogin();
                break;
            } 
            case 2: // User sign up for new account
            {
                User user1;
                user1.signUp();                 
                //user1.printUsr();
                break;
            }
            case 3:  // User login. If successful, then play game          
            {       
                Admin admin1;
                if(admin1.isUsrLogin()){
                    
                    cout<<"\n\nUser login was successful.\n"; 
                    //cout<<"\n inside main()";
                    //admin.printAdUsr();                    
                    
                    
                    // Create new User & copy admin values to user
                    User user2;
                    admin1.copy2Usr(user2);    
                    cout << "\nWelcome " << user2.getName();
                    user2.printUsr(); 
                    
                    // Create new instance of Yahtzee class
                    Yahtzee game1;
                    
                    // Play game
                    bool isP1HiScore = game1.play(user2);                    
                       
                    // if user is winner & has new hiScore, then print their update record
                    if(isP1HiScore) {                         
                        
                        //user2.printUsr();
                        user2.reWrtBin(admin1.getBegnFile()); // rewrites this record in binary & text files    
                        cout << "\nUpdating binary....";
                        admin1.findByIndx(user2.getNumRec());
                        admin1.printAdUsr();   
                    }                                                    
                }
                break;
            }             
            case 4: // Play Yahtzee as a guest
            {          
                User guest("Guest");    
                Yahtzee game2;                                                  
                game2.play(guest);
                break;
            }
            case 5: // Read inputs to fill User binary with records
            {
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
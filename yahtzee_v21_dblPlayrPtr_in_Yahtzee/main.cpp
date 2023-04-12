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
 * Moved reWrtBin() and reWrtTxt() to User.cpp and passed
 * beginFile to them.
 * 
 * Fixed bug in isUserLogin(). Forgot to reset hiScore in the obj.
 * 
 * Added conditional in AdminPortal() checks if a record is deleted,
 * then don't allow them to edit hiScore.
 * 
 * 
 * Created an array of Users, so the game can run with 2 players. 
 
 * Altered play() in Yahtzee, so it accepts a double pointer, pointer and number of players.
   Play() also returns if player 1 is the winner or not.
  
 * in main() I made User rewrite their hiScore directly instead of having admin do it.
   
   
 To Do: 
 * Figure out double pointers for 2 players inside of Yahtzee class
  
 * Added double pointer array so I can print all Users.
 
 * use string parse for -> if(usr4.user.getName()[0] == 'x'){
 
 * DRY. Clean up repetitive code.
 
 
 Ask Lehr:
 * inBin.read(&binEmail[0]  ...better way?
 * main() adm loosing ttlRec number inside of case 3
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
void getMenu();

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    
    
    int choice = 0;
    Admin admin;
    //admin.printAdUsr();    
    
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
                Admin admin3;
                admin3.adminLogin();
                break;
            } 
            case 2: // User sign up for new account
            {
                User user1;
                user1.signUp();                 
                //user1.print1User();
                break;
            }
            case 3:  // User login. If successful, then play game          
            {           
                User user2;
                if(admin.isUsrLogin(user2)){
                //if(admin.isUsrLogin()){
                    
                    cout<<"\n\nUser login was successful.\n"; 
                    //cout<<"\n inside main() Admin view";
                    //admin.printAdUsr();
                    
                    
                    //User user3;
                    //cout<<"\n adm record: " << admin.getUsrRec() <<endl;
                    //admin.copy2Usr(user3);
                    //cout<<"\nWelcome "<<user3.getName();
                    //user3.print1User();               
                    
                    
                    cout<<"\nWelcome "<<user2.getName();
                    user2.print1User();                    
                    Yahtzee game1;
                    
                    bool p1Winner = game1.play();

                    string msg = p1Winner ? "P1 wins!\n" : "P2 wins!";
                    cout<<msg<<endl;
                    
                    
//                    int score = 4;                     
//                    if(user2.isHiScore(score)) {
//                        
//                        //admin.setUsrHiScore(score); 
//                        user2.setHiScore(score);
//                        cout<<"\nNew High Score of "<<user2.getHiScore()<<"!\n";
//                        //cout<<"Updating binary....";
//                        user2.reWrtBin(admin.getBegnFile()); // rewrites this record in binary & text files    
//                        admin.findByIndx(user2.getTtlRec());
//                        cout<<"Updated profile: ";
//                        user2.print1User();   
//                    }                                   
//                    else { cout<<"\n\nGood Game!\n"; }

                }
                break;
            } 
            
            case 4: // Play Yahtzee as a guest
            {      
                int nPlayer = 2;
                
                // create a pointer to Player's structure and create array size of 2   
                User **player;
                
                // creating an array of Player pointers
                player = new User*[nPlayer];
                
                //array of index to keep track of each player
                int *indx = new int[nPlayer];

                // creating each individual player by calling Player constructor
                for (int i=0; i < nPlayer; i++) {         
                    indx[i]=i;
                }
    
                player[indx[0]] = new User("Guest","guest@email.com","G!23456");
                player[indx[1]] = new User("Computer","computer@email.com","C!23456");
    
                Yahtzee game2;
                                                  
//                bool p1Winner = game2.play(player,indx,nPlayer);
//               
//                string msg2 = p1Winner ? "P1 wins!\n" : "P2 wins!";
//                cout << msg2 << endl;
                
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

/**********  Function Definitions  **************/
void getMenu(){
    
}
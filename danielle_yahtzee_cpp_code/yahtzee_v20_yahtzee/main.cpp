/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 03-28-23 @10 PM
 * Purpose:  yahtzee_v20_yahtzee

 v20:
 * Moved reWrtBin() & reWrtTxt() to User.cpp and passed beginFile to them.
 * Fixed bug in isUserLogin(). Forgot to reset hiScore in the obj.
 * Added conditional in AdminPortal() checks if a record is deleted, then don't allow them to edit hiScore.
 * Created an array of Users, so the game can run with 2 players. 
 * Altered play() in Yahtzee, so it accepts a double pointer, pointer and number of players.
   Play() also returns if player 1 is the winner or not.
 * In main() I made User rewrite their hiScore directly instead of having admin do it.
      
 To Do: 
 * Figure out double pointers for 2 players inside of Yahtzee class  
 * Added double pointer array so I can print all Users. 
 * use string parse for -> if(usr4.user.getName()[0] == 'x'){ 
 * DRY. Clean up repetitive code. 
 
 Ask Lehr:
 * inBin.read(&binEmail[0]  ...better way?
 * main() adm loosing ttlRec number inside of case 3
 
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
                    //game1.play();                    
                    int score = 4;                     
                    if(user2.isHiScore(score)) {
                        
                        //admin.setUsrHiScore(score); 
                        user2.setHiScore(score);
                        cout<<"\nNew High Score of "<<user2.getHiScore()<<"!\n";
                        //cout<<"Updating binary....";
                        user2.reWrtBin(admin.getBegnFile()); // rewrites this record in binary & text files    
                        admin.findByIndx(user2.getTtlRec());
                        cout<<"Updated profile: ";
                        user2.print1User();   
                    }                                   
                    else { cout<<"\n\nGood Game!\n"; }
                    
//                    int nPlayer = 2;
//                
//                    // create a pointer to Player's structure and create array size of 2   
//                    User **player;
//
//                    // creating an array of Player pointers
//                    player = new User*[nPlayer];
//
//                    //array of index to keep track of each player
//                    int *indx = new int[nPlayer];
//
//                    // creating each individual player by calling Player constructor
//                    for (int i=0; i < nPlayer; i++) {         
//                        indx[i]=i;
//                    }
//
//                    player[indx[0]] = new User("Guest","guest@email.com","G!23456");
//                    player[indx[1]] = new User("Computer","computer@email.com","C!23456");
//
//                    bool p1Winner = game1.play(player,indx,nPlayer);
//
//                    string msg = p1Winner ? "P1 wins!\n" : "P2 wins!";
//                    cout<<msg<<endl;
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
                                                  
                bool p1Winner = game2.play(player,indx,nPlayer);
               
                string msg2 = p1Winner ? "P1 wins!\n" : "P2 wins!";
                cout << msg2 << endl;
                
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
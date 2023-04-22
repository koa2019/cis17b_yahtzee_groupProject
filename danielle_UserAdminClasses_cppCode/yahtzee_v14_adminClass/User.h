/* File:   User.h
 * Author: Danielle F
 * Created:March 22, 2023, 10:42 PM
*/

#ifndef USER_H
#define USER_H
#include "Admin.h" // User inherits Admin class

using namespace std;  //STD Name-space where Library is compiled

class User : public Admin {
    
private:
    int nRolls;
    
public:
    
    // Default constructor
    User(){
        cout<<"\nHit User constructor.\n";
        nRolls = 3;
    }
    User(int,int,string,string,string);// Constructor #2
    
        
    // Destructor
    ~User(); 

    // Mutators
    void setNRolls(int n){nRolls = n;}
    void signUp();  // Calls functions to create 1 or more profiles
    void readInputFile();  // Reads 27 records from a file
    void play();
    
    // Accessors
    int getNRolls() const {return nRolls;}
    void print1User() const;  // prints User obj and nRolls
};
#endif /* USER_H */


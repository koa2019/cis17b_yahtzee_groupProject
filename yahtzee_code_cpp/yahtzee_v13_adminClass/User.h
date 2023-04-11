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
        nRolls = 3;
        cout<<"\nHit User constructor.\n";
    }

    // Constructor #2
    User(int rec, int i, string n, string e, string p){
        setTtlRec(rec);
        setID(i);
        setName(n);
        setNamSiz(n.size());
        setEmail(e);
        setEmaiSiz(e.size());
        setPwrd(p);
        setPwrdSiz(p.size());
        nRolls = 3;
    }
        
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


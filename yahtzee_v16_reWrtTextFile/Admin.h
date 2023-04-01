/* File:   Admin.h
 * Author: DanYell
 *
 * Created on March 28, 2023, 11:00 PM
 */

#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
#include <string>
#include <iostream>
using namespace std;  //STD Name-space where Library is compiled

class Admin : public User {
    
private:
    int recSiz;   // record's number of bits
    long begnFile; // Cursor is the beginning of this record
public:
    Admin(){
        cout<<"Hit Admin Default Constructor\n";
        recSiz=0;
        begnFile=0;
        
    }
    Admin(string n, string e, string p) : User(n, e, p) {
        //cout<<"Hit Admin Constructor\n";
        recSiz=0;
        begnFile=0;
    }
    ~Admin(){ cout<<"\nHit Admin Destructor().";}
    
    // Mutator
    void setRecSiz(int n){ recSiz = n;}
    void setCursLoc(int n){ begnFile = n;}
    
    // Admin
    void adminLogin();
    void adminPortal();
    void readAdBin(); // ReadS binary file & locate file by index
    void wrtAdTxt();
    void wrtAdBin();
    void updateAdmin();
    
    // Reading User binary file
    bool isUsrLogin(); // Calls functions to verify login credentials
    void findByUsrIndx(int); // Reads userData.dat   
    void findByEmail(string); // Reads binary file & locate file by email
    void read1Bin(); // read this file binary & save
    void reWrtBin();
    void reWrtTxt();
    
    // Accessors
    void print1Admin()const;
    void printUser() const; // prints all members in a record
    
    
};
#endif /* ADMIN_H */


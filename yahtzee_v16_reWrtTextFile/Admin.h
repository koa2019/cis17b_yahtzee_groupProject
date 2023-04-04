/* File:   Admin.h
 * Author: DanYell
 *
 * Created on March 28, 2023, 11:00 PM
 */

#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include <iostream>
#include "User.h"
using namespace std;  //STD Name-space where Library is compiled

class Admin : public User {
    
private:
    int recSiz;   // record's number of bits
    long begnFile; // Cursor is the beginning of this record
public:
    Admin(){
        //cout<<"Hit Admin Default Constructor\n";
        recSiz = 0;
        begnFile = 0;
        
    }
    Admin(string n, string e, string p) : User(n, e, p) {
        //cout<<"Hit Admin Constructor\n";
        recSiz = 0;
        begnFile = 0;
    }
    ~Admin(){ cout<<"\nHit Admin Destructor().";}
    
    // Mutator
    void setRecSiz(int n){ recSiz = n;}
    void setBegnFile(int n){ begnFile = n;}
    void deleteUsr();
    
    // Admin
    void adminLogin();
    void adminPortal();
    void readAdBin(); // ReadS binary file & locate file by index
    void wrtAdTxt();
    void wrtAdBin();
    void updateAdmin();
    
    // Reading User binary file
    bool isUsrLogin();        // Calls functions to verify login credentials
    void findByIndx(int);     // Reads binary file to search for an index
    void findByEmail(string); // Reads binary file to search for an email
    void read1Bin();   // read this file's record in binary file & save to class object
    void reWrtBin();  // Rewrite 1 record in User's binary file
    void reWrtTxt();  // Rewrite 1 record in User's text file
    
    // Accessors
    int getRecSiz(){ return recSiz;}
    int getBegnFile(){ return begnFile;}
    void print1Admin()const;  // Print admin's login info
    void printAdUsr() const; // prints all members in an Admin + User's record
  
};
#endif /* ADMIN_H */


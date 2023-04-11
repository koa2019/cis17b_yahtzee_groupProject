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
    int recSiz;    // record's number of bits
    long begnFile; // Beginning bit location of this file in binary
public:
    Admin();
    Admin(string n, string e, string p);    
    Admin(int);
    ~Admin(){ cout<<"\nHit Admin Destructor().";}
    
    // Mutator
    void setRecSiz(int n){ recSiz = n;}
    void setBegnFile(int n){ begnFile = n;}
    void deleteUsr(); // deletes User in binary file
    
    // Access Admin binary & text files
    void adminLogin();  // checks admin login 
    void adminPortal(); // if Admin is logged in, then display menu
    void readAdBin();   // ReadS binary file & locate file by index
    void wrtAdTxt();    // write to Admin text file
    void wrtAdBin();    // write to Admin binary file
    void updateAdmin(); // Update Admin's record
    
    // Access User binary & text files
    bool isUsrLogin();        // Calls functions to verify login credentials
    void findByIndx(int);     // Reads binary file to search for an index
    bool findByEmail(string); // Reads binary file to search for an email
    void read1Bin();   // read this file's record in binary file & save to class object
    void reWrtBin();  // Rewrite 1 record in User's binary file
    void reWrtTxt();  // Rewrite 1 record in User's text file
    
    // Accessors
    int getRecSiz(){ return recSiz;}
    int getBegnFile(){ return begnFile;}
    void getIndex(int &); 
    void print1Admin()const;  // Print Admin's login info
    void printAdUsr() const; // prints all member variable's in an Admin + User's record
    void getAllUsrs(Admin **);
    Admin **getAllUsrs();
};
#endif /* ADMIN_H */


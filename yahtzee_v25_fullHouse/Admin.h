/* File:   Admin.h
 * Author: DanYell
 * Created on March 28, 2023, 11:00 PM
*/

#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include <iostream>
#include "User.h"   // Admin aggregates instance of User
using namespace std;  //STD Name-space where Library is compiled

class Admin {
    
private:
    int recSiz;    // record's number of bits
    long begnFile; // Beginning bit location of this file in binary
    User user;   // Admin aggregates instance of User
    
public:
    Admin();
    Admin(string, string, string );    
    Admin(int);
    ~Admin(){ cout<<"\nHit Admin Destructor()."; }
    void copy2Usr(User &);  // copy Admin variables to intance of User
    
    
    // Mutator
    void setRecSiz(int n){ recSiz = n;}
    void setBegnFile(int n){ begnFile = n;}
    void deleteUsr(); // deletes User in binary file
    
    
    // Reads & writes Admin binary & text files
    void adminLogin();  // checks admin login 
    void adminPortal(); // if Admin is logged in, then display menu
    void readAdBin();   // ReadS binary file & locate file by index
    void wrtAdTxt();    // write to Admin text file
    void wrtAdBin();    // write to Admin binary file
    void updateAdmin(); // Update Admin's record
    
    
    // Reads User binary & text files
    bool isUsrLogin();        // Calls functions to verify login credentials
    void findByIndx(int);     // Reads binary file to search for an index
    bool findByEmail(string); // Reads binary file to search for an email
    void read1Bin();   // read this file's record in binary file & save to class object
  
    
    // Accessors
    int  getRecSiz(){ return recSiz;}
    int  getBegnFile(){ return begnFile;}
    void getIndex(int &);
    void print1Admin()const;  // Print Admin's login info
    void printAdUsr() const; // prints all member variable's in an Admin + User's record
    void getAllUsrs(Admin **);
    Admin **getAllUsrs();
    
    
    // Calls aggregated member functions from User class
    void setUsrHiScore(); // Reassign hiScore in User and rewrite in binary & text files
    
};
#endif /* ADMIN_H */
/* File:   Admin.h
 * Author: DanYell
 * Created on March 28, 2023, 11:00 PM
*/

#ifndef ADMIN_H
#define ADMIN_H
#include <string>     // string var
#include <iostream> // convert int to string type
#include <iomanip>  // setw()
#include <fstream>  // fstream
#include "User.h"   // Admin aggregates instance of User
using namespace std;  //STD Name-space where Library is compiled

class Admin {
    
private:
    
    int totalRec;  // total records
    int recSiz;    // record's number of bits
    long begnFile; // Beginning bit location of this file in binary
    User user;   // Admin aggregates instance of User
    Admin **usrArr = nullptr;
    
public:
    
    Admin();     // Default constructor
    Admin(int); // Constructor #2                
    Admin(string, string, string ); // Constructor #3   
    ~Admin();   // Destructor
    void copy2Usr(User &,const int);  // copy Admin variables to instance of User
    
    
    // Mutator
    void setRecSiz(int n){ recSiz = n;}
    void setBegnFile(int n){ begnFile = n;}
    void deleteUsr(); // deletes User in binary file
    void setUsrHiScore();
    
    // Reads & writes Admin binary & text files
    int isUsrLogin();        // Calls functions to verify login credentials
    void adminLogin();  // checks admin login 
    void adminPortal(); // if Admin is logged in, then display menu   
    void readBin_setArray(); // reads User's binary file
    void readAdBin();   // ReadS binary file & locate file by index
    void wrtAdTxt();    // write to Admin text file
    void wrtAdBin();    // write to Admin binary file
    void updateAdmin(); // Update Admin's record
    
    // Accessors
    int  getRecSiz(){ return recSiz;}
    int  getBegnFile(){ return begnFile;}
    int  getBegnFile(const int indx){ return usrArr[indx]->begnFile;}
    void getIndex(int &);
    void getByEmail(); // adminPortal() calls it
    bool findByEmail(string, int &); // isUsrLogin() calls it
    void print1Admin()const;  // Print Admin's login info
    void printAdUsr() const; // prints all member variable's in an Admin + User's record
    void printAdUsr(int) const; // passes indx to print
    void printAllUsr() const;  // prints usrArr[]  
    void pause(char ch='c');      
};
#endif /* ADMIN_H */
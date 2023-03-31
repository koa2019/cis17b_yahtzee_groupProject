/* File:   Admin.h
 * Author: DanYell
 * Created:March 24, 2023, 1:36 PM
 */

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <fstream>
#include <string> 
using namespace std; //STD Name-space where Library is compiled

class Admin {
   
private: // ONLY Admin has access to these member functions 
    
    void adminLogin();
    bool isUsrLogin(); // Calls functions to verify login credentials
    void updateAdmin();
    void readBin(const char, int); // ReadS binary file & locate file by index
    long findEmail(const char, string, int &); // ReadS binary file & locate file by email
    void read1Bin(const char, long cursor=0L); // read this file binary & save
    void wrtAdminTxt();
    void wrtAdminBin();

protected:  // Derived classes will have direct access to these member variables
    
    static int ttlRec; // static variable to keep track on total records in file
    int id; // unique I.D. number
    unsigned short namSiz; // length of name string
    string name; // name 
    unsigned short emaiSiz; // length of email string
    string email; // email
    unsigned short pwrdSiz; // length of password string
    string password; // password 
    int hiScore; // player's highest score  

public:

    Admin();    // Default constructor
    ~Admin();  // Destructor

    // Mutators   
    void setID(int num) {id = num;}
    void setNamSiz(int size){  namSiz = size; }
    void setEmaiSiz(int size){ emaiSiz = size; }
    void setPwrdSiz(int size){ pwrdSiz = size; }
    void setName(string str){  name = str; }
    void setEmail(string str){ email = str; }
    void setPwrd(string str){  password = str;}
    void setHiScore(int s) { hiScore = s; }
    
     
    // Validates user input before setting member variable
    bool isName();
    bool isEmail();
    bool isPwrd();
    bool isHiScore(int score = 0); // Checks if score is higher than current hiScore

    // ! MIGHT MOVE THESE TO Protected/private !
    // Helper functions for validating member variables      
    bool isMinSize(string, int size = 2);
    bool isStrEqual(string, string);
    bool hasSpecialChars(string);
    bool confrmEmail(string);
    string toLowerCase(string);

    // Write to files
    void wrtTxt();
    void wrtBin();
    void reWrtBin(int,long);
    
    // Accessors 
    int getID() const { return id;}
    int getTtlRec() const { return ttlRec;}
    int getHiScore() const {return hiScore;}
    unsigned short getNamSiz() const {return namSiz; }
    unsigned short getEmaiSiz() const { return emaiSiz; }
    unsigned short getPwrdSiz() const {return pwrdSiz;}
    string getName() const {return name;}
    string getEmail() const {return email;}
    string getPwrd() const { return password; }
    void print1Record() const;
    
    // Calls private member functions
    bool getUsrLogin(){        
        if(! isUsrLogin() ){ return false;} 
        else { return true;}        
    }
    void getAdLogin() { adminLogin(); }
    void adminPortal();
       
   

    // static member functions
    static void setTtlRec(int num) { ttlRec = num; }
    static void addTtlRec(); // Static member()
    static void readTtlRec();   // Read total number of records from file
    static void wrtTtlRec();    // Write the total number of records in UsrData.bin
};
#endif /* ADMIN_H */


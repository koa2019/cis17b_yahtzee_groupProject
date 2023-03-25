/* File:   Admin.h
 * Author: DanYell
 * Created:March 24, 2023, 1:36 PM
*/

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <fstream>
#include <string> 
using namespace std;  //STD Name-space where Library is compiled

class Admin {
    
private:
    static int ttlRec;       // static variable to keep track on total records in file
    int id;                  // unique I.D. number
    unsigned short namSiz;  // length of name string
    string name;            // name 
    unsigned short emaiSiz; // length of email string
    string email;           // email
    unsigned short pwrdSiz; // length of password string
    string password;       // password 
    int hiScore;           // player's highest score  
  
    public:
        
    // ONLY ADMIN has this ability. 
    void readBin(const char, int); // ReadS binary file. 
    void setHiScore(int s)   { hiScore = s;}     
    bool checkHiScore(int score=0); // Checks if score is higher than current hiScore
    void adminLogin();
    void updateAdmin();
    void wrtAdminTxt();
    void wrtAdminBin();
    void getAdminBin();
        


    Admin();    // Default constructor
    Admin(int); // Constructor #2
    ~Admin();   // Destructor


    // Mutators     
    void setID(int num)      { id = num;}      
    void setNamSiz(int size) { namSiz = size;}
    void setEmaiSiz(int size){ emaiSiz = size;}
    void setPwrdSiz(int size){ pwrdSiz = size;}
    void setName (string str){ name = str;}  
    void setEmail(string str){ email = str;}  
    void setPwrd (string str){ password = str;}        

    // Validates user input before setting member variable
    bool isName();  
    bool isEmail(); 
    bool isPwrd();  

    // ! MIGHT MOVE THESE TO PRIVATE !
    // Helper functions for validating member variables      
    bool isMinSize(string ,int size=2);
    bool isStrEqual(string,string);
    bool hasSpecialChars(string);
    bool confrmEmail(string);   
    string toLowerCase(string);

    // Write to files
    void wrtTxt(const char);
    void wrtBin(const char);

    // Accessors  
    int getID()      const { return id;}   
    int getTtlRec()  const { return ttlRec;}
    int getHiScore() const { return hiScore;}
    unsigned short getNamSiz() const { return namSiz;}
    unsigned short getEmaiSiz() const { return emaiSiz;}
    unsigned short getPwrdSiz() const { return pwrdSiz;}
    string getName()  const { return name;}
    string getEmail() const { return email;}
    string getPwrd()  const { return password;}     
    void signUp();      // Calls functions to create 1 or more profiles
    void usrLogin();    // Calls functions to verify login credentials
    void getAdLogin();    // Calls functions to verify login credentials
    void findByIndx();  // Calls private member() that reads Binary file
    void print1Profile() const; 
    void readInputFile();
    
    // static member functions
    static void setTtlRec(int num) { ttlRec = num;}
    static void addTtlRec(); // Static member()
};
#endif /* ADMIN_H */


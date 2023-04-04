/*File:   User.h
 * Author: DanYell
 *
 * Created on March 28, 2023, 10:11 PM
 */

#ifndef USER_H
#define USER_H
#include <string> 
#include<iostream>
using namespace std;  //STD Name-space where Library is compiled

class User {
    
protected:
    static int ttlRec; // static variable to keep track on total records in file
    int id; // unique I.D. number
    unsigned short namSiz; // length of name string
    string name; // name 
    unsigned short emaiSiz; // length of email string
    string email; // email
    unsigned short pwrdSiz; // length of password string
    string password; // password 
    int hiScore;
    
public:
    
    User();    
    User(string,string,string);
    User(int,string,string,string);
    User(int,int,string,string,string);
    ~User(){cout<<"\nHit User Destructor()."; }
    
    // Mutators   
    void setID(int num) {id = num;}
    void setNamSiz(int size){  namSiz = size; }
    void setEmaiSiz(int size){ emaiSiz = size; }
    void setPwrdSiz(int size){ pwrdSiz = size; }
    void setName(string str){  name = str; namSiz = name.size(); }
    void setEmail(string str){ email = str; }
    void setPwrd(string str){  password = str;}
    void setHiScore(int s) { hiScore = s; }
    
    // Create new User 
    void signUp();  // Calls functions to create 1 or more profiles
    void readInputFile();  // Reads 27 records from a file
    
    // Validates user input before setting member variable
    bool isName();
    bool isEmail();
    bool isPwrd();
    
    
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
    void print1User() const;  // User friendly print out
    void print1URec() const;
    
    // static member functions
    static void setTtlRec(int num) { ttlRec = num; }
    static void addTtlRec(); // Static member()
    static void readTtlRec();   // Read total number of records from file
    static void wrtTtlRec();    // Write the total number of records in UsrData.bin
};

#endif /* USER_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.h
 * Author: DanYell
 *
 * Created on March 27, 2023, 2:33 PM
 */

#ifndef USER_H
#define USER_H
#include <iostream>
#include <fstream>
#include <string> 
using namespace std;  //STD Name-space where Library is compiled

class User {
    
protected:
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
        
    
        
    bool checkHiScore(int score=0); // Checks if score is higher than current hiScore
    void setHiScore(int s)   { hiScore = s;}     


    User();    // Default constructor
    User(int); // Constructor #2
    ~User();   // Destructor


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
    
    void print1Profile() const; 
    void readInputFile();
    
    // static member functions
    static void setTtlRec(int num) { ttlRec = num;}
    static void addTtlRec(); // Static member()
};
#endif /* USER_H */


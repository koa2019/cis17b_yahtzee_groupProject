/* File:   Admin.h
 * Author: DanYell
 * Created:March 24, 2023, 1:36 PM
*/

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string> 
#include <fstream>
using namespace std;  //STD Name-space where Library is compiled

class Admin {
    private:
        int id=0;                // unique I.D. number
        unsigned short namSiz=0; // length of name string
        string name="";          // name 
        unsigned short emaiSiz=0; // length of email string
        string email="";          // email
        unsigned short pwrdSiz=0; // length of password string
        string password="";       // password 
        int hiScore=0;            // player's highest score       
               
    public:
       
        Admin();     // Default constructor
        Admin(int);   // Constructor #2
        ~Admin();    // Destructor
        
        
        // Mutators     
        void setID(int num)      { id = num;}
        void setHiScore(int s)   { hiScore = s;}       
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
        
        // Helper functions for validating member variables      
        bool isMinSize(string ,int=0);
        bool isStrEqual(string,string);
        bool hasSpecialChars(string);
        bool confrmEmail(string);
        bool checkHiScore(int score=0); // Checks if score is higher than current hiScore
        string toLowerCase(string);
        
        // Writing a profile to files
        void wrtTxt(int);
        void wrtBin();
        
        // Reading binary. !!!Make Private if Admin is base class!!!
        void find1Record(int);
        
      
        // Accessors
        void readInputFile();
        void signUp();
        void login();
        int getID()      const { return id;}   
        int getHiScore() const { return hiScore;}
        unsigned short getNamSiz() const { return namSiz;}
        unsigned short getEmaiSiz() const { return emaiSiz;}
        unsigned short getPwrdSiz() const { return pwrdSiz;}
        string getName()  const { return name;}
        string getEmail() const { return email;}
        string getPwrd()  const { return password;}        
        void print1Profile() const; 
};

#endif /* ADMIN_H */


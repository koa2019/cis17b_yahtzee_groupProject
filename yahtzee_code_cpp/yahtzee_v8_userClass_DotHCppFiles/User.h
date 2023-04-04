/* File:   User.h
 * Author: Danielle F
 * Created on March 22, 2023, 10:42 PM
*/

#ifndef USER_H
#define USER_H
//#include <string> 
using namespace std;  //STD Name-space where Library is compiled

class User {
    private:
        unsigned short namSiz = 0;
        string name = "";    
        unsigned short emaiSiz = 0;
        string email = "";    
        unsigned short pwrdSiz = 0;
        string password = ""; 
        int hiScore = 0;
        
        // Private Mutators
        void setNamSiz(int size) { namSiz = size;}
        void setEmaiSiz(int size){ emaiSiz = size;}
        void setPwrdSiz(int size){ pwrdSiz = size;}
        void setHiScore(int s){ hiScore = s;}       
        string setToLower(string);
        
    public:
       
        User();     // Default constructor
        ~User();    // Destructor
        
        // Mutators
        bool setName();  // Validates user input before setting member variable
        bool setEmail(); // Validates user input before setting member variable
        bool setPwrd();  // Validates user input before setting member variable
        
        // For reading from binary
        void setName (string str){ name=str;}  // 
        void setEmail(string str){ email=str;}  // 
        void setPwrd (string str){ password=str;}  // 
        
        bool isMinSize(string , int);
        bool isStrEqual(string, string);
        bool hasSpecialChars(string);
        bool confrmEmail(string);
        bool checkHiScore(int score=0); // Checks if score is higher than current hiScore
        void wrtTxt(int);
        void wrtBin();
        void get1Record(int);
        //User *get1Record(int);
        
        // Accessors   
        unsigned short getNamSiz() const { return namSiz;}
        unsigned short getEmaiSiz() const { return emaiSiz;}
        unsigned short getPwrdSiz() const { return pwrdSiz;}
        string getName() const  { return name;}
        string getEmail() const { return email;}
        string getPwrd() const  { return password;}
        //int getNRecord() const { return nRecord;}
        int getHiScore() const  { return hiScore;}
        void print1User (bool,bool,bool) const; 
};

#endif /* USER_H */


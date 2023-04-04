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
        unsigned short namSiz=0; // length of name string
        string name="";          // name 
        unsigned short emaiSiz=0; // length of email string
        string email="";          // email
        unsigned short pwrdSiz=0; // length of password string
        string password="";       // password 
        int hiScore=0;            // player's highest score       
               
    public:
       
        User();     // Default constructor
        ~User();    // Destructor        
        
        // Mutators           
        void setHiScore(int s)   { hiScore = s;}       
        void setNamSiz(int size) { namSiz = size;}
        void setEmaiSiz(int size){ emaiSiz = size;}
        void setPwrdSiz(int size){ pwrdSiz = size;}
        void setName (string str){ name=str;}  
        void setEmail(string str){ email=str;}  
        void setPwrd (string str){ password=str;}        
       
        // Validates user input before setting member variable
        void createProfile();
        bool isName();  
        bool isEmail(); 
        bool isPwrd();  
        
        // Helper functions for creating a new profile        
        bool isMinSize(string ,int=0);
        bool isStrEqual(string,string);
        bool hasSpecialChars(string);
        bool confrmEmail(string);
        string toLowerCase(string);
        bool checkHiScore(int score=0); // Checks if score is higher than current hiScore
        
        // Writing a user profile to files
        void wrtTxt(int);
        void wrtBin();
        
        // Reading binary. !!!Make Private if Admin is base class!!!
        void find1Record(int);
      
        // Accessors
        void readInputFile();         
        int getHiScore()  const { return hiScore;}
        string getName()  const { return name;}
        string getEmail() const { return email;}
        string getPwrd()  const { return password;}    
        unsigned short getNamSiz() const { return namSiz;}
        unsigned short getEmaiSiz() const { return emaiSiz;}
        unsigned short getPwrdSiz() const { return pwrdSiz;}            
        void print1User() const; 
};

#endif /* USER_H */


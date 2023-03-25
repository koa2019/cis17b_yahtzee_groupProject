/* File:   Admin.h
 * Author: DanYell
 *
 * Created on March 23, 2023, 2:50 AM
 */

#ifndef ADMIN_H
#define ADMIN_H
#include <string>
using namespace std;  //STD Name-space where Library is compiled

class Admin {
    private:
        unsigned short namSiz = 0;
        string name = "";    
        unsigned short emaiSiz = 0;
        string email = "";    
        unsigned short pwrdSiz = 0;
        string password = ""; 
        //int hiScore = 0;
        
        // Private Mutators
        void setNamSiz(int size) { namSiz = size;}
        void setEmaiSiz(int size){ emaiSiz = size;}
        void setPwrdSiz(int size){ pwrdSiz = size;}
        //void setHiScore(int s){ hiScore = s;}       
        string setToLower(string);
        
        
    public:
       
        Admin();     // Default constructor
        ~Admin();    // Destructor
        
        // Admin login info
        void adminLogin();
        void updateAdminProfile();
        void wrtAdminTxt();
        void wrtAdminBin();
        void getAdminBin();
        
        
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
        int checkHiScore(int score=0); // Checks if score is higher than current hiScore
        void wrtTxt(int);
        void wrtBin();
        void get1Record(int);
        
        
        
        // Accessors   
        unsigned short getNamSiz() const { return namSiz;}
        unsigned short getEmaiSiz() const { return emaiSiz;}
        unsigned short getPwrdSiz() const { return pwrdSiz;}
        string getName() const  { return name;}
        string getEmail() const { return email;}
        string getPwrd() const  { return password;}
        //int getNRecord() const { return nRecord;}
        //int getHiScore() const  { return hiScore;}
        void print1Admin (bool,bool,bool) const; 
        void print1Admin () const;
};

#endif /* ADMIN_H */


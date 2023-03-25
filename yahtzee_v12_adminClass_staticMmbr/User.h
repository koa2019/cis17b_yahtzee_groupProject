/* File:   User.h
 * Author: Danielle F
 * Created:March 22, 2023, 10:42 PM
*/

#ifndef USER_H
#define USER_H
#include "Admin.h" // User inherits Admin class

using namespace std;  //STD Name-space where Library is compiled

class User : public Admin {
    
    private:
    int numWins;
    
    public:
    
        // Default constructor
        User(){
            readInputFile();
            numWins=0;
            cout<<"\nHit User constructor.\n";
        } 
//    User(string n, string e, string p){
//        setName(n);
//        setNamSiz(n.size());
//        setEmail(e);
//        setEmaiSiz(e.size());
//        setPwrd(p);
//        setPwrdSiz(p.size());
//    }
        
        // Destructor
        ~User(); 
        
        // Mutators
        void setNumWins(int n){numWins=n;}
        
        // Accessors
        int getNumWins() const {return numWins;}
        void print1User() const;
};
#endif /* USER_H */


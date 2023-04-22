/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-10-2023 @ 12:36 PM
 * Purpose:  yahtzee group project-userLogin v1
 * 
 * v1: Reads inputs from user and confirms them in main().
 *     If all inputs are valid, then it prints inputs.
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include <cstdlib> // rand()
#include <ctime> // time()
#include <string> //string var
using namespace std;  //STD Name-space where Library is compiled

//User Libraries

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Function Prototypes

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    //rand()%90+10;//2 digit numbers
    
    //Declare variables here
    string name="",
           email="",
           password="",
           tempPwd="";
    
    // Initialize variables here
    cout<<"Enter your name: ";
    cin>>name;
    cout<<"Enter your email: ";
    cin>>email;
    
    // Compare password and temp password are the same
    bool isPswd = true, 
         isLeng=true;
    int pwrdLen = 4;
    
    do{
        
        if( tempPwd.compare(password) != 0) { cout<<"Passwords must match!\n"; }
        
        // confirm password is correct length 
        do{
            cout<<"Enter your "<<pwrdLen<<" character password:    ";
            cin>>password;
            
            if(password.length() != pwrdLen){ cout<<"\nPassword must be"<<pwrdLen<<" characters long\n";}
            
        } while(password.length() !=pwrdLen);
        
        // confirm password is correct length 
        do {
            cout<<"Re-enter your "<<pwrdLen<<" character password: ";
            cin>>tempPwd;
            
            if(tempPwd.length() !=pwrdLen){ cout<<"\nPassword must be"<<pwrdLen<<" characters long\n";} 
            
        } while(tempPwd.length() !=pwrdLen);
        
        // set flag for password length
        if( (password.length() !=pwrdLen) && (tempPwd.length() !=pwrdLen)){ isLeng=false; }
        else { isLeng=true; }
        
        // set flag for password being the same as temp password
        if(password.compare(tempPwd) !=0){ isPswd=false; }
        else { isPswd=true; }
                
        
    } while( isPswd==false || isLeng==false );
    
    
    
    //Display the results
    if(isPswd==true && isLeng==true){
        cout<<endl
            <<"Name: " << name << endl
            <<"Email: " << email << endl
            <<"Password: " << password << endl;
    }
    return 0;
}

/**********  Function definitions  **************/
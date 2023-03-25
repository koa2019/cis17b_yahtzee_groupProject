/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-10-2023 @ 12:36 PM
 * Purpose:  yahtzee group project-userLogin v4
 * 
 * v1: Reads inputs from user and confirms them in main().
 *     If all inputs are valid, then it prints inputs.
 * 
 * v2: Creates one name string, one email string, one password string.
 *     Adds functions that confirm each input meets certain criteria.
 *     Prints one name, one email, one password    
 * 
 * v3: Writes & appends to text and binary file:
 *     size of name string, one name string,
 *     size of email string, one email string,
 *     size of password string, one password string.
 * 
 *     Reads first three strings in from binary file.
 * 
 * v4: Reads in third record in from binary file
 *     by accumulating the size of each string.  
 *     Stops at the beginning of record 3
 * 
 * To do:
 *       change password minSize to 7
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include <cstdlib> // rand()
#include <ctime> // time()
#include <string> //string var
#include <fstream>
using namespace std;  //STD Name-space where Library is compiled

//User Libraries
struct User {
    
};
//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

// Function Prototypes
string setName();
string setEmail();
string setPwrd();
bool isMinSize(string , int);
bool isStrEqual(string, string);
bool hasSpecialChars(string);
bool confrmEmail(string);
void print1User(string, string, string);        


//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here
    //srand(static_cast<unsigned int>(time(0)));
    //rand()%90+10;//2 digit numbers
    
    //Declare variables here
    //unsigned short emaiSiz = 0;
    string name="";
    
    //unsigned short emaiSiz = 0;
    string email="";
    
    //unsigned short pwrdSiz = 0;
    string password=""; 
    
    // Create 1 profile
    name     = setName();
    email    = setEmail();
    password = setPwrd();
     
    
//    // Print 1 profile
//    print1User(name,email,password);
    
 /********* START WRITING TO TEXT AND BINARY FILES  ********/
    
    cout<<endl<<endl;
    
    ofstream outTxt, outBin;
    outTxt.open("data.txt",ios::out | ios::app); // appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening outTxt.txt\n";}
    
    outBin.open("data.dat",ios::out | ios::app | ios::binary); // appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening outBin.dat\n";}
    
    unsigned short sizeN = 0, sizeE = 0, sizeP = 0;
    sizeN = name.size();     // get size of this string
    sizeE = email.size();    // get size of this string
    sizeP = password.size(); // get size of this string
     
    
    /**************   WRITE 1 RECORD TO TEXT FILE  ***************/
    
    outTxt<<sizeN<<endl; // write the size of this string to text file
    outTxt<<name<<endl;  // write this string to text file
    outTxt<<sizeE<<endl; // write the size of this string to text file
    outTxt<<email<<endl;  // write this string to text file
    outTxt<<sizeP<<endl; // write the size of this string to text file
    outTxt<<password<<endl<<endl;   // write this string to text file
    
    
    /**************   WRITE 1 RECORD TO BINARY FILE  ***************/    
    
    outBin.write(reinterpret_cast<char *>(&sizeN), sizeof(sizeN) ); // write the size of this string to binary file
    outBin.write(name.c_str(), name.size()); // write this actual string to binary file
    
   
    outBin.write(reinterpret_cast<char *>(&sizeE), sizeof(sizeE) ); // write the size of this string to binary file
    outBin.write(email.c_str(), email.size()); // write this actual string to binary file
    
   
    outBin.write(reinterpret_cast<char *>(&sizeP), sizeof(sizeP) ); // write the size of this string to binary file
    outBin.write(password.c_str(), password.size()); // write this actual string to binary file
    
    // close files
    outTxt.close();
    outBin.close();
    
    
    
    /*********   READ BINARY FILE    ********/
        
    ifstream inTxt, inBin;
    inTxt.open("data.txt",ios::in); // appends content to the current content of the file.
    if(!inTxt.is_open()){ cout<<"\nError opening inTxt.txt\n";}
    
    inBin.open("data.dat",ios::in | ios::binary); // appends content to the current content of the file.
    if(!inBin.is_open()){ cout<<"\nError opening inBin.dat\n";}
    
    int randRec = 2;
    long cursor = 0L;
    int count=1;    // start at 1, so it stops before the randRec
    unsigned short sz = 0;
    string nme = "";
    string emai = "";
    string pwd = "";
      
    cout<<endl<<endl<<"Looking for record "<<randRec<<" in binary file.\n\n";
    
    while(count<=randRec){
        
        // set cursor to beginning of file       
        inBin.seekg(cursor,ios::beg);
        
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file       
        nme.resize(sz);
        inBin.read(&nme[0], nme.size()); // read this actual string to binary file    
        //cout<<"sizeof(sz) = "<<sizeof(sz)<<"\nnme.size() = " << nme.size()<<endl;    
        //cout<<"nme = "<<nme<<endl;
        cursor += (sizeof(sz) + nme.size());
        

        sz = 0;
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file       
        emai.resize(sz);
        inBin.read(&emai[0], emai.size()); // read this actual string to binary file    
        //cout<<"sizeof(sz) = "<<sizeof(sz)<<"\nemai.size() = " << emai.size()<<endl;    
        //cout<<"emai = "<<emai<<endl;
        cursor += (sizeof(sz) + emai.size());
        
        sz = 0;
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file      
        pwd.resize(sz);
        inBin.read(&pwd[0], pwd.size()); // read this actual string to binary file    
        //cout<<"sizeof(sz) = "<<sizeof(sz)<<"\npwd.size() = " << pwd.size()<<endl;    
        //cout<<"pwd = "<<pwd<<endl;
        cursor += (sizeof(sz) + pwd.size());        
        //cout<<"\tcursor = "<<cursor<<endl;
        
        count++;
    }
    cout<<endl<<endl;
    
    
    
    cout<<"cursor = "<<cursor<<" which means at the last bit before the record we're looking for\n";
    
    // sets cursor at the beginning of the file we're looking for
    inBin.seekg(cursor,ios::beg);
    
    cout<<"Found record " << randRec <<endl;
    
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // write the size of this string to binary file
    nme = "";
    nme.resize(sz);  
    inBin.read(&nme[0], nme.size()); // write this actual string to binary file    
    //cout<<"sizeof(sz) = "<<sizeof(sz)<<"\nnme.size() = " << nme.size()<<endl;    
    cout<<"nme = "<<nme<<endl;
    
    sz = 0;
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // write the size of this string to binary file
    emai = "";
    emai.resize(sz);    
    inBin.read(&emai[0], emai.size()); // write this actual string to binary file    
    //cout<<"sizeof(sz) = "<<sizeof(sz)<<"\nemai.size() = " << emai.size()<<endl;    
    cout<<"emai = "<<emai<<endl;
    
    sz = 0;
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // write the size of this string to binary file
    pwd = "";
    pwd.resize(sz);   
    inBin.read(&pwd[0], pwd.size()); // write this actual string to binary file    
    //cout<<"sizeof(sz) = "<<sizeof(sz)<<"\npwd.size() = " << pwd.size()<<endl;    
    cout<<"pwd = "<<pwd<<endl;
    
    
    inTxt.close();
    inBin.close();
    
    
    return 0;
}

/**********  Function definitions  **************/
void print1User(string name, string email, string password){
    cout<<endl
        <<"Profile successfully created.\n"
        <<"Name: " << name << endl
        <<"Email: " << email << endl
        <<"Password: ";
    for(int i=0;i<password.length();i++){
        cout<< '*';
    }
    cout<<endl;
}

// SET NAME
string setName(){
    
    bool isLeng=true;
    string name="";
    
    // Loop until a valid name is entered
    do {
        cout<<"\nEnter your name. Must be at least 2 characters: ";
        getline(cin,name);
        
        // Set flag. Confirm name is at least 2 characters long
        isLeng = isMinSize(name,2);
       
    } while(!isLeng);
    
    return name;
}

//  SET EMAIL
string setEmail(){
    string email="";
    // Loop until a valid email is entered
    bool isEmail = true, isLeng=true;
    unsigned short minSize=9;
    
    do {
        cout<<"\nEnter your email: ";
        cin>>email;
        
        // Set flags. Confirm emails length and that it contains '@' and '.'
        isEmail = confrmEmail(email);
        isLeng = isMinSize(email, minSize);
        
    } while( !isEmail || !isLeng );
    return email;
}


//  SET PASSWORD
string setPwrd(){
    
    bool isPwd=true,  
         isLeng=true,
         hasSpCh=true;
    unsigned short minSize = 4;    
    string pwd="",
           tempPwd="";
    
    
    //  Loop until password and temp password are exactly the same
    //  and it is at least the minimum length
    do{
       
        // Loop until password is correct length 
        do{
            cout<<"\nPassword must be at least "
                <<minSize<<" characters long, and "  
                <<"\ninclude: 1 uppercase letter, 1 digit, "
                <<"and 1 special character (! $ #)."
                <<"\nEnter your password:   ";       
            cin>>pwd;
            
            // Set flag. Confirm string length is a minimum length
            isPwd = isMinSize(pwd,minSize);            
            
            // Confirm password has digit, uppercase and $,!, or # in it
            hasSpCh = hasSpecialChars(pwd);            
            
        } while(!isPwd && !hasSpCh);
        
        
        // Loop until temp password is correct length 
        do {
            cout<<"\nConfirm your password: ";
            cin>>tempPwd;
            
            // Set flag. Confirm string length is a minimum length
            isPwd = isMinSize(tempPwd,minSize); 
            
           // Confirm tempPwd has digit, uppercase and $,!, or # in it
           hasSpCh = hasSpecialChars(tempPwd);             
            
        } while(!isPwd && !hasSpCh);        
                
        //  Confirm password is the exactly the same as temp password 
       isPwd = isStrEqual(pwd,tempPwd);
       
         
    } while( !isPwd );
    
    return pwd;
}


/*********  Confirms strings is @least minimum length  ***********/
bool isMinSize(string str, int minLeng){
    
    if(str.length() < minLeng || str.length() > 70){ 
        cout<<"\nError. Minimum length is: "<<minLeng<<endl;
        return false; 
    }
    return true;            
}


/*********  Confirms strings have the same exact characters  ***********/
bool isStrEqual(string password, string tempPwd){
    
    // confirm strings have the same exact characters
    if( password.compare(tempPwd) !=0 ){ 
        cout<<endl<<"Passwords must match!\n";
        return false; 
    }
    return true;   
}


/*********  Confirms password includes at least 1 digit, uppercase & special char  ***********/
bool hasSpecialChars(string password){
     
    bool isValid1=true,
         isValid2=true,
         isValid3=true;
    
    // Check if password has at least 1 digit
    for(int i=0;i<password.length();i++){        
       
        if( isdigit(password[i]) !=0 ){    
            isValid1 = true;
            break;
        } else { isValid1 = false; }
    }  
    
    // Check if password has at least 1 uppercase letter
    for(int i=0;i<password.length();i++){
        if( isupper(password[i]) !=0 ){
            isValid2 = true;
            break;
        } else { isValid2 = false; }  
    }
    
    
    // Check if password has at least 1 special character
    for(int i=0;i<password.length();i++){
        if( password[i]=='!' || password[i]=='$' || password[i]=='#'){
            isValid3 = true;
            break;            
        } else { isValid3 = false; }  
    }
    
    // Return a true/false that says if password meets all the criteria or not
    if( !(isValid1 && isValid2 && isValid3) ){
        cout<<"\nInvalid Password.\n";
        return false;
    } 
    
    return true; 
}


/********    Confirm email string has a '@' AND '.' in it   **************/
bool confrmEmail(string email){
    
    // Find these characters in string
    short indxAt =  email.find("@");
    short indxDot = email.find(".");
    //cout<<"indxAt "<< indxAt <<endl<<"indxDot "<< indxDot <<endl;


    // Confirm email has a  '@' AND dot in it. Check if position is -1 or not
    if(indxAt == string::npos || indxDot == string::npos){ // npos=-1 indicates that no matches were found in the string.
        cout<<"\nInvalid email.";
        return false;
    } 
    return true;
}

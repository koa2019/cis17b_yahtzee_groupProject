
//System Libraries
#include <iostream>   //Input/Output Library
#include <cstdlib>   // rand()
#include <ctime>    // time()
#include <string>   //string variable
#include <cstring>  // c-strings
#include <cctype>  // helper functions for c-strings
#include <fstream> // input/output for files
using namespace std;  //STD Name-space where Library is compiled
#include "User.h"

//   Default Constructor
User::User(){
    namSiz = 0;
    name = "";
    emaiSiz = 0;
    email = "";
    pwrdSiz = 0;
    password = ""; 
    hiScore = 0;
}

//   Destructor
User::~User(){
    //cout<<"\nHit Destructor(). Static class, so nothing to destroy.\n";
}
       
// Converts any uppercase characters to lowercase letters
string User::setToLower(string n){       
    string str="";
    for(int i=0;i<n.size();i++){
        str += tolower(n[i]);
    }
    return str;
}


// Accepts score from game and checks if it is higher than the current hiScore
bool User::checkHiScore(int score){
    if(score > hiScore) { 
        setHiScore(score); // Call private member function to reset hiScore
        return true;
    } 
    return false;
}


// After a user submits their info, it prints a message whether their profile
// was created or not.
void User::print1User(bool isName, bool isEmail, bool isPwrd) const {
    
    if( isName && isEmail && isPwrd){
        cout<<"\nProfile successfully created.\n"
            <<"Name: " << getName() << endl
            <<"Email: " << getEmail() << endl
            <<"Password: ";
        for(int i=0;i<(getPwrd().length()) ;i++){ // prints stars instead of actual password
            cout<< '*';
        }
        cout<<"\nHigh Score: "<<getHiScore()<<endl<<endl;
        
    }
    else { cout<<"\nOops! Profile not created.\n"; }
}

// SET NAME. Loops until a name's length is within the range
bool User::setName(){
    
    bool isLeng=true;
    string n="";
    
    // Loop until a valid name is entered
    do {
        cout<<"\nEnter your name. Must be at least 2 characters: ";
        getline(cin,n);
        
        // Set flag. Confirm name is at least 2 characters long
        isLeng = isMinSize(n,2);
       
    } while(!isLeng);
    
    if(isLeng){
        //name = setToLower(n);     // set variable in class    
        setName(setToLower(n));     // changes to lowercase & set variable in class    
        setNamSiz(n.size());  // set this string's length in the class
        return true;
    
    } else { return false; }
}

//  SET EMAIL. Loops until a email's length is within the range
//             and contains '@' and '.' 
bool User::setEmail(){
    
    bool isEmail = true, 
          isLeng = true;
    unsigned short minSize = 9;
    string em = "";
    
    // Loop until a valid email is entered
    do {
        cout<<"\nEnter your email: ";
        cin>>em;
        
        // Set flags. Confirm emails length and that it contains '@' and '.'
        isEmail = confrmEmail(em);
        isLeng = isMinSize(em, minSize);
        
    } while( !isEmail || !isLeng );
    
    if(isEmail && isLeng){
        //email = setToLower(em);   // set variable in class
        setEmail(setToLower(em));   // set variable in class
        setEmaiSiz(em.size()); // set this string's length in the class
        return true;
        
    } else { return false; }
}


//  SET PASSWORD.  Loops until a password's length is within the range
//             and contains at least 1 digit, 1 uppercase and 1 special char
bool User::setPwrd(){
    
    bool isPwd   = true,  // password meets all of its criteria 
         isLeng  = true, // string is minimum length
         hasSpCh = true; // string contains one of these special chars
    unsigned short minSize = 7;    
    string pwd="",
           tempPwd="";
    
    
    //  Loop until password AND temp password are exactly the same
    //  and it is at least the minimum length
    do{
       
        // Loop until password is correct length 
        do{
            cout<<"\nPassword must be at least "
                <<minSize<<" characters long, and "  
                <<"\ninclude: 1 uppercase letter, 1 digit, "
                <<"and 1 special character (! $ #). "
                <<"\nEnter your password:   ";       
            cin>>pwd;
            
            // Set flag. Confirm string length is a minimum length
            isPwd = isMinSize(pwd,minSize);            
           
            // Confirm string has digit, uppercase and $,!, or # in it
            hasSpCh = hasSpecialChars(pwd);            
            
        } while(!isPwd || !hasSpCh);
        
        
        // Loop until temp password is correct length 
        do {
            cout<<"\nConfirm your password: ";
            cin>>tempPwd;
            
            // Set flag. Confirm string length is a minimum length
            isPwd = isMinSize(tempPwd,minSize); 
           
           // Confirm tempPwd has digit, uppercase and $,!, or # in it
           hasSpCh = hasSpecialChars(tempPwd);             
            
        } while(!isPwd || !hasSpCh);        
                
        //  Confirm password is the exactly the same as temp password 
       isPwd = isStrEqual(pwd,tempPwd);       
         
    } while( !isPwd );
    
    if(isPwd){
        //password = pwd; // set variable in class    
        setPwrd(pwd); // set variable in class
        setPwrdSiz(pwd.size());  // set this string's length in the class
        return true;
        
    } else { return false; }
}


/*********  Confirms strings length is within a range  ***********/
bool User::isMinSize(string str, int minLeng){
    
    if(str.size() < minLeng || str.size() > 70){ 
        cout<<"\nError. Minimum length is: "<<minLeng<<endl;
        if(str.length()>70){ cout<<"\nError. Input is too long.\n"; }
        return false; 
    }
    return true;            
}


/*********  Confirms strings have the same exact characters  ***********/
bool User::isStrEqual(string password, string tempPwd){
    
    // confirm strings have the same exact characters
    if( password.compare(tempPwd) !=0 ){ 
        cout<<endl<<"Passwords must match!\n";
        return false; 
    }
    return true;   
}


/*********  Confirms password includes at least 1 digit, uppercase & special char  ***********/
bool User::hasSpecialChars(string password){
     
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
bool User::confrmEmail(string email){
    
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


 /**************   WRITE 1 RECORD TO TEXT FILE  ***************/
void User::wrtTxt(int recNum){
    
    ofstream outTxt;
    outTxt.open("data.txt",ios::out | ios::app); // appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening outTxt.txt\n";}
    
        
    unsigned short sizeN = 0, sizeE = 0, sizeP = 0;
    sizeN = getNamSiz();     // get size of this string
    sizeE = getEmaiSiz();    // get size of this string
    sizeP = getPwrdSiz(); // get size of this string
    int hScore = getHiScore(); // get value of hiScore from class
    //cout<<"\nsizeN= "<<sizeN<<"\nsize= "<<sizeE<<"\nsizeP= "<<sizeP<<endl; 
    
       
    outTxt<<"Record "  <<recNum<<endl;
    outTxt<<"namSiz:  "<<sizeN<<endl; // write the size of this string to text file
    outTxt<<"name:    "<<getName()<<endl;  // write this string to text file
    outTxt<<"emaiSiz: "<<sizeE<<endl; // write the size of this string to text file
    outTxt<<"email:   "<<getEmail()<<endl;  // write this string to text file
    outTxt<<"pwrdSiz: "<<sizeP<<endl; // write the size of this string to text file
    outTxt<<"pwrd:    "<<getPwrd()<<endl;   // write this string to text file
    outTxt<<"hiScore: "<<hScore<<endl<<endl;
  
    outTxt.close(); // close file
}


/**************   WRITE 1 RECORD TO BINARY FILE  ***************/    
void User::wrtBin(){
        
    ofstream outBin; 
    outBin.open("data.dat",ios::out | ios::app | ios::binary); // appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening outBin.dat\n";}
    
    unsigned short sizeN = 0, sizeE = 0, sizeP = 0;
    sizeN = getNamSiz();     // get size of this string
    sizeE = getEmaiSiz();    // get size of this string
    sizeP = getPwrdSiz(); // get size of this string
    int hScore = getHiScore(); // get value of hiScore from class
    //cout<<"\nsizeN= "<<sizeN<<"\nsize= "<<sizeE<<"\nsizeP= "<<sizeP<<endl; 
    
    // Write the size of this string to binary file
    // and then write this actual string to binary file
    outBin.write(reinterpret_cast<char *>(&sizeN), sizeof(sizeN)); 
    outBin.write((getName().c_str()), sizeN); 
    
    // Write the size of this string to binary file
    // and then write this actual string to binary file
    outBin.write(reinterpret_cast<char *>(&sizeE), sizeof(sizeE));     
    outBin.write((getEmail().c_str()), sizeE); 
    
    
    // Write the size of this string to binary file
    // and then write this actual string to binary file
    outBin.write(reinterpret_cast<char *>(&sizeP), sizeof(sizeP) ); 
    outBin.write((getPwrd().c_str()), sizeP); 
    
    // Write hiScore to binary file
    outBin.write(reinterpret_cast<char *>(&hScore) , sizeof(int) ); 
      
    outBin.close(); // close file    
}


/*********   READ BINARY FILE & RETURN 1 RECORD   ********/
//User User::*get1Record(int record){
void User::get1Record(int recIndx){ 
      
    recIndx = recIndx < 0 ? 0 : recIndx;
    
    ifstream inBin;
    inBin.open("data.dat",ios::in | ios::binary); // appends content to the current content of the file.
    if(!inBin.is_open()){ cout<<"\nError opening inBin.dat\n";}
    
    long cursor = 0L;
    int count = 1;       // start at 1, so it stops before the record I'm looking for
    unsigned short sz = 0;
    int hScore = 0;        
      
    cout<<endl<<endl<<"Looking for record "<<recIndx<<" in binary file.\n\n";
    
    while(count<=recIndx){
                    
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file       
        cursor += ( sizeof(sz) + sz*sizeof(char) );
        //cout<<"     sizeof(sz) = "<<sizeof(sz)<<"\nsz*sizeof(char) = " << sz*sizeof(char)<<endl; 
        //cout<<"this record sum = "<< (sizeof(sz) + sz*sizeof(char)) <<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        // Read the value of emaiSiz and then use it calculate the number of bits
        // that emaiSiz and email take up in memory. 
        // Add it to cursor and move on to the next variables
        sz = 0;
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file              
        cursor += ( sizeof(sz) + sz*sizeof(char) );
        //cout<<"     sizeof(sz) = "<<sizeof(sz)<<"\nsz*sizeof(char) = " << sz*sizeof(char)<<endl;          
        //cout<<"this record sum = "<< (sizeof(sz) + sz*sizeof(char)) <<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        // Read the value of pwrdSiz and then use it calculate the number of bits
        // that pwrdSiz and password take up in memory. 
        // Add it to cursor and move on to the next variables
        sz = 0;
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file      
        cursor += ( sizeof(sz) + sz*sizeof(char) );        
        //cout<<"     sizeof(sz) = "<<sizeof(sz)<<"\nsz*sizeof(char) = " << sz*sizeof(char)<<endl;    
        //cout<<"this record sum = "<< ( sizeof(sz) + sz*sizeof(char) ) <<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        inBin.read(reinterpret_cast<char *>(&hScore) , sizeof(int) ); // write the size of this string to binary file
        cursor += sizeof(hScore);  // size of int hiScore  
        //cout<<sizeof(hScore)<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        count++;
    }
    //cout<<"\n\ncursor = "<<cursor<<" which means it's at the last bit before the record we're looking for.\n\n";
    
    /******  Save 1 record to a single instance of User class  *******/
    cout<<"Found record "<<recIndx<<endl;
    string nme  = "";
    string emai = "";
    string pwd  = ""; 
    
    User oUser;
    
    // sets cursor at the beginning of the file we're looking for
    inBin.seekg(cursor,ios::beg);
    
    // Read & save the length of name and the name string
    sz = 0;
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // write the size of this string to binary file
    setNamSiz(sz);     // set size of name string
    oUser.setNamSiz(sz);     // set size of name string
    
    nme = "";
    nme.resize(sz); 
    inBin.read(&nme[0], nme.size()); // write this actual string to binary file    
    setName(nme);
    oUser.setName(nme);
     
    // Read & save the length of email and the email string
    sz = 0;
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // write the size of this string to binary file
    setEmaiSiz(sz);    // set size of email string
    oUser.setEmaiSiz(sz);    // set size of email string
     
    emai = "";
    emai.resize(sz);    
    inBin.read(&emai[0], emai.size()); // write this actual string to binary file    
    setEmail(emai);
    oUser.setEmail(emai);
    
    
    // Read & save the length of password and the password string
    sz = 0;
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // write the size of this string to binary file
    setPwrdSiz(sz); // set size of password string
    oUser.setPwrdSiz(sz); // set size of password string
    
    
    pwd = "";
    pwd.resize(sz);   
    inBin.read(&pwd[0], pwd.size()); // write this actual string to binary file    
    setPwrd(pwd);
    oUser.setPwrd(pwd);
    
    // Read & save hiScore
    hScore=0;
    inBin.read(reinterpret_cast<char *>(&hScore) , sizeof(int) ); // write the size of this string to binary file
    setHiScore(hScore);
    oUser.setHiScore(hScore);
     
    //cout<<"\ninside wrtBinary() "; 
    //print1User(true,true,true);
    
    cout<<"\noUser inside wrtBinary() ";
    oUser.print1User(true,true,true);
    cout<<"nme = "<<nme<<endl;
    cout<<"emai = "<<emai<<endl;
    cout<<"pwd = "<<pwd<<endl;
    cout<<"hiScore = "<<hScore<<endl;
    
    
    inBin.close(); // close file
    
    //return oneUser;
}
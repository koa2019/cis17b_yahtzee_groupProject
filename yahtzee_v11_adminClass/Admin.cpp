
//System Libraries
#include <iostream>   //Input/Output Library
#include <cstdlib>   // rand()
#include <ctime>    // time()
#include <string>   //string variable
#include <cstring>  // c-strings
#include <cctype>  // helper functions for c-strings
#include <fstream> // input/output for files
using namespace std;  //STD Name-space where Library is compiled
#include "Admin.h"

//   Default Constructor
Admin::Admin(){
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    id = rand()%((0+16)+3);
    namSiz=0;
    name="";
    emaiSiz=0;
    email="";
    pwrdSiz=0;
    password=""; 
    hiScore=0;    
}

//   Constructor #2
Admin::Admin(int idNum){
    id = idNum;
    namSiz=0;
    name="";
    emaiSiz=0;
    email="";
    pwrdSiz=0;
    password=""; 
    hiScore=0;    
}


//   Destructor
Admin::~Admin(){
    //cout<<"\nHit Destructor(). Static class, so nothing to destroy.\n";
}
     


/*******************************************************************/
/*****    HELPER FUNCTIONS FOR CREATING NEW CLASS OBJECT     ******/
/*****************************************************************/

void Admin::login(){
    
    // Need to add function that searches binary for an email
    string em = "blank", pwrd = "blank";
    string tempEmail="";
    string tempPwrd="";
    bool isName=false,
         isPwrd=false;
    
    cout<<"\n\tUser Login\n"
        <<"Enter email: ";
    cin>>tempEmail;
    cout<<"Enter password: ";
    cin>>tempPwrd;
    
    isName = isStrEqual(em,tempEmail);
    isPwrd = isStrEqual(pwrd,tempPwrd);
    
    if(!isName || !isPwrd){ 
        cout<<"Username and/or password does not match.\n";
        tempEmail=tempPwrd="";        
        isName=isPwrd=false;        
        exit(0);//refresh page with javascript
    }
}
    
    
void Admin::signUp(){
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
    int num;  
    
    const int MAXACCTS=4; // Don't want a site to crash if someone created a bunch of profiles @once
    bool isAgain=true,
         isNameGood=false,
         isEmailGood=false,
         isPwrdGood=false;
    char ans='n';
    int usrCount=0;  // counts number of profiles created in a single session
      
    num = 10*(rand()%(0+16)+3) * (rand()%(0+9)+1);
    
    // Loop until user is finished creating profiles
    while(isAgain){
        
        // Create 1 profile with default constructor         
        isNameGood  = isName();
        isEmailGood = isEmail();
        isPwrdGood  = isPwrd();
        
//        num = 10*(rand()%(0+16)+3) * (rand()%(0+9)+1);
        setID(num);
        
        // If user's input was valid, then write it files
        if(isNameGood && isEmailGood && isPwrdGood){        

            wrtTxt(usrCount);  // Write to text file
            wrtBin();       // Write to binary file 

            cout<<"\nProfile successfully created.\n";
            print1Profile();  // Print 1 profile

        } else { cout<<"\nOops! Profile not created.\n"; }
    
        // Conditional only allows a max number of profiles to be created
        cout<<"\nNumber of Accounts Created: "<<usrCount+1;
        
        if(usrCount+1 >= MAXACCTS) {
            
            cout<<"\nYou've reached maximum number of players you can create in 1 session.\n";
            isAgain=false;
            
        } else {
            
            cout<<"\nWould you like to create another user profile?\nY for yes or N for no.\n";
            cin>>ans;
            cin.ignore();
            
            // Checks if user wants to create another profile
            if(ans == 'y' || ans == 'Y'){                
                isAgain=true; 
                usrCount++;                            
            }                   
            else { isAgain=false; } 
        }
    } // Ends while loop
}


/******  Loops until a name's length is within the range   *******/
bool Admin::isName(){
    
    bool isLeng = true;
    const int MIN = 2;
    string n = "";
    
    // Loop until a valid name is entered
    do {
        cout<<"\nEnter your name. Must be at least 2 characters: ";
        getline(cin,n);
        
        // Set flag. Confirm name is at least 2 characters long
        isLeng = isMinSize(n,MIN);
       
    } while(!isLeng);
    
    if(isLeng){
        // Reset class member variables
        name = toLowerCase(n); // changes to lowercase & set variable in class    
        namSiz = name.size(); 
        return true;
    }    
    
    return false;
}


/*      Loops until a email's length is within the range & 
        contains '@' and '.'                               ************/
bool Admin::isEmail(){
    
    bool isEmail = true, 
          isLeng = true;
    unsigned short MINSIZE = 9;
    string em = "";
    
    // Loop until a valid email is entered
    do {
        cout<<"\nEnter your email: ";
        cin>>em;
        
        // Set flags. Confirm emails length and that it contains '@' and '.'
        isEmail = confrmEmail(em);
        isLeng = isMinSize(em, MINSIZE);
        
    } while( !isEmail || !isLeng );
    
    if(isEmail && isLeng){        
        // Reset class member variables
        email = toLowerCase(em);  
        emaiSiz = email.size(); 
        return true;
    }   
    
    return false;
}


/*      Loops until a password's length is within the range &
        contains at least 1 digit, 1 uppercase and 1 special char   */
bool Admin::isPwrd(){
    
    bool isPwd   = true,  // password meets all of its criteria 
         isLeng  = true, // string is minimum length
         hasSpCh = true; // string contains one of these special chars
    unsigned short MINSIZE = 7;    
    string pwd = "",
           tempPwd = "";
    
    
    //  Loop until password AND temp password are exactly the same
    //  and it is at least the minimum length
    do{
       
        // Loop until password is correct length 
        do{
            cout<<"\nPassword must be at least "
                <<MINSIZE<<" characters long, and "  
                <<"\ninclude: 1 uppercase letter, 1 digit, "
                <<"and 1 special character (! $ #). "
                <<"\nEnter your password:   ";       
            cin>>pwd;
            
            // Set flag. Confirm string length is a minimum length
            isPwd = isMinSize(pwd,MINSIZE);            
           
            // Confirm string has digit, uppercase and $,!, or # in it
            hasSpCh = hasSpecialChars(pwd);            
            
        } while(!isPwd || !hasSpCh);
        
        
        // Loop until temp password is correct length 
        do {
            cout<<"\nConfirm your password: ";
            cin>>tempPwd;
            
            // Set flag. Confirm string length is a minimum length
            isPwd = isMinSize(tempPwd,MINSIZE); 
           
           // Confirm tempPwd has digit, uppercase and $,!, or # in it
           hasSpCh = hasSpecialChars(tempPwd);             
            
        } while(!isPwd || !hasSpCh);        
                
        //  Confirm password is the exactly the same as temp password 
       isPwd = isStrEqual(pwd,tempPwd);       
         
    } while( !isPwd );
    
    if(isPwd){
        password = pwd; // set variable in class   
        pwrdSiz = password.size();  // set this string's length in the class
        return true;
        
    } else { return false; }
}


/*********  Confirms strings length is within a range  ***********/
bool Admin::isMinSize(string str, int minLeng){
    
    if(str.size() < minLeng || str.size() > 70){ 
        cout<<"\nError. Minimum length is: "<<minLeng<<endl;
        if(str.length()>70){ cout<<"\nError. Input is too long.\n"; }
        return false; 
    }
    return true;            
}


/*********  Confirms strings have the same exact characters  ***********/
bool Admin::isStrEqual(string password, string tempPwd){
    
    // confirm strings have the same exact characters
    if( password.compare(tempPwd) !=0 ){ 
        cout<<endl<<"Passwords must match!\n";
        return false; 
    }
    return true;   
}


/*********  Confirms password includes at least 1 digit, uppercase & special char  ***********/
bool Admin::hasSpecialChars(string password){
     
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
bool Admin::confrmEmail(string email){
    
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


// Accepts score from game and checks if it is higher than the current hiScore
bool Admin::checkHiScore(int score){
    if(score > hiScore) { 
        setHiScore(score); // Call private member function to reset hiScore
        return true;
    } 
    return false;
}


// Converts any uppercase characters to lowercase letters
string Admin::toLowerCase(string n){       
    string str="";
    for(int i=0;i<n.size();i++){
        str += tolower(n[i]);
    }
    return str;
}


/******************************************************************/
/***************    WRITE TO TEXT & BINARY FILE     ***************/
/*****************************************************************/


 /**************   WRITE 1 RECORD TO TEXT FILE  ***************/
void Admin::wrtTxt(int recNum){
    
    ofstream outTxt;
    outTxt.open("data.txt",ios::out | ios::app); // appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening outTxt.txt\n";}      
       
    outTxt<<"Record "  <<recNum<<endl;
    outTxt<<"ID:      "<<id<<endl; // write id to text file
    outTxt<<"namSiz:  "<<namSiz<<endl; // write the size of this string to text file
    outTxt<<"name:    "<<name<<endl;   // write this string to text file
    outTxt<<"emaiSiz: "<<emaiSiz<<endl;// write the size of this string to text file
    outTxt<<"email:   "<<email<<endl;  // write this string to text file
    outTxt<<"pwrdSiz: "<<pwrdSiz<<endl; // write the size of this string to text file
    outTxt<<"pwrd:    "<<password<<endl;// write this string to text file
    outTxt<<"hiScore: "<<hiScore<<endl<<endl;  
    outTxt.close(); // close file
}


/**************   WRITE 1 RECORD TO BINARY FILE  ***************/    
void Admin::wrtBin(){
        
    ofstream outBin; 
    outBin.open("data.dat",ios::out | ios::app | ios::binary); // appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening outBin.dat\n";}
    
    unsigned short sizeN = 0, sizeE = 0, sizeP = 0;
    sizeN = getNamSiz();     // get size of this string
    sizeE = getEmaiSiz();    // get size of this string
    sizeP = getPwrdSiz(); // get size of this string
    int hScore = getHiScore(); // get value of hiScore from class
    int idNum = getID();
    //cout<<"\nsizeN= "<<sizeN<<"\nsize= "<<sizeE<<"\nsizeP= "<<sizeP<<endl; 
    
    
    // Write id to binary file
    outBin.write(reinterpret_cast<char *>(&idNum) , sizeof(int)); 
    
    
    // Write the size of this string to binary file
    // and then write this string to binary file
    outBin.write(reinterpret_cast<char *>(&sizeN), sizeof(sizeN)); 
    outBin.write((getName().c_str()), sizeN); 

    
    
    // Write the size of this string to binary file
    // and then write this string to binary file
    outBin.write(reinterpret_cast<char *>(&sizeE), sizeof(sizeE));     
    outBin.write((getEmail().c_str()), sizeE); 
    
    
    // Write the size of this string to binary file
    // and then write this string to binary file
    outBin.write(reinterpret_cast<char *>(&sizeP), sizeof(sizeP)); 
    outBin.write(password.c_str(), pwrdSiz); 
    
    
    // Write hiScore to binary file
    outBin.write(reinterpret_cast<char *>(&hiScore) , sizeof(int)); 
      
    outBin.close(); // close file    
}



/******************************************************************/
/***************READ BINARY FILE & RETURN 1 RECORD ***************/
/*****************************************************************/

void Admin::find1Record(int recIndx){ 
    
    cout<<endl<<endl<<"Looking for record "<<recIndx<<" in binary file.\n\n";  
    
    recIndx = recIndx < 0 ? 0 : recIndx;
    
    ifstream inBin;
    inBin.open("data.dat",ios::in | ios::binary); // appends content to the current content of the file.
    if(!inBin.is_open()){ cout<<"\nError opening inBin.dat\n"; return;}
    
    long cursor = 0L;
    int count = 1;       // start at 1, so it stops before the record I'm looking for
    unsigned short size = 0;
    int idSize=0, 
        hScore = 0;        
      
    
    // Accumulate all the bits between the beginning of file up the record I'm looking for.
    while(count<=recIndx){ 
                    
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&idSize) , sizeof(int)); 
        cursor += sizeof(idSize);  
        //cout<<sizeof(idSize)<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        inBin.read(reinterpret_cast<char *>(&size), sizeof(size) ); // read the size of this string to binary file       
        cursor += ( sizeof(size) + size*sizeof(char) );
        //cout<<"     sizeof(size) = "<<sizeof(size)<<"\nsize*sizeof(char) = "<<size*sizeof(char)<<endl; 
        //cout<<"this record sum = "<<(sizeof(size)+size*sizeof(char))<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        
        // Read the value of emaiSiz and then use it calculate the number of bits
        // that emaiSiz and email take up in memory. 
        // Add it to cursor and move on to the next variables
        size = 0;
        inBin.read(reinterpret_cast<char *>(&size), sizeof(size) );               
        cursor += ( sizeof(size) + size*sizeof(char) );
        //cout<<"     sizeof(size) = "<<sizeof(size)<<"\nsize*sizeof(char) = "<<size*sizeof(char)<<endl;          
        //cout<<"this record sum = "<<(sizeof(size)+size*sizeof(char) <<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        
        // Read the value of pwrdSiz and then use it calculate the number of bits
        // that pwrdSiz and password take up in memory. 
        // Add it to cursor and move on to the next variables
        size = 0;
        inBin.read(reinterpret_cast<char *>(&size), sizeof(size));      
        cursor += ( sizeof(size) + size*sizeof(char) );        
        //cout<<"     sizeof(size) = "<<sizeof(size)<<"\nsize*sizeof(char) = "<<size*sizeof(char)<<endl;    
        //cout<<"this record sum = "<<(sizeof(size)+size*sizeof(char))<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        // Read in sizeof hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&hScore) , sizeof(int)); 
        cursor += sizeof(hScore);  
        //cout<<sizeof(hScore)<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        count++;
    }
    //cout<<"\n\ncursor = "<<cursor<<" which means it's at the bit before the record we're looking for.\n\n";
    
    
    /******  Find 1 record & save it  *******/
    
    
    // sets cursor at the beginning of the file we're looking for
    inBin.seekg(cursor,ios::beg);
    
    // Read & set idSize in class object
    idSize = 0;
    inBin.read(reinterpret_cast<char *>(&idSize) , sizeof(int)); 
    setID(idSize);     
        
        
    // Read & set the length of name in class object
    size = 0;
    inBin.read(reinterpret_cast<char *>(&size), sizeof(size));
    setNamSiz(size);       
   
    // Read & set name in class object
    string nme  = "";
    nme.resize(size); 
    inBin.read(&nme[0], nme.size()); // write this  string to binary file    
    setName(nme); // Set name in class object
   
     
    // Read & set the length of email in class object
    size = 0;
    inBin.read(reinterpret_cast<char *>(&size), sizeof(size)); 
    setEmaiSiz(size);    // set size of email string
   
    // Read & set email in class object 
    string emai = "";
    emai.resize(size);    
    inBin.read(&emai[0], emai.size());    
    setEmail(emai);
       
    
    // Read & set the length of password in class object
    size = 0;
    inBin.read(reinterpret_cast<char *>(&size), sizeof(size)); 
    setPwrdSiz(size); 
    
    // Read & set email in class object 
    string pwd  = "";
    pwd.resize(size);   
    inBin.read(&pwd[0], pwd.size()); 
    setPwrd(pwd);
    
    // Read & set hiScore in class object
    hScore=0;
    inBin.read(reinterpret_cast<char *>(&hScore) , sizeof(int)); 
    setHiScore(hScore);     
    
    //cout<<"\nInside find1Record()\n";    
    //cout<<"nme = "<<nme<<endl;
    //cout<<"emai = "<<emai<<endl;
    //cout<<"pwd = "<<pwd<<endl;
    //cout<<"hiScore = "<<hScore<<endl;   
    
    inBin.close(); // close file
}


/******************************************************************/
/***************   ACCESSOR FUNCTIONS  ***************************/
/*****************************************************************/


/********  READ INPUT FROM FILE  ************/
void Admin::readInputFile(){
    ifstream inTxt;
    
    inTxt.open("input.txt",ios::in); // read in inputs from a file
    
    if(!inTxt.is_open()){ 
        cout<<"\nError opening inTxt.txt\n";
        exit(0);
    } 
    
    // Save to an array?
    
    inTxt.close();
}

/***********     PRINT ONE USER'S INFO  ******************/
void Admin::print1Profile()const{     
    cout<<"ID:       "<<id<< endl
        <<"Name:     "<<name<< endl
        <<"Email:    "<<email<< endl
        <<"Password: ";
    for(int i=0;i<(pwrdSiz) ;i++){ // prints stars instead of actual password
        cout<< '*';
    }
    cout<<"\nHigh Score: "<<hiScore<<endl<<endl;    
}



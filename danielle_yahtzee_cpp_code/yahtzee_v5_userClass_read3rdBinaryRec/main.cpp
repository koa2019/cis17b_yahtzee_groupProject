/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-10-2023 @ 12:36 PM
 * Purpose:  yahtzee group project-userLogin v6
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
 *     Stops at the beginning of record 3.
 * 
 * v5: At this point program can read in three strings and validate
 *     they meet certain requirements, saves the three variables, then
 *     it writes these 3 strings and their lengths to a text & binary file.
 *     The program opens binary file and looks for the third record in it.
 *     Once it finds the record it reads and saves the length of each string
 *     as well as the actual string. Since this is all working 
 *     I added a User class. It took a LOT of adjustments to get this working again.
 *     This version now does everything it was doing in version 4, 
 *     but now it saves the strings and their lengths inside of class.
 * 
 *      Writing and reading files runs in main(). I will them into functions 
 *      once I add a rand() to randRec.
 * 
 * To do:
         * Add int hiScore=0 to class. Add a setHiScore(int score), getHiScore();
         * Need to add a variable that keeps count of how many records 
           are written. We are appending the files every time the 
           program runs. Static variable doesn't work.
        *  Change password minSize to 7 after testing is finished.
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include <cstdlib>   // rand()
#include <ctime>    // time()
#include <string>   //string var
#include <fstream>
using namespace std;  //STD Name-space where Library is compiled

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

// Function Prototypes


//User Libraries
class User {
    private:
        unsigned short namSiz = 0;
        string name="";    
        unsigned short emaiSiz = 0;
        string email="";    
        unsigned short pwrdSiz = 0;
        string password=""; 
        
        // Private Mutators
        void setNamSiz() { namSiz = name.size(); }
        void setEmaiSiz() { emaiSiz = email.size(); }
        void setPwrdSiz() { pwrdSiz = password.size(); }
        
    public:
        User();     // Default constructor
        User(int);  // Constructor #2
        ~User();
        
        // Mutators
        void setName();
        void setEmail();
        void setPwrd();
        
        bool isMinSize(string , int);
        bool isStrEqual(string, string);
        bool hasSpecialChars(string);
        bool confrmEmail(string);
        
        // Accessors   
        unsigned short getNamSiz() const { return namSiz; }
        unsigned short getEmaiSiz() const { return emaiSiz; }
        unsigned short getPwrdSiz() const { return pwrdSiz; }
        string getName() const{ return name;}
        string getEmail() const{ return email;}
        string getPwrd() const{ return password;}
        void print1User(); 
};

//   Default Constructor
User::User(){
    namSiz = 0;
    name = "";
    emaiSiz = 0;
    email = "";
    pwrdSiz = 0;
    password = ""; 
}

//   Destructor
User::~User(){
    cout<<"\nHit Destructor()\n";
}
       


//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here
    //srand(static_cast<unsigned int>(time(0)));
    //rand()%90+10;//2 digit numbers
    
    //Declare variables here
    User user;
    
    // Create 1 profile
//    user.setName();
//    user.setEmail();
//    user.setPwrd();
     
    
    // Print 1 profile
    //user.print1User();
    
 /********* START WRITING TO TEXT AND BINARY FILES  ********/
    
//    cout<<endl<<endl;
//    
//    ofstream outTxt, outBin;
//    outTxt.open("data.txt",ios::out | ios::app); // appends content to the current content of the file.
//    if(!outTxt.is_open()){ cout<<"\nError opening outTxt.txt\n";}
//    
//    outBin.open("data.dat",ios::out | ios::app | ios::binary); // appends content to the current content of the file.
//    if(!outBin.is_open()){ cout<<"\nError opening outBin.dat\n";}
//    
//    unsigned short sizeN = 0, sizeE = 0, sizeP = 0;
//    sizeN = user.getNamSiz();     // get size of this string
//    sizeE = user.getEmaiSiz();    // get size of this string
//    sizeP = user.getPwrdSiz(); // get size of this string
//    cout<<"\nsizeN= "<<sizeN<<"\nsize= "<<sizeE<<"\nsizeP= "<<sizeP<<endl; 

    
    /**************   WRITE 1 RECORD TO TEXT FILE  ***************/
//    static int rcCount = 6;
//    outTxt<<"record "<<rcCount<<endl;
//    outTxt<<sizeN<<endl; // write the size of this string to text file
//    outTxt<<user.getName()<<endl;  // write this string to text file
//    outTxt<<sizeE<<endl; // write the size of this string to text file
//    outTxt<<user.getEmail()<<endl;  // write this string to text file
//    outTxt<<sizeP<<endl; // write the size of this string to text file
//    outTxt<<user.getPwrd()<<endl<<endl;   // write this string to text file
//    rcCount++;
    
    /**************   WRITE 1 RECORD TO BINARY FILE  ***************/    
    
//    outBin.write(reinterpret_cast<char *>(&sizeN), sizeof(sizeN) ); // write the size of this string to binary file
//    outBin.write( (user.getName().c_str() ), sizeN); // write this actual string to binary file
//    
//   
//    outBin.write(reinterpret_cast<char *>(&sizeE), sizeof(sizeE) ); // write the size of this string to binary file
//    outBin.write((user.getEmail().c_str() ), sizeE); // write this actual string to binary file
//    
//   
//    outBin.write(reinterpret_cast<char *>(&sizeP), sizeof(sizeP) ); // write the size of this string to binary file
//    outBin.write( (user.getPwrd().c_str()), sizeP); // write this actual string to binary file
//    
//    // close files
//    outTxt.close();
//    outBin.close();
    
    
    
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
                    
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file       
        cout<<"     sizeof(sz) = "<<sizeof(sz)<<"\nsz*sizeof(char) = " << sz*sizeof(char)<<endl; 
        cout<<"this record sum = "<< (sizeof(sz) + sz*sizeof(char)) <<endl;
        cursor += ( sizeof(sz) + sz*sizeof(char) );
        cout<<"\t   cursor = "<<cursor<<endl;
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        // Read the value of emaiSiz and then use it calculate the number of bits
        // that emaiSiz and email take up in memory. 
        // Add it to cursor and move on to the next variables
        sz = 0;
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file              
        cout<<"     sizeof(sz) = "<<sizeof(sz)<<"\nsz*sizeof(char) = " << sz*sizeof(char)<<endl;          
        cout<<"this record sum = "<< (sizeof(sz) + sz*sizeof(char)) <<endl;
        cursor += ( sizeof(sz) + sz*sizeof(char) );
        cout<<"\t   cursor = "<<cursor<<endl;
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        // Read the value of pwrdSiz and then use it calculate the number of bits
        // that pwrdSiz and password take up in memory. 
        // Add it to cursor and move on to the next variables
        sz = 0;
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file      
        cout<<"     sizeof(sz) = "<<sizeof(sz)<<"\nsz*sizeof(char) = " << sz*sizeof(char)<<endl;    
        cout<<"this record sum = "<< ( sizeof(sz) + sz*sizeof(char) ) <<endl;
        cursor += ( sizeof(sz) + sz*sizeof(char) );        
        cout<<"\t   cursor = "<<cursor<<endl;
        
        count++;
    }
    cout<<endl<<endl;
    
    
    
    cout<<"cursor = "<<cursor<<" which means it's at the last bit before the record we're looking for.\n\n";
    
    // sets cursor at the beginning of the file we're looking for
    inBin.seekg(cursor,ios::beg);
    
    cout<<"Found record " << randRec <<endl;
    
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // write the size of this string to binary file
    nme = "";
    nme.resize(sz); 
    inBin.read(&nme[0], nme.size()); // write this actual string to binary file    
    //cout<<"sizeof(sz) = "<<sizeof(sz)<<"\nnme.size() = " << nme.size()<<endl;    
    
    
    sz = 0;
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // write the size of this string to binary file
    emai = "";
    emai.resize(sz);    
    inBin.read(&emai[0], emai.size()); // write this actual string to binary file    
    //cout<<"sizeof(sz) = "<<sizeof(sz)<<"\nemai.size() = " << emai.size()<<endl;    
   
    
    sz = 0;
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // write the size of this string to binary file
    pwd = "";
    pwd.resize(sz);   
    inBin.read(&pwd[0], pwd.size()); // write this actual string to binary file    
    //cout<<"sizeof(sz) = "<<sizeof(sz)<<"\npwd.size() = " << pwd.size()<<endl;    
    
    cout<<"nme = "<<nme<<endl;
    cout<<"emai = "<<emai<<endl;
    cout<<"pwd = "<<pwd<<endl;
    
    inTxt.close();
    inBin.close();
    
    
    return 0;
}

/**********  Function definitions  **************/
void User::print1User(){
    cout<<endl
        <<"Profile successfully created.\n"
        <<"Name: " << getName() << endl
        <<"Email: " << getEmail() << endl
        <<"Password: ";
    for(int i=0;i<(getPwrd().length()) ;i++){
        cout<< '*';
    }
    cout<<endl;
}

// SET NAME. Loops until a name's length is within the range
void User::setName(){
    
    bool isLeng=true;
    string n="";
    
    // Loop until a valid name is entered
    do {
        cout<<"\nEnter your name. Must be at least 2 characters: ";
        getline(cin,n);
        
        // Set flag. Confirm name is at least 2 characters long
        isLeng = isMinSize(n,2);
       
    } while(!isLeng);
    
    name = n;     // set variable in class
    
    setNamSiz();  // set this string's length in the class
}

//  SET EMAIL. Loops until a email's length is within the range
//             and contains '@' and '.' 
void User::setEmail(){
    
    string em="";
    
    // Loop until a valid email is entered
    bool isEmail = true, isLeng=true;
    unsigned short minSize=9;
    
    do {
        cout<<"\nEnter your email: ";
        cin>>em;
        
        // Set flags. Confirm emails length and that it contains '@' and '.'
        isEmail = confrmEmail(em);
        isLeng = isMinSize(em, minSize);
        
    } while( !isEmail || !isLeng );
    
    email = em;   // set variable in class
    setEmaiSiz(); // set this string's length in the class
}


//  SET PASSWORD.  Loops until a password's length is within the range
//             and contains at least 1 digit, 1 uppercase and 1 special char
void User::setPwrd(){
    
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
    
    password = pwd; // set variable in class
    
    setPwrdSiz();  // set this string's length in the class
}


/*********  Confirms strings length is within a range  ***********/
bool User::isMinSize(string str, int minLeng){
    
    if(str.length() < minLeng || str.length() > 70){ 
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

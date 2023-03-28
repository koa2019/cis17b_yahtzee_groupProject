
//System Libraries
//#include <iostream>   //Input/Output Library
//#include <cstdlib>   // rand()
//#include <ctime>    // time()
//#include <string>   //string variable
//#include <cstring>  // c-strings
//#include <cctype>  // helper functions for c-strings
//#include <fstream> // input/output for files
using namespace std;  //STD Name-space where Library is compiled
#include "User.h"


/*****************************************************************/
//       Definition of ttlRec static member variable   
/*****************************************************************/
int User::ttlRec = 0;


//****************************************************************
//      Definition of static member().
//      Keeps count how many records will ever be written, so we can
//      write it in the data text file
//****************************************************************

void User::addTtlRec(){
    ttlRec++;
    //cout<<"ttlRec= "<<ttlRec<<endl;
}

/*****************************************************************/
//                Default Constructor
/*****************************************************************/

User::User(){    
    id = rand()%((0+16)+3);
    namSiz=0;
    name="";
    emaiSiz=0;
    email="";
    pwrdSiz=0;
    password=""; 
    hiScore=0;    
}

/*****************************************************************/
//                    Constructor #2
/*****************************************************************/

User::User(int idNum){
    id = idNum;
    namSiz=0;
    name="";
    emaiSiz=0;
    email="";
    pwrdSiz=0;
    password=""; 
    hiScore=0;    
}

/*****************************************************************/
//                          Destructor
/*****************************************************************/

User::~User(){
    cout<<"\nHit User Destructor(). Static class, so nothing to destroy.\n";
}
     





/*******************************************************************/
//
//                   HELPER FUNCTION SECTION
//               FOR CREATING NEW CLASS OBJECT  
//
/*****************************************************************/


//******************************************************************************
//              Checks is user's login matches the database
//
//       NEED to add function that searches binary for a specific email
//******************************************************************************

void User::usrLogin(){    
    
    cout<<"\n\tUser Login\n";
            
    string emai = "aa@aa.com", pwrd = "ppppppp";
    string tempE="",
           tempPw="";
    bool isLeng=false,
         isEmail=false,
         isName=false,
         isPwrd=false;
    
    do {
        cout<<"\n   Enter email: ";
        cin>>tempE;
    } while(!(isMinSize(tempE,8)) || !(confrmEmail(tempE)));
     
    do{
        cout<<"Enter password: ";
        cin>>tempPw;       
    } while(!(isMinSize(tempPw,7)));
    
    isName = isStrEqual(emai,tempE);
    isPwrd = isStrEqual(pwrd,tempPw);
    
    if(!isName || !isPwrd){ 
        cout<<"Username and/or password does not match.\n";      
        exit(0);//refresh page with javascript
        
    } else {
        cout<<"Login was successful.\n";
        //string nam="";
        //or copy constuctor?
        //User(nam,emai,pwrd);
        //openGame();
    }
}
    

//******************************************************************************
//            Allows user to create up to 4 profiles in one session
//******************************************************************************
   
void User::signUp(){    
    
    int num=0;    
    const int MAXACCTS=4; // Don't want a site to crash if someone created a bunch of profiles @once
    bool isAgain=true,
         isNameGood=false,
         isEmailGood=false,
         isPwrdGood=false;
    char ans='n';
    int count=0;  
    int recrdCnt = User::getTtlRec();  // Gets the total # of profiles created.
                                        // Using it as a record counter
        
    // Loop until user is finished creating profiles
    while(isAgain){
                
        num = 10*(rand()%(0+16)+1) * (rand()%(17+29)+1);
        setID(num);
        
        // If user's input was valid, then write it files
        if(isName() && isEmail() && isPwrd()){       
                       
            wrtTxt('u');  // Write to text file
            wrtBin('u'); // Write to binary file 
            
            cout<<"\nProfile successfully created.\n";
            print1Profile();     // Print 1 profile
            User::addTtlRec(); // increment total # of profiles created

        } else { cout<<"\nOops! Profile not created.\n"; }
    
        
        // Conditional only allows a max number of profiles to be created        
        if(count+1 >= MAXACCTS) {
            
            cout<<"\nYou've reached maximum number of players you can create in 1 session.\n";
            isAgain=false;
            
        } else {
            
            cout<<"\nWould you like to create another user profile?\nY for yes or N for no.\n";
            cin>>ans;
            cin.ignore();
            
            // Checks if user wants to create another profile
            if(ans == 'y' || ans == 'Y'){                
                isAgain=true; 
                count++;                            
            }                   
            else { isAgain=false; } 
        }
    } // Ends while loop
}


//******************************************************************************
//            Loops until a name's length is within the range   
//******************************************************************************

bool User::isName(){
    
    bool isLeng = true;
    const unsigned short  MIN = 2;
    const unsigned short MAX_ATTEMPTS=4;
    unsigned short count=0;  
    
    string n = "";
    
    // Loop until a valid name is entered
    do {
        cout<<"\nEnter your name. Must be at least 2 characters: ";
        getline(cin,n);
        
        // Set flag. Confirm name is at least 2 characters long
        isLeng = isMinSize(n,MIN);
       
    } while(!isLeng);
    
    if(isLeng){
        // changes to lowercase & set variable in class    
        // Reset class member variables         
        setName(toLowerCase(n));
        setNamSiz(n.size()); 
        return true;
    }    
    
    return false;
}


//******************************************************************************
//         Loops until a email's length is within the range  
//         AND contains '@' AND '.'                              
//******************************************************************************

bool User::isEmail(){
    
    bool isEmail = true, 
          isLeng = true;
    const unsigned short MINSIZE = 8;
    const unsigned short MAX_ATTEMPTS=4;
    unsigned short count=0;  
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
        setEmail(toLowerCase(em));
        setEmaiSiz(em.size());   
        return true;
    }       
    return false;
}


//******************************************************************************
//          Loops until a password's length is within the range &
//          contains at least 1 digit, 1 uppercase and 1 special char   
//******************************************************************************

bool User::isPwrd(){
    
    const unsigned short MINSIZE=7;
    const unsigned short MAX_ATTEMPTS=4;
    unsigned short count=0;    
    bool isPwd   = true,  // password meets all of its criteria 
         isLeng  = true, // string is minimum length
         hasSpCh = true; // string contains one of these special chars
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
        setPwrd(toLowerCase(pwd));
        setPwrdSiz(pwd.size());   
        return true;        
    } else { return false; }
}

//******************************************************************************
//              Confirms strings length is within a range 
//******************************************************************************

bool User::isMinSize(string str, int minLeng){
    
    if(str.size() < minLeng || str.size() > 70){ 
        cout<<"\nError. Minimum length is: "<<minLeng<<endl;
        if(str.length()>70){ cout<<"\nError. Input is too long.\n"; }
        return false; 
    }
    return true;            
}


//******************************************************************************
//             Confirms strings are identical   
//******************************************************************************

bool User::isStrEqual(string password, string tempPwd){ 
    if( password.compare(tempPwd) !=0 ){ 
        cout<<endl<<"Passwords must match!\n";
        return false; 
    }
    return true;   
}

//******************************************************************************
//    Confirms password includes at least 1 digit, uppercase & special char 
//******************************************************************************

bool User::hasSpecialChars(string pwd){
     
    bool isValid1=true,
         isValid2=true,
         isValid3=true;
    
    // Check if password has at least 1 digit
    for(int i=0;i<pwd.length();i++){        
       
        if( isdigit(pwd[i]) !=0 ){    
            isValid1 = true;
            break;
        } else { isValid1 = false; }
    }  
    
    // Check if password has at least 1 uppercase letter
    for(int i=0;i<pwd.length();i++){
        if( isupper(pwd[i]) !=0 ){
            isValid2 = true;
            break;
        } else { isValid2 = false; }  
    }
    
    
    // Check if password has at least 1 special character
    for(int i=0;i<pwd.length();i++){
        if( pwd[i]=='!' || pwd[i]=='$' || pwd[i]=='#'){
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


//******************************************************************************
//           Confirm email string contains '@' AND '.' in it  
//******************************************************************************

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


// Accepts score from game and checks if it is higher than the current hiScore
bool User::checkHiScore(int score){
    if(score > hiScore) { 
        setHiScore(score); // Call private member function to reset hiScore
        return true;
    } 
    return false;
}


// Converts any uppercase characters to lowercase letters
string User::toLowerCase(string n){       
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
void User::wrtTxt(const char ch){
    
    ofstream outTxt;
    if(ch=='u'){
        outTxt.open("usrData.txt",ios::out | ios::app); // appends content to the current content of the file.
        if(!outTxt.is_open()){ cout<<"\nError opening usrData.txt\n"; exit(0);}      
    
    } else {
        outTxt.open("admin.txt",ios::out); // DOES NOT appends content to the current content of the file.
        if(!outTxt.is_open()){ cout<<"\nError opening admin.txt\n"; exit(0);}
    }
    outTxt<<"Record "  <<ttlRec<<endl;
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
void User::wrtBin(const char ch){
        
    ofstream outBin; 
    if(ch=='u'){
        outBin.open("usrData.dat",ios::out | ios::app | ios::binary); // appends content to the current content of the file.
        if(!outBin.is_open()){ cout<<"\nError opening outBin.dat\n";}
    
    } else {
        outBin.open("admin.dat",ios::out | ios::app | ios::binary); // appends content to the current content of the file.
        if(!outBin.is_open()){ cout<<"\nError opening outBin.dat\n";}
    }
    
    // Write total records to binary file
    outBin.write(reinterpret_cast<char *>(&ttlRec) , sizeof(int)); 
    
    
    // Write id to binary file
    outBin.write(reinterpret_cast<char *>(&id) , sizeof(int)); 
    
    
    // Write name's length to binary file
    // and then write this string to binary file
    outBin.write(reinterpret_cast<char *>(&namSiz), sizeof(unsigned short)); 
    outBin.write(name.c_str(), namSiz*sizeof(char)); 

    
    
    // Write email's length to binary file
    // and then write this string to binary file
    outBin.write(reinterpret_cast<char *>(&emaiSiz), sizeof(unsigned short));     
    outBin.write( email.c_str(), emaiSiz*sizeof(char)); 
    
    
    // Write password's length to binary file
    // and then write this string to binary file
    outBin.write(reinterpret_cast<char *>(&pwrdSiz), sizeof(unsigned short)); 
    outBin.write(password.c_str(), pwrdSiz*sizeof(char)); 
    
    
    // Write hiScore to binary file
    outBin.write(reinterpret_cast<char *>(&hiScore) , sizeof(int)); 
      
    outBin.close(); // close file    
}




/******************************************************************/
//
//                     ACCESSOR FUNCTIONs SECTION
//
/*****************************************************************/
void User::getAdLogin(){    
    //    Admin oneAdmin;
    //adminLogin();
}





/*****************************************************************/
//                     PRINT ONE USER'S INFO  
/*****************************************************************/

void User::print1Profile()const{  
    
    cout<<"Record: "  <<ttlRec<<endl
        <<"ID:       "<<id<< endl
        <<"Name:     "<<name<< endl
        <<"Email:    "<<email<< endl
        <<"Password: ";
    for(int i=0;i<(pwrdSiz) ;i++){ // prints stars instead of actual password
        cout<< '*';
    }
    cout<<"\nHigh Score: "<<hiScore<<endl<<endl;    
}



/*****************************************************************/
//                READ INPUT FROM FILE  
/*****************************************************************/

void User::readInputFile(){
    
    ifstream in;    
    in.open("input.txt",ios::in); // read in inputs from a file    
    if(!in.is_open()){ 
        cout<<"\nError opening inTxt.txt\n";
        return;
    } 
    
    int count=0, 
        num=0;
    string n="", em="", pwd="";
    bool isNameGood,isEmailGood,isPwrdGood,isLeng,isEmail,isPwd,hasSpCh;
    
    
    while(!in.eof() && count<28){
        
        
        // Read name  from file & validate
        getline(in,n);
        
        isLeng = isMinSize(n,2);
        if(isLeng){               
                setName(toLowerCase(n));
                setNamSiz(n.size());
                isNameGood = true;
        } else { isNameGood = false;}

        // Read email  from file & validate
        in>>em;
        
        isEmail = confrmEmail(em); // Set flags. Confirm emails length and that it contains '@' and '.'
        isLeng = isMinSize(em, 8);
        if(isEmail && isLeng){ 
            setEmail(toLowerCase(em));
            setEmaiSiz(email.size());                 
            isEmailGood = true;
        } else { isEmailGood = false;}
        
        
        // Read password from file
        in>>pwd;
        in.ignore();
        
        isPwd = isMinSize(pwd,7); 
        hasSpCh = hasSpecialChars(pwd);  
        if(isPwd){
            setPwrd(toLowerCase(pwd));
            setPwrdSiz(password.size());              
            isPwrdGood = true;
        } else { isPwrdGood = false;}
        
        
        // SAVE TO TEXT FILE & BINARY FILE
        count++;
        num = 10*(rand()%(0+16)+3) * (rand()%(0+9)+1);
        setID(num);
        
        if(isNameGood && isEmailGood && isPwrdGood){       
            wrtTxt('u');  // Write to text file
            wrtBin('u');  // Write to binary file 
            
            cout<<"\nProfile successfully created.\n";
            //print1Profile();     // Print 1 profile
            User::addTtlRec(); // increment total # of profiles created

        } else { cout<<"\nOops! Profile not created.\n"; }      
    } 
    in.close();
}
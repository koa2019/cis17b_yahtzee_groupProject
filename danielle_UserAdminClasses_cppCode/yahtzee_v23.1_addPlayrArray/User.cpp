using namespace std;  //STD Name-space where Library is compiled
#include "User.h"
#include <iostream>
#include <fstream>
#include <string>


//****************************************************************
//         Read how many records there in binary from a text file      
//****************************************************************

void User::readNumRec(){
    
    ifstream in;    
    in.open("numRecrds.txt", ios::in); 
    if(!in.is_open()){ cout<<"\nError opening numRecrds.txt\n"; return;}
    int num;
    in>>num;
    setNumRec(num);
    //cout<<"\nIn readNumRec(). numRec= "<< numRec<<endl;  
    in.close();
}


//****************************************************************
//         Write how many records there in a text file   
//****************************************************************

void User::wrtNumRec(){
    ofstream out;    
    out.open("numRecrds.txt", ios::out); 
    if(!out.is_open()){ cout<<"\nError opening numRecrds.txt\n"; return;}
    out<<numRec;
    //cout<<"\nIn wrtNumRec(). numRec= "<< numRec<<endl;  
    out.close();    
}


/*****************************************************************/
//                Default Constructor
/*****************************************************************/

User::User(){   
    //cout<<"\nHit User Default constructor\n";
    readNumRec();  
    namSiz=0;
    name="";
    emaiSiz=0;
    email="";
    pwrdSiz=0;
    password="";  
    hiScore=0;
}

/*****************************************************************/
//                     Constructor #2
//                  Called in readInputFile()
/*****************************************************************/

User::User(string n, string e, string p){
    //cout<<"\nHit User constructor #2\n";
        readNumRec(); 
        setName(n);
        setEmail(e);
        setPwrd(p);
        hiScore=0;
        wrtTxt();
        wrtBin();
        addNumRec(); // increment total # of profiles created       
        wrtNumRec(); 
}


/*****************************************************************/
//                     Constructor #3
//                  Called in Yahtzee class & main()
/*****************************************************************/

User::User(string n){
    
    //cout<<"\nHit User constructor #3\n";
    readNumRec();
    addNumRec(); // increment total # of profiles created
    setName(n); // namSize is automatically set when setName() is called
    emaiSiz=0;
    email="";
    pwrdSiz=0;
    password=""; 
    hiScore=0;
    //printUsr();
}


/*****************************************************************/
//                  Constructor #4
/*****************************************************************/

//User::User(int rec, string n, string e, string p){
//    //cout<<"\nHit User constructor #4\n";
//    setNumRec(rec);
//    setName(n);
//    setNamSiz(n.size());
//    setEmail(e);
//    setEmaiSiz(e.size());
//    setPwrd(p);
//    setPwrdSiz(p.size());
//    hiScore=0;
//}


/*****************************************************************/
//                  Constructor #5
//                  Admin calls it in getAllUsr()
/*****************************************************************/

User::User(int rec){
    //cout<<"\nHit User constructor #5\n";
    numRec = rec;
    namSiz=0;
    name="";
    emaiSiz=0;
    email="";
    pwrdSiz=0;
    password="";  
    hiScore=0;
}


/******************************************************************/              
//                  WRITE 1 RECORD TO TEXT FILE     
/*****************************************************************/

void User::wrtTxt(){
    
    ofstream outTxt; 
    outTxt.open("usrData.txt", ios::out | ios::app); // appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening usrData.txt\n"; exit(0);}      
 
    outTxt<<endl;
    outTxt<<"Record   "<<numRec<<endl;
    outTxt<<"namSiz:  "<<namSiz<<endl; // write the size of this string to text file
    outTxt<<"name:    "<<name<<endl;   // write this string to text file
    outTxt<<"emaiSiz: "<<emaiSiz<<endl;// write the size of this string to text file
    outTxt<<"email:   "<<email<<endl;  // write this string to text file
    outTxt<<"pwrdSiz: "<<pwrdSiz<<endl; // write the size of this string to text file
    outTxt<<"pwrd:    "<<password<<endl;// write this string to text file 
    outTxt<<"hiScore: "; 
    outTxt<< (hiScore/100) << (hiScore/10%10) << (hiScore%10) <<endl; 
    outTxt.close(); // close file
}


/******************************************************************/              
//                  WRITE 1 RECORD TO BINARY FILE     
/*****************************************************************/

void User::wrtBin(){
        
    ofstream outBin; 
    outBin.open("usrData.dat",ios::out | ios::app | ios::binary); // appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening usrData.dat\n";}
    
    // Write total records to binary file
    outBin.write(reinterpret_cast<char *>(&numRec) , sizeof(int)); 
    
       
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
//                  REWRITE 1 RECORD in Text FILE    
//          Important! When you change # bits in any variable it 
//                  will effect rewriting it in text file
/*****************************************************************/

void User::reWrtTxt(long begnFile){
        
    //cout<<"\n\nHit reWrtTxt()  recSize= "<<recSiz<<"  begnFile = "<<begnFile<<endl;
    
    fstream outTxt; 
    outTxt.open("usrData.txt", ios::ate | ios::in | ios::out ); // appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening usrData.txt\n";}
    
    //cout<<"\ngetNumRec() = "<<getNumRec()<<endl;
    
    int charCount = (getNumRec()==0) ? 0 : ((76)*getNumRec());
    
    //cout<<"\ncharCount = "<< charCount <<endl;
    
    long cursor = (begnFile <= 0) ? 0 : (begnFile+charCount); // hiScore is a int which is 4 bits
    
    //cout<<"begnFile = "<< cursor <<endl;
    
    outTxt.seekp(cursor,ios::beg);  // Sets the position of the get pointer
       
    outTxt<<endl;
    outTxt<<"Record   "<<numRec<<endl;
    outTxt<<"namSiz:  "<<getNamSiz()<<endl; // write the size of this string to text file
    outTxt<<"name:    "<<getName()<<endl;   // write this string to text file
    outTxt<<"emaiSiz: "<<getEmaiSiz()<<endl;// write the size of this string to text file
    outTxt<<"email:   "<<getEmail()<<endl;  // write this string to text file
    outTxt<<"pwrdSiz: "<<getPwrdSiz()<<endl; // write the size of this string to text file
    outTxt<<"pwrd:    "<<getPwrd()<<endl;// write this string to text file 
    outTxt<<"hiScore: "; 
    outTxt<< (getHiScore()/100) << (getHiScore()/10%10) << (getHiScore()%10) <<endl<<endl;
    outTxt.close(); // close file    
}


/******************************************************************/              
//                  REWRITE 1 RECORD TO BINARY FILE     
/*****************************************************************/

void User::reWrtBin(long begnFile){
      
    //cout<<"\n\n Hit reWrtBin()  begnFile = " << begnFile << endl;
    //cout<<"\n\nHit reWrtBin()  recSize = "<< recSiz << "  begnFile = " << begnFile <<endl;
    
    fstream outBin; 
    outBin.open("usrData.dat", ios::ate | ios::in | ios::out | ios::binary); // appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening usrData.dat\n";}
    
    long cursor = (begnFile <= 0) ? 0 : begnFile; 
    
    //cout<<"begnFile = "<< cursor <<endl;
    
    outBin.seekp(cursor,ios::beg);  // Sets the position of the get pointer
        
    // Write total records to binary file
    outBin.write(reinterpret_cast<char *>(&numRec) , sizeof(int));     
   
    
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
   
    
    // Rewrite hiScore in binary file     
    outBin.write(reinterpret_cast<char *>(&hiScore) , sizeof(int)); 
    
    outBin.close(); // close file  
    
    reWrtTxt(begnFile);  // rewrite this record in usrData text file
}



//******************************************************************************
//            Checks if current score is greater than hiScore 
//******************************************************************************

bool User::isHiScore(int score){
    
    if((score > 999 || score < 0)){ return false; }
    // hiScore is formatted for max of 3 digits 
    
    else if(score > hiScore ) { return true; }
    
    else { return false;}
}


//******************************************************************************
//            Loops until a name's length is within the range   
//******************************************************************************

bool User::isName(){
    
    bool isLeng = true;
    const unsigned short  MIN = 2;
    const unsigned short MAX_ATTEMPTS = 4;
    unsigned short count = 0;     
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
//         Loops until a email's length is within range  
//                  AND contains '@' AND '.'                              
//******************************************************************************

bool User::isEmail(){
    
    bool isEmail = false, 
          isLeng = false;
    const unsigned short MINSIZE = 8;
    const unsigned short MAX_ATTEMPTS = 4; // Limits how many time user can re-input
    unsigned short count = 0;  
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
    bool isPwd,  // password meets all of its criteria 
         isLeng, // string is minimum length
         hasSpCh; // string contains one of these special chars
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
       
       if(!isPwd){ cout<<"Passwords must match!\n"; }
         
    } while( !isPwd );
    
    if(isPwd){
        setPwrd(pwd);
        setPwrdSiz(pwd.size());   
        return true; 
    }
    
    return false; 
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
        return false; 
    }
    return true;   
}

//******************************************************************************
//    Confirms password includes at least 1 digit, uppercase & special char 
//******************************************************************************

bool User::hasSpecialChars(string pwd){
     
    bool isValid1=false,
         isValid2=false,
         isValid3=false;
    
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

/******************************************************************/              
//      Converts any uppercase characters to lowercase letters
/*****************************************************************/
   
string User::toLowerCase(string n){       
    string str="";
    for(int i=0;i<n.size();i++){
        str += tolower(n[i]);
    }
    return str;
}

/*****************************************************************/
//                     PRINT ONE USER'S INFO  
/*****************************************************************/

void User::printUsr()const{  
    
    cout<<"\nRecord:   "<< numRec <<endl
        <<"Name:       "<< name   <<endl
        <<"Email:      "<< email  <<endl
        <<"Password:   "<<password<<endl
        <<"High Score: "<<hiScore<<endl;
}

/*****************************************************************/
//                     PRINT 1 record  
/*****************************************************************/

void User::printUsrRec() const{  
   
    cout<<"\nRecord:   "<< numRec <<endl
        <<"NamSiz:     "<< namSiz <<endl
        <<"Name:       "<< name    <<endl
        <<"EmaiSiz:    "<< emaiSiz <<endl
        <<"Email:      "<< email   <<endl
        <<"PwrdSiz:    "<< pwrdSiz <<endl
        <<"Password:   "<< password<<endl
        <<"High Score: "<< hiScore<<endl;
}


//******************************************************************************
//            Allows user to create up to 4 profiles in one session
//******************************************************************************
   
void User::signUp(){  

    // If user's input was valid, then write it files
    if(isName() && isEmail() && isPwrd()){       
        
        wrtTxt();  // Write to text file
        wrtBin(); // Write to binary file 

        cout<<"\nProfile successfully created.";
        printUsr();     // Print 1 profile
        setNumRec(numRec);
        addNumRec(); // increment total # of profiles created         
        wrtNumRec();
        
    } else { cout<<"\nOops! Profile not created.\n"; }
}



/*****************************************************************/
//                READ INPUT FROM FILE  
/*****************************************************************/

void User::readInputFile(){
    
    // clear usrData text & binary files. Used for testing 
    setNumRec(0);
    wrtNumRec();
    ifstream out, oB;    
    out.open("usrData.txt", ios::out | ios::trunc); // read in inputs from a file    
    if(!out.is_open()){ 
        cout<<"\nError opening usrData.txt\n";
        return;
    } 
    oB.open("usrData.dat",ios::out | ios::trunc); // read in inputs from a file    
    if(!oB.is_open()){ 
        cout<<"\nError opening usrData.dat\n";
        return;
    } 
    out.close();
    oB.close();
    
   User usera("homer simpson","homer@simp.com","Homer!23");
   User userb("marge simpson","marge@simp.com","Marge$ab");
   User userd("lisa simpson","lisa@simp.com","Lisa!2345");   
   User userc("day tripper","lucy@beatles.com","DayT#2345"); 
}
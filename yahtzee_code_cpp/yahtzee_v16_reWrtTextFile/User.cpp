using namespace std;  //STD Name-space where Library is compiled
#include "User.h"
#include <iostream>
#include <fstream>
#include <string>

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
    wrtTtlRec();
    //cout<<"ttlRec= "<<ttlRec<<endl;
}
//****************************************************************
//      Definition of static member().
//      
//****************************************************************

void User::readTtlRec(){
    
    ifstream in;    
    in.open("numRecrds.txt", ios::in); 
    if(!in.is_open()){ cout<<"\nError opening numRecrds.txt\n"; return;}
    int num;
    in>>num;
    setTtlRec(num);
    //cout<<"\nIn readTtlRec(). ttlRec= "<< ttlRec<<endl;  
    in.close();
}
//****************************************************************
//      Definition of static member().
//     
//****************************************************************

void User::wrtTtlRec(){
    ofstream out;    
    out.open("numRecrds.txt", ios::out); 
    if(!out.is_open()){ cout<<"\nError opening numRecrds.txt\n"; return;}
    out<<ttlRec;
    //cout<<"\nIn wrtTtlRec(). ttlRec= "<< ttlRec<<endl;  
    out.close();    
}


/*****************************************************************/
//                Default Constructor
/*****************************************************************/

User::User(){   
    //cout<<"\nHit User Default constructor\n";
    readTtlRec();  
    id = 10*(rand()%(0+16)+1) * (rand()%(17+29)+1);
    namSiz=0;
    name="";
    emaiSiz=0;
    email="";
    pwrdSiz=0;
    password="";  
    hiScore=0;
}

/*****************************************************************/
//                  Constructor #2
/*****************************************************************/

User::User(string n, string e, string p){
    cout<<"\nHit User constructor #2\n";
        readTtlRec(); 
        id = 10*(rand()%(0+16)+1) * (rand()%(17+29)+1);
        setName(n);
        setNamSiz(n.size());
        setEmail(e);
        setEmaiSiz(e.size());
        setPwrd(p);
        setPwrdSiz(p.size());
        hiScore=0;
}


/*****************************************************************/
//                  Constructor #3
/*****************************************************************/

User::User(int i, string n, string e, string p){
    cout<<"\nHit User constructor #3\n";
        setTtlRec(i);
        id = 10*(rand()%(0+16)+1) * (rand()%(17+29)+1);
        setName(n);
        setNamSiz(n.size());
        setEmail(e);
        setEmaiSiz(e.size());
        setPwrd(p);
        setPwrdSiz(p.size());
        hiScore=0;
}


/*****************************************************************/
//                  Constructor #4
/*****************************************************************/

User::User(int rec, int i, string n, string e, string p){
    cout<<"\nHit User constructor #4\n";
        setTtlRec(rec);
        setID(i);
        setName(n);
        setNamSiz(n.size());
        setEmail(e);
        setEmaiSiz(e.size());
        setPwrd(p);
        setPwrdSiz(p.size());
        hiScore=0;
}


/******************************************************************/              
//                  WRITE 1 RECORD TO TEXT FILE     
/*****************************************************************/

void User::wrtTxt(){
    
    ofstream outTxt; 
    outTxt.open("usrData.txt", ios::out | ios::app); // appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening usrData.txt\n"; exit(0);}      
 
//    outTxt<<endl;
//    outTxt<<ttlRec<<endl;
//    outTxt<<id<<endl;      // write id to text file
//    outTxt<<namSiz<<endl; // write the size of this string to text file
//    outTxt<<name<<endl;   // write this string to text file
//    outTxt<<emaiSiz<<endl;// write the size of this string to text file
//    outTxt<<email<<endl;  // write this string to text file
//    outTxt<<pwrdSiz<<endl; // write the size of this string to text file
//    outTxt<<password<<endl;// write this string to text file 
//    outTxt<<hiScore<<endl; 
    outTxt<<endl;
    outTxt<<"Record   "<<ttlRec<<endl;
    outTxt<<"ID:      "<<id<<endl;      // write id to text file
    outTxt<<"namSiz:  "<<namSiz<<endl; // write the size of this string to text file
    outTxt<<"name:    "<<name<<endl;   // write this string to text file
    outTxt<<"emaiSiz: "<<emaiSiz<<endl;// write the size of this string to text file
    outTxt<<"email:   "<<email<<endl;  // write this string to text file
    outTxt<<"pwrdSiz: "<<pwrdSiz<<endl; // write the size of this string to text file
    outTxt<<"pwrd:    "<<password<<endl;// write this string to text file 
    outTxt<<"hiScore: "; 
    outTxt<< (hiScore/100) << (hiScore/10%10) << (hiScore%10) <<endl<<endl; 
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

void User::print1User()const{  
    
    cout<<"\nRecord: "  << ttlRec <<endl
        <<"ID:       "<< id     <<endl
        <<"Name:     "<< name   <<endl
        <<"Email:    "<< email  <<endl
        <<"Password: "<<password<<endl
        <<"High Score: "<<hiScore<<endl;
}

/*****************************************************************/
//                     PRINT 1 record  
/*****************************************************************/

void User::print1URec() const{  
   
    cout<<"\nRecord:  "<< ttlRec <<endl
        <<"ID:        "<< id     <<endl 
        <<"NamSiz:    "<< namSiz <<endl
        <<"Name:      "<< name    <<endl
        <<"EmaiSiz:   "<< emaiSiz <<endl
        <<"Email:     "<< email   <<endl
        <<"PwrdSiz:   "<< pwrdSiz <<endl
        <<"Password:  "<< password<<endl
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

        cout<<"\nProfile successfully created.\n";
        print1User();     // Print 1 profile
        User::addTtlRec(); // increment total # of profiles created         

    } else { cout<<"\nOops! Profile not created.\n"; }
}



/*****************************************************************/
//                READ INPUT FROM FILE  
/*****************************************************************/

void User::readInputFile(){
    
    // clear usrData text & binary files. Used for testing 
    setTtlRec(0);
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
    
    
    // Start reading inputs from file
    ifstream in;    
    in.open("input.txt",ios::in); // read in inputs from a file    
    if(!in.is_open()){ 
        cout<<"\nError opening inTxt.txt\n";
        return;
    } 
    
   
    
    int count=0, num=0;
    string n="", em="", pwd="";
    bool isNameGood,isEmailGood,isPwrdGood,isLeng,isEmail,isPwd,hasSpCh;
    
    int max = 5; // 27 files 
    
    while(!in.eof() && count<max){        
        
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
            setPwrd(pwd);
            setPwrdSiz(password.size());              
            isPwrdGood = true;
        } else { isPwrdGood = false;}
        
        
        // SAVE TO TEXT FILE & BINARY FILE
        count++;
        num = 10*(rand()%(0+16)+3) * (rand()%(0+9)+1);
        setID(num);
        
        if(isNameGood && isEmailGood && isPwrdGood){       
            wrtTxt();  // Write to text file
            wrtBin();  // Write to binary file 
            
            //cout<<"\nProfile successfully created.\n";
            //print1User();     // Print 1 profile
            User::addTtlRec(); // increment total # of profiles created

        } else { cout<<"\nOops! Profile not created.\n"; }      
    }  
    in.close();
}
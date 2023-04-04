using namespace std;  //STD Name-space where Library is compiled
#include <string>
#include <iostream>
#include "User.h"


//   Destructor
User::~User(){
    cout<<"\nHit User Destructor().";
}



// Calls inherited print function from Admin
// and number of rolls 
void User::print1User() const{
    print1Record();
    cout << "Number of Rolls: " << getNRolls() <<endl;
}

void User::play(){
    
    cout<<"\n\nWelcome to Yahtzee.\n";
    //print1User();
    
    int score = (rand()%50);

    if(isHiScore(score)){
        
        cout<<"\nNew High Score!\n"<<hiScore<<endl;        
        wrtTxt(); 
        wrtBin();
        
    } else {cout<<"\nGood Game!";}
    
    print1User();
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
        Admin::addTtlRec(); // increment total # of profiles created         

    } else { cout<<"\nOops! Profile not created.\n"; }
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
    
    int count=0, num=0;
    string n="", em="", pwd="";
    bool isNameGood,isEmailGood,isPwrdGood,isLeng,isEmail,isPwd,hasSpCh;
    int max = 28; // 27 files 
    
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
            //print1Record();     // Print 1 profile
            Admin::addTtlRec(); // increment total # of profiles created

        } else { cout<<"\nOops! Profile not created.\n"; }      
    }  
    in.close();
}
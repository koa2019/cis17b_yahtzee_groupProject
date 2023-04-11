
//System Libraries
//#include <iostream>   //Input/Output Library
//#include <cstdlib>   // rand()
//#include <ctime>    // time()
//#include <string>   //string variable
//#include <cstring>  // c-strings
//#include <cctype>  // helper functions for c-strings
//#include <fstream> // input/output for files
using namespace std;  //STD Name-space where Library is compiled
#include "Admin.h"


/*****************************************************************/
//       Definition of ttlRec static member variable   
/*****************************************************************/
int Admin::ttlRec = 0;


//****************************************************************
//      Definition of static member().
//      Keeps count how many records will ever be written, so we can
//      write it in the data text file
//****************************************************************

void Admin::addTtlRec(){
    ttlRec++;
    wrtTtlRec();
    //cout<<"ttlRec= "<<ttlRec<<endl;
}
//****************************************************************
//      Definition of static member().
//      
//****************************************************************

void Admin::readTtlRec(){
    
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

void Admin::wrtTtlRec(){
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

Admin::Admin(){    
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
//                          Destructor
/*****************************************************************/

Admin::~Admin(){
    cout<<"\nHit Admin Destructor().";
}
     

/*******************************************************************/
//               ONLY ADMIN CLASS HAS PERMISSION!
//                  Change Admin login info
/*****************************************************************/

void Admin::updateAdmin(){ 
    if(isName() && isEmail() && isPwrd()){  
        cout<<"\nProfile Updated,\n";
        print1Record();
        wrtAdminTxt();
        wrtAdminBin();
    }
}


/******************************************************************/ 
//               ONLY ADMIN CLASS HAS PERMISSION!
//          READ ADMIN BINARY FILE, RETURN 1 RECORD    
//                  & COMPARE IT TO INPUTS
/*****************************************************************/
  
void Admin::adminLogin(){
    
    cout<<"\n\tAdmin Login\n";
    
    const char ch = 'a';   
    const int index = 0;
 
    readBin(ch,index);       
    cout<<getName()<<endl<<getPwrd()<<endl;
    
    string tempNam = "",
           tempPwrd = "";
    
    bool isName=false,
         isPwrd=false;
    
//    do{        
//        cout<<"\nEnter username: ";
//        cin>>tempNam;
//        isName = isMinSize(tempNam,2);
//    } while(!isName);
//    
//    cout<<"Enter password: ";
//    cin>>tempPwrd;
    
    tempNam="admin";
    tempPwrd = "pass!234";
    
    isName = isStrEqual(getName(),tempNam);
    isPwrd = isStrEqual(getPwrd(),tempPwrd);
    
    if(!isName || !isPwrd){ 
        cout<<"Username and/or password does not match.\n";       
        return;//refresh page with javascript
    
    } else { adminPortal(); } // opens function that Admin is only allowed to access
}


/******************************************************************/              
//          ONLY allowed to access these functions  
//                  if logged in as admin
/*****************************************************************/

void Admin::adminPortal(){
    
    cout<<"Admin login successful.\n";
    char ans='n';
    int choice;
     
    do {
        cout<<"\n\nMenu\n"
            <<"Press 1: Update Admin\n"
            <<"Press 2: Find one index\n"
            <<"Press 3: Find by email\n"
            //<<"Press 4: \n"
            //<<"Press 5: \n"
            <<"Press 9: Logout\n";
        cin>>choice;
        cin.ignore();

        switch(choice){
            case 1:{                
                updateAdmin();        
                break;
            } 
            case 2:{ // find index in binary file  
                int oneRec = (rand()%(getTtlRec()));
                readBin('u', 2);    
                print1Record(); 
                break;
            } 
            case 3:{ // find email in binary file
                string em = "sister@sis.com"; //father@email.com
                //cout<<"\n\nEnter email ";
                //cin>>em;     
                int recSize=0;
                long cursor = findEmail('u',em,recSize);
                
                if(!(cursor == -99)){ 
                    
                    cout<<"Found it\n";
                    cout<<"recSize= "<<recSize<<"\ncursor= "<<cursor<<endl;       
                    print1Record(); 
                    setHiScore(3);
                    cout<<"\nNew High Score!";
                    print1Record();
                    reWrtBin(recSize, cursor);
                    //Admin ad;
                    //cout<<"\nLooking for rewritten record...\n";
                    //ad.readBin('u',2);
                }
                else{ cout<<"Unable to locate that email.\n";}
                break;
            }            
            default: {
                cout<<"\nLogged Out.\n";                
                return;
            }
        }
    } while(choice==1 || choice==2 || choice==3);
}


/******************************************************************/ 
//                 ONLY ADMIN CLASS HAS PERMISSION!
//                  WRITE 1 RECORD TO TEXT FILE     
/*****************************************************************/

void Admin::wrtAdminTxt(){
    
    ofstream outTxt; 
    outTxt.open("admin.txt",ios::out); // DOES NOT appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening admin.txt\n"; exit(0);}
    
    outTxt<<"Record "  <<ttlRec<<endl;
    outTxt<<"ID:      "<<id<<endl;      // write id to text file
    outTxt<<"namSiz:  "<<namSiz<<endl; // write the size of this string to text file
    outTxt<<"name:    "<<name<<endl;   // write this string to text file
    outTxt<<"emaiSiz: "<<emaiSiz<<endl;// write the size of this string to text file
    outTxt<<"email:   "<<email<<endl;  // write this string to text file
    outTxt<<"pwrdSiz: "<<pwrdSiz<<endl; // write the size of this string to text file
    outTxt<<"pwrd:    "<<password<<endl;// write this string to text file
    outTxt.close(); // close file
}


/******************************************************************/  
//                 ONLY ADMIN CLASS HAS PERMISSION!
//                  WRITE 1 RECORD TO BINARY FILE     
/*****************************************************************/

void Admin::wrtAdminBin(){
        
    ofstream outBin;
    outBin.open("admin.dat",ios::out | ios::binary); // DOES NOT appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening admin.dat\n";}
        
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


/*****************************************************************/
//               ONLY ADMIN CLASS HAS PERMISSION!
//           Read binary file, find 1 record by email
//                  & return 1 record  
/*****************************************************************/

long Admin::findEmail(const char ch, string emai, int &recSize){ 
    
    cout<<endl<<endl<<"Looking for "<<emai<<" in binary file.\n\n";   
    
    ifstream inBin;
    string file = "";
    file = (ch == 'a') ? "admin.dat" : "usrData.dat";        
    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; exit(0);} 
    
    bool foundEm;
    long cursor = 0L, thisSum=0L;
    int count = 0,   // start at 1, so it stops before the record I'm looking for     
        recIndx=0;
    
    int nRec=getTtlRec();
    //cout<<"ttlRec= "<<nRec<<endl;
    
    // Accumulate all the bits between the beginning of file up the record I'm looking for.
    for(int i=0;i<nRec;i++){ 
    //while( (count <= getTtlRec()) || (!inBin.eof())   ){                 
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&ttlRec) , sizeof(int)); 
        thisSum +=sizeof(int);
        cursor += sizeof(int);  
        //cout<<sizeof(ttlRec)<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&id) , sizeof(int)); 
        thisSum += sizeof(int);
        cursor += sizeof(int);  
        //cout<<sizeof(id)<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        inBin.read(reinterpret_cast<char *>(&namSiz), sizeof(unsigned short) );
        thisSum += ( sizeof(unsigned short) + namSiz*sizeof(char) );
        cursor += ( sizeof(unsigned short) + namSiz*sizeof(char) );
        //cout<<"     sizeof(namSiz) = "<<sizeof(namSiz)<<"\nnamSiz*sizeof(char) = "<<namSiz*sizeof(char)<<endl; 
        //cout<<"this record sum = "<<(sizeof(namSiz)+namSiz*sizeof(char))<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        
        // Read the value of emaiSiz and then use it calculate the number of bits
        // that emaiSiz and email take up in memory. 
        // Add it to cursor and move on to the next variables        
        inBin.read(reinterpret_cast<char *>(&emaiSiz), sizeof(unsigned short) );               
        thisSum += ( sizeof(unsigned short) + emaiSiz*sizeof(char) );
        cursor += ( sizeof(unsigned short) + emaiSiz*sizeof(char) );
        //cout<<"     sizeof(emaiSiz) = "<<sizeof(emaiSiz)<<"\nemaiSiz*sizeof(char) = "<<emaiSiz*sizeof(char)<<endl;          
        //cout<<"this record sum = "<<(sizeof(emaiSiz)+emaiSiz*sizeof(char) <<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        // Read & set email in class object 
        string binEmail = "";
        binEmail.resize(emaiSiz);
        inBin.read(&binEmail[0], emaiSiz*sizeof(char));              
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        
        // Read the value of pwrdSiz and then use it calculate the number of bits
        // that pwrdSiz and password take up in memory. 
        // Add it to cursor and move on to the next variables
       
        inBin.read(reinterpret_cast<char *>(&pwrdSiz), sizeof(unsigned short));      
        thisSum += ( sizeof(unsigned short) + pwrdSiz*sizeof(char) );
        cursor += ( sizeof(unsigned short) + pwrdSiz*sizeof(char) );        
        //cout<<"     sizeof(pwrdSiz) = "<<sizeof(pwrdSiz)<<"\npwrdSiz*sizeof(char) = "<<pwrdSiz*sizeof(char)<<endl;    
        //cout<<"this record sum = "<<(sizeof(pwrdSiz)+pwrdSiz*sizeof(char))<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        // Read in size of hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&hiScore) , sizeof(int)); 
        thisSum += sizeof(int);
        cursor += sizeof(int);
        cout<<sizeof(hiScore)<<endl;
        
        
        foundEm = isStrEqual(emai,binEmail);
        //cout<<"\nFound = "<<foundEm<<endl;
        if(foundEm){
            recIndx=ttlRec; 
            recSize = thisSum;
            cursor -= thisSum;
            //cout<<"found email "<<foundEm<<endl;
            //cout<<"ttlREc= "<<ttlRec<<" recIndx= "<<recIndx<<"  count= "<<count<<endl;
            break;
        }
        else{
            foundEm = false;
            count++;
            recIndx=count;
            thisSum = 0L;    
        }
        //cout<<count<<"=count \t   cursor = "<<cursor<<endl;   
    }
    //cout<<"Out loop foundEm= "<<foundEm<<endl;
    //cout<<"\n\tcursor = "<<cursor<<"  count= "<<count<<"  recIndx= "<<recIndx<<endl;
    
    inBin.close();
    
    if(foundEm){        
        cursor = (count==0) ? 0 : cursor;               
        read1Bin(ch, cursor); //SAVE LOCATED RECORD  
        return cursor;        
    }     
    cursor = -99;
    return cursor;
   
    
}
/******************************************************************/              
//                  REWRITE 1 RECORD TO BINARY FILE     
/*****************************************************************/

void Admin::reWrtBin(int recSize, long cursor){
        
    cout<<"\nHit reWrtBin()  recSize= "<<recSize<<"  cursor= "<<cursor<<endl;
    
    fstream outBin; 
    outBin.open("usrData.dat",ios::out | ios::app | ios::binary); // appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening usrData.dat\n";}
    
    cursor -=4; // hiScore is a int which is 4 bits
    cout<<"cursor= "<<cursor<<endl;
    
    outBin.seekg(cursor,ios::beg);  // Sets the position of the get pointer
        
//    // Write total records to binary file
//    outBin.write(reinterpret_cast<char *>(&ttlRec) , sizeof(int)); 
//    
//    
//    // Write id to binary file
//    outBin.write(reinterpret_cast<char *>(&id) , sizeof(int)); 
//    
//    
//    // Write name's length to binary file
//    // and then write this string to binary file
//    outBin.write(reinterpret_cast<char *>(&namSiz), sizeof(unsigned short)); 
//    outBin.write(name.c_str(), namSiz*sizeof(char)); 
//    
//    
//    // Write email's length to binary file
//    // and then write this string to binary file
//    outBin.write(reinterpret_cast<char *>(&emaiSiz), sizeof(unsigned short));     
//    outBin.write( email.c_str(), emaiSiz*sizeof(char)); 
//    
//    
//    // Write password's length to binary file
//    // and then write this string to binary file
//    outBin.write(reinterpret_cast<char *>(&pwrdSiz), sizeof(unsigned short)); 
//    outBin.write(password.c_str(), pwrdSiz*sizeof(char)); 
    
    cout<<"\nHiScore= "<<hiScore<<endl;
    // Write hiScore to binary file
    outBin.write(reinterpret_cast<char *>(&hiScore) , sizeof(int)); 
      
    outBin.close(); // close file    
}
    
  
/*****************************************************************/
//               ONLY ADMIN CLASS HAS PERMISSION!
//           Read binary file, find 1 record by index
//                     & return 1 record  
/*****************************************************************/

void Admin::readBin(const char ch, int recIndx){ 
    
    //cout<<endl<<endl<<"Looking for record "<<recIndx<<" in binary file.\n\n";  
    
    recIndx = recIndx < 0 ? 0 : recIndx;    
    
    ifstream inBin;
    string file = "";
    file = (ch == 'a') ? "admin.dat" : "usrData.dat";        
    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; return;}
    
    
    long cursor = 0L;
    int count = 1;   // start at 1, so it stops before the record I'm looking for     
    
     
    // Accumulate all the bits between the beginning of file up the record I'm looking for.
    while(count<=recIndx){ 
                    
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&ttlRec) , sizeof(int)); 
        cursor += sizeof(int);          
        
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&id) , sizeof(int)); 
        cursor += sizeof(int);  
       
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        inBin.read(reinterpret_cast<char *>(&namSiz), sizeof(unsigned short) );
        cursor += ( sizeof(unsigned short) + namSiz*sizeof(char) );
               
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        
        // Read the value of emaiSiz and then use it calculate the number of bits
        // that emaiSiz and email take up in memory. 
        // Add it to cursor and move on to the next variables        
        inBin.read(reinterpret_cast<char *>(&emaiSiz), sizeof(unsigned short) );               
        cursor += ( sizeof(unsigned short) + emaiSiz*sizeof(char) );
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        
        // Read the value of pwrdSiz and then use it calculate the number of bits
        // that pwrdSiz and password take up in memory. 
        // Add it to cursor and move on to the next variables       
        inBin.read(reinterpret_cast<char *>(&pwrdSiz), sizeof(unsigned short));      
        cursor += ( sizeof(unsigned short) + pwrdSiz*sizeof(char) );        
        
        
        // Read in size of hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&hiScore) , sizeof(int)); 
        cursor += sizeof(int);  
       
        count++;
    }
       
    //***********    SAVE LOCATED RECORD   ************************//            
    read1Bin(ch, cursor); 
    
    inBin.close(); // close file
}

/*****************************************************************/
//               ONLY ADMIN CLASS HAS PERMISSION!
//                          Read 1 binary & save 
/*****************************************************************/

void Admin::read1Bin(const char ch, long cursor){
    
    ifstream inBin;
    string file = "";
    file = (ch == 'a') ? "admin.dat" : "usrData.dat";        
    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; return;}
    
    //Admin oneRec;
    // sets cursor at the beginning of the file we're looking for
    inBin.seekg(cursor,ios::beg);
    
    
    // Read & set ttlRec in class object   
    inBin.read(reinterpret_cast<char *>(&ttlRec) , sizeof(int)); 
    
    
    // Read & set id in class object   
    inBin.read(reinterpret_cast<char *>(&id) , sizeof(int)); 
        
        
    // Read & set name's length in class object
    inBin.read(reinterpret_cast<char *>(&namSiz), sizeof(unsigned short));
    
    
    // Read & set name in class object    
    string tempStr="";
    tempStr.resize(namSiz);
    inBin.read( &tempStr[0] , namSiz*sizeof(char) ); // write this  string to binary file    
    setName(tempStr); // Set name in class object
    
    
    // Read & set email's length in class object
    inBin.read(reinterpret_cast<char *>(&emaiSiz), sizeof(unsigned short));
    

    // Read & set email in class object    
    tempStr.resize(emaiSiz);
    inBin.read(&tempStr[0], emaiSiz*sizeof(char));    
    setEmail(tempStr);   
    
    
    // Read & set the length of password in class object
    inBin.read(reinterpret_cast<char *>(&pwrdSiz), sizeof(unsigned short)); 
    

    // Read & set email in class object 
    tempStr.resize(pwrdSiz);
    inBin.read(&tempStr[0], pwrdSiz*sizeof(char) );  
    setPwrd(tempStr);
    
    // Read & set hiScore in class object
    inBin.read(reinterpret_cast<char *>(&hiScore) , sizeof(int));   
     
    inBin.close(); // close file
}



//******************************************************************************
//               ONLY ADMIN CLASS HAS PERMISSION!
//              Checks is user's login matches the database
//******************************************************************************

bool Admin::isUsrLogin(){    
    
    cout<<"\n\tUser Login\n";
      
    const char ch = 'u';
    cout<<"\n\n*****Erase after testing*****\nsister@sis.com\nSs!2345\n";
    string tempE="",
           tempPw="";
    bool isName = false ,
         isPwrd = false;
    
    do {
        cout<<"\nEnter email:    ";
        cin>>tempE;
    } while(!(isMinSize(tempE,8)) || !(confrmEmail(tempE)));
     
    do{
        cout<<"Enter password: ";
        cin>>tempPw;       
    } while(!(isMinSize(tempPw,7)));
    
    int recSize=0;
    long cursr = findEmail(ch,tempE, recSize);
    //cout<<"cursr= " <<cursr<<endl;
    
    if( !(cursr == -99)){// look for this email in usrBin.dat
    
        isName = isStrEqual(getEmail(),tempE);
        isPwrd = isStrEqual(getPwrd(),tempPw);
        
    } else { return false; }
    
    if(!isName || !isPwrd){ 
        cout<<"Username and/or password does not match.\n";
        return false; }        
    else {
        cout<<"\n\nUser login was successful."; 
        return true;
    }
}
    

//******************************************************************************
//            Loops until a name's length is within the range   
//******************************************************************************

bool Admin::isName(){
    
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

bool Admin::isEmail(){
    
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

bool Admin::isPwrd(){
    
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

bool Admin::isMinSize(string str, int minLeng){
    
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

bool Admin::isStrEqual(string password, string tempPwd){ 
    if( password.compare(tempPwd) !=0 ){ 
        return false; 
    }
    return true;   
}

//******************************************************************************
//    Confirms password includes at least 1 digit, uppercase & special char 
//******************************************************************************

bool Admin::hasSpecialChars(string pwd){
     
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

/******************************************************************/              
//               Accepts score from game and 
//      checks if it is higher than the current hiScore
/*****************************************************************/
   
bool Admin::isHiScore(int score){
    if(score > hiScore) { 
        setHiScore(score); // Call private member function to reset hiScore
        return true;
    } 
    return false;
}

/******************************************************************/              
//      Converts any uppercase characters to lowercase letters
/*****************************************************************/
   
string Admin::toLowerCase(string n){       
    string str="";
    for(int i=0;i<n.size();i++){
        str += tolower(n[i]);
    }
    return str;
}


/******************************************************************/              
//                  WRITE 1 RECORD TO TEXT FILE     
/*****************************************************************/

void Admin::wrtTxt(){
    
    ofstream outTxt; 
    outTxt.open("usrData.txt", ios::out | ios::app); // appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening usrData.txt\n"; exit(0);}      
 
    outTxt<<"Record "  <<ttlRec<<endl;
    outTxt<<"ID:      "<<id<<endl;      // write id to text file
    outTxt<<"namSiz:  "<<namSiz<<endl; // write the size of this string to text file
    outTxt<<"name:    "<<name<<endl;   // write this string to text file
    outTxt<<"emaiSiz: "<<emaiSiz<<endl;// write the size of this string to text file
    outTxt<<"email:   "<<email<<endl;  // write this string to text file
    outTxt<<"pwrdSiz: "<<pwrdSiz<<endl; // write the size of this string to text file
    outTxt<<"pwrd:    "<<password<<endl;// write this string to text file
    outTxt<<"hiScore: "<<hiScore<<endl<<endl;  
    outTxt.close(); // close file
}


/******************************************************************/              
//                  WRITE 1 RECORD TO BINARY FILE     
/*****************************************************************/

void Admin::wrtBin(){
        
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


/*****************************************************************/
//               Calls private member functions  
/*****************************************************************/
      



/*****************************************************************/
//                     PRINT ONE USER'S INFO  
/*****************************************************************/

void Admin::print1Record()const{  
    
    cout<<"\nRecord: "  << ttlRec <<endl
        <<"ID:       "<< id     <<endl
        <<"Name:     "<< name   <<endl
        <<"Email:    "<< email  <<endl
        <<"Password: ";
    for(int i=0;i<(pwrdSiz) ;i++){ // prints stars instead of actual password
        cout<< '*';
    }
    cout<<"\nHigh Score: "<<hiScore<<endl;    
}
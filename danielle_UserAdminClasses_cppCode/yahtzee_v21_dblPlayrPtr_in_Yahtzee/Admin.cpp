#include <string>
#include <iostream>
#include <fstream>
#include "Admin.h"

using namespace std;  //STD Name-space where Library is compiled


//******************************************************************************
//                Default Constructor
//******************************************************************************

Admin::Admin(){
        //cout<<"Hit Admin Default Constructor\n";
        recSiz = 0;
        begnFile = 0;        
}


//******************************************************************************
//                 Constructor #2
//              Calls User's constructor
//              Used in readInput()
//******************************************************************************

Admin::Admin(string n, string e, string p) {
        //cout<<"Hit Admin Constructor #2\n";
        user.setName(n);
        user.setEmail(e);
        user.setPwrd(p);
        recSiz = 0;
        begnFile = 0;
}


//******************************************************************************
//                 Constructor #3
//              Calls User's constructor
//              Called in getAllUsr()
//******************************************************************************

Admin::Admin(int record) {
    
    record = record < 0 ? 0 : record;
    //cout<<"Hit Admin Constructor #3\n";
    user.setNumRec(record);
    recSiz = 0;
    begnFile = 0;
}


//******************************************************************************
//                 Copy Admin values to User class object
 // reassign user2 variables based on user object that was read from binary
//******************************************************************************

void Admin::copy2Usr(User &user2){
   
    //cout<< "\n inside copy2Usr()";
    user2.setNumRec(user.getNumRec());
    user2.setName(user.getName());       
    user2.setEmail(user.getEmail());
    user2.setPwrd(user.getPwrd());
    user2.setHiScore(user.getHiScore());        
    //cout<<"\n admin record: " << user.getNumRec() <<endl;
    //printAdUsr();
}


//******************************************************************************
//              Checks if user's login matches the binary's record
//******************************************************************************

bool Admin::isUsrLogin(){    
    
    cout<<"\n\tUser Login\n";

    //cout<<"\n\n*****Reset strings after testing*****\nlisa@simp.com\nLisa!2345\n";
    string tempE= "lisa@simp.com",
           tempPw="Lisa!2345";
    bool isName = false,
         isPwrd = false;
    
//    do {
        cout<<"\nEnter email:    ";
//        cin>>tempE;
//    } while(!(isMinSize(tempE,8)) || !(confrmEmail(tempE)));
       cout<<tempE<<endl;
                
//    do{
        cout<<"Enter password: ";
//        cin>>tempPw;       
//    } while(!(isMinSize(tempPw,7)));
    cout<<tempPw;
       
    
    // look for this email in usrBin.dat. If it exists, then
    // compare email and password with record in binary file
    if(findByEmail(tempE)){
    
        isName = user.isStrEqual(user.getEmail(),tempE);
        isPwrd = user.isStrEqual(user.getPwrd(),tempPw);        
    
    } else { return false; }
    
    // if user inputs do NOT match record in binary then exit
    if(!isName || !isPwrd){ 
        
        cout<<"Username and/or password does not match.\n";
        return false;  
        
    } else { return true; }
}


/******************************************************************/ 
//          READ ADMIN BINARY FILE, RETURN 1 RECORD    
//                  & COMPARE IT TO INPUTS
/*****************************************************************/
  
void Admin::adminLogin(){
    
    cout<<"\n\tAdmin Login\n"; 
    
    string tempNam = "",
           tempPwrd = "";
    
    bool isName = false,
         isPwrd = false;
    
    readAdBin(); 
    //print1Admin();
   
    //************************************
    //delete after all testing is finished
    tempNam  = user.getName();
    tempPwrd = user.getPwrd();
    //************************************
    
//    do{        
        cout<<"\nEnter username: \n";
//        cin>>tempNam;
//        isName = isMinSize(tempNam,2);
//    } while(!isName);
//    
    cout<<"Enter password: \n";
//    cin>>tempPwrd;   
    
    isName = user.isStrEqual(user.getName(),tempNam);
    isPwrd = user.isStrEqual(user.getPwrd(),tempPwrd);
    
    if(!isName || !isPwrd){ 
        cout<<"Username and/or password does not match.\n";       
        return;
    
    } else { adminPortal(); } // opens function that Admin is only allowed to access
}


/******************************************************************/              
//             ONLY able to access this menu  
//                  if Admin is logged in 
/*****************************************************************/

void Admin::adminPortal(){
    
    cout<<"\n\nAdmin login was successful.\n";
    int choice;   
    
    do {
        cout<<"\n\n\tMenu\n"
            <<"1: Show all users\n"
            <<"2: Find one index\n"
            <<"3: Find by email\n"
            <<"4: Edit hiScore\n"
            <<"5: Delete a user\n"
            <<"6: Update Admin\n"
            <<"9: Logout\n"
            <<"Enter a number: ";
        cin>>choice;

        switch(choice){
            case 1:
            {      
                Admin **usrArr;
                getAllUsrs(usrArr);
                //usrArr = getAllUsrs();
                
//               usrArr[0]->printAdUsr();
//                usrArr[1]->printAdUsr();
//                usrArr[2]->printAdUsr();
//                usrArr[3]->printAdUsr();                                            
                break;
            } 
            case 2:  // Find user by index in binary file 
            { 
                Admin admin2;
                int num = 0;  
                cout<<"\nWhich record are you looking for?\n";
                admin2.getIndex(num);                  
                admin2.findByIndx(num);
                admin2.printAdUsr(); 
                break;
            } 
            
            case 3: // Find user by email in binary file
            {                 
                Admin admin3;
                //admin3.printAdUsr();
                string str = "";
                cout<<"\nEnter the email you want to find: ";
                //cin>>str;
                str = "homer@simp.com";
                //str = "marge@simp.com";
                //str = "lucy@beatles.com";                
                
                if(admin3.findByEmail(str)){
                    cout<<"Located " << str << "'s profile";
                    admin3.printAdUsr(); 
                }
                
                break;
            }      
            case 4:  // Edit hiScore in binary and text files
            {    
                int n = 0;  
                Admin admin4;
                cout<<"\nWhich record do you want to edit?\n";
                admin4.getIndex(n); 
                admin4.findByIndx(n);
                
                if(admin4.user.getName().compare(0,6,"xxxxxx") == 0){
                    
                    cout<<"\nYou can not edit this record.\n"
                        <<"This record was deleted.\n";
                    
                } else { admin4.setUsrHiScore(); }
                break;
            }
            case 5: // Delete record in binary & text
            {   
                Admin admin5;
                admin5.deleteUsr();
                break;
            } 
            case 6:
            {                
                updateAdmin();        
                break;
            } 
            default: {
                cout<<"\nLogged Out.\n";                
                return;
            }
        }
    } while(choice>=1 && choice<=6);
}


//Admin Admin::**getAllUsrs(){
void Admin::getAllUsrs(Admin **usrArr){
    
    ifstream inBin;
    string file = "usrData.dat";
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; return;}
        
    long cursor = 0L,
         rSize  = 0L,
         thisSum = 0L;
    int  i = 0,  
         nRec = user.getNumRec();
    
    // Create an array of Admin objects
    usrArr = new Admin*[user.getNumRec()];
    
    // Accumulate all the bits between the beginning of file up the record I'm looking for.
    while(i < nRec){
     
        usrArr[i] = new Admin(i);   
        
        thisSum = 0L;
        //cout<<"\n\n i = " << i <<" cursor = "<< cursor<< " thisSUm="<<thisSum<<endl;
        
        
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read in sizeof numRec and add to cursor
        int num;
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        usrArr[i]->user.setNumRec(num);
        thisSum += sizeof(int);         
        //cout<<"thisSum=="<<thisSum<<endl;
       
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        unsigned short size;
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );
        usrArr[i]->user.setNamSiz(size);
        
        // Read & set name to Admin class object    
        string tempStr = "";
        tempStr.resize(usrArr[i]->user.getNamSiz());
        inBin.read( &tempStr[0] , size*sizeof(char) ); // write this  string to binary file    
        usrArr[i]->user.setName(tempStr); // Set name 
        thisSum += ( sizeof(size) + (size*sizeof(char)) );
        //cout<<"thisSum=="<<thisSum<<endl;     
        
        
        // Read email size & save to Admin class object
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );               
        usrArr[i]->user.setEmaiSiz(size);
        
        // Read & set email to Admin class object    
        tempStr.resize(usrArr[i]->user.getEmaiSiz());
        inBin.read(&tempStr[0], size*sizeof(char));    
        usrArr[i]->user.setEmail(tempStr);           
        thisSum += ( sizeof(size) + size*sizeof(char) );
        //cout<<"thisSum=="<<thisSum<<endl;
        
        
        // Read password size & save to Admin class object
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));      
         
        // Read & set password to Admin class object
        tempStr.resize(size);
        inBin.read(&tempStr[0], size*sizeof(char) );  
        usrArr[i]->user.setPwrd(tempStr);
        thisSum += ( sizeof(size) + (size*sizeof(char)) );   
        //cout<<"thisSum=="<<thisSum<<endl;
        
        // Read in size of hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        //cout<< sizeof(num)<<" thisSum = "<< thisSum ;
        thisSum += sizeof(num);  
        cursor  += thisSum;    
        
        //cout << "\n thisSum = " << thisSum << " cursor = " << cursor << endl;
        
        // if its the first record set the cursor to the zero 
        long bFile = (i==0)? 0L : (cursor-thisSum); 
        usrArr[i]->setBegnFile(bFile);
        usrArr[i]->setRecSiz(thisSum);
        //cout<<"\ni = "<<i<<" recSiz = "<<usrArr[i]->recSiz<<"  begnFile = "<<usrArr[i]->begnFile<<endl;   

        usrArr[i]->printAdUsr();
        i++;
    }    
    inBin.close();              
}


/******************************************************************/ 
//                     Reset hiScore in User object
//                   and rewrite binary & text files
/******************************************************************/ 

void Admin::setUsrHiScore(){ 
    
    int score = 0;
    
    do {
        cout<<"\nEdit " << user.getName() << "'s new high Score.\nEnter a score between 0 and 999: ";
        cin >> score;
    } while(!(score>=0 && score<=999));

    if(user.isHiScore(score)){
        
        user.setHiScore(score);
        cout<<"\nNew High Score of "<<user.getHiScore()<<"!\n";
        cout<<"Updating binary....";
        user.reWrtBin(begnFile); // rewrites this record in binary & text files    
        findByIndx(user.getNumRec());
        printAdUsr();  
        
    } else { cout<<"\n\nNot a high score.\n"; }
}


/******************************************************************/ 
//             Delete 1 record in User binary file
/******************************************************************/ 

void Admin::deleteUsr(){
    
    Admin delUsr;    
    int num = 0; 
    
    cout<<"\nWhich record do you want to delete?\n";
    delUsr.getIndex(num); 
    delUsr.findByIndx(num);
    cout<<"\nFound record "<<num<<endl<<endl;
    delUsr.printAdUsr();   
    
                
    // Should set some sort of flag that says its deleted?
    int i;
    string temp = "";
    for(i=0; i < delUsr.user.getNamSiz();i++){
        temp += "x";
    }
    delUsr.user.setName(temp);
    
    temp = "";
    for(i=0; i < delUsr.user.getEmaiSiz();i++){
        temp += "x";
    }
    delUsr.user.setEmail(temp);
    
    temp = "";
    for(i=0; i < delUsr.user.getPwrdSiz();i++){
        temp += "x";
    }
    delUsr.user.setPwrd(temp); 
    
    delUsr.user.setHiScore(0);
    
    delUsr.user.reWrtBin(delUsr.begnFile); // rewrites this record in binary & text files  
    cout<<"\n\nRecord successfully deleted.";
    delUsr.printAdUsr();    
}


/*****************************************************************/
//                 Finds a User's record by their index
//                Assumes the records are in ascending order
/*****************************************************************/

void Admin::findByIndx(int recIndx){
    
    cout << "\nLooking for record " << recIndx << " in binary file.\n";  
    
    ifstream inBin;
    string file = "usrData.dat"; 
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; return;}
        
    long cursor = 0L,
         rSize = 0L,
         thisSum;
    int  count = 0;  
    
    
    // Accumulate all the bits between the beginning of file up the 
    // record I'm looking for.
    
    while(count <= recIndx){ // Has to be <= else it wont read record size when recIndx==0
         
        thisSum = 0L;
        
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read in sizeof numRec and add to cursor
        int num = 0;
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        thisSum += sizeof(num);
        cursor  += sizeof(num);          
        
               
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        unsigned short size;
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );
        thisSum += ( sizeof(size) + size*sizeof(char) );
        cursor  += ( sizeof(size) + size*sizeof(char) );        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        // Read the value of emaiSiz & then use it calculate the number of bits       
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );               
        thisSum += ( sizeof(size) + size*sizeof(char) );
        cursor  += ( sizeof(size) + size*sizeof(char) );
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        
        // Read the value of pwrdSiz & then use it calculate the number of bits
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));      
        thisSum += ( sizeof(size) + size*sizeof(char) );        
        cursor  += ( sizeof(size) + size*sizeof(char) );
        
        // Read in size of hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        thisSum += sizeof(num);  
        cursor  += sizeof(num);     
        
        if(count==recIndx){ rSize = thisSum; break;}
            
        count++;        
    }
       
    // if recIndx is 0, then set the cursor to zero 
    cursor = (count==0)? 0 : cursor-rSize; 
    setRecSiz(rSize);
    setBegnFile(cursor); // beginning bit location of this file in files
    //cout << "\n inside findByIndx() recSiz = " << recSiz << "  begnFile = " << begnFile<<endl;   
              
    read1Bin(); //read binary & save record
    
    inBin.close();    
}


/*****************************************************************/
//                     Read user's binary file.
//           if email is found, then return class obj with record  
//              else if email is NOT found return false
/*****************************************************************/

bool Admin::findByEmail(string emai){
    
    cout <<"\n\nLooking for " << emai << "...\n\n";   
    
    ifstream inBin;
    string file = "usrData.dat";     
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; exit(0);} 
    
    bool foundEm;
    long cursor  = 0L, 
         thisSum = 0L;
    int count = 0,   // start at 1, so it stops before the record I'm looking for     
        rSize = 0,  // hold this records size
        nRec  = user.getNumRec();
    
    
    // Accumulate all the bits between the beginning of file up the record I'm looking for. 
    while( (!foundEm) && (count <= nRec) ){                 
        
        inBin.seekg(cursor,ios::beg);  // cursor is set to the beginning of the record 
        
        // Read in sizeof id and add to cursor
        int num;
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        thisSum += sizeof(num);
        cursor  += sizeof(num);          
               
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next member variables
        unsigned short size;
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );
        thisSum += ( sizeof(unsigned short) + size*sizeof(char) );
        cursor  += ( sizeof(unsigned short) + size*sizeof(char) );
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        
        // Read the value of emaiSiz & then use it calculate the number of bits
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );               
        thisSum += ( sizeof(size) + size*sizeof(char) );
        cursor  += ( sizeof(size) + size*sizeof(char) );
        
        // Read email & save to a temp variable
        string binEmail = "";
        binEmail.resize(size);
        inBin.read(&binEmail[0], size*sizeof(char));              
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        
        // Read the value of pwrdSiz and then use it calculate the number of bits
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));      
        thisSum += ( sizeof(size) + size*sizeof(char) );
        cursor  += ( sizeof(size) + size*sizeof(char) );        
        
        
        // Read in size of hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        thisSum += sizeof(num);
        cursor  += sizeof(num);
        
        //cout << "\n thisSum = " << thisSum << "  cursor=" << cursor << "  count = " << count << endl;
        
        foundEm = user.isStrEqual(emai, binEmail); // looking for email inputted by user
        
        if(foundEm){
            count = user.getNumRec();  
            rSize = thisSum;
            setRecSiz(rSize);
            cursor = (count==0) ? 0 : (cursor-rSize); 
            setBegnFile(cursor); 
            //cout << "\n\t recSiz = " << recSiz << "  cursLoc = " << cursLoc << "  count = " << count << endl<<endl;
            read1Bin(); // read this file in binary & save to admin class object
            return true;
        } else{
            count++;
            thisSum = 0L;    
        }
        //cout << " count = " << count << "   cursor = " << cursor << endl;   
    }    
       
    inBin.close();
    cout<<"\nUnable to locate email.\n";
    return false;
}
    
  
/*****************************************************************/
///         Read 1 User's record in binary & save to class object
//              Cursor is the beginning of this record
/*****************************************************************/

void Admin::read1Bin(){
    
    //cout << "Hit read1Bin()\n";
    //cout << "recSiz = " << recSiz << "  cursor = " << begnFile << endl;
    
    ifstream inBin;
    string file = "usrData.dat";        
    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; return;}
    
    // sets cursor at the beginning of the file we're looking for
    inBin.seekg(begnFile,ios::beg);    
    
    // Read & set numRec    
    int num;
    inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
    user.setNumRec(num);   
    
    // Read & set the length of name 
    unsigned short size;
    inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));
    user.setNamSiz(size);
    
    // Read & set name     
    string tempStr="";
    tempStr.resize(size);
    inBin.read( &tempStr[0] , size*sizeof(char) ); // write this  string to binary file    
    user.setName(tempStr); // Set name 
    
    
    // Read & set the length of email 
    inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));
    user.setEmaiSiz(size);

    // Read & set email     
    tempStr.resize(size);
    inBin.read(&tempStr[0], size*sizeof(char));    
    user.setEmail(tempStr);       
    
    // Read & set the length of password 
    inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short)); 
    user.setPwrdSiz(size);
    
    // Read & set password  
    tempStr.resize(size);
    inBin.read(&tempStr[0], size*sizeof(char) );  
    user.setPwrd(tempStr);
    
    // Read & set hiScore 
    inBin.read(reinterpret_cast<char *>(&num) , sizeof(int));   
    user.setHiScore(num);
    
    //cout<<"\n inside read1Bin()";
    //printAdUsr();
    
    inBin.close(); // close file
}


/*****************************************************************/
//            Read Admin's binary file, find 1st record 
//             & return 1 record as a Admin class object
/*****************************************************************/

void Admin::readAdBin(){ 
     
    cout<<"\nReading Admin Binary...\n";
    
    ifstream inBin;
    string file = "admin.dat";    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; return;}
        
    long cursor = 0L;
     
    // Set cursor at the very beginning of Admin's binary file              
    inBin.seekg(cursor,ios::beg); 

    // Read the value of namSiz & set Admin member variable
    unsigned short size;
    inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );
    user.setNamSiz(size);
    
    // Read name & set Admin member variable
    string str;
    str.resize(size);
    inBin.read(&str[0] , size*sizeof(char) );
    user.setName(str);
    
    
    // Read the value of emaiSiz and set Admin object        
    inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );      
    user.setEmaiSiz(size);
     
    // Read email & set Admin member variable
    str="";
    str.resize(size);
    inBin.read(&str[0], size*sizeof(char) );
    user.setEmail(str);

    
    // Read the value of pwrdSiz and set Admin object     
    inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));  
    user.setPwrdSiz(size);
    
    // Read name & set Admin member variable
    str = "";
    str.resize(size);    
    inBin.read(&str[0], size*sizeof(char) );        
    user.setPwrd(str);  
  
    inBin.close(); // close file
}


/******************************************************************/ 
//                  Write 1 Admin record to text file  
/*****************************************************************/

void Admin::wrtAdTxt(){
    
    ofstream outTxt; 
    outTxt.open("admin.txt",ios::out); // DOES NOT appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening admin.txt\n"; exit(0);}
    
    outTxt<<"namSiz:  "<<user.getNamSiz()<<endl; // write the size of this string to text file
    outTxt<<"name:    "<<user.getName()<<endl;   // write this string to text file
    outTxt<<"emaiSiz: "<<user.getEmaiSiz()<<endl;// write the size of this string to text file
    outTxt<<"email:   "<<user.getEmail()<<endl;  // write this string to text file
    outTxt<<"pwrdSiz: "<<user.getPwrdSiz()<<endl; // write the size of this string to text file
    outTxt<<"pwrd:    "<<user.getPwrd()<<endl;// write this string to text file
    outTxt.close(); // close file
}


/******************************************************************/  
//                   Write 1 Admin record to binary file   
/*****************************************************************/

void Admin::wrtAdBin(){
        
    ofstream outBin;
    outBin.open("admin.dat",ios::out | ios::binary); // DOES NOT appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening admin.dat\n";}      
    
    // Write name's size & name to binary file
    unsigned short size = user.getNamSiz();
    outBin.write(reinterpret_cast<char *>(&size), sizeof(unsigned short)); 
    outBin.write(user.getName().c_str(), size*sizeof(char)); 
        
    // Write email's size & email to binary file
    size = user.getEmaiSiz();
    outBin.write(reinterpret_cast<char *>(&size), sizeof(unsigned short));      
    outBin.write( user.getEmail().c_str(), size*sizeof(char)); 
        
    // Write password's size & password to binary file
    size = user.getPwrdSiz();
    outBin.write(reinterpret_cast<char *>(&size), sizeof(unsigned short)); 
    outBin.write(user.getPwrd().c_str(), size*sizeof(char));         
      
    outBin.close(); // close file    
}


/******************************************************************/ 
//               Calls User functions to rewrite Admin's 
//                  record in binary & text 
/******************************************************************/ 
void Admin::updateAdmin(){ 
    
    if(user.isName() && user.isEmail() && user.isPwrd()){
        print1Admin();
        wrtAdTxt();
        wrtAdBin(); 
     
    } else { cout<<"\n\nUnable to update Admin's profile.\n";}
} 


/*****************************************************************/
//                     PRINT 1 Admin'S INFO  
/*****************************************************************/

void Admin::print1Admin()const{  
    cout<<endl<<endl        
        <<"NamSiz:    "<< user.getNamSiz() <<endl
        <<"Name:      "<< user.getName()   <<endl
        <<"EmaiSiz:   "<< user.getEmaiSiz() <<endl
        <<"Email:     "<< user.getEmail()   <<endl
        <<"PwrdSiz:   "<< user.getPwrdSiz() <<endl
        <<"Password:  "<< user.getPwrd() <<endl;    
}


/*****************************************************************/
//               PRINT 1 User + Admin member variables
/*****************************************************************/

void Admin::printAdUsr() const{
    
    cout<<"\nAdmin's view";
    user.printUsrRec();
    cout<<"Record Size    "<<recSiz<<endl
        <<"Start of file: "<<begnFile<<endl;
}


/*****************************************************************/
//               Validate user's input before 
//             searching for it in binary file
/*****************************************************************/

void Admin::getIndex(int &num){
   
    do {
        cout<<"Enter a number between 0 and " << (user.getNumRec()-1) <<endl;
        cin>>num;
    } while (!(num>=0 && num <= (user.getNumRec()-1)));
}
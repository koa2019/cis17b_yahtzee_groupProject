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
    
    //cout<<"Hit Admin Constructor #3\n";
    user.setTtlRec(record);
    recSiz = 0;
    begnFile = 0;
}

//******************************************************************************
//              Checks is user's login matches the database
//******************************************************************************

bool Admin::isUsrLogin(){    
    
    cout<<"\n\tUser Login\n";
      
    //cout<<"\n\n*****Reset after testing*****\nsister@sis.com\nSs!2345\n";
    string tempE= "sister@sis.com",
           tempPw="Ss!2345";
    bool isName = false ,
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
       
    
    if(findByEmail(tempE)){// look for this email in usrBin.dat
    
        isName = user.isStrEqual(user.getEmail(),tempE);
        isPwrd = user.isStrEqual(user.getPwrd(),tempPw);        
    
    } else { return false; }
    
    if(!isName || !isPwrd){ 
        
        cout<<"Username and/or password does not match.\n";
        return false;  
        
    } else { return true;}
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
//          ONLY allowed to access this menu  
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
            <<"4: Edit binary\n"
            <<"5: Delete a user\n"
            <<"6: Update Admin\n"
            <<"9: Logout\n"
            <<"Enter a number: ";
        cin>>choice;
        //cin.ignore();

        switch(choice){
            case 1:
            {      
                Admin **usrArr;
                getAllUsrs(usrArr);
                //usrArr = getAllUsrs();
                
//                usrArr[0]->printAdUsr();
//                usrArr[1]->printAdUsr();
//                usrArr[2]->printAdUsr();
//                usrArr[3]->printAdUsr();                                
              
                break;
            } 
            case 2:  // Find user by index in binary file 
            { 
                Admin usr2;
                int num = 0;  
                cout<<"\nWhich record do you want to look for? ";
                usr2.getIndex(num);                  
                usr2.findByIndx(num);
                usr2.printAdUsr(); 
                break;
            } 
            
            case 3: // Find user by email in binary file
            {                 
                Admin usr3;
                //usr3.printAdUsr();
                string str;
                cout<<"\nEnter the email you want to find: ";
                //cin>>str;
                //str = "mother@aa.com";
                str = "father@email.com";
                //str = "sister@sis.com";                
                
                if(usr3.findByEmail(str)){
                    cout<<"Here is "<<str<<"'s profile";
                    usr3.printAdUsr(); 
                }
                
                break;
            }      
            case 4:  // Edit hiScore in binary and text files
            {    
                Admin usr4;
                int n = 0;  
                cout<<"\nWhich record do you want to edit? ";
                usr4.getIndex(n); 
                usr4.findByIndx(n);
                usr4.user.setHiScore(37);
                cout<<"\nNew High Score of "<<usr4.user.getHiScore()<<"!\n";
                cout<<"Updating binary....";
                usr4.reWrtBin(); // rewrites this record in binary & text files                           
                usr4.findByIndx(n);
                usr4.printAdUsr(); 
                
                break;
            }
            case 5: // Delete record in binary & text
            {   
                Admin usr5;
                usr5.deleteUsr();
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
//   
}


/******************************************************************/ 
//                      Delete 1 record
/******************************************************************/ 

void Admin::deleteUsr(){
    
    Admin delUsr;
    
    int num = 0;                
    cout<<"\nWhich record do you want to delete? ";
    delUsr.getIndex(num); 
    delUsr.findByIndx(num);
    cout<<"\nFound record "<<num<<endl<<endl;
    delUsr.printAdUsr();   
    
                
    // Need to set some sort of flag that its deleted
    int i;
    string temp="";
    for(i=0; i< delUsr.user.getNamSiz();i++){
        temp += "x";
    }
    delUsr.user.setName(temp);
    
    temp="";
    for(i=0; i< delUsr.user.getEmaiSiz();i++){
        temp += "#";
    }
    delUsr.user.setEmail(temp);
    
    temp="";
    for(i=0; i< delUsr.user.getPwrdSiz();i++){
        temp += "#";
    }
    delUsr.user.setPwrd(temp);    
    delUsr.user.setHiScore(0);
    delUsr.reWrtBin(); // rewrites this record in binary & text files  
    cout<<"\n\nRecord successfully deleted.";
    delUsr.printAdUsr();    
}


/******************************************************************/              
//                  REWRITE 1 RECORD in Text FILE    
//          Important! When you change # bits in any variable it 
//                  will effect rewriting it in text file
/*****************************************************************/

void Admin::reWrtTxt(){
        
    //cout<<"\n\nHit reWrtTxt()  recSize= "<<recSiz<<"  begnFile = "<<begnFile<<endl;
    
    fstream outTxt; 
    outTxt.open("usrData.txt", ios::ate | ios::in | ios::out ); // appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening usrData.txt\n";}
    
    //cout<<"\ngetTtlRec() = "<<getTtlRec()<<endl;
    
    int charCount = (user.getTtlRec()==0) ? 0 : ((86)*user.getTtlRec());
    //cout<<"\ncharCount = "<< charCount <<endl;
    long cursor = (begnFile <= 0) ? 0 : (begnFile+charCount); // hiScore is a int which is 4 bits
    
    //cout<<"begnFile = "<< cursor <<endl;
    
    outTxt.seekp(cursor,ios::beg);  // Sets the position of the get pointer
       
    outTxt<<endl;
    outTxt<<"Record   "<<user.getTtlRec()<<endl;
    outTxt<<"ID:      "<<user.getID()<<endl;      // write id to text file
    outTxt<<"namSiz:  "<<user.getNamSiz()<<endl; // write the size of this string to text file
    outTxt<<"name:    "<<user.getName()<<endl;   // write this string to text file
    outTxt<<"emaiSiz: "<<user.getEmaiSiz()<<endl;// write the size of this string to text file
    outTxt<<"email:   "<<user.getEmail()<<endl;  // write this string to text file
    outTxt<<"pwrdSiz: "<<user.getPwrdSiz()<<endl; // write the size of this string to text file
    outTxt<<"pwrd:    "<<user.getPwrd()<<endl;// write this string to text file 
    outTxt<<"hiScore: "; 
    outTxt<< (user.getHiScore()/100) << (user.getHiScore()/10%10) << (user.getHiScore()%10) <<endl<<endl;
    outTxt.close(); // close file    
}

/******************************************************************/              
//                  REWRITE 1 RECORD TO BINARY FILE     
/*****************************************************************/

void Admin::reWrtBin(){
        
    //cout<<"\n\nHit reWrtBin()  recSize="<<recSiz<<"  begnFile ="<<begnFile<<endl;
    
    fstream outBin; 
    outBin.open("usrData.dat", ios::ate | ios::in | ios::out | ios::binary); // appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening usrData.dat\n";}
    
    long cursor = (begnFile <= 0) ? 0 : begnFile; 
    
    //cout<<"begnFile = "<< cursor <<endl;
    
    outBin.seekp(cursor,ios::beg);  // Sets the position of the get pointer
        
    // Write total records to binary file
    int num = user.getTtlRec();
    outBin.write(reinterpret_cast<char *>(&num) , sizeof(int)); 
    
    
    // Write id to binary file
    num = user.getID();
    outBin.write(reinterpret_cast<char *>(&num) , sizeof(int)); 
    
    
    // Write name's length to binary file
    // and then write this string to binary file
    unsigned short size = user.getNamSiz();
    outBin.write(reinterpret_cast<char *>(&size), sizeof(unsigned short)); 
    
    string str = user.getName();
    outBin.write(str.c_str(), size*sizeof(char)); 
    
    
    // Write email's length to binary file
    // and then write this string to binary file
    size = user.getEmaiSiz();
    outBin.write(reinterpret_cast<char *>(&size), sizeof(unsigned short));     
    
    str = user.getEmail();
    outBin.write( str.c_str(), size*sizeof(char)); 
    
    
    // Write password's length to binary file
    // and then write this string to binary file
    size = user.getPwrdSiz();
    outBin.write(reinterpret_cast<char *>(&size), sizeof(unsigned short)); 
    
    str = user.getPwrd();
    outBin.write(str.c_str(), size*sizeof(char)); 
   
    
    // Rewrite hiScore in binary file    
    num = user.getHiScore();  
    outBin.write(reinterpret_cast<char *>(&num) , sizeof(int)); 
    outBin.close(); // close file  
    
    reWrtTxt();  // rewrite this record in usrData text file
}


/*****************************************************************/
//                 Finds a User's record by their index
//                Assumes the records are in ascending order
/*****************************************************************/

void Admin::findByIndx(int recIndx){
    
    cout<<endl<<"Looking for record "<<recIndx<<" in binary file.\n";  
    
    ifstream inBin;
    string file = "usrData.dat";        
    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; return;}
        
    long cursor = 0L,
         rSize = 0L;
    int  count = 0;  // if recIndx==0, then it wont do the while loop
    
    
    // Accumulate all the bits between the beginning of file up the record I'm looking for.
    while(count<=recIndx){
         
        long thisSum = 0;
        
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read in sizeof id and add to cursor
        int num;
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        thisSum += sizeof(int);
        cursor += sizeof(int);          
        
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        thisSum += sizeof(int);
        cursor +=  sizeof(int);  
       
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        unsigned short size;
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );
        thisSum += ( sizeof(unsigned short) + size*sizeof(char) );
        cursor += ( sizeof(unsigned short) + size*sizeof(char) );
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

               
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );               
        thisSum += ( sizeof(unsigned short) + size*sizeof(char) );
        cursor += ( sizeof(unsigned short) + size*sizeof(char) );
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));      
        thisSum += ( sizeof(unsigned short) + size*sizeof(char) );        
        cursor += ( sizeof(unsigned short) + size*sizeof(char) );
        
        // Read in size of hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        thisSum += sizeof(int);  
        cursor += sizeof(int);     
        
        if(count==recIndx){ rSize = thisSum; break;}
            
        count++;        
    }
       
    // if its the first record set the cursor to the zero 
    cursor = (count==0)? 0 : cursor-rSize; 
    setRecSiz(rSize);
    setBegnFile(cursor); // beginning bit location of this file in binary
    //cout<<"\nrecSiz = "<<recSiz<<"  begnFile = "<<begnFile<<endl;   
    
    //***********    SAVE LOCATED RECORD   ************************//            
    read1Bin(); //read binary & save record
    
    inBin.close();    
}


/*****************************************************************/
//                     Read user's binary file.
//           if email is found, then return class obj with record  
//              else if email is NOT found return false
/*****************************************************************/

bool Admin::findByEmail(string emai){
    
    cout<<endl<<endl<<"Looking for "<<emai<<"...\n";   
    
    ifstream inBin;
    string file = "usrData.dat";        
    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; exit(0);} 
    
    bool foundEm;
    long cursor = 0L, thisSum=0L;
    int count = 0,   // start at 1, so it stops before the record I'm looking for     
            rSize = 0, // hold this records size
            nRec = user.getTtlRec();
    
    
    // Accumulate all the bits between the beginning of file up the record I'm looking for. 
    while( (!foundEm) && (count <= nRec) ){                 
        
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read in sizeof id and add to cursor
        int num;
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        thisSum +=sizeof(int);
        cursor += sizeof(int);  
        
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        thisSum += sizeof(int);
        cursor += sizeof(int);  
        
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        unsigned short size;
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );
        thisSum += ( sizeof(unsigned short) + size*sizeof(char) );
        cursor += ( sizeof(unsigned short) + size*sizeof(char) );
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        
        // Read the value of emaiSiz and then use it calculate the number of bits
        // that emaiSiz and email take up in memory. 
        // Add it to cursor and move on to the next variables        
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );               
        thisSum += ( sizeof(unsigned short) + size*sizeof(char) );
        cursor += ( sizeof(unsigned short) + size*sizeof(char) );
        
        // Read email & save to a temp variable
        string binEmail = "";
        binEmail.resize(size);
        inBin.read(&binEmail[0], size*sizeof(char));              
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        
        // Read the value of pwrdSiz and then use it calculate the number of bits
        inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));      
        thisSum += ( sizeof(unsigned short) + size*sizeof(char) );
        cursor += ( sizeof(unsigned short) + size*sizeof(char) );        
        
        
        // Read in size of hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
        thisSum += sizeof(int);
        cursor += sizeof(int);
        
        //cout<<"\nthisSum="<<thisSum<<"  cursor="<<cursor<<"  count="<<count<<endl;
        
        foundEm = user.isStrEqual(emai, binEmail); // looking for email inputted by user
        
        if(foundEm){
            count = user.getTtlRec();  
            rSize = thisSum;
            setRecSiz(rSize);
            cursor = (count==0) ? 0 : (cursor-rSize); 
            setBegnFile(cursor); 
            //cout<<"\n\trecSiz ="<<recSiz<<"  cursLoc="<<cursLoc<<"  count="<<count<<endl<<endl;
            read1Bin(); // read this file binary & save  
            return true;
        } else{
            count++;
            thisSum = 0L;    
        }
        //cout<<count<<"=count \t   cursor = "<<cursor<<endl;   
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
    
    //cout<<"Hit read1Bin()\n";
    //cout<<"recSiz = "<<recSiz<<"  cursor = "<<begnFile<<endl;
    
    ifstream inBin;
    string file = "usrData.dat";        
    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; return;}
    
    // sets cursor at the beginning of the file we're looking for
    inBin.seekg(begnFile,ios::beg);    
    
    // Read & set ttlRec    
    int num;
    inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
    user.setTtlRec(num);
    
    // Read & set id    
    inBin.read(reinterpret_cast<char *>(&num) , sizeof(int)); 
    user.setID(num);    
        
    // Read & set name's length 
    unsigned short size;
    inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));
    user.setNamSiz(size);
    
    // Read & set name     
    string tempStr="";
    tempStr.resize(size);
    inBin.read( &tempStr[0] , size*sizeof(char) ); // write this  string to binary file    
    user.setName(tempStr); // Set name 
    
    
    // Read & set email's length 
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
    
    inBin.close(); // close file
}


/*****************************************************************/
//           Read Admin's binary file, find 1 record by index
//                     & return 1 record  
/*****************************************************************/

void Admin::readAdBin(){ 
     
    cout<<"\nReading Admin Binary...\n";
    
    ifstream inBin;
    string file = "admin.dat";
    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; return;}
        
    long cursor = 0L;
     
    // Accumulate total bits for one record                    
    inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  


    // Read the value of namSiz and then use it to calculate the number of bits
    // that namSiz and name take up in memory. 
    // Add it to cursor and move on to the next variables
    unsigned short size;
    inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );
    user.setNamSiz(size);
    
    string str;
    str.resize(size);
    inBin.read(&str[0] , size*sizeof(char) );
    user.setName(str);
    
    
    // Read the value of emaiSiz and then use it calculate the number of bits
    // that emaiSiz and email take up in memory. 
    // Add it to cursor and move on to the next variables        
    inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short) );      
    user.setEmaiSiz(size);
     
    str="";
    str.resize(size);
    inBin.read(&str[0], size*sizeof(char) );
    user.setEmail(str);

    
    // Read the value of pwrdSiz and then use it calculate the number of bits
    // that pwrdSiz and password take up in memory. 
    // Add it to cursor and move on to the next variables       
    inBin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));  
     user.setPwrdSiz(size);
    
    str="";
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
    
    // Write name's length to binary file
    // and then write this string to binary file
    unsigned short size = user.getNamSiz();
    outBin.write(reinterpret_cast<char *>(&size), sizeof(unsigned short)); 
    outBin.write(user.getName().c_str(), size*sizeof(char)); 
        
    // Write email's length to binary file
    // and then write this string to binary file
    size = user.getEmaiSiz();
    outBin.write(reinterpret_cast<char *>(&size), sizeof(unsigned short));      
    outBin.write( user.getEmail().c_str(), size*sizeof(char)); 
        
    // Write password's length to binary file
    // and then write this string to binary file
    size = user.getPwrdSiz();
    outBin.write(reinterpret_cast<char *>(&size), sizeof(unsigned short)); 
    outBin.write(user.getPwrd().c_str(), size*sizeof(char));         
      
    outBin.close(); // close file    
}


/******************************************************************/ 
//               Calls User functions to rewrite Admin's record
/******************************************************************/ 
void Admin::updateAdmin(){ 
    
    if(user.isName() && user.isEmail() && user.isPwrd()){
        print1Admin();
        wrtAdTxt();
        wrtAdBin(); 
     
    } else { cout<<"\n\nUnable to update Admin's profile.\n";}
} 


/*****************************************************************/
//                     PRINT ONE Admin'S INFO  
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
//                     PRINT 1 record  
/*****************************************************************/

void Admin::printAdUsr() const{ 
    user.print1URec();
    cout<<"Record Size    "<<recSiz<<endl
        <<"Start of file: "<<begnFile<<endl;
}

void Admin::getIndex(int &num){
    do {
        cout<<"\nEnter a number between 0 and " << (user.getTtlRec()-1) <<endl;
        cin>>num;
    } while (!(num>=0 && num <= (user.getTtlRec()-1)));
}
#include "Admin.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;  //STD Name-space where Library is compiled



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
    
   
    findByEmail(tempE); // returns -66 if email is NOT found in binary
    
    
    if( !(begnFile == -66)){// look for this email in usrBin.dat
    
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


/******************************************************************/ 
//               ONLY ADMIN CLASS HAS PERMISSION!
//          READ ADMIN BINARY FILE, RETURN 1 RECORD    
//                  & COMPARE IT TO INPUTS
/*****************************************************************/
  
void Admin::adminLogin(){
    
    cout<<"\n\tAdmin Login\n";
    
    const char ch = 'a';   
    const int index = 0;
 
    readAdBin(); 
    //print1Admin();
   
    string tempNam = "",
           tempPwrd = "";
    
    bool isName=false,
         isPwrd=false;
    
    //************************************
    //delete after all testing is finished
    tempNam=getName();
    tempPwrd = getPwrd();
    //************************************
    
//    do{        
        cout<<"\nEnter username: ";
//        cin>>tempNam;
//        isName = isMinSize(tempNam,2);
//    } while(!isName);
//    
    cout<<"Enter password: ";
//    cin>>tempPwrd;   
    
    isName = isStrEqual(getName(),tempNam);
    isPwrd = isStrEqual(getPwrd(),tempPwrd);
    
    if(!isName || !isPwrd){ 
        cout<<"Username and/or password does not match.\n";       
        return;
    
    } else { adminPortal(); } // opens function that Admin is only allowed to access
}


/******************************************************************/              
//          ONLY allowed to access these functions  
//                  if logged in as admin
/*****************************************************************/

void Admin::adminPortal(){
    
    cout<<"\nAdmin login successful.\n";
    char ans='n';
    int choice;
     
    
    
    do {
        cout<<"\n\nMenu\n"
            <<"Press 1: Update Admin\n"
            <<"Press 2: Find one index\n"
            <<"Press 3: Find by email\n"
            <<"Press 4: Edit binary\n"
            //<<"Press 5: \n"
            <<"Press 9: Logout\nEnter a number: ";
        cin>>choice;
        //cin.ignore();

        switch(choice){
            case 1:{                
                updateAdmin();        
                break;
            } 
            case 2:{ // find index in binary file  
                //cout<<"\nttlRec in user = "<<getTtlRec()<<endl;
                int num = ( rand()%(getTtlRec()) );   
                Admin usr1;
                //usr1.printUser(); 
                cout<<"\nWhich index do you want to look for? ";
                cin>>num;
                usr1.findByUsrIndx(num); 
                usr1.printUser(); 
                break;
            } 
            case 3:{ // find email in binary file
                Admin usr3;
                usr3.printUser();
                string str = "father@email.com";//mother@aa.com
                //string str = "sister@sis.com";//mother@aa.com
                usr3.findByEmail(str);
                usr3.printUser();
                break;
            }      
            case 4: {
                Admin usr2;
                //int indx=1;
                //usr2.findByUsrIndx(indx);
                string temp = "mother@aa.com";
                //string temp = "father@email.com";//
                //string temp = "sister@sis.com";
                usr2.findByEmail(temp);
                cout<<"Found "<<temp<<endl;
                usr2.printUser(); 
                usr2.setHiScore(45);
                //usr2.setName("mommy zero");
                cout<<"\nNew High Score! Updated class obj:";
                usr2.printUser();
                cout<<"\nUpdating binary....";
                usr2.reWrtBin(); // rewrites this record in binary & text files                           
                usr2.findByEmail(temp);
                //usr2.findByUsrIndx(indx); 
                usr2.printUser(); 
                break;
            }
            default: {
                cout<<"\nLogged Out.\n";                
                return;
            }
        }
    } while(choice==1 || choice==2 || choice==3 || choice==4);
}

/******************************************************************/              
//                  REWRITE 1 RECORD TO Text FILE    
//          Important! When you change # bits in any varibale will
//                  effect rewriting it to text file
/*****************************************************************/

void Admin::reWrtTxt(){
        
    cout<<"\n\nHit reWrtTxt()  recSize= "<<recSiz<<"  begnFile = "<<begnFile<<endl;
    
    fstream outTxt; 
    outTxt.open("usrData.txt", ios::ate | ios::in | ios::out ); // appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening usrData.txt\n";}
    
    cout<<"\nttlRec = "<<ttlRec<<endl;
    
    int endlCount = (ttlRec==0) ? 0 : ((85)*ttlRec);
    cout<<"\nendlCount = "<<endlCount<<endl;
    long cursor = (begnFile <= 0) ? 0 : (begnFile+endlCount); // hiScore is a int which is 4 bits
    
    cout<<"begnFile = "<< cursor <<endl;
    
    outTxt.seekp(cursor,ios::beg);  // Sets the position of the get pointer
       
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
//                  REWRITE 1 RECORD TO BINARY FILE     
/*****************************************************************/

void Admin::reWrtBin(){
        
    cout<<"\n\nHit reWrtBin()  recSize= "<<recSiz<<"  begnFile = "<<begnFile<<endl;
    
    fstream outBin; 
    outBin.open("usrData.dat", ios::ate | ios::in | ios::out | ios::binary); // appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening usrData.dat\n";}
    
    long cursor = (begnFile <= 0) ? 0 : begnFile; // hiScore is a int which is 4 bits
    
    cout<<"begnFile = "<< cursor <<endl;
    
    outBin.seekp(cursor,ios::beg);  // Sets the position of the get pointer
        
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
   
    
    // Rewrite hiScore in binary file
    cout<<"\nHiScore= "<< hiScore<<endl;
    
    outBin.write(reinterpret_cast<char *>(&hiScore) , sizeof(int)); 
      
    outBin.close(); // close file  
    
    usr2.reWrtTxt();  // rewrite this record in usrData text file
}


/*****************************************************************/
//                 Finds a User's record by their index
//                Assumes the records are in ascending order
/*****************************************************************/

void Admin::findByUsrIndx(int recIndx){
    
    recIndx = recIndx < 0 ? 0 : recIndx;
    
    cout<<endl<<"Looking for record "<<recIndx<<" in binary file.\n\n";  
    
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
        inBin.read(reinterpret_cast<char *>(&ttlRec) , sizeof(int)); 
        thisSum += sizeof(int);
        cursor += sizeof(int);          
        
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&id) , sizeof(int)); 
        thisSum += sizeof(int);
        cursor +=  sizeof(int);  
       
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        inBin.read(reinterpret_cast<char *>(&namSiz), sizeof(unsigned short) );
        thisSum += ( sizeof(unsigned short) + namSiz*sizeof(char) );
        cursor += ( sizeof(unsigned short) + namSiz*sizeof(char) );
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

               
        inBin.read(reinterpret_cast<char *>(&emaiSiz), sizeof(unsigned short) );               
        thisSum += ( sizeof(unsigned short) + emaiSiz*sizeof(char) );
        cursor += ( sizeof(unsigned short) + emaiSiz*sizeof(char) );
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        
        inBin.read(reinterpret_cast<char *>(&pwrdSiz), sizeof(unsigned short));      
        thisSum += ( sizeof(unsigned short) + pwrdSiz*sizeof(char) );        
        cursor += ( sizeof(unsigned short) + pwrdSiz*sizeof(char) );
        
        // Read in size of hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&hiScore) , sizeof(int)); 
        thisSum += sizeof(int);  
        cursor += sizeof(int);     
        
        if(count==recIndx){ rSize = thisSum; break;}
            
        count++;        
    }
       
    cursor = (count==0)? 0 : cursor;
    setRecSiz(rSize);
    setCursLoc(cursor);
    //cout<<"\nrSize = "<<rSize<<"\ncursor = "<<cursor<<endl;   
    
    //***********    SAVE LOCATED RECORD   ************************//            
    read1Bin(); //read binary & save record
    
    inBin.close();    
}

/*****************************************************************/
///         Read 1 User's record in binary & save to class object
//              Cursor is the beginning of this record
/*****************************************************************/

void Admin::read1Bin(){
    
    cout<<"Hit read1Bin()\n";
    cout<<"recSiz = "<<recSiz<<"  cursor = "<<begnFile<<endl;
    
    ifstream inBin;
    string file = "usrData.dat";        
    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; return;}
    
    // sets cursor at the beginning of the file we're looking for
    inBin.seekg(begnFile,ios::beg);    
    
    // Read & set ttlRec    
    inBin.read(reinterpret_cast<char *>(&ttlRec) , sizeof(int)); 
    
    
    // Read & set id    
    inBin.read(reinterpret_cast<char *>(&id) , sizeof(int)); 
        
        
    // Read & set name's length 
    inBin.read(reinterpret_cast<char *>(&namSiz), sizeof(unsigned short));
    
    
    // Read & set name     
    string tempStr="";
    tempStr.resize(namSiz);
    inBin.read( &tempStr[0] , namSiz*sizeof(char) ); // write this  string to binary file    
    setName(tempStr); // Set name 
    
    
    // Read & set email's length 
    inBin.read(reinterpret_cast<char *>(&emaiSiz), sizeof(unsigned short));
    

    // Read & set email     
    tempStr.resize(emaiSiz);
    inBin.read(&tempStr[0], emaiSiz*sizeof(char));    
    setEmail(tempStr);       
    
    // Read & set the length of password 
    inBin.read(reinterpret_cast<char *>(&pwrdSiz), sizeof(unsigned short)); 
    
    // Read & set password  
    tempStr.resize(pwrdSiz);
    inBin.read(&tempStr[0], pwrdSiz*sizeof(char) );  
    setPwrd(tempStr);
    
    // Read & set hiScore 
    inBin.read(reinterpret_cast<char *>(&hiScore) , sizeof(int));   
     
    
    inBin.close(); // close file
}


/*****************************************************************/
//           Read binary file, find 1 record by index
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
    inBin.read(reinterpret_cast<char *>(&namSiz), sizeof(unsigned short) );
    string str;
    str.resize(namSiz);
    inBin.read(&str[0] , namSiz*sizeof(char) );
    setName(str);
    
    
    // Read the value of emaiSiz and then use it calculate the number of bits
    // that emaiSiz and email take up in memory. 
    // Add it to cursor and move on to the next variables        
    inBin.read(reinterpret_cast<char *>(&emaiSiz), sizeof(unsigned short) );      
    str="";
    str.resize(emaiSiz);
    inBin.read(&str[0], emaiSiz*sizeof(char) );
    setEmail(str);

    
    // Read the value of pwrdSiz and then use it calculate the number of bits
    // that pwrdSiz and password take up in memory. 
    // Add it to cursor and move on to the next variables       
    inBin.read(reinterpret_cast<char *>(&pwrdSiz), sizeof(unsigned short));  
    str="";
    str.resize(pwrdSiz);    
    inBin.read(&str[0], pwrdSiz*sizeof(char) );        
    setPwrd(str);  
  
    inBin.close(); // close file
}


/******************************************************************/ 
//                 ONLY ADMIN CLASS HAS PERMISSION!
//                  WRITE 1 RECORD TO TEXT FILE     
/*****************************************************************/

void Admin::wrtAdTxt(){
    
    ofstream outTxt; 
    outTxt.open("admin.txt",ios::out); // DOES NOT appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening admin.txt\n"; exit(0);}
    
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

void Admin::wrtAdBin(){
        
    ofstream outBin;
    outBin.open("admin.dat",ios::out | ios::binary); // DOES NOT appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening admin.dat\n";}      
    
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
      
    outBin.close(); // close file    
}


/******************************************************************/ 
//
/******************************************************************/ 
void Admin::updateAdmin(){ 
    
    if(isName() && isEmail() && isPwrd()){
        print1Admin();
        wrtAdTxt();
        wrtAdBin(); 
    }
} 



/*****************************************************************/
//           Read binary file, find 1 record by email
//                     & return 1 record  
//          returns -66 if email is NOT found in binary
/*****************************************************************/

void Admin::findByEmail(string emai){
    
    cout<<endl<<endl<<"Looking for "<<emai<<" in binary file.\n\n";   
    
    ifstream inBin;
    string file = "usrData.dat";        
    
    inBin.open(file.c_str(), ios::in | ios::binary); 
    if(!inBin.is_open()){ cout<<"\nError opening "<<file<<endl; exit(0);} 
    
    bool foundEm;
    long cursor = 0L, thisSum=0L;
    int count = 0,   // start at 1, so it stops before the record I'm looking for     
            rSize = 0, // hold this records size
            nRec = getTtlRec();
    
    
    // Accumulate all the bits between the beginning of file up the record I'm looking for. 
    while( (!foundEm) && (count <= nRec) ){                 
        
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&ttlRec) , sizeof(int)); 
        thisSum +=sizeof(int);
        cursor += sizeof(int);  
        
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&id) , sizeof(int)); 
        thisSum += sizeof(int);
        cursor += sizeof(int);  
        
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        inBin.read(reinterpret_cast<char *>(&namSiz), sizeof(unsigned short) );
        thisSum += ( sizeof(unsigned short) + namSiz*sizeof(char) );
        cursor += ( sizeof(unsigned short) + namSiz*sizeof(char) );
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        
        // Read the value of emaiSiz and then use it calculate the number of bits
        // that emaiSiz and email take up in memory. 
        // Add it to cursor and move on to the next variables        
        inBin.read(reinterpret_cast<char *>(&emaiSiz), sizeof(unsigned short) );               
        thisSum += ( sizeof(unsigned short) + emaiSiz*sizeof(char) );
        cursor += ( sizeof(unsigned short) + emaiSiz*sizeof(char) );
        
        // Read email & save to a temp variable
        string binEmail = "";
        binEmail.resize(emaiSiz);
        inBin.read(&binEmail[0], emaiSiz*sizeof(char));              
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        
        // Read the value of pwrdSiz and then use it calculate the number of bits
        inBin.read(reinterpret_cast<char *>(&pwrdSiz), sizeof(unsigned short));      
        thisSum += ( sizeof(unsigned short) + pwrdSiz*sizeof(char) );
        cursor += ( sizeof(unsigned short) + pwrdSiz*sizeof(char) );        
        
        
        // Read in size of hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&hiScore) , sizeof(int)); 
        thisSum += sizeof(int);
        cursor += sizeof(int);
        
        //cout<<"\nthisSum="<<thisSum<<"  cursor="<<cursor<<"  count="<<count<<endl;
        
        foundEm = isStrEqual(emai, binEmail);
        
        if(foundEm){
            count = getTtlRec();  
            rSize = thisSum;
            
        } else{
            count++;
            thisSum = 0L;    
        }
        //cout<<count<<"=count \t   cursor = "<<cursor<<endl;   
    }    
    
    if(foundEm){        
        setRecSiz(rSize);
        cursor = (count==0) ? 0 : (cursor-rSize); 
        setCursLoc(cursor); 
        //cout<<"\n\trecSiz ="<<recSiz<<"  cursLoc="<<cursLoc<<"  count="<<count<<endl<<endl;
        read1Bin(); // read this file binary & save         
        
    } else { setCursLoc(-66); }
   
    inBin.close();
}
    
  
/*****************************************************************/
//                     PRINT ONE Admin'S INFO  
/*****************************************************************/

void Admin::print1Admin()const{  
    cout<<endl<<endl
        <<"NamSiz:    "<< namSiz <<endl
        <<"Name:      "<< name    <<endl
        <<"EmaiSiz:   "<< emaiSiz <<endl
        <<"Email:     "<< email   <<endl
        <<"PwrdSiz:   "<< pwrdSiz <<endl
        <<"Password:  "<<password<<endl;    
}

/*****************************************************************/
//                     PRINT 1 record  
/*****************************************************************/

void Admin::printUser() const{ 
    print1URec();
    cout<<"Record Size    "<<recSiz<<endl
        <<"Start of file: "<<begnFile<<endl;
}

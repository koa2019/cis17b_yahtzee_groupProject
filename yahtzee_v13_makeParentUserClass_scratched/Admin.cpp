#include "Admin.h"
#include <string> 
//#include <iostream>
//#include <fstream>
using namespace std;  //STD Name-space where Library is compiled


/*******************************************************************/
//
//               ADMIN PRIVATE FUNCTIONS SECTION
//                  FOR READING BINARY FILE  
//
/*****************************************************************/

void Admin::adminLogin(){
    
    cout<<"\n\tAdmin Login\n";
    
    /*********   READ BINARY FILE & RETURN 1 RECORD   ********/       
    Admin oneAdmin;            
    oneAdmin.readBin('a',0);  
    //cout<<"Found admin's credential.\n"; 
    oneAdmin.print1Profile();
        
    //cout<<oneAdmin.getName()<<endl<<oneAdmin.getPwrd()<<endl;
    
    string tempNam = "";
    string tempPwrd = "";
    
    bool isName=false,
         isPwrd=false;
    
    do{        
        cout<<"\nEnter username: ";
        cin>>tempNam;
        isName = isMinSize(tempNam,2);
    } while(!isName);
    
    cout<<"Enter password: ";
    cin>>tempPwrd;
    
    isName = isStrEqual(getName(),tempNam);
    isPwrd = isStrEqual(getPwrd(),tempPwrd);
    
    if(!isName || !isPwrd){ 
        cout<<"Username and/or password does not match.\n";       
        exit(0);//refresh page with javascript
    
    } else { cout<<"Admin login successful.\n";}
}


// change Admin login info
void Admin::updateAdmin(){   
    
    if(isName() && isEmail() && isPwrd()){  
        cout<<"\nProfile Updated,\n";
        print1Profile();
        wrtTxt('a');
        wrtBin('a');
    }
}

/******************************************************************/
//               ONLY ADMIN CLASS HAS PERMISSION!
//                 READING BINARY SECTION 
/*****************************************************************/


/*****************************************************************/
//               ONLY ADMIN CLASS HAS PERMISSION!
//               Read binary file & return 1 record  
/*****************************************************************/

void Admin::readBin(const char ch, int recIndx){ 
    
    cout<<endl<<endl<<"Looking for record "<<recIndx<<" in binary file.\n\n";  
    
    recIndx = recIndx < 0 ? 0 : recIndx;    
    
    ifstream inBin;
    if(ch=='u'){
        inBin.open("usrData.dat",ios::in | ios::binary); 
        if(!inBin.is_open()){ cout<<"\nError opening inBin.dat\n"; return;}
        
    } else {
        inBin.open("admin.dat",ios::in | ios::binary); 
        if(!inBin.is_open()){ cout<<"\nError opening inBin.dat\n"; return;}
    }
    
    long cursor = 0L;
    int count = 1;       // start at 1, so it stops before the record I'm looking for     
    
     
    // Accumulate all the bits between the beginning of file up the record I'm looking for.
    while(count<=recIndx){ 
                    
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&ttlRec) , sizeof(int)); 
        cursor += sizeof(int);  
        //cout<<sizeof(ttlRec)<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        // Read in sizeof id and add to cursor
        inBin.read(reinterpret_cast<char *>(&id) , sizeof(int)); 
        cursor += sizeof(int);  
        //cout<<sizeof(idSize)<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        inBin.read(reinterpret_cast<char *>(&namSiz), sizeof(unsigned short) );
        cursor += ( sizeof(unsigned short) + namSiz*sizeof(char) );
        //cout<<"     sizeof(size) = "<<sizeof(size)<<"\nsize*sizeof(char) = "<<size*sizeof(char)<<endl; 
        //cout<<"this record sum = "<<(sizeof(size)+size*sizeof(char))<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        
        // Read the value of emaiSiz and then use it calculate the number of bits
        // that emaiSiz and email take up in memory. 
        // Add it to cursor and move on to the next variables
        
        inBin.read(reinterpret_cast<char *>(&emaiSiz), sizeof(unsigned short) );               
        cursor += ( sizeof(unsigned short) + emaiSiz*sizeof(char) );
        //cout<<"     sizeof(size) = "<<sizeof(size)<<"\nsize*sizeof(char) = "<<size*sizeof(char)<<endl;          
        //cout<<"this record sum = "<<(sizeof(size)+size*sizeof(char) <<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        
        // Read the value of pwrdSiz and then use it calculate the number of bits
        // that pwrdSiz and password take up in memory. 
        // Add it to cursor and move on to the next variables
       
        inBin.read(reinterpret_cast<char *>(&pwrdSiz), sizeof(unsigned short));      
        cursor += ( sizeof(unsigned short) + pwrdSiz*sizeof(char) );        
        //cout<<"     sizeof(size) = "<<sizeof(size)<<"\nsize*sizeof(char) = "<<size*sizeof(char)<<endl;    
        //cout<<"this record sum = "<<(sizeof(size)+size*sizeof(char))<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        // Read in size of hiScore and add to cursor
        inBin.read(reinterpret_cast<char *>(&hiScore) , sizeof(int)); 
        cursor += sizeof(int);  
        //cout<<sizeof(hScore)<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        count++;
    }
    //cout<<"\n\ncursor = "<<cursor<<" which means it's at the bit before the record we're looking for.\n\n";
    
    
    //***********    SAVE LOCATED RECORD   ************************//            
    
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


/*****************************************************************/
//               Calls private member functions  
/*****************************************************************/

void Admin::findByIndx(){
    
    int nRecords = 26; // This is will need to retrieve this number from database
    int oneRec = nRecords; //(rand()%(0+nRecords)); // As of now there's 13 records in data file
        
    Admin oneAdmin;
        
    oneAdmin.readBin('a', oneRec);
    
    cout<<"Found record "<<oneRec<<endl<<endl;
    oneAdmin.print1Profile();       
}
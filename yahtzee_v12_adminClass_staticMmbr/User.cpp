using namespace std;  //STD Name-space where Library is compiled
#include "User.h"


//   Destructor
User::~User(){
    cout<<"\nHit User Destructor(). Static class, so nothing to destroy.\n";
}
void User::print1User() const{
    print1Profile();
    cout<<"Num wins: "<<getNumWins()<<endl;
}

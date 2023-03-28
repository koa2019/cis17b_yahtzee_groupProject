/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Admin.h
 * Author: DanYell
 *
 * Created on March 27, 2023, 3:05 PM
 */

#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"   // Admin class inherits User class
#include <iostream>
#include <fstream>
#include <string> 
using namespace std;  //STD Name-space where Library is compiled

class Admin : public User {
private:
    string fname; // file name
public:
    
    using User::User;
    Admin() : User(){
        fname="admin.dat";
    }
    ~Admin();
    
    // ONLY ADMIN has this ability. 
    void adminLogin();
    void updateAdmin();
    void readBin(const char, int); // ReadS binary file. 
    void findByIndx();  // Calls private member() that reads Binary file
    
    void wrtAdminTxt();
    void wrtAdminBin();
    void getAdminBin();
    
};

#endif /* ADMIN_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Customer.h
 * Author: DanYell
 *
 * Created on March 31, 2023, 1:55 PM
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H
class Customer {
    
protected:
    int hiScore;
    
public:
    Customer(){hiScore=0;}
    ~Customer(){cout<<"\nHit Customer Destructor";}
};


#endif /* CUSTOMER_H */


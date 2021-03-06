//
//  Topping.cpp
//  PizzaKerfi
//
//  Created by Þórður Atlason on 28/11/2017.
//  Copyright © 2017 Þórður Atlason. All rights reserved.
//

#include "Topping.hpp"
//using namespace std;
#include <iostream>
#include <string>

//Defult constructor.
Topping::Topping(){
    price = 0;
    name[0] = '\0';
}

///A constructor that takes in a character array and an int as parameters and gives the private variables
///nane and price the values of them.
Topping::Topping(char inName[MAXCHARINTOPPINGNAME], int inPrice){
    this->price = inPrice;
    
    strcpy(name, inName);
}

//Returns the private variable name.
char* Topping::getName(){
    return name;
}

//Take in a character array as a paramaeter and puts it into the private variable name.
void Topping::setName(char inName[MAXCHARINTOPPINGNAME]){
    for(int i = 0; i < MAXCHARINTOPPINGNAME; i++){
    name[i] = inName[i];
    }
}

//Returns the price of the topping.
int Topping::getPrice(){
    return price;
}

//Takes in a parameter and gives the private variable price the value of the parameter
void Topping::setPrice(int inPrice){
    price = inPrice;
}
    

//Overloads the ostream operator so one can use the '<<' operator to print the contents of a topping instance.
ostream& operator << (ostream& out, const Topping& topping){
    out << topping.name << TABSTRING << topping.price << endl;
    
    return out;
}

//Overloads the ostream operator so one can use the '>>' operator to input the contents of a topping instance.
istream& operator >> (istream& in, Topping& topping){
    
    cout << "Enter topping name: ";
    in >> topping.name;
    cout << "Enter topping price: ";
    in >> topping.price;
    
    return in;
}

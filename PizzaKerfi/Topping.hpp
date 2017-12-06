//
//  Topping.hpp
//  PizzaKerfi
//
//  Created by Þórður Atlason on 28/11/2017.
//  Copyright © 2017 Þórður Atlason. All rights reserved.
//

#ifndef Topping_hpp
#define Topping_hpp

#include <stdio.h>
#include <string>
#include "Global.hpp"

using namespace std;

class Topping {
    public:
        Topping();
        int getPrice();
        void setPrice(int inPrice);
        void setVerbose(bool v);
        char* getName();
        void setName(char inName[]);
        friend istream& operator >> (istream& in, Topping& topping);
        friend ostream& operator << (ostream& out, const Topping& topping);
    private:
        char name[30];
        int price;
        bool verbose = true;
};

#endif /* Topping_hpp */

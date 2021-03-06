//
//  ToppingRepo.hpp
//  PizzaKerfi
//
//  Created by Þórður Atlason on 29/11/2017.
//  Copyright © 2017 Þórður Atlason. All rights reserved.
//

#ifndef ToppingRepo_hpp
#define ToppingRepo_hpp

#include <stdio.h>
#include <vector>
#include "Topping.hpp"
#include "Global.hpp"

using namespace std;

class ToppingRepo{
    
public:
        void addTopping(Topping& topping);
        Topping retrieveTopping();
        void displayToppings();
        vector<Topping> getVectorOfToppings();
        void storeVectorOfToppings(vector<Topping> toppings);
        Topping selectTopping();
    private:
        void clearToppings();
        void createToppings();
};

#endif /* ToppingRepo_hpp */


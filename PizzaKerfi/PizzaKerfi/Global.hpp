//
//  Global.hpp
//  PizzaKerfi
//
//  Created by Þórður Atlason on 06/12/2017.
//  Copyright © 2017 Þórður Atlason. All rights reserved.
//

#ifndef Global_hpp
#define Global_hpp

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

const char CHARFORSETFILL = '-';
const int SIZEOFSETW = 76;
const int SIZEOFSETWBIG = 100;
const int MAXCHARSINBASENAME = 4;
const int MAXCHARINSIZENAME = 4;
const int MAXCHARINSIDENAME = 20;
const int MAXCHARINDRINKNAME = 10;
const int MAXCHARINLOCATIONNAME = 15;
const int MAXTOPPINGS = 16;
const int MAXCHARSINTOPPINGNAME = 4;
const int MAXSTUFFSINORDER = 20;
const int MAXCHARINSTATUSSTRING = 10;
const int MAXCHARINPRICESTRING = 5;
const int MAXCHARINSTATUSANDPRICESTRING = 40;
const int SIZEOFSPACEBETWEENPIZZASTATUSANDPRICE = 10;

const int MAXTOPPINGSONPIZZA = 16;
const int MAXCHARSINPIZZANAME = 100;
const int MAXCHARSINPIZZASIZE = 4;
const int MAXPIZZASINPIZZAFILE = 20;

const string TABSTRING = "\t\t\t\t\t\t\t\t\t\t\t\t\t";
const string HALFTABSTRING = "\t\t\t\t\t";
const string LONGLINE = "---------------------------------------------------------------------------";
enum status {WAITING, PREPPING, READY, DELIVERED};

const string PIZZAFILE = "pizzas.dat";
const string ORDERFILE = "orders.dat";
#endif /* Global_hpp */

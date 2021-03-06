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

//MUNA AÐ SKILJA EFTIR PLÁSS FYRIR NULLCHARACTER Í LOKIN

const int SIZEFORSETWSPACE = 17;
const int SIZEFORSETWBIGSPACE = 22;
const int SIZEOFCENTERHEADING = 26;
const int SIZEOFBIGCENTERHEADING = 35;
const int SIZEOFPRICECHARACTERS = 8;
const int SIZEOFIDCHARACTERS = 6;


const int SIZEOFPRICESPACE = 82;
const int SIZEOFSMALLPRICESPACE = 58;

const char CHARFORSETFILL = '-';
const char CHARFORSUBACTION = '+';
const char CHARFORSPACE = ' ';

const int SIZEOFSETW = 76;
const int SIZEOFSETWBIG = 100;
const int MAXCHARINBASENAME = 5;
const int MAXCHARINSIZENAME = 5;
const int MAXCHARINSIDENAME = 20;
const int MAXCHARINDRINKNAME = 10;
const int MAXCHARINLOCATIONNAME = 26;
const int MAXCHARINTOPPINGNAME = 4;
const int MAXSTUFFSINORDER = 20;
const int MAXCHARINSTATUSSTRING = 10;
const int MAXCHARINORDERSTATUSSTRING = 10;
const int MAXCHARINPRICESTRING = 5;
const int MAXCHARINSTATUSANDPRICESTRING = 40;

const int SIZEOFADDTOPPINGSPACES = 42;

const int MAXTOPPINGSONPIZZA = 16;
const int MAXCHARSINPIZZANAME = 36;
const int MAXPIZZASINPIZZAFILE = 20;
const int MAXCHARINORDERCOMMENT = SIZEOFSETWBIG-8;
const int CHARFORTIME = 13;

const string TABSTRING = "\t\t\t\t\t\t\t\t\t\t\t\t\t";
enum status {WAITING, PREPPING, READY, OUTOFSHOP};
enum orderStatus {UNPAID, PAID, DELIVERED};

const string PIZZAFILE = "pizzas.dat";
const string ORDERFILE = "orders.dat";
const string LEGACYORDERFILE = "legacyOrders.dat";
const string BASEFILE = "bases.dat";
const string MENUITEMFILE = "menuitems.dat";
#endif /* Global_hpp */

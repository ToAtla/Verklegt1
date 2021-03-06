//
//  DeliveryUI.cpp
//  PizzaKerfi
//
//  Created by Nokkvi Karlsson on 11/29/17.
//  Copyright © 2017 Þórður Atlason. All rights reserved.
//

#include "DeliveryUI.hpp"
#include "OrderRepo.hpp"
#include "LocationRepo.hpp"
#include <iostream>

using namespace std;

void DeliveryUI::startDeliveryUI(){
    
    if(bizniz.isValidLocationFile()){
    
        char input = '\0';
        string sInput;
        bool cont = true;
        try {
            chooseYourLocation();
            magic.clearScreen();
        } catch (InvalidInputException) {
            cout << endl << "Invalid input! (input can't be a character and has to match a number on the list) Try again" << endl << endl;
            cout << "Press any key to continue: ";
            cin.ignore();
            getline(cin, sInput);
            cont = false;
        }
        
        if(cont){
            while(input != 'b'){
                cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETW) << "-" << setfill(' ') << endl;
                cout << setfill(' ') << setw(SIZEOFCENTERHEADING) << " " << "Delivery for " << locationOfDelivery << endl;
                cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETW) << "-" << setfill(' ') << endl << endl;
                cout << setfill(' ') << setw(SIZEFORSETWSPACE) << " "  << "1: List all orders" << endl;
                uiItemSeparator();
                cout << setfill(' ') << setw(SIZEFORSETWSPACE) << " " << "2: List all unpaid orders" << endl;
                uiItemSeparator();
                cout << setfill(' ') << setw(SIZEFORSETWSPACE) << " " << "3: List all paid orders" << endl;
                uiItemSeparator();
                cout << setfill(' ') << setw(SIZEFORSETWSPACE) << " " << "4: List all legacy orders" << endl;
                uiItemSeparator();
                cout << setfill(' ') << setw(SIZEFORSETWSPACE) << " " << "b: back" << endl;
                uiItemSeparator();
                cin >> input;
                cout << endl;
                
                if(input == '1'){
                    magic.clearScreen();
                    displayAllOrders();
                }
                else if(input == '2'){
                    magic.clearScreen();
                    displayUnpaidOrders();
                }
                else if(input == '3'){
                    magic.clearScreen();
                    displayPaidOrders();
                }
                else if(input == '4'){
                    magic.clearScreen();
                    displayLegacyOrders();
                }
            }
        }
    }
}

void DeliveryUI::chooseYourLocation(){
    
    vector<Location> locations;
    LocationRepo lr;
    locations = lr.getVectorOfLocations();
    
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETW) << "-" << endl;
    cout << setfill(CHARFORSPACE) << setw(SIZEOFCENTERHEADING+7) << " " << "Delivery" << endl;
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETW) << "-" << endl << endl;
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFCENTERHEADING-2) << "-" << "    Choose your location    " << setfill(CHARFORSETFILL) << setw(24) << "-";
    cout << endl << endl;
    
    
    for(int i = 0; i < locations.size(); i++){
        cout << setfill(' ') << setw(SIZEFORSETWSPACE) << " " << "Location number: " << i+1 << endl;
        cout << setfill(' ') << setw(SIZEFORSETWSPACE) << " " << locations[i] << endl;
        uiItemSeparator();
    }
    cout << "Choose location (no whitespaces): ";
    string input;
    cin >> input;
    
    if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), locations.size())){
        
        int intInput = stoi(input);
    
        for(int i = 0; i < locations.size(); i++){
            if(intInput == i+1){
                this->locationOfDelivery = locations[i];
            }
        }
    }
}

void DeliveryUI::displayAllOrders(){
    string orderFile = "orders.dat";
    OrderRepo ordRep;
    int sizeOfOrderList;
    Order* orders = ordRep.retrieveOrderArray(orderFile, sizeOfOrderList);
    //Kominn með allar pantanir
    //þarf núna að sigta út virkar pantanir þeas þær sem er ekki búið að afgreiða
    int amountOfUndeliveredOrdersAtThisLocation = 0;
    for (int i = 0; i < sizeOfOrderList; i++) {
        if(locationOfDelivery.getLocation() == orders[i].getLocation().getLocation() && orders[i].getStatusOfOrder() != DELIVERED){
            amountOfUndeliveredOrdersAtThisLocation++;
        }
    }
    
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETWBIG) << "-" << setfill(CHARFORSPACE) << endl;
    cout << setfill(CHARFORSPACE) << setw(SIZEOFCENTERHEADING+2) << " " << "Listing All Active Orders in " << locationOfDelivery << endl;
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETWBIG) << "-" << setfill(CHARFORSPACE) << endl << endl;
    
    if(ordRep.fileExists(orderFile) && amountOfUndeliveredOrdersAtThisLocation != 0){
        for (int i = 0; i < sizeOfOrderList; i++) {
            if(locationOfDelivery.getLocation() == orders[i].getLocation().getLocation() && orders[i].getStatusOfOrder() != DELIVERED){
                cout << orders[i] << endl;
            }
        }
        cout << endl;
    }else{
        cout << endl;
        cout << "List is empty" << endl;
        cout << endl;
    }
    delete [] orders;
}

void DeliveryUI::displayUnpaidOrders(){
    
    OrderRepo ordRep;
    int sizeOfOrderList;
    Order* orders = ordRep.retrieveOrderArray(ORDERFILE, sizeOfOrderList);
    //Kominn með allar pantanir
    //þarf núna að sigta út ógreiddar
    int amountOfUnpaidOrdersAtThisLocation = 0;
    for (int i = 0; i < sizeOfOrderList; i++) {
        if(locationOfDelivery.getLocation() == orders[i].getLocation().getLocation() && orders[i].getStatusOfOrder() == UNPAID){
            amountOfUnpaidOrdersAtThisLocation++;
        }
    }
    
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETWBIG) << "-" << setfill(CHARFORSPACE) << endl;
    cout << setfill(CHARFORSPACE) << setw(SIZEOFCENTERHEADING+2) << " " << "Listing All UNPAID Orders in " << locationOfDelivery << endl;
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETWBIG) << "-" << setfill(CHARFORSPACE) << endl << endl;
    
    if(ordRep.fileExists(ORDERFILE) && amountOfUnpaidOrdersAtThisLocation != 0){
        for (int i = 0; i < sizeOfOrderList; i++) {
            if(locationOfDelivery.getLocation() == orders[i].getLocation().getLocation() && orders[i].getStatusOfOrder() == UNPAID){
                cout << orders[i] << endl;
            }
        }
        cout << endl;
    
    
        int input = 1;
        while(input != 0){
            cout << "Enter order number to mark as PAID or 0 to exit (order number is in the top left corner, no whitespaces): ";
            char charInput = 0;
            cin >> charInput;
            input = charInput-48;
            if(input != 0 && bizniz.orderExist(input) && bizniz.getOrderByID(input).getStatusOfOrder() == UNPAID){
                
                bizniz.setOrderStatus(ORDERFILE, input, PAID);
                cout << endl << "Order number " << input << " has been marked as PAID" << endl;
                input = 0;
            }
        }
    }else{  
        cout << endl;
        cout << "List is empty" << endl;
        cout << endl;
    }
    delete [] orders;
}

void DeliveryUI::displayPaidOrders(){
    string orderFile = "orders.dat";
    OrderRepo ordRep;
    int sizeOfOrderList;
    Order* orders = ordRep.retrieveOrderArray(orderFile, sizeOfOrderList);
    //Kominn með allar pantanir
    //þarf núna að sigta út greiddar
    int amountOfPaidUndeliveredOrdersAtThisLocation = 0;
    for (int i = 0; i < sizeOfOrderList; i++) {
        if(locationOfDelivery.getLocation() == orders[i].getLocation().getLocation() && orders[i].getStatusOfOrder() == PAID && orders[i].getStatusOfOrder() != DELIVERED){
            amountOfPaidUndeliveredOrdersAtThisLocation++;
        }
    }
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETWBIG) << "-" << setfill(CHARFORSPACE) << endl;
    cout << setfill(CHARFORSPACE) << setw(SIZEOFCENTERHEADING) << " " << "Listing All PAID Orders in " << locationOfDelivery << endl;
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETWBIG) << "-" << setfill(CHARFORSPACE) << endl << endl;
    
    if(ordRep.fileExists(orderFile) && amountOfPaidUndeliveredOrdersAtThisLocation != 0){
        for (int i = 0; i < sizeOfOrderList; i++) {
            if(locationOfDelivery.getLocation() == orders[i].getLocation().getLocation() && orders[i].getStatusOfOrder() == PAID && orders[i].getStatusOfOrder() != DELIVERED){
                cout << orders[i] << endl;
            }
        }
        cout << endl;
    
    
        int input = 1;
        while(input != 0){
            cout << "Enter number of order to mark delivered or 0 to exit (order number is in the top left corner, no whitespaces): ";
            char charInput = 0;
            cin >> charInput;
            input = charInput-48;
            if((input != 0) && bizniz.orderExist(input) && bizniz.getOrderByID(input).getStatusOfOrder() == PAID){
                
                if(!bizniz.allPizzasInOrderReady(bizniz.getOrderByID(input))){
                    cout << "Not all items in that order are ready" << endl;
                }else{
                    
                    for (int i = 0; i < bizniz.getOrderByID(input).getNumberOfPizzas(); i++) {
                        bizniz.changeStatusOfPizzaInOrder(bizniz.getOrderIndexByID(input), i, OUTOFSHOP);
                    }
                    bizniz.setOrderStatus(ORDERFILE, input, DELIVERED);
                    bizniz.moveOrderBetween(ORDERFILE, LEGACYORDERFILE, input);
                    cout << endl << "Order number " << input << " has been marked DELIVERED" << endl;
                    input = 0;
                }
            }
        }
    }else{
        cout << endl;
        cout << "List is empty" << endl;
        cout << endl;
    }
    delete [] orders;
}


void DeliveryUI::displayLegacyOrders(){
    
    //BREYTA ÞESSU!!
    string orderFile = LEGACYORDERFILE;
    OrderRepo ordRep;
    int sizeOfOrderList;
    Order* orders = ordRep.retrieveOrderArray(orderFile, sizeOfOrderList);
    //Kominn með allar pantanir
    //þarf núna að sigta út óvirkar pantanir þeas þær sem er bið að afgreiða
    int amountOfDeliveredOrdersAtThisLocation = 0;
    for (int i = 0; i < sizeOfOrderList; i++) {
        if(locationOfDelivery.getLocation() == orders[i].getLocation().getLocation() && orders[i].getStatusOfOrder() == DELIVERED){
            amountOfDeliveredOrdersAtThisLocation++;
        }
    }
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETWBIG) << "-" << setfill(CHARFORSPACE) << endl;
    cout << setfill(CHARFORSPACE) << setw(SIZEOFCENTERHEADING) << " " << "Listing All Legacy Orders in " << locationOfDelivery << endl;
    cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETWBIG) << "-" << setfill(CHARFORSPACE) << endl << endl;
    
    if(ordRep.fileExists(orderFile) && amountOfDeliveredOrdersAtThisLocation != 0){
        for (int i = 0; i < sizeOfOrderList; i++) {
            if(locationOfDelivery.getLocation() == orders[i].getLocation().getLocation() && orders[i].getStatusOfOrder() == DELIVERED){
                cout << orders[i] << endl;
            }
        }
        cout << endl;
    }else{
        cout << endl;
        cout << "List is empty" << endl;
        cout << endl;
    }
    delete [] orders;
}

void DeliveryUI::uiItemSeparator () {
    cout << setw(SIZEFORSETWSPACE) << " " << setfill(CHARFORSETFILL) << setw(SIZEOFSETW-41) << "-" << endl << endl;
    cout << setfill(' ');
}

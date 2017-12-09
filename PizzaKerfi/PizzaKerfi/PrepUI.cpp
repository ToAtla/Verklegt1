//
//  PrepUI.cpp
//  PizzaKerfi
//
//  Created by Nokkvi Karlsson on 11/29/17.
//  Copyright © 2017 Þórður Atlason. All rights reserved.
//

#include "PrepUI.hpp"
#include "PizzaRepo.hpp"
#include <iostream>

using namespace std;

void PrepUI::startPrepUI(){
    char input = '\0';
    magic.clearScreen();
    cout << "++++++++++++++++ Preperation +++++++++++++++++++" << endl << endl;;
    chooseYourLocation();
    
    while(input != 'b'){
        magic.clearScreen();
        cout << "Preparation line in " << locationOfPrep << endl;
        cout << "1: List all pizzas in house" << endl;
        cout << "2: List waiting pizzas and sides" << endl;
        cout << "3: List pizzas and sides in preparation" << endl;
        cout << "4: List ready pizzas and sides" << endl;
        cout << "b: back" << endl;
        cin >> input;
        cout << endl;
        
        if(input == '1'){
            allActiveOverview();
        }
        else if(input == '2'){
            waitingOverview();
        }
        else if(input == '3'){
            preppingOverview();
        }
        else if(input == '4'){
            readyOverview();
        }
    }
}

void PrepUI::chooseYourLocation(){
    
    vector<Location> locations;
    LocationRepo lr;
    locations = lr.getVectorOfLocations();
    bool goodInput = true;
    
    while(goodInput) {
        cout << "- - - - - - Choose your location - - - - - - -" << endl;
        for(int i = 0; i < locations.size(); i++){
            cout << "Location number: " << i+1 << endl;
            cout << locations[i] << endl << endl;
        }
        cout << "Choose location: ";
        char input = 0;
        cin >> input;
        
        //Herna athuga eg hvort að input se bokstafur og ef það er bokstafur þa breyti eg good input i false.
        if(!isdigit(input)){
            cout << "Please enter a valid input" << endl;
            goodInput = false;
        }
        
        //Ef að inputið er ekki bokstafur þa fer fer maður í for loopuna og gefur private breytunni locationOfPrep gildid sem þu valdir.
        //Og goodInput er sett false og while loopan hættir að loopa.
        if(goodInput)
        {
            for(int i = 0; i < locations.size(); i++){
                if(input-48 == i+1){
                    this->locationOfPrep = locations[i];
                    goodInput = false;
                }
            }
        }
    }
}

void PrepUI::allActiveOverview(){
    //Fylki af öllum
    //ýtra í gegnum það og birta þær
    string input;
    input[0] = '\0';
    magic.clearScreen();
    while(input != "0"){
        canPrintPizzaListWithoutStatusAtCurrentLocationAndDoes(DELIVERED);
        cout << "Enter any key to continue: ";
        cin >> input;
        input = "0";
    }
}

void PrepUI::waitingOverview(){
    status currentStatus = WAITING;
    status nextStatus = PREPPING;
    string input;
    input[0] = '\0';
    magic.clearScreen();
    while(input != "0"){
        if(canPrintPizzaListWithStatusAtCurrentLocationAndDoes(WAITING)){
            cout << "Enter any key to mark top pizza in preparation or 0 to exit: ";
            cin >> input;
            if(input != "0"){
                int orderNum;
                int pizzaNum;
                bizniz.locateFirstOrderWithPizzaWithStatusAtLocation(currentStatus, locationOfPrep, orderNum, pizzaNum);
                bizniz.changeStatusOfPizzaInOrder(orderNum, pizzaNum, nextStatus);
                cout << "Top pizza marked in preparation" << endl;
                magic.clearScreen();
            }else{
                break;
            }
        }else{
            cout << "Enter any key to continue: ";
            cin >> input;
            input = "0";
        }
    }
}










bool PrepUI::canPrintPizzaListWithStatusAtCurrentLocationAndDoes(status status){
    int size;
    Order* orderList = bizniz.getArrayOfOrdersAtLocationWithPizzasWithStatus(status, locationOfPrep, size);
    cout << " - - - - Pizzas with status " << bizniz.statusToString(status) << " - - - - " << endl;
    
    if(size != 0){
        for (int i = 0; i < size; i++) {
            cout << "#" << orderList[i].getID() << endl;
            int howManyPizzasApply;
            Pizza* pizzasThatApply = bizniz.extractAllPizzasWithStatusFromOrder(orderList[i], status, howManyPizzasApply);
            for (int c = 0; c < howManyPizzasApply; i++) {
                cout << pizzasThatApply[c];
            }
            delete [] pizzasThatApply;
            //cout << "[" << i+1 << "] " << pizzaList[i] << endl;
        }
        delete [] orderList;
        return true;
    }else{
        cout << endl;
        cout << "List is empty" << endl;
        cout << endl;
        delete [] orderList;
        return false;
    }
}








bool PrepUI::canPrintPizzaListWithoutStatusAtCurrentLocationAndDoes(status status){
    int size;
    Order* orderList = bizniz.getArrayOfOrdersAtLocationWithPizzasWithoutSomeStatus(status, locationOfPrep, size);
    cout << " - - - - Pizzas with status " << bizniz.statusToString(status) << " - - - - " << endl;
    
    if(size != 0){
        for (int i = 0; i < size; i++) {
            cout << "#" << orderList[i].getID() << endl;
            int howManyPizzasApply;
            Pizza* pizzasThatApply = bizniz.extractAllPizzasWithStatusFromOrder(orderList[i], status, howManyPizzasApply);
            for (int c = 0; c < howManyPizzasApply; i++) {
                cout << pizzasThatApply[c];
            }
            delete [] pizzasThatApply;
            //cout << "[" << i+1 << "] " << pizzaList[i] << endl;
        }
        delete [] orderList;
        return true;
    }else{
        cout << endl;
        cout << "List is empty" << endl;
        cout << endl;
        delete [] orderList;
        return false;
    }
}


void PrepUI::preppingOverview(){
    status currentStatus = PREPPING;
    status nextStatus = READY;
    string input;
    input[0] = '\0';
    magic.clearScreen();
    while(input != "0"){
        if(canPrintPizzaListWithStatusAtCurrentLocationAndDoes(currentStatus)){
            cout << "Enter any key to mark top pizza ready or 0 to exit: ";
            cin >> input;
            if(input != "0"){
                int orderNum;
                int pizzaNum;
                bizniz.locateFirstOrderWithPizzaWithStatusAtLocation(currentStatus, locationOfPrep, orderNum, pizzaNum);
                bizniz.changeStatusOfPizzaInOrder(orderNum, pizzaNum, nextStatus);
                cout << "Top pizza marked ready" << endl;
                magic.clearScreen();
            }else{
                break;
            }
        }else{
            cout << "Enter any key to continue: ";
            cin >> input;
            input = "0";
        }
    }
}


void PrepUI::readyOverview(){
    string input;
    input[0] = '\0';
    magic.clearScreen();
    while(input != "0"){
        canPrintPizzaListWithStatusAtCurrentLocationAndDoes(READY);
        cout << "Enter any key to continue: ";
        cin >> input;
        input = "0";
    }
}



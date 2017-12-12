//
//  AdminUI.cpp
//  PizzaKerfi
//
//  Created by Nokkvi Karlsson on 11/29/17.
//  Copyright © 2017 Þórður Atlason. All rights reserved.
//

#include "AdminUI.hpp"



//Prentar út valmynd sem býður notandanum að velja það sem hann vill fikta í.
void AdminUI::startAdminUI(){

    
    
    char input = 0;
    while(input != 'b'){
        magic.clearScreen();
        cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETW) << "-" << endl;
        cout << setfill (' ') << setw(40) << "Admin" << endl;
        cout << setfill(CHARFORSETFILL) << setw(SIZEOFSETW) << "-" << setfill(' ') << endl << endl;
        cout << setw(SIZEOFNUMBERLISTADMINUI) << "1: " << "Add/change the topping list" << endl;
        uiItemSeparator();
        cout << setw(SIZEOFNUMBERLISTADMINUI) << "2: " << "Add/change the location list" << endl;
        uiItemSeparator();
        cout << setw(SIZEOFNUMBERLISTADMINUI) << "3: " << "Add/change the side list" << endl;
        uiItemSeparator();
        cout << setw(SIZEOFNUMBERLISTADMINUI) << "4: " << "Add/change the drink list" << endl;
        uiItemSeparator();
        cout << setw(SIZEOFNUMBERLISTADMINUI) << "5: " << "Add/change the size list" << endl;
        uiItemSeparator();
        cout << setw(SIZEOFNUMBERLISTADMINUI) << "6: " << "Add/change the base list" << endl;
        uiItemSeparator();
        cout << setw(SIZEOFNUMBERLISTADMINUI) << "b: " << "back" << endl;
        uiItemSeparator();
        cin >> input;
        magic.clearScreen();
        cout << endl;

        if(input == '1'){
            magic.clearScreen();
            displayToppingMenu();
        }
        else if(input == '2'){
            magic.clearScreen();
            displayLocationMenu();
        }
        else if(input == '3'){
            magic.clearScreen();
            displaySideMenu();
        }
        else if(input == '4'){
            magic.clearScreen();
            displayDrinkMenu();
        }
        else if(input == '5'){
            magic.clearScreen();
            displaySizeMenu();
        }
        else if(input == '6'){
            magic.clearScreen();
            displayBaseMenu();
        }
    }
}

//Prentar út valmynd sem býður notandanum uppá að velja það sem hann vill gera með topping listann.
void AdminUI::displayToppingMenu(){
    
    char input = '\0';
    while(input != 'b'){
        cout << setfill(CHARFORSETFILL) << setw(30) << "-" << "    Toppings    " << setfill(CHARFORSETFILL) << setw(30) << "-" << endl << endl;
        cout << setfill(' ') << setw(20) << "1: " << "List toppings" << endl;
        uiItemSeparator();
        cout << setw(20) << "2: " << "Change a topping" << endl;
        uiItemSeparator();
        cout << setw(20) << "3: " << "Add a topping" << endl;
        uiItemSeparator();
        cout << setw(20) << "4: " << "Remove a topping" << endl;
        uiItemSeparator();
        cout << setw(20) << "b: " << "back" << endl;
        uiItemSeparator();
        cin >> input;
        cout << endl;

        if(input == '1'){
            magic.clearScreen();
            displayAllToppings();
        }
        else if(input == '2'){
            magic.clearScreen();
            try {
                changeTopping();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidPriceException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
            
        }
        else if(input == '3'){
            magic.clearScreen();
            try {
                addTopping();
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidPriceException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
        else if(input == '4'){
            magic.clearScreen();
            try {
                removeTopping();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
    }
}

//Prentar út lista yfir öll álegg sem eru í toppings.txt
void AdminUI::displayAllToppings(){

    ToppingRepo toppingRepo;
    vector<Topping> toppings = bizniz.getVectorOfToppings();
    
    cout << endl << setfill(CHARFORSETFILL)<< setw(24) << "-" << "    List of all toppings    " << setfill(CHARFORSETFILL) << setw(24) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(toppings.size() < 1){
        cout << endl << setfill(' ') << setw(48) << "The file is empty :(" << endl << endl;
    }
    else{
        for (int i = 0; i < toppings.size(); i++) {
            Topping temp = toppings.at(i);
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }
    }
    
    cout << endl;
    
}

//Bætir við áleggi í textaskránna toppings.txt
void AdminUI::addTopping(){
    
    string name;
    string price;

    
    cout << setfill(CHARFORSETFILL) << setw(25) << "-" << "    Adding a topping!    " << setfill(CHARFORSETFILL) << setw(26) << "-" << endl << endl;
    cout << setfill(' ') << setw(SIZEOFADDTOPPINGSPACES) << "Enter topping name (Max " << MAXCHARINTOPPINGNAME-1 << " letters): ";
    cin >> name;
    cout << setw(SIZEOFADDTOPPINGSPACES-3) << "Enter topping price: ";
    cin >> price;
    if(bizniz.isValidName(name) && bizniz.isPriceDigit(price) && bizniz.isValidNameLength(name, MAXCHARINTOPPINGNAME)){
            
        int intPrice = stoi(price);
        char tempName[MAXCHARINTOPPINGNAME];
        strcpy(tempName, name.c_str());
        Topping temp(tempName, intPrice);
            
        bizniz.addTopping(temp);
        
    }
    cout << endl << setw(SIZEOFADDTOPPINGSPACES-10) << "Topping added!" << endl << endl;
}

//Tekur á móti vector af öllum áleggjum úr toppings.txt skránni og birtir það sem lista.
//Gerir notandanum kleift að velja álegg af listanum og breyta nafninu og verðinu á því.
void AdminUI::changeTopping(){

    vector<Topping> toppings = bizniz.getVectorOfToppings();
    cout << endl;
    cout << endl << setfill(CHARFORSETFILL) << setw(24) << "-" << "    List of all toppings    " << setfill(CHARFORSETFILL) << setw(24) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    if(toppings.size() < 1){
        cout << endl << setfill(' ') << setw(48) << "The file is empty :(" << endl << endl;
    }
    else{
        for(int i = 0; i < toppings.size(); i++){
            Topping temp = toppings.at(i);
            cout << setfill(' ') << setw(30) << "Topping number: " << i+1 << endl;
            cout << setw(17) << temp.getName() << setw(40) << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl;
        }
        string input;
        cout << setfill(' ') << setw(42) << "Choose a topping to change: ";
        cin >> input;
        
        
        
        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), toppings.size())){
            int intInput = stoi(input);
            
            for(int i = 0; i < toppings.size(); i++){
                if(intInput == i+1){
                    cout << setw(SIZEOFADDTOPPINGSPACES-4) << "Enter topping name (Max " << MAXCHARINTOPPINGNAME-1 << " letters): ";
                    string name;
                    cin >> name;
                    cout << setw(SIZEOFADDTOPPINGSPACES-7) << "Enter toppine price: ";
                    string price;
                    cin >> price;
                    if(bizniz.isValidName(name) && bizniz.isPriceDigit(price) && bizniz.isValidNameLength(name, MAXCHARINTOPPINGNAME)){
                        
                        int intPrice = stoi(price);
                        
                        if(bizniz.isValidPrice(intPrice)){
                            char tempName[MAXCHARINTOPPINGNAME];
                            strcpy(tempName, name.c_str());
                            
                            Topping temp(tempName, intPrice);
                            toppings.at(i) = temp;
                            cout << endl << setw(SIZEOFADDTOPPINGSPACES-12) << "Topping changed!" << endl << endl;
                        }
                    }
                }
            }
            bizniz.storeVectorOfToppings(toppings);
        }
    }
}

//Tekur á móti vector af af öllum áleggjum úr toppings.txt skránni og birtir það sem lista.
//Gerir notandanum kleift að velja álegg af listanum og eyða því.
void AdminUI::removeTopping(){

        vector<Topping> toppings = bizniz.getVectorOfToppings();
        cout << endl;
    
        cout << endl << setfill(CHARFORSETFILL) << setw(24) << "-" << "    List of all toppings    " << setfill(CHARFORSETFILL) << setw(24) << "-" << endl << endl;
        cout << setfill(' ') << setw(58) << "Price" << endl;
        cout << setw(58) << "-----" << endl;
    
        if(toppings.size() < 1){
                cout << endl << setfill(' ') << setw(48) << "The file is empty :(" << endl << endl;
        }  else {
            for(int i = 0; i < toppings.size(); i++){
                Topping temp = toppings.at(i);
                cout << setfill(' ') << setw(30) << "Topping number: " << i+1 << endl;
                cout << setw(17) << temp.getName() << setw(40) << temp.getPrice() << endl;
                cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl;
            }

            string input;
            cout << setfill(' ') << setw(42) << "Choose a topping to remove: ";
            cin >> input;
        
            if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), toppings.size())){
                int intInput = stoi(input);

                    bizniz.removeTopping(toppings, intInput);
                    cout << endl << setw(29) << "Topping removed" << endl << endl;
            }
        }
}


void AdminUI::displayLocationMenu(){
   
    char input = '\0';
    while(input != 'b'){
        cout << setfill(CHARFORSETFILL) << setw(30) << "-" << "    Locations    " << setfill(CHARFORSETFILL) << setw(29) << "-" << endl << endl;
        cout << setfill(' ') << setw(20) << "1: " << "List locations" << endl;
        uiItemSeparator();
        cout << setw(20) << "2: " << "Change a location" << endl;
        uiItemSeparator();
        cout << setw(20) << "3: " << "Add a location" << endl;
        uiItemSeparator();
        cout << setw(20) <<"4: " << "Remove a location" << endl;
        uiItemSeparator();
        cout << setw(20) << "b: " << "back" << endl;
        uiItemSeparator();
        cin >> input;
        cout << endl;

        if(input == '1'){
            magic.clearScreen();
            displayAllLocations();
        }
        else if(input == '2'){
            magic.clearScreen();
            try {
                changeLocation();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
        else if(input == '3'){
            magic.clearScreen();
            try {
                addLocation();
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
        else if(input == '4'){
            magic.clearScreen();
            try {
                removeLocation();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
            
        }
    }
}

//Prentar út lista yfir alla afhendingarstaði.
void AdminUI::displayAllLocations(){
    
    vector<Location> locations = bizniz.getVectorOfLocations();
    cout << endl << setfill(CHARFORSETFILL)<< setw(24) << "-" << "    List of all locations    " << setfill(CHARFORSETFILL) << setw(23) << "-" << endl << endl;
    if(locations.size() < 1){
        cout << endl << setfill(' ') << setw(48) << "The file is empty :("  << endl;
    }
    
    for (int i = 0; i < locations.size(); i++) {
        Location temp = locations.at(i);
        cout << setfill(' ') << setw(14) << " " << temp.getLocation() << endl;
        cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
    }
    cout << endl;
}

void AdminUI::addLocation(){

    string name;
    cout << setfill(CHARFORSETFILL) << setw(25) << "-" <<  "    Adding a location!    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(SIZEOFADDTOPPINGSPACES) << "Enter location name (Max " << MAXCHARINLOCATIONNAME-1 << " letters): ";
    cin.ignore();
    getline(cin, name);
    char tempName[MAXCHARINLOCATIONNAME];
    
    strcpy(tempName, name.c_str());
    
    if(bizniz.isValidNameLength(name, MAXCHARINLOCATIONNAME)){
        Location temp(tempName);
        bizniz.addLocation(temp);
        cout << endl << setw(SIZEOFADDTOPPINGSPACES-10) << "Location added!" << endl << endl;
    }
}

void AdminUI::changeLocation(){
   
    vector<Location> locations = bizniz.getVectorOfLocations();
    cout << endl;
    cout << endl << setfill(CHARFORSETFILL)<< setw(24) << "-" << "    List of all locations    " << setfill(CHARFORSETFILL) << setw(23) << "-" << endl << endl;
    
    if(locations.size() > 0){
    for(int i = 0; i < locations.size(); i++){
        Location temp = locations.at(i);
        cout << setfill(' ') << setw(31) << "Location number: " << i+1 << endl;
        cout << "\t\t\t " << temp << endl;
        cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl;
    }
    string input;
    cout << endl << setfill(' ') << setw(43) << "Choose a location to change: ";
    cin >> input;
    
    
        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), locations.size())){
        int intInput = stoi(input);
            
        for(int i = 0; i < locations.size(); i++){
            if(intInput == i+1){
                cout << setw(SIZEOFADDTOPPINGSPACES-3) << "Enter location name (Max " << MAXCHARINLOCATIONNAME-1 << " letters): ";
                string name;
                cin.ignore();
                getline(cin, name);
                char tempName[MAXCHARINLOCATIONNAME];
                
                strcpy(tempName, name.c_str());
                
                if(bizniz.isValidNameLength(name, MAXCHARINLOCATIONNAME)){
                    Location temp(tempName);
                    locations.at(i) = temp;
                    cout << endl << setw(SIZEOFADDTOPPINGSPACES-11) << "Location changed!" << endl << endl;
                }
            }
        }
        bizniz.storeVectorOfLocations(locations);
    }
    }
    else{
        cout << endl << setfill(' ') << setw(48) << "The file is empty :(" << endl << endl;
    }
}

void AdminUI::removeLocation(){

    
    vector<Location> locations = bizniz.getVectorOfLocations();
    cout << endl;
    cout << endl << setfill(CHARFORSETFILL)<< setw(24) << "-" << "    List of all locations    " << setfill(CHARFORSETFILL) << setw(23) << "-" << endl << endl;
    if(locations.size() < 1){
        cout << endl << setfill(' ') << setw(48) << "The file is empty :(" << endl << endl;
    } else {
        for(int i = 0; i < locations.size(); i++){
            Location temp = locations.at(i);
            cout << setfill(' ') << setw(31) << "Location number: " << i+1 << endl;
            cout <<  "\t\t\t " << temp << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl;
        }

        string input;
        cout << setfill(' ') << setw(43) << "Choose a location to remove: ";
        cin >> input;
        
        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), locations.size())){
            int intInput = stoi(input);
            
            bizniz.removeLocation(locations, intInput);
            cout << endl << setw(31) << "Location removed!" << endl << endl;
        }
    }
}


void AdminUI::displaySideMenu(){
    char input = '\0';
    while(input != 'b'){
        cout << setfill(CHARFORSETFILL) << setw(32) << "-" << "    Sides    " << setfill(CHARFORSETFILL) << setw(31) << "-" << endl << endl;
        cout << setfill(' ') << setw(20) << "1: " << "List sides" << endl;
        uiItemSeparator();
        cout << setw(20) << "2: " << "Change a side" << endl;
        uiItemSeparator();
        cout << setw(20) << "3: " << "Add a side" << endl;
        uiItemSeparator();
        cout << setw(20) << "4: " << "Remove a side" << endl;
        uiItemSeparator();
        cout << setw(20) << "b: " << "back" << endl;
        uiItemSeparator();
        cin >> input;
        cout << endl;

        if(input == '1'){
            magic.clearScreen();
            displayAllSides();
        }
        else if(input == '2'){
            magic.clearScreen();
            try {
                changeSide();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidPriceException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
            
        }
        else if(input == '3'){
            magic.clearScreen();
            try {
                addSide();
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidPriceException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
        else if(input == '4'){
            magic.clearScreen();
            try {
                removeSide();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
    }
}


void AdminUI::displayAllSides(){
    
    vector<Side> sides = bizniz.getVectorOfSides();
    
    cout << endl << setfill(CHARFORSETFILL)<< setw(26) << "-" << "    List of all sides    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(sides.size() < 1){
          cout << endl << setfill(' ') << setw(48) << "The file is empty :("  << endl;
    }
    else {
        for (int i = 0; i < sides.size(); i++) {
            
            Side temp = sides.at(i);
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }
        
    }
    cout << endl;
}


void AdminUI::addSide(){
    
    cout << setfill(CHARFORSETFILL) << setw(27) << "-" <<  "    Adding a side!    " << setfill(CHARFORSETFILL) << setw(27) << "-" << endl << endl;
    cout << setfill(' ') << setw(SIZEOFADDTOPPINGSPACES-4) << "Enter side name (Max " << MAXCHARINSIDENAME-1 << " letters): ";
    string name;
    cin.ignore();
    getline(cin, name);
    cout << setw(30) << "Enter price: ";
    string price;
    cin >> price;
    
    if(bizniz.isValidName(name) && bizniz.isPriceDigit(price) && bizniz.isValidNameLength(name, MAXCHARINSIDENAME)){
       
        int intPrice = stoi(price);
        char tempName[MAXCHARINSIDENAME];
        strcpy(tempName, name.c_str());
        Side temp(tempName, intPrice);
        bizniz.addSide(temp);
        cout << endl << setw(28) << "Side added!" << endl << endl;
    }
}


void AdminUI::changeSide(){

    vector<Side> sides = bizniz.getVectorOfSides();
    cout << endl;
    cout << endl << setfill(CHARFORSETFILL)<< setw(26) << "-" << "    List of all sides    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(sides.size() < 1){
        cout << endl << setfill(' ') << setw(48) << "The file is empty :("  << endl;
    } else {
        for(int i = 0; i < sides.size(); i++){
            Side temp = sides.at(i);
            cout << setfill(' ') << setw(27) << "Side number: " << i+1 << endl;
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl;
        }
        string input;
        cout << setfill(' ') << setw(39) << "Choose a side to change: ";
        cin >> input;

        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), sides.size())){
        
            int intInput = stoi(input);
            
            for(int i = 0; i < sides.size(); i++){
                if(intInput == i+1){
                    cout << setw(35) << "Enter side name (Max " << MAXCHARINSIDENAME-1 << " letters): ";
                    string name;
                    cin.ignore();
                    getline(cin, name);
                    cout << setw(27) << "Enter price: ";
                    string price;
                    cin >> price;
                    
                    if(bizniz.isValidName(name) && bizniz.isPriceDigit(price) && bizniz.isValidNameLength(name, MAXCHARINSIDENAME)){
                        int intPrice = stoi(price);
                        char tempName[MAXCHARINSIDENAME];
                        strcpy(tempName, name.c_str());
                        Side temp(tempName, intPrice);
                        sides.at(i) = temp;
                        cout << endl << setw(27) << "Side changed!" << endl << endl;
                    }
                }
            }
            bizniz.storeVectorOfSides(sides);
        }
    }
}


void AdminUI::removeSide(){
    
    vector<Side> sides = bizniz.getVectorOfSides();
    cout << endl;
    cout << endl << setfill(CHARFORSETFILL)<< setw(26) << "-" << "    List of all sides    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(sides.size() < 1){
        cout << endl << "The file is empty :(" << endl << endl;
    } else {
        for(int i = 0; i < sides.size(); i++){
            Side temp = sides.at(i);
            cout << setfill(' ') << setw(27) << "Side number: " << i+1 << endl;
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl;
        }

        string input;
        cout << endl << setfill(' ') << setw(39) << "Choose a side to remove: ";
        cin >> input;

        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), sides.size())){
        
            int intInput = stoi(input);
            
            
            bizniz.removeSide(sides, intInput);
            cout << endl << setw(27) << "Side removed!" << endl << endl;
        }
    }
}


void AdminUI::displayDrinkMenu(){
    char input = '\0';
    while(input != 'b'){
        cout << setfill(CHARFORSETFILL) << setw(32) << "-" << "    Drinks    " << setfill(CHARFORSETFILL) << setw(31) << "-" << endl << endl;
        cout << setfill(' ') << setw(20) << "1: " << "List drinks" << endl;
        uiItemSeparator();
        cout << setw(20) << "2: " << "Change a drink" << endl;
        uiItemSeparator();
        cout << setw(20) << "3: " << "Add a drink" << endl;
        uiItemSeparator();
        cout << setw(20) << "4: " << "Remove a drink" << endl;
        uiItemSeparator();
        cout << setw(20) << "b: " << "back" << endl;
        uiItemSeparator();
        cin >> input;
        cout << endl;

        if(input == '1'){
            magic.clearScreen();
            displayAllDrinks();
        }
        else if(input == '2'){
            magic.clearScreen();
            try {
                changeDrink();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidPriceException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
        else if(input == '3'){
            magic.clearScreen();
            try {
                addDrink();
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidPriceException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
        else if(input == '4'){
            magic.clearScreen();
            try {
                removeDrink();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
    }
}

void AdminUI::displayAllDrinks(){
    
    vector<Drink> drinks = bizniz.getVectorOfDrinks();
    
    cout << endl << setfill(CHARFORSETFILL)<< setw(25) << "-" << "    List of all drinks    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(drinks.size() < 1){
        cout << endl << setw(48) << "The file is empty :("  << endl;
    }
    else {
        for (int i = 0; i < drinks.size(); i++) {
            Drink temp = drinks.at(i);
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }
    }
    cout << endl;
}

void AdminUI::changeDrink(){
    
    vector<Drink> drinks = bizniz.getVectorOfDrinks();
    
    cout << endl << setfill(CHARFORSETFILL)<< setw(25) << "-" << "    List of all drinks    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(drinks.size() < 1){
        cout << endl << setfill(' ') << setw(48) << "The file is empty :("  << endl;
    } else {
        for(int i = 0; i < drinks.size(); i++){
            Drink temp = drinks.at(i);
            cout << setfill(' ') << setw(28) << "Drink number: " << i+1 << endl;
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }
        string input;
        cout << setfill(' ') << setw(40) << "Choose a drink to change: ";
        cin >> input;
        
        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), drinks.size())){
            
            int intInput = stoi(input);
            
            for(int i = 0; i < drinks.size(); i++){
                if(intInput == i+1){
                    cout << setw(36) << "Enter drink name (Max " << MAXCHARINDRINKNAME-1 << " letters): ";
                    string name;
                    cin.ignore();
                    getline(cin, name);
                    cout << setw(27) << "Enter price: ";
                    string price;
                    cin >> price;
                    
                    if(bizniz.isValidName(name) && bizniz.isPriceDigit(price) && bizniz.isValidNameLength(name, MAXCHARINDRINKNAME)){
                        int intPrice = stoi(price);
                        char tempName[MAXCHARINDRINKNAME];
                        strcpy(tempName, name.c_str());
                        Drink temp(tempName, intPrice);
                        drinks.at(i) = temp;
                        cout << endl << setw(28) << "Drink changed!" << endl << endl;
                    }
                }
            }
            bizniz.storeVectorOfDrinks(drinks);
        }
    }
}

void AdminUI::addDrink(){
    
    
    cout << setfill(CHARFORSETFILL) << setw(27) << "-" <<  "    Adding a Drink!    " << setfill(CHARFORSETFILL) << setw(26) << "-" << endl << endl;
    cout << setfill(' ') << setw(SIZEOFADDTOPPINGSPACES-3) << "Enter drink name (Max " << MAXCHARINDRINKNAME-1 << " letters): ";
    string name;
    cin.ignore();
    getline(cin, name);
    cout << setw(30) << "Enter price: ";
    string price;
    cin >> price;
    
    if(bizniz.isValidName(name) && bizniz.isPriceDigit(price) && bizniz.isValidNameLength(name, MAXCHARINDRINKNAME)){
        
        int intPrice = stoi(price);
        char tempName[MAXCHARINDRINKNAME];
        strcpy(tempName, name.c_str());
        Drink temp(tempName, intPrice);
        bizniz.addDrink(temp);
        cout << endl << setw(29) << "Drink added!" << endl << endl;
    }
}


void AdminUI::removeDrink(){
    
    vector<Drink> drinks = bizniz.getVectorOfDrinks();

    cout << endl << setfill(CHARFORSETFILL)<< setw(25) << "-" << "    List of all drinks    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(drinks.size() < 1){
        cout << endl << setfill(' ') << setw(48) << "The file is empty :("  << endl;
    } else {
        for(int i = 0; i < drinks.size(); i++){
            Drink temp = drinks.at(i);
            cout << setfill(' ') << setw(28) << "Drink number: " << i+1 << endl;
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }
        
        string input;
        cout << endl << setfill(' ') << setw(40) << "Choose a drink to remove: ";
        cin >> input;
        
        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), drinks.size())){
            
            int intInput = stoi(input);
            
            bizniz.removeDrink(drinks, intInput);
            cout << endl << setw(28) << "Drink removed!" << endl << endl;
        }
    }
}



void AdminUI::displaySizeMenu(){
    char input = '\0';
    while(input != 'b'){
        cout << setfill(CHARFORSETFILL) << setw(31) << "-" << "    Sizes    " << setfill(CHARFORSETFILL) << setw(31) << "-" << endl << endl;
        cout << setfill(' ') << setw(20) << "1: " << "List sizes" << endl;
        uiItemSeparator();
        cout << setw(20) << "2: " << "Change a size" << endl;
        uiItemSeparator();
        cout << setw(20) << "3: " << "Add a size" << endl;
        uiItemSeparator();
        cout << setw(20) << "4: " << "Remove a size" << endl;
        uiItemSeparator();
        cout << setw(20) << "b: " << "back" << endl;
        uiItemSeparator();
        cin >> input;
        cout << endl;

        if(input == '1'){
            magic.clearScreen();
            displayAllSizes();
        }
        else if(input == '2'){
            magic.clearScreen();
            try {
                changeSize();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidPriceException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
        else if(input == '3'){
            magic.clearScreen();
            try {
                addSize();
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidPriceException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
        else if(input == '4'){
            magic.clearScreen();
            try {
                removeSize();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
    }
}

void AdminUI::displayAllSizes(){
    
    vector<Size> sizes = bizniz.getVectorOfSizes();
    cout << endl << setfill(CHARFORSETFILL)<< setw(26) << "-" << "    List of all sizes    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(sizes.size() < 1){
        cout << endl << setw(48) << "The file is empty :("  << endl;
    } else {
        for (int i = 0; i < sizes.size(); i++) {
            Size temp = sizes.at(i);
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }
    }
    cout << endl;
}


void AdminUI::changeSize(){
    
    vector<Size> sizes = bizniz.getVectorOfSizes();
    
    cout << endl << setfill(CHARFORSETFILL)<< setw(26) << "-" << "    List of all sizes    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(sizes.size() < 1){
        cout << endl << setfill(' ') << setw(48) << "The file is empty :("  << endl;
    } else {
        for(int i = 0; i < sizes.size(); i++){
            Size temp = sizes.at(i);
            cout << setfill(' ') << setw(27) << "Size number: " << i+1 << endl;
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }
        
        string input;
        cout << setfill(' ') << setw(39) << "Choose a size to change: ";
        cin >> input;
        
        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), sizes.size())){
            
            int intInput = stoi(input);
            
            for(int i = 0; i < sizes.size(); i++){
                if(intInput == i+1){
                    cout << setw(35) << "Enter size name (Max " << MAXCHARINSIZENAME-2 << " letters): ";
                    string name;
                    cin.ignore();
                    getline(cin, name);
                    cout << setw(27) << "Enter price: ";
                    string price;
                    cin >> price;
                    
                    if(bizniz.isValidName(name) && bizniz.isPriceDigit(price) && bizniz.isValidNameLength(name, MAXCHARINSIZENAME-1)){
                        int intPrice = stoi(price);
                        char tempName[MAXCHARINSIZENAME];
                        strcpy(tempName, name.c_str());
                        Size temp(tempName, intPrice);
                        sizes.at(i) = temp;
                        cout << endl << setw(27) << "Size changed!" << endl << endl;
                    }
                }
            }
            bizniz.storeVectorOfSizes(sizes);
        }
    }
}


void AdminUI::addSize(){

    cout << setfill(CHARFORSETFILL) << setw(26) << "-" <<  "    Adding a size!    " << setfill(CHARFORSETFILL) << setw(26) << "-" << endl << endl;
    cout << setfill(' ') << setw(SIZEOFADDTOPPINGSPACES-4) << "Enter size name (Max " << MAXCHARINSIZENAME-2 << " letters): ";
    string name;
    cin.ignore();
    getline(cin, name);
    cout << setw(30) << "Enter price: ";
    string price;
    cin >> price;
    
    if(bizniz.isValidName(name) && bizniz.isPriceDigit(price) && bizniz.isValidNameLength(name, MAXCHARINSIZENAME-1)){
        
        int intPrice = stoi(price);
        char tempName[MAXCHARINSIZENAME];
        strcpy(tempName, name.c_str());
        Size temp(tempName, intPrice);
        bizniz.addSize(temp);
        cout << endl << setw(28) << "Size added!" << endl << endl;
    }
}


void AdminUI::removeSize(){
    
    vector<Size> sizes = bizniz.getVectorOfSizes();
    
    cout << endl << setfill(CHARFORSETFILL)<< setw(26) << "-" << "    List of all sizes    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(sizes.size() < 1){
        cout << endl << setfill(' ') << setw(48) << "The file is empty :("  << endl;
    } else {
        for(int i = 0; i < sizes.size(); i++){
            Size temp = sizes.at(i);
            cout << setfill(' ') << setw(27) << "Size number: " << i+1 << endl;
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }

        
        string input;
        cout << setfill(' ') << setw(39) << "Choose a size to remove: ";
        cin >> input;
        
        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), sizes.size())){
            
            int intInput = stoi(input);
            
            bizniz.removeSize(sizes, intInput);
            cout << endl << setw(27) << "Size removed!" << endl << endl;
        }
    }
}


void AdminUI::displayBaseMenu(){
    char input = '\0';
    while(input != 'b'){
        cout << setfill(CHARFORSETFILL) << setw(31) << "-" << "    Bases    " << setfill(CHARFORSETFILL) << setw(31) << "-" << endl << endl;
        cout << setfill(' ') << setw(20) << "1: " << "List bases" << endl;
        uiItemSeparator();
        cout << setw(20) << "2: " << "Change a base" << endl;
        uiItemSeparator();
        cout << setw(20) << "3: " << "Add a base" << endl;
        uiItemSeparator();
        cout << setw(20) << "4: " << "Remove a base" << endl;
        uiItemSeparator();
        cout << setw(20) << "b: " << "back" << endl;
        uiItemSeparator();
        cin >> input;
        cout << endl;

        if(input == '1'){
            magic.clearScreen();
            displayAllBases();
        }
        else if(input == '2'){
            magic.clearScreen();
            try {
                changeBase();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidPriceException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
        }
        else if(input == '3'){
            magic.clearScreen();
            try {
                addBase();
            } catch (InvalidNameException e) {
                cout << endl << e.getMessage() << endl << endl;
            } catch (InvalidPriceException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
            
        }
        else if(input == '4'){
            magic.clearScreen();
            try {
                removeBase();
            } catch (InvalidInputException e) {
                cout << endl << e.getMessage() << endl << endl;
            }
            
        }
    }
}
void AdminUI::displayAllBases(){
    
    vector<Base> bases = bizniz.getVectorOfBases();
    
    cout << endl << setfill(CHARFORSETFILL)<< setw(26) << "-" << "    List of all bases    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    if(bases.size() < 1){
        cout << endl << setw(48) << "The file is empty :("  << endl;
    } else {
        for (unsigned int i = 0; i < bases.size(); i++) {
            Base temp = bases.at(i);
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }
    }
    cout << endl;
}

void AdminUI::changeBase(){
    
    vector<Base> bases = bizniz.getVectorOfBases();
    
    cout << endl << setfill(CHARFORSETFILL)<< setw(26) << "-" << "    List of all sizes    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(bases.size() < 1){
        cout << endl << setfill(' ') << setw(48) << "The file is empty :("  << endl;
    } else {
        for(int i = 0; i < bases.size(); i++){
            Base temp = bases.at(i);
            cout << setfill(' ') << setw(27) << "Base number: " << i+1 << endl;
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }
        
        string input;
        cout << setfill(' ') << setw(39) << "Choose a base to change: ";
        cin >> input;
        
        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), bases.size())){
            
            int intInput = stoi(input);
            
            for(int i = 0; i < bases.size(); i++){
                if(intInput == i+1){
                    cout << setw(35) << "Enter base name (Max " << MAXCHARINBASENAME-2 << " letters): ";
                    string name;
                    cin.ignore();
                    getline(cin, name);
                    cout << setw(27) << "Enter price: ";
                    string price;
                    cin >> price;
                    
                    if(bizniz.isValidName(name) && bizniz.isPriceDigit(price) && bizniz.isValidNameLength(name, MAXCHARINBASENAME-1)){
                        int intPrice = stoi(price);
                        char tempName[MAXCHARINBASENAME];
                        strcpy(tempName, name.c_str());
                        Base temp(tempName, intPrice);
                        bases.at(i) = temp;
                        cout << endl << setw(27) << "Base changed!" << endl << endl;
                    }
                }
            }
            bizniz.storeVectorOfBases(bases);
        }
    }
}

void AdminUI::addBase(){
    
    cout << setfill(CHARFORSETFILL) << setw(26) << "-" <<  "    Adding a base!    " << setfill(CHARFORSETFILL) << setw(26) << "-" << endl << endl;
    cout << setfill(' ') << setw(SIZEOFADDTOPPINGSPACES-4) << "Enter base name (Max " << MAXCHARINBASENAME-2 << " letters): ";
    string name;
    cin.ignore();
    getline(cin, name);
    cout << setw(30) << "Enter price: ";
    string price;
    cin >> price;
    
    if(bizniz.isValidName(name) && bizniz.isPriceDigit(price) && bizniz.isValidNameLength(name, MAXCHARINBASENAME-1)){
        
        int intPrice = stoi(price);
        char tempName[MAXCHARINBASENAME];
        strcpy(tempName, name.c_str());
        Base temp(tempName, intPrice);
        bizniz.addBase(temp);
        cout << endl << setw(28) << "Base added!" << endl << endl;
    }
}

void AdminUI::removeBase(){
    
    vector<Base> bases = bizniz.getVectorOfBases();
    cout << endl;
    cout << endl << setfill(CHARFORSETFILL)<< setw(26) << "-" << "    List of all bases    " << setfill(CHARFORSETFILL) << setw(25) << "-" << endl << endl;
    cout << setfill(' ') << setw(58) << "Price" << endl;
    cout << setw(58) << "-----" << endl;
    
    if(bases.size() < 1){
        cout << endl << setw(48) << "The file is empty :("  << endl;
    } else {
        for(int i = 0; i < bases.size(); i++){
            Base temp = bases.at(i);
            cout << setfill(' ') << setw(27) << "Base number: " << i+1 << endl;
            cout << setfill(' ') << setw(14) << " " << setw(19) << left << temp.getName() << setw(24) << setfill(' ') << right << temp.getPrice() << endl;
            cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl << endl;
        }
        cout << endl;

        string input;
        cout << setfill(' ') << setw(39) << "Choose a base to remove: ";
        cin >> input;
        
        if(bizniz.isInputDigit(input) && bizniz.isValidInput(stoi(input), bases.size())){
            
            int intInput = stoi(input);
            
            bizniz.removeBase(bases, intInput);
            cout << endl << setw(27) << "Base removed!" << endl << endl;
        }
    }
}

void AdminUI::uiItemSeparator () {
    cout << setw(17) << " " << setfill(CHARFORSETFILL) << setw(SIZEOFSETW-41) << "-" << endl << endl;
    cout << setfill(' ');
}

void AdminUI::locationUIItemSeperator(){
    cout << setw(14) << " " << setfill(CHARFORSETFILL) << setw(43) << "-" << endl;
    cout << setfill(' ');
}

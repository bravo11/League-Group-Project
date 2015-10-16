//  Dalton Rick, Nathan Foster, Kush Patel, Desmond Lee, Kurtis Hoang
//
//  CIS 22C
//
//  Group Project - Leaugue of Legends Character engine
//
//  main.cpp

#include "List.h"
#include "Random.h"
#include <fstream>

//======================================================= Local Function to main() Driver

// Must Run at Start
void getData(List<Hero>* Champions, List<Equipment>* Inventory);

// Menus
char mainMenu();
char championHallMenu();
char searchMenu();
char attributeMenu();
char equipmentRoomMenu();

//Switch case Functions
void addChampion(List<Hero>* Champions);
void print_to_file(List<Hero> Champions);
void search(List<Hero>* Champions, List<Equipment>* Inventory, bool remove, char typeSwitch);
void equipChampion(List<Hero>* Champions, List<Equipment> Inventory);
void dequipChampion(List<Hero>* Champions);
void equipmentRoom(List<Hero>* Champions, List<Equipment>* Inventory);
void championHall(List<Hero>* Champions, List<Equipment>* Inventory);

//Other functions
void battle(List<Hero>* hero);

///////////////////////////////////////////////////////////  - Main Test Driver
int main(int argc, const char * argv[]) {
    
    //creating a new list object L
    
    List<Hero> Champions; List<Equipment> Inventory; getData(&Champions, &Inventory); char choice;
	
    
//Main Menu
    
    while ((choice = mainMenu()) && choice != 'Q') {
        switch (choice) {
            case 'C':
                championHall(&Champions, &Inventory);
                break;
                
            case 'E':
                equipmentRoom(&Champions, &Inventory);
                break;
                
            default:
                cout << endl << choice << " is not a valid choice!\n";
                break;
        }
    }

   
// Menu should start here:
    
    
    
    
    
    
    
/* /////////////////////////////////////// Test Case:
    Champions.print();
    
    addChampion(&Champions);
    
    Champions.print();
        
    print_to_file(Champions);
    
*/
    
//======================================================= Save any New Champions or data to file before exit
    print_to_file(Champions);
    
    return 0;
}
//======================================================= getData()
void getData(List<Hero>* Champions, List<Equipment>* Inventory){
    
    Hero current; Weapon weapon; Armor armor; Equipment tempEquip;
    string tempString; int tempInt; double tempDouble; //char tempChar;
    ifstream inFile;

    inFile.open("Champions.txt");
    if (inFile.fail()) {
        cout << "Error! Champions data not found!" << endl;
        return;
    }
    
        while (!inFile.eof()) {
            inFile >> tempString;
            current.setName(tempString);
            inFile >> tempInt;
            current.setHealth(tempInt);
            inFile >> tempInt;
            current.setMana(tempInt);
            inFile >> tempInt;
            current.setAttackRange(tempInt);
            inFile >> tempInt;
            current.setAttackDamage(tempInt);
            inFile >> tempDouble;
            current.setAttackSpeed(tempDouble);
            inFile >> tempDouble;
            current.setarmor(tempDouble);
            inFile >> tempDouble;
            current.setMagicResistance(tempDouble);
            inFile >> tempInt;
            current.setMovementSpeed(tempInt);
            //current.zeroEquippedCount();
            Champions->push_back(current);
            inFile.ignore();
        }//While Loop END
    
    
    inFile.close();
    
    
    inFile.open("Inventory.txt");
    if(inFile.fail()){
        cout << "Error! Inventory Data not Found!" << endl;
        return;
    }

        while (!inFile.eof()) {
            inFile >> tempString;
            
            if (tempString == "Armor") {
                
                inFile >> tempDouble;
                armor.setArmorBoost(tempDouble);
                inFile >> tempInt;
                armor.setHealthBoost(tempInt);
                inFile >> tempInt;
                armor.setManaBoost(tempInt);
                inFile >> tempDouble;
                armor.setMagicResistanceBoost(tempDouble);
                inFile.ignore();
                getline(inFile, tempString);
                tempEquip.setName(tempString);
                tempEquip.setArmor(armor);
                Inventory->push_back(tempEquip);
            }
            else{
                
                inFile >> tempInt;
                weapon.setAttackDamageBoost(tempInt);
                inFile >> tempDouble;
                weapon.setattackSpeedBoost(tempDouble);
                inFile.ignore();
                getline(inFile, tempString);
                tempEquip.setName(tempString);
                tempEquip.setWeapon(weapon);
                Inventory->push_back(tempEquip);
            }
        
        }
        
    inFile.close();
    
    
}// getData Function END

//======================================================= mainMenu()
char mainMenu(){
    char choice;
    
    cout << endl;
    cout << "\t\t\t\t ** Welcome to the Main Menu **\n\nPlease choose from the following:\n\n";
    
    cout << "\t C to enter the Champions Lounge\n"
    << "\t E to enter the Equipment room\n"
    << "\t Q to exit program";
    
    
    cout << "\n\nChoice: "; cin >> choice;
    return toupper(choice);
    
    return toupper(choice);
}
//======================================================= championHallMenu()
char championHallMenu(){
    char choice = 'E';
    cout << endl;
    cout << "\t\t\t\t ** Welcome to the Champions Lounge **\n\nPlease choose from the following:\n\n";
    
    cout << "\t A to add new champion\n"
	<< "\t B to go to battle\n"
    << "\t S to enter search menu\n"
    << "\t P to print champion list\n"
    << "\t R to remove a champion\n"
    << "\t E to exit the Lounge";
    
    
    cout << "\n\nChoice: "; cin >> choice;
    return toupper(choice);
}// mainMenu() function END

//======================================================= searchMenu()
char searchMenu(){

    char choice = 'E';
    cout << endl;
    cout << "\t\t\t\t\t *** Search Menu ***\n\nPlease choose from the following:\n\n";
    
        cout << "\t N to search by name\n"
        << "\t H to search by hash number\n"
        << "\t A to search by Attribute\n"
        << "\t E to exit the search menu\n";
    
    cout << "\n\nChoice: ";
    cin >> choice;
    //cout << "------------------------------------------------------\n\n";
    
    return toupper(choice);
}
//======================================================= attributeMenu()
char attributeMenu(){
    char choice = 'E';
    cout << endl;
    cout << "\t\t\t\t *** Attribute Menu ***\n\nPlease choose from the following:\n\n";
    
    cout << "\t H to search by Health\n"
    << "\t M to search by Mana\n"
    << "\t R to search by Attack Range\n"
    << "\t D to search by Attack Damage\n"
    << "\t S to search by Attack Speed\n"
    << "\t A to search by Armor \n"
    << "\t G to search by Magic Resistance\n"
    << "\t Q to search by Movement Speed\n"
    << "\t E to exit the attribute menu";
    
    cout << "\n\nChoice: ";
    cin >> choice;
    
    return toupper(choice);
    
}
//======================================================= equipmentRoom()
char equipmentRoomMenu(){
    char choice = 'E';
    cout << endl;
    cout << "\t\t\t\t *** Equipment Room ***\n\nPlease choose from the following:\n\n";
    
    cout << "\t Q to equip a champion\n"
    << "\t D to remove champion equipment\n"
    << "\t A to create new item to inventory\n"
    << "\t S to search for equipment\n"
    << "\t R to destroy an item\n"
    << "\t P to print inventory List\n"
    //<< "\t N to search for champion by name and print current equipment\n"
    << "\t E to exit the Equipment Room\n";
    
    cout << "\n\nChoice: ";
    cin >> choice;
    
    
    return toupper(choice);
}

//======================================================= addChampion()
void addChampion(List<Hero>* Champions){
    Hero newChampion; string tempString;int tempInt; double tempDouble; int count; char choice;

	//creating random generator

    Random r;  // Example of how to generator a number between 1-200 -> r.DrawNumber(1, 200);
    
    cout << "Would you like to use the Random Stat Generator? (Y/N): ";
    cin >> choice;
    
    if (toupper(choice) == 'Y') {
        
        cout << "How many champions would you like to add?: ";
        cin >> count;
        
        for (int i=0; i < count; i++) {
            
            cout << "\nEnter champion's Name: ";
            cin >> tempString;
            newChampion.setName(tempString);
            
            newChampion.setHealth(r.DrawNumber(450, 650));
            cout << "Health: " << newChampion.getHealth() << endl;
            
            newChampion.setMana(r.DrawNumber(235, 365));
            cout << "Mana: " << newChampion.getMana() << endl;
            
            newChampion.setAttackRange(r.DrawNumber(150, 565));
            cout << "Attack Range: " << newChampion.getAttackRange() << endl;
            
            newChampion.setAttackDamage(r.DrawNumber(38, 60));
            cout << "Attack Damage: " << newChampion.getAttackDamage() << endl;
            
            newChampion.setAttackSpeed(r.DrawNumber(600, 800) * .001); // Convert the random generated int into a double.
            cout << "Attack Speed: " << newChampion.getAttackSpeed() << endl;
            
            newChampion.setarmor(r.DrawNumber(15, 35));
            cout << "Armor: " << newChampion.getarmor() << endl;
            
            newChampion.setMagicResistance(r.DrawNumber(25, 35));
            cout << "Magic Resistance: " << newChampion.getMagicResistance() << endl;
            
            newChampion.setMovementSpeed(r.DrawNumber(315, 375));
            cout << "Movement Speed: " << newChampion.getMovementSpeed() << endl;
            
            Champions->push_back(newChampion);
            
            cout << i+1 << " of " << count << " added." << endl;
            
        }// for loop END
    }// if statement END
    
    else{
        
        cout << "How many champions would you like to add?: ";
        cin >> count;
        
        for (int i=0; i < count; i++) {
            cout << "\nEnter champion's Name: ";
            
            cin >> tempString;
            newChampion.setName(tempString);
            
            cout << "\nEnter champion's Health: ";
            cin >> tempInt;
            newChampion.setHealth(tempInt);
    
            
            cout << "\nEner champion's Mana: ";
            cin >> tempInt;
            newChampion.setMana(tempInt);
            
            cout << "\nEnter champion's Damage Range: ";
            cin >> tempInt;
            newChampion.setAttackRange(tempInt);
            
            cout << "\nEnter champion's Attack Damage: ";
            cin >> tempInt;
            newChampion.setAttackDamage(tempInt);
            
            
            cout << "\nEnter champion's Attack Speed: ";
            cin >> tempDouble;
            newChampion.setAttackSpeed(tempDouble); // The random number generator only works with ints
           
            
            cout << "\nEnter champion's Armor: ";
            cin >> tempDouble;
            newChampion.setarmor(tempDouble);
            
            cout << "\nEnter champion's Magic Resistance: ";
            cin >> tempDouble;
            newChampion.setMagicResistance(tempDouble);
            
            cout << "\nEnter champion's Movement Speed: ";
            cin >> tempInt;
            newChampion.setMovementSpeed(tempInt);
            
            Champions->push_back(newChampion);
            
            cout << i+1 << " of " << count << " added." << endl;
        }// for Loop END

    }// else statement END
    return;
}// addChampion Function END

//======================================================= print_to_file()
void print_to_file(List<Hero> Champions){
   
    ofstream outFile; Hero tempChampion; int count = 0;
    ofstream pventoryOut; Equipment tempArray[6]; Weapon tempWeapon; Armor tempArmor;
    
    outFile.open("Champions.txt");
    if (outFile.fail()) {
        cout << "Error opening file! " << endl;
    }else
    {
        Champions.begin();
        
        while (!Champions.off_end()) {
            tempChampion = Champions.current();
            if (count != 0)
                outFile << endl;
            
            outFile << tempChampion.getName() << " " << tempChampion.getHealth() << " " << tempChampion.getMana() << " "
            << tempChampion.getAttackRange() << " " << tempChampion.getAttackDamage() << " " << tempChampion.getAttackSpeed()
            << " " << tempChampion.getarmor() << " " << tempChampion.getMagicResistance() << " " << tempChampion.getMovementSpeed();
            
            if (tempChampion.getEquippedCount() > 0) {
                
                pventoryOut.open("/Personal Inventory/" + tempChampion.getName() + ".txt");
                
                tempArray[6] = tempChampion.sendInventory();
                
                for (int i=0; i < tempChampion.getEquippedCount(); i++) {
                    if (tempArray[i].getType() == "Weapon") {
                        tempWeapon = tempArray[i].getWeapon();
                        pventoryOut << tempWeapon.getAttackDamage() << " " << tempWeapon.getAttackSpeed() << " " << tempArray[i].getName() << endl;
                    }
                }
            
                
            }
            Champions.scroll();
            count++;
        }//While Loop END
        
        cout << count << " Champions saved to file. " << endl;
    }// else statement END

    
}// print_to_file Function END
//======================================================= search()
void search(List<Hero>* Champions, List<Equipment>* Inventory, bool remove, char typeSwitch){
    char choice; string query; Hero temp; Equipment eTemp; int selected =0; int count =0; char response = 'N'; bool found = false; char attribute;
    int intMin, intMax; double doubleMin, doubleMax; int counted=0; int convert=0;
    
    while((choice = searchMenu()) && choice != 'E'){
        found = false;
        switch (choice) {
            case 'N':// Name
                
                if (typeSwitch == 'C') {
                    cout << "\nEnter champion name: ";
                    cin >> query; cout << endl;
                    
                    Champions->begin(); selected = 0;
                    
                    while (Champions->off_end() == false) {
                        
                        temp = Champions->current();
                        selected++;// this keeps track of where in the list we are. If query is found, selected is the spot in the list that remove function must delete;
                        if (temp.getName() == query) {
                            temp.print(); found = true;
                            //====================================== Remove option enabled
                            if (remove == true) {
                                cout << "\nWould you like to delete? (Y/N): ";
                                cin >> response;
                                if (toupper(response) == 'N') {
                                    selected=0;
                                }// if response == 'N' statement END
                            }// if (remove==true) statement END
                            break;
                            
                        }//if Statement END
                        
                        Champions->scroll();
                        
                    }// while loop END
                    if (found == false)
                        cout << "\nNo match found!" << endl;
                    
                    
                }else if(typeSwitch == 'I'){
                    cin.ignore();
                    cout << "\nEnter Item name: ";
                    
                    getline(cin, query); cout << endl;
                    
                    Inventory->begin(); selected = 0;
                    
                    while (Inventory->off_end() == false) {
                        
                        eTemp = Inventory->current();
                        selected++;// this keeps track of where in the list we are. If query is found, selected is the spot in the list that remove function must delete;
                        if (eTemp.getName() == query) {
                            eTemp.print(); found = true;
                            //====================================== Remove option enabled
                            if (remove == true) {
                                cout << "\nWould you like to delete? (Y/N): ";
                                cin >> response;
                                if (toupper(response) == 'N') {
                                    selected=0;
                                }// if response == 'N' statement END
                            }// if (remove==true) statement END
                            break;
                            
                        }//if Statement END
                        
                        Inventory->scroll();
                        
                    }// while loop END
                    if (found == false)
                        cout << "\nNo match found!" << endl;
                }
                
                break;// End Name
                
            case 'H':// Hash
                
                break;// END Hash
                
            case 'A':// Attribute
                Champions->begin(); selected = 0; counted =0;
                cout << "Select an attribute:\n";
                
                if (typeSwitch == 'C') {
                    
                    switch ((attribute = attributeMenu())) {
                            
                        case 'H':// Health
                            cout << "Enter Min Range: "; cin >> intMin;
                            cout << "\nEnter Max Range: "; cin >> intMax;
                            
                            while (Champions->off_end() == false) {
                                temp = Champions->current();
                                
                                if (temp.getHealth() >= intMin && temp.getHealth() <= intMax) { counted++;
                                    cout << endl << endl << counted << endl; temp.print(); found = true;
                                    
                                }//if Statement END
                                
                                Champions->scroll();
                                
                            }// while loop END
                            
                            //====================================== Remove option enabled
                            if (remove == true && found == true) {
                                cout << "\nWhich you like to delete? (Enter 0 to cancel): ";
                                cin >> convert;
                                if (convert == 0) {
                                    selected=0;
                                }else
                                {
                                    Champions->begin(); counted =0; selected =0;
                                    while (Champions->off_end() == false && counted < convert) {
                                        temp = Champions->current();
                                        selected++;
                                        if (temp.getHealth() >= intMin && temp.getHealth() <= intMax) {
                                            counted++;
                                        }//if Statement END
                                        
                                        Champions->scroll();
                                        
                                    }// while loop END
                                    
                                }
                            }// if (remove==true) statement END
                            
                            
                            if (found == false)
                                cout << "\nNo match found!" << endl;
                            break;// END Health
                            
                        case 'M':// Mana
                            cout << "Enter Min Range: "; cin >> intMin;
                            cout << "\nEnter Max Range: "; cin >> intMax;
                            
                            while (Champions->off_end() == false) {
                                temp = Champions->current();
                                if (temp.getMana() >= intMin && temp.getMana() <= intMax) {counted++;
                                    cout << endl << endl << counted << endl; temp.print(); found = true;
                                    
                                }//if Statement END
                                
                                Champions->scroll();
                                
                            }// while loop END
                            
                            //====================================== Remove option enabled
                            if (remove == true && found == true) {
                                cout << "\nWhich you like to delete? (Enter 0 to cancel): ";
                                cin >> convert;
                                if (convert == 0) {
                                    selected=0;
                                }else
                                {
                                    Champions->begin(); counted =0; selected =0;
                                    while (Champions->off_end() == false && counted < convert) {
                                        temp = Champions->current();
                                        selected++;
                                        if (temp.getMana() >= intMin && temp.getMana() <= intMax) {
                                            counted++;
                                        }//if Statement END
                                        
                                        Champions->scroll();
                                        
                                    }// while loop END
                                    
                                }
                            }// if (remove==true) statement END
                            
                            
                            if (found == false)
                                cout << "\nNo match found!" << endl;
                            
                            break;
                            
                        case 'R':// Attack Range
                            cout << "Enter Min Range: "; cin >> intMin;
                            cout << "\nEnter Max Range: "; cin >> intMax;
                            
                            while (Champions->off_end() == false) {
                                temp = Champions->current();
                                
                                if (temp.getAttackRange() >= intMin && temp.getAttackRange() <= intMax) {
                                    counted++;
                                    cout << endl << endl << counted << endl; temp.print(); found = true;
                                    
                                    
                                }//if Statement END
                                
                                Champions->scroll();
                                
                            }// while loop END
                            
                            //====================================== Remove option enabled
                            if (remove == true && found == true) {
                                cout << "\nWhich you like to delete? (Enter 0 to cancel): ";
                                cin >> convert;
                                if (convert == 0) {
                                    selected=0;
                                }else
                                {
                                    Champions->begin(); counted =0; selected =0;
                                    while (Champions->off_end() == false && counted < convert) {
                                        temp = Champions->current();
                                        selected++;
                                        if (temp.getAttackRange() >= intMin && temp.getAttackRange() <= intMax) {
                                            counted++;
                                        }//if Statement END
                                        
                                        Champions->scroll();
                                        
                                    }// while loop END
                                    
                                }
                            }// if (remove==true) statement END
                            
                            
                            if (found == false)
                                cout << "\nNo match found!" << endl;
                            break;
                            
                        case 'D':// Attack Damage
                            cout << "Enter Min Range: "; cin >> intMin;
                            cout << "\nEnter Max Range: "; cin >> intMax;
                            
                            while (Champions->off_end() == false) {
                                temp = Champions->current();
                                
                                if (temp.getAttackDamage() >= intMin && temp.getAttackDamage() <= intMax) {
                                    counted++;
                                    cout << endl << endl << counted << endl; temp.print(); found = true;
                                    
                                    
                                }//if Statement END
                                
                                Champions->scroll();
                                
                            }// while loop END
                            
                            //====================================== Remove option enabled
                            if (remove == true && found == true) {
                                cout << "\nWhich you like to delete? (Enter 0 to cancel): ";
                                cin >> convert;
                                if (convert == 0) {
                                    selected=0;
                                }else
                                {
                                    Champions->begin(); counted =0; selected =0;
                                    while (Champions->off_end() == false && counted < convert) {
                                        temp = Champions->current();
                                        selected++;
                                        if (temp.getHealth() >= intMin && temp.getHealth() <= intMax) {
                                            counted++;
                                        }//if Statement END
                                        
                                        Champions->scroll();
                                        
                                    }// while loop END
                                    
                                }
                            }// if (remove==true) statement END
                            
                            
                            if (found == false)
                                cout << "\nNo match found!" << endl;
                            break;
                            
                        case 'S':// Attack Speed
                            cout << "Enter Min Range: "; cin >> doubleMin;
                            cout << "\nEnter Max Range: "; cin >> doubleMax;
                            
                            while (Champions->off_end() == false) {
                                temp = Champions->current();
                                
                                if (temp.getAttackSpeed() >= doubleMin && temp.getAttackSpeed() <= doubleMax) {
                                    counted++;
                                    cout << endl << endl << counted << endl; temp.print(); found = true;
                                    
                                    
                                }//if Statement END
                                
                                Champions->scroll();
                                
                            }// while loop END
                            
                            //====================================== Remove option enabled
                            if (remove == true && found == true) {
                                cout << "\nWhich you like to delete? (Enter 0 to cancel): ";
                                cin >> convert;
                                if (convert == 0) {
                                    selected=0;
                                }else
                                {
                                    Champions->begin(); counted =0; selected =0;
                                    while (Champions->off_end() == false && counted < convert) {
                                        temp = Champions->current();
                                        selected++;
                                        if (temp.getAttackSpeed() >= doubleMin && temp.getAttackSpeed() <= doubleMax) {
                                            counted++;
                                        }//if Statement END
                                        
                                        Champions->scroll();
                                        
                                    }// while loop END
                                    
                                }
                            }// if (remove==true) statement END
                            
                            
                            if (found == false)
                                cout << "\nNo match found!" << endl;
                            break;
                            
                        case 'A':// armor
                            cout << "Enter Min Range: "; cin >> doubleMin;
                            cout << "\nEnter Max Range: "; cin >> doubleMax;
                            
                            while (Champions->off_end() == false) {
                                temp = Champions->current();
                                
                                if (temp.getarmor() >= doubleMin && temp.getarmor() <= doubleMax) {
                                    counted++;
                                    cout << endl << endl << counted << endl; temp.print(); found = true;
                                    
                                    
                                }//if Statement END
                                
                                Champions->scroll();
                                
                            }// while loop END
                            
                            //====================================== Remove option enabled
                            if (remove == true && found == true) {
                                cout << "\nWhich you like to delete? (Enter 0 to cancel): ";
                                cin >> convert;
                                if (convert == 0) {
                                    selected=0;
                                }else
                                {
                                    Champions->begin(); counted =0; selected =0;
                                    while (Champions->off_end() == false && counted < convert) {
                                        temp = Champions->current();
                                        selected++;
                                        if (temp.getarmor() >= doubleMin && temp.getarmor() <= doubleMax) {
                                            counted++;
                                        }//if Statement END
                                        
                                        Champions->scroll();
                                        
                                    }// while loop END
                                    
                                }
                            }// if (remove==true) statement END
                            
                            
                            if (found == false)
                                cout << "\nNo match found!" << endl;
                            break;
                            
                        case 'G':// Magic Resistance
                            cout << "Enter Min Range: "; cin >> doubleMin;
                            cout << "\nEnter Max Range: "; cin >> doubleMax;
                            
                            while (Champions->off_end() == false) {
                                temp = Champions->current();
                                
                                if (temp.getMagicResistance() >= doubleMin && temp.getMagicResistance() <= doubleMax) {
                                    counted++;
                                    cout << endl << endl << counted << endl; temp.print(); found = true;
                                    
                                }//if Statement END
                                
                                Champions->scroll();
                                
                            }// while loop END
                            
                            //====================================== Remove option enabled
                            if (remove == true && found == true) {
                                cout << "\nWhich you like to delete? (Enter 0 to cancel): ";
                                cin >> convert;
                                if (convert == 0) {
                                    selected=0;
                                }else
                                {
                                    Champions->begin(); counted =0; selected =0;
                                    while (Champions->off_end() == false && counted < convert) {
                                        temp = Champions->current();
                                        selected++;
                                        if (temp.getMagicResistance() >= doubleMin && temp.getMagicResistance() <= doubleMax) {
                                            counted++;
                                        }//if Statement END
                                        
                                        Champions->scroll();
                                        
                                    }// while loop END
                                    
                                }
                            }// if (remove==true) statement END
                            
                            
                            if (found == false)
                                cout << "\nNo match found!" << endl;
                            break;
                            
                        case 'Q':// Movement Speed
                            cout << "Enter Min Range: "; cin >> intMin;
                            cout << "\nEnter Max Range: "; cin >> intMax;
                            
                            while (Champions->off_end() == false) {
                                temp = Champions->current();
                                
                                if (temp.getMovementSpeed() >= intMin && temp.getMovementSpeed() <= intMax) {
                                    counted++;
                                    cout << endl << endl << counted << endl; temp.print(); found = true;
                                    
                                    
                                }//if Statement END
                                
                                Champions->scroll();
                                
                            }// while loop END
                            
                            //====================================== Remove option enabled
                            if (remove == true && found == true) {
                                cout << "\nWhich you like to delete? (Enter 0 to cancel): ";
                                cin >> convert;
                                if (convert == 0) {
                                    selected=0;
                                }else
                                {
                                    Champions->begin(); counted =0; selected =0;
                                    while (Champions->off_end() == false && counted < convert) {
                                        temp = Champions->current();
                                        selected++;
                                        if (temp.getMovementSpeed() >= intMin && temp.getMovementSpeed() <= intMax) {
                                            counted++;
                                        }//if Statement END
                                        
                                        Champions->scroll();
                                        
                                    }// while loop END
                                    
                                }
                            }// if (remove==true) statement END
                            
                            
                            if (found == false)
                                cout << "\nNo match found!" << endl;
                            break;
                            
                        default:
                            cout << endl << choice << " is not a valid choice!\n";
                            break;
                    }// End Attribute switch
                    
                    
                }else if (typeSwitch == 'I'){
                    
                    switch ((attribute = attributeMenu())) {
                            
                        case 'D'://attack damage Boost
                            
                            break;
                            
                        case 'Sp':// Attack Speed
                            
                            break;
                            
                        case 'H':// Health Boost
                            
                            break;
                            
                        case 'A':// Armor Boost
                            
                            break;
                            
                        case 'M': // Mana Boost
                            
                            break;
                            
                        case 'R': // Magic Resistance Boost
                            
                            break;
                            
                        default:
                            cout << endl << attribute << " is not a valid choice!\n";;
                            break;
                            
                            
                    }// switch inventory attribute
                    
                    
                }else
                    cout << "Invalid Seach choice\n";
                
                
                
        
                break;// End Attribute
                
            case 'E'://Exit
                return;
                
                break;
                
            default:
                cout << "\nNot a valid choice!\n";
                break;
        }
        //=========================================== Remove option enabled
        if (remove == true && selected != 0 && typeSwitch == 'C') {
            Champions->begin();
            for (count = 0; count < selected-1; count++){
                Champions->scroll();
            }// for statement END
            Champions->remove();
        }else if(remove == true && selected != 0 && typeSwitch == 'I'){
            Inventory->begin();
            for (count =0; count < selected-1; count++) {
                Inventory->scroll();
            }
            Inventory->remove();
        }
        
            }// while statement END
}
//======================================================= battle()
void battle(List<Hero>* Champions) {
	string selectedChampion; int selected; Hero temp; bool found = false;
	cout << "Enter the name of the champion you want to fight with: " << endl;
	cin >> selectedChampion;

	Champions->begin(); selected = 0;

	while (Champions->off_end() == false) {

		temp = Champions->current();
		selected++;// this keeps track of where in the list we are. If query is found, selected is the spot in the list that remove function must delete;
		if (temp.getName() == selectedChampion) {
			//temp.print();
			found = true;
		}
	}//end while
	if (found == true)
	{
		cout << "true" << endl;
	}
	else { cout << "false" << endl; }

}
//======================================================= EquipmentRoom()
void equipmentRoom(List<Hero>* Champions, List<Equipment>* Inventory){
    
    char choice; bool remove; char typeSwitch = 'I';
    
    while((choice = equipmentRoomMenu()) && choice != 'E'){
        
        switch (choice) {
                
            case 'Q':
                
                equipChampion(Champions, *Inventory);
                
                break;
                
            case 'D':
                
                dequipChampion(Champions);
                
                break;
                
            case 'R':
                remove = true;
                search(Champions, Inventory, remove, typeSwitch);
                
                break;
                
            case 'S'://Search equipment
                remove = false;
                search(Champions, Inventory, remove, typeSwitch);
                
                break;
                
            case 'P':
                
                Inventory->print();
                
                break;
                
            case 'N':
                
                break;
                
            case 'A':// add item
                
                break;
                
                
            default:
                cout << endl << choice << " is not a valid choice!\n";
            
                break;
                
        }// End Switch
        
    }// End While
    
    
}
//======================================================= Champion Hall
void championHall(List<Hero>* Champions, List<Equipment>* Inventory){
    char typeSwitch = 'C'; bool remove; char choice;
    
    while((choice = championHallMenu()) && choice != 'E'){
        
        switch (choice) {
            case 'A':
                addChampion(Champions);
                break;
            case 'B':
                battle(Champions);
                break;
            case 'R':
                remove = true; typeSwitch = 'C';
                search(Champions, Inventory, remove, typeSwitch);
                break;
                
            case 'S':
                remove = false; typeSwitch = 'C';
                search(Champions, Inventory, remove, typeSwitch);
                break;
                
            case 'P'://case 'C':
                Champions->print();
                break;
                
            
            default:
                cout << endl << choice << "is not a valid choice!\n";
                break;
        }
        
        
    }
}

//======================================================= equipChampion()
void equipChampion(List<Hero>* Champions, List<Equipment> Inventory){
    
    Equipment tempEquipment; int choice; Hero tempHero;
    
    Champions->print();
    
    cout << "\nEnter Champion to equip: ";
    cin >> choice;
    cout << endl << endl;
    Champions->begin();
    for (int i=0; i < choice-1; i++) {
        Champions->scroll();
    }

    
    Inventory.print();
    
    cout << "\nEnter item to equip: ";
    cin >> choice;
    cout << endl << endl;
    
    Inventory.begin();
    
    for(int i=0; i < choice-1; i++){
        Inventory.scroll();
    }
    
    tempEquipment = Equipment(Inventory.current());
    
   Champions->equipCurrent(tempEquipment);    
    
    
    
    
}
//======================================================= dequipChampion()
void dequipChampion(List<Hero>* Champions){
    
    Champions->print(); int choice=0; int count=0;
    
    cout << "\nEnter Champion Number: ";
    cin >> choice;
    cout << endl << endl;
    
    Champions->begin();
    for (int i=0; i < choice-1; i++) {
        Champions->scroll();
    }
    
    Champions->print1();
    
    cout << "\nEnter item to remove: ";
    cin >> count;
    cout << endl;
    
     Champions->dequipCurrent(count);
    
    
}

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdlib>
#include <fstream>

using namespace std;

const string PROPERTY_TYPE_APARTMENT = "Apartment";
const string PROPERTY_TYPE_HOUSE = "House";
const string PROPERTY_TYPE_LAND = "Land";


typedef struct Owner {
    int TelNumber;
    string Name;
} Owner;


class Property {
public:
    string Address;
    Owner owner;
    float price;
    float area; //m2
    bool Rent;

    virtual string getType() const {
        return "Property";
    }

    Property() {

    }


    Property(string address, Owner person, float p, float a, bool rent) {
        Address = address;
        owner.TelNumber = person.TelNumber;
        owner.Name = person.Name;
        price = p;
        area = a;
        Rent = rent;
    }

    void set_p() {
    string tempAddress;
    int tempTelNumber;
    string tempName;
    float tempPrice;
    float tempArea;
    string tempRentStr;
    bool tempRent;

    cout << "Enter Address: ";
    getline(cin >> ws, tempAddress); 
    Address = tempAddress;

    cout << "Enter Owner full name: ";
    getline(cin >> ws, tempName); 
    owner.Name = tempName;

    cout << "Enter Owner contact number: ";
    while (!(cin >> tempTelNumber)) {
        cout << "Invalid input. Please enter a valid contact number: ";
        cin.clear(); 
    }
    owner.TelNumber = tempTelNumber;
    
    cout << "Enter price: ";
    while (!(cin >> tempPrice)) {
        cout << "Invalid input. Please enter a valid price: ";
        cin.clear();
    }
    price = tempPrice;

    cout << "Enter property area size in m2: ";
    while (!(cin >> tempArea)) {
        cout << "Invalid input. Please enter a valid area size: ";
        cin.clear();
    }
    area = tempArea;

    cout << "Is the property available for rent? (true/false): ";
    while (!(cin >> tempRentStr) || (tempRentStr != "true" && tempRentStr != "false")) {
        cout << "Invalid input. Please enter 'true' or 'false': ";
        cin.clear();
    }
    tempRent = (tempRentStr == "true");
    Rent = tempRent;
}


    virtual void info() const {
        cout << "Address: " << Address << endl;
        cout << "Owner: " << owner.Name << endl;
        cout << "Contact: " << owner.TelNumber << endl;
        cout << "Price: " << price << "$" << endl;
        cout << "Area: " << area << " m^2" << endl;
        cout << "Available for " << (Rent ? "Rent" : "Sale") << endl;
    }
};


class Apartment : public Property {

    public:

    unsigned int Rooms;
    unsigned int floor;
    bool Elevator;

    Apartment() {

    }

    Apartment(string address, Owner person, float p, float a, bool rent, unsigned int roomCount, unsigned int floorNum, bool hasElevator)
    : Property(address, person, p, a, rent), Rooms(roomCount), floor(floorNum), Elevator(hasElevator) {}



    string getType() const override {

        return PROPERTY_TYPE_APARTMENT;
    }

    void set() {

        string tempStr;
        bool tmp;

        set_p();
        cout << "Enter number of rooms: ";
        cin >> Rooms;
        cout << "Enter floor number: ";
        cin >> floor;
        cout << "Does it have an elevator? (true or false): ";
        while (!(cin >> tempStr) || (tempStr != "true" && tempStr != "false")) {
        cout << "Invalid input. Please enter 'true' or 'false': ";
        cin.clear();
    }
    tmp = (tempStr == "true");
    Elevator = tmp;


    }

    void info() const override{
        Property::info();
        cout << "Rooms: " << Rooms << endl;
        cout << "Floor: " << floor << endl;
        cout << "Elevator: " << (Elevator ? "Yes" : "No") << endl;
    }


};


class House : public Property {
    public :

    unsigned int rooms;
    unsigned int floors;
    float gardenArea;


    House() {

    }

    House(string address, Owner person, float p, float a, bool rent, unsigned int roomCount, unsigned int floorCount, float area)
    : Property(address, person, p, a, rent), rooms(roomCount), floors(floorCount), gardenArea(area) {}


    string getType() const override {

        return PROPERTY_TYPE_HOUSE;
    }

    void set() {
        float tempArea;

        set_p();
        cout << "Enter number of rooms: ";
        cin >> rooms;
        cout << "Enter number of floors: ";
        cin >> floors;
        cout << "Enter garden size in m2: ";
        while (!(cin >> tempArea)) {
        cout << "Invalid input. Please enter a valid area size: ";
        cin.clear();
        }
        gardenArea = tempArea;

    }

    void info() const override{
        Property::info();
        cout << "Rooms: " << rooms << endl;
        cout << "Floors: " << floors << endl;
        cout << "Garden Area: " << gardenArea << endl;
    }

};


class Land : public Property {
    public :

    bool electricity;
    bool water;
    bool road;

    Land() {

    }

    Land(string address, Owner person, float p, float a, bool rent, bool hasElectr, bool hasWater, bool nearRoad)
    : Property(address, person, p, a, rent), electricity(hasElectr), water(hasWater), road(nearRoad) {}


    string getType() const override {

        return PROPERTY_TYPE_LAND;
    }

    
    void set() {
    string tempStr;
    bool tmp;

    set_p();
    cout << "Electricity ? (true or false): ";
    while (!(cin >> tempStr) || (tempStr != "true" && tempStr != "false")) {
        cout << "Invalid input. Please enter 'true' or 'false': ";
        cin.clear();
    }
    tmp = (tempStr == "true");
    electricity = tmp;

    cout << "Water source ? (true or false): ";
    while (!(cin >> tempStr) || (tempStr != "true" && tempStr != "false")) {
        cout << "Invalid input. Please enter 'true' or 'false': ";
        cin.clear();
    }
    tmp = (tempStr == "true");
    water = tmp;
    

    cout << "Near a road ?  (true or false): ";
    while (!(cin >> tempStr) || (tempStr != "true" && tempStr != "false")) {
        cout << "Invalid input. Please enter 'true' or 'false': ";
        cin.clear();
    }
    tmp = (tempStr == "true");
    road = tmp;

    }

    void info() const override{
        Property::info();
        cout << "Electricity: " << electricity << endl;
        cout << "Water: " << water << endl;
        cout << "Road nearby: " << road << endl;
    }


};


class Agency {
public:
    string Name;
    Property** Properties;
    unsigned int Properties_count;
    unsigned int capacity;

    Agency(string name) {
        Name = name;
        Properties = nullptr;
        Properties_count = 0;
        capacity = 0;
    }

    ~Agency() {
        for (unsigned int i = 0; i < Properties_count; ++i) {
            delete Properties[i];
        }
        delete[] Properties;
    }

    

    void add(Property* prop) {
        if (Properties_count >= capacity) {
            resize();
        }
        Properties[Properties_count] = prop;
        Properties_count++;
        cout << "Poperty added" << endl;
    }


    void remove(unsigned int index) {
    if (index >= Properties_count) {
        cout << "Invalid index." << endl;
        return;
    }
    delete Properties[index];

    for (unsigned int i = index; i < Properties_count - 1; ++i) {
        Properties[i] = Properties[i + 1];
    }
    Properties_count--;
    cout << "Property Deleted" << endl;
    }


    void resize() {
        unsigned int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        Property** newProperties = new Property*[newCapacity];
        for (unsigned int i = 0; i < Properties_count; ++i) {
            newProperties[i] = Properties[i];
        }   

        delete[] Properties;
        Properties = newProperties;
        capacity = newCapacity;
    }


    void show() {
        if (Properties_count == 0) {
            cout << "No properties available." << endl;
            return;
        }
        cout << " " << endl;
        for (unsigned int i = 0; i < Properties_count; ++i) {
            cout << "Property " << i + 1 << ":" << endl;
            cout << "Type: " << Properties[i]->getType() << endl;
            Properties[i]->info();
            cout << endl;
        }
    }

    void search(float p) {

        if (Properties_count == 0) {
            cout << "No properties available." << endl;
            return;
        }

        bool found = false;
        cout << "Properties within price range:" << endl;
        cout << "-------------------------------" << endl;

        for (unsigned int i = 0; i < Properties_count; ++i) {
            if (Properties[i]->price <= p) {
                cout << "Property " << i + 1 << ":" << endl;
                cout << "Type: " << Properties[i]->getType() << endl;
                Properties[i]->info();
                cout << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No properties found within the specified price range." << endl;
        }
    }
};


void showMainMenu() {
    cout << "MENU:" << endl;
    cout << "---------------" << endl;
    cout << "ADD        - 1" << endl;
    cout << "DELETE     - 2" << endl;
    cout << "SHOW       - 3" << endl;
    cout << "SEARCH     - 4" << endl;
    cout << "_______________" << endl;
    cout << "Press 'esc' to exit" << endl;
    cout << " " << endl;
}

void AddMenu() {
    cout << "ADD:" << endl;
    cout << "--------------" << endl;
    cout << "Apartment - 1" << endl;
    cout << "House     - 2" << endl;
    cout << "Land      - 3" << endl;
    cout << "______________" << endl;
    cout << "Press 'esc' to exit" << endl;
    cout << " " << endl;
}


void readFromFile(Agency& A) {
    ifstream inputFile("record.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            if (line == "Property:") {
                string type, address, ownerName, contactStr;
                int telNumber, rooms, floor;
                float price, area, gardenArea;
                bool rent, elevator, electricity, water, road;

                getline(inputFile, type); 
                getline(inputFile, address); 
                getline(inputFile, ownerName); 
                inputFile >> telNumber >> price >> area >> rent; 
                inputFile.ignore(); 
                
                if (type == "Apartment") {
                    inputFile >> rooms >> floor >> elevator; 
                    inputFile.ignore(); 
                    Owner owner = {telNumber, ownerName};
                    Apartment* apartment = new Apartment(address, owner, price, area, rent, rooms, floor, elevator);
                    A.add(apartment);
                }
                else if (type == "House") {
                    inputFile >> rooms >> floor >> gardenArea; 
                    inputFile.ignore();
                    Owner owner = {telNumber, ownerName};
                    House* house = new House(address, owner, price, area, rent, rooms, floor, gardenArea);
                    A.add(house);
                }
                else if (type == "Land") {
                    inputFile >> electricity >> water >> road;
                    inputFile.ignore(); 
                    Owner owner = {telNumber, ownerName};
                    Land* land = new Land(address, owner, price, area, rent, electricity, water, road);
                    A.add(land);
                }
            }
        }
        inputFile.close();
    }
}



void saveToFile(const Agency& A) {
    ofstream outputFile("record.txt");
    if (outputFile.is_open()) {
        for (unsigned int i = 0; i < A.Properties_count; ++i) {
            outputFile << "Property:" << endl;
            Property* prop = A.Properties[i];
            outputFile << prop->getType() << endl;
            outputFile << prop->Address << endl;
            outputFile << prop->owner.Name << endl;
            outputFile << prop->owner.TelNumber << endl;
            outputFile << prop->price << " " << prop->area << " " << prop->Rent << endl;
            if (typeid(*prop) == typeid(Apartment)) {
                Apartment* apartment = dynamic_cast<Apartment*>(prop);
                outputFile << apartment->Rooms << " " << apartment->floor << " " << apartment->Elevator << endl;
            }
            else if (typeid(*prop) == typeid(House)) {
                House* house = dynamic_cast<House*>(prop);
                outputFile << house->rooms << " " << house->floors << " " << house->gardenArea << endl;
            }
            else if (typeid(*prop) == typeid(Land)) {
                Land* land = dynamic_cast<Land*>(prop);
                outputFile << land->electricity << " " << land->water << " " << land->road << endl;
            }
        }
        outputFile.close();
        cout << "Data saved to record.txt successfully." << endl;
    } else {
        cout << "Unable to open record.txt for writing." << endl;
    }
}


int main() {
    //Owner person1 = {1234567890, "Ivan Ivanov"};
    //Property A("Street 1", person1, 200.015, 125, true);
    //Property A;
    Agency A("My Agency");
    readFromFile(A);
    char choice;

    do {
        system("clear"); 

        showMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                char addChoice;
                do {
                    system("clear"); 

                    AddMenu();
                    cout << "Enter your choice: ";
                    cin >> addChoice;
                    switch (addChoice) {
                        case '1': {
                            Apartment *newApartment = new Apartment();
                            newApartment->set();
                            A.add(newApartment);
                            break;
                        }
                        case '2': {
                            House *newHouse = new House();
                            newHouse->set();
                            A.add(newHouse);
                            break;
                        }
                        case '3': {
                            Land *newLand = new Land();
                            newLand->set();
                            A.add(newLand);
                            break;
                        }
                        case 27: 
                            break; 
                        default:
                            cout << "Invalid choice. Try again." << endl;
                            break;
                    }
                } while (addChoice != 27); 
                break;
            }
            case '2': {
                unsigned int index;
                bool deleted = false;

                do {
                    system("clear"); 

                    cout << "Delete Property:" << endl;
                    cout << "------------------" << endl;
                    cout << "Enter the index of the property ('esc' to return to main menu): ";
                    char input;
                    cin >> input;

                    if (input == 27) {
                        break;
                    }

                    index = input - '0'; 
                    index = index - 1;

                    if (index >= A.Properties_count) {
                        cout << "Invalid index. Please try again." << endl;
                    } else {
                        A.remove(index);
                        deleted = true;
                    }
                } while (!deleted);

                cout << "Press 'esc' to return to the main menu..." << endl;
                char anyKey;
                cin >> anyKey; 
                break;
            }
            case '3': {
                system("clear"); 
                cout << "Properties in " << A.Name << ":" << endl;
                A.show();
                cout << "Press 'esc' to return to the main menu..." << endl;
                char esc;
                do {
                    cin >> esc;
                } while (esc != 27); 
                break;
            }
            case '4': {
                bool search = false;

                do {
                    system("clear");

                    cout << "Search Property:" << endl;
                    cout << "------------------" << endl;
                    cout << "Enter max price ('esc' to return to main menu): ";

                    string input;
                    cin >> input;

                    if (input.size() == 1 && input[0] == 27) {
                        break;
                    }

                    float price;
                    try {
                        price = std::stof(input); 
                        A.search(price);
                        search = true;
                    } catch (const std::invalid_argument& e) {
                        cout << "Invalid input. Please enter a valid number or 'esc' to return to the main menu." << endl;
                        continue;
                    }

                } while (!search);

                cout << "Press any key to return to the main menu..." << endl;
                char anyKey;
                cin >> anyKey; 
                break;
            }
            case 27: 
                break; 
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    } while (choice != 27); 

    saveToFile(A);

    return 0;
}

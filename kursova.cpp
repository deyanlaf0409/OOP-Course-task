#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

const string PROPERTY_TYPE_APARTMENT = "Apartment";


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
    getline(cin >> ws, tempAddress); // Read input with spaces
    Address = tempAddress;

    cout << "Enter Owner full name: ";
    getline(cin >> ws, tempName); // Read input with spaces
    owner.Name = tempName;

    cout << "Enter Owner contact number: ";
    while (!(cin >> tempTelNumber)) {
        cout << "Invalid input. Please enter a valid contact number: ";
        cin.clear(); // Clear error flags
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

        delete[] Properties;
    }
    

    void add(Property* prop) {
        if (Properties_count >= capacity) {
            // Resize the array if needed
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
        // Move elements after the deleted one to fill the gap
        for (unsigned int i = index; i < Properties_count - 1; ++i) {
            Properties[i] = Properties[i + 1];
        }
        Properties_count--;
    }


    void resize() {
        // Double the capacity
        unsigned int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        Property** newProperties = new Property*[newCapacity];
        // Copy existing properties
        for (unsigned int i = 0; i < Properties_count; ++i) {
            newProperties[i] = Properties[i];
        }
        // Free the old array
        delete[] Properties;
        // Update properties and capacity
        Properties = newProperties;
        capacity = newCapacity;
    }



    void show() {
        if (Properties_count == 0) {
            cout << "No properties available." << endl;
            return;
        }
        cout << "Properties in " << Name << ":" << endl;
        for (unsigned int i = 0; i < Properties_count; ++i) {
            cout << "Property " << i + 1 << ":" << endl;
            cout << "Type: " << Properties[i]->getType() << endl;
            Properties[i]->info();
            cout << endl;
        }
    }
};

int main() {
    //Owner person1 = {1234567890, "Ivan Ivanov"};
    //Property A("Street 1", person1, 200.015, 125, true);
    //Property A;
    Apartment P;
    P.set();
    cout << "" << endl;

    Agency A("My Agency");
    A.add(&P);
    A.show();

    return 0;
}

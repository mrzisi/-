#ifndef VEHICLE_RENTAL_H
#define VEHICLE_RENTAL_H

#include <iostream>
#include <string>
#include <vector>


using namespace std;
//========================================================
class Vehicle {
protected:
    string make;
    string model;
    string color;
    int year;
    int maxSpeed;

public:
    Vehicle(string make, string model, string color, int year, int maxSpeed);
    virtual ~Vehicle() {}

    virtual void drive() = 0; 

    virtual void displayDetails() const {
        cout << "Make: " << make << ", Model: " << model
            << ", Color: " << color << ", Year: " << year
            << ", Max Speed: " << maxSpeed;
    }
};
//=============================================================
class InventoryItem {
public:
    Vehicle* vehicle;
    bool isRented;

public:
    InventoryItem(Vehicle* v) : vehicle(v), isRented(false) {}
    virtual ~InventoryItem() { delete vehicle; }

    virtual void displayDetails() const {
        vehicle->displayDetails();
    }

    virtual bool isAvailable() const = 0;
    virtual bool canBeSold() const = 0;
    virtual bool canBeRented() const = 0;

    virtual void requestSale() = 0;
    virtual void requestRental(int days) = 0;
    virtual void returnItem() = 0;
};
//================================================================
class Car : public Vehicle {
public:
    Car(string make, string model, string color, int year, int maxSpeed)
        : Vehicle(make, model, color, year, maxSpeed) {}

    void drive() override {
        for (int i = 0; i <= maxSpeed; i += 10) {
            cout << "Driving at " << i << " km/h" << endl;
        }
    }
};
//==================================================================
class Motorcycle : public Vehicle {
public:
    Motorcycle(string make, string model, string color, int year, int maxSpeed)
        : Vehicle(make, model, color, year, maxSpeed) {}

    void drive() override {
        for (int i = 0; i <= maxSpeed / 2; i += 10) {
            cout << "Riding carefully at " << i << " km/h" << endl;
        }
    }
};

//=================================================================
class Bicycle : public Vehicle {
public:
    Bicycle(string make, string model, string color, int year, int maxSpeed)
        : Vehicle(make, model, color, year, maxSpeed) {}

    void drive() override {
        for (int i = 0; i < maxSpeed; i++) {
            cout << "Pedaling... ";
        }
        cout << endl;
    }
};
//=================================================================
class ForSaleItem : public InventoryItem {
    double price;

public:
    ForSaleItem(Vehicle* v, double price) : InventoryItem(v), price(price) {}

    bool isAvailable() const override { return !isRented; }
    bool canBeSold() const override { return true; }
    bool canBeRented() const override { return false; }

    void requestSale() override {
        cout << "Item sold for $" << price << endl;
    }

    void requestRental(int) override {
        cout << "This item is not available for rental" << endl;
    }

    void returnItem() override {
        cout << "This item cannot be returned as it's for sale only" << endl;
    }

    void displayDetails() const override {
        InventoryItem::displayDetails();
        cout << ", Price: $" << price << " (For Sale)" << endl;
    }
};
//================================================================
class ForRentItem : public InventoryItem {
    double dailyRate;

public:
    ForRentItem(Vehicle* v, double dailyRate) : InventoryItem(v), dailyRate(dailyRate) {}

    bool isAvailable() const override { return !isRented; }
    bool canBeSold() const override { return false; }
    bool canBeRented() const override { return true; }

    void requestSale() override {
        cout << "This item is not available for sale" << endl;
    }

    void requestRental(int days) override {
        if (!isRented) {
            isRented = true;
            cout << "Item rented for " << days << " days. Total cost: $" << (days * dailyRate) << endl;
        }
        else {
            cout << "Item is already rented" << endl;
        }
    }

    void returnItem() override {
        if (isRented) {
            isRented = false;
            cout << "Item returned successfully" << endl;
        }
        else {
            cout << "Item was not rented" << endl;
        }
    }

    void displayDetails() const override {
        InventoryItem::displayDetails();
        cout << ", Daily Rate: $" << dailyRate << " (For Rent"
            << (isRented ? " - Currently Rented" : "") << ")" << endl;
    }
};
//=============================================================================
class RentalSystem {
    vector<unique_ptr<InventoryItem>> inventory;

public:
    void addItem(InventoryItem* item);
    void displayAllItems() const;
    void requestSale(int index);
    void requestRental(int index, int days);
    void returnItem(int index);
    void testDrive(int index);
};

#endif

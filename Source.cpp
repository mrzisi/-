#include "Header.h"


void RentalSystem::addItem(InventoryItem* item) {
    inventory.emplace_back(item);
}

void RentalSystem::displayAllItems() const {
    cout << "\n=== Inventory Items ===" << endl;
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << "[" << i << "] ";
        inventory[i]->displayDetails();
    }
}

void RentalSystem::requestSale(int index) {
    if (index >= 0 && index < inventory.size()) {
        if (inventory[index]->canBeSold()) {
            inventory[index]->requestSale();
            inventory.erase(inventory.begin() + index);
        }
        else {
            cout << "This item cannot be sold" << endl;
        }
    }
    else {
        cout << "Invalid item index" << endl;
    }
}

void RentalSystem::requestRental(int index, int days) {
    if (index >= 0 && index < inventory.size()) {
        if (inventory[index]->canBeRented()) {
            inventory[index]->requestRental(days);
        }
        else {
            cout << "This item cannot be rented" << endl;
        }
    }
    else {
        cout << "Invalid item index" << endl;
    }
}

void RentalSystem::returnItem(int index) {
    if (index >= 0 && index < inventory.size()) {
        inventory[index]->returnItem();
    }
    else {
        cout << "Invalid item index" << endl;
    }
}

void RentalSystem::testDrive(int index) {
    if (index >= 0 && index < inventory.size()) {
        dynamic_cast<Vehicle*>(inventory[index]->vehicle)->drive();
    }
    else {
        cout << "Invalid item index" << endl;
    }
}
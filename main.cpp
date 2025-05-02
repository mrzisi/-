#include "Header.h"

int main() {
    RentalSystem system;

    system.addItem(new ForSaleItem(
        new Car("BMW", "M3 GTR", "White and Blue", 2005, 250),
        45000.0
    ));

    system.addItem(new ForRentItem(
        new Motorcycle("Harley-Davidson", "Street 750", "Black", 2020, 180),
        75.0
    ));

    system.addItem(new ForRentItem(
        new Bicycle("Trek", "FX 2", "Red", 2021, 30),
        15.0
    ));

    system.addItem(new ForSaleItem(
        new Motorcycle("Yamaha", "YZF-R1", "Blue", 2019, 300),
        12000.0
    ));

    system.displayAllItems();

 
    cout << "\n=== Test Drive ===" << endl;
    system.testDrive(0); 
    system.testDrive(1); 
    system.testDrive(2);

    
    cout << "\n=== Rental Operations ===" << endl;
    system.requestRental(1, 5); 
    system.requestSale(1);      
    system.returnItem(1);       
    system.requestSale(1);      

    cout << "\n=== Sale Operations ===" << endl;
    system.requestSale(0);    
    system.displayAllItems();   

    return 0;
}
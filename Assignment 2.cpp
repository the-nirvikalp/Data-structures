#include <iostream>
#include <string>
using namespace std;

//---------------------------------------------
// 1. Inventory Item ADT
//---------------------------------------------
class InventoryItem {
private:
    int ItemID;          // Unique ID for each item
    string ItemName;     // Item name
    int Quantity;        // Current stock
    float Price;         // Price per unit

public:
    // Constructor
    InventoryItem() {
        ItemID = 0;
        ItemName = "";
        Quantity = 0;
        Price = 0.0;
    }

    // Parameterized constructor
    InventoryItem(int id, string name, int qty, float price) {
        ItemID = id;
        ItemName = name;
        Quantity = qty;
        Price = price;
    }

    // Getters
    int getItemID() const { return ItemID; }
    string getItemName() const { return ItemName; }
    int getQuantity() const { return Quantity; }
    float getPrice() const { return Price; }

    // Setters
    void setItemID(int id) { ItemID = id; }
    void setItemName(string name) { ItemName = name; }
    void setQuantity(int qty) { Quantity = qty; }
    void setPrice(float price) { Price = price; }

    // Display details
    void displayItem() const {
        cout << "------------------------------------\n";
        cout << "Item ID     : " << ItemID << endl;
        cout << "Item Name   : " << ItemName << endl;
        cout << "Quantity    : " << Quantity << endl;
        cout << "Price (?)   : " << Price << endl;
        cout << "------------------------------------\n";
    }
};

//---------------------------------------------
// 2. Inventory Management System
//---------------------------------------------
class InventoryManagementSystem {
private:
    InventoryItem ItemArray[100]; // Fixed array of inventory items
    int count;                    // Total number of items in the array

public:
    // Constructor
    InventoryManagementSystem() {
        count = 0;
    }

    // Add a new item
    void addItemRecord() {
        if (count >= 100) {
            cout << "\n?? Inventory full! Cannot add more items.\n";
            return;
        }

        int id, qty;
        string name;
        float price;

        cout << "\nEnter Item ID: ";
        cin >> id;

        // Check duplicate ID
        for (int i = 0; i < count; i++) {
            if (ItemArray[i].getItemID() == id) {
                cout << "? Item with this ID already exists!\n";
                return;
            }
        }

        cout << "Enter Item Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> qty;
        cout << "Enter Price (?): ";
        cin >> price;

        // Add new item
        ItemArray[count] = InventoryItem(id, name, qty, price);
        count++;
        cout << "? Item added successfully!\n";
    }

    // Delete item by ItemID
    void removeItemRecord() {
        if (count == 0) {
            cout << "\n?? No items to delete.\n";
            return;
        }

        int id;
        cout << "\nEnter Item ID to delete: ";
        cin >> id;

        for (int i = 0; i < count; i++) {
            if (ItemArray[i].getItemID() == id) {
                // Shift elements left to fill gap
                for (int j = i; j < count - 1; j++) {
                    ItemArray[j] = ItemArray[j + 1];
                }
                count--;
                cout << "??? Item deleted successfully!\n";
                return;
            }
        }
        cout << "? Item not found!\n";
    }

    // Search item by ID or Name
    void searchByItem() {
        if (count == 0) {
            cout << "\n?? Inventory is empty!\n";
            return;
        }

        int choice;
        cout << "\nSearch by: 1. ItemID  2. ItemName\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            cout << "Enter Item ID: ";
            cin >> id;

            for (int i = 0; i < count; i++) {
                if (ItemArray[i].getItemID() == id) {
                    ItemArray[i].displayItem();
                    return;
                }
            }
            cout << "? Item not found!\n";
        }
        else if (choice == 2) {
            string name;
            cout << "Enter Item Name: ";
            cin.ignore();
            getline(cin, name);

            for (int i = 0; i < count; i++) {
                if (ItemArray[i].getItemName() == name) {
                    ItemArray[i].displayItem();
                    return;
                }
            }
            cout << "? Item not found!\n";
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    // Display all items
    void displayAll() {
        if (count == 0) {
            cout << "\n?? Inventory is empty!\n";
            return;
        }

        cout << "\n======= INVENTORY RECORDS =======\n";
        for (int i = 0; i < count; i++) {
            ItemArray[i].displayItem();
        }
    }

    // Manage price & quantity data (row-major representation)
    void managePriceQuantity() {
        if (count == 0) {
            cout << "\n?? No data to display.\n";
            return;
        }

        cout << "\nOrganizing Price and Quantity Data (Row-Major Order)\n";
        cout << "------------------------------------\n";
        for (int i = 0; i < count; i++) {
            cout << "Item: " << ItemArray[i].getItemName()
                 << " | Quantity: " << ItemArray[i].getQuantity()
                 << " | Price: ?" << ItemArray[i].getPrice() << endl;
        }
        cout << "------------------------------------\n";
    }

    // Sparse storage (for rarely restocked products)
    void optimizeSparseStorage() {
        if (count == 0) {
            cout << "\n?? Inventory is empty!\n";
            return;
        }

        cout << "\nOptimizing Sparse Storage for Rarely Restocked Products...\n";
        cout << "(Products with Quantity < 5 are considered sparse)\n";
        cout << "------------------------------------\n";

        bool found = false;
        for (int i = 0; i < count; i++) {
            if (ItemArray[i].getQuantity() < 5) {
                cout << "(Sparse) Item ID: " << ItemArray[i].getItemID()
                     << " | Name: " << ItemArray[i].getItemName()
                     << " | Qty: " << ItemArray[i].getQuantity()
                     << " | Price: ?" << ItemArray[i].getPrice() << endl;
                found = true;
            }
        }

        if (!found)
            cout << "? No sparse items found.\n";

        cout << "------------------------------------\n";
    }
};

//---------------------------------------------
// Main Program
//---------------------------------------------
int main() {
    InventoryManagementSystem IMS;
    int choice;

    do {
        cout << "\n=========== INVENTORY MANAGEMENT MENU ===========\n";
        cout << "1. Add Item Record\n";
        cout << "2. Remove Item Record\n";
        cout << "3. Search Item\n";
        cout << "4. Display All Items\n";
        cout << "5. Manage Price & Quantity (Row-Major)\n";
        cout << "6. Optimize Sparse Storage\n";
        cout << "7. Exit\n";
        cout << "=================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            IMS.addItemRecord();
            break;
        case 2:
            IMS.removeItemRecord();
            break;
        case 3:
            IMS.searchByItem();
            break;
        case 4:
            IMS.displayAll();
            break;
        case 5:
            IMS.managePriceQuantity();
            break;
        case 6:
            IMS.optimizeSparseStorage();
            break;
        case 7:
            cout << "Exiting program... ?\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}


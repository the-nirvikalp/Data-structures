#include <iostream>
#include <string>
using namespace std;

//----------------------------------------------------------
// 1. Weather Record ADT
//----------------------------------------------------------
class WeatherRecord {
private:
    string Date;        // e.g. "12/06/2025"
    string City;        // City name
    double Temperature; // Temperature value

public:
    // Default Constructor
    WeatherRecord() {
        Date = "";
        City = "";
        Temperature = 0.0;
    }

    // Parameterized Constructor
    WeatherRecord(string date, string city, double temp) {
        Date = date;
        City = city;
        Temperature = temp;
    }

    // Getter Methods
    string getDate() const { return Date; }
    string getCity() const { return City; }
    double getTemperature() const { return Temperature; }

    // Setter Methods
    void setDate(string date) { Date = date; }
    void setCity(string city) { City = city; }
    void setTemperature(double temp) { Temperature = temp; }

    // Display weather record
    void display() const {
        cout << "------------------------------------\n";
        cout << "Date         : " << Date << endl;
        cout << "City         : " << City << endl;
        cout << "Temperature  : " << Temperature << " °C\n";
        cout << "------------------------------------\n";
    }
};

//----------------------------------------------------------
// 2. Weather System Class (implements the ADT methods)
//----------------------------------------------------------
class WeatherSystem {
private:
    WeatherRecord records[100]; // Fixed-size array
    int count;                  // Total number of records

public:
    WeatherSystem() {
        count = 0;
    }

    // Insert a new weather record
    void insertRecord() {
        if (count >= 100) {
            cout << "\n?? Record storage full!\n";
            return;
        }

        string date, city;
        double temp;

        cout << "\nEnter Date (dd/mm/yyyy): ";
        cin.ignore();
        getline(cin, date);
        cout << "Enter City: ";
        getline(cin, city);
        cout << "Enter Temperature (°C): ";
        cin >> temp;

        // Add new record
        records[count] = WeatherRecord(date, city, temp);
        count++;
        cout << "? Record inserted successfully!\n";
    }

    // Delete a record by city and date
    void deleteRecord() {
        if (count == 0) {
            cout << "\n?? No records to delete.\n";
            return;
        }

        string city, date;
        cout << "\nEnter City: ";
        cin.ignore();
        getline(cin, city);
        cout << "Enter Date (dd/mm/yyyy): ";
        getline(cin, date);

        for (int i = 0; i < count; i++) {
            if (records[i].getCity() == city && records[i].getDate() == date) {
                // Shift array elements left
                for (int j = i; j < count - 1; j++)
                    records[j] = records[j + 1];
                count--;
                cout << "??? Record deleted successfully!\n";
                return;
            }
        }
        cout << "? Record not found!\n";
    }

    // Retrieve all temperature data for a specific city and year
    void retrieveByCityAndYear() {
        if (count == 0) {
            cout << "\n?? No records available.\n";
            return;
        }

        string city, year;
        cout << "\nEnter City: ";
        cin.ignore();
        getline(cin, city);
        cout << "Enter Year (yyyy): ";
        getline(cin, year);

        bool found = false;
        cout << "\nTemperature Data for " << city << " in " << year << ":\n";
        cout << "------------------------------------\n";

        for (int i = 0; i < count; i++) {
            string date = records[i].getDate();
            if (records[i].getCity() == city && date.substr(6, 4) == year) {
                cout << date << "  ->  " << records[i].getTemperature() << " °C\n";
                found = true;
            }
        }

        if (!found)
            cout << "No records found for " << city << " in " << year << ".\n";
        cout << "------------------------------------\n";
    }

    // Display all records
    void displayAllRecords() {
        if (count == 0) {
            cout << "\n?? No records available.\n";
            return;
        }
        cout << "\n======= ALL WEATHER RECORDS =======\n";
        for (int i = 0; i < count; i++)
            records[i].display();
    }
};

//----------------------------------------------------------
// 3. Data Storage Class (2D Array for City-Year Data)
//----------------------------------------------------------
class DataStorage {
private:
    double tempArray[10][10];   // 2D array: rows=years, cols=cities
    string cities[10];
    int years[10];
    int rowCount, colCount;

public:
    DataStorage() {
        rowCount = 0;
        colCount = 0;
        // Initialize with sentinel value (-9999 means missing data)
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                tempArray[i][j] = -9999;
    }

    // Populate the 2D array with sample data
    void populateArray() {
        cout << "\nEnter number of years (max 10): ";
        cin >> rowCount;
        cout << "Enter number of cities (max 10): ";
        cin >> colCount;

        // Get city names
        cout << "Enter city names:\n";
        cin.ignore();
        for (int j = 0; j < colCount; j++) {
            getline(cin, cities[j]);
        }

        // Get years
        cout << "Enter years:\n";
        for (int i = 0; i < rowCount; i++) {
            cin >> years[i];
        }

        // Fill temperature data
        cout << "\nEnter temperature values (°C), use -9999 for missing data:\n";
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < colCount; j++) {
                cout << "Year " << years[i] << ", City " << cities[j] << ": ";
                cin >> tempArray[i][j];
            }
        }
        cout << "? Data populated successfully!\n";
    }

    // Access data in row-major order
    void rowMajorAccess() {
        cout << "\n--- Row-Major Access ---\n";
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < colCount; j++) {
                cout << "[" << years[i] << ", " << cities[j] << "] = " << tempArray[i][j] << " °C\n";
            }
        }
    }

    // Access data in column-major order
    void columnMajorAccess() {
        cout << "\n--- Column-Major Access ---\n";
        for (int j = 0; j < colCount; j++) {
            for (int i = 0; i < rowCount; i++) {
                cout << "[" << years[i] << ", " << cities[j] << "] = " << tempArray[i][j] << " °C\n";
            }
        }
    }

    // Handle sparse data (-9999 means missing)
    void handleSparseData() {
        cout << "\n--- Handling Sparse Data ---\n";
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < colCount; j++) {
                if (tempArray[i][j] == -9999)
                    cout << "(Missing) Year: " << years[i] << ", City: " << cities[j] << endl;
            }
        }
        cout << "------------------------------------\n";
    }

    // Analyze time and space complexity
    void analyzeComplexity() {
        cout << "\n--- Complexity Analysis ---\n";
        cout << "Time Complexity:\n";
        cout << "  - populateArray(): O(n*m)\n";
        cout << "  - rowMajorAccess(): O(n*m)\n";
        cout << "  - columnMajorAccess(): O(n*m)\n";
        cout << "  - handleSparseData(): O(n*m)\n";
        cout << "\nSpace Complexity:\n";
        cout << "  - Uses a 2D array of size [n][m] => O(n*m)\n";
        cout << "------------------------------------\n";
    }
};

//----------------------------------------------------------
// 4. Main Program
//----------------------------------------------------------
int main() {
    WeatherSystem ws;
    DataStorage ds;
    int choice;

    do {
        cout << "\n================ WEATHER DATA MENU ================\n";
        cout << "1. Insert Weather Record\n";
        cout << "2. Delete Weather Record\n";
        cout << "3. Retrieve City-Year Data\n";
        cout << "4. Display All Records\n";
        cout << "5. Populate Temperature Array\n";
        cout << "6. Row-Major Access\n";
        cout << "7. Column-Major Access\n";
        cout << "8. Handle Sparse Data\n";
        cout << "9. Analyze Complexity\n";
        cout << "10. Exit\n";
        cout << "==================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: ws.insertRecord(); break;
        case 2: ws.deleteRecord(); break;
        case 3: ws.retrieveByCityAndYear(); break;
        case 4: ws.displayAllRecords(); break;
        case 5: ds.populateArray(); break;
        case 6: ds.rowMajorAccess(); break;
        case 7: ds.columnMajorAccess(); break;
        case 8: ds.handleSparseData(); break;
        case 9: ds.analyzeComplexity(); break;
        case 10: cout << "Exiting program... ?\n"; break;
        default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 10);

    return 0;
}


#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <conio.h>
using namespace std;

// ==================== STRUCTS ====================

struct Car {
    int carID = 0;
    string brand;
    string model;
    int year = 0;
    string plateNumber;
    float dailyRate = 0.0;
    string status;
    string color;
};



struct Date {
    int day, month, year;
};

int toDays(Date d) {
    return d.day + (d.month * 31) + (d.year * 365);
}



struct Customer {
    string name;
    string mobileNo;
    string pass;
    string Address;
    string National_ID;
    string Jop_title;
};

struct CreditCard {
    string cardNumber;
    string bankName;
    string cardOwnerName;
    string cvv;
};

struct Payment {
    int paymentID = 0;
    CreditCard cardDetails;
};

struct Rental {
    int rentalID = 0;
    int carID = 0;
    string customerNationalID; 
    int rentalDays = 0;
    float totalCost = 0.0f;
    Date startDate;
    Date endDate;
};

struct Admin {
    string username;
    string password;
};

// ==================== GLOBAL ARRAYS ====================

const int MAX = 100;

Car cars[MAX];
int cars_counter = 0;

Customer customers[MAX];
int customersCount = 0;

Payment payments[MAX];
int paymentCounter = 0;

Rental rentals[500];
int rentalCount = 0;

// Admin credentials (hardcoded)
Admin admin = { "admin", "admin123" };

// ==================== FUNCTION DECLARATIONS ====================

// File Functions
void loadAllData();
void saveAllData();

// Car Functions
void Show_Car_Det(Car c);
bool Check_Car();
void Add_car();
void Remove_car();
void showCars();
void Update_car_details();  /////RAHF

// Customer Functions
bool signUp();
int login();
void showAllCustomers();
bool deleteCustomer();
void adminMenu();
void adminLogin();
void userMenu(int userIndex);

// Payment Function
void Payment_Methods();

// Rental Functions
void rentCar();
void cancelReservation();
void returnCar(int number);

// ==================== LOAD & SAVE (File used ONLY here) ====================

void loadAllData() {
    // --- Load Cars ---
    ifstream carsFile("cars.txt");
    if (carsFile.is_open()) {
        carsFile >> cars_counter;
        carsFile.ignore();
        for (int i = 0; i < cars_counter; i++) {
            carsFile >> cars[i].carID;
            carsFile.ignore();
            getline(carsFile, cars[i].brand);
            getline(carsFile, cars[i].model);
            carsFile >> cars[i].year;
            carsFile >> cars[i].plateNumber;
            carsFile >> cars[i].dailyRate;
            carsFile.ignore();
            getline(carsFile, cars[i].status);
            getline(carsFile, cars[i].color);
        }
        carsFile.close();
    }
    else {



        cars[cars_counter++] = { 1, "Toyota", "Camry", 2022, "ABC-001", 500.0, "Available" ,"Red" };
        cars[cars_counter++] = { 2, "BMW", "X5", 2023, "BMW-002", 800.0, "Available" ,"Black" };
        cars[cars_counter++] = { 3, "Mercedes", "C200", 2022, "MRC-003", 900.0, "Available","White" };
        cars[cars_counter++] = { 4, "Kia", "Sportage", 2023, "KIA-004", 400.0, "Available","Gold" };
        cars[cars_counter++] = { 5, "Audi", "A6", 2023, "AUD-005", 750.0, "Available","silver" };
        cars[cars_counter++] = { 6, "Hyundai", "Tucson", 2022, "HYN-006", 350.0, "Available","Orange" };
        cars[cars_counter++] = { 7, "Nissan", "Altima", 2022, "NIS-007", 450.0, "Available","Yellow" };


    }

    // --- Load Customers ---
    ifstream custFile("customers.txt");
    if (custFile.is_open()) {
        custFile >> customersCount;
        custFile.ignore();
        for (int i = 0; i < customersCount; i++) {
            getline(custFile, customers[i].name);
            getline(custFile, customers[i].pass);
            getline(custFile, customers[i].National_ID);
            getline(custFile, customers[i].mobileNo);
            getline(custFile, customers[i].Address);
            getline(custFile, customers[i].Jop_title);
        }
        custFile.close();
    }
    else {
        cout << "No customers file found.\n";
    }

    // --- Load Rentals ---
    ifstream rentFile("rentals.txt");
    if (rentFile.is_open()) {
        rentFile >> rentalCount;
        rentFile.ignore();
        for (int i = 0; i < rentalCount; i++) {
            rentFile >> rentals[i].rentalID;
            rentFile >> rentals[i].carID;
            rentFile.ignore();
            getline(rentFile, rentals[i].customerNationalID); 
            rentFile >> rentals[i].rentalDays;
            rentFile >> rentals[i].totalCost;
            rentFile >> rentals[i].startDate.day;
            rentFile >> rentals[i].startDate.month;
            rentFile >> rentals[i].startDate.year;
            rentFile >> rentals[i].endDate.day;
            rentFile >> rentals[i].endDate.month;
            rentFile >> rentals[i].endDate.year;
            rentFile.ignore();
            rentFile.ignore();
        }
        rentFile.close();
    }
    else {
        cout << "No rentals file found.\n";
    }
}

void saveAllData() {
    // --- Save Cars ---
    ofstream carsFile("cars.txt");
    if (carsFile.is_open()) {
        carsFile << cars_counter << "\n";
        for (int i = 0; i < cars_counter; i++) {
            carsFile << cars[i].carID << "\n";
            carsFile << cars[i].brand << "\n";
            carsFile << cars[i].model << "\n";
            carsFile << cars[i].year << "\n";
            carsFile << cars[i].plateNumber << "\n";
            carsFile << cars[i].dailyRate << "\n";
            carsFile << cars[i].status << "\n";
            carsFile << cars[i].color << "\n";

        }
        carsFile.close();
    }

    // --- Save Customers ---
    ofstream custFile("customers.txt");
    if (custFile.is_open()) {
        custFile << customersCount << "\n";
        for (int i = 0; i < customersCount; i++) {
            custFile << customers[i].name << "\n";
            custFile << customers[i].pass << "\n";
            custFile << customers[i].National_ID << "\n";
            custFile << customers[i].mobileNo << "\n";
            custFile << customers[i].Address << "\n";
            custFile << customers[i].Jop_title << "\n";
        }
        custFile.close();
    }

    // --- Save Rentals ---
    ofstream rentFile("rentals.txt");
    if (rentFile.is_open()) {
        rentFile << rentalCount << "\n";
        for (int i = 0; i < rentalCount; i++) {
            rentFile << rentals[i].rentalID << "\n";
            rentFile << rentals[i].carID << "\n";
            rentFile << rentals[i].customerNationalID << "\n"; 
            rentFile << rentals[i].rentalDays << "\n";
            rentFile << rentals[i].totalCost << "\n";

            rentFile << rentals[i].startDate.day << "\n";
            rentFile << rentals[i].startDate.month << "\n";
            rentFile << rentals[i].startDate.year << "\n";
            rentFile << rentals[i].endDate.day << "\n";
            rentFile << rentals[i].endDate.month << "\n";
            rentFile << rentals[i].endDate.year << "\n";
        }
        rentFile.close();
    }
}

// ==================== TAB 1: Show_Car_Det HAGER ====================

void Show_Car_Det(Car c) {
    cout << "\n-----Car Details-----" << endl;
    cout << "ID           : " << c.carID << endl;
    cout << "Brand & Model: " << c.brand << " " << c.model << endl;
    cout << "Year         : " << c.year << endl;
    cout << "Plate Number : " << c.plateNumber << endl;
    cout << "Daily Rate   : " << c.dailyRate << " EGP" << endl;
    cout << "Status       : " << c.status << endl;
    cout << "Color        : " << c.color << endl;
    cout << "-------------------------------------------------------------" << endl;
}

// ==================== TAB 2: Check_Car HAGER ====================

bool Check_Car() {
    if (cars_counter == 0) {
        cout << "The Car Record Is Empty." << endl;
        return false;
    }
    int searchID;
    cout << "Enter the car ID to check: ";
    cin >> searchID;

    bool found = false;
    for (int i = 0; i < cars_counter; i++) {
        if (cars[i].carID == searchID) {
            found = true;
            cout << "Car is Found!" << endl;
            cout << "Current Staus :" << cars[i].status << endl;
            char choice;
            cout << "\n Do you want to see full details ?(y,n)";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                Show_Car_Det(cars[i]);

            }
            else {
                cout << "Returning to menu" << endl;
            }
            return true;
        }
    }
    if (!found) {
        cout << " Car with ID " << searchID << " Not found." << endl;
        return false;
    }
    return false;
}

// ==================== TAB 3: Add_car LOGIN ====================

void Add_car() {
    if (cars_counter >= MAX) {
        cout << "Car storage is full!\n";
        return;
    }
    cout << "Add car's ID: ";
    cin >> cars[cars_counter].carID;

    int id = cars[cars_counter].carID;
    for (int i = 0; i < cars_counter; i++) {
        if (id == cars[i].carID) {
            cout << "The car's ID already exists.\n";
            return;
        }
    }

    cin.ignore();
    cout << "Add car's brand: ";
    getline(cin, cars[cars_counter].brand);

    cout << "Add car's model: ";
    getline(cin, cars[cars_counter].model);

    cout << "Add car's year: ";
    cin >> cars[cars_counter].year;

    cout << "Add car's plate number: ";
    cin >> cars[cars_counter].plateNumber;

    cout << "Add car's daily rate: ";
    cin >> cars[cars_counter].dailyRate;

    cin.ignore();
    cout << "Add car's status:(Available/Ranted) ";
    getline(cin, cars[cars_counter].status);
    cout << "Add car color: ";
    getline(cin, cars[cars_counter].color);

    cout << "Car with ID " << cars[cars_counter].carID << " has been added successfully.\n";
    cars_counter++;
}

// ==================== TAB 4: Remove_car LOGIN ====================

void Remove_car() {
    if (cars_counter == 0) {
        cout << "There are no cars available to remove!\n";
        return;
    }

    int id;
    bool found = false;
    cout << "Enter the car's ID that you want to remove: ";
    cin >> id;

    for (int i = 0; i < cars_counter; i++) {
        if (id == cars[i].carID) {
            found = true;
            for (int j = i; j < cars_counter - 1; j++) {
                cars[j] = cars[j + 1];
            }
            cars_counter--;
            cout << "Car with ID " << id << " has been removed successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "Car with ID " << id << " Not Found.\n";
    }
}

// ==================== TAB 5: listCars ====================

void showCars() {
    if (cars_counter == 0) {
        cout << "No cars available.\n";
        return;
    }

    cout << "\n========== AVAILABLE CARS ==========\n";
    int totalAvailable = 0;
    int displayIndex = 1;

    for (int i = 0; i < cars_counter; i++) {
        if (cars[i].status == "Available") {
            cout << displayIndex << ". "
                << cars[i].brand << " " << cars[i].model
                << " | Daily Rate: " << cars[i].dailyRate << " EGP" << endl;
            displayIndex++;
            totalAvailable++;
        }
    }
    cout << "------------------------------------\n";
    cout << "Total Available : " << totalAvailable << endl;
}



// ==================== TAB 6: Update_car_details RAHF ====================

void Update_car_details() {
    if (cars_counter == 0) {
        cout << "No cars available to update!\n";
        return;
    }
    int id;
    bool found = false;
    cout << "Enter the car's ID that you want to update: ";
    cin >> id;
    for (int i = 0; i < cars_counter; i++) {
        if (id == cars[i].carID) {
            found = true;
            cout << "\n--- Car Found! Enter new details ---\n";

            cin.ignore();
            cout << "Enter new brand: ";
            getline(cin, cars[i].brand);

            cout << "Enter new model: ";
            getline(cin, cars[i].model);
            cout << "Enter new color: ";
            getline(cin, cars[i].color);

            cout << "Enter new year: ";
            cin >> cars[i].year;

            cout << "Enter new plate number: ";
            cin >> cars[i].plateNumber;

            cout << "Enter new daily rate: ";
            cin >> cars[i].dailyRate;

            cin.ignore();
            cout << "Enter new status: ";
            getline(cin, cars[i].status);

            cout << "\nCar with ID " << id << " has been updated successfully.\n";
            break;
        }
    }
    if (!found) {
        cout << "Car with ID " << id << " Not Found.\n";
    }
}


// ==================== TAB 7: signUp ====================
bool signUp() {


    if (customersCount >= MAX) {
        cout << "System is full!" << endl;
        return false;
    }

    cout << "\n========================================" << endl;
    cout << "           CREATE NEW ACCOUNT           " << endl;
    cout << "========================================\n" << endl;


    cout << " ENTER NAME : ";
    getline(cin, customers[customersCount].name);
    if (customers[customersCount].name.empty()) {
        cout << "Name cannot be empty!\n";
        return false;
    }

    cout << " ENTER PASSWORD : ";
    cin >> customers[customersCount].pass;


    cout << " ENTER National_ID : ";
    cin >> customers[customersCount].National_ID;


    cout << " ENTER Mobile No : ";
    cin >> customers[customersCount].mobileNo;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << " ENTER Address : ";
    getline(cin, customers[customersCount].Address);

    cout << " ENTER Job Title : ";
    cin >> customers[customersCount].Jop_title;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    customersCount++;
    cout << "\nAccount created successfully!" << endl;
    return true;
}



// ==================== TAB 8: login ====================

int login() {
    string inputName, inputPass;

    cout << "\n========================================" << endl;
    cout << "               CUSTOMER LOGIN           " << endl;
    cout << "========================================\n" << endl;

    cout << " ENTER NAME : ";
    getline(cin, inputName);
    cout << " ENTER PASSWORD : ";
    cin >> inputPass;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < customersCount; i++) {
        if (customers[i].name == inputName && customers[i].pass == inputPass) {
            cout << "\nLogin Successful! Welcome, " << customers[i].name << endl;
            return i;
        }
    }

    cout << "\nInvalid name or password!" << endl;
    return -1;
}


void userMenu(int userIndex) {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "              USER MENU                 " << endl;
        cout << "========================================" << endl;
        cout << "1. Show Cars" << endl;
        cout << "2. Rent a Car" << endl;
        cout << "3. Check Car" << endl;
        cout << "4. Cancel Reservation" << endl;
        cout << "5. Return a Car" << endl;
        cout << "6. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Choose: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)      showCars();
        else if (choice == 2) rentCar();
        else if (choice == 3) Check_Car();
        else if (choice == 4) cancelReservation();
        else if (choice == 5) {
            int num;
            cout << "Enter car ID to return: ";
            cin >> num;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            returnCar(num);
        }
        else if (choice == 6) cout << "\nLogged out successfully." << endl;
        else                  cout << "Invalid choice!" << endl;

    } while (choice != 6);
}

// ==================== TAB 9: showAllCustomers ====================

void showAllCustomers() {
    if (customersCount == 0) {
        cout << "\nNo customers registered yet." << endl;
        return;
    }
    cout << "\n============================================" << endl;
    cout << "        ALL CUSTOMERS (" << customersCount << ")        " << endl;
    cout << "============================================" << endl;
    for (int i = 0; i < customersCount; i++) {
        cout << "\n[" << i + 1 << "] Name       : " << customers[i].name << endl;
        cout << "    Mobile    : " << customers[i].mobileNo << endl;
        cout << "    Address   : " << customers[i].Address << endl;
        cout << "    Nat. ID   : " << customers[i].National_ID << endl;
        cout << "    Job Title : " << customers[i].Jop_title << endl;
        cout << "--------------------------------------------" << endl;
    }
}

// ==================== TAB 10: deleteCustomer ====================

bool deleteCustomer() {
    if (customersCount == 0) {
        cout << "\nNo customers to delete." << endl;
        return false;
    }

    showAllCustomers();

    cout << "\nEnter the number of the customer to delete (1-" << customersCount << "): ";
    int index;
    cin >> index;

    if (index < 1 || index > customersCount) {
        cout << "Invalid choice!" << endl;
        return false;
    }

    for (int i = index - 1; i < customersCount - 1; i++) {
        customers[i] = customers[i + 1];
    }
    customersCount--;
    cout << "Customer deleted successfully!" << endl;
    return true;
}

// ==================== TAB 11: adminMenu ====================


void adminMenu() {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "             ADMIN PANEL                " << endl;
        cout << "========================================" << endl;
        cout << "1. Add Car" << endl;
        cout << "2. Remove Car" << endl;
        cout << "3. Update Car Details" << endl;
        cout << "4. Show All Customers" << endl;
        cout << "5. Delete a Customer" << endl;
        cout << "6. Check Car" << endl;
        cout << "7. Total Customers Count" << endl;

        cout << "8. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) Add_car();
        else if (choice == 2) Remove_car();
        else if (choice == 3) Update_car_details();
        else if (choice == 4) showAllCustomers();
        else if (choice == 5) deleteCustomer();
        else if (choice == 6) Check_Car();
        else if (choice == 7) cout << "\nTotal Customers: " << customersCount << endl;
        else if (choice == 8) cout << "\nAdmin logged out." << endl;
        else                  cout << "Invalid choice!" << endl;

    } while (choice != 8);
}

// ==================== TAB 12: adminLogin ====================

void adminLogin() {
    string inputUser, inputPass;

    cout << "\n========================================" << endl;
    cout << "              ADMIN LOGIN               " << endl;
    cout << "========================================\n" << endl;


    cout << " ENTER ADMIN USERNAME : ";
    getline(cin, inputUser);
    cout << " ENTER ADMIN PASSWORD : ";
    cin >> inputPass;

    if (inputUser == admin.username && inputPass == admin.password) {
        cout << "\nWelcome, Admin!" << endl;
        adminMenu();
    }
    else {
        cout << "\nInvalid admin credentials!" << endl;
    }
}

// ==================== TAB 13: Payment_Methods  JANA====================

void Payment_Methods() {
    int choice;
    bool success = false;

    while (!success) {
        cout << "\n      SELECT PAYMENT METHOD       " << endl;
        cout << "1. Credit Card (Visa/MasterCard)" << endl;
        cout << "2. Cash" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            payments[paymentCounter].paymentID = 5000 + paymentCounter;

            cout << "Enter 16-digit Card Number: ";
            int i = 0;
            payments[paymentCounter].cardDetails.cardNumber = "";
            while (i < 16) {
                char ch = _getch();
                if (ch >= '0' && ch <= '9') {
                    cout << ch;
                    payments[paymentCounter].cardDetails.cardNumber += ch;
                    i++;
                }
                else if (ch == 8 && i > 0) {
                    cout << "\b \b";
                    i--;
                }
            }
            cout << endl;

            cin.ignore();
            cout << "Bank Name: ";
            getline(cin, payments[paymentCounter].cardDetails.bankName);

            cout << "Owner Name: ";
            getline(cin, payments[paymentCounter].cardDetails.cardOwnerName);

            cout << "CVV (3 digits): ";
            int j = 0;
            payments[paymentCounter].cardDetails.cvv = "";
            while (j < 3) {
                char ch = _getch();
                if (ch >= '0' && ch <= '9') {
                    cout << "*";
                    payments[paymentCounter].cardDetails.cvv += ch;
                    j++;
                }
                else if (ch == 8 && j > 0) {
                    cout << "\b \b";
                    j--;
                }
            }
            cout << endl;

            success = true;
            paymentCounter++;
            cout << "\nTransaction Successful!!" << endl;

        }
        else if (choice == 2) {
            success = true;
            cout << "\n====Cash selected====" << endl;
        }
        else {
            cout << "Invalid choice, try again.\n";
        }
    }
}

// ==================== TAB 14: rentCar ====================

void rentCar() {
    int carID, days;
    string customerID;

    cout << "Enter Car ID: ";
    cin >> carID;

    // Search for car
    int carIndex = -1;
    for (int i = 0; i < cars_counter; i++) {
        if (cars[i].carID == carID) {
            carIndex = i;
            break;
        }
    }

    if (carIndex == -1) {
        cout << "Car not found.\n";
        return;
    }

    if (cars[carIndex].status != "Available" && cars[carIndex].status != "available") {
        cout << "Car is not available.\n";
        return;
    }

    cin.ignore();
    cout << "Enter Customer National ID: ";
    getline(cin, customerID); 

    // Check if customer exists
    bool customerFound = false;
    for (int i = 0; i < customersCount; i++) {
        if (customers[i].National_ID == customerID) { 
            customerFound = true;
            break;
        }
    }

    if (!customerFound) {
        cout << "Customer not found.\n";
        return;
    }

    cout << "Enter number of rental days: ";
    cin >> days;

    Date startDate;
    cout << "Enter Start Date (day month year): ";
    cin >> startDate.day >> startDate.month >> startDate.year;

    // ضيف الـ End Date
    Date endDate;
    cout << "Enter End Date (day month year): ";
    cin >> endDate.day >> endDate.month >> endDate.year;
    cin.ignore();



    // Create rental record
    rentals[rentalCount].rentalID = rentalCount + 1;
    rentals[rentalCount].carID = carID;
    rentals[rentalCount].customerNationalID = customerID; 
    rentals[rentalCount].rentalDays = days;
    rentals[rentalCount].totalCost = days * cars[carIndex].dailyRate;
    rentals[rentalCount].startDate = startDate;
    rentals[rentalCount].endDate = endDate;

    // Update car status
    cars[carIndex].status = "Rented";

    cout << "Car rented successfully!\n";
    cout << "Total cost: " << rentals[rentalCount].totalCost << " EGP\n";

    rentalCount++;

    // Ask for payment
    Payment_Methods();

    
}

// ==================== TAB 15: cancelReservation YARA ====================

void cancelReservation() {
    int rentalID;
    cout << "Enter Rental ID to cancel: ";
    cin >> rentalID;

    int rentalIndex = -1;
    for (int i = 0; i < rentalCount; i++) {
        if (rentals[i].rentalID == rentalID) {
            rentalIndex = i;
            break;
        }
    }

    if (rentalIndex == -1) {
        cout << "Rental not found.\n";
        return;
    }

    int carID = rentals[rentalIndex].carID;

    // Find car and make it available again
    for (int i = 0; i < cars_counter; i++) {
        if (cars[i].carID == carID) {
            cars[i].status = "Available";
            break;
        }
    }

    // Remove rental by shifting array
    for (int i = rentalIndex; i < rentalCount - 1; i++) {
        rentals[i] = rentals[i + 1];
    }
    rentalCount--;

    cout << "Reservation canceled successfully!\n";

    
}

// ==================== TAB 16: returnCar asel ====================

void returnCar(int carID) {
    // دور على العربية
    int carIndex = -1;
    for (int i = 0; i < cars_counter; i++) {
        if (cars[i].carID == carID) {
            carIndex = i;
            break;
        }
    }

    if (carIndex == -1) {
        cout << "Car not found.\n";
        return;
    }

    if (cars[carIndex].status == "Available") {
        cout << "This car is not rented!\n";
        return;
    }

    // دور على الـ rental record
    int rentalIndex = -1;
    for (int i = 0; i < rentalCount; i++) {
        if (rentals[i].carID == carID) {
            rentalIndex = i;
            break;
        }
    }

    if (rentalIndex == -1) {
        cout << "Rental record not found.\n";
        return;
    }

    // اسأل عن تاريخ الإرجاع
    Date returnDate;
    cout << "Enter Return Date (day month year): ";
    cin >> returnDate.day >> returnDate.month >> returnDate.year;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // احسب الأيام
    int plannedDays = rentals[rentalIndex].rentalDays;
    int actualDays = toDays(returnDate) - toDays(rentals[rentalIndex].startDate);
    int extraDays = actualDays - plannedDays;
    float fine = 0;

    if (extraDays > 0)
        fine = extraDays * 200;

    // اطبع الـ invoice
    cout << "\n========== INVOICE ==========\n";
    cout << "Customer ID  : " << rentals[rentalIndex].customerNationalID << endl;
    cout << "Planned Days : " << plannedDays << endl;
    cout << "Actual Days  : " << actualDays << endl;
    cout << "Daily Rate   : " << cars[carIndex].dailyRate << " EGP\n";
    cout << "Total Cost   : " << rentals[rentalIndex].totalCost << " EGP\n";
    if (fine > 0)
        cout << "Late Fine    : " << fine << " EGP\n";
    cout << "==============================\n";
    cout << "Car returned successfully!\n";

    // احذف الـ rental record
    for (int i = rentalIndex; i < rentalCount - 1; i++) {
        rentals[i] = rentals[i + 1];
    }
    rentalCount--;

    // رجّع العربية Available
    cars[carIndex].status = "Available";
}

// ==================== MAIN ====================

int main() {
    loadAllData();

    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "         CAR RENTAL SYSTEM              " << endl;
        cout << "========================================" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Customer Login" << endl;
        cout << "3. Admin Login" << endl;
        cout << "4. Exit" << endl;
        cout << "========================================" << endl;
        cout << "Choose Number : ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) signUp();
        else if (choice == 2) {
            int userIndex = login();
            if (userIndex != -1) {
                userMenu(userIndex);
            }
        }
        else if (choice == 3) adminLogin();
        else if (choice == 4) cout << "\nGoodbye!\n";
        else                  cout << "Invalid choice!\n";

    } while (choice != 4);

    saveAllData();
    return 0;
}

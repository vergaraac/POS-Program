/*
Machine Problem 5 - C2A Group 3

How many classes have you generated? What are these?
 - There are 4 classes generated for the use of this program, with 2 super classes named Employee and Inventory, and 2 sub classes named Manager and Cashier.
 The two parent classes are essential to make the POS system w/ item inventory much viable, applying the OOP concenpts of constructors/destructors, inheritance,
 polymorphism, and file i/o handling.

Can you name your abstract classes?
- The Employee class and the Inventory class are the generalization classes that holds the attributes and methods in which are the bare essentials for the Manager
and Cashier classes, allowing for code reusability in between them. 

For this activity, where you able to use the protected access specifier?
- Yes, protected access specifier is essential for performing inheritance/polymorphism work on our subclasses Manager and Cashier, which both exist in the 
superclasses of Employee and Inventory.

How did you use constructors and destructors?
- We used constructors / destructors to initialize PIN values in the Employee superclass, and inventory variable values in the Inventory superclass, which is 
to be used by the subclasses.

Did you apply method overloading or overriding? Which part of the program?
- From our code, there is no use of method overloading as there is no essential utility in having such. 

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream> 
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;

class Employee { //super class Employee, attributes to be inherited by Manager and Cashier subclasses
protected:
    int cashierpin, managerpin, PINtemp;

private:

    int inttemp{};
    string stringtemp;

    int IntValidation(int inttemp) //validation
    {
        //data type validation
        while ((cin.fail()) || (inttemp != cashierpin && inttemp != managerpin))
        {
            cout << "\nInvalid PIN. Please try again. " << endl;
            system("pause");
            system("CLS");
            cout << "MCJOLLIBEE\n";
            cout << "Lipa City, Batangas\n";
            cout << "Enter Employee Name: " << stringtemp << endl;
            cout << "INPUT YOUR 6 DIGIT PIN (177013 - Cashier PIN; 265198 - Manager PIN): ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> inttemp; //reentry of input, process repeats if the value given to cin fails the condition
            cout << endl;
        }
        return inttemp;
    }

public:
    Employee() {  // constructor for PIN values
        cashierpin = 177013;
        managerpin = 265198;
        PINtemp = 0;
    }
    ~Employee() {} // destructor

    virtual void menuselection() {} //virtual function for menu selection of manager and cashier classes
    virtual void setemployeename(string employeename) {} //virtual function for setting employee name in manager and cashier classes

    void setPINinput(int inputpin, string name) { //method for cashier and manager pin input
        inttemp = inputpin;
        stringtemp = name;
        inttemp = IntValidation(inttemp);
        system("CLS");
    }

    int getPINinput() { //pin input accessor
        return inttemp;
    }

};

class Inventory { //super class Inventory, attributes to be inherited by Manager and Cashier subclasses

protected:
    float price[5]{}, pricechange{};
    int initial[5]{}, pricenum{}, actual[5]{}, waste[5]{}, sales[5]{};
    int reorder_point;

public:
    Inventory() {

        reorder_point = 25;

        price[0] = 100.00;
        price[1] = 150.00;
        price[2] = 150.00;
        price[3] = 130.00;
        price[4] = 180.00;

        for (int i = 0; i < 5; i++) {

            waste[i] = 0;
            sales[i] = 0;
            initial[i] = 100;
            actual[i] = 100;

        }

    }
    ~Inventory() {}

    virtual void getorderamount(int arr[]) {}

    virtual void returnorderamount(int arr[]) {}

};

class Manager : public Employee, public Inventory { //Manager subclass, with multiple inheritance

private:
    bool loop{};
    int inttemp{}, temp, productEntry;
    char menu_select{};
    string stringtemp;

    int IntValidation(int inttemp) //validation for number of processes input
    {
        //data type validation
        while ((cin.fail()))
        {
            cout << "Invalid. Manager PIN (177013 - PIN indicated for the purpose of checking, not in actual setting): ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> inttemp; //reentry of input, process repeats if the value given to cin fails the condition
        }
        return inttemp;
    }

    int IntValidation2(int inttemp) { //validation for order number input

        while ((cin.fail()) || (inttemp < 0 || inttemp > 5))
        {
            system("CLS");
            cout << "Order Number input is invalid. Please try again. " << endl;
            system("pause");
            system("CLS");
            cout << "Add Order Menu (Type Order No to Add Stocks; Enter [0] to stop process): \n" << endl << "(100 Stocks per Order is the maximum)" << endl;

            for (int i = 0; i < 5; i++) {

                cout << "Order No. " << i + 1 << "\tCurrent Stock Amount: " << left << setw(15) << actual[i] << "\t # of orders that has spoiled since the last order: " << waste[i] << endl;

            }

            cout << "\nOption: ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> inttemp;
        }
        return inttemp;
    }

    int IntValidation3(int inttemp) { //validation for quantity input

        while ((cin.fail()) || temp + inttemp > 100)
        {
            system("CLS");
            cout << "Quantity input is invalid. Please try again. " << endl;
            system("pause");
            system("CLS");
            cout << "Add Order Menu (Type Order No to Add Stocks; Enter [0] to stop process): \n" << endl << "(100 Stocks per Order is the maximum)" << endl;

            for (int i = 0; i < 5; i++) {

                cout << "Order No. " << i + 1 << "\tCurrent Stock Amount: " << left << setw(15) << actual[i] << "\t # of orders that has spoiled since the last order: " << waste[i] << endl;

            }

            cout << "\nOption: " << productEntry;
            cout << "\nQuantity: ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> inttemp;
        }
        return inttemp;
    }

public:

    void getorderamount(int arr[]) { //mutator to get cashier modified values to manager

        for (int i = 0; i < 5; i++) {

            sales[i] = arr[i + 5];
            waste[i] = arr[i + 10];
            actual[i] = 0;
            actual[i] += arr[i + 15];
        }

    }

    void returnorderamount(int arr[]) { //mutator to give out manager modified values to cashier

        for (int i = 0; i < 5; i++) {

            arr[i] = 0;
            arr[i + 5] = 0;
            arr[i + 10] = 0;
            arr[i + 15] = actual[i];
        }

    }

    void viewStock() { //method that views the current inventory, generates inventory file, and restocks inventory when needed
        // writing to file then printing from file
        bool reorder_check = true;
        int reorder_count = 0;
        cout << "Stock Inventory (Orders with 25% or below of their actual stock are given option to be restocked back to 100) \n\n";
        cout << left << setw(20) << "Items " << setw(15) << "Initial" << setw(15) << "Sales" << setw(15) << "Waste" << setw(15) << "Actual" << endl;
        for (int i = 0; i < 5; i++) {
            cout << left << "Order " << i + 1 << setw(13) << " " << setw(15) << initial[i] << setw(15) << sales[i] << setw(15) << waste[i] << setw(15) << actual[i] << endl;
            if (actual[i] <= 25) {
                reorder_count++;
            }
        }

        ofstream write_inv("Inventory.txt");
        write_inv << "\t\t    MCJOLLIBEE" << endl;
        write_inv << "\t       Lipa City, Batangas" << endl;
        write_inv << "\t\t  Stock Inventory" << endl << endl;

        write_inv << left << setw(20) << "Items " << setw(15) << "Initial" << setw(15) << "Sales" << setw(15) << "Waste" << setw(15) << "Actual" << endl;
        for (int i = 0; i < 5; i++) {
            write_inv << left << "Order " << i + 1 << setw(13) << " " << setw(15) << initial[i] << setw(15) << sales[i] << setw(15) << waste[i] << setw(15) << actual[i] << endl;
        }
        write_inv << endl << endl;
        write_inv.close();
        if (reorder_count > 0) {
            reorder_check = false;
        }
        if (reorder_check == false) {
            char reorder_choice;
            do {
                cout << endl << "Items are in need of stock, Reorder[Y/N]: ";
                cin >> reorder_choice;
                reorder_choice = toupper(reorder_choice);
                switch (reorder_choice) {
                case 'Y': {
                    system("cls");
                    ofstream note("Inventory.txt", ios::app);
                    note << "\t\t*Items ";
                    cout << "\t\t Item Reorder" << endl << endl;
                    cout << left << setw(20) << "Items " << setw(25) << "No. of Orders" << endl;
                    for (int i = 0; i < 5; i++) {
                        if (actual[i] <= 25) {
                            int no_of_orders = 0;
                            note << i + 1 << ", ";
                            no_of_orders = 100 - actual[i];
                            cout << left << "Order " << i + 1 << setw(13) << " " << setw(25) << no_of_orders << endl;
                            no_of_orders = (actual[i] + 100) - actual[i];
                            actual[i] = no_of_orders;
                        }
                    }
                    cout << endl;
                    note << "have been replenished of stock" << endl << endl;
                    note.close();
                    break;
                }
                case 'N': {
                    system("cls");
                    break;
                }
                default: {
                    system("cls");
                    cout << "Invalid Input please try again\n\n";
                    system("pause");
                    system("cls");
                }
                }

            } while (reorder_choice != 'Y' && reorder_choice != 'N');

        }
    }

    void addStock() //method to addstock in the inventory orders
    {
        bool order_loop = true;
        int quantity;


        while (order_loop) {

            cin.clear();
            cin.ignore(123, '\n');
            system("cls");

            cout << "Add Order Menu (Type Order No to Add Stocks; Enter [0] to stop process): \n" << endl << "(100 Stocks per Order is the maximum)" << endl;

            for (int i = 0; i < 5; i++) {

                cout << "Order No. " << i + 1 << "\tCurrent Stock Amount: " << left << setw(15) << actual[i] << "\t # of orders that has spoiled since the last order: " << waste[i] << endl;

            }

            cout << "\nOption: ";
            cin >> productEntry;
            inttemp = productEntry;
            productEntry = IntValidation2(inttemp);
            if (productEntry != 0) {
                temp = actual[productEntry - 1];
            }

            if (productEntry == 0) {
                order_loop = false;
            }
            else if ((productEntry > 0 && productEntry < 6) && temp < 100) {
                cout << "Quantity: ";
                cin >> quantity;
                inttemp = quantity;
                quantity = IntValidation3(inttemp);
                actual[productEntry - 1] += quantity;
            }
            else if ((productEntry > 0 && productEntry < 6) && temp >= 100) {
                cout << "\nWrong input or the stock is already full for this order. Provide a different input, or exit the process with [0]." << endl;
                system("pause");
            }
            else {
                system("CLS");
                cout << "Order Input is invalid. Please try again. " << endl;
                system("pause");
            }

            system("CLS");
        }

    }

    void menuselection() { //manager's use of virtual function menuselection()
        bool menu_loop = true;

        do {
            system("cls");
            cout << "MCJOLLIBEE" << endl;
            cout << "Lipa City, Batangas" << endl;
            cout << "Welcome Manager " << stringtemp << endl << endl;
            cout << "[1] ADD STOCKS" << endl;
            cout << "[2] VIEW STOCKS" << endl;
            cout << "[3] LOG OUT" << endl << endl << "Option: ";
            cin >> menu_select;
            switch (menu_select) {
            case '1': {
                addStock();
                break;
            }
            case '2': {
                viewStock();
                system("pause");
                break;
            }
            case '3': {
                menu_loop = false;
                system("cls");
                cout << "MCJOLLIBEE\n";
                cout << "Lipa City, Batangas\n";
                cout << "\nManager " << stringtemp << " has logged out." << endl;
                system("pause");
                break;
            }
            default: {
                cout << "\nInvalid Input. Please Try Again" << endl << endl;
                system("pause");
                system("cls");
                break;
            }
            }
        } while (menu_loop == true);

    }

    char getmenuselect() {// menu option accessor
        return menu_select;
    }

    void confirmation() { //method to confirm void transactions

        loop = true;

        while (loop) {
            cout << "Manager PIN (265198 - PIN indicated for checking, not in actual setting): ";
            cin >> PINtemp;
            inttemp = PINtemp;
            PINtemp = IntValidation(inttemp);
            try { //exception handling of wrong PIN input
                if (PINtemp == managerpin) {
                    loop = false;
                    cout << "Order cancelled / Process cancelled." << endl;
                    cout << endl;
                    system("pause");
                }
                else {
                    throw (PINtemp);
                }
            }
            catch (const int PINtemp) {
                cout << "Invalid PIN. " << endl;
            }
        }

    }

    void setemployeename(string name) { //manager's use of virtual function setemployeename()
        stringtemp = name;
    }

};


class Cashier : public Employee, public Inventory { //Cashier subclass, with multiple inheritance

private:

    bool void_condition = false, void_condition2 = false;
    int inttemp{}, quantity{}, orderamount[5] = { 0 }, ordercount = 0, additional[5] = { 0 }, temp{};
    char chartemp{}, orderinput{};
    float total_cost{}, payment{}, floattemp{}, change{};
    string stringtemp;

    void printmenu() { //private method to print out menu options

        system("CLS");
        cout << "MCJOLLIBEE\n";
        cout << "Lipa City, Batangas\n";
        cout << "Welcome, Cashier " << stringtemp << "\n";
        cout << endl;
        cout << "Please type your order. \n\n";
        cout << left << setw(40) << "Orders " << setw(33) << "Price" << "Stock Left" << endl;
        cout << left << setw(40) << "\n[1]: Burger, Fries, Soda " << " P" << setw(35) << price[0] << setw(25) << actual[0] << endl;
        cout << left << setw(40) << "[2]: Chicken, Spaghetti, Soda " << "P" << setw(35) << price[1] << setw(25) << actual[1] << endl;
        cout << left << setw(40) << "[3]: Chicken, Rice, Soda " << "P" << setw(35) << price[2] << setw(25) << actual[2] << endl;
        cout << left << setw(40) << "[4]: Burger stake, Rice, Soda " << "P" << setw(35) << price[3] << setw(25) << actual[3] << endl;
        cout << left << setw(40) << "[5]: Fish Fillet, Rice, Soda " << "P" << setw(35) << price[4] << setw(25) << actual[4] << endl;
        cout << "[X]: Finalize Order\n";
        cout << "[V]: Void Order\n";

    }

    int IntValidation2(int inttemp) { //validation for order quantity input
        while ((cin.fail()) || temp - inttemp < 0)
        {
            system("CLS");
            cout << "Quantity input is invalid. Please try again. " << endl;
            system("pause");
            system("CLS");
            printmenu();
            cout << "\nOrder No: " << orderinput;
            cout << "\nQuantity: ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> inttemp;
        }
        return inttemp;
    }

    int IntValidation3(int inttemp, int temp) { //validation for void quantity input

        while ((cin.fail()) || temp - inttemp < 0)
        {
            system("CLS");
            cout << "Quantity input is invalid. Please try again. " << endl;
            system("pause");
            system("CLS");
            cout << "\nCurrent Orders: " << endl;
            for (int i = 0; i < 5; i++) {

                cout << "Order No. " << i + 1 << "\tQuantity: " << orderamount[i] << "\tPrice: Php " << price[i] << "\tCost: Php " << price[i] * orderamount[i] << endl;
                total_cost += (price[i] * orderamount[i]);


            }
            cout << "\nGive order number to void. Send [X] to stop voiding process.";
            cout << "\nOrder No: " << orderinput;
            cout << "\nQuantity: ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> inttemp;
        }
        return inttemp;
    }

    float FloatValidation(float floattemp) //validation for payment input
    {
        //data type validation
        while ((cin.fail()) || floattemp < total_cost)
        {
            cout << "\nInvalid input or insufficient amount. Please try again. " << endl;
            system("pause");
            system("CLS");
            cout << "MCJOLLIBEE\n";
            cout << "Lipa City, Batangas\n";
            cout << "\nTotal: Php " << total_cost << endl;
            cout << "Cash Payment: ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> floattemp; //reentry of input, process repeats if the value given to cin fails the condition
        }
        return floattemp;
    }

    char CharValidation(char chartemp) //validation for cashier menu option input
    {
        do { //Option to inquire more or not loop, uses do-while loop
            chartemp = tolower(chartemp);
            if (chartemp != 'a' && chartemp != 'b') {
                system("CLS");
                cout << "Invalid. Please try again. " << endl;
                system("pause");
                system("CLS");
                cin.clear();
                cin.ignore(123, '\n');
                cout << "MCJOLLIBEE\n";
                cout << "Lipa City, Batangas\n";
                cout << "Welcome, Cashier " << stringtemp << "\n";
                cout << endl;

                cout << "Choose from the selection: " << endl;
                cout << "[A] Create Order" << endl;
                cout << "[B] Logout" << endl;
                cout << "Option: ";
                cin >> chartemp;
            }
        } while (chartemp != 'a' && chartemp != 'b');
        system("CLS");
        return chartemp; //return
    }

    char CharValidation2(char chartemp2) //validation for void menu option input
    {
        do { //Option to inquire more or not loop, uses do-while loop
            chartemp2 = tolower(chartemp2);
            if (chartemp2 != 'a' && chartemp2 != 'b') {
                system("CLS");
                cout << "Invalid. Please try again. " << endl;
                system("pause");
                system("CLS");
                cin.clear();
                cin.ignore(123, '\n');
                cout << "\nChoose from the selection: " << endl;
                cout << "[A] Void specific orders" << endl;
                cout << "[B] Void all orders" << endl;
                cout << "Option: ";
                cin >> chartemp2;
            }
        } while (chartemp2 != 'a' && chartemp2 != 'b');
        system("CLS");
        return chartemp2; //return
    }

    void additionalorders() { //private method to provide additional orders

        bool loop;
        char choice;

        do {
            cin.clear();
            cin.ignore(123, '\n');
            if (ordercount > 0) {
                cout << "\nYou have " << ordercount << " orders with soda drinks. Choose from 0 - " << ordercount << " drinks that you want to upsize to large (additional P30 each). \nOption: ";
                cin >> additional[0];
            }
        } while (additional[0] < 0 || additional[0] > ordercount || cin.fail());

        do {
            cin.clear();
            cin.ignore(123, '\n');
            if (orderamount[0] > 0) {
                cout << "\nYou have " << orderamount[0] << " orders with fries. Choose from 0 - " << orderamount[0] << " fries that you want to upsize to large (additional P40 each). \nOption: ";
                cin >> additional[1];
            }
        } while (additional[1] < 0 || additional[1] > orderamount[0] || cin.fail());

        loop = true;
        while (loop) {
            cout << "\nAny additional ala carte orders? \n[A] Fries (P30 each) \n[B] Drinks (P20 each) \n[C] No More Additional \nOption: ";
            cin >> choice;

            if (choice == 'a' || choice == 'b' || choice == 'c') {
                choice = toupper(choice);
            }

            switch (choice) {
            case 'A':
                cout << "\nEnter the amount: ";
                cin >> additional[2];
                while (cin.fail()) {
                    cout << "\nInvalid. Please try again. " << endl;
                    cin.clear();
                    cin.ignore(123, '\n');
                    cout << "\nEnter the amount: ";
                    cin >> additional[2];
                }
                break;
            case 'B':
                cout << "\nEnter the amount: ";
                cin >> additional[3];
                while (cin.fail()) {
                    cout << "\nInvalid. Please try again. " << endl;
                    cin.clear();
                    cin.ignore(123, '\n');
                    cout << "\nEnter the amount: ";
                    cin >> additional[3];
                }
                break;
            case 'C':
                loop = false;
                break;
            default:
                cout << "\nInput is invalid. Please try again. " << endl;
            }

        }

    }


public:

    void setemployeename(string name) { //manager's use of virtual function setemployeename()
        stringtemp = name;
    }

    void menuselection() { //method for Cashier menu selection

        cout << "MCJOLLIBEE\n";
        cout << "Lipa City, Batangas\n";
        cout << "Welcome, Cashier " << stringtemp << "\n";
        cout << "\nSystem loading. Please wait.\n";

        system("CLS");
        cout << "MCJOLLIBEE\n";
        cout << "Lipa City, Batangas\n";
        cout << "Welcome, Cashier " << stringtemp << "\n";
        cout << endl;

        cout << "Choose from the selection: " << endl;
        cout << "[A] Create Order" << endl;
        cout << "[B] Logout" << endl;
        cout << "Option: ";
        cin >> chartemp;
        chartemp = CharValidation(chartemp);

        if (chartemp == 'b') {
            cout << "MCJOLLIBEE\n";
            cout << "Lipa City, Batangas\n";
            cout << "\nCashier " << stringtemp << " has logged out." << endl;
            system("pause");
        }

    }

    char getselectionvalue() { //accessor for cashier menu selection option
        return chartemp;
    }

    void customerorderselect() { //method for selecting order options

        bool order_loop = true, order_loop2 = true;

        while (order_loop) {

            order_loop2 = true;
            while (order_loop2) {
                system("CLS");

                printmenu();

                cout << "\nOrder No: ";
                cin.clear();
                cin.ignore(123, '\n');
                cin >> orderinput;
                temp = orderinput - '0'; //converts char to int
                temp = actual[temp - 1];

                if (orderinput == 'x' || orderinput == 'v') {
                    orderinput = toupper(orderinput);
                    order_loop2 = false;
                }
                else if ((temp > 0 && temp < 6) || temp <= 0) {
                    cout << "\nWrong order input or there are no more stock for this meal. Provide a different input, or exit the process with [X]." << endl;
                    system("pause");
                }
                else {
                    order_loop2 = false;
                }
            }

            switch (orderinput) {
            case '1':
                cout << "Quantity: ";
                cin >> quantity;
                inttemp = quantity;
                quantity = IntValidation2(inttemp);
                orderamount[0] += quantity;
                ordercount += quantity;
                sales[0] += quantity;
                actual[0] = actual[0] - quantity;
                break;

            case '2':
                cout << "Quantity: ";
                cin >> quantity;
                inttemp = quantity;
                quantity = IntValidation2(inttemp);
                orderamount[1] += quantity;
                ordercount += quantity;
                sales[1] += quantity;
                actual[1] = actual[1] - quantity;
                break;

            case '3':
                cout << "Quantity: ";
                cin >> quantity;
                inttemp = quantity;
                quantity = IntValidation2(inttemp);
                orderamount[2] += quantity;
                ordercount += quantity;
                sales[2] += quantity;
                actual[2] = actual[2] - quantity;
                break;

            case '4':
                cout << "Quantity: ";
                cin >> quantity;
                inttemp = quantity;
                quantity = IntValidation2(inttemp);
                orderamount[3] += quantity;
                ordercount += quantity;
                sales[3] += quantity;
                actual[3] = actual[3] - quantity;
                break;

            case '5':
                cout << "Quantity: ";
                cin >> quantity;
                inttemp = quantity;
                quantity = IntValidation2(inttemp);
                orderamount[4] += quantity;
                ordercount += quantity;
                sales[4] += quantity;
                actual[4] = actual[4] - quantity;
                break;
            case 'X':
                order_loop = false;
                void_condition = false;
                break;
            case 'V':
                order_loop = false;
                void_condition = true;
                break;
            default:
                system("CLS");
                cout << "Order Input is invalid. Please try again. " << endl;
                system("pause");
                system("CLS");

            }

        }
    }

    bool getvoidcondition() { //accessor to get whether order goes to void menu or not
        return void_condition;
    }

    void setvoidselection() { //method for void menu

        int temp = 0, tempactual[5]{};
        char chartemp2;
        system("CLS");
        cout << "\nChoose from the selection: " << endl;
        cout << "[A] Void specific orders" << endl;
        cout << "[B] Void all orders" << endl;
        cout << "Option: ";
        cin >> chartemp2;
        chartemp2 = CharValidation2(chartemp2);

        if (chartemp2 == 'a') { // [A] Void specific orders

            int voidloop = true, voidloop2;

            while (voidloop) {

                voidloop2 = true;
                while (voidloop2) {
                    system("CLS");

                    cout << "\nCurrent Orders: " << endl; // Displays current order quantities
                    for (int i = 0; i < 5; i++) {

                        cout << "Order No. " << i + 1 << "\tQuantity: " << orderamount[i] << "\tPrice: Php " << price[i] << "\tCost: Php " << price[i] * orderamount[i] << endl;

                    }

                    cout << "\nGive order number to void. Send [X] to stop voiding process.";
                    cout << "\nOrder No: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                    cin >> orderinput;
                    temp = orderinput - '0'; //converts char to int
                    temp = orderamount[temp - 1];

                    if (orderinput == 'x') {
                        orderinput = toupper(orderinput);
                        voidloop2 = false;
                    }
                    else if (temp == 0) {
                        cout << "\nWrong input or there are no orders for this meal. Provide a different input, or exit the process with [X]." << endl;
                        system("pause");
                    }
                    else {
                        voidloop2 = false;
                    }
                }

                switch (orderinput) {
                case '1':
                    cout << "Quantity: ";
                    cin >> quantity;
                    inttemp = quantity;
                    quantity = IntValidation3(inttemp, temp);
                    orderamount[0] -= quantity;
                    ordercount -= quantity;
                    sales[0] -= quantity;
                    actual[0] = actual[0] + quantity;
                    break;

                case '2':
                    cout << "Quantity: ";
                    cin >> quantity;
                    inttemp = quantity;
                    quantity = IntValidation3(inttemp, temp);
                    orderamount[1] -= quantity;
                    ordercount -= quantity;
                    sales[1] -= quantity;
                    actual[1] = actual[1] + quantity;
                    break;

                case '3':
                    cout << "Quantity: ";
                    cin >> quantity;
                    inttemp = quantity;
                    quantity = IntValidation3(inttemp, temp);
                    orderamount[2] -= quantity;
                    ordercount -= quantity;
                    sales[2] -= quantity;
                    actual[2] = actual[2] + quantity;
                    break;

                case '4':
                    cout << "Quantity: ";
                    cin >> quantity;
                    inttemp = quantity;
                    quantity = IntValidation3(inttemp, temp);
                    orderamount[3] -= quantity;
                    ordercount -= quantity;
                    sales[3] -= quantity;
                    actual[3] = actual[3] + quantity;
                    break;

                case '5':
                    cout << "Quantity: ";
                    cin >> quantity;
                    inttemp = quantity;
                    quantity = IntValidation3(inttemp, temp);
                    orderamount[4] -= quantity;
                    ordercount -= quantity;
                    sales[4] -= quantity;
                    actual[4] = actual[4] + quantity;
                    break;
                case 'X':
                    voidloop = false;
                    cout << endl;
                    break;
                default:
                    system("CLS");
                    cout << "Order Input is invalid. Please try again. " << endl;
                    system("pause");
                    system("CLS");

                }

            }

            void_condition2 = false;
        }
        else if (chartemp2 == 'b') { //[B] Void All orders

            // this for loop is for resetting all orders should customer void all orders
            for (int i = 0; i < 5; i++) {
                orderamount[i] = 0;
                sales[i] = 0;
                actual[i] = 100;
            }
            ordercount = 0;
            void_condition2 = false;

        }

    }

    bool getvoidcondition2() { //accessor for 2nd void condition that allows if transaction is going to be processed and paid or repeat back to the order menu 
        return void_condition2;
    }

    void printsummary() { //method that prints out overall summary of orders

        total_cost = 0;

        additionalorders(); //private method for additional orders

        total_cost = (additional[0] * 30) + (additional[1] * 40) + (additional[2] * 30) + (additional[3] * 20);

        system("CLS");

        cout << "MCJOLLIBEE\n";
        cout << "Lipa City, Batangas\n";

        cout << "\nSummary of Orders: " << endl;
        for (int i = 0; i < 5; i++) {

            cout << "Order No. " << i + 1 << "\tQuantity: " << orderamount[i] << "\tPrice: Php " << price[i] << "\tCost: Php " << price[i] * orderamount[i] << endl;
            total_cost += (price[i] * orderamount[i]);
        }

        cout << "\nNumber of Upsized Drinks: " << additional[0] << "\tPrice: Php " << additional[0] * 30 << endl;
        cout << "\nNumber of Upsized Fries: " << additional[1] << "\tPrice: Php " << additional[1] * 40 << endl;
        cout << "\nAla Carte Fries: " << additional[2] << "\tPrice: Php " << additional[2] * 30 << endl;
        cout << "\nAla Carte Drinks: " << additional[3] << "\tPrice: Php " << additional[3] * 20 << endl;

        cout << endl << "Total: Php " << total_cost << endl;
        cout << endl;
        system("pause");
        system("CLS");

    }

    void managepayment() { //method that manages payment

        cout << "MCJOLLIBEE\n";
        cout << "Lipa City, Batangas\n";
        cout << "\nTotal: Php " << total_cost << endl;
        cout << "Cash Payment: Php ";
        cin >> payment;
        floattemp = payment;
        payment = FloatValidation(floattemp);

        change = payment - total_cost;

        cout << "\n Payment confirmed. Please check your receipt." << endl;
        cout << endl;
        system("pause");
    }

    void getorderamount(int arr[]) { //mutator that get variable values from cashier to manager, also generates waste value of each order after each order session

        for (int i = 0; i < 5; i++) {
            if (actual[i] > 10) {
                waste[i] = (rand() % (actual[i] / 10));
            }
            else {
                waste[i] = (rand() % 2);
            }
        }

        for (int i = 0; i < 5; i++) {

            arr[i] += orderamount[i];
            arr[i + 5] += sales[i];
            if (waste[i] > actual[i]) {
                waste[i] = actual[i];
            }
            arr[i + 10] += waste[i];
            arr[i + 15] = actual[i] - waste[i];
            if (arr[i + 15] < 0) {
                arr[i + 15] = 0;
            }
        }

    }

    void returnorderamount(int arr[]) {  //mutator that get variable values to cashier from manager, 

        for (int i = 0; i < 5; i++) {

            sales[i] = arr[i + 5];
            waste[i] = arr[i + 10];
            actual[i] = arr[i + 15];
        }

    }

    void generateRecieptfile(string name) { //method that generates reciept file
        time_t today = time(0);
        char* t = ctime(&today);

        int OR_num = (rand() % 899999) + 100000;

        bool isFirst = true;
        string orderDescription[] = { "", "Burger, Fries, Soda", "Chicken, Spaghetti, Soda", "Chicken, Rice, Soda", "Burger stake, Rice, Soda", "Fish Fillet, Rice, Soda" };
        string orderDescription2[] = { "Upsized Drinks", "Upsized Fries", "Ala Carte Fries", "Ala Carte Drinks" };
        int additionalpricing[4] = { 30, 40, 30, 20 };
        fstream receiptTextFile;

        for (int i = 0; i < 5; i++) {
            if (isFirst)
            {
                ofstream receiptPrinter("receipt.txt");
                if (!receiptPrinter.is_open())
                {
                    cout << "receipt cannot be made";
                    system("pause");
                    exit(1);
                }
                receiptPrinter.close();
            }

            receiptTextFile.open("receipt.txt", ios::app);
            if (!receiptTextFile.is_open())
            {
                cout << "Receipt cannot be opened";
                system("pause");
                exit(1);
            }
            else
            {
                if (isFirst)
                {
                    receiptTextFile << "\t\t    MCJOLLIBEE" << endl;
                    receiptTextFile << "\t       Lipa City, Batangas" << endl;
                    receiptTextFile << "\t\t     Receipt" << endl << endl;
                    receiptTextFile << setw(50) << setfill('_') << "" << endl;
                    receiptTextFile << setfill(' ') << endl;
                    receiptTextFile << "\tReceipt Number: " << 0 << OR_num << endl;
                    receiptTextFile << "\tCashier: " << name << endl;
                    receiptTextFile << "\tDate: " << t << endl;
                    receiptTextFile << setw(50) << setfill('_') << "" << endl;
                    receiptTextFile << setfill(' ') << endl;
                    receiptTextFile << left << setw(5) << "Qty" << setw(30) << "Item" << setw(30) << "Cost" << endl << endl;
                }
                receiptTextFile.close();
                receiptTextFile.open("receipt.txt", ios::app);
                receiptTextFile << setprecision(2) << fixed;
                if (orderamount[i] > 0)
                {
                    receiptTextFile << left << setw(5) << orderamount[i] << setw(30) << orderDescription[i + 1] << setw(30) << price[i] * orderamount[i] << endl;
                }

                receiptTextFile.close();
            }
            isFirst = false;
        }

        for (int i = 0; i < 4; i++) {
            ofstream receiptTextFile2;
            receiptTextFile2.open("receipt.txt", ios::app);
            receiptTextFile2 << setprecision(2) << fixed;


            if (additional[i] > 0) {
                receiptTextFile2 << left << setw(5) << additional[i] << setw(30) << orderDescription2[i] << setw(30) << float(additional[i] * additionalpricing[i]) << endl;
            }

            receiptTextFile.close();
        }

        receiptTextFile.open("receipt.txt", ios::app);
        receiptTextFile << setprecision(2) << fixed;
        receiptTextFile << setw(50) << setfill('_') << "" << endl;
        receiptTextFile << setfill(' ') << endl;
        receiptTextFile << left << setw(35) << "Total: " << setw(30) << total_cost << endl;
        receiptTextFile << left << setw(35) << "Payment: " << setw(30) << payment << endl;
        receiptTextFile << left << setw(35) << "Change: " << setw(30) << change << endl << endl << endl;
        receiptTextFile << "\tThank You Please Come Again" << endl;
        receiptTextFile << setw(50) << setfill('_') << "" << endl;
        receiptTextFile << setfill(' ');
        receiptTextFile.close();
        ordercount = 0;
        for (int i = 0; i < 5; i++) {

            orderamount[i] = 0;
            additional[i] = 0;

        }
    }

};

int main()
{
    Cashier ServiceFunctions;
    Manager ManageFunctions;
    Employee PINLogin;
    Employee* Employee1 = &ServiceFunctions;
    Employee* Employee2 = &ManageFunctions;
    Inventory* Inventory1 = &ServiceFunctions;
    Inventory* Inventory2 = &ManageFunctions;

    int stock_mutator[20] = { 0 };

    srand(time(NULL));
    bool repeat = true;
    while (repeat == true) {
        char main_selection;

        system("CLS");
        cout << "MCJOLLIBEE\n";
        cout << "Lipa City, Batangas\n";
        cout << "\nPlease Select an option:\n";
        cout << "[1] Login Employee\n[2] Exit\n\nOption: ";
        cin >> main_selection;

        switch (main_selection) {
        case '1': {

            string employeename;
            int inputpin;
            bool orderloop, orderloop2;

            cin.clear();
            cin.ignore(256, '\n');
            system("CLS");
            cout << "MCJOLLIBEE\n";
            cout << "Lipa City, Batangas\n";
            cout << "Enter Employee Name: ";
            getline(cin, employeename);
            cout << "INPUT YOUR 6 DIGIT PIN (177013 - Cashier PIN; 265198 - Manager PIN): ";
            cin >> inputpin;
            PINLogin.setPINinput(inputpin, employeename);

            orderloop = true;

            while (orderloop) {
                if (PINLogin.getPINinput() == 177013) {

                    Employee1->setemployeename(employeename);
                    Employee1->menuselection();
                    orderloop2 = true;
                    if (ServiceFunctions.getselectionvalue() == 'b') {
                        orderloop2 = false;
                        orderloop = false;
                    }

                    while (orderloop2) {

                        ServiceFunctions.customerorderselect();
                        if (ServiceFunctions.getvoidcondition() == true) {
                            ServiceFunctions.setvoidselection();
                            ManageFunctions.confirmation();
                        }
                        else if (ServiceFunctions.getvoidcondition() == false && ServiceFunctions.getvoidcondition2() == false) {
                            ServiceFunctions.printsummary();
                            ServiceFunctions.managepayment();
                            Inventory1->getorderamount(stock_mutator);
                            Inventory2->getorderamount(stock_mutator);
                            ServiceFunctions.generateRecieptfile(employeename);
                            orderloop2 = false;
                        }
                    }
                }
                else if (PINLogin.getPINinput() == 265198) {
                    Employee2->setemployeename(employeename);
                    Employee2->menuselection();
                    orderloop = false;
                    Inventory2->returnorderamount(stock_mutator);
                    Inventory1->returnorderamount(stock_mutator);

                }

            }

            break;
        }
        case '2': {
            exit(0);
            break;
        }
        default: {
            system("cls");
            cout << "Input is invalid please try again\n\n";
            system("pause");
            break;
        }
        }

    }

}
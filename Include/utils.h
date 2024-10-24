#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "./product.h"
#include "./roles.h"
#include "./greet.h"
#include "./error.h"
#include <ctime>
#include <cstdlib>
#include <limits>
using namespace std;

//
void GenerateBill(vector<Product> &Products);

void GenerateAdminBill();

// General Greeting Function
// void GeneralGreeting();
void GeneralGreeting();

// To show the Custom Messages
void CustomMessage(string Message);

// To open File According to Role
ifstream OpenFileForRole(const int Role);

// To check if the Given Username ansd Password is valid Or Not
// if Exists then True
// if not Exists then False
bool IsValidUser(string Username, string Password, const int Role);

// To check if the New Username is Unique or not
// if unique then True
// if not then False
// if it matches to the ignore then it is counted as unique
bool IsUniqueUsername(string Username, int Role, string Ignore = "");

// To chec that the both passwords are same or not
bool EqualPassword(string Password1, string Password2);

// To check that the given Salary is valid or not
bool IsValidSalary(int Salary);

// To check that the given Price is valid or not
bool IsValidPrice(int Price);

// TO check that the given Qty is valid or not
bool IsValidQty(int Qty);

// if unique then True
// if not then False
bool IsUniqueProduct(const string ProductName, string Ignore = "");

// SignIn Function for various Roles
void SignIn(const int Auth);

// self SignUp Function available only for Customer
void SignUp();

// To check that the given contact number is valid or not
bool IsValidContact(const string Contact);

// To check that the given gender is valid or not
bool IsValidGender(const char Gender);

// For Adding Customer Function
void AddCustomer(const Customer C);

// To Purchasd A product
void PurchaseProduct();

// General Menu Function
void GeneralMenu();

// Customer Menu
void CustomerMenu();

// Employee Menu
void EmployeeMenu();

// Admin Menu
void AdminMenu();

#endif

const string GeneralGreet = "Welcome to A-Z Store! We are thrilled to have you with us today. Feel free to explore and let us know how we can assist you!";

void GeneralGreeting()
{
    cout << endl;
    cout << "--------------------- A-Z store ---------------------" << endl;
    cout << GeneralGreet << endl;
    cout << "-----------------------------------------------------" << endl;
}

void CustomMessage(string Message)
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << Message << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

ifstream OpenFileForRole(const int Role)
{
    ifstream file;
    switch (Role)
    {
    case 1:
        file.open("./LoginData/Customer.txt", ios::in);
        break;
    case 2:
        file.open("./LoginData/Employee.txt", ios::in);
        break;
    case 3:
        file.open("./LoginData/Admin.txt", ios::in);
        break;
    default:
        throw Error(3);
    }
    return file;
}

vector<Product> ExtractProduct()
{
    vector<Product> Products;
    try
    {
        ifstream ProductDetails("./Product/Product.txt", ios::in);

        if (!ProductDetails.is_open())
        {
            throw Error(3);
        }

        string Name;
        int Price;
        int Qty;

        while (ProductDetails >> Name >> Price >> Qty)
        {
            Product newProduct(Name, Price, Qty);
            Products.push_back(newProduct);
        }
        ProductDetails.close();
        return Products;
    }
    catch (Error E)
    {
        E.ShowError();
    }
    catch (...)
    {
        Error E(4);
        E.ShowError();
    }

    return Products;
}

bool IsValidUser(string Username, string Password, const int Role)
{
    ifstream file = OpenFileForRole(Role);
    string Uname, Pword;
    try
    {
        while (file >> Uname >> Pword)
        {
            if (Uname == Username && Pword == Password)
            {
                file.close();
                return true; // Username and Password Matched.
            }
        }

        if (file.is_open())
        {
            file.close();
        }
        return false; // Username or Password not Matched.
    }
    catch (...)
    {
        Error E(0);
        E.ShowError();
    }
    if (file.is_open())
    {
        file.close();
    }
    return false; // Operation Failed.
}

bool IsUniqueUsername(string Username, int Role, string Ignore)
{
    ifstream file = OpenFileForRole(Role);
    string Uname, Pword;

    try
    {
        while (file >> Uname >> Pword)
        {
            if ((Uname == Username))
            {
                if (Uname == Username)
                {
                    // If Ignore is empty, or Ignore doesn't match the username, return false
                    if (Ignore.empty() || Ignore != Uname)
                    {
                        CustomMessage("Username already exists..!\nRe-Set Username..!");
                        file.close();
                        return false; // Username already exists
                    }
                }
            }
        }
        file.close();
        return true; // Username is Unique.
    }
    catch (Error E)
    {
        E.ShowError();
    }
    catch (...)
    {
        Error E(0);
        E.ShowError();
    }
    file.close();
    return false; // Operation Failed.
}

bool EqualPassword(string Password1, string Password2)
{
    if (Password1 == Password2)
    {
        return true;
    }
    CustomMessage("Both Password Must be same...!");
    return false;
}

bool IsUniqueProduct(const string ProductName, const string Ignore)
{
    vector<Product> Products = ExtractProduct();
    for (auto &P : Products)
    {
        if (P.Getname() == ProductName)
        {
            // If Ignore is empty or doesn't match the product name, the product already exists
            if (Ignore.empty() || P.Getname() != Ignore)
            {
                CustomMessage("Product already exists...!\nRe-Enter a unique name...!");
                return false; // Product already exists
            }
        }
    }
    return true; // Product is unique
}

void SignIn(const int Auth)
{
    cout << endl;
    string Username, Password;

    int Flag = 0;
    system("cls");
    while (Flag != 1)
    {

        cout << "--------------------------- SignIn ---------------------------" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "Enter Username : ";
        cin >> Username;
        cout << "Enter Password : ";
        cin >> Password;
        cout << "------------------------------------------------------------" << endl;

        if (IsValidUser(Username, Password, Auth))
        {
            Flag = 1;
        }
        else
        {
            CustomMessage("Username or Password doesn't matched..!\nSignIn failed...!");
        }
    }

    CustomMessage("SignIn Successfully...!");
    cout << "--------------------------------------------------------------" << endl;
}

Customer AddCustomerwithIgnore(string Ignore)
{

    string Username, Password1, Password2, Name, Contact;
    char Gender;

    cout << "------------------------------" << endl;
    cout << "Enter Name : ";
    cin >> Name;
    cout << "------------------------------" << endl;

    do
    {
        cout << "------------------------------" << endl;
        cout << "Enter Contact : ";
        cin >> Contact;
        cout << "------------------------------" << endl;
    } while (!IsValidContact(Contact));

    do
    {
        cout << "------------------------------" << endl;
        cout << "Enter Gender (M/F/N) : ";
        cin >> Gender;
        cout << "------------------------------" << endl;
    } while (!IsValidGender(Gender));

    do
    {
        cout << "------------------------------" << endl;
        cout << "Set Username : ";
        cin >> Username;
        cout << "------------------------------" << endl;

    } while (!IsUniqueUsername(Username, 1, Ignore));

    do
    {
        Password1 = "";
        Password2 = "";
        cout << "------------------------------" << endl;
        cout << "Set Password : ";
        cin >> Password1;
        cout << "------------------------------" << endl;
        cout << "Confirm Password : ";
        cin >> Password2;
        cout << "------------------------------" << endl;
    } while (!EqualPassword(Password1, Password2));

    Customer newCustomer(Username, Password1, Name, Gender, Contact);

    return newCustomer;
}

void SignUp()
{
    cout << "------------------------------ SignUp ------------------------------" << endl;

    string Ignore = "";
    Customer newCustomer = AddCustomerwithIgnore(Ignore);
    AddCustomer(newCustomer);

    CustomMessage("SignUp Succesfully...!");
    cout << "--------------------------------------------------------------------" << endl;
    SignIn(1);
}

bool IsValidContact(const string Contact)
{
    if (Contact.length() != 10)
    {
        CustomMessage("Invalid Contact Number...!");
        return false; // Invalid Length
    }

    for (int i = 0; i < 10; ++i)
    {
        if (!(Contact[i] >= '0' && Contact[i] <= '9'))
        {
            CustomMessage("Invalid Contact Number...!");
            return false; // Invalid Character
        }
    }
    return true; // Valid Gender
}

bool IsValidGender(const char Gender)
{

    if ((Gender == 'M') || (Gender == 'F') || (Gender == 'N'))
    {
        return true; // valid Gender
    }
    CustomMessage("Invalid Gender...!");
    return false; // Invalid input
}

bool IsValidSalary(int Salary)
{
    if (Salary > 0)
    {
        return true; // Valid Salary
    }

    CustomMessage("Invalid Salary...!");
    return false; // Invalid Salary
}

bool IsValidPrice(int Price)
{
    if (Price > 0)
    {
        return true; // Valid Price
    }

    CustomMessage("Invalid Price...!");
    return false;
}

bool IsValidQty(int Qty)
{
    if (Qty > 0)
    {
        return true; // Valid Quantity
    }

    CustomMessage("Invalid Quantity...!");
    return false;
}

vector<Customer> ExtractCustomer()
{
    vector<Customer> Customers;
    try
    {
        ifstream CustomerDetails("./UserData/Customer.txt");

        if (!CustomerDetails.is_open())
        {
            throw Error(3);
        }

        string Username, Password, Name, Contact;
        char Gender;

        while (CustomerDetails >> Username >> Password >> Name >> Gender >> Contact)
        {
            Customer newCustomer(Username, Password, Name, Gender, Contact);
            Customers.push_back(newCustomer);
        }
        return Customers;
    }
    catch (Error E)
    {
        E.ShowError();
    }
    catch (...)
    {
        Error E(4);
        E.ShowError();
    }

    return Customers;
}

void AddCustomer(vector<Customer> &Customers)
{
    ofstream CustomerLogin("./LoginData/Customer.txt");
    ofstream CustomerDetails("./UserData/Customer.txt");

    CustomerLogin << left;
    CustomerDetails << left;

    for (auto &C : Customers)
    {
        CustomerLogin << setw(8) << C.GetUsername() << "\t" << setw(8) << C.GetPassword() << "\t" << endl;

        CustomerDetails << setw(8) << C.GetUsername() << "\t" << setw(8) << C.GetPassword() << "\t" << setw(20) << C.Name << "\t" << setw(5) << C.Gender << "\t" << setw(10) << C.Contact << "\t" << endl;
    }
}

void AddCustomer(Customer newCustomer)
{
    string Username = newCustomer.GetUsername();
    if (IsUniqueUsername(Username, 1))
    {
        vector<Customer> Customers = ExtractCustomer();
        Customers.push_back(newCustomer);
        AddCustomer(Customers);
    }
}

void AddCustomerMenu()
{
    char Flag = 'Y';

    while (Flag == 'Y' || Flag == 'y')
    {

        vector<Customer> Customers = ExtractCustomer();
        DisplayCustomer(Customers);
        int Number = 0;
        string Ignore = "";
        Customer newCustomer = AddCustomerwithIgnore(Ignore);
        Customers.push_back(newCustomer);
        AddCustomer(Customers);

        cout << "Do you want to Add another Customer Details (Y/N) : ";
        cin >> Flag;
    }
}

void DisplayCustomer(vector<Customer> &Customers)
{
    cout << left;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << setw(3) << "No." << "\t" << setw(8) << "Username" << "\t" << setw(20) << "Name" << "\t" << setw(5) << "Gender" << "\t" << setw(10) << "Contact" << "\t" << endl;
    cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

    cout << left;
    for (int i = 0; i < Customers.size(); ++i)
    {
        cout << setw(3) << (i + 1) << "\t" << setw(8) << Customers[i].GetUsername() << "\t" << setw(20) << Customers[i].Name << "\t" << setw(5) << Customers[i].Gender << "\t" << setw(10) << Customers[i].Contact << "\t" << endl;
    }
    cout << "--------------------------------------------------------------------------" << endl;
    cout << endl;
}

void EditCustomer()
{
    char Flag = 'Y';

    while (Flag == 'Y' || Flag == 'y')
    {

        vector<Customer> Customers = ExtractCustomer();
        DisplayCustomer(Customers);
        int Number = 0;

        do
        {
            cout << "which Customer details do you want to edit : ";
            cin >> Number;
        } while (!(Number > -1 && Number < Customers.size()));

        string Ignore = Customers[Number - 1].GetUsername();

        Customer newCustomer = AddCustomerwithIgnore(Ignore);

        Customers[Number - 1] = newCustomer;

        AddCustomer(Customers);

        cout << "Do you want to Edit another Customer Details (Y/N) : ";
        cin >> Flag;
    }
}

Employee AddEmployee(string Ignore)
{
    string Username, Password1, Password2, Name, Contact;
    char Gender;
    int Salary;

    cout << "------------------------------" << endl;
    cout << "Enter Name : ";
    cin >> Name;
    cout << "------------------------------" << endl;

    do
    {
        cout << "------------------------------" << endl;
        cout << "Enter Contact : ";
        cin >> Contact;
        cout << "------------------------------" << endl;
    } while (!IsValidContact(Contact));

    do
    {
        cout << "------------------------------" << endl;
        cout << "Enter Gender (M/F/N) : ";
        cin >> Gender;
        cout << "------------------------------" << endl;
    } while (!IsValidGender(Gender));

    do
    {
        cout << "------------------------------" << endl;
        cout << "Set Username : ";
        cin >> Username;
        cout << "------------------------------" << endl;

    } while (!IsUniqueUsername(Username, 2, Ignore));

    do
    {
        Password1 = "";
        Password2 = "";
        cout << "------------------------------" << endl;
        cout << "Set Password : ";
        cin >> Password1;
        cout << "------------------------------" << endl;
        cout << "Confirm Password : ";
        cin >> Password2;
        cout << "------------------------------" << endl;
    } while (!EqualPassword(Password1, Password2));

    do
    {
        cout << "------------------------------" << endl;
        cout << "Enter Salary : ";
        cin >> Salary;
        cout << "------------------------------" << endl;
    } while (!IsValidSalary(Salary));

    Employee newEmployee(Username, Password1, Name, Gender, Contact, Salary);

    return newEmployee;
}

vector<Employee> ExtractEmployee()
{
    vector<Employee> Employees;
    try
    {
        ifstream EmployeeDetails("./UserData/Employee.txt");

        if (!EmployeeDetails.is_open())
        {
            throw Error(3);
        }

        string Username, Password, Name, Contact;
        char Gender;

        while (EmployeeDetails >> Username >> Password >> Name >> Gender >> Contact)
        {
            Employee newEmployee(Username, Password, Name, Gender, Contact);
            Employees.push_back(newEmployee);
        }
        return Employees;
    }
    catch (Error E)
    {
        E.ShowError();
    }
    catch (...)
    {
        Error E(4);
        E.ShowError();
    }
}

void AddEmployee(Employee newEmployee)
{

    string Username = newEmployee.GetUsername();
    if (IsUniqueUsername(Username, 2))
    {
        vector<Employee> Employees = ExtractEmployee();
        Employees.push_back(newEmployee);
        AddEmployee(Employees);
    }
}

void AddEmployee(vector<Employee> &Employees)
{
    ofstream EmployeeLogin("./LoginData/Employee.txt");
    ofstream EmployeeDetails("./UserData/Employee.txt");

    EmployeeLogin << left;
    EmployeeDetails << left;
    for (auto &E : Employees)
    {
        EmployeeLogin << setw(8) << E.GetUsername() << "\t" << setw(8) << E.GetPassword() << "\t" << endl;

        EmployeeDetails << setw(8) << E.GetUsername() << "\t" << setw(8) << E.GetPassword() << "\t" << setw(20) << E.Name << "\t" << setw(5) << E.Gender << "\t" << setw(10) << E.Contact << "\t" << endl;
    }
}

void DisplayEmployee(vector<Employee> &Employees)
{
    system("cls");
    cout << left;
    cout << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << setw(3) << "No." << "\t" << setw(8) << "Username" << "\t" << setw(20) << "Name" << "\t" << setw(5) << "Gender" << "\t" << setw(10) << "Contact" << "\t" << endl;
    cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    for (int i = 0; i < Employees.size(); ++i)
    {
        cout << setw(3) << (i + 1) << "\t" << setw(8) << Employees[i].GetUsername() << "\t" << setw(20) << Employees[i].Name << "\t" << setw(5) << Employees[i].Gender << "\t" << setw(10) << Employees[i].Contact << "\t" << endl;
    }
    cout << "--------------------------------------------------------------------------" << endl;
    cout << endl;
}

void EditEmployee()
{
    char Flag = 'Y';

    while (Flag == 'Y' || Flag == 'y')
    {

        vector<Employee> Employees = ExtractEmployee();
        DisplayEmployee(Employees);
        int Number = 0;

        do
        {
            cout << "which employee details do you want to edit : ";
            cin >> Number;
        } while (!(Number > -1 && Number < Employees.size()));

        string Ignore = Employees[Number - 1].GetUsername();

        Employee newEmployee = AddEmployee(Ignore);

        Employees[Number - 1] = newEmployee;

        AddEmployee(Employees);

        cout << "Do you want to Edit another Employee Details (Y/N) : ";
        cin >> Flag;
    }
}

void AddEmployeeMenu()
{
    char Flag = 'Y';

    while (Flag == 'Y' || Flag == 'y')
    {

        vector<Employee> Employees = ExtractEmployee();
        DisplayEmployee(Employees);
        int Number = 0;

        Employee newEmployee = AddEmployee("");
        Employees.push_back(newEmployee);
        AddEmployee(Employees);

        cout << "Do you want to Add another Employee Details (Y/N) : ";
        cin >> Flag;
    }
}

Product AddProduct(string Ignore)
{
    string Name;
    int Price, Qty;

    do
    {
        cout << "------------------------------" << endl;
        cout << "Enter Name : ";
        cin >> Name;
        cout << "------------------------------" << endl;
    } while (!IsUniqueProduct(Name, Ignore));

    do
    {
        cout << "------------------------------" << endl;
        cout << "Enter Price : ";
        cin >> Price;
        cout << "------------------------------" << endl;
    } while (!IsValidPrice(Price));

    do
    {
        cout << "------------------------------" << endl;
        cout << "Enter Quantity : ";
        cin >> Qty;
        cout << "------------------------------" << endl;
    } while (!IsValidQty(Qty));

    Product newProduct(Name, Price, Qty);

    return newProduct;
}

void AddProduct(Product newProduct)
{

    string ProductName = newProduct.Getname();
    if (IsUniqueProduct(ProductName))
    {
        vector<Product> Products = ExtractProduct();
        Products.push_back(newProduct);
        AddProduct(Products);
    }
}

void AddProduct(vector<Product> &Products)
{
    ofstream file("./Product/Product.txt", ios::out);

    try
    {
        if (!file.is_open())
        {
            throw Error(3);
        }

        for (auto &P : Products)
        {
            file << setw(10) << P.Getname() << "\t" << setw(6) << P.GetPrice() << "\t" << setw(3) << P.GetQty() << "\t" << endl;
        }
    }
    catch (Error E)
    {
        E.ShowError();
    }
    catch (...)
    {
        Error E(4);
        E.ShowError();
    }
}

void DisplayProduct(vector<Product> &Products)
{
    cout << left;
    cout << "-----------------------------------------------" << endl;
    cout << setw(3) << "No." << "\t" << setw(10) << "Product" << "\t" << setw(6) << "Price" << "\t" << setw(3) << "Quantity" << "\t" << endl;
    cout << "-----------------------------------------------" << endl;
    for (int i = 0; i < Products.size(); ++i)
    {
        cout << setw(3) << (i + 1) << "\t" << setw(10) << Products[i].Getname() << "\t" << setw(6) << Products[i].GetPrice() << "\t" << setw(3) << Products[i].GetQty() << "\t" << endl;
    }
    CustomMessage("* All Prices are in Indian Rupee...!");
}

void EditProduct()
{
    char Flag = 'Y';

    while (Flag == 'Y' || Flag == 'y')
    {
        system("cls");
        vector<Product> Products = ExtractProduct();
        DisplayProduct(Products);
        int Number = 0;

        do
        {
            cout << "which Product details do you want to edit : ";
            cin >> Number;

            if (Number < 0 || Number > Products.size())
            {
                CustomMessage("Invalid input...!");
            }

        } while (!(Number > -1 && Number < Products.size()));

        string Ignore = Products[Number - 1].Getname();

        Product newProduct = AddProduct(Ignore);

        Products[Number - 1] = newProduct;

        AddProduct(Products);

        cout << "Do you want to Edit another Product Details (Y/N) : ";
        cin >> Flag;
    }
}

void PurchaseProduct()
{
    system("cls");
    vector<Product> Products = ExtractProduct();
    vector<Product> Purchase;

    char Flag = 'Y';

    do
    {
        DisplayProduct(Products);
        int Number = 0;

        // Prompt user to select a product
        do
        {
            cout << "Enter the product number you want to purchase: ";
            cin >> Number;

            if ( Number < 1 || Number > Products.size() || Products[Number - 1].GetQty() == 0 )
            {
                CustomMessage("Invalid product number...!");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
                Number = 0;                                          // Reset invalid input
            }
        } while (Number < 1 || Number > Products.size());

        int Qty = 0;

        // Prompt user for quantity
        do
        {
            cout << "Enter quantity: ";
            cin >> Qty;

            if (cin.fail())
            {
                CustomMessage("Invalid input for quantity...!");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear invalid input
                Qty = 0;                                             // Reset invalid input
            }
            else if (Qty < 1)
            {
                CustomMessage("Invalid quantity...!");
            }
            else if (Qty > Products[Number - 1].GetQty())
            {
                CustomMessage("That much quantity is not available currently...!");
            }
        } while (Qty < 1 || Qty > Products[Number - 1].GetQty());

        // Adjust product quantity after purchase
        int NewQty = Products[Number - 1].GetQty() - Qty;
        Products[Number - 1].SetQty(NewQty);

        // Add the product to the purchase list
        string PurchaseName = Products[Number - 1].Getname();
        int PurchasePrice = Products[Number - 1].GetPrice();
        int PurchaseQty = Qty; // Corrected to store the quantity, not the product number

        Product NewPurchase(PurchaseName, PurchasePrice, PurchaseQty);
        Purchase.push_back(NewPurchase);

        // Ask if the user wants to purchase another product
        cout << "Want to purchase another product (Y/N): ";
        cin >> Flag;
        Flag = tolower(Flag); // Convert to lowercase for consistency

    } while (Flag == 'y' || Flag == 'Y');

    // Update the product list and generate a bill for the purchases
    AddProduct(Products);
    GenerateBill(Purchase);
}

void AddProductMenu()
{
    char Flag = 'Y';

    while (Flag == 'Y' || Flag == 'y')
    {

        vector<Product> Products = ExtractProduct();
        DisplayProduct(Products);
        int Number = 0;

        Product newProduct = AddProduct();
        Products.push_back(newProduct);
        AddProduct(Products);

        cout << "Do you want to Add another Product Details (Y/N) : ";
        cin >> Flag;
    }
}

void CustomerMenu()
{
    system("cls");
    char Flag = 'Y';

    cout << "Already Customer...? (Y/N) : ";
    cin >> Flag;

    if (Flag == 'Y' || Flag == 'y')
    {
        SignIn(1);
    }
    else if (Flag == 'N' || Flag == 'n')
    {
        SignUp();
    }
    else
    {
        cout << "Invalid Input...!";
        return;
    }

    system("cls");
    // Greet G(1);
    // G.Welcome();
    int Choice = 0;
    do
    {

        cout << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. View Product" << endl;
        cout << "2. Purchase Product" << endl;
        cout << "0. exit" << endl;
        cout << "----------------------------------------" << endl;

        cout << "Enter your Choice : ";
        cin >> Choice;

        vector<Product> Products;
        switch (Choice)
        {
        case 1:
            system("cls");
            Products = ExtractProduct();
            DisplayProduct(Products);
            break;

        case 2:
            system("cls");
            PurchaseProduct();
            break;

        case 0:
            system("cls");
            break;

        default:
            system("cls");
            CustomMessage("Invalid Input...!");
            break;
        }
    } while (Choice != 0);
}

void EmployeeMenu()
{
    system("cls");

    SignIn(2);
    system("cls");

    int Choice = 0;
    do
    {

        cout << "-------------------------" << endl;
        cout << "1. View Product" << endl;
        cout << "2. Add Product" << endl;
        cout << "3. Add Customer" << endl;
        cout << "4. Edit Customer" << endl;
        cout << "5. Edti Product" << endl;
        cout << "0. exit" << endl;
        cout << "-------------------------" << endl;
        cout << "Enter Choice : ";
        cin >> Choice;
        vector<Product> Products;
        switch (Choice)
        {
        case 1:
            system("cls");
            Products = ExtractProduct();
            DisplayProduct(Products);
            break;

        case 2:
            system("cls");
            AddProductMenu();
            break;

        case 3:
            system("cls");
            AddCustomerMenu();
            break;

        case 4:
            system("cls");
            EditCustomer();
            break;

        case 5:
            system("cls");
            EditProduct();
            break;

        case 0:
            system("cls");
            break;

        default:
            system("cls");
            CustomMessage("Invalid input...!");
            break;
        }
    } while (Choice != 0);
}

void AdminMenu()
{
    system("cls");

    SignIn(3);

    system("cls");

    int Role = 3;
    // Greet G(3);
    // G.Welcome();

    cout << endl;
    int choice;
    do
    {
        cout << "------------------------------" << endl;
        cout << "1. View Product" << endl;
        cout << "2. View Customer" << endl;
        cout << "3. View Employee" << endl;
        cout << "4. Add Product" << endl;
        cout << "5. Add Customer" << endl;
        cout << "6. Add Employee" << endl;
        cout << "7. Edit Product" << endl;
        cout << "8. Edit Customer" << endl;
        cout << "9. Edit Employee" << endl;
        cout << "0. exit" << endl;
        cout << "------------------------------" << endl;

        cout << endl;
        cout << "Enter Your choice : ";
        cin >> choice;
        vector<Product> Products;
        vector<Customer> Customers;
        vector<Employee> Employees;
        switch (choice)
        {
        case 1:
            Products = ExtractProduct();
            DisplayProduct(Products);
            break;
        case 2:
            Customers = ExtractCustomer();
            DisplayCustomer(Customers);
            break;
        case 3:
            Employees = ExtractEmployee();
            DisplayEmployee(Employees);
            break;

        case 4:
            AddProductMenu();
            break;
        case 5:
            AddCustomerMenu();
            break;
        case 6:
            AddEmployeeMenu();
            break;
        case 7:
            EditProduct();
            break;
        case 8:
            EditCustomer();
            break;
        case 9:
            EditEmployee();
            break;
        case 0:
            break;

        default:
            CustomMessage("Invalid Input...!");
        }

    } while (choice != 0);
    // G.GoodBye();
}

void GeneralMenu()
{
    // General Greeting Function Whoever visits the Store...!
    GeneralGreeting();

    int Choice = 0;
    do
    {
        cout << "--------------------" << endl;
        cout << "1. Customer " << endl;
        cout << "2. Employee" << endl;
        cout << "3. Admin" << endl;
        cout << "0. exit" << endl;
        cout << "--------------------" << endl;

        cout << "Enter your choice : ";
        cin >> Choice;

        Greet G;

        switch (Choice)
        {
        case 0:
            break;

        case 1:
            CustomerMenu();
            G.SetRole(1);
            G.GoodBye();
            break;

        case 2:
            EmployeeMenu();
            G.SetRole(2);
            G.GoodBye();
            break;
        case 3:
            AdminMenu();
            G.SetRole(3);
            G.GoodBye();
            break;

        default:
            CustomMessage("invalid Input...!");
            break;
        }

    } while (Choice != 0);
}

void GenerateBill(vector<Product> &Purchases)
{
    string CustomerName, CustomerContact;
    long int TotalPrice = 0;
    ofstream Bill("./Billing/Bill.txt", ios::out);

    cout << "Enter Name : ";
    cin >> CustomerName;

    do{
        cout << "Enter Contact : ";
        cin >> CustomerContact;
    }while(!IsValidContact(CustomerContact));

    Bill << "=============================================================" << endl;
    Bill << "------------------------- A-Z Store -------------------------" << endl;
    Bill << "=============================================================" << endl;
    Bill << left;
    Bill << "Date : " << setw(23) << __DATE__;
    Bill << right;
    Bill << setw(23) << "Time : " << __TIME__ << endl;
    Bill << left;
    Bill << "Name : " << CustomerName << endl;
    Bill << "Contact No. : " << CustomerContact << endl;
    Bill << "=============================================================" << endl;
    Bill << left;
    Bill << setw(3) << "No." << "\t" << setw(20) << "Product" << "\t" << setw(10) << "Price" << "\t" << setw(10) << "Qty" << "\t" << setw(9) << "Total" << endl;
    Bill << "=============================================================" << endl;
    for (int i = 0; i < Purchases.size(); ++i)
    {
        TotalPrice += (Purchases[i].GetPrice() * Purchases[i].GetQty());
        Bill << setw(3) << (i + 1) << "\t" << setw(20) << Purchases[i].Getname() << "\t" << setw(10) << Purchases[i].GetPrice() << "\t" << setw(10) << Purchases[i].GetQty() << "\t" << setw(9) << (Purchases[i].GetPrice() * Purchases[i].GetQty()) << endl;
    }
    Bill << "=============================================================" << endl;
    Bill << "=============================================================" << endl;
    Bill << setw(32) << "";
    Bill << "Total : " << TotalPrice << endl;
    Bill << "=============================================================" << endl;
    Bill << "------------------ Thank You ! Visit Again ------------------" << endl;
    Bill << "=============================================================" << endl;
    Bill.close();
    GenerateAdminBill();
    CustomMessage("Bill Generated Successfully...!");
}

void GenerateAdminBill()
{
    ifstream CustomerBill("./Billing/Bill.txt", ios::in);
    ofstream AdminBill("./Billing/BillAdmin.txt", ios::app);

    string str = "";

    while (getline(CustomerBill, str))
    {
        AdminBill << str;
        AdminBill << endl;
    }

    AdminBill << endl
              << endl;

    CustomerBill.close();
    AdminBill.close();
}
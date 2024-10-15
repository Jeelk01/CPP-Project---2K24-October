#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// Error Messages Array;
string ErrorMessage[5] = {"Error Occur...!", "Invalid Input...!", "Out of Bound...!", "File not Opened Properly...!", ""};

// General Welcome Greet
string GeneralGreet = "Welcome to A-Z Store! We are thrilled to have you with us today. Feel free to explore and let us know how we can assist you!";

// Welcome Greeting Message for Various Roles.
string WelcomeGreetMessage[3] = {"Welcome to A-Z store! We're excited to have you here. Enjoy exploring our offerings!", "Good morning, team! Welcome back! Let's make today productive and inspiring!", "Welcome, Admin! Your guidance is always appreciated. Let's get started on today's tasks!"};

// Goodbye Greeting Message for Various Roles.
string GoodbyeGreetMessage[3] = {"Thank you for visiting A-Z store! We hope to see you again soon. Happy shopping!", "Great job today, team! Have a wonderful evening, and see you tomorrow!", "Thanks for your hard work today, Admin! Have a great evening and see you next time!"};

// Error Object to handling Error occur during Program.
class Error
{
private:
    int code;

public:
    Error(int code = 0) : code(code) {}
    void ShowError()
    {
        cout << "----- Error -----" << endl;
        cout << ErrorMessage[code] << endl;
        cout << "-----------------" << endl;
    }
};

// Base class Person
class Person
{
private:
    string Username;
    string Password;

protected:
    string Name;
    char Gender;
    string Contact;

public:
    Person(string Username, string Password, string Name = "", char Gender = 'N', string Contact = "0000000000")
    {
        this->Username = Username;
        this->Password = Password;
        this->Name = Name;
        this->Gender = Gender;
        this->Contact = Contact;
    }
};

class Customer : public Person
{
private:
public:
    Customer(string Username, string Password, string Name = "", char Gender = 'N', string Contact = "0000000000") : Person(Username, Password, Name, Gender, Contact)
    {
    }
};

class Employee : public Person
{
private:
    int Salary;

public:
    Employee(string Username, string Password, string Name = "", char Gender = 'N', string Contact = "0000000000", int Salary = 0) : Person(Username, Password, Name, Gender, Contact)
    {
        this->Salary = Salary;
    }
};

class Admin : public Person
{
private:
public:
    Admin(string Username, string Password, string Name = "", char Gender = 'N', string Contact = "0000000000") : Person(Username, Password, Name, Gender, Contact)
    {
    }
};

class Product
{
private:
    string Name;
    int Price;
    int Quantity;

public:
    Product(string Name, int Price, int Quantity) : Name(Name), Price(Price), Quantity(Quantity) {}

    void Display() const
    {
        cout << setw(20) << Name << "\t" << setw(6) << Quantity << endl;
    }

    string Getname() const
    {
        return Name;
    }

    int GetPrice() const
    {
        return Price;
    }

    int GetQty() const
    {
        return Quantity;
    }
};
// Authentication
// 1. Customer
// 2. Employee
// 3. Admin

// General Greet Message
void GeneralGreeting()
{
    cout << endl;
    cout << "--------------------- A-Z store ---------------------" << endl;
    cout << GeneralGreet << endl;
    cout << "-----------------------------------------------------" << endl;
}

// greeting Function Base on Roles of visitors.
void Greeting(const int Role, int Flag)
{
    cout << endl;
    cout << "--------------------- A-Z store ---------------------" << endl;
    // Flag 1 --> Welcome Greet
    // else   --> GoodBye Greet
    if (Flag == 1)
    {
        cout << WelcomeGreetMessage[Role - 1] << endl;
    }
    else
    {
        cout << GoodbyeGreetMessage[Role - 1] << endl;
    }
    cout << "-----------------------------------------------------" << endl;
}

// if user exists as Customer , Employee or Admin it returns true.
bool isValid(string Username, string Password, const int Role)
{
    ifstream file;
    string Uname, Pword;
    if (Role == 1)
    {
        file.open("./UserData/Customer.txt", ios::in);
    }
    else if (Role == 2)
    {
        file.open("./UserData/Employee.txt", ios::in);
    }
    else if (Role == 3)
    {
        file.open("./UserData/Admin.txt", ios::in);
    }
    else
    {
        return false;
    }

    while (file >> Uname >> Pword)
    {
        if (Uname == Username && Pword == Password)
        {
            return true; // Username and Password Matched.
        }
    }

    return false; // Username or Password not Matched.
}

// for checking That the new username is already exist or not..?
// if username is unique then return true. else false.
bool IsUsernameAvailable(string Username, int Role)
{
    ifstream file;
    string Uname, Pword;

    if (Role == 1)
    {
        file.open("./UserData/Customer.txt", ios::in);
    }
    else if (Role == 2)
    {
        file.open("./UserData/Employee.txt", ios::in);
    }
    else if(Role == 3){
        file.open("./Userdata/Admin.txt",ios::in);
    }
    else
    {
        return false;
    }

    while (file >> Uname >> Pword)
    {
        if (Uname == Username)
        {
            return false; // Username is already exists.
        }
    }
    file.close();
    return true; // Username is unique.
}

// for checking if new product is already exists or not...?
// if pproduct is unique then return true else false/
bool IsProductAvailable(const vector<Product> Products, const Product newProduct)
{

    for (const auto &product : Products)
    {
        if (product.Getname() == newProduct.Getname())
        {
            return false;
            // Product is already Available.
        }
    }

    return true; // Product is Unique.
}

// SignIn function Available for all Roles
void SignIn(const int Auth)
{
    cout << left;
    string Username, Password;
    ifstream file;

    cout << "------------------------------ SignIn ------------------------------" << endl;
    do
    {
        cout << "Enter Username : ";
        cin >> Username;
        cout << "Enter Password : ";
        cin >> Password;

    } while (!isValid(Username, Password, Auth));

    cout << "--------------------------------------------------------------------" << endl;

    file.close();
}

// SignUp function available for only Customer.
void SignUp()
{
    cout << "------------------------------ SignUp ------------------------------" << endl;
    string Username, Password1, Password2;
    int FlagU = 0, FlagP = 0;
    do
    {
        cout << "Set Username : ";
        cin >> Username;
        if (IsUsernameAvailable(Username, 1))
        {
            FlagU = 1;
        }
        else
        {
            cout << "Username is already exist..!" << endl;
            cout << "Re-Set Usernme..!" << endl;
        }
    } while (FlagU != 1);

    do
    {
        cout << "Set Password : ";
        cin >> Password1;

        cout << "Confirm Password : ";
        cin >> Password2;

        if (Password1 == Password2)
        {
            FlagP = 1;
        }
        else
        {
            cout << "Both Password Must be same...!" << endl;
        }
    } while (FlagP != 1);

    cout << "SignUp Succesfully...!";
    cout << "--------------------------------------------------------------------" << endl;
    SignIn(1);
}

// Add Employee fucntionality available for only admins.
void AddEmployee()
{
    cout << "--------------------------- Add Employee ---------------------------" << endl;
    cout << "--------------------------------------------------------------------" << endl;
}

// Product listing function
void DisplayProduct(vector<Product> &P)
{
    cout << left;
    cout << "--------------------------- Product List ---------------------------" << endl;
    cout << setw(3) << "No." << "\t\t" << setw(20) << "Product" << "\t\t" << setw(6) << "Price" << "\t\t" << setw(3) << "Qty" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    for (int i = 0; i < P.size(); ++i)
    {
        cout << setw(3) << (i + 1) << "-" << "\t\t" << setw(20) << P[i].Getname() << "\t\t" << setw(6) << P[i].GetPrice() << "\t\t" << setw(3) << P[i].GetQty() << endl;
    }
    cout << "--------------------------------------------------------------------" << endl;
    cout << "* All Prices are in Indian Rupee" << endl;
    cout << "--------------------------------------------------------------------" << endl;
}

// Display Products Available for all Roles
vector<Product> ExtractProduct()
{
    vector<Product> P;
    ifstream ProductList("./Products/Product.txt", ios::in);
    string Name;
    int Price;
    int Quantity;

    while (ProductList >> Name >> Price >> Quantity)
    {
        Product Dummy(Name, Price, Quantity);
        P.push_back(Dummy);
    }
    ProductList.close();

    return P;
}

// Fucntionality available for both Admin and Employee
void AddProduct()
{
    vector<Product> P = ExtractProduct();

    int Flag = 0;
    while (Flag != 1)
    {
        string Name;
        int Price;
        int Quantity;
        cout << "---------------------------------------------" << endl;
        cout << "Enter Product Name : ";
        cin >> Name;
        cout << "Enter Product Price : ";
        cin >> Price;
        cout << "Enter Product Quantity : ";
        cin >> Quantity;
        cout << "---------------------------------------------" << endl;

        Product Dummy(Name, Price, Quantity);

        if (IsProductAvailable(P, Dummy))
        {
        }

        P.push_back(Dummy);

        char Repeat;
        cout << "Want to Add another Product (Y/N) : ";
        cin >> Repeat;

        if (Repeat == 'Y' || Repeat == 'y')
        {
            continue;
        }
        else
        {
            Flag = 1;
        }
    }

    ofstream ProductFile("./Products/Product.txt", ios::app);
    ProductFile << left;
    for (int i = 0; i < P.size(); ++i)
    {
        ProductFile << setw(20) << P[i].Getname() << "\t" << setw(6) << P[i].GetPrice() << "\t\t" << setw(3) << P[i].GetQty() << endl;
    }
    ProductFile.close();

    ExtractProduct();
}

// Update Product list
void UpdateProduct(vector<Product> &P)
{
}

// Generate Bill records for Admin
// that copy UserBill And append to AdminnBill Records
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

// Billing For Customers
// void GenerateBill(Customer &C, vector<Product> BuyProduct)
void GenerateBill()
{
    ofstream Bill("./Billing/Bill.txt", ios::out);
    ofstream AdminBill("BillAdmin.txt", ios::app);

    Bill << "=============================================================" << endl;
    Bill << "------------------------- A-Z Store -------------------------" << endl;
    Bill << "=============================================================" << endl;
    Bill << left;
    Bill << "Date : " << setw(23) << __DATE__;
    Bill << right;
    Bill << setw(23) << "Time : " << __TIME__ << endl;
    Bill << left;
    Bill << "Name : " << endl;
    Bill << "Contact No. : " << endl;
    Bill << "=============================================================" << endl;
    Bill << setw(3) << "No.";
    Bill << "\t";
    Bill << left;
    Bill << setw(20) << "Product";
    Bill << "\t";
    Bill << setw(10) << "Price";
    Bill << "\t";
    Bill << setw(10) << "Qty";
    Bill << "\t";
    Bill << setw(9) << "Total";
    Bill << endl;
    Bill << "=============================================================" << endl;
    Bill << "=============================================================" << endl;
    Bill << setw(32) << "";
    Bill << "Total : " << endl;
    Bill << "=============================================================" << endl;
    Bill << "------------------ Thank You ! Visit Again ------------------" << endl;
    Bill << "=============================================================" << endl;
    Bill.close();
    GenerateAdminBill();
}

void CustomerMenu()
{
    int Flag = 0;

    cout<<"Already User..? (Yes - 1 / No - 0) : ";
    cin>>Flag;

    if(Flag == 1){
        SignIn(1);
    }else{
        SignUp(1);
    }

}

void EmployeeMenu()
{
}

void AdminMenu()
{
    Greeting(3, 1);
}

void GeneralMenu()
{
    int Flag = 0;

    cout << "------------------------------" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Employee" << endl;
    cout << "3. Admin" << endl;
    cout << "4. exit" << endl;
    cout << "------------------------------" << endl
         << endl;

    cout << "Enter Your Choice : ";
    cin >> Flag;

    switch (Flag)
    {
    case 1:
        CustomerMenu();
        break;

    case 2:
        EmployeeMenu();
        break;

    case 3:
        AdminMenu();
        break;

    case 4:
        break;

    default:
        cout << "Invalid input...!" << endl;
    }
}

int main()
{
    GeneralGreeting();
    GeneralMenu();

    return 0;
}
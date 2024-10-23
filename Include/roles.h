#ifndef ROLES_H
#define ROLES_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base Class Person
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
    Person(string Username, string Password, string Name, char Gender, string Contact);
    string GetUsername();
    string GetPassword();
};

// Customer Class Derived from Person
class Customer : public Person
{
private:
public:
    Customer(string Username, string Password, string Name = "", char Gender = 'N', string Contact = "0000000000"):Person(Username, Password , Name , Gender , Contact)
    {
    }
    // To display Details of Single customer
    void Display() const;
    // Add customer Section
    friend void AddCustomerMenu();
    // To add single Customer
    friend Customer AddCustomerwithIgnore(string Ignone = "");
    // To add Customer
    friend void AddCustomer(Customer newCustomer);
    // To add Customers
    friend void AddCustomer(vector<Customer> &Customers);
    // Extract Customer Details From Files
    friend vector<Customer> ExtractCustomer();
    // Display All Customers Details
    friend void DisplayCustomer(vector<Customer> &Customers);
    // To Edit Customer Details
    friend void EditCustomer();
};

// Employee Class Derived from Person
class Employee : public Person
{
private:
    int Salary;

public:
    Employee(string Username, string Password, string Name = "", char Gender = 'N', string Contact = "0000000000", int Salary = 0);
    // For Get the Employee name
    string GetName() const;
    // For get the Emplyee Contact
    string GetContact() const;
    // For get the Emplyee Gender
    char GetGender() const;
    // For get the Employee Salary
    int GetSalary() const;
    // To display Details of Single Employee
    void Display() const;
    // Add Employee Section
    friend void AddEmployeeMenu();
    // To add single Employee
    friend void AddEmployee(Employee E);
    // to add single Employee userinput
    friend Employee AddEmployee(string Ignore = "");
    // To add Employees
    friend void AddEmployee(vector<Employee> &Employees);
    // Extract Employee Details From Files
    friend vector<Employee> ExtractEmployee();
    // Display All Employees Details
    friend void DisplayEmployee(vector<Employee> &Employees);
    // To edit Employee details
    friend void EditEmployee();
};

// Admin Class Derived from Person
class Admin : public Person
{
private:
public:
    Admin(string Username, string Password, string Name = "", char Gender = 'N', string Contact = "0000000000"):Person(Username,Password,Name,Gender, Contact){}
};

#endif

Person::Person(string Username, string Password, string Name, char Gender, string Contact)
    {
        this->Username = Username;
        this->Password = Password;
        this->Name = Name;
        this->Gender = Gender;
        this->Contact = Contact;
    }

string Person::GetUsername()
{
    return Username;
}

string Person::GetPassword()
{
    return Password;
}

void Customer::Display()const{
    cout<<"------------------------------"<<endl;
    cout<<"Name     : "<<Name<<endl;
    cout<<"Gender   : "<<Gender<<endl;
    cout<<"Contact  : "<<Contact<<endl;
    cout<<"------------------------------"<<endl;
}

Employee::Employee(string Username, string Password, string Name, char Gender, string Contact, int Salary) : Person(Username, Password, Name, Gender, Contact)
{
    this->Salary = Salary;
}

string Employee::GetName() const
{
    return Name;
}

string Employee::GetContact() const
{
    return Contact;
}

char Employee::GetGender() const
{
    return Gender;
}

int Employee::GetSalary() const
{
    return Salary;
}

void Employee::Display()const{
    cout<<"------------------------------"<<endl;
    cout<<"Name     : "<<Name<<endl;
    cout<<"Gender   : "<<Gender<<endl;
    cout<<"Contact  : "<<Contact<<endl;
    cout<<"------------------------------"<<endl;
}


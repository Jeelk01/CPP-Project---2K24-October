#ifndef BILL_H
#define BILL_H

#include<iostream>
#include<fstream>
#include "./product.h"
#include <vector>
#include "./utils.h"
using namespace std;

class Bill{
    vector<Product> Products;
    string Date;
    string Time;

    public:
    // for get Time of bill generation
    string GetTime()const;
    // for get Date of bill Generation
    string GetDate()const;
    // Constructor for Bill Class 
    Bill(vector<Product> Products);
    // Generate Bill Function
    void GenerateBill();
    // Generate Admin Bill Function
    void GenerateAdminBill();
};

#endif

Bill::Bill(vector<Product> Products)
{
    this->Products = Products;
    this->Date = __DATE__;
    this->Time = __TIME__;
}

string Bill::GetDate() const
{
    return Date;
}

string Bill::GetTime() const
{
    return Time;
}

void Bill::GenerateBill()
{
    ofstream Bill("../Billing/Bill.txt", ios::out);
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
    CustomMessage("Bill Generatesd Successfully...!");
}

void Bill::GenerateAdminBill()
{
    ifstream CustomerBill("../Billing/Bill.txt", ios::in);
    ofstream AdminBill("../Billing/BillAdmin.txt", ios::app);

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

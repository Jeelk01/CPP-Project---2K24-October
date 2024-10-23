#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class Product
{
private:
    string Name;
    int Price;
    int Quantity;

public:
    Product(string Name, int Price, int Quantity);

    // to display single PRduct Details
    void Display();
    // get the name of the prodyct
    string Getname();
    // get the price of the prodyct
    int GetPrice();
    // get the quantity of the prodyct
    int GetQty();
    // re-set Qty
    void SetQty(int NewQty = 0);
    // AddProduct Menu
    friend void AddProductMenu();
    // to add single product
    friend Product AddProduct(string Ignore ="");
    // to add single product
    friend void AddProduct(Product E);
    // To add Employees
    friend void AddProduct(vector<Product> &Products);
    // Extract Product Details From Files
    friend vector<Product> ExtractProduct();
    // Display All Employees Details
    friend void DisplayProduct(vector<Product> &Products);
    // To edit the product
    friend void EditProduct();
};



Product::Product(string Name, int Price, int Quantity){
    this->Name = Name;
    this-> Price = Price;
    this->Quantity = Quantity;
}

void Product::Display()
{
    cout << setw(20) << Name << "\t" << setw(6) << Quantity << endl;
}

string Product::Getname()
{
    return Name;
}

int Product::GetPrice()
{
    return Price;
}

int Product::GetQty()
{
    return Quantity;
}

void Product::SetQty(int NewQty){
    Quantity = NewQty;
}

#endif
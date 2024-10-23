#ifndef ERROR_H
#define ERROR_H

#include<iostream>
#include<string>
using namespace std;


// Error Object to Handle run Time Error
class Error{
    private:
    int code;
    static string ErrorMessage[5];

    public:
    // Constructor For Error Object
    Error(int code = 0):code(code){}
    // Show error Member Function
    void ShowError();
    // Re-set the Error Code
    void SetCode(int code = 0);
};

#endif

string Error::ErrorMessage[5] = {"Error Occur...!", "Invalid Input...!", "Out of Bound...!", "File not Opened Properly...!", "Error while reading From the file...!"};

void Error::ShowError()
{
    cout << "----- Error -----" << endl;
    cout << ErrorMessage[code] << endl;
    cout << "-----------------" << endl;
}

void Error::SetCode(int code)
{
    this->code = code;
}


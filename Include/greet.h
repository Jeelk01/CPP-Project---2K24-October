#ifndef GREET_H
#define GREET_H

#include <iostream>
#include <string>
using namespace std;

// To show the Custom Messages
void CustomMessage(string Message);

// Greet object for greeting according to various roles
class Greet
{
private:
    int Role;
   
public:
     // Welcome Greet strings
    static string WelcomeGreet[3];
    // GoodBye Greet strings
    static string GoodByeGreet[3];
    
    // Constructor for Greet
    Greet(int Role = 0);
    // Re-set the Role
    void SetRole(int Role = 0);
    // Show Welcome Greet
    void Welcome();
    // Show GoodBye Greet
    void GoodBye();
};

#endif

// Welcome Greeting Message for Various Roles.
string Greet::WelcomeGreet[3] = {
    "Welcome to A-Z store! We're excited to have you here. Enjoy exploring our offerings!",
    "Good morning, team! Welcome back! Let's make today productive and inspiring!",
    "Welcome, Admin! Your guidance is always appreciated. Let's get started on today's tasks!"
};

// Goodbye Greeting Message for Various Roles.
string Greet::GoodByeGreet[3] = {
    "Thank you for visiting A-Z store! We hope to see you again soon. Happy shopping!",
    "Great job today, team! Have a wonderful evening, and see you tomorrow!",
    "Thanks for your hard work today, Admin! Have a great evening and see you next time!"
};

Greet::Greet(int Role){
    this->Role;
}

void Greet::SetRole(int Role){
    this->Role;
}

void Greet::Welcome(){
    string str = WelcomeGreet[Role - 1];
    CustomMessage(str);
}

void Greet::GoodBye(){  
    string str = GoodByeGreet[Role - 1];
    CustomMessage(str);
}

#include <iostream>
#include <string>
using namespace std;

// Base class
class Student {
protected:
    string name;
    int id;

public:
    // Base constructor with parameters
    Student(string sName, int sId) : name(sName), id(sId) {
        cout << "Student constructor called for: " << name << endl;
    }
    
    ~Student() {
        cout << "Student destructor called for: " << name << endl;
    }
};

// Derived class
class UnderGrad : public Student {
private:
    string major;

public:
    // Derived constructor passing variables to the base constructor
    UnderGrad(string uName, int uId, string uMajor) 
        : Student(uName, uId), major(uMajor) {
        cout << "UnderGrad constructor called. Major: " << major << endl;
    }
    
    ~UnderGrad() {
        cout << "UnderGrad destructor called. Major: " << major << endl;
    }

    void displayInfo() {
        cout << "Name: " << name << ", ID: " << id << ", Major: " << major << endl;
    }
};

int main() {
    // Creating the object with variable values
    UnderGrad u1("Alex Smith", 12345, "Computer Science");
    
    u1.displayInfo();
    
    return 0;
}

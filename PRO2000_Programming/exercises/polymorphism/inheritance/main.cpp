#include <iostream>
#include <string>
using namespace std;

class Employee {
protected: 
    string name;       
    double salary;     

public:
    void setBaseDetails(string n, double s) {
        name = n;
        salary = s;
    }
};

class Manager : public Employee {
private:
    int teamSize;      

public:
    void setTeamSize(int size) {
        teamSize = size;
    }

    void displayDetails() {
        cout << "Manager Name: " << name << endl;
        cout << "Base Salary: $" << salary << endl;
        cout << "Team Size: " << teamSize << " members" << endl;
    }
};

int main() {
    Manager mgr;
    mgr.setBaseDetails("Alice", 95000.0); 
    mgr.setTeamSize(12);
    mgr.displayDetails();
    return 0;
}

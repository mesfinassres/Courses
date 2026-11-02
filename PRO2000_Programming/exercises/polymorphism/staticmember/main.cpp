#include <iostream>

// This tells the compiler to look in the 'std' namespace for symbols
using namespace std;

class Counter {
public:
    static int objectCount; 

    Counter() {
        objectCount++;
    }

    ~Counter() {
        objectCount--;
    }
};

int Counter::objectCount = 0;

int main() {
    // Look Ma, no std:: !
    cout << "Initial count: " << Counter::objectCount << "\n"; 

    Counter obj1;
    Counter obj2;
    cout << "Count after creating obj1 and obj2: " << Counter::objectCount << "\n";

    {
        Counter tempObj;
        cout << "Count inside block (with tempObj): " << Counter::objectCount << "\n";
    } 

    cout << "Count after block: " << Counter::objectCount << "\n";

    return 0;
}

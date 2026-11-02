#include <iostream>
using namespace std;

class Number {
public:
    int value;

    Number(int v) {
        value = v;
    }

    // Overload the + operator
    Number operator+(const Number &n) {
        return Number(value + n.value);
    }

    void display() {
        cout << value << endl;
    }
};

int main() {
    Number n1(5);
    Number n2(10);
    
    // Using the overloaded + operator
    Number n3 = n1 + n2; 

    n3.display(); // Outputs: 15
    return 0;
}

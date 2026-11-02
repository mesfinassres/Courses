#include <iostream>
#include <string>

using namespace std;

class Printer {
public:
    // Overload 1: Takes an integer
    void print(int i) {
        std::cout << "Printing integer: " << i << std::endl;
    }

    // Overload 2: Takes a double (different type)
    void print(double d) {
        std::cout << "Printing float/double: " << d << std::endl;
    }

    // Overload 3: Takes a string and an integer (different number and types)
    void print(std::string s, int repetitions) {
        for(int i = 0; i < repetitions; ++i) {
            std::cout << "Printing string: " << s << " | "<<endl;
        }
        std::cout << std::endl;
    }
};

int main() {
    Printer myPrinter;

    // The compiler automatically matches the call to the correct method
    myPrinter.print(10);                    // Calls Overload 1
    myPrinter.print(3.14);                  // Calls Overload 2
    myPrinter.print("Hello OOP", 10);        // Calls Overload 3

    return 0;
}

#include <iostream>
#include <sstream>
#include <iomanip> // Needed for setprecision

using namespace std;

int main() {
    double amount = 125.5;
    
    ostringstream outStr;
    
    // Write formatted data using I/O manipulators
    outStr << showpoint << fixed 
           << setprecision(2) 
           << '$' << amount;
           
    // Access and print the string from the ostringstream
    cout << outStr.str() << endl;

    // 1. Basic right justification (Default behavior requires a width)
    std::cout << std::setw(15) << "apple" << "\n";
    std::cout << std::setw(15) << "banana" << "\n";
    
    // 2. Explicitly forcing right alignment (Useful if you previously used std::left)
    std::cout << std::left  << std::setw(15) << "Left aligned" << "\n";
    std::cout << std::right << std::setw(15) << "Right aligned" << "\n";


    int* p = new int(65);
    char* ch = reinterpret_cast<char*>(p);
    cout << *p << endl;
    cout << *ch << endl;
    cout << p << endl;
    cout << ch << endl;
    
    return 0;
}
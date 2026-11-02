#include <iostream>

// The compiler replaces 'T' with the actual data type at compile-time
template <typename T>

T getMax(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T2>

class Wrapper {
private:
    T2 value;
public:
    Wrapper(T2 val) : value(val) {}
    T2 getValue() const { return value; }
};

int main() {
    // Explicit type specification
    std::cout << getMax<int>(3, 7) << "\n";       // Output: 7

    // Automatic Template Argument Deduction (compiler infers the type)
    std::cout << getMax(3.14, 1.59) << "\n";   // Output: 3.14 (Deduced T = double)


    Wrapper<int> intInstance(42);
    
    Wrapper<std::string> stringInstance("Hello Templates");

    std::cout << intInstance.getValue() << "\n";
    std::cout << stringInstance.getValue() << "\n";
    
    return 0;
}
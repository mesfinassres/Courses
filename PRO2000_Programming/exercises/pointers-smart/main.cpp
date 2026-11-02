#include <iostream>
#include <memory>

struct Widget {
    Widget() { std::cout << "Widget Created\n"; }
    ~Widget() { std::cout << "Widget Destroyed\n"; }
    void do_something() { std::cout << "Working...\n"; }
};

int main() {
    // Allocation via make_unique
    std::unique_ptr<Widget> ptr1 = std::make_unique<Widget>();
    ptr1->do_something(); // Uses overloaded -> operator

    // std::unique_ptr<Widget> ptr2 = ptr1; // COMPILER ERROR: Cannot be copied!

    // Transferring ownership via move semantics
    std::unique_ptr<Widget> ptr2 = std::move(ptr1); 
    // ptr1 is now null; ptr2 owns the Widget
    if (ptr1) {
        std::cout<<"ptr1 ";
        ptr1->do_something(); 
    } else if (ptr2) {
        std::cout<<"ptr2 ";
        ptr2->do_something(); 
    }

    return 0; 
} //
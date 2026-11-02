#include <iostream>

using namespace std;
class Animal {
public:
    // Virtual function tells the compiler to look at the VTABLE at runtime
    virtual void make_sound() {
         cout << "Generic animal sound" <<  endl;
    }
    virtual ~Animal() = default; // Always use a virtual destructor in polymorphic base classes
};

class Dog : public Animal {
public:
    void make_sound() override { // Overriding the base function
         cout << "Woof! Woof!" <<  endl;
    }
};

class Cat : public Animal {
public:
    void make_sound() override {
         cout << "Meow!" <<  endl;
    }
};

int main() {
    // Base class pointers pointing to derived objects
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();

    // Resolves at runtime to call derived implementations
    animal1->make_sound(); // Outputs: Woof! Woof!
    animal2->make_sound(); // Outputs: Meow!

    delete animal1;
    delete animal2;
}

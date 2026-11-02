#include <iostream>

class Animal {
public:
    void eat() { std::cout << "Eating...\n"; }
};

class Dog : public Animal { // Public inheritance
public:
    void bark() { std::cout << "Woof!\n"; }
};

int main() {
    Dog myDog;
    
    // Automatically allowed: A Dog IS-A Animal
    Animal* animalPtr = &myDog; 
    animalPtr->eat(); // Works perfectly!
    
    // animalPtr->bark(); // Error! The Animal pointer only knows about Animal features.
}

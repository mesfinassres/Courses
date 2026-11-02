#include <iostream>

using namespace std;

class Square {
private:
    int side;

    int calculateArea() {
        return side * side;
    }

public:
    Square(int s = 1) {
        side = s;
    }
    void setSide(int);

    int getSide() {
        return side;
    }
    void displayArea() {
        cout << "Area of the Square: " << calculateArea() << endl;
    }
};

int main() {
    Square mySquare(5);
    cout << "Square Side: " << mySquare.getSide() <<endl;
    mySquare.setSide(10);
    cout << "Square Side: " << mySquare.getSide() <<endl;
    mySquare.displayArea();

    return 0;
}

void Square::setSide(int s) {
    if (s > 0) {
        side = s;
    } else {
        cout << "Invalid side length! Keeping current value.\n";
    }
}
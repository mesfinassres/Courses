#include <iostream>

int main() {
    int a, b, sum;

    a = 2;
    b = 3;
    sum = a + b;

    std::cout << sum << std::endl;
    int sumi=0;
    for (int i=0; i<10;i++) {
        sumi += i;
    }
    std::cout <<sumi << std::endl;
    return 0;
}
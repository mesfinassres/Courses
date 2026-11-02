#include <iostream>
#include<limits>

#include<cctype>

using namespace std;

int modifyByValue(int num) {
    num = num + 10; 
    return num;
}

int modifyByReference(int &num) {
    num = num + 10;
    return num;
}

int main()
{
    int a = 5;
    int b = 5;

    int x= modifyByValue(a);
    std::cout << "After modifyByValue: " << a << std::endl; 

    int y= modifyByReference(b);
    std::cout << "After modifyByReference: " << b << std::endl; 

    modifyByValue(42);

    return 0;
}

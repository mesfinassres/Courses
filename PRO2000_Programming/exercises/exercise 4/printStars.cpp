#include <iostream>
using namespace std;

int main() {

    cout<<"Original:"<<endl;

    int rows = 5;

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }

    cout<<"Reflect:"<<endl;
    rows = 5;

    for (int i = 1; i <= rows; i++) {
        // Print leading spaces
        for (int j = 1; j <= rows - i; j++) {
            cout << "  ";
        }

        // Print stars
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }

        cout << endl;
    }
    return 0;
}
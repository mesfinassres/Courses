#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

inline void displayPerson()
{
    string name = "John Doe";
    int age = 25;
    double height = 1.78;
    bool isStudent = true;

    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Height: " << height << endl;
    cout << "Student: " << isStudent << endl;
    for (int i = 0; i < 10; i++)
    {
        /* code */
        cout << i << endl;
    }
    
}

#endif
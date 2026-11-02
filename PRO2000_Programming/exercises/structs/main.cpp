#include <iostream>
#include <string>
using namespace std;

struct Student {
    int studentID;
    string name;
    short year;
    double gpa;
};

int main() {
    Student students[5] = {
        {101, "Anna", 1, 3.5},
        {102, "Bjørn", 2, 3.8},
        {103, "Clara", 3, 3.2},
        {104, "David", 2, 3.9},
        {105, "Emma", 1, 3.6}
    };

    for (int i = 0; i < 5; i++) {
        cout << "ID: " << students[i].studentID
             << ", Name: " << students[i].name
             << ", Year: " << students[i].year
             << ", GPA: " << students[i].gpa << endl;
    }

    return 0;
}
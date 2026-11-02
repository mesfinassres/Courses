// main.cpp - client program: menu that uses StudentRegistry
#include <iostream>
#include <iomanip>
#include <string>
#include "StudentRegistry.h"

using namespace std;

const string DATA_FILE = "students.txt";

void showMenu()
{
    cout << "\n--- Student Records ---\n"
         << "1. List all students\n"
         << "2. Find a student by ID\n"
         << "3. Add a student\n"
         << "4. Show class average\n"
         << "5. Save to file\n"
         << "0. Quit\n"
         << "Choice: ";
}

void addNewStudent(StudentRegistry& registry)
{
    int id;
    string name;
    double scores[Student::NUM_SCORES];

    cout << "ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    if (registry.findById(id) != nullptr)
    {
        cout << "A student with that ID already exists." << endl;
        return;
    }

    cout << "Name: ";
    getline(cin, name);

    for (int i = 0; i < Student::NUM_SCORES; i++)
    {
        cout << "Score " << (i + 1) << ": ";
        cin >> scores[i];
    }
    cin.ignore(1000, '\n');

    registry.addStudent(Student(id, name, scores));
    cout << "Student added." << endl;
}

int main()
{
    StudentRegistry registry;

    if (!registry.loadFromFile(DATA_FILE))
        cout << "Could not open " << DATA_FILE << ". Starting with an empty list." << endl;
    else
        cout << "Loaded " << registry.size() << " students." << endl;

    int choice;
    do
    {
        showMenu();
        if (!(cin >> choice))
            break;
        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
            registry.listAll();
            break;
        case 2:
        {
            int id;
            cout << "ID: ";
            cin >> id;
            cin.ignore(1000, '\n');
            const Student* s = registry.findById(id);
            if (s) s->display();
            else   cout << "No student with ID " << id << "." << endl;
            break;
        }
        case 3:
            addNewStudent(registry);
            break;
        case 4:
            cout << fixed << setprecision(2)
                 << "Class average: " << registry.classAverage() << endl;
            break;
        case 5:
            if (registry.saveToFile(DATA_FILE))
                cout << "Saved." << endl;
            else
                cout << "Could not write " << DATA_FILE << "." << endl;
            break;
        case 0:
            cout << "Goodbye." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}

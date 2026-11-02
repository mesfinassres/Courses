#include <iostream>

using namespace std;

enum class MenuOption {
    Add = 1,
    Subtract,
    Multiply,
    Divide,
    Exit
};

int main() {
    int choice;
    double firstNumber, secondNumber, result;
    bool running = true;

    while (running) {
        cout << "\n===== Simple Calculator =====\n";
        cout << "1. Add\n";
        cout << "2. Subtract\n";
        cout << "3. Multiply\n";
        cout << "4. Divide\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        MenuOption option = static_cast<MenuOption>(choice);

        switch (option) {
            case MenuOption::Add:
                cout << "Enter two numbers: ";
                cin >> firstNumber >> secondNumber;

                result = firstNumber + secondNumber;
                cout << "Result = " << result << '\n';
                break;

            case MenuOption::Subtract:
                cout << "Enter two numbers: ";
                cin >> firstNumber >> secondNumber;

                result = firstNumber - secondNumber;
                cout << "Result = " << result << '\n';
                break;

            case MenuOption::Multiply:
                cout << "Enter two numbers: ";
                cin >> firstNumber >> secondNumber;

                result = firstNumber * secondNumber;
                cout << "Result = " << result << '\n';
                break;

            case MenuOption::Divide:
                cout << "Enter two numbers: ";
                cin >> firstNumber >> secondNumber;

                if (secondNumber == 0) {
                    cout << "Error: Cannot divide by zero.\n";
                } else {
                    result = firstNumber / secondNumber;
                    cout << "Result = " << result << '\n';
                }

                break;

            case MenuOption::Exit:
                running = false;
                cout << "Program ended.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
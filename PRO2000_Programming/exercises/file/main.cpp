#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt", ios::app);

    if (!inputFile) {
        cout << "Error: Could not open input.txt.\n";
        return 1;
    }

    if (!outputFile) {
        cout << "Error: Could not create output.txt.\n";
        return 1;
    }

    string line;

    while (getline(inputFile, line)) {
        outputFile << line << '\n';
    }

    inputFile.close();
    outputFile.close();

    cout << "Data copied successfully to output.txt.\n";

    return 0;
}
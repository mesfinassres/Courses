#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3};

    cout << v[0] << endl; 
    v.push_back(4);       
    cout << v[3] << endl; 
    v.pop_back(); // Remove last element
    cout << v[3] << endl; //???
}
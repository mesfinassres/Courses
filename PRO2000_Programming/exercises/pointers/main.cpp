#include <iostream>
using namespace std;

int main() {

    int *count, *arrayptr; 
    count = new int;

    cout <<"How many students? "; 
    cin >> *count;
    
    arrayptr = new int[*count];

    for (int i=0; i<*count; i++)
    {
        cout << "Enter score " << i << ": "; cin >> arrayptr[i];
    }
    for (int i=0; i<*count; i++) cout<<arrayptr[i]<<endl;
    
   

    arrayptr[0] = 10;

    cout<<arrayptr[0];
     delete [] arrayptr;
    return 0;
}
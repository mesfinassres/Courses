#include<iostream>
#include<string>

using namespace std;

int main(){
    string str(9,' ');
    str="Hello wordl!";
    cout<<str<<endl;

    string s = "Hello";
    
    // Total stack footprint (Usually 24 or 32 bytes)
    cout << "Stack size: " << sizeof(s) << " bytes\n"; 
    
    // Active characters used
    cout << "String length: " << s.size() << " characters\n"; 

    // Total heap capacity allocated
    cout << "Heap capacity: " << s.capacity() << " characters\n"; 
    
    cout<<str.max_size()<<endl;
    int num[5]={35, 20, 76, 18, 50};
    for(int i=0; i<5; i++)
        cout<<num[i]<<endl;

    return 0;
}
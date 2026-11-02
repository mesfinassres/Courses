#include<iostream>
using namespace std;

int main(){
    int num;

    printf("Enter a number:\n"); // without std 
    cin >> num;

    if (num>0) cout<<"Positive.";
    else if (num<0) cout << "Negative.";
    else cout<<"Zero.";
    
    return 0;
}
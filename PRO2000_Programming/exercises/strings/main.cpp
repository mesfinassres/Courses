#include <iostream>
#include<cstring>
using namespace std;

void stringOperator();

int main() {
    char str[20] = "Hi there";
    char *pStr;
    pStr = str; 
    cout << pStr << " "<< pStr;
    //pStr= " Test.";
    strcpy(pStr, " Test.");
    
    strcpy(str, pStr);
    //str=pStr;
    
    cout << str << " "<< str;
    int x = atoi("100");
    cout<<x<<endl;

    stringOperator();
}
void stringOperator(){
    string word1, phrase;
    string word2 = " Dog";
    cin >>word1; // user enters "Hot“, word1 has "Hot“

    phrase=word1 +word2; //phrase has "Hot Dog"
    phrase +=" on a bun";
    //for (int i = 0; i < 16; i++) cout<<phrase[i]; //displays "Hot Dog on a bun"
    cout<<phrase;
}
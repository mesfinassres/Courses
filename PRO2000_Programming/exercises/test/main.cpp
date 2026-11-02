#include <iostream> 
#include<string>

using namespace std; 
int main() { 
    string name ="John Doe";
    string program = "Bachelor in AI";
    int year = 2026;
    bool isStudent = true;

    cout<<"Name: "<<name<<endl;
    cout<<"Program: "<<program<<endl;
    cout<<"Year: "<<year<<endl;
    cout<<"isStudent: "<<boolalpha<<isStudent<<endl;

    string studentName;

    cout<<"Enter infor:"<<endl;
    cout<<"Name: ";  
    cin>>studentName;
    cout<<studentName<<endl;



    int x=5, y=8;
    int z=x+y;

    cout<<z<<endl;

   //Create a program that asks for a user age and determines whether
    //the user qualifies for a student discount. Age must be between 18 and 30 years

    int age;
    bool qualify;
    cout<<"Enter age: "; 
    cin>>age;
    ((age>=18)&&(age<=30))? qualify=true:qualify=false;

    cout<<endl<<boolalpha<<qualify;







    return 0; 

}
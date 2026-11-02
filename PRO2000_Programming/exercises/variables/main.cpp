#include <iostream>
#include<limits>

#include<cctype>

using namespace std;
int main()
{
    cout << "Hello World!" << endl;
    int val = 0x10;
    cout<<val<<endl;
    cout<<hex<<val<<endl;

    int y=1234;
    cout<<sizeof(y)<<endl;

    long long x=1234LL;
    cout<<sizeof(x)<<endl;

    double z=3.14159E1;
    cout<<z<<" "<<sizeof(z)<<endl;

    cout<<'A'<<endl;
    char ch='A';

    cout<<dec<<(int)ch<<endl;    

    bool exists=true;

    cout<<boolalpha<<exists<<" "<<sizeof(exists)<<endl;  

    cout << "shift = (1 << 2) + 1 -> " <<(1 << 2) + 1 << '\n';
    //cout<<"\a"<<flush;

    for (int i = 0; i < 5; i++)
    {
        int x=2;
        cout<<x<<endl;
    }
    cout << " int min: " << numeric_limits<int>::min() << '\n';
    unsigned int t=-200;
    cout<<t<<endl;
    return 0;
}

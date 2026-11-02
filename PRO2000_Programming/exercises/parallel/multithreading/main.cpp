#include<iostream>
#include<cctype>


#include<iostream> 
#include<thread> 
#include<vector>
#include <mutex>
using namespace std;
std::mutex	bankMutex;

int	bankBalance	= 1000;	//	Initial	bank	balance 
void performTransactions(){
	for	(int i = 0;	i <	10000; ++i)	{ 
        bankMutex.lock();	//Manually lock	the mutex

		bankBalance	+= 10; // Deposit 
		bankBalance	-= 10; // Withdrawal
        bankMutex.unlock();
	}
}

int main()
{
    vector<thread>threads; 
	for (int i =0; i<8;	++i){
		// Initiate	transactions without synchronization 
		threads.emplace_back(performTransactions);
	}
	for	(auto& thread:threads){
		thread.join();	//	Wait for all threads to	finish
	}
	cout<<"Expected balance:1000\n Actual balance: "<<bankBalance<<endl;
    // int x=5;
    // int y=6;

    // int z=x+y;

    // cout<<z<<endl;

    // cout<<"Hello, World!"<<endl;

    // x < 0 ? y++ : z++;
    
    // bool t= isalpha('a');

    return 0;
}
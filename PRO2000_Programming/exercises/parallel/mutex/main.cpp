#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

using namespace std;

// Global variables for thread synchronization
long long global_sum = 0;
mutex sum_mutex;

// Thread worker function to compute the sum of a specific chunk
void compute_sum(vector<int>& v, int start, int end) {
    long long res = 0;
    for (int i = start; i < end; i++) {
        res += v[i];
    }
    
    // Protect shared global variable using lock_guard
    {
        //lock_guard<mutex> lock(sum_mutex);
        global_sum += res;
    }
}

int main() {
    int n = 100000000; // Example size of the vector
    vector<int> v(n, 1); // Example vector initialized with 1s

    int num_threads = 8;
    vector<thread> threads;
    
    // Calculate size of array chunk per thread (rounding up)
    int chunk_size = (n + num_threads - 1) / num_threads; 
    
    // Launch threads
    for (int t = 0; t < num_threads; t++) {
        int start = t * chunk_size;
        int end = min(start + chunk_size, n);
        threads.emplace_back(compute_sum, ref(v), start, end);
    }

    // Join threads back to the main thread
    for (auto& th : threads) {
        th.join();
    }

    cout << "Total Sum: " << global_sum << endl;
    return 0;
}
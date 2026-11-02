#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

void sum_half(const vector<int>& a, int start, int end, long long& partial_sum) {
    long long local_sum = 0;
    for (int i = start; i < end; i++) {
        local_sum += a[i];
    }
    partial_sum = local_sum;
}

int main() {
    int n = 100000000;
    vector<int> a(n, 1);

    long long global_sum = 0;
    long long sum1 = 0;
    long long sum2 = 0;
    int mid = n / 2;

    auto start_time = chrono::high_resolution_clock::now();

    thread t1(sum_half, ref(a), 0, mid, ref(sum1));
    thread t2(sum_half, ref(a), mid, n, ref(sum2));

    t1.join();
    t2.join();

    global_sum = sum1 + sum2;

    auto end_time = chrono::high_resolution_clock::now();

    auto elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    cout << "Global Sum: " << global_sum << endl;
    cout << "Time elapsed: " << elapsed_time << " microseconds" << endl;

    return 0;
}

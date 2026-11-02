#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main() {
    int n = 100000000;
    vector<int> a(n, 1);

    long long global_sum = 0;

    auto start_time = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        global_sum += a[i];
    }

    auto end_time = chrono::high_resolution_clock::now();

    auto elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    cout << "Global Sum: " << global_sum << endl;
    cout << "Time elapsed: " << elapsed_time << " microseconds" << endl;

    return 0;
}

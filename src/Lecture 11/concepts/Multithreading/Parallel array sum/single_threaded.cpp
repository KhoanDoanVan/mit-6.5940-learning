#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

const size_t N = 50'000'000;
vector<int> a(N, 1);

long long sum_single() {
    long long sum = 0;
    for (size_t i = 0; i < N; ++i) {
        sum += a[i];
    }
    return sum;
}

int main() {
    auto start = high_resolution_clock::now();
    auto result = sum_single();
    auto end = high_resolution_clock::now();

    cout << "single-thread: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms, sum = " << result << '\n';
}
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int N = 2048;
static int a[N][N];

long long test_bad() {
    long long sum = 0;
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            sum += a[i][j];
        }
    }
    return sum;
}

long long test_good() {
    long long sum = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sum += a[i][j];
        }
    }
    return sum;
}

int main() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            a[i][j] = i + j;

    auto start1 = high_resolution_clock::now();
    auto s1 = test_bad();
    auto end1 = high_resolution_clock::now();

    auto start2 = high_resolution_clock::now();
    auto s2 = test_good();
    auto end2 = high_resolution_clock::now();

    auto t1 = duration_cast<milliseconds>(end1 - start1).count();
    auto t2 = duration_cast<milliseconds>(end2 - start2).count();

    cout << "bad:  " << t1 << " ms, sum = " << s1 << '\n';
    cout << "good: " << t2 << " ms, sum = " << s2 << '\n';

    return 0;
}

// final:
// - bad:  24 ms, sum = 8585740288
// - good: 0 ms, sum = 8585740288
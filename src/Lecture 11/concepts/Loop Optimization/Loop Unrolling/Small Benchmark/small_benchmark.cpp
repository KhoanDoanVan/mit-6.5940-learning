#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 1 << 24;
static int a[N];

long long test_normal() {
    long long sum = 0;
    for (int i = 0; i < N; i++) {
        sum += a[i];
    }
    return sum;
}

long long test_unrolled_4() {
    long long sum = 0;
    int i = 0;

    for (; i <= N - 4; i += 4) {
        sum += a[i];
        sum += a[i + 1];
        sum += a[i + 2];
        sum += a[i + 3];
    }

    for (; i <= N; ++i) {
        sum += a[i];
    }

    return sum;
}

int main() {
    for (int i = 0; i < N; ++i) {
        a[i] = i % 100;
    }

    auto start1 = high_resolution_clock::now();
    auto s1 = test_normal();
    auto end1 = high_resolution_clock::now();

    auto start2 = high_resolution_clock::now();
    auto s2 = test_unrolled_4();
    auto end2 = high_resolution_clock::now();

    auto t1 = duration_cast<milliseconds>(end1 - start1).count();
    auto t2 = duration_cast<milliseconds>(end2 - start2).count();

    cout << "normal:   " << t1 << " ms, sum = " << s1 << '\n';
    cout << "unroll-4: " << t2 << " ms, sum = " << s2 << '\n';

    return 0;
}

// Final: 
// - normal:   11 ms, sum = 830471520
// - unroll-4: 2 ms, sum = 830471520
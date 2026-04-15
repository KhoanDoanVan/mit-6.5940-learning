#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::chrono;

const size_t N = 50'000'000;
vector<int> a(N, 1);

void partial_sum(size_t start, size_t end, long long& result) {
    long long local = 0;
    for (size_t i = start; i < end; ++i) {
        local += a[i];
    }
    result = local;
}

long long sum_multi(int num_threads) {
    vector<thread> threads;
    vector<long long> partial_results(num_threads, 0);

    size_t chunk = N / num_threads;

    for (int t = 0; t < num_threads; ++t) {
        size_t start = t * chunk;
        size_t end = (t == num_threads - 1) ? N : start + chunk;

        threads.emplace_back(partial_sum, start, end, ref(partial_results[t]));
    }

    for (auto& th : threads) {
        th.join();
    }

    long long total = 0;
    for (long long x : partial_results) {
        total += x;
    }

    return total;
}

int main() {
    int num_threads = 4;

    auto start1 = high_resolution_clock::now();
    long long s1 = 0;
    for (size_t i = 0; i < N; ++i) {
        s1 += a[i];
    }
    auto end1 = high_resolution_clock::now();

    auto start2 = high_resolution_clock::now();
    long long s2 = sum_multi(num_threads);
    auto end2 = high_resolution_clock::now();

    auto t1 = duration_cast<milliseconds>(end1 - start1).count();
    auto t2 = duration_cast<milliseconds>(end2 - start2).count();

    cout << "single-thread: " << t1 << " ms, sum = " << s1 << '\n';
    cout << "multi-thread:  " << t2 << " ms, sum = " << s2 << '\n';

    return 0;
}
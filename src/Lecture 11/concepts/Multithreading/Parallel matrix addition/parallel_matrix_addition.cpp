#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int N = 2048;
static int A[N][N];
static int B[N][N];
static int C[N][N];

void add_rows(int row_begin, int row_end) {
    for (int i = row_begin; i < row_end; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    int num_threads = 4;
    vector<thread> threads;
    int rows_per_thread = N / num_threads;

    auto start = high_resolution_clock::now();

    for (int t = 0; t < num_threads; ++t) {
        int begin = t * rows_per_thread;
        int end = (t == num_threads - 1) ? N : begin + rows_per_thread;
        threads.emplace_back(add_rows, begin, end);
    }

    for (auto& th : threads) {
        th.join();
    }

    auto end = high_resolution_clock::now();

    long long checksum = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            checksum += C[i][j];
        }
    }

    cout << "time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms, checksum = " << checksum << '\n';

    return 0;
}
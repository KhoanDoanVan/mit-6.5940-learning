#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>

using namespace std;
using namespace std::chrono;

constexpr int N = 2048;
constexpr int TILE = 32;
constexpr int REPEATS = 30;

static int A[N][N];
static int B[N][N];
static int C[N][N];

void init_data() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }
    }
}

long long checksum() {
    long long sum = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sum += C[i][j];
        }
    }
    return sum;
}

long long test_bad() {
    long long final_sum = 0;

    for (int r = 0; r < REPEATS; ++r) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        final_sum = checksum();
    }

    return final_sum;
}

long long test_good() {
    long long final_sum = 0;

    for (int r = 0; r < REPEATS; ++r) {
        for (int ii = 0; ii < N; ii += TILE) {
            for (int jj = 0; jj < N; jj += TILE) {
                const int i_end = min(ii + TILE, N);
                const int j_end = min(jj + TILE, N);

                for (int i = ii; i < i_end; ++i) {
                    for (int j = jj; j < j_end; ++j) {
                        C[i][j] = A[i][j] + B[i][j];
                    }
                }
            }
        }
        final_sum = checksum();
    }

    return final_sum;
}

int main() {
    init_data();
    auto start1 = high_resolution_clock::now();
    auto s1 = test_bad();
    auto end1 = high_resolution_clock::now();

    init_data();
    auto start2 = high_resolution_clock::now();
    auto s2 = test_good();
    auto end2 = high_resolution_clock::now();

    auto t1 = duration_cast<milliseconds>(end1 - start1).count();
    auto t2 = duration_cast<milliseconds>(end2 - start2).count();

    cout << "Matrix Addition (N=" << N << ", repeats=" << REPEATS << ")\n";
    cout << "without tiling: " << t1 << " ms, checksum = " << s1 << '\n';
    cout << "with tiling:    " << t2 << " ms, checksum = " << s2 << '\n';
    cout << "tile size:      " << TILE << '\n';

    return 0;
}

// Final:
// Matrix Addition (N=2048, repeats=30)
// - without tiling: 48 ms, checksum = 8585740288
// - with tiling:    92 ms, checksum = 8585740288
// - tile size:      32
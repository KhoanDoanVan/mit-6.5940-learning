#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>

using namespace std;
using namespace std::chrono;

constexpr int N = 512;
constexpr int TILE = 32;

static int A[N][N];
static int B[N][N];
static long long C[N][N];

void init_data() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = (i + j) % 100;
            B[i][j] = (i - j + 100) % 100;
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
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            long long sum = 0;
            for (int k = 0; k < N; ++k) {
                sum += 1LL * A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    return checksum();
}

long long test_good() {
    for (int ii = 0; ii < N; ii += TILE) {
        for (int jj = 0; jj < N; jj += TILE) {
            for (int kk = 0; kk < N; kk += TILE) {
                const int i_end = min(ii + TILE, N);
                const int j_end = min(jj + TILE, N);
                const int k_end = min(kk + TILE, N);

                for (int i = ii; i < i_end; ++i) {
                    for (int j = jj; j < j_end; ++j) {
                        long long sum = C[i][j];
                        for (int k = kk; k < k_end; ++k) {
                            sum += 1LL * A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;
                    }
                }
            }
        }
    }

    return checksum();
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

    cout << "Matrix Multiplication (N=" << N << ")\n";
    cout << "without tiling: " << t1 << " ms, checksum = " << s1 << '\n';
    cout << "with tiling:    " << t2 << " ms, checksum = " << s2 << '\n';
    cout << "tile size:      " << TILE << '\n';

    return 0;
}

// Final:
// Matrix Multiplication (N=512)
// - without tiling: 113 ms, checksum = 116082664192
// - with tiling:    12 ms, checksum = 116082664192
// - tile size:      32
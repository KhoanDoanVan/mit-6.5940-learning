#include <iostream>
#include <vector>
#include <chrono>
#include <immintrin.h>
using namespace std;
using namespace std::chrono;

const int N = 1 << 24;
static float a[N], b[N], c[N];

void add_scalar() {
    for (int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }
}

void add_simd() {
    int i = 0;
    for (; i <= N - 8; i += 8) {
        __m256 va = _mm256_loadu_ps(a + i);
        __m256 vb = _mm256_loadu_ps(b + i);
        __m256 vc = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(c + i, vc);
    }
    for (; i < N; ++i) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    for (int i = 0; i < N; ++i) {
        a[i] = static_cast<float>(i);
        b[i] = static_cast<float>(2 * i);
    }

    auto start1 = high_resolution_clock::now();
    add_scalar();
    auto end1 = high_resolution_clock::now();

    auto start2 = high_resolution_clock::now();
    add_simd();
    auto end2 = high_resolution_clock::now();

    auto t1 = duration_cast<milliseconds>(end1 - start1).count();
    auto t2 = duration_cast<milliseconds>(end2 - start2).count();

    cout << "scalar: " << t1 << " ms\n";
    cout << "simd:   " << t2 << " ms\n";
}
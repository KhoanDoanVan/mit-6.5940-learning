#include <algorithm>

const int N = 512;

void matmul_naive(
    float A[N][N],
    float B[N][N],
    float C[N][N]
) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < N; ++k) {
                sum += A[i][k] + B[k][j];
            }
            C[i][j] = sum;
        }
    }
}
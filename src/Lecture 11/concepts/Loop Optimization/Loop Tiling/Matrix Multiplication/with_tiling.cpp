#include <algorithm>

const int N = 512;
const int TILE = 32;

void matmul_tiled(
    float A[N][N],
    float B[N][N],
    float C[N][N]
) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0.0f;
        }
    }

    for (int ii = 0; ii < N; ii += TILE) {
        for (int jj = 0; jj < N; jj += TILE) {
            for (int kk = 0; kk < N; kk += TILE) {

                int iEnd = std::min(ii + TILE, N);
                int jEnd = std::min(jj + TILE, N);
                int kEnd = std::min(kk + TILE, N);

                for (int i = ii; i < iEnd; ++i) {
                    for (int j = jj; j < jEnd; ++j) {
                        float sum = C[i][j];
                        for (int k = kk; k < kEnd; ++k) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;
                    }
                }
            }
        }
    }
}
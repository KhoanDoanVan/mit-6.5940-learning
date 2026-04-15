#include <vector>
#include <algorithm>


void add_tiled(
    const std::vector<std::vector<float>>& A,
    const std::vector<std::vector<float>>& B,
    std::vector<std::vector<float>>& C,
    int N,
    int M,
    int tileSize
) {
    for (int ii = 0; ii < N; ii += tileSize) {
        for (int jj = 0; jj < M; jj += tileSize) {
            int iEnd = std::min(ii + tileSize, N);
            int jEnd = std::min(jj + tileSize, M);

            for (int i = ii; i < iEnd; ++i) {
                for (int j = jj; j < jEnd; ++j) {
                    C[i][j] = A[i][j] + B[i][j];
                }
            }
        }
    }
}
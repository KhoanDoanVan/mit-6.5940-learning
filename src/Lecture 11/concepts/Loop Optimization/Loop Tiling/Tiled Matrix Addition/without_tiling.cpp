#include <vector>

void add_naive(
    const std::vector<std::vector<float>>& A,
    const std::vector<std::vector<float>>& B,
    std::vector<std::vector<float>>& C,
    int N,
    int M
) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; i < M; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
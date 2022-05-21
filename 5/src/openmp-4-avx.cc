#include <emmintrin.h>  // SSE2
#include <immintrin.h>  // AVX、AVX2
#include <nmmintrin.h>  // SSSE4.2
#include <omp.h>
#include <pmmintrin.h>  // SSE3
#include <smmintrin.h>  // SSE4.1
#include <tmmintrin.h>  // SSSE3
#include <xmmintrin.h>  // SSE

#include "main.hh"
#include "solve.hh"

using namespace std;
#define NUM_THREADS 4

void func(int& ans, float arr[], int n) {
#define matrix(i, j)  arr[(i) *n + (j)]
#define pmatrix(i, j) (arr + (i * n + j))
  int    i, j, k;
  float  tmp;
  __m256 vaik, vakj, vaij, vx;
#pragma omp parallel num_threads(NUM_THREADS), \
  private(i, j, k, tmp, vaik, vakj, vaij, vx)
  for (k = 0; k < n; ++k) {
    tmp = matrix(k, k);
#pragma omp for
    for (j = k + 1; j < n; ++j) matrix(k, j) = matrix(k, j) / tmp;
    matrix(k, k) = 1.0;
#pragma omp for
    for (i = k + 1; i < n; ++i) {
      vaik =
        _mm256_set_ps(matrix(i, k), matrix(i, k), matrix(i, k), matrix(i, k),
                      matrix(i, k), matrix(i, k), matrix(i, k), matrix(i, k));
      for (j = k + 1; j + 8 <= n; j += 8) {
        vakj = _mm256_loadu_ps(pmatrix(k, j));
        vaij = _mm256_loadu_ps(pmatrix(i, j));
        vx   = _mm256_mul_ps(vakj, vaik);
        vaij = _mm256_sub_ps(vaij, vx);
        _mm256_storeu_ps(pmatrix(i, j), vaij);
      }
      for (; j < n; ++j)
        matrix(i, j) = matrix(i, j) - matrix(i, k) * matrix(k, j);
      matrix(i, k) = 0;
    }
  }
#undef matrix
}
signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
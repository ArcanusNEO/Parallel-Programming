#include <emmintrin.h>  // SSE2
#include <immintrin.h>  // AVX、AVX2
#include <nmmintrin.h>  // SSSE4.2
#include <pmmintrin.h>  // SSE3
#include <smmintrin.h>  // SSE4.1
#include <tmmintrin.h>  // SSSE3
#include <xmmintrin.h>  // SSE

#include "main.hh"
#include "solve.hh"
using namespace std;

void func(int& ans, float arr[], int n) {
#define matrix(i, j)  arr[i * n + j]
#define pmatrix(i, j) (arr + (i * n + j))
  for (int k = 0; k < n; ++k) {
    auto vt =
      _mm_set_ps(matrix(k, k), matrix(k, k), matrix(k, k), matrix(k, k));
    int j = k + 1;
    for (; j < n && j % 4; ++j) matrix(k, j) = matrix(k, j) / matrix(k, k);
    for (; j + 4 <= n; j += 4) {
      auto va = _mm_load_ps(pmatrix(k, j));
      va      = _mm_div_ps(va, vt);
      _mm_store_ps(pmatrix(k, j), va);
    }
    for (; j < n; ++j) matrix(k, j) = matrix(k, j) / matrix(k, k);
    matrix(k, k) = 1.0;
    for (int i = k + 1; i < n; ++i) {
      auto vaik =
        _mm_set_ps(matrix(i, k), matrix(i, k), matrix(i, k), matrix(i, k));
      for (j = k + 1; j < n && j % 4; ++j)
        matrix(i, j) = matrix(i, j) - matrix(i, k) * matrix(k, j);
      for (; j + 4 <= n; j += 4) {
        auto vakj = _mm_load_ps(pmatrix(k, j));
        auto vaij = _mm_load_ps(pmatrix(i, j));
        auto vx   = _mm_mul_ps(vakj, vaik);
        vaij      = _mm_sub_ps(vaij, vx);
        _mm_store_ps(pmatrix(i, j), vaij);
      }
      for (; j < n; ++j)
        matrix(i, j) = matrix(i, j) - matrix(i, k) * matrix(k, j);
      matrix(i, k) = 0;
    }
  }
#undef matrix
#undef pmatrix
}
signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
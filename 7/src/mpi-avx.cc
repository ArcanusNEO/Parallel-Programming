#include <bits/stdc++.h>
#include <emmintrin.h>  // SSE2
#include <immintrin.h>  // AVX、AVX2
#include <mpi.h>
#include <nmmintrin.h>  // SSSE4.2
#include <pmmintrin.h>  // SSE3
#include <smmintrin.h>  // SSE4.1
#include <tmmintrin.h>  // SSSE3
#include <xmmintrin.h>  // SSE

#include "main.hh"
#include "solve.hh"
using namespace std;

#define matrix(i, j)  (arr[(i) * (n) + (j)])
#define pmatrix(i, j) (arr + ((i) * (n) + (j)))
#define prow(i)       (pmatrix(i, 0))

void func(int& ans, float arr[], int n) {
  int comm_sz;
  int my_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  MPI_Bcast(arr, n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);

  int block_sz  = n / comm_sz;
  int row_begin = block_sz * my_rank;
  int row_end   = (my_rank + 1 == comm_sz ? n : row_begin + block_sz);

  for (int k = 0; k < n; ++k) {
    int j;
    if (row_begin <= k && k < row_end) {
      auto vt =
        _mm256_set_ps(matrix(k, k), matrix(k, k), matrix(k, k), matrix(k, k),
                      matrix(k, k), matrix(k, k), matrix(k, k), matrix(k, k));
      for (j = k + 1; j + 8 <= n; j += 8) {
        auto va = _mm256_loadu_ps(pmatrix(k, j));
        va      = _mm256_div_ps(va, vt);
        _mm256_storeu_ps(pmatrix(k, j), va);
      }
      for (; j < n; ++j) matrix(k, j) /= matrix(k, k);
      matrix(k, k) = 1.0;
    }
    int bc_rank = comm_sz - 1;
    if (block_sz && k / block_sz < bc_rank) bc_rank = k / block_sz;
    MPI_Bcast(prow(k), n, MPI_FLOAT, bc_rank, MPI_COMM_WORLD);
    for (int i = max(row_begin, k + 1); i < row_end; ++i) {
      auto vaik =
        _mm256_set_ps(matrix(i, k), matrix(i, k), matrix(i, k), matrix(i, k),
                      matrix(i, k), matrix(i, k), matrix(i, k), matrix(i, k));
      for (j = k + 1; j + 8 <= n; j += 8) {
        auto vakj = _mm256_loadu_ps(pmatrix(k, j));
        auto vaij = _mm256_loadu_ps(pmatrix(i, j));
        auto vx   = _mm256_mul_ps(vakj, vaik);
        vaij      = _mm256_sub_ps(vaij, vx);
        _mm256_storeu_ps(pmatrix(i, j), vaij);
      }
      for (; j < n; ++j) matrix(i, j) -= matrix(i, k) * matrix(k, j);
      matrix(i, k) = 0;
    }
  }
}

signed main(int argc, char* argv[]) {
  _main(argc, argv);
}
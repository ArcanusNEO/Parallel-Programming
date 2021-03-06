#include <bits/stdc++.h>
#include <mpi.h>
#include <omp.h>

#include "main.hh"
#include "solve.hh"
using namespace std;

#define THREADS 4

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

  int   i, j, k;
  int   bc_rank;
  float tmp;
#pragma omp parallel num_threads(THREADS), private(i, j, k, tmp, bc_rank)
  for (k = 0; k < n; ++k) {
    if (row_begin <= k && k < row_end) {
      tmp = matrix(k, k);
#pragma omp for
      for (j = k + 1; j < n; ++j) matrix(k, j) /= tmp;
      matrix(k, k) = 1.0;
    }
    bc_rank = comm_sz - 1;
    if (block_sz && k / block_sz < bc_rank) bc_rank = k / block_sz;
#pragma omp barrier
    if (omp_get_thread_num() == 0)
      MPI_Bcast(prow(k), n, MPI_FLOAT, bc_rank, MPI_COMM_WORLD);
#pragma omp barrier
#pragma omp for
    for (i = max(row_begin, k + 1); i < row_end; ++i) {
      tmp = matrix(i, k);
      for (j = k + 1; j < n; ++j) matrix(i, j) -= tmp * matrix(k, j);
      matrix(i, k) = 0;
    }
  }
}

signed main(int argc, char* argv[]) {
  _main(argc, argv);
}
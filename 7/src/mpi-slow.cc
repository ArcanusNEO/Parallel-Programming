#include <bits/stdc++.h>
#include <mpi.h>

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
    if (row_begin <= k && k < row_end) {
      for (int j = k + 1; j < n; ++j) matrix(k, j) /= matrix(k, k);
      matrix(k, k) = 1.0;
    }
    int bc_rank = min(k / block_sz, comm_sz - 1);
    MPI_Bcast(prow(k), n, MPI_FLOAT, bc_rank, MPI_COMM_WORLD);
    int inner_block_sz  = (n - k - 1) / comm_sz;
    int inner_row_begin = k + 1 + inner_block_sz * my_rank;
    int inner_row_end =
      (my_rank + 1 == comm_sz ? n : inner_row_begin + inner_block_sz);
    for (int i = inner_row_begin; i < inner_row_end; ++i) {
      for (int j = k + 1; j < n; ++j)
        matrix(i, j) -= matrix(i, k) * matrix(k, j);
      matrix(i, k) = 0;
    }
    for (int i = 0; i < comm_sz; ++i) {
      int local_row_begin = k + 1 + inner_block_sz * i;
      int local_row_end =
        (i + 1 == comm_sz ? n : local_row_begin + inner_block_sz);
      MPI_Bcast(prow(local_row_begin), (local_row_end - local_row_begin) * n,
                MPI_FLOAT, i, MPI_COMM_WORLD);
    }
  }
}

signed main(int argc, char* argv[]) {
  _main(argc, argv);
}
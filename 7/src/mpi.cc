#include <bits/stdc++.h>
#include <mpi.h>

#include "main.hh"
#include "solve.hh"
using namespace std;

#define matrix(i, j)  (arr[(i) * (n) + (j)])
#define pmatrix(i, j) (arr + ((i) * (n) + (j)))
#define prow(i)       (pmatrix(i, 0))

void mpi_sub_func(float arr[], int n) {
  int comm_sz;
  int my_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int block_sz  = n / comm_sz;
  int row_begin = block_sz * my_rank;
  int row_end   = (my_rank + 1 == comm_sz ? row_begin + block_sz : n);

  for (int k = 0; k < n; ++k) {
    if (row_begin <= k && k < row_end) {
      for (int j = k + 1; j < n; ++j) matrix(k, j) /= matrix(k, k);
      matrix(k, k) = 1.0;
    }
    MPI_Bcast(prow(k), n, MPI_FLOAT, my_rank, MPI_COMM_WORLD);
    int inner_block_sz  = (n - k - 1) / comm_sz;
    int inner_row_begin = inner_block_sz * my_rank;
    int inner_row_end =
      (my_rank + 1 == comm_sz ? inner_row_begin + inner_block_sz : n);
    for (int i = inner_row_begin; i < inner_row_end; ++i) {
      for (int j = k + 1; j < n; ++j)
        matrix(i, j) -= matrix(i, k) * matrix(k, j);
      matrix(i, k) = 0;
    }
    MPI_Bcast(prow(inner_row_begin), (inner_row_end - inner_row_begin) * n,
              MPI_FLOAT, my_rank, MPI_COMM_WORLD);
  }
}

void mpi_func() {
  int n;
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  auto arr = (float*) aligned_alloc(32, n * n * sizeof(float));
  MPI_Bcast(arr, n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
  mpi_sub_func(arr, n);
  free(arr);
}

void func(int& ans, float arr[], int n) {
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(arr, n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
  mpi_sub_func(arr, n);
}

signed main(int argc, char* argv[]) {
  int comm_sz;
  int my_rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  if (my_rank) {
    mpi_func();
  } else {
    _main(argc, argv);
  }
  MPI_Finalize();
}
#include <mpi.h>

#include "solve.hh"
using namespace std;

double _solve(int& ans, int T) {
  int comm_sz;
  int my_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int    n;
  double ret = 0;

  if (my_rank == 0) cin >> n;
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  auto   arr = (float*) aligned_alloc(32, n * n * sizeof(float));
  float* bak = nullptr;
  if (my_rank == 0) {
    bak = (float*) aligned_alloc(32, n * n * sizeof(float));
    for (int i = 0; i < n * n; ++i) cin >> bak[i];
  }
  for (int _counter = 0; _counter < T; ++_counter) {
    ans = 0;
    if (my_rank == 0) memcpy(arr, bak, sizeof(float) * n * n);
    MPI_Barrier(MPI_COMM_WORLD);
    auto t1 = chrono::high_resolution_clock::now();
    func(ans, arr, n);
    auto t2  = chrono::high_resolution_clock::now();
    auto sec = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    ret += sec.count() / T;
  }

#define matrix(i, j) (arr[(i) * (n) + (j)])
  if (my_rank == 0) {
    cout.precision(4);
    cout.setf(ios_base::fixed);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) cout << matrix(i, j) << " \n"[j == n - 1];
  }
#undef matrix

  free(arr);
  if (bak != nullptr) free(bak);
  return ret;
}
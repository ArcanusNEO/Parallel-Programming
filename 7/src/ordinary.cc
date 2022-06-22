#include "main.hh"
#include "solve.hh"
using namespace std;
#define matrix(i, j) (arr[(i) * (n) + (j)])

void func(int& ans, float arr[], int n) {
  for (int k = 0; k < n; ++k) {
    for (int j = k + 1; j < n; ++j) matrix(k, j) /= matrix(k, k);
    matrix(k, k) = 1.0;
    for (int i = k + 1; i < n; ++i) {
      for (int j = k + 1; j < n; ++j)
        matrix(i, j) -= matrix(i, k) * matrix(k, j);
      matrix(i, k) = 0;
    }
  }
  // cout.precision(4);
  // cout.setf(ios_base::fixed);
  // for (int i = 0; i < n; ++i)
  //   for (int j = 0; j < n; ++j) cout << matrix(i, j) << " \n"[j == n - 1];
}

#undef matrix
signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
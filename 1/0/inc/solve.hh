#include <chrono>
#include <iostream>

#include "matrix.hh"
using namespace std;

template <typename T>
void func(long long& ans, const matrix_t<T>& matrix, const matrix_t<T>& vec);

double _solve(long long& ans, int T) {
  matrix_t<int> matrix, vec;
  int           n;
  double        ret = 0.0;

  cin >> n;
  matrix.resize(n, n);
  vec.resize(n);
  for (int i = 1; i <= matrix.row(); ++i)
    for (int j = 1; j <= matrix.col(); ++j) cin >> matrix(i, j);
  for (int i = 1; i <= vec.size(); ++i) cin >> vec(i);

  for (int _counter = 0; _counter < T; ++_counter) {
    ans     = 0;
    auto t1 = chrono::steady_clock::now();
    func(ans, matrix, vec);
    auto t2  = chrono::steady_clock::now();
    auto sec = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    ret += sec.count() / T;
  }
  return ret;
}
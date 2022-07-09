#include <bits/stdc++.h>

#include "constant.hh"
#include "matrix.hh"
using namespace std;

template <typename T> void gauss(matrix_t<T>& m) {
  if (m.row() != m.col()) return;
  const auto n = m.row();
  for (size_t k = 0; k < n; ++k) {
    for (size_t j = k + 1; j < n; ++j) m(k, j) /= m(k, k);
    m(k, k) = 1;
    for (size_t i = k + 1; i < n; ++i) {
      for (size_t j = k + 1; j < n; ++j) m(i, j) -= m(i, k) * m(k, j);
      m(i, k) = 0;
    }
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  for (size_t i = 0; i < lengthof(matrix_scale); ++i) {
    double           tot_time = 0.0;
    matrix_t<double> matrix(matrix_scale[i], matrix_scale[i]);
    for (size_t j = 0; j < rep_time[i]; ++j) {
      init_matrix(matrix);
      auto t1 = chrono::high_resolution_clock::now();
      gauss(matrix);
      auto t2 = chrono::high_resolution_clock::now();
      auto sec =
        chrono::duration_cast<chrono::duration<double, std::milli>>(t2 - t1);
      tot_time += sec.count();
    }
    cout.precision(9);
    cout << "N: " << matrix_scale[i] << " avg_time: " << tot_time / rep_time[i]
         << " ms" << endl;
  }
}
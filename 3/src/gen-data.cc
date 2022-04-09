#include <bits/stdc++.h>

#include "matrix.hh"
using namespace std;

signed main(int argc, char* argv[]) {
  uniform_real_distribution<float> dist(0, 100);
  mt19937                          mt(12345687);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#define endl '\n'

  int           n;
  istringstream iss(argv[1]);
  iss >> n;
  cout << n << endl;
  matrix_t<float> matrix(n, n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j < i; ++j) matrix(i, j) = 0;
    matrix(i, i) = 1.0;
    for (int j = i + 1; j <= n; ++j) matrix(i, j) = dist(mt);
  }
  for (int k = 1; k <= n; ++k)
    for (int i = k + 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j) matrix(i, j) += matrix(k, j);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) cout << matrix(i, j) << " \n"[j == n];
}
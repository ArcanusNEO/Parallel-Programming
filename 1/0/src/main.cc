#include <bits/stdc++.h>

#include "matrix.hh"

using namespace std;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#define endl '\n'

  matrix_t<int> matrix, vec;
  int           n;
  long long     ans1 = 0, ans2 = 0;

  cin >> n;
  matrix.resize(n, n);
  vec.resize(n);
  for (int i = 1; i <= matrix.row(); ++i)
    for (int j = 1; j <= matrix.col(); ++j) cin >> matrix(i, j);

  for (int i = 1; i <= vec.size(); ++i) cin >> vec(i);

  // 逐列访问的平凡算法
  for (int i = 1; i <= matrix.col(); ++i)
    for (int j = 1; j <= matrix.row(); ++j)
      ans1 += (long long) matrix(j, i) * vec(i);
  // cache优化算法
  for (int i = 1; i <= matrix.row(); ++i)
    for (int j = 1; j <= matrix.col(); ++j)
      ans2 += (long long) matrix(i, j) * vec(j);

  cout << ans1 << " " << ans2 << endl;
}
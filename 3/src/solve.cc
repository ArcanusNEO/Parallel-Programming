#include <cstring>

#include "solve.hh"
using namespace std;

double _solve(int& ans, int T) {
  int    n;
  double ret = 0.0;

  cin >> n;
  auto arr = new float[n * n];
  auto bak = new float[n * n];

  for (int i = 0; i < n * n; ++i) cin >> bak[i];
  for (int _counter = 0; _counter < T; ++_counter) {
    ans = 0;
    memcpy(arr, bak, sizeof(float) * n * n);
    auto t1 = chrono::high_resolution_clock::now();
    func(ans, arr, n);
    auto t2  = chrono::high_resolution_clock::now();
    auto sec = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    ret += sec.count() / T;
  }
#define matrix(i, j) arr[i * n + j]
  // cout.precision(4);
  // cout.setf(ios_base::fixed);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) cout << matrix(i, j) << " \n"[j == n - 1];
#undef matrix
  delete[] arr;
  delete[] bak;
  return ret;
}
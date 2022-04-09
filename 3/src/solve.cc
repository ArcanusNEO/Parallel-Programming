#include <cstring>

#include "solve.hh"
using namespace std;

double _solve(int& ans, int T) {
  int    n;
  double ret = 0.0;

  cin >> n;
  auto arr = new int[n * n];
  auto bak = new int[n * n];

  for (int i = 0; i < n * n; ++i) cin >> bak[i];
  for (int _counter = 0; _counter < T; ++_counter) {
    ans = 0;
    memcpy(arr, bak, sizeof(int) * n * n);
    auto t1 = chrono::high_resolution_clock::now();
    func(ans, arr, n);
    auto t2  = chrono::high_resolution_clock::now();
    auto sec = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    ret += sec.count() / T;
  }
  delete[] arr;
  delete[] bak;
  return ret;
}
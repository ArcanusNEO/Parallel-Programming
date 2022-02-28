#include "solve.hh"
using namespace std;

double _solve(long long& ans, int T) {
  int    n;
  double ret = 0.0;

  cin >> n;
  auto arr = new int[n];

  for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int _counter = 0; _counter < T; ++_counter) {
    ans     = 0;
    auto t1 = chrono::steady_clock::now();
    func(ans, arr, n);
    auto t2  = chrono::steady_clock::now();
    auto sec = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    ret += sec.count() / T;
  }
  delete[] arr;
  return ret;
}
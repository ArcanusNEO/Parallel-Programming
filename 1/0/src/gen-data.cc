#include <bits/stdc++.h>
using namespace std;

signed main() {
  random_device            rd;
  mt19937                  mt(rd());
  uniform_int_distribution dist(0, 100);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#define endl '\n'

  int n = 100;
  // int n = 1000;
  // int n = 10000;
  cout << n << endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) cout << dist(mt) << " ";
    cout << endl;
  }
  for (int j = 0; j < n; ++j) cout << dist(mt) << " ";
}
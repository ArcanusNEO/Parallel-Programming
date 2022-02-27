#include <bits/stdc++.h>
using namespace std;

signed main(int argc, char* argv[]) {
  random_device            rd;
  mt19937                  mt(rd());
  uniform_int_distribution dist(0, 100);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#define endl '\n'

  int           n;
  istringstream iss(argv[1]);
  iss >> n;
  cout << n << endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) cout << dist(mt) << " ";
    cout << endl;
  }
  for (int j = 0; j < n; ++j) cout << dist(mt) << " ";
}
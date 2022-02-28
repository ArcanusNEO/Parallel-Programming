#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

signed main(int argc, char* argv[]) {
  random_device            rd;
  mt19937                  mt(rd());
  uniform_int_distribution dist(-100, 100);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int           n;
  istringstream iss(argv[1]);
  iss >> n;
  cout << n << endl;
  for (int j = 0; j < n; ++j) cout << dist(mt) << " ";
}
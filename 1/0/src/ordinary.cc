#include <bits/stdc++.h>

#include "matrix.hh"

using namespace std;

#define endl '\n'

double solve(long long& ans, int T) {
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
    // 逐列访问的平凡算法
    for (int i = 1; i <= matrix.col(); ++i)
      for (int j = 1; j <= matrix.row(); ++j)
        ans += (long long) matrix(j, i) * vec(i);

    auto t2  = chrono::steady_clock::now();
    auto sec = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    ret += sec.count() / T;
  }
  return ret;
}

signed main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  string path, file;
  file = (argc > 1 ? argv[1] : "");
  ifstream   ifs;
  streambuf* cin_orig = nullptr;
  if (file != "") {
    ifs.open(file);
    cin_orig = cin.rdbuf(ifs.rdbuf());
  }
  getline(cin, path);
  if (path.back() != '/' && path.back() != '\\') {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) \
  || defined(__WINDOWS_)
    path += '\\';
#else
    path += '/';
#endif
  }
  int              count;
  map<string, int> counter;
  while (cin >> file >> count) counter[file] = count;
  ifs.close();
  cout << "Ordinary Algorithm" << endl;
  for (const auto& filename__count : counter) {
    auto filename = filename__count.first;
    auto count    = filename__count.second;
    file          = path + filename;
    ifs.open(file);
    cin.rdbuf(ifs.rdbuf());
    long long ans      = 0;
    auto      avg_time = solve(ans, count);
    cout << "file: " << filename << " result: " << ans << " repeat: " << count
         << " avg-time: " << avg_time << " s" << endl;
    ifs.close();
  }
}
#include <bits/stdc++.h>

#include "matrix.hh"

using namespace std;

#define endl '\n'

double _solve(long long& ans, int T);

signed _main(int argc, char* argv[]) {
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
  for (const auto& filename__count : counter) {
    auto filename = filename__count.first;
    auto count    = filename__count.second;
    file          = path + filename;
    ifs.open(file);
    cin.rdbuf(ifs.rdbuf());
    long long ans      = 0;
    auto      avg_time = _solve(ans, count);
    cout << "file: " << filename << " result: " << ans << " repeat: " << count
         << " avg-time: " << avg_time << " s" << endl;
    ifs.close();
  }
  return 0;
}
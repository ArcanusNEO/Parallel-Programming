#include <bits/stdc++.h>

#include "constant.hh"
#include "list_matrix.hh"
using namespace std;
namespace fs = filesystem;

void gauss(list_matrix_t& m) {
  for (auto& eliminatee : m.op) {
    while (!eliminatee.empty()) {
      auto  key        = *(eliminatee.cbegin());
      auto& eliminater = m.pool[key];
      if (eliminater.empty()) {
        eliminater = eliminatee;
        break;
      } else {
        auto jt = eliminatee.begin();
        auto it = eliminater.cbegin();
        while (it != eliminater.cend() && jt != eliminatee.end())
          if (*it > *jt) eliminatee.insert(jt, *it++);
          else if (*it == *jt) jt = eliminatee.erase(jt), ++it;
          else ++jt;
        for (; it != eliminater.cend(); ++it) eliminatee.push_back(*it);
      }
    }
  }
}

signed main(int argc, char* argv[]) {
  if (argc < 2) exit(EXIT_FAILURE);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  for (size_t i = 1; i <= cases; ++i) {
    list_matrix_t m;
    m.read(argv[1], i);
    auto t1 = chrono::high_resolution_clock::now();
    gauss(m);
    auto t2 = chrono::high_resolution_clock::now();
    auto chrono_time =
      chrono::duration_cast<chrono::duration<double, std::milli>>(t2 - t1);
    cout.precision(9);
    cout << "N: " << matrix_sz[i] << " time: " << chrono_time.count() << " ms"
         << endl;
    if (argc >= 3) {
      fs::path      out_dir(argv[2]);
      ostringstream oss;
      oss << i;
      auto     out_file = out_dir / (oss.str() + ".out");
      ofstream ofs;
      ofs.open(out_file);
      auto cout_orig = cout.rdbuf(ofs.rdbuf());
      for (const auto& line : m.op) {
        for (auto pos : line) cout << pos << " ";
        cout << '\n';
      }
      cout.rdbuf(cout_orig);
      ofs.close();
    }
  }
}
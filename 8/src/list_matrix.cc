#include <bits/stdc++.h>

#include "list_matrix.hh"
using namespace std;
namespace fs = filesystem;

void list_matrix_t::read(const char* dir, int test_case) {
  ostringstream oss;
  fs::path      res_dir(dir);
  oss << test_case;
  auto     pool_file = res_dir / (oss.str() + ".0");
  ifstream ifs;
  ifs.open(pool_file);
  cin.rdbuf(ifs.rdbuf());
  string line;
  while (getline(cin, line)) {
    istringstream iss(line);
    size_t        key, val;
    iss >> key;
    list ls = {key};
    while (iss >> val) ls.push_back(val);
    pool[key].swap(ls);
  }
  ifs.close();
  auto op_file = res_dir / (oss.str() + ".1");
  ifs.open(op_file);
  cin.rdbuf(ifs.rdbuf());
  while (getline(cin, line)) {
    istringstream iss(line);
    size_t        val;
    list<size_t>  ls;
    while (iss >> val) ls.push_back(val);
    op.push_back(move(ls));
  }
}
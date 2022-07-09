#pragma once
#include <list>
#include <map>

class list_matrix_t {
public:
  void read(const char* dir, int test_case);

  std::map<size_t, std::list<size_t>> pool;
  std::list<std::list<size_t>>        op;
};

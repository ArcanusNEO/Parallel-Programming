#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

template <typename T> class matrix_t {
public:
  matrix_t() { n = m = 0; }
  matrix_t(const matrix_t& other) {
    n = other.n;
    m = other.m;
    arr.reset(new T[n * m]);
    std::memcpy(arr.get(), other.arr.get(), n * m);
  }
  matrix_t(matrix_t&& other) {
    n = other.n;
    m = other.m;
    arr.release();
    arr.swap(other.arr);
  }

  T& operator()(size_t x, size_t y) { return arr[(x - 1) * m - 1 + y]; }
  T  operator()(size_t x, size_t y) const { return arr[(x - 1) * m - 1 + y]; }

protected:
  size_t n, m;
  // n 行 m 列
  std::unique_ptr<T> arr;
};
#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

// NOTE: 为了方便实现而采用memcpy复制T的值，所以一般而言仅支持内置类型的T
template <typename T> class matrix_t {
public:
  matrix_t() noexcept { n = m = 0; }
  matrix_t(const matrix_t& other) noexcept { this->operator=(other); }
  matrix_t(matrix_t&& other) noexcept { this->swap(other); }

  matrix_t& operator=(const matrix_t& other) noexcept {
    if (n != other.n || m != other.m) {
      n = other.n;
      m = other.m;
      arr.reset(new T[n * m]);
    }
    if (n && m) std::memcpy(arr.get(), other.arr.get(), n * m);
  }
  matrix_t& operator=(matrix_t&& other) noexcept {
    n = m = 0;
    arr.release();
    this->swap(other);
  }

  void swap(matrix_t&& other) noexcept {
    std::swap(n, other.n);
    std::swap(m, other.m);
    arr.swap(other.arr);
  }

  size_t row() const noexcept { return n; }
  size_t col() const noexcept { return m; }

  T& operator()(size_t x, size_t y) { return arr[(x - 1) * m - 1 + y]; }
  T  operator()(size_t x, size_t y) const { return arr[(x - 1) * m - 1 + y]; }

protected:
  size_t n = 0, m = 0;
  // n 行 m 列
  std::unique_ptr<T> arr;
};
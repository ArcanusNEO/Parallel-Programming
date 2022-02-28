#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

// NOTICE:
// 为了方便实现而采用memcpy和memset等低级函数处理T的值，所以一般而言仅支持内置类型的T
template <typename T> class matrix_t {
public:
  matrix_t() noexcept { n = m = 0; }
  matrix_t(const matrix_t& other) noexcept { this->operator=(other); }
  matrix_t(matrix_t&& other) noexcept { this->swap(other); }

  matrix_t& operator=(const matrix_t& other) noexcept {
    if (n != other.n || m != other.m) {
      n = other.n;
      m = other.m;
      if (n && m) arr.reset(new T[n * m]);
      else arr.release();
    }
    if (n && m) std::memcpy(arr.get(), other.arr.get(), n * m * sizeof(T));
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

  // NOTICE: 会清空内容
  size_t resize(size_t x, size_t y = 1) noexcept {
    if (n == x && m == y && n && m)
      std::memset(arr.get(), 0, n * m * sizeof(T));
    else {
      n = x;
      m = y;
      if (n && m) arr.reset(new T[n * m]());
      else arr.release();
    }
    return n * m;
  }

  void clear() noexcept {
    n = m = 0;
    arr.release();
  }

  size_t size() const noexcept { return n * m; }
  size_t row() const noexcept { return n; }
  size_t col() const noexcept { return m; }

  // 读取引用
  // NOTICE: 没有越界检查
  T& operator()(size_t x, size_t y = 1) {
    return arr.get()[(x - 1) * m + y - 1];
  }
  // 读取值
  // NOTICE: 没有越界检查
  T operator()(size_t x, size_t y = 1) const {
    return arr.get()[(x - 1) * m + y - 1];
  }

protected:
  size_t n = 0, m = 0;
  // n 行 m 列
  std::unique_ptr<T> arr;
};
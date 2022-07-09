#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <random>
#include <string>

// 简单的矩阵类，基本也可以当作普通向量或者二维数组使用，重载了 ()
// 以实现元素访问
template <typename T> class matrix_t {
public:
  matrix_t() noexcept { n = m = 0; }
  // NOTICE: 使用了 new，假设不会抛出 std::bad_alloc 异常
  matrix_t(size_t x, size_t y = 1) noexcept {
    n = m = 0;
    this->resize(x, y);
  }
  // NOTICE: 使用了 new，假设不会抛出 std::bad_alloc 异常
  matrix_t(const matrix_t<T>& other) noexcept { this->operator=(other); }
  matrix_t(matrix_t<T>&& other) noexcept { this->swap(other); }

  // NOTICE: 使用了 new，假设不会抛出 std::bad_alloc 异常
  matrix_t<T>& operator=(const matrix_t<T>& other) noexcept {
    if (n != other.n || m != other.m) {
      n = other.n;
      m = other.m;
      if (n && m) arr.reset(new T[n * m]);
      else arr.release();
    }
    if (n && m && this != &other)
      for (size_t i = 0; i < n * m; ++i) arr.get()[i] = other.arr.get()[i];
  }
  matrix_t<T>& operator=(matrix_t<T>&& other) noexcept { this->swap(other); }

  void swap(matrix_t<T>& other) noexcept {
    std::swap(n, other.n);
    std::swap(m, other.m);
    arr.swap(other.arr);
  }

  // NOTICE: 必定会清空内容
  // NOTICE: 使用了 new，假设不会抛出 std::bad_alloc 异常
  size_t resize(size_t x, size_t y = 1) noexcept {
    if (n == x && m == y && n && m)
      for (size_t i = 0; i < n * m; ++i) arr.get()[i] = T();
    else {
      n = x;
      m = y;
      if (n && m) arr.reset(new T[n * m]());
      else arr.release();
    }
    return n * m;
  }

  // NOTICE: 会删除矩阵所有信息，包括大小，如果只是想重置所有元素请使用
  // resize(row(), col())
  void clear() noexcept {
    n = m = 0;
    arr.release();
  }

  // 行数 × 列数
  size_t size() const noexcept { return n * m; }
  // 行数
  size_t row() const noexcept { return n; }
  // 列数
  size_t col() const noexcept { return m; }

  // 读取引用
  // NOTICE: 没有越界检查
  T& operator()(size_t x, size_t y = 0) { return arr.get()[x * m + y]; }
  // 读取值
  // NOTICE: 没有越界检查
  T operator()(size_t x, size_t y = 0) const { return arr.get()[x * m + y]; }

protected:
  size_t n = 0, m = 0;
  // n 行 m 列
  std::unique_ptr<T> arr;
};

template <typename T>
void init_matrix(matrix_t<T>& __matrix, uint_fast32_t __sd = 12345687,
                 T __lower_bound = 0, T __upper_bound = 100) {
  std::mt19937                      mt(__sd);
  std::uniform_real_distribution<T> dist(__lower_bound, __upper_bound);
  for (size_t i = 0; i < __matrix.row(); ++i)
    for (size_t j = 0; j < __matrix.col(); ++j) __matrix(i, j) = dist(mt);
}
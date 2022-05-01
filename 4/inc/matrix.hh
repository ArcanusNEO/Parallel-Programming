#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

// 简单的矩阵类，基本可以当作普通向量或者二维数组使用，重载了 () 以实现元素访问
template <typename T> class matrix_t {
public:
  matrix_t() noexcept { n = m = 0; }
  matrix_t(size_t x, size_t y = 1) noexcept {
    n = m = 0;
    this->resize(x, y);
  }
  matrix_t(const matrix_t<T>& other) noexcept { this->operator=(other); }
  matrix_t(matrix_t<T>&& other) noexcept { this->swap(other); }

  // NOTICE: 调用了 new，假设不会抛出 std::bad_alloc 异常
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
  // NOTICE: 调用了 new，假设不会抛出 std::bad_alloc 异常
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
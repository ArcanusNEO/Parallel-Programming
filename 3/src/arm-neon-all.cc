#include <arm_neon.h>

#include "main.hh"
#include "solve.hh"
using namespace std;

void func(int& ans, float arr[], int n) {
#define matrix(i, j)  arr[i * n + j]
#define pmatrix(i, j) (arr + (i * n + j))
  for (int k = 0; k < n; ++k) {
    auto vt = vdupq_n_f32(matrix(k, k));
    int  j;
    for (j = k + 1; j + 4 <= n; j += 4) {
      auto va = vld1q_f32(pmatrix(k, j));
      va      = vdivq_f32(va, vt);
      vst1q_f32(pmatrix(k, j), va);
    }
    for (; j < n; ++j) matrix(k, j) = matrix(k, j) / matrix(k, k);
    matrix(k, k) = 1.0;
    for (int i = k + 1; i < n; ++i) {
      auto vaik = vdupq_n_f32(matrix(i, k));
      for (j = k + 1; j + 4 <= n; j += 4) {
        auto vakj = vld1q_f32(pmatrix(k, j));
        auto vaij = vld1q_f32(pmatrix(i, j));
        auto vx   = vmulq_f32(vakj, vaik);
        vaij      = vsubq_f32(vaij, vx);
        vst1q_f32(pmatrix(i, j), vaij);
      }
      for (; j < n; ++j)
        matrix(i, j) = matrix(i, j) - matrix(i, k) * matrix(k, j);
      matrix(i, k) = 0;
    }
  }
#undef matrix
#undef pmatrix
}
signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
#include <arm_neon.h>
#include <omp.h>

#include "main.hh"
#include "solve.hh"

using namespace std;
#define NUM_THREADS 8

void func(int& ans, float arr[], int n) {
#define matrix(i, j)  arr[(i) *n + (j)]
#define pmatrix(i, j) (arr + (i * n + j))
  int         i, j, k;
  float       tmp;
  float32x4_t vaik, vakj, vaij, vx;
#pragma omp parallel num_threads(NUM_THREADS), \
  private(i, j, k, tmp, vaik, vakj, vaij, vx)
  for (k = 0; k < n; ++k) {
    tmp = matrix(k, k);
#pragma omp for
    for (j = k + 1; j < n; ++j) matrix(k, j) = matrix(k, j) / tmp;
    matrix(k, k) = 1.0;
#pragma omp for
    for (i = k + 1; i < n; ++i) {
      vaik = vdupq_n_f32(matrix(i, k));
      for (j = k + 1; j + 4 <= n; j += 4) {
        vakj = vld1q_f32(pmatrix(k, j));
        vaij = vld1q_f32(pmatrix(i, j));
        vx   = vmulq_f32(vakj, vaik);
        vaij = vsubq_f32(vaij, vx);
        vst1q_f32(pmatrix(i, j), vaij);
      }
      tmp = matrix(i, k);
      for (; j < n; ++j) matrix(i, j) = matrix(i, j) - tmp * matrix(k, j);
      matrix(i, k) = 0;
    }
  }
#undef matrix
}
signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
#include <arm_neon.h>
#include <pthread.h>
#include <semaphore.h>

#include "main.hh"
#include "solve.hh"
using namespace std;
#define matrix(i, j) arr[(i) *n + (j)]
#define pmatrix(i, j) (arr + ((i) * n + (j)))

#define MAX_SUB_THREAD 7

int    n;
float* arr;

struct thread_param_t {
  int t_id;
};

pthread_barrier_t barrier_div;
pthread_barrier_t barrier_elim;
pthread_t         handle[MAX_SUB_THREAD];
thread_param_t    param[MAX_SUB_THREAD];

void* thread_func(void* param) {
  auto p    = (thread_param_t*) param;
  auto t_id = p->t_id;
  for (int k = 0; k < n; ++k) {
    if (t_id == 0) {
      auto vt = vdupq_n_f32(matrix(k, k));
      int  j;
      for (j = k + 1; j + 4 <= n; j += 4) {
        auto va = vld1q_f32(pmatrix(k, j));
        va      = vdivq_f32(va, vt);
        vst1q_f32(pmatrix(k, j), va);
      }
      for (; j < n; ++j) matrix(k, j) = matrix(k, j) / matrix(k, k);
      matrix(k, k) = 1.0;
    }

    pthread_barrier_wait(&barrier_div);

    for (int i = k + 1 + t_id; i < n; i += MAX_SUB_THREAD) {
      auto vaik = vdupq_n_f32(matrix(i, k));
      int  j;
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

    pthread_barrier_wait(&barrier_elim);
  }
  pthread_exit(nullptr);
}

void func(int& ans, float arr[], int n) {
  ::n   = n;
  ::arr = arr;
  pthread_barrier_init(&barrier_div, nullptr, MAX_SUB_THREAD);
  pthread_barrier_init(&barrier_elim, nullptr, MAX_SUB_THREAD);

  for (int t_id = 0; t_id < MAX_SUB_THREAD; ++t_id) {
    param[t_id].t_id = t_id;
    pthread_create(handle + t_id, nullptr, thread_func, param + t_id);
  }
  for (int t_id = 0; t_id < MAX_SUB_THREAD; ++t_id)
    pthread_join(handle[t_id], nullptr);

  pthread_barrier_destroy(&barrier_div);
  pthread_barrier_destroy(&barrier_elim);
}
#undef matrix
#undef pmatrix

signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
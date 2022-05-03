#include <pthread.h>
#include <semaphore.h>

#include "main.hh"
#include "solve.hh"
using namespace std;
#define matrix(i, j) arr[(i) *n + (j)]

#define MAX_SUB_THREAD 7

int    n;
float* arr;

struct thread_param_t {
  int t_id;
};

sem_t sem_leader;
sem_t sem_div[MAX_SUB_THREAD];
sem_t sem_elim[MAX_SUB_THREAD];

void* thread_func(void* param) {
  auto p    = (thread_param_t*) param;
  auto t_id = p->t_id;
  for (int k = 0; k < n; ++k) {
    if (t_id == 0) {
      for (int j = k + 1; j < n; ++j)
        matrix(k, j) = matrix(k, j) / matrix(k, k);
      matrix(k, k) = 1.0;
    } else sem_wait(sem_div + t_id - 1);
  }
  for (int j = k + 1; j < n; ++j)
    matrix(i, j) = matrix(i, j) - matrix(i, k) * matrix(k, j);
  matrix(i, k) = 0;
  pthread_exit(nullptr);
}

void func(int& ans, float arr[], int n) {
  ::n   = n;
  ::arr = arr;
  for (int k = 0; k < n; ++k) {
    for (int j = k + 1; j < n; ++j) matrix(k, j) = matrix(k, j) / matrix(k, k);
    matrix(k, k)     = 1.0;
    int worker_count = n - 1 - k;
    for (int offset = 0; offset < worker_count; offset += MAX_SUB_THREAD) {
      for (int t_id = 0, i = t_id + offset;
           i < worker_count && t_id < MAX_SUB_THREAD;
           ++t_id, i = t_id + offset) {
        thread_param[t_id] = {k, i};
        pthread_create(thread_handle + t_id, nullptr, thread_func,
                       thread_param + t_id);
      }
      for (int t_id = 0, i                                      = t_id + offset;
           i < worker_count && t_id < MAX_SUB_THREAD; ++t_id, i = t_id + offset)
        pthread_join(thread_handle[t_id], nullptr);
    }
  }
}
#undef matrix

signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
#include <pthread.h>

#include "main.hh"
#include "solve.hh"
using namespace std;
#define matrix(i, j) arr[(i) *n + (j)]

int    n;
float* arr;

struct thread_param_t {
  int k, t_id;
};

void* thread_func(void* param) {
  auto p    = (thread_param_t*) param;
  auto k    = p->k;
  auto t_id = p->t_id;
  int  i    = k + t_id + 1;
  for (int j = k + 1; j < n; ++j)
    matrix(i, j) = matrix(i, j) - matrix(i, k) * matrix(k, j);
  matrix(i, k) = 0;
  pthread_exit(nullptr);
}

void func(int& ans, float arr[], int n) {
  ::n                = n;
  ::arr              = arr;
  auto thread_handle = new pthread_t[n];
  auto thread_param  = new thread_param_t[n];
  for (int k = 0; k < n; ++k) {
    for (int j = k + 1; j < n; ++j) matrix(k, j) = matrix(k, j) / matrix(k, k);
    matrix(k, k)     = 1.0;
    int worker_count = n - 1 - k;
    for (int t_id = 0; t_id < worker_count; ++t_id)
      thread_param[t_id] = {k, t_id};
    for (int t_id = 0; t_id < worker_count; ++t_id)
      pthread_create(thread_handle + t_id, nullptr, thread_func,
                     thread_param + t_id);

    for (int t_id = 0; t_id < worker_count; ++t_id)
      pthread_join(thread_handle[t_id], nullptr);
  }
  delete[] thread_handle;
  delete[] thread_param;
}
#undef matrix

signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
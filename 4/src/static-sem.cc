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

sem_t          sem_main;
sem_t          sem_workerstart[MAX_SUB_THREAD];
pthread_t      handle[MAX_SUB_THREAD];
thread_param_t param[MAX_SUB_THREAD];

void* thread_func(void* param) {
  auto p    = (thread_param_t*) param;
  auto t_id = p->t_id;
  for (int k = 0; k < n; ++k) {
    sem_wait(sem_workerstart + t_id);
    for (int i = k + 1 + t_id; i < n; i += MAX_SUB_THREAD) {
      for (int j = k + 1; j < n; ++j)
        matrix(i, j) = matrix(i, j) - matrix(i, k) * matrix(k, j);
      matrix(i, k) = 0;
    }
    sem_post(&sem_main);
  }
  pthread_exit(nullptr);
}

void func(int& ans, float arr[], int n) {
  ::n   = n;
  ::arr = arr;
  sem_init(&sem_main, 0, 0);
  for (int i = 0; i < MAX_SUB_THREAD; ++i) sem_init(sem_workerstart + i, 0, 0);
  for (int t_id = 0; t_id < MAX_SUB_THREAD; ++t_id) {
    param[t_id].t_id = t_id;
    pthread_create(handle + t_id, nullptr, thread_func, param + t_id);
  }
  for (int k = 0; k < n; ++k) {
    for (int j = k + 1; j < n; ++j) matrix(k, j) = matrix(k, j) / matrix(k, k);
    matrix(k, k) = 1.0;
    for (int t_id = 0; t_id < MAX_SUB_THREAD; ++t_id)
      sem_post(sem_workerstart + t_id);
    for (int t_id = 0; t_id < MAX_SUB_THREAD; ++t_id) sem_wait(&sem_main);
  }
  for (int t_id = 0; t_id < MAX_SUB_THREAD; ++t_id)
    pthread_join(handle[t_id], nullptr);
  sem_destroy(&sem_main);
  for (int i = 0; i < MAX_SUB_THREAD; ++i) sem_destroy(sem_workerstart + i);
}
#undef matrix

signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
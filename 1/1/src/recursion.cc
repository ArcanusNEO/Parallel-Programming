#include "main.hh"
#include "solve.hh"
using namespace std;

int recur(const int arr[], int n) {
  if (n <= 1) return *arr;
  int halfn = n >> 1;
  return recur(arr, halfn) + recur(arr + halfn, halfn);
}

void func(int& ans, const int arr[], int n) {
  ans = recur(arr, n);
}

signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
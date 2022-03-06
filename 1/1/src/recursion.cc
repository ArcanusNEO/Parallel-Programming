#include "main.hh"
#include "solve.hh"
using namespace std;

void recur(int arr[], int n) {
  if (n <= 1) return;
  int halfn = n >> 1;
  for (int i = 0; i < halfn; ++i) arr[i] += arr[halfn + i];
  recur(arr, halfn);
}

void func(int& ans, int arr[], int n) {
  recur(arr, n);
  ans = arr[0];
}

signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
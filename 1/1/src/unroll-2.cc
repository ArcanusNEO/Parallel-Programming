#include "main.hh"
#include "solve.hh"
using namespace std;

void func(int& ans, const int arr[], int n) {
  int sum0 = 0;
  int sum1 = 0;
  for (int i = 0; i < n; i += 2) {
    sum0 += arr[i];
    sum1 += arr[i | 1];  // i + 1
  }
  ans = sum0 + sum1;
}
signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
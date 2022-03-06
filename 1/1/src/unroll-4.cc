#include "main.hh"
#include "solve.hh"
using namespace std;

void func(int& ans, const int arr[], int n) {
  int sum0 = 0;
  int sum1 = 0;
  int sum2 = 0;
  int sum3 = 0;
  for (int i = 0; i < n; i += 4) {
    sum0 += arr[i];
    sum1 += arr[i | 1];  // i + 1
    sum2 += arr[i | 2];  // i + 2
    sum3 += arr[i | 3];  // i + 3
  }
  ans = sum0 + sum1 + sum2 + sum3;
}
signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
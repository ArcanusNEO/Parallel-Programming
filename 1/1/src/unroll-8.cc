#include "main.hh"
#include "solve.hh"
using namespace std;

void func(int& ans, int arr[], int n) {
  int sum0 = 0;
  int sum1 = 0;
  int sum2 = 0;
  int sum3 = 0;
  int sum4 = 0;
  int sum5 = 0;
  int sum6 = 0;
  int sum7 = 0;
  for (int i = 0; i < n; i += 8) {
    sum0 += arr[i];
    sum1 += arr[i | 1];  // i + 1
    sum2 += arr[i | 2];  // i + 2
    sum3 += arr[i | 3];  // i + 3
    sum4 += arr[i | 4];  // i + 4
    sum5 += arr[i | 5];  // i + 5
    sum6 += arr[i | 6];  // i + 6
    sum7 += arr[i | 7];  // i + 7
  }
  ans = sum0 + sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7;
}
signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
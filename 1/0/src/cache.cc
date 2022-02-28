#include "main.hh"
#include "solve.hh"
using namespace std;

template <typename T>
void func(long long& ans, const matrix_t<T>& matrix, const matrix_t<T>& vec) {
  // cache优化算法
  for (int i = 1; i <= matrix.row(); ++i)
    for (int j = 1; j <= matrix.col(); ++j)
      ans += (long long) matrix(i, j) * vec(j);
}

signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
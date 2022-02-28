#include "main.hh"
#include "solve.hh"
using namespace std;

template <typename T>
void func(long long& ans, const matrix_t<T>& matrix, const matrix_t<T>& vec) {
  // 逐列访问的平凡算法
  for (int i = 1; i <= matrix.col(); ++i)
    for (int j = 1; j <= matrix.row(); ++j)
      ans += (long long) matrix(j, i) * vec(i);
}

signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
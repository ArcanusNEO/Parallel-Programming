#include <mpi.h>

#include "main.hh"
using namespace std;

signed _main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);
  int comm_sz;
  int my_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  map<string, int> counter;
  size_t           counter_sz;
  int              count;
  int              ans = 0;

  if (my_rank) {
    MPI_Bcast(&counter_sz, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
    for (size_t i = 0; i < counter_sz; ++i) {
      MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
      _solve(ans, count);
    }
  } else {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string path, file;
    file = (argc > 1 ? argv[1] : "");
    ifstream   ifs;
    streambuf* cin_orig = nullptr;
    if (file != "") {
      ifs.open(file);
      cin_orig = cin.rdbuf(ifs.rdbuf());
    }
    getline(cin, path);
    if (path.back() != '/' && path.back() != '\\') {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) \
  || defined(__WINDOWS_)
      path += '\\';
#else
      path += '/';
#endif
    }
    while (cin >> file >> count) counter[file] = count;
    ifs.close();
    counter_sz = counter.size();

    MPI_Bcast(&counter_sz, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

    for (const auto& filename_count : counter) {
      const auto& filename = filename_count.first;
      count                = filename_count.second;
      file                 = path + filename;
      ifs.open(file);
      cin.rdbuf(ifs.rdbuf());

      MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
      auto avg_time = _solve(ans, count);

      cout.precision(12);
      cout.setf(ios_base::fixed);
      cout << "file: " << filename << " repeat: " << count
           << " avg-time: " << avg_time << " s" << endl;
      ifs.close();
    }
  }

  MPI_Finalize();
  return 0;
}
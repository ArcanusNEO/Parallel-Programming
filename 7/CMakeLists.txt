cmake_minimum_required(VERSION 3.9.1)
# set(CMAKE_C_COMPILER "/usr/local/bin/clang")
# set(CMAKE_CXX_COMPILER "/usr/local/bin/clang++")
# set(CMAKE_C_COMPILER "/usr/bin/aarch64-linux-gnu-gcc")
# set(CMAKE_CXX_COMPILER "/usr/bin/aarch64-linux-gnu-g++")
project(matrix LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS "-Wall -Wextra -march=armv8-a")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -march=native")
# set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
include_directories(inc)
link_directories(lib)
add_library(main SHARED src/main.cc)
add_library(mpi-main SHARED src/mpi-main.cc)
add_library(solve SHARED src/solve.cc)
add_library(mpi-solve SHARED src/mpi-solve.cc)
add_executable(gen-data src/gen-data.cc)

add_executable(ordinary src/ordinary.cc)
target_link_libraries(ordinary PRIVATE main solve)

add_executable(mpi src/mpi.cc)
target_link_libraries(mpi PRIVATE mpi-main mpi-solve)

# add_executable(mpi-neon src/mpi-neon.cc)
# target_link_libraries(mpi-neon PRIVATE mpi-main mpi-solve)

add_executable(mpi-avx src/mpi-avx.cc)
target_link_libraries(mpi-avx PRIVATE mpi-main mpi-solve)

add_executable(mpi-openmp src/mpi-openmp.cc)
target_link_libraries(mpi-openmp PRIVATE mpi-main mpi-solve)

add_executable(mpi-slow src/mpi-slow.cc)
target_link_libraries(mpi-slow PRIVATE mpi-main mpi-solve)

# set(MPI_EXECUTABLE_SUFFIX ".mpich")
find_package(MPI REQUIRED)
# add_definitions(-DOMPI_SKIP_MPICXX)
target_link_libraries(mpi PRIVATE MPI::MPI_CXX)
# target_link_libraries(mpi-neon PRIVATE MPI::MPI_CXX)
target_link_libraries(mpi-avx PRIVATE MPI::MPI_CXX)
target_link_libraries(mpi-openmp PRIVATE MPI::MPI_CXX)
target_link_libraries(mpi-slow PRIVATE MPI::MPI_CXX)

find_package(OpenMP REQUIRED)
target_link_libraries(mpi-openmp PRIVATE OpenMP::OpenMP_CXX)
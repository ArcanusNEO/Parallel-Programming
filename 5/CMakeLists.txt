cmake_minimum_required(VERSION 3.0)
# set(CMAKE_C_COMPILER "/usr/local/bin/mpicc")
# set(CMAKE_C_COMPILER "/usr/local/bin/clang")
# set(CMAKE_CXX_COMPILER "/usr/local/bin/clang++")
# set(CMAKE_C_COMPILER "/usr/bin/aarch64-linux-gnu-gcc")
# set(CMAKE_CXX_COMPILER "/usr/bin/aarch64-linux-gnu-g++")
project(matrix LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS "-Wall -march=armv8-a")
set(CMAKE_CXX_FLAGS "-Wall -march=native")
# set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
include_directories(inc)
link_directories(lib)
find_package(OpenMP REQUIRED)
add_library(main SHARED src/main.cc)
add_library(solve SHARED src/solve.cc)
add_executable(gen-data src/gen-data.cc)
add_executable(ordinary src/ordinary.cc)
add_executable(openmp-8 src/openmp-8.cc)
add_executable(openmp-4 src/openmp-4.cc)
add_executable(openmp-16 src/openmp-16.cc)
# add_executable(openmp-8-neon src/openmp-8-neon.cc)
# add_executable(openmp-4-neon src/openmp-4-neon.cc)
add_executable(openmp-8-avx src/openmp-8-avx.cc)
add_executable(openmp-4-avx src/openmp-4-avx.cc)
target_link_libraries(ordinary PRIVATE main solve)
target_link_libraries(openmp-8 PRIVATE main solve OpenMP::OpenMP_CXX)
target_link_libraries(openmp-4 PRIVATE main solve OpenMP::OpenMP_CXX)
target_link_libraries(openmp-16 PRIVATE main solve OpenMP::OpenMP_CXX)
# target_link_libraries(openmp-8-neon PRIVATE main solve OpenMP::OpenMP_CXX)
# target_link_libraries(openmp-4-neon PRIVATE main solve OpenMP::OpenMP_CXX)
target_link_libraries(openmp-8-avx PRIVATE main solve OpenMP::OpenMP_CXX)
target_link_libraries(openmp-4-avx PRIVATE main solve OpenMP::OpenMP_CXX)
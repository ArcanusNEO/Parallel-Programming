#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include "main.hh"
#include "solve.hh"
using namespace std;

#define matrix(i, j) arr[(i) *n + (j)]

__global__ void division_kernel(float arr[], int n, int k) {
  auto tid = blockDim.x * blockIdx.x + threadIdx.x;
  if (k < tid && tid < n) matrix(k, tid) /= matrix(k, k);
}

__global__ void eliminate_kernel(float arr[], int n, int k) {
  auto tid = blockDim.x * blockIdx.x + threadIdx.x;
  if (tid == 0) matrix(k, k) = 1.0;
}

void func(int& ans, float arr[], int n) {
  float* gpu_arr;
  auto   siz = sizeof(float) * n * n;
  if (cudaMalloc(&gpu_arr, siz) != cudaSuccess)
    cerr << "cudaMalloc failed" << endl;
  if (cudaMemcpy(gpu_arr, arr, siz, cudaMemcpyHostToDevice) != cudaSuccess)
    cerr << "cudaMemcpyHostToDevice failed" << endl;

  for (int k = 0; k < n; ++k) {
    auto rest = n - k;
    dim3 grid(std::ceil(rest / 1024.0));
    dim3 block(1024);
    division_kernel<<<grid, block>>>(gpu_arr, n, k);
    cudaDeviceSynchronize();
    if (auto ret = cudaGetLastError(); ret != cudaSuccess)
      cerr << "division kernel failed: " << cudaGetErrorString(ret) << endl;
    matrix(k, k) = 1.0;
    eliminate_kernel<<<grid, block>>>(gpu_arr, n, k);
    cudaDeviceSynchronize();
    if (auto ret = cudaGetLastError(); ret != cudaSuccess)
      cerr << "eliminate kernel failed: " << cudaGetErrorString(ret) << endl;
  }
  if (cudaMemcpy(arr, gpu_arr, siz, cudaMemcpyDeviceToHost) != cudaSuccess)
    cerr << "cudaMemcpyDeviceToHost failed" << endl;
  cudaFree(gpu_arr);
}

#undef matrix

signed main(int argc, char* argv[]) {
  return _main(argc, argv);
}
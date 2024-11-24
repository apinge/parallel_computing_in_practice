/* Adapted from: https://github.com/Apress/data-parallel-CPP
 *
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 */

#include <algorithm>
#include <iostream>
#include <random>

#include <sycl/sycl.hpp>

using namespace sycl;

int main()
{
  // set up queue to use the GPU
  sycl::queue Q{gpu_selector_v};
  std::cout << "Running on: " << Q.get_device().get_info<info::device::name>() <<", using backend:"<< Q.get_backend()<< std::endl;

  // initialize input and output memory on the host
  constexpr size_t N = 256;

  // allocate operands of N*N size
  auto A = sycl::malloc_host<double>(N*N, Q);
  auto B = sycl::malloc_host<double>(N*N, Q);

  // fill a and b with random numbers in the unit interval
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  for (auto i = 0; i < N * N; ++i) {
    A[i] = dist(mt);
    B[i] = dist(mt);
  }

  // allocate result of N*N size
  auto C = sycl::malloc_shared<double>(N*N, Q);;
  // zero-out c, should we wait?
  Q.fill(C,0.0f,N*N).wait();

  // submit work to queue. You can use a command group if you prefer!
  Q.parallel_for(
     range{N,N},
     [=](id<2> idx) {
       // define matrix multiplication kernel
      auto i = idx[0];
      auto j = idx[1];
      for(int k =0;k<N;++k){
        C[i*N+j] += A[i*N+k]*B[k*N+j];
      }
      
     }).wait();
  // should we wait?

  // Check that all outputs match serial execution
  bool passed = true;
  for (int j = 0; j < N; ++j) {
    for (int i = 0; i < N; ++i) {
      double gold = 0;
      for (int k = 0; k < N; ++k) {
        gold += A[j * N + k] * B[k * N + i];
      }
      if (std::abs(gold - C[j * N + i]) / gold > 1.0e-12) {
        passed = false;
      }
    }
  }
  std::cout << ((passed) ? "SUCCESS" : "FAILURE") << std::endl;
  return (passed) ? 0 : 1;
}
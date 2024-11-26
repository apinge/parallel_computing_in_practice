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
  // set up queue on GPU
  sycl::queue Q{gpu_selector_v};
  std::cout << "Running on: " << Q.get_device().get_info<info::device::name>() <<", using backend:"<< Q.get_backend()<< std::endl;

  // initialize input and output memory on the host
  constexpr size_t N = 256;
  // create operands and result of N*N size
  std::vector<double> a(N*N), b(N*N), c(N*N);

  // fill operands with random numbers in the unit interval
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  std::generate(a.begin(), a.end(), [&dist, &mt]() {
    return dist(mt);
  });
  std::generate(b.begin(), b.end(), [&dist, &mt]() {
    return dist(mt);
  });

  // zero-out c
  std::fill(c.begin(),c.end(),0.0f);

  {
    // create 2-dimensional buffers associated with inputs and output
    buffer<double, 2> a_buf(a.data(),range<2>(N,N));
    buffer<double, 2> b_buf(b.data(),range<2>(N,N));
    buffer<double, 2> c_buf(c.data(),range<2>(N,N));

    // Submit the kernel to the queue
    Q.submit([&](handler& cgh) {
      // define accessors for the buffers
      accessor a { a_buf, cgh, read_only };
      accessor b { b_buf, cgh, read_only };
      accessor c { c_buf, cgh, write_only };
      auto out = sycl::stream(1024, /* maximum size of output per kernel invocation */
                      256, /* maximum size before flushing the stream */
                     cgh);
      cgh.parallel_for(
        // Fuse an appropriate 2-dimensional range
        range{N,N}, [=](id<2> idx) {
        // mplement the matrix multiplication kernel
        auto i = idx[0];
        auto j = idx[1];
        for(int k =0;k<N;++k){
          // or c[i][j] += a[i][k]*b[k][j];
          c[idx] += a[id(i,k)] * b[id(k,j)];
          //out <<"k"<<k<<',';
        }
        out << "("<<i<<","<<j<<")\t";//You can observe that (i,j) are executed out of order.
      });

    });
  }

  // Check that all outputs match serial execution
  bool passed = true;
  for (int j = 0; j < N; ++j) {
    for (int i = 0; i < N; ++i) {
      double gold = 0;
      for (int k = 0; k < N; ++k) {
        gold += a[j * N + k] * b[k * N + i];
      }
      if (std::abs(gold - c[j * N + i]) / gold > 1.0e-12) {
        passed = false;
      }
    }
  }
  std::cout << ((passed) ? "SUCCESS" : "FAILURE") << std::endl;
  return (passed) ? 0 : 1;
}

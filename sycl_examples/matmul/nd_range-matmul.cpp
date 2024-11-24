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
  queue Q{gpu_selector_v};
  // initialize input and output memory on the host
  constexpr size_t N = 256;

  // create operands and result of N*N size
  std::vector<double> a(N*N), b(N*N), c(N*N);

  // fill operands with random numbers in the unit interval
  // hint: you call dist(mt) to get one random number
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
    // size of local range
    constexpr size_t B = 4;
    // Create 2-dimensional buffers associated with inputs and output
    buffer<double, 2> a_buf(a.data(),range<2>(N,N)),b_buf(b.data(),range<2>(N,N)), c_buf(c.data(),range<2>(N,N));

    // submit work to the queue
    Q.submit([&](handler& cgh) {
      // define accessors for the buffers
      accessor a { a_buf, cgh, read_only };
      accessor b { b_buf, cgh, read_only };
      accessor c { c_buf, cgh, write_only };

      // declare global and local 2-dimensional ranges
      range global { N,N };
      // hint: the dimensions in the local range should divide exactly those in
      // the global range
      range local { B,B };
      //auto out = sycl::stream(1024,256,cgh);
      // use nd_range with appropriate global and local ranges
      cgh.parallel_for(nd_range {global,local}, [=](nd_item<2> it) {
        // implement the matrix multiplication kernel
        auto i = it.get_global_id(0);
        auto j = it.get_global_id(1);
        //auto ii = it.get_local_id(0);
        //auto jj = it.get_local_id(1);
       // out <<it.get_group_range()[0]<<' '<<it.get_global_range()[1]<< "\n";//64 256?
       // out << "("<<i<<","<<j << "):"<<"["<<ii<<","<<jj << "],";
        for(int k = 0;k<N;++k)
          c[i][j] += a[i][k]*b[k][j];
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

#include <cstdlib>
#include <string>
#include <iostream>
#include "libtest.h"
#include "sycl/sycl.hpp"

using namespace sycl;

void VectorAddKernel(queue &q, buffer<int, 1> &bufferA, buffer<int, 1> &bufferB, buffer<int, 1> &bufferC, unsigned long vector_len);
extern "C" int vector_add(int *a, int *b, int *c, unsigned long vector_len) {
    try {
        sycl::device gpu_device = sycl::device(sycl::gpu_selector_v);
        std::string name = gpu_device.get_platform().get_info<info::platform::name>();
        std::cout << "Platform: " << name << std::endl;

        queue q(gpu_device);
        sycl::range<1> numOfItems{vector_len};
        sycl::buffer<int, 1> bufferA(a, numOfItems);
        sycl::buffer<int, 1> bufferB(b, numOfItems);
        sycl::buffer<int, 1> bufferC(c, numOfItems);
        // 在此可以添加 SYCL 计算逻辑，例如：
        VectorAddKernel(q, bufferA, bufferB, bufferC, vector_len);
        
    } catch (exception const &e) {
        std::cout << "An exception is caught for vector add.\n";
        return -1;
    }
    return 0;
}
void VectorAddKernel(queue &q, buffer<int, 1> &bufferA, buffer<int, 1> &bufferB, buffer<int, 1> &bufferC, unsigned long vector_len) {
    q.submit([&](handler &h) {
        auto a = bufferA.get_access<access::mode::read>(h);
        auto b = bufferB.get_access<access::mode::read>(h);
        auto c = bufferC.get_access<access::mode::write>(h);

        h.parallel_for(range<1>(vector_len), [=](id<1> i) {
            c[i] = a[i] + b[i];
        });
    }).wait();
}
// ref https://github.com/xipingyan/hw_optimization/blob/main/intel_gpu/opencl_learn/CodeSamples/01_HelloOpenCL/src/main.cpp
#include <stdio.h>
#include <iostream>
#include <CL/opencl.hpp>
#include <stddef.h>
#include <stdint.h>
#include <chrono>


std::string kernel_code = R"(
#define INC1(x) ((x) = (x) + 1);

#define INC10(x)                                                               \
  INC1(x)                                                                      \
  INC1(x)                                                                      \
  INC1(x)                                                                      \
  INC1(x)                                                                      \
  INC1(x)                                                                      \
  INC1(x)                                                                      \
  INC1(x)                                                                      \
  INC1(x)                                                                      \
  INC1(x)                                                                      \
  INC1(x)

#define INC100(x)                                                              \
  INC10(x)                                                                     \
  INC10(x)                                                                     \
  INC10(x)                                                                     \
  INC10(x)                                                                     \
  INC10(x)                                                                     \
  INC10(x)                                                                     \
  INC10(x)                                                                     \
  INC10(x)                                                                     \
  INC10(x)                                                                     \
  INC10(x)

#define INC1000(x)                                                             \
  INC100(x)                                                                    \
  INC100(x)                                                                    \
  INC100(x)                                                                    \
  INC100(x)                                                                    \
  INC100(x)                                                                    \
  INC100(x)                                                                    \
  INC100(x)                                                                    \
  INC100(x)                                                                    \
  INC100(x)                                                                    \
  INC100(x)

#define INC10000(x)                                                            \
  INC1000(x)                                                                   \
  INC1000(x)                                                                   \
  INC1000(x)                                                                   \
  INC1000(x)                                                                   \
  INC1000(x)                                                                   \
  INC1000(x)                                                                   \
  INC1000(x)                                                                   \
  INC1000(x)                                                                   \
  INC1000(x)                                                                   \
  INC1000(x)

// OpenCL Kernel
__kernel void increment_kernel(__global int* data) {
    int gid = get_global_id(0);
    int value = data[gid];
   
    INC10000(value);
    data[gid] = value;
    
}
)";

int main() {

    const int num_elements = 1;
    std::vector<int> data(num_elements, 0);

    cl::Platform platform = cl::Platform::getDefault();
    cl::Device device = cl::Device::getDefault();
     auto start = std::chrono::steady_clock::now();
    cl::Context context({ device });
    cl::CommandQueue queue(context, device);

   
    cl::Buffer buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * data.size(), data.data());

  
    cl::Program program(context, kernel_code);
    program.build({ device });


    cl::Kernel kernel(program, "increment_kernel");
    kernel.setArg(0, buffer);


    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(num_elements));
    queue.finish();


    queue.enqueueReadBuffer(buffer, CL_TRUE, 0, sizeof(int) * data.size(), data.data());
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed kernel time: " << elapsed_seconds.count() << "s\n";

    for (int i = 0; i < data.size(); ++i) {
        std::cout << "data[" << i << "] = " << data[i] << std::endl;
    }

    return 0;
}

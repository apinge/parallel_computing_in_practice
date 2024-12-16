#include <CL/cl.h>
#include <iostream>
#include <chrono>

// Increment kernel as a string for OpenCL
const char *kernelSource = R"(
kernel void Inc(global int *data) {
    int gid = get_global_id(0);
    for (int i = 0; i < 100000; ++i) {
        data[gid]++;
    }
}
)";

// Helper function to check OpenCL errors
void checkError(cl_int err, const char *operation) {
    if (err != CL_SUCCESS) {
        std::cerr << "Error during operation '" << operation << "': " << err << std::endl;
        exit(1);
    }
}

int main() {
    cl_int err;

    // Step 1: Platform and Device Setup
    cl_uint numPlatforms;
    checkError(clGetPlatformIDs(0, nullptr, &numPlatforms), "clGetPlatformIDs");
    cl_platform_id platform;
    checkError(clGetPlatformIDs(1, &platform, nullptr), "clGetPlatformIDs");

    cl_uint numDevices;
    checkError(clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, nullptr, &numDevices), "clGetDeviceIDs");
    cl_device_id device;
    checkError(clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, nullptr), "clGetDeviceIDs");

    // Step 2: Create Context
    cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &err);
    checkError(err, "clCreateContext");

    // Step 3: Create Command Queue
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);
    checkError(err, "clCreateCommandQueue");

    // Step 4: Create and Build Program
    auto start = std::chrono::steady_clock::now();

    cl_program program = clCreateProgramWithSource(context, 1, &kernelSource, nullptr, &err);
    checkError(err, "clCreateProgramWithSource");

    err = clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);
    if (err != CL_SUCCESS) {
        // Print build log on failure
        size_t logSize;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &logSize);
        std::vector<char> log(logSize);
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, log.data(), nullptr);
        std::cerr << "Build log:\n" << log.data() << std::endl;
        checkError(err, "clBuildProgram");
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed build time: " << elapsed_seconds.count() << "s\n";

    // Step 5: Create Kernel
    cl_kernel kernel = clCreateKernel(program, "Inc", &err);
    checkError(err, "clCreateKernel");

    // Step 6: Create Buffer
    int data = 0;
    cl_mem buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int), &data, &err);
    checkError(err, "clCreateBuffer");

    // Step 7: Set Kernel Arguments
    checkError(clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer), "clSetKernelArg");

    // Step 8: Execute Kernel
    size_t globalWorkSize = 1;
    start = std::chrono::steady_clock::now();
    checkError(clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &globalWorkSize, nullptr, 0, nullptr, nullptr), "clEnqueueNDRangeKernel");
    checkError(clFinish(queue), "clFinish");
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Elapsed kernel execution time: " << elapsed_seconds.count() << "s\n";

    // Step 9: Read Results
    checkError(clEnqueueReadBuffer(queue, buffer, CL_TRUE, 0, sizeof(int), &data, 0, nullptr, nullptr), "clEnqueueReadBuffer");
    std::cout << "Result: " << data << std::endl;

    // Step 10: Cleanup
    clReleaseMemObject(buffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    return 0;
}

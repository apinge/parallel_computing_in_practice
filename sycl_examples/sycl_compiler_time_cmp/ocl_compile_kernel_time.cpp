// Reference:

#include <stdio.h>
#include <iostream>
#include <CL/opencl.hpp>
#include <stddef.h>
#include <stdint.h>

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



int main()
{
	std::cout << "== Hello OpenCL(CPP)." << std::endl;
	// get all platforms (drivers)
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if (all_platforms.size() == 0)
	{
		std::cout << " No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform default_platform = all_platforms[0];
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

	// get default device of the default platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if (all_devices.size() == 0)
	{
		std::cout << " No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Device default_device = all_devices[0];
	std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";
	auto start = std::chrono::steady_clock::now();
	std::cout << "== Create context" << std::endl;
	cl::Context context({default_device});

	std::cout << "== Create Sources" << std::endl;
	cl::Program::Sources sources;

	
                                                                           

	std::cout << "== Put kernel string to source." << std::endl;
	sources.push_back({kernel_code.c_str(), kernel_code.length()});

	std::cout << "== Construct program with source and context." << std::endl;
	cl::Program program(context, sources);
	auto start1 = std::chrono::steady_clock::now();
	if (program.build({default_device}) != CL_SUCCESS)
	{
		std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << "\n";
		exit(1);
	}
	auto end1 = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
	std::cout << "elapsed build time: " << elapsed_seconds1.count() << "s\n";
	// create buffers on the device
	const int num_elements = 1;
	std::vector<int> data(num_elements, 0);
	cl::Buffer buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * data.size(), data.data());


	std::cout << "== Create command queue" << std::endl;
	// create queue to which we will push commands for the device.
	cl::CommandQueue queue(context, default_device);

	// write data to the device
	queue.enqueueWriteBuffer(buffer, CL_TRUE, 0, sizeof(int) * num_elements, data.data());



	std::cout << "== Create Kernel with program and run." << std::endl;
	// alternative way to run the kernel
	cl::Kernel kernel = cl::Kernel(program, "increment_kernel");
	kernel.setArg(0, buffer);

	//queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1), cl::NullRange);
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(num_elements));
	queue.finish();

	// compute kernel time
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "== elapsed kernel time: " << elapsed_seconds.count() << "s\n ==";

	std::cout << "== Read result." << std::endl;
	int res[1];
	// read result C from the device to array C
	queue.enqueueReadBuffer(buffer, CL_TRUE, 0, sizeof(int) * num_elements, res);

	int expected = 10000;

	std::cout << "== Start compare result with expected.\n";
	bool is_expected = true;

	if (expected != res[0])
	{
		std::cout << " Result " << res[0] << "!=" << " Expected " << expected << std::endl;
		is_expected = false;
	}
	

	std::cout << "== Result is_expected == " << std::boolalpha << is_expected << std::endl;
	std::cout << "== Done." << std::endl;
	return 0;
}
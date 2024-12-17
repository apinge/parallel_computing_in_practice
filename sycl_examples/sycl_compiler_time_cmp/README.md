### Contents
* `sycl_compile_kernel_time.cpp` - sycl kernel compiled in sycl code (tested in `build_sycl.bat` `build_sycl.sh`)
* `ocl_compile_kernel_time.cpp` - ocl kernel compiled in ocl code   (tested in `build_ocl.bat`)
* `kernel_compiler_opencl.cpp` - ocl kernel compiled in sycl code  (tested in `build_sycl_ocl_kernel.bat`)

### How to enable ocl and l0 cache 
https://github.com/intel/compute-runtime/blob/master/programmers-guide/COMPILER_CACHE.md

for example  ocl cache default is located in C:\Users\YourUserName\AppData\Local\NEO\neo_compiler_cache

### How to enable sycl cache
https://github.com/intel/llvm/blob/sycl/sycl/doc/EnvironmentVariables.md


https://intel.github.io/llvm/design/KernelProgramCache.html


### OCL kernel built by SYCL
When SYCL code is used to build an OpenCL kernel, the generated cache is stored in .l0_cache.


### Related compiler option
`-fsycl-device-code-split`
https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2024-1/fsycl-device-code-split.html

From experience, if there are many kernels in the code, but only one will actually be used during runtime, then setting `per_kernel` will save JIT time. If every kernel will be used, then adding this option should not make much difference.

### SYCL_EXTERNAL
https://www.intel.com/content/www/us/en/developer/articles/technical/use-the-sycl-external-macro.html
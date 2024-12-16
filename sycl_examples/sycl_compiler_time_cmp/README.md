### How to enable ocl cache 
https://github.com/intel/compute-runtime/blob/master/programmers-guide/COMPILER_CACHE.md

ocl cache default is on
for example in o C:\Users\myUserName\AppData\Local\NEO\neo_compiler_cache

### How to enable sycl cache
https://github.com/intel/llvm/blob/sycl/sycl/doc/EnvironmentVariables.md


### OCL kernel built by SYCL
When SYCL code is used to build an OpenCL kernel, the generated cache is stored in .l0_cache.


### related compiler option
`-fsycl-device-code-split`


https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2024-1/fsycl-device-code-split.html


### SYCL_EXTERNAL
https://www.intel.com/content/www/us/en/developer/articles/technical/use-the-sycl-external-macro.html
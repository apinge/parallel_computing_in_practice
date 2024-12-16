@echo on
:: Enable command echoing for better visibility

::Set environment variables
echo Setting environment variables...
set SYCL_CACHE_PERSISTENT=1
echo SYCL_CACHE_PERSISTENT set to %SYCL_CACHE_PERSISTENT%
set SYCL_CACHE_DIR=cache_dir
echo SYCL_CACHE_DIR set to %SYCL_CACHE_DIR%

::Compile the C++ file with SYCL support
echo Compiling kernel_compiler_opencl.cpp into kernel_compiler_opencl.exe...
echo icpx -fsycl -O3 kernel_compiler_opencl.cpp -o kernel_compiler_opencl.exe
icpx -fsycl -O3 kernel_compiler_opencl.cpp -o kernel_compiler_opencl.exe

::Run the executable twice
echo Running kernel_compiler_opencl.exe for the first time...
kernel_compiler_opencl.exe

echo Running kernel_compiler_opencl.exe for the second time...
kernel_compiler_opencl.exe

::Indicate script completion
echo Script execution complete.

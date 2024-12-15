@echo on
:: Enable command echoing for better visibility

::Set environment variables
echo Setting environment variables...
set SYCL_CACHE_PERSISTENT=1
echo SYCL_CACHE_PERSISTENT set to %SYCL_CACHE_PERSISTENT%
set SYCL_CACHE_DIR=cache_dir
echo SYCL_CACHE_DIR set to %SYCL_CACHE_DIR%

::Compile the C++ file with SYCL support
echo Compiling sycl_compile_kernel_time.cpp into sycl_compile_kernel_time.exe...
echo icpx -fsycl -O3 sycl_compile_kernel_time.cpp -o sycl_compile_kernel_time.exe
icpx -fsycl -O3 sycl_compile_kernel_time.cpp -o sycl_compile_kernel_time.exe

::Run the executable twice
echo Running sycl_compile_kernel_time.exe for the first time...
sycl_compile_kernel_time.exe

echo Running sycl_compile_kernel_time.exe for the second time...
sycl_compile_kernel_time.exe

::Indicate script completion
echo Script execution complete.

@echo on
:: Enable command echoing for better visibility

::Set environment variables
echo Setting environment variables...
set SYCL_CACHE_PERSISTENT=1
echo SYCL_CACHE_PERSISTENT set to %SYCL_CACHE_PERSISTENT%
set SYCL_CACHE_DIR=cache_dir
echo SYCL_CACHE_DIR set to %SYCL_CACHE_DIR%

::Compile the C++ file with SYCL support
echo Compiling sycl_compile_kernel_time.cpp into a.exe...
echo icpx -fsycl sycl_compile_kernel_time.cpp -o a.exe
icpx -fsycl sycl_compile_kernel_time.cpp -o a.exe

::Run the executable twice
echo Running a.exe for the first time...
a.exe

echo Running a.exe for the second time...
a.exe

::Indicate script completion
echo Script execution complete.

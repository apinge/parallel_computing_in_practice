@echo off
setlocal


rem Replace with your actual Intel oneAPI compiler version
icpx ocl_compile_kernel_time.cpp -I"C:\\Users\\gta\\source\\repos\\parallel_computing_in_practice\\sycl_examples\\sycl_compiler_time_cmp\\OpenCL-SDK\\include" -L"C:\\Users\\gta\\source\\repos\\parallel_computing_in_practice\\sycl_examples\\sycl_compiler_time_cmp\\OpenCL-SDK\\include\\OpenCL-SDK\\lib" -lOpenCL -o ocl_compile_kernel_time.exe
rem -fuse-ld=lld
rem icx Main.c /I"C:\\Users\\gta\\source\\repos\\parallel_computing_in_practice\\sycl_examples\\sycl_compiler_time_cmp\\OpenCL-SDK\\include" /LIBPATH:"C:\\Users\\gta\\source\\repos\\parallel_computing_in_practice\\sycl_examples\\sycl_compiler_time_cmp\\OpenCL-SDK\\lib" OpenCL.lib /o Main.exe
rem icx-cl ocl_compiler_time.cpp  /I"C:\\Users\\gta\\source\\repos\\parallel_computing_in_practice\\sycl_examples\\sycl_compiler_time_cmp\\OpenCL-SDK\\include" /LIBPATH"C:\\Users\\gta\\source\\repos\\parallel_computing_in_practice\\sycl_examples\\sycl_compiler_time_cmp\\OpenCL-SDK\\lib"  OpenCL.lib  /ENTRY:mainCRTStartup

::Run the executable twice
echo Running ocl_compile_kernel_time.exe for the first time...
ocl_compile_kernel_time.exe

echo Running ocl_compile_kernel_time.exe for the second time...
ocl_compile_kernel_time.exe


endlocal
cmake_minimum_required(VERSION 3.10)


project(detect_opencl_device VERSION 1.0)


set(OPENCL_SDK_PATH "OpenCL_SDK")  # Please modify according to the actual path


include_directories("${OPENCL_SDK_PATH}/include")
include_directories("${OPENCL_SDK_PATH}/include/CL")


link_directories("${OPENCL_SDK_PATH}/lib")


add_executable(OpenCLExample detect_opencl_device.c) 


target_link_libraries(OpenCLExample OpenCL)

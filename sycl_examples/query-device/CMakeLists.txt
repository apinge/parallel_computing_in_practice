if(UNIX)
    # Direct CMake to use icpx rather than the default C++ compiler/linker
    set(CMAKE_CXX_COMPILER icpx)
else() # Windows
    # Force CMake to use icx-cl rather than the default C++ compiler/linker 
    # (needed on Windows only)
    include (CMakeForceCompiler)
    include_directories("C:/Program Files (x86)/Intel/oneAPI/compiler/latest/include")
    link_directories("C:/Program Files (x86)/Intel/oneAPI/compiler/latest/lib")
    CMAKE_FORCE_CXX_COMPILER ("C:/Program Files (x86)/Intel/oneAPI/compiler/latest/bin/icx-cl.exe" IntelDPCPP)
    include (Platform/Windows-Clang)
endif()

cmake_minimum_required (VERSION 3.4)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(QueryDevice CXX)
add_compile_options("/std:c++17")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory (src)

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
project(SingleTask CXX)
add_compile_options("/std:c++17")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


# This is a Windows-specific flag that enables exception handling in host code
if(WIN32)
    set(WIN_FLAG "/EHsc")
endif()

#
# SECTION 1
# This section defines rules to create a cpu-gpu make target
# This can safely be removed if your project is only targetting FPGAs
#

set(COMPILE_FLAGS "-fsycl -Wall ${WIN_FLAG}")
set(LINK_FLAGS "-fsycl")

set(SOURCE_FILE range-matmul.cpp)
set(TARGET_NAME range-matmul)

# To compile in a single command:
#    icpx -fsycl <file>.cpp -o <file>
# CMake executes:
#    [compile] icpx -fsycl -o <file>.cpp.o -c <file>.cpp
#    [link]    icpx -fsycl <file>.cpp.o -o <file>
add_executable(${TARGET_NAME} ${SOURCE_FILE})
set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")


set(SOURCE_FILE1 usm-range-matmul.cpp)
set(TARGET_NAME1 usm-range-matmul)
# To compile in a single command:
#    icpx -fsycl <file>.cpp -o <file>
# CMake executes:
#    [compile] icpx -fsycl -o <file>.cpp.o -c <file>.cpp
#    [link]    icpx -fsycl <file>.cpp.o -o <file>
add_executable(${TARGET_NAME1} ${SOURCE_FILE1})
set_target_properties(${TARGET_NAME1} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
set_target_properties(${TARGET_NAME1} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")

set(SOURCE_FILE2 nd_range-matmul.cpp)
set(TARGET_NAME2 nd_range-matmul)
# To compile in a single command:
#    icpx -fsycl <file>.cpp -o <file>
# CMake executes:
#    [compile] icpx -fsycl -o <file>.cpp.o -c <file>.cpp
#    [link]    icpx -fsycl <file>.cpp.o -o <file>
add_executable(${TARGET_NAME2} ${SOURCE_FILE2})
set_target_properties(${TARGET_NAME2} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
set_target_properties(${TARGET_NAME2} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")


set(SOURCE_FILE3 usm-nd_range-matmul.cpp)
set(TARGET_NAME3 usm-nd_range-matmul)
# To compile in a single command:
#    icpx -fsycl <file>.cpp -o <file>
# CMake executes:
#    [compile] icpx -fsycl -o <file>.cpp.o -c <file>.cpp
#    [link]    icpx -fsycl <file>.cpp.o -o <file>
add_executable(${TARGET_NAME3} ${SOURCE_FILE3})
set_target_properties(${TARGET_NAME3} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
set_target_properties(${TARGET_NAME3} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")


set(SOURCE_FILE4 tiled-matmul.cpp)
set(TARGET_NAME4 tiled-matmul)
# To compile in a single command:
#    icpx -fsycl <file>.cpp -o <file>
# CMake executes:
#    [compile] icpx -fsycl -o <file>.cpp.o -c <file>.cpp
#    [link]    icpx -fsycl <file>.cpp.o -o <file>
add_executable(${TARGET_NAME4} ${SOURCE_FILE4})
set_target_properties(${TARGET_NAME4} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
set_target_properties(${TARGET_NAME4} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")




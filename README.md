# parallel-computing-lab
Examples of deploying and computing with SYCL, OpenCL, Level Zero nd OpenMP on GPU devices for enhanced parallel performance, primarily on the Windows platform.


## Setting Up the SYCL Compilation Environment on Windows
### Basic Setting
1. Download and install the GPU driver according to the instructions provided in [How to Install an Intel® Graphics Driver in Windows® 10 & Windows 11*](https://www.intel.com/content/www/us/en/support/articles/000005629/graphics/processor-graphics.html)

2. Download and install the latest oneAPI Base Toolkit from [Get the Intel® oneAPI Base Toolkit](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html)


    You only need to install the following four components:
    - Intel® oneAPI DPC++/C++ Compiler
    - Intel® oneAPI DPC++ Library
    - Intel® Distribution for GDB
    - Intel® oneAPI Threading Building Blocks.

3. Search for **Intel oneAPI Command Prompt for Intel 64 for Visual Studio 2022** in the Windows search bar,  or directly call the oneAPI `setvars.bat` (usually located in `C:\Program Files (x86)\Intel\oneAPI`), then type `sycl-ls` and press Enter to check your SYCL device and backend.
If you find a GPU device but no Level Zero backend, and only the OpenCL backend is available, you may consider deleting the registry key `[HKEY_LOCAL_MACHINE\SOFTWARE\Khronos\OpenCL]` and then restarting the oneAPI setvars script. Then, you can find that the GPU has both OpenCL backend and Level Zero backend options available.
```
C:\Program Files (x86)\Intel\oneAPI>sycl-ls
[level_zero:gpu][level_zero:0] Intel(R) oneAPI Unified Runtime over Level-Zero, Intel(R) Arc(TM) Graphics 12.71.4 [1.3.29516]
[opencl:gpu][opencl:0] Intel(R) OpenCL Graphics, Intel(R) Arc(TM) Graphics OpenCL 3.0 NEO  [31.0.101.5592]
```

You can use the environment variable [**ONEAPI_DEVICE_SELECTOR**](https://github.com/intel/llvm/blob/sycl/sycl/doc/EnvironmentVariables.md#oneapi_device_selector) to specifiy the backend.

### Enabling Clang in the oneAPI Compiler

The oneAPI installation package includes tools such as clang, clang++, and other Clang utilities. By default, these are not used, but you can access them using specific commands `---include-intel-llvm`.
```
C:\Program Files (x86)\Intel\oneAPI>setvars.bat ---include-intel-llvm
C:\Program Files (x86)\Intel\oneAPI>where clang
C:\Program Files (x86)\Intel\oneAPI\compiler\latest\bin\compiler\clang.exe
```
clang exposes more switches like `-emit-llvm`, which makes it easier to view the LLVM IR compared to icx.





## Setting Up the Level Zero Development Environment on Windows
You can directly find the release package at https://github.com/oneapi-src/level-zero. The release package does not include the runtime DLLs. You can build the runtime DLLs, such as `ze_loader.dll`, yourself.


## About Debugging
I recommend checking out this repository to find the release package (e.g., llvm-mingw-20241030-msvcrt-x86_64). After downloading and extracting the package, locate **lldb.exe**. Then, in the oneAPI setvars environment, launch lldb with your executable, like so
```
C:\Users\gta\Downloads\llvm-mingw-20241030-msvcrt-x86_64\bin>lldb.exe C:\target.exe
```
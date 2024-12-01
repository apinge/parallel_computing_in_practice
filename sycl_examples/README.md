## SYCL tutorial
https://enccs.github.io/sycl-workshop/what-is-sycl/
https://github.khronos.org/SYCL_Reference/iface/defining-kernels.html


## SYCL Programming Tutorial Source Code
Our source code is based on the following repository, with additional modifications. The compiler used is oneAPI 2025.

- [sycl-workshop](https://github.com/ENCCS/sycl-workshop)
- [data-parallel-CPP](https://github.com/Apress/data-parallel-CPP)

## About Compiler Driver
https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2024-1/invoke-the-compiler.html


## Configuring the IntelliSense Environment in VSCode

* Installe `C/C++ Extension` (note: do not install `clangd` simultaneously)
* Press `Ctrl + Shift + P` to open the Command Palette. Select  `C/C++: Edit Configurations (JSON)` to edit the `c_cpp_properties.json` file. (If you cannot find C++: Edit Configurations (JSON), follow [Visual Studio Code - C/C++ Extension commands don't exist](https://stackoverflow.com/questions/72673961/visual-studio-code-c-c-extension-commands-dont-exist) for troubleshooting steps.)
* In the `c_cpp_properties.json` file, you can specify the include path for SYCL. For example:
```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C://Program Files (x86)//Intel//oneAPI//compiler//latest//include",
                "C://Program Files (x86)//Intel//oneAPI//compiler//latest//include//sycl",
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.22621.0",
            "compilerPath": "cl.exe", // keeping msvc here for intellisence configuration
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-msvc-x64"
            //"intelliSenseMode": "windows-clang-x64"
        }
    ],
    "version": 4
}
```
Then you can get IntelliSense suggestions and class completions in VS Code.

## Debugger with gdb-oneapi
https://www.intel.com/content/www/us/en/docs/oneapi/user-guide-vs-code/2023-1/gdb-gpu-support-for-intel-oneapi-toolkits.html

# SYCL with MKL
https://www.alcf.anl.gov/sites/default/files/2024-06/oneMKL_Argonne_v01.pdf
https://www.intel.com/content/www/us/en/docs/oneapi/programming-guide/2024-1/onemkl-usage.html

More examples can be found in C:\Program Files (x86)\Intel\oneAPI\mkl\latest\share\doc\mkl\examples

# Official SYCL examples
https://github.com/intel/llvm/tree/sycl/sycl/test-e2e



# SYCL libraries
https://github.com/codeplaysoftware/portBLAS
https://github.com/codeplaysoftware/portDNN
https://github.com/intel/xetla

# Reference 
https://www.ospray.org/documentation.html

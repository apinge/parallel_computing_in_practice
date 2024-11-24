## SYCL tutorial
https://enccs.github.io/sycl-workshop/what-is-sycl/

## SYCL Programming Tutorial Source Code
Our source code is based on the following repository, with additional modifications. The compiler used is oneAPI 2025.

- [sycl-workshop](https://github.com/ENCCS/sycl-workshop)
- [data-parallel-CPP](https://github.com/Apress/data-parallel-CPP)

## Configuring the IntelliSense Environment in VSCode

* Installe `C/C++ Extension` (note: do not install `clangd` simultaneously)
* Press `Ctrl + Shift + P` to open the Command Palette. Select  `C/C++: Edit Configurations (JSON)` to edit the `c_cpp_properties.json` file. (If you cannot find C++: Edit Configurations (JSON), follow [Visual Studio Code - C/C++ Extension commands don't exist](https://stackoverflow.com/questions/72673961/visual-studio-code-c-c-extension-commands-dont-exist) for troubleshooting steps.)
* In the c_cpp_properties.json file, you can specify the include path for SYCL. For example:
```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C://Program Files (x86)//Intel//oneAPI//compiler//latest//include"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.22621.0",
            "compilerPath": "C://Program Files (x86)//Intel//oneAPI//compiler//latest//bin//icx-cl.exe",
            //compilerPath": "cl.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-msvc-x64"
            //"intelliSenseMode": "windows-clang-x64"
        }
    ],
    "version": 4
}
```
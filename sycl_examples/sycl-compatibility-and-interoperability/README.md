# Interoperability of Libraries Built with ICX -fsycl and Other Compilers

## Install SYCL runtime 
Besides installing the oneAPI package, you can also install the SYCL runtime separately.
https://www.intel.com/content/www/us/en/developer/articles/tool/compilers-redistributable-libraries-by-version.html

For Linux, you can refer to [intel/oneapi-runtime dockerhub](https://hub.docker.com/r/intel/oneapi-runtime), e.g. https://github.com/intel/oneapi-containers/blob/master/images/docker/runtime/Dockerfile.ubuntu-24.04


## Use SYCL Shared Library With Third-Party Applications

To build shared libraries containing SYCL code for use in host applications (compiled with MSVC or GCC), we need to consider both source and binary compatibility. You can achieve this by exposing both C and C++ interfaces. The C API is often the safest bet to minimize compatibility headaches. For more details, you can refer to the documentation for the C interface here: [Use SYCL Shared Library With Third-Party Applications](https://www.intel.com/content/www/us/en/docs/oneapi/programming-guide/2023-1/use-sycl-shared-library-with-third-party.html).


### C++ ABI compability 

We need to consider the **C++ ABI compatibility** when exposing the C++ interface in the library, while the host code is compiled with MSVC or GCC.
#### MSVC Compatibility
According to [Microsoft Compatibility](https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2025-0/microsoft-compatibility.html)
> The Intel® oneAPI DPC++/C++ Compiler is fully source- and binary-compatible (native code only) with Microsoft Visual C++ (MSVC). You can debug binaries built with the Intel® oneAPI DPC++/C++ Compiler from within the Microsoft Visual Studio environment.


About inline `dllimport`

> The Intel oneAPI DPC++/C++ Compiler will attempt to inline any functions that are marked dllimport but Microsoft will not. Therefore, any calls or variables used inside a dllimport routine need to be available at link time or the result will be an unresolved symbol.

About Enum Bit-Field Signedness

>The Intel® oneAPI DPC++/C++ Compiler and Microsoft Visual C++ differ in how they attribute signedness to bit fields declared with an enum type. Microsoft Visual C++ always considers enum bit fields to be signed, even if not all values of the enum type can be represented by the bit field.

#### GCC Compatibility
Refer to [GCC Compatibility and Interoperability](https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2025-0/gcc-compatibility-and-interoperability.html)

> The Intel® oneAPI DPC++/C++ Compiler is highly compatible with the GNU compilers.

The document explains certain limitations of [statement expressions](https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html) in ICX.








## ICX Compiler Driver on Windows
On Windows, you can use `icx-cl` or `icpx` as your compiler driver. For better compatibility with MSVC compiler options, it's recommended to use icx-cl on Windows.
https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2025-0/invoke-the-compiler.html

# Install SYCL runtime 
Besides installing the oneAPI package, you can also install the SYCL runtime separately.
https://www.intel.com/content/www/us/en/developer/articles/tool/compilers-redistributable-libraries-by-version.html


# Use SYCL Shared Library With Third-Party Applications
You can build shared libraries containing SYCL code for use in host applications (compiled with MSVC or GCC) by exposing both C and C++ interfaces. C API is often the safest bet to minimize compatibility headaches.

Here is the reference documentation for the C interface. https://www.intel.com/content/www/us/en/docs/oneapi/programming-guide/2023-1/use-sycl-shared-library-with-third-party.html

## C++ ABI compability 
These documents detail C++ ABI compability.
https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2025-0/microsoft-compatibility.html
https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2025-0/gcc-compatibility-and-interoperability.html











# ICX Compiler Driver on Windows
On Windows, you can use icx-cl or icpx as your compiler driver. For better compatibility with MSVC compiler options, it's recommended to use icx-cl on Windows.
https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2025-0/invoke-the-compiler.html
# How to build and run
This example introduces the most basic use case of SYCL.. Assuming that you have already called the setvars.bat script from the oneAPI installation directory.
```
mkdir build
cd build
cmake -S .. -G Ninja
cmake --build .
./hello-sycl.exe
```
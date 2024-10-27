The source comes from https://github.com/apinge/oneAPI-samples
# Build and Run on windows
```
<ONEAPI_INSTALL_DIR>\oneapi-vars.bat
cd vector-add
cmake -B build -S . -G Ninja 
cmake --build build --config Release
build\vector-add-buffers.exe
```
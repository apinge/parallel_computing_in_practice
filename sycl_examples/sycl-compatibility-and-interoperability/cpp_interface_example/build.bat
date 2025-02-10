@echo off
setlocal

call "C:\Program Files (x86)\Intel\oneAPI\setvars.bat"

echo icx-cl /fsycl /EHs /LD libtest.cpp
icx-cl /fsycl /EHs /LD libtest.cpp
echo cl main.cpp /link libtest.lib /OUT:main.exe
cl main.cpp /link libtest.lib /OUT:main.exe

echo Build complete.
endlocal
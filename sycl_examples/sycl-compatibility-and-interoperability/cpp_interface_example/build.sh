icpx -fsycl -shared -fPIC -o libtest.so libtest.cpp
g++ -c main.cpp
g++ main.o -o main -L. -ltest -Wl,-rpath=.
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <vector>
#include "libtest.h"


std::random_device rd;  // a seed source for the random number engine
std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> distrib(1, 6);

int N = 20;
int main() {
    std::vector<int> a(N), b(N), c(N),expect(N);
    for(int i=0;i<N;i++){
        a[i] = distrib(gen);
        b[i] = distrib(gen);
        expect[i] = a[i] + b[i];
    }
    vector_add(a.data(), b.data(), c.data(),  N);
    if(c == expect)
        std::cout << "Test passed!" << std::endl;   
    else
        std::cout << "Test failed!" << std::endl;
    
    return 0;
}
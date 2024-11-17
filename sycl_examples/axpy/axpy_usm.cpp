#include <cassert>
#include <iostream>
#include <sycl/sycl.hpp>

using namespace sycl;

template <typename T>
T* axpy(queue& Q, size_t sz, T alpha, const T* x, const T* y)
{
  // FIXME allocate the result array
  // should it be host, device or shared?
  auto z = sycl::malloc_shared<double>(sz,Q);

  Q.submit([&](handler& cgh) {
     sycl::stream out(1024, 256, cgh);
     cgh.parallel_for(range { sz }, [=](id<1> tid) {
       // define the AXPY kernel.
       // you need to extract an integer index from the id object. Hint: it can
       // be done with the subscript operator
         auto i  = tid[0];
         z[i] = x[i] * alpha + y[i];
         out << tid[0] << ' ';//From the printing order, the execution appears to be parallel.
     
     });
    // out << sycl::endl; error here
   }).wait();

  return z;
}

int main()
{
  constexpr auto sz = 1024;

  constexpr auto alpha = 1.0;

  queue Q;

  std::cout << "Running on: " << Q.get_device().get_info<info::device::name>()
            << std::endl;

  // allocate space for the x array
  // should it be host, device or shared?
  auto x = sycl::malloc_host<double>(sz, Q);
  // fill array with 0, 1, 2, ..., sz-1
 
  // allocate space for the y array
  // should it be host, device or shared?
  auto y = sycl::malloc_host<double>(sz, Q);
  // fill array with sz-1, sz-2, ..., 1, 0
  for (int i = 0; i < sz; ++i) {
      x[i] = i;
      y[i] = sz-1-i;
  }
  auto z = axpy(Q, sz, alpha, x, y);

  free(x, Q);
  free(y, Q);

  std::cout << "Checking results..." << std::endl;
  auto message = "Nice job!";
  for (auto i = 0; i < sz; ++i) {
    if (std::abs(z[i] - (sz - 1)) >= 1.0e-13) {
      std::cout << "Uh-oh!" << std::endl;
      std::cout << z[i] << std::endl;
      message = "Not quite there yet :(";
      break;
    }
  }
  std::cout << message << std::endl;

  free(z, Q);
}
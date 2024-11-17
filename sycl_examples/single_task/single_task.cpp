#include <iostream>
#include <sycl/sycl.hpp>

using namespace sycl;

int
main()
{
    //create a queue object
    sycl::queue Q = queue{ sycl::gpu_selector_v };

    std::cout << "we are running on: "
        << Q.get_device().get_info<info::device::vendor>() << " "
        << Q.get_device().get_info<info::device::name>() << std::endl;

    // submit work with a command group handler
    Q.submit([&](handler& cgh) {
        // create a stream object
        auto out = sycl::stream(1024, /* maximum size of output per kernel invocation */
                      256, /* maximum size before flushing the stream */
                      cgh);
        // FIXME create a single task in the command group handler
        cgh.single_task([=]() {
            /* task code */
            out << "Hello from within a task!" << sycl::endl;// Here isnot 
        });
        }).wait();// should we wait?
    

    return 0;
}
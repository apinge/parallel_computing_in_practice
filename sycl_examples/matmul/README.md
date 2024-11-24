In usm-range-matmul.cpp, the sycl::queue::submit function is not explicitly called, yet wait() is still used. Why is that?

Like example in `axpy_buf_acc.cpp`, no `wait()` here, this is because the scope of the buffers ensures that the SYCL runtime will implicitly wait for the operations to complete before the buffers are destroyed. 
```C++
Q.submit([&](handler &cgh) {
    // declare accessor into bx. read-only and in global memory
    sycl::accessor ax = sycl::accessor(bx, cgh, read_only);
    // declare accessor into by. read-only and in global memory
    sycl::accessor ay = sycl::accessor(by, cgh, read_only);
    // declare accessor into bz. write-only and in global memory, , and discarding previous contents
    sycl::accessor az = sycl::accessor(bz, cgh, write_only, no_init);
    cgh.parallel_for(work_items, [=](id<1> tid) {
      // perform AXPY operation. Hint: we can index accessor directly with an id object
        az[tid] = ax[tid] * alpha +ay[tid];
    });
```

On the other hand, in `usm-range-matmul.cpp`, the code is used to submit a kernel to the SYCL queue Q. The submit function is not explicitly used because parallel_for is a higher-level abstraction that internally handles the submission of the kernel to the queue.
```C++
Q.parallel_for(
     range{N,N},
     [=](id<2> idx) {
       // define matrix multiplication kernel
      auto i = idx[0];
      auto j = idx[1];
      for(int k =0;k<N;++k){
        C[i*N+j] += A[i*N+k]*B[k*N+j];
      }
      
     }).wait();
```
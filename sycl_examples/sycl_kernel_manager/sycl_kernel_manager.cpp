// REQUIRES: (level_zero || opencl) && linux && gpu

// RUN: %{build} -o %t.out
// RUN: rm -rf %t/cache_dir
// RUN: env NEOReadDebugKeys=1 CreateMultipleRootDevices=3 SYCL_CACHE_PERSISTENT=1 SYCL_CACHE_TRACE=1 SYCL_CACHE_DIR=%t/cache_dir env -u XDG_CACHE_HOME env -u HOME %{run} %t.out 2>&1 | FileCheck %s --check-prefixes=CHECK-BUILD
// RUN: env NEOReadDebugKeys=1 CreateMultipleRootDevices=3 SYCL_CACHE_PERSISTENT=1 SYCL_CACHE_TRACE=1 SYCL_CACHE_DIR=%t/cache_dir env -u XDG_CACHE_HOME env -u HOME %{run} %t.out 2>&1 | FileCheck %s --check-prefixes=CHECK-CACHE

// Test checks that persistent cache works correctly with multiple devices.
#include <iostream>
#include <unordered_map>
#include <string>
#include <sycl/detail/core.hpp>

using namespace sycl;

// class SimpleKernel;
class SimpleKernel;
// template<typename KernelName>
class KernelManager
{
public:
  KernelManager() : q(gpu_selector_v)
  {
    dev = q.get_device();
    ctx = q.get_context();

    std::cout << "== Using "
              << q.get_device().get_info<sycl::info::device::name>()
              << ", Backend: " << q.get_backend() << " ===\n";
  }
  // Note that this name is mangled name!
  // Can use kernel_id.get_name()
  sycl::kernel get_kernel(const char *name)
  {
    kernel_bundle Bundle = get_kernel_bundle<bundle_state::executable>(q.get_context());
    for (auto K : AllKernelIDs)
    {
      auto Kname = K.get_name();
      if (strcmp(name, Kname) == 0)
      {
        sycl::kernel Kernel = Bundle.get_kernel(K);
        std::cout << "Found kernel\n";
        return Kernel;
      }
    }
    std::cout << "No kernel found\n";
    exit(1);
  }
  // template <typename KernelName>
  // void build_single_kernel()
  // {
  //   sycl::kernel_bundle<sycl::bundle_state::input> bundle = sycl::get_kernel_bundle<bundle_state::input>(ctx);
  //   sycl::kernel_bundle<sycl::bundle_state::executable> bundle_exe = sycl::build(bundle, {dev});
  //   sycl::kernel kernel = bundle_exe.get_kernel(sycl::get_kernel_id<KernelName>());
  // }

  void print_all_kernel_ids()
  {
    AllKernelIDs = sycl::get_kernel_ids();
    std::cout << "Number of kernels = " << AllKernelIDs.size() << std::endl;
    for (auto K : AllKernelIDs)
      std::cout << "Kernel obtained: " << K.get_name() << std::endl;
  }
  void print_all_keys()
  {
    for (const auto &[id, _] : KernelMap)
      std::cout << "kernel id" << id.get_name() << std::endl;
  }


  void submit_one_kernel()
  {
    range<1> R1{1};
    q.submit([&](handler &CGH)
             { CGH.parallel_for<SimpleKernel>(R1, [=](id<1> WIid) {}); });
    q.wait();
  
    sycl::kernel_id kernel_id = sycl::get_kernel_id<SimpleKernel>();
    //std::cout << kernel_id.get_name() << std::endl;
    kernel_bundle Bundle = get_kernel_bundle<bundle_state::executable>(q.get_context());
    sycl::kernel kernel = Bundle.get_kernel(kernel_id);
    KernelMap.emplace(kernel_id,kernel);
  }

private:
  sycl::queue q;
  sycl::device dev;  // only gpu
  sycl::context ctx; // assume only one context
  std::unordered_map<sycl::kernel_id, sycl::kernel> KernelMap;
  std::vector<sycl::kernel_id> AllKernelIDs;
};

int main(void)
{
  KernelManager mgr;
  mgr.submit_one_kernel();


  mgr.print_all_keys();

  return 0;
}

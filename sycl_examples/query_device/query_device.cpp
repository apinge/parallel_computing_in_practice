#include <sycl/sycl.hpp>
#include <iostream>
using namespace sycl;

inline std::uint64_t get_device_global_mem_size(const sycl::device& d) {
    return d.get_info<sycl::info::device::global_mem_size>();
}

inline std::uint64_t get_device_local_mem_size(const sycl::device& d) {
    return d.get_info<sycl::info::device::local_mem_size>();
}

int main(){
  for(auto &p: platform::get_platforms()){
      std::cout << "SYCL Platform: "
          << p.get_info<info::platform::name>()
          << " is associated with SYCL Backend:"
          << p.get_backend() << ". "
          << "Platform::vendor is "
          << p.get_info<info::platform::vendor>() << std::endl;
  }
  sycl::device gpu_device = sycl::device(sycl::gpu_selector_v);
  std::cout << "gpu get_device_global_mem_size:" << get_device_global_mem_size(gpu_device) <<  " bytes."<< std::endl;
  std::cout << "gpu get_device_local_mem_size:" << get_device_local_mem_size(gpu_device) << " bytes." << std::endl;
   

  for (const auto& dev : sycl::device::get_devices()) {
      const auto Name = dev.get_info<sycl::info::device::name>();
      const auto Backend = dev.get_backend();
      const auto LocalMemType = dev.get_info<sycl::info::device::local_mem_type>();
      // none, dedicated local storage, or an abstraction built using global memory.
      std::cout << Name << " from " << Backend << " has local_mem_type " << static_cast<int>(LocalMemType) << std::endl;
  }
  return 0;
}
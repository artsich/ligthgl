#include "lightgl.h"

 #if defined(__EMSCRIPTEN__)
     #include <webgpu/webgpu.h>
     #include <emscripten/emscripten.h>
     #include <emscripten/html5.h>
 #else
#include <webgpu/webgpu_cpp.h>
#include <webgpu/webgpu_cpp_print.h>
#endif

 #include <iostream>
 #include <string>
 #include <functional>

int my_function(int x) {
#if defined(__EMSCRIPTEN__)
    std::cout << "Try to create wgpu instance!\n";

    WGPUInstance instance = wgpuCreateInstance(nullptr);

    if (instance) {
        std::cout << "WebGPU Instance is created!\n";
        wgpuInstanceRelease(instance);
    } else {
        std::cerr << "WebGPU Instance creating failed\n";
        return EXIT_FAILURE;
    }
#else
    wgpu::InstanceDescriptor instanceDescriptor{};
    instanceDescriptor.capabilities.timedWaitAnyEnable = true;
    wgpu::Instance instance = wgpu::CreateInstance(&instanceDescriptor);
    if (instance == nullptr) {
        std::cerr << "Instance creation failed!\n";
        return EXIT_FAILURE;
    }
    // Synchronously request the adapter.
    wgpu::RequestAdapterOptions options = {};
    wgpu::Adapter adapter;

    auto callback = [](wgpu::RequestAdapterStatus status, wgpu::Adapter adapter, const char* message, void* userdata) {
        if (status != wgpu::RequestAdapterStatus::Success) {
            std::cerr << "Failed to get an adapter:" << message;
            return;
        }
        *static_cast<wgpu::Adapter*>(userdata) = adapter;
        };

    auto callbackMode = wgpu::CallbackMode::WaitAnyOnly;
    void* userdata = &adapter;
    instance.WaitAny(instance.RequestAdapter(&options, callbackMode, callback, userdata), UINT64_MAX);
    if (adapter == nullptr) {
        std::cerr << "RequestAdapter failed!\n";
        return EXIT_FAILURE;
    }

    wgpu::DawnAdapterPropertiesPowerPreference power_props{};

    wgpu::AdapterInfo info{};
    info.nextInChain = &power_props;

    adapter.GetInfo(&info);
    std::cout << "VendorID: " << std::hex << info.vendorID << std::dec << "\n";
    std::cout << "Vendor: " << info.vendor << "\n";
    std::cout << "Architecture: " << info.architecture << "\n";
    std::cout << "DeviceID: " << std::hex << info.deviceID << std::dec << "\n";
    std::cout << "Name: " << info.device << "\n";
    std::cout << "Driver description: " << info.description << "\n";
#endif
    return EXIT_SUCCESS;
}

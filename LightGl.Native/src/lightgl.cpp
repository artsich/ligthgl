#include "lightgl.h"

#include <webgpu/webgpu_cpp.h>
#include <iostream>

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#else
//#include <webgpu/webgpu_glfw.h>
#endif

wgpu::Instance instance = nullptr;
wgpu::Device device = nullptr;

void PrintAdapterInfo(const wgpu::AdapterInfo& info) {
	std::cout << "Adapter properties:\n"
		<< " - vendorID: " << info.vendorID << "\n"
		<< " - vendorName: " << info.vendor.data << "\n"
		<< " - architecture: " << info.architecture.data << "\n"
		<< " - deviceID: " << info.deviceID << "\n"
		<< " - name: " << info.device.data << "\n"
		<< " - driverDescription: " << info.description.data << "\n"
		<< " - adapterType: 0x" << std::hex << static_cast<uint32_t>(info.adapterType) << std::dec << "\n"
		<< " - backendType: 0x" << std::hex << static_cast<uint32_t>(info.backendType) << std::dec << std::endl;
}

void PrintSupportedFeatures(const wgpu::SupportedFeatures& features) {
	std::cout << "List of supported features" << std::endl;
	std::cout << std::hex;
	for (int i = 0; i < features.featureCount; i++) {
		wgpu::FeatureName name = features.features[i];
		std::cout << " - 0x" << (uint32_t)name << std::endl;
	}
	std::cout << std::dec;
}

int light_gl_init() {
	wgpu::InstanceDescriptor desc{};
	desc.capabilities.timedWaitAnyEnable = true;
	instance = wgpu::CreateInstance(&desc);

	std::cout << "WebGPU Instance is created!\n";

	wgpu::Adapter adapter;
	wgpu::RequestAdapterOptions adapterOpts{};
	adapterOpts.powerPreference = wgpu::PowerPreference::HighPerformance;

	instance.RequestAdapter(
		&adapterOpts,
		wgpu::CallbackMode::AllowProcessEvents,
		[&adapter](wgpu::RequestAdapterStatus status, wgpu::Adapter ad, wgpu::StringView message) {
			if (status != wgpu::RequestAdapterStatus::Success) {
				std::cerr << "Adapter request failed: " << message.data << "\n";
				std::exit(1);
			}
			adapter = ad;
		}
	);

	instance.ProcessEvents();

	std::cout << "Adapter is created!\n";

	wgpu::AdapterInfo info;
	adapter.GetInfo(&info);
	PrintAdapterInfo(info);

	wgpu::SupportedFeatures supportedFeatures;
	adapter.GetFeatures(&supportedFeatures);
	PrintSupportedFeatures(supportedFeatures);

	wgpu::DeviceDescriptor deviceDesc{};
	deviceDesc.label = "LightGlGraphicsDevice";
	deviceDesc.requiredFeatureCount = 0;
	deviceDesc.requiredLimits = nullptr;
	deviceDesc.defaultQueue.nextInChain = nullptr;
	deviceDesc.defaultQueue.label = "LightGlGraphicsQueue";

	deviceDesc.SetDeviceLostCallback(
		wgpu::CallbackMode::AllowProcessEvents,
		[](const wgpu::Device& device, wgpu::DeviceLostReason reason, wgpu::StringView message) {
			std::cerr << "Device lost: reason=" << static_cast<uint32_t>(reason);
			std::cerr << " (" << message.data << ")";
			std::cerr << std::endl;
		}
	);

	deviceDesc.SetUncapturedErrorCallback(
		[](const wgpu::Device&, wgpu::ErrorType error, wgpu::StringView message) {
			__debugbreak();
			std::cerr << "Uncaptured error: type=" << static_cast<uint32_t>(error);
			std::cerr << " (" << message.data << ")";
			std::cerr << std::endl;
		}
	);

	device = adapter.CreateDevice(&deviceDesc);
	std::cout << "Device is created!\n";

	return EXIT_SUCCESS;
}

int light_gl_destroy() {
	return EXIT_SUCCESS;
}

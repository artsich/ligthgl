#pragma once

#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#define LIGHT_GPU_API __declspec(dllexport)
#else
#define LIGHT_GPU_API
#endif

extern "C" {
    LIGHT_GPU_API int print_adapter_info();
} 
#pragma once

#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#define LIGHT_GL_API __declspec(dllexport)
#else
#define LIGHT_GL_API 
#endif

extern "C" {
    LIGHT_GL_API int my_function(int v);
} 

#include "lightgl.h"
#include <iostream>

int main() {
	std::cout << "Initializing LightGL..." << std::endl;
    
	int result = light_gl_init();
	if (result != EXIT_SUCCESS) {
		std::cerr << "Failed to initialize LightGL!" << std::endl;
		return result;
	}
	std::cout << "LightGL initialized successfully!" << std::endl;
	std::cout << "Running sandbox application..." << std::endl;

	std::cout << "Shutting down LightGL..." << std::endl;

	result = light_gl_destroy();
	if (result != EXIT_SUCCESS) {
		std::cerr << "Failed to properly shutdown LightGL!" << std::endl;
		return result;
	}
    
	std::cout << "LightGL shutdown successfully!" << std::endl;
	return EXIT_SUCCESS;
} 
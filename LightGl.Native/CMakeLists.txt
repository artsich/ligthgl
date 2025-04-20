cmake_minimum_required(VERSION 3.14)
project(lightgl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lightgl SHARED 
    "src/lightgl.h"
    "src/lightgl.cpp"
)

if(EMSCRIPTEN)
	set_target_properties(app PROPERTIES SUFFIX ".html")
	target_link_options(app PRIVATE "-sUSE_WEBGPU=1" "-sUSE_GLFW=3")
else()
    find_package(Dawn REQUIRED)
    target_link_libraries(lightgl PRIVATE dawn::webgpu_dawn)
    
    add_custom_command(TARGET lightgl POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:dawn::webgpu_dawn>
            $<TARGET_FILE_DIR:lightgl>
    )
endif()
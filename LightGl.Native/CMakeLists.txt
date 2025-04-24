cmake_minimum_required(VERSION 3.14)
project(lightgl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(EMSCRIPTEN)
    add_library(lightgl STATIC
        src/lightgl.cpp
        src/lightgl.h
    )
    target_include_directories(lightgl PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

    target_link_options(lightgl PRIVATE
        "-sUSE_WEBGPU=1"
        "-sUSE_GLFW=3"
    )

    set_target_properties(lightgl PROPERTIES
        PREFIX ""
        SUFFIX ".a"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )
else()
    add_library(lightgl SHARED
        "src/lightgl.h"
        "src/lightgl.cpp"
    )

    find_package(Dawn REQUIRED)
    target_link_libraries(lightgl PRIVATE dawn::webgpu_dawn)
    
    add_custom_command(TARGET lightgl POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:dawn::webgpu_dawn>
            $<TARGET_FILE_DIR:lightgl>
    )
    
    add_executable(sandbox
        src/sandbox.cpp
    )
    set_target_properties(sandbox PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:lightgl>
    )
    target_include_directories(sandbox PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    target_link_libraries(sandbox PRIVATE lightgl)
endif()
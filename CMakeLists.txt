cmake_minimum_required(VERSION 3.10)
project(DitherBoy VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(DitherBoy
    main.cpp
    Image.cpp
    Color.cpp
    pallete.cpp
    ordered_dithrer.cpp
)

# Include directories
target_include_directories(DitherBoy PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# Compiler flags
if(MSVC)
    target_compile_options(DitherBoy PRIVATE /W4)
else()
    target_compile_options(DitherBoy PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Set output directory
set_target_properties(DitherBoy PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
) 
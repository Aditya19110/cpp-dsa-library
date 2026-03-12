cmake_minimum_required(VERSION 3.10)
project(DSA_Library VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Main executable
add_executable(DSA_Library
    src/main.cpp
)

# Examples executable
add_executable(DSA_Examples
    examples/usage_examples.cpp
)

# Tests executable (optional - can be expanded with testing framework)
add_executable(DSA_Tests
    tests/test_data_structures.cpp
)

# Enable testing
enable_testing()
add_test(NAME DSA_Tests COMMAND DSA_Tests)

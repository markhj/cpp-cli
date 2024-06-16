cmake_minimum_required(VERSION 3.28)
project(cpp_cli)

set(CMAKE_CXX_STANDARD 20)

file(MAKE_DIRECTORY build)

# Set the build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Convert build type to lowercase
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE_LOWER)

# Set output directories for different build configurations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${BUILD_TYPE_LOWER}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${BUILD_TYPE_LOWER}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${BUILD_TYPE_LOWER}/bin)

include_directories(lib/src include/cpp-cli/contracts include)

# Build library
add_subdirectory(lib)

# Build samples (if requested)
if ($ENV{BUILD_SAMPLES})
    add_subdirectory(samples)
endif ()

# Build tests (if requested)
if ($ENV{BUILD_TESTS})
    add_subdirectory(tests)
endif ()

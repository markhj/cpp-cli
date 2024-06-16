cmake_minimum_required(VERSION 3.28)
project(cpp_cli)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

# cpp-cli library
add_library(cpp_cli STATIC
        ${CMAKE_SOURCE_DIR}/include/cpp-cli/contracts/helper.hpp
        src/services/cli.cpp
        src/utilities/interpretation.cpp
        src/services/interpreter.cpp
        src/utilities/subcommand.cpp
        src/services/io.cpp
        ${CMAKE_SOURCE_DIR}/include/cpp-cli/contracts/console-io.hpp
        ${CMAKE_SOURCE_DIR}/include/cpp-cli/cpp-cli.hpp
        ${CMAKE_SOURCE_DIR}/include/cpp-cli/misc/enums.hpp
        src/utilities/std-helper.cpp
        src/utilities/value.cpp)

target_include_directories(cpp_cli PUBLIC include)
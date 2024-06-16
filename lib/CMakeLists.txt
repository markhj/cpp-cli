cmake_minimum_required(VERSION 3.28)
project(cpp_cli)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

# cpp-cli library
add_library(cpp_cli STATIC
        ../include/cpp-cli/contracts/helper.hpp
        src/services/cli.cpp
        src/utilities/interpretation.cpp
        src/services/interpreter.cpp
        src/utilities/subcommand.cpp
        src/services/io.cpp
        ../include/cpp-cli/contracts/console-io.hpp
        ../include/cpp-cli/cpp-cli.hpp
        ../include/cpp-cli/misc/enums.hpp
        src/utilities/std-helper.cpp
        src/utilities/value.cpp)

target_include_directories(cpp_cli PUBLIC include)
cmake_minimum_required(VERSION 3.28)
project(cpp_cli_tests)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/vendor/cpp-bbunit/lib
        src)

add_executable(tests main.cpp
        src/base-test.cpp
        src/test-tools.cpp
        src/test-emitter.cpp)

target_link_libraries(tests PRIVATE cpp_cli)
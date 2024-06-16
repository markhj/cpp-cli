cmake_minimum_required(VERSION 3.28)
project(cpp_cli_samples)

set(CMAKE_CXX_STANDARD 20)

set(SAMPLE_APPS
    hello-world
    sample
    subcommand-tree)

foreach (SAMPLE_APP ${SAMPLE_APPS})
    add_executable(${SAMPLE_APP} src/${SAMPLE_APP}.cpp)
    target_link_libraries(${SAMPLE_APP} PRIVATE cpp_cli)
    target_include_directories(${SAMPLE_APP} PRIVATE include)
endforeach ()

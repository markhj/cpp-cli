include(CMakePackageConfigHelpers)

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

add_library(cpp-cli STATIC IMPORTED)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/cpp_cli-Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/cpp_cli-ConfigVersion.cmake"
        DESTINATION lib/cmake/cpp-cli
)

set_target_properties(cpp-cli PROPERTIES
        IMPORTED_LOCATION_DEBUG "${PACKAGE_PREFIX_DIR}/build/debug/lib/libcpp_cli.a"
        IMPORTED_LOCATION_RELEASE "${PACKAGE_PREFIX_DIR}/build/release/lib/libcpp_cli.a"
        INTERFACE_INCLUDE_DIRECTORIES "${PACKAGE_PREFIX_DIR}/include"
)

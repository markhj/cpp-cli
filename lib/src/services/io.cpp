#include "cpp-cli/services/io.hpp"
#include <format>
#include <iostream>

void CppCLI::IO::emit(const std::string& msg) noexcept {
    std::cout << msg << std::endl;
    std::cout.flush();
}

void CppCLI::IO::error(const std::string &msg) noexcept {
    emit(std::format("ERROR: {}", msg));
}

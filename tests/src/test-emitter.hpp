#pragma once

#include <iostream>
#include "cpp-cli/cpp-cli.hpp"

using CppCLI::ConsoleIO;

class TestEmitter : public ConsoleIO {
public:
    void emit(const std::string &msg) noexcept override;

    void error(const std::string &msg) noexcept override;

    [[nodiscard]] std::vector<std::string> getMessage() const;

private:
    std::vector<std::string> m_messages;
};

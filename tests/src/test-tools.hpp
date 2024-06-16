#pragma once

#include "cpp-cli/cpp-cli.hpp"

class TestTools {
protected:
//    static const char **vecToArgv(const std::vector<std::string> &args);

    static std::vector<std::string> parseArgs(const std::string &cmd);

    void simulateCmd(const std::string &cmd,
                     const std::function<void(int argc, char *argv[])> &assertions);
};

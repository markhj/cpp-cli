#include <vector>
#include <string>
#include "test-tools.hpp"

#include <cstring>

std::vector<std::string> TestTools::parseArgs(const std::string &cmd) {
    std::vector<std::string> vec = {"app-name"};
    std::string buffer;
    bool withinStringLiteral = false;
    for (char c : cmd) {
        if (c == '"') {
            withinStringLiteral = !withinStringLiteral;
        } else if (c == ' ' && !withinStringLiteral) {
            if (!buffer.empty()) {
                vec.push_back(buffer);
            }
            buffer = "";
        } else {
            buffer += c;
        }
    }
    if (!buffer.empty()) {
        vec.push_back(buffer);
    }
    return vec;
}

void TestTools::simulateCmd(const std::string &cmd, const std::function<void(int argc, char *argv[])> &run) {
    std::vector<std::string> vec = parseArgs(cmd);

    char** args = new char*[vec.size() + 1];

    for (std::size_t i = 0; i < vec.size(); ++i) {
        args[i] = const_cast<char*>(vec[i].c_str());
    }

    args[vec.size()] = nullptr;

    int argc = static_cast<int>(vec.size());

    std::vector<char *> argv(argc);
    for (int i = 0; i < argc; ++i) {
        argv[i] = new char[strlen(args[i]) + 1];
        strcpy(argv[i], args[i]);
    }

    run(argc, argv.data());

    delete[] args;
}

#include "cpp-cli/services/interpreter.hpp"
#include <format>
#include <iostream>
#include <stdexcept>

enum OptionReaderContext {
    PrefixedDashes,
    Key,
    Value,
};

enum OptionPrefixType {
    None,
    SingleDash,
    DoubleDash,
};

CppCLI::Interpretation CppCLI::Interpreter::interpret(int argc, char **argv) {
    Interpretation interpretation;

    bool initialArgList = true;

    // We ignore argument 0 (which is just the program name)
    for (int i = 1; i <= argc - 1; i++) {
        if (initialArgList && *argv[i] == '-') {
            initialArgList = false;
        }

        if (initialArgList) {
            interpretation.appendInitialArgument({.value = std::string(argv[i])});
            if (!interpretation.getSubcommand().has_value()) {
                interpretation.setSubcommand(std::string(argv[i]));
            }
        } else if (*argv[i] == '-') {
            interpretation.appendOption(parseOption(argv[i]));
        } else {
            interpretation.appendArgument({argv[i]});
        }
    }

    return interpretation;
}

Option CppCLI::Interpreter::parseOption(const std::string &arg) {
    std::string key, value;
    bool equalsFound = false;
    OptionPrefixType prefixType = OptionPrefixType::None;
    OptionReaderContext context = OptionReaderContext::PrefixedDashes;

    for (int i = 0; i < arg.length(); i++) {
        char c = arg[i];

        switch (context) {
            case OptionReaderContext::PrefixedDashes:
                if (c == '-') {
                    switch (prefixType) {
                        case None:
                            prefixType = SingleDash;
                            break;
                        case SingleDash:
                            prefixType = DoubleDash;
                            break;
                        case DoubleDash:
                            throw std::runtime_error(std::format("Option must have only one or two dashes: {}",
                                                                 arg));
                    }
                } else {
                    context = OptionReaderContext::Key;
                    key += c;
                }
                break;
            case OptionReaderContext::Key:
                if (prefixType == SingleDash && key.length() == 1) {
                    context = OptionReaderContext::Value;
                    value += c;
                } else if (c == '=') {
                    equalsFound = true;
                    context = OptionReaderContext::Value;
                } else {
                    key += c;
                }
                break;
            case OptionReaderContext::Value:
                value += c;
                break;
        }
    }

    // When no EQUALS operator is present, we treat the option as a (bool) flag
    if (!equalsFound && value.empty()) {
        return {key, "", Value(true)};
    }

    return {key, "", Value(value)};
}

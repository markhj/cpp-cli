#include "cpp-cli/services/cli.hpp"
#include "cpp-cli/services/interpreter.hpp"
#include "cpp-cli/utilities/std-helper.hpp"
#include <cassert>
#include <format>
#include <iostream>
#include <utility>

bool isPaired(const DefineOption &defOption, const Option &option) {
    std::string raw = option.rawInput;

    if (defOption.long_name.has_value() && defOption.long_name.value() == raw) {
        return true;
    }

    if (defOption.short_name.has_value() && raw.length() == 1 && defOption.short_name.value() == raw[0]) {
        return true;
    }

    return false;
}

void CppCLI::CLI::define(const Subcommand &subcommand) noexcept {
    m_subcommands.push_back(subcommand);
}

Response CppCLI::CLI::run(int argc, char **argv) {
    // Welcome the end-user
    m_io->emit(std::format("{} {}\n", m_appName, m_appVersion));

    // Look for the required "universal command" (a Subcommand instance
    // without any name)
    std::optional<Subcommand> universalCmd = findSubcommand("");

    // If found is false (i.e. no "empty subcommand" is found), the developer
    // must be notified that no universal command is defined
    assert(universalCmd.has_value() && "You must define a universal command (without any value for subcommand)");

    // Interpret the input and attempt to find a fitting subcommand
    Interpretation interpretation = Interpreter::interpret(argc, argv);
    std::optional<Subcommand> result = traceSubcommand(interpretation);

    if (!result.has_value()) {
        m_helper->print(m_io, universalCmd.value(), m_subcommands);
        return err("Unknown command.");
    }

    Subcommand subcommand = result.value();

    // Fill in default values and check required
    for (const DefineOption &defOption: subcommand.getOptions()) {
        if (!defOption.defaultValue.has_value()) {
            continue;
        }
        bool noValueFound = false;
        for (const Option &option: interpretation.getOptions()) {
            if (isPaired(defOption, option)) {
                noValueFound = true;
            }
        }
        if (!noValueFound) {
            interpretation.appendOption({.rawInput = defOption.id,
                                         .mappedId = defOption.id,
                                         .value = defOption.defaultValue.value()});
        }
    }

    // Map options
    // In essence, we want to fill out the "mappedId" which
    // the library uses internally to connect a user input
    // with a ``DefineOption``.
    interpretation.mapOptions([&](Option &option) {
        for (const DefineOption &defOption: subcommand.getOptions()) {
            if (isPaired(defOption, option)) {
                option.mappedId = defOption.id;
            }
        }
    });

    try {
        validate(subcommand, interpretation);
    } catch (std::runtime_error &e) {
        m_errorHandler(m_io, e);
        m_helper->print(m_io, subcommand, m_subcommands);
        return err(e.what());
    }

    Response response = subcommand.exec(interpretation);

    if (response.showHelp) {
        m_helper->print(m_io, subcommand, m_subcommands);
    }

    return response;
}

void CppCLI::CLI::validate(const Subcommand &subcommand,
                           const CppCLI::Interpretation &interpretation) noexcept(false) {
    std::vector<DefineOption> definedOptions = subcommand.getOptions();
    std::vector<Option> inputs = interpretation.getOptions();

    // Check that all required values are provided
    std::for_each(definedOptions.begin(), definedOptions.end(), [&](const DefineOption &defOption) {
        if (!defOption.required) {
            return;
        }
        bool requiredValFound = std::any_of(inputs.begin(), inputs.end(), [&](const Option &item) {
            return isPaired(defOption, item);
        });
        if (!requiredValFound) {
            throw std::runtime_error(std::format("Required option not provided: {}", defOption.id));
        }
    });

    std::for_each(inputs.begin(), inputs.end(), [&](const Option &option) {
        auto foundOpt = std::find_if(definedOptions.begin(),
                                     definedOptions.end(),
                                     [&](const auto &defOption) {
                                         return isPaired(defOption, option);
                                     });

        if (foundOpt == definedOptions.end()) {
            throw std::runtime_error(std::format("Unknown option: {}", option.rawInput));
        }

        // If the data types aren't identical, we'll switch through
        // the supported options to output an error message specific
        // to the mismatched expectation
        if (foundOpt->dataType != option.value.getDataType()) {
            switch (foundOpt->dataType) {
                case Boolean:
                    throw std::runtime_error(std::format("{} must be boolean.", option.rawInput));
                case String:
                    throw std::runtime_error(std::format("{} must be string.", option.rawInput));
            }
        }
    });
}

void CppCLI::CLI::setErrorHandler(const std::function<Response(std::shared_ptr<ConsoleIO>,
                                                               std::runtime_error &)> &errorHandler) {
    m_errorHandler = errorHandler;
}

CppCLI::CLI::CLI(std::string appName,
                 std::string appVersion,
                 std::shared_ptr<ConsoleIO> io) : m_appName(std::move(appName)),
                                                  m_appVersion(std::move(appVersion)),
                                                  m_io(std::move(io)),
                                                  m_helper(std::make_shared<StdHelper>(StdHelper())) {
}

std::optional<Subcommand> CppCLI::CLI::findSubcommand(const std::optional<std::string> &cmd) const noexcept {
    for (const Subcommand &item: m_subcommands) {
        if (!cmd.has_value() && item.getSubcommand().empty() || item.getSubcommand() == cmd) {
            return item;
        }
    }
    return std::nullopt;
}

Response CppCLI::CLI::err(const std::string &msg) const {
    Response errResponse = Response();
    errResponse.state = ResponseState::Error;
    errResponse.error = msg;
    return errResponse;
}

void CppCLI::CLI::setHelper(std::shared_ptr<Helper> helper) {
    m_helper = helper;
}
std::optional<Subcommand> CppCLI::CLI::traceSubcommand(const CppCLI::Interpretation &interpretation) const {
    std::optional<Subcommand> first = findSubcommand(interpretation.getSubcommand());

    if (!first.has_value()) {
        return std::nullopt;
    }

    Subcommand result = first.value();
    std::vector<Argument> initialArgList = interpretation.getInitialArgumentList();

    // Remove the first subcommand entry (as that's already located with the
    // first run of the "findCommand"
    if (!initialArgList.empty()) {
        initialArgList.erase(initialArgList.begin());
    }
    bool subSatisfied = true;

    std::for_each(initialArgList.begin(), initialArgList.end(), [&](const Argument &arg) {
        // @todo When argument support is added, this is the point where
        //      we "branch out" and check within the subcommand, if it has
        //      matching subcommands or arguments

        bool innerFound = false;
        std::vector<Subcommand> subcommandsToCurrent = result.getSubcommands();
        std::for_each(subcommandsToCurrent.begin(),
                      subcommandsToCurrent.end(),
                      [&](Subcommand &scmd) {
                          if (!arg.value.empty() && arg.value == scmd.getSubcommand()) {
                              result = std::move(scmd);
                              innerFound = true;
                          }
                      });

        if (!innerFound) {
            subSatisfied = false;
        }
    });

    if (!subSatisfied) {
        return std::nullopt;
    }

    return result;
}

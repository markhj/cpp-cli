#include "cpp-cli/utilities/interpretation.hpp"

std::optional<Argument> CppCLI::Interpretation::getArgument(int index) const noexcept {
    if (m_arguments.size() < index - 1) {
        return std::nullopt;
    }
    return m_arguments[index];
}

bool CppCLI::Interpretation::hasFlag(const char *flag) const noexcept {
    std::optional<Option> opt = getOption(flag);
    if (!opt.has_value()) {
        return false;
    }
    return opt.value().value.getAsBool();
}

std::vector<Argument> CppCLI::Interpretation::getArguments() const noexcept {
    return m_arguments;
}

void CppCLI::Interpretation::appendOption(const CppCLI::Option &option) noexcept {
    m_options.push_back(option);
}

void CppCLI::Interpretation::setSubcommand(const std::string &command) noexcept {
    m_subcommand = command;
}

std::optional<std::string> CppCLI::Interpretation::getSubcommand() const noexcept {
    return m_subcommand;
}

std::vector<Option> CppCLI::Interpretation::getOptions() const noexcept {
    return m_options;
}

void CppCLI::Interpretation::appendArgument(const Argument &arg) noexcept {
    m_arguments.push_back(arg);
}

std::optional<Option> CppCLI::Interpretation::getOption(const char *optionId) const noexcept {
    for (const Option& option : m_options) {
        if (option.mappedId == optionId) {
            return option;
        }
    }
    return std::nullopt;
}

void CppCLI::Interpretation::mapOptions(const std::function<void(Option &)>& func) {
    for (Option &option : m_options) {
        func(option);
    }
}
void CppCLI::Interpretation::appendInitialArgument(const Argument &arg) noexcept {
    m_initialArgs.push_back(arg);
}
std::vector<Argument> CppCLI::Interpretation::getInitialArgumentList() const noexcept {
    return m_initialArgs;
}

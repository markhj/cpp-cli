#include "cpp-cli/utilities/subcommand.hpp"
#include <cassert>

CppCLI::Subcommand &CppCLI::Subcommand::addOption(CppCLI::DefineOption option) noexcept {
    m_options.push_back(option);
    return *this;
}

CppCLI::Subcommand &CppCLI::Subcommand::handle(
        const std::function<Response(ConsoleIO &printer,
                                     const Interpretation &interpretation)> &handler) {
    m_handler = handler;
    return *this;
}

std::string CppCLI::Subcommand::getSubcommand() const noexcept {
    return m_subcommand;
}

std::string CppCLI::Subcommand::getDescription() const noexcept {
    return m_description;
}

Response CppCLI::Subcommand::exec(const CppCLI::Interpretation &interpretation) {
    assert(!!m_handler && "You have not provided an implementation.");
    return m_handler(getIO(), interpretation);
}

std::vector<DefineOption> CppCLI::Subcommand::getOptions() const noexcept {
    return m_options;
}

CppCLI::IO &CppCLI::Subcommand::getIO() {
    return m_io;
}

void CppCLI::Subcommand::addSubcommand(CppCLI::Subcommand subcommand) noexcept {
    m_subcommands.push_back(subcommand);
}

std::vector<CppCLI::Subcommand> CppCLI::Subcommand::getSubcommands() const noexcept {
    return m_subcommands;
}

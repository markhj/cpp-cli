#include "cpp-cli/utilities/std-helper.hpp"
#include <format>

const unsigned int MIN_CELL_LENGTH = 16;

size_t fixedColLength;

std::string optionFirstCol(const DefineOption& defineOption) {
    std::string out;
    if (defineOption.short_name.has_value()) {
        out += std::format("-{}", defineOption.short_name.value());
    }
    if (defineOption.long_name.has_value()) {
        if (defineOption.short_name.has_value()) {
            out += ", ";
        }
        out += std::format("--{}", defineOption.long_name.value());
    }
    return out;
}

void CppCLI::StdHelper::print(std::shared_ptr<CppCLI::ConsoleIO> io,
                              const CppCLI::Subcommand &subcommand,
                              const std::vector<Subcommand> &allSubcommands) noexcept {
    size_t longest = 0;
    std::for_each(allSubcommands.begin(), allSubcommands.end(), [&longest](const Subcommand &item) {
        longest = std::max(longest, item.getSubcommand().length());
    });

    bool showAll = subcommand.getSubcommands().empty();

    std::vector<DefineOption> options = subcommand.getOptions();
    std::for_each(options.begin(), options.end(), [&](const auto &item) {
        longest = std::max(longest, optionFirstCol(item).length());
    });

    fixedColLength = longest + 6;
    if (fixedColLength < MIN_CELL_LENGTH) {
        fixedColLength = MIN_CELL_LENGTH;
    }

    if (!options.empty()) {
        io->emit("\nOPTIONS:\n");
        std::for_each(options.begin(), options.end(), [&](const auto &item) {
            printCell(optionFirstCol(item), item.description, io);
        });
    }

    if (!subcommand.getSubcommands().empty()) {
        io->emit("\nCOMMANDS:");
        for (const Subcommand &cmd: subcommand.getSubcommands()) {
            printCell(cmd.getSubcommand(), cmd.getDescription(), io);
        }
    } else if (showAll && !allSubcommands.empty()) {
        io->emit("\nCOMMANDS:");
        for (const Subcommand &cmd: allSubcommands) {
            printCell(cmd.getSubcommand(), cmd.getDescription(), io);
        }
    }
}

void CppCLI::StdHelper::printCell(const std::string& first,
                                  const std::string& second,
                                  std::shared_ptr<ConsoleIO> io) const noexcept {
    std::string firstCell = first;
    while (firstCell.length() < fixedColLength) {
        firstCell += " ";
    }
    io->emit(std::format("{}{}", firstCell, second));
}

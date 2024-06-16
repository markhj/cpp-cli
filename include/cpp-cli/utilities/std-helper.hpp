#pragma once

#include <memory>
#include "subcommand.hpp"
#include "cpp-cli/contracts/console-io.hpp"
#include "cpp-cli/contracts/helper.hpp"

namespace CppCLI {
    /**
     * The standard "out of the box" implementation of the Helper.
     * Used, unless instructed otherwise.
     */
    class StdHelper : public Helper {
    public:
        StdHelper() = default;

        /**
         * Print a helpful text to the console, explaining the options
         * and subcommands of the provided Subcommand.
         *
         * @param io
         * @param subcommand
         * @param allSubcommands
         */
        void print(std::shared_ptr<CppCLI::ConsoleIO> io,
                   const Subcommand &subcommand,
                   const std::vector<Subcommand> &allSubcommands) noexcept override;

    private:
        void printCell(const std::string &first,
                       const std::string &second,
                       std::shared_ptr<ConsoleIO> io) const noexcept;
    };
}

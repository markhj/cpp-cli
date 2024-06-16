#pragma once

#include "cpp-cli/contracts/console-io.hpp"
#include "cpp-cli/utilities/subcommand.hpp"
#include <memory>

namespace CppCLI {
    /**
     * Helper Contract
     *
     * Interface for objects intended to provide helpful messages
     * when given a Subcommand.
     *
     * @ref helpers
     */
    class Helper {
    public:
        /**
         * Outputs the (hopefully) helpful text to the console, such that
         * the end-user gets a list of commands, options and arguments,
         * and understands how to use them.
         *
         * @param io
         * @param subcommand
         * @param allSubcommands
         */
        virtual void print(std::shared_ptr<CppCLI::ConsoleIO> io,
                           const Subcommand &subcommand,
                           const std::vector<Subcommand> &allSubcommands) noexcept = 0;
    };
}

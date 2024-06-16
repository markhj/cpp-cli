#pragma once

#include <string>
#include "cpp-cli/contracts/console-io.hpp"

namespace CppCLI {
    /**
     * The standard "out of the box" implementation of ConsoleIO.
     * The one used unless otherwise instructed.
     */
    class IO : public ConsoleIO {
    public:
        /**
         * Print a standard message to the console.
         *
         * @param msg
         */
        void emit(const std::string &msg) noexcept override;

        /**
         * Print an error to the console.
         *
         * @param msg
         */
        void error(const std::string &msg) noexcept override;
    };
}
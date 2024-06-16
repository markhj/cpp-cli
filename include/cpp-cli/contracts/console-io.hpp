#pragma once

#include <string>

namespace CppCLI {
    /**
     * Console I/O Contract
     *
     * This interface is used for objects injected into subcommand handles
     * and error handles, such that they can write output to (and in the future:
     * receive input from) the console, via a streamlined interface.
     *
     * @note The methods of ``ConsoleIO`` should _not_ be marked ``const``.
     * While in many use-cases they don't modify the object, it should be possible.
     * For instance for unit testing purposes.
     */
    class ConsoleIO {
    public:
        /**
         * Writes a standard message to the console.
         *
         * @param msg
         */
        virtual void emit(const std::string& msg) noexcept = 0;

        /**
         * Writes an error message to the console.
         *
         * @param msg
         */
        virtual void error(const std::string& msg) noexcept = 0;
    };
}

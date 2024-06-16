#pragma once

#include "cpp-cli/utilities/interpretation.hpp"

namespace CppCLI {
    /**
     * Takes the argc and argv arguments, and provides a structured interpretation
     * of its meaning. This has been separated to its own class, to make testing
     * this part easier
     */
    class Interpreter {
    public:
        /**
         * Generate an Interpretation, based on the ``argc`` and ``argv`` typically
         * provided by C++'s ``main`` function.
         *
         * @param argc
         * @param argv
         * @return
         */
        static Interpretation interpret(int argc, char **argv);

    private:
        static Option parseOption(const std::string &arg);
    };
}

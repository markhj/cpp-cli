#pragma once

#include "cpp-cli/misc/structs.hpp"
#include "value.hpp"
#include <functional>
#include <optional>
#include <string>
#include <vector>

using CppCLI::Argument;
using CppCLI::Option;

namespace CppCLI {
    /**
     * A utility class containing the results performed by the Interpreter.
     * The Interpretation contains information about subcommand(s), arguments
     * and options.
     */
    class Interpretation {
    public:
        /**
         * Returns true, if there is a boolean flag with the
         * DefineOption ``id`` column.
         *
         * @param flag
         * @return
         */
        bool hasFlag(const char *flag) const noexcept;

        /**
         * Retrieve list of arguments.
         *
         * @note Not yet implemented - arguments are not yet supported
         * @return
         */
        [[nodiscard]] std::vector<Argument> getArguments() const noexcept;

        /**
         * Retrieve a specific argument.
         *
         * @note Not yet implemented - arguments are not yet supported
         * @param index
         * @return
         */
        [[nodiscard]] std::optional<Argument> getArgument(int index) const noexcept;

        /**
         * Retrieve list of options.
         *
         * @return
         */
        [[nodiscard]] std::vector<Option> getOptions() const noexcept;

        /**
         * Retrieve a specific option based on its DefineOption ``id``.
         *
         * @param optionId
         * @return
         */
        [[nodiscard]] std::optional<Option> getOption(const char *optionId) const noexcept;

        /**
         * Iterate over the options.
         * Options are passed as reference (but not ``const``), and are therefore
         * subject to manipulation.
         *
         * @param func
         */
        void mapOptions(const std::function<void(Option&)>& func);

        /**
         * Add another option.
         *
         * @param option
         */
        void appendOption(const Option &option) noexcept;

        /**
         * Another another argument.
         *
         * @param arg
         */
        void appendArgument(const Argument &arg) noexcept;

        /**
         * Add an "initial argument", which is an argument provided
         * before any options.
         *
         * At this point, it means it could be interpreted as either
         * subcommand or argument to a subcommand.
         *
         * @param arg
         */
        void appendInitialArgument(const Argument &arg) noexcept;

        /**
         * Retrieve the list of initial arguments
         *
         * @return
         */
        [[nodiscard]] std::vector<Argument> getInitialArgumentList() const noexcept;

        /**
         * Set the subcommand name.
         *
         * @param command
         */
        void setSubcommand(const std::string &command) noexcept;

        /**
         * Retrieve the subcommand name.
         * Will be an empty ``std::optional`` if not set, and treated
         * as a universal command.
         *
         * @return
         */
        [[nodiscard]] std::optional<std::string> getSubcommand() const noexcept;

    private:
        std::optional<std::string> m_subcommand;
        std::vector<Option> m_options;
        std::vector<Argument> m_arguments;
        std::vector<Argument> m_initialArgs;
    };
}

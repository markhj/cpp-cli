#pragma once

#include "cpp-cli/services/io.hpp"
#include "interpretation.hpp"
#include <functional>

using CppCLI::Response, CppCLI::DefineOption;

namespace CppCLI {
    /**
     * Used to define the behavior and expectations of an individual subcommand.
     */
    class Subcommand {
    public:
        Subcommand() = default;

        /**
         * Create a subcommand with a name and description.
         * The description is displayed by helpers.
         *
         * @ref helpers
         * @param subcommand
         * @param description
         */
        Subcommand(std::string subcommand, std::string description) : m_subcommand(std::move(subcommand)),
                                                                      m_description(std::move(description)),
                                                                      m_io(IO()) {}

        /**
         * Define an Option (see DefineOption), which this specific
         * subcommand understands.
         *
         * Example: If you're writing a tiny app to greet a user by their
         * first name, an option could ``name``.
         *
         * @param option
         * @return
         */
        Subcommand &addOption(DefineOption option) noexcept;

        /**
         * Retrieve the list of defined/expected options.
         *
         * @return
         */
        [[nodiscard]] std::vector<DefineOption> getOptions() const noexcept;

        /**
         * Define a handler for this specific subcommand.
         * The handler is executed by CLI.
         *
         * @param handler
         * @return
         */
        Subcommand &
        handle(const std::function<Response(ConsoleIO &printer,
                                            const Interpretation &interpretation)> &handler);

        /**
         * Retrieve the subcommand (name).
         *
         * @return
         */
        [[nodiscard]] std::string getSubcommand() const noexcept;

        /**
         * Retrieve the description.
         * This is typically used by helpers.
         *
         * @ref helpers
         * @return
         */
        [[nodiscard]] std::string getDescription() const noexcept;

        /**
         * Execute the handler with the given interpretation.
         * At this point, it's expected that the interpretation is fully mapped
         * and validated. If not, this can cause errors and undefined behavior.
         *
         * @param interpretation
         * @return
         */
        [[nodiscard]] Response exec(const Interpretation &interpretation);

        /**
         * Add a (child) subcommand to this one.
         * This makes it possible to group commands underneath each other.
         *
         * @ref subcommand-structure
         * @param subcommand
         */
        void addSubcommand(Subcommand subcommand) noexcept;

        /**
         * Retrieve a list of (child) subcommands.
         *
         * @ref subcommand-structure
         * @return
         */
        [[nodiscard]] std::vector<Subcommand> getSubcommands() const noexcept;

    private:
        IO& getIO();

        IO m_io;
        std::string m_subcommand, m_description;
        std::vector<DefineOption> m_options;
        std::vector<Subcommand> m_subcommands;


        std::function<Response(IO &io,
                               const Interpretation &interpretation)> m_handler = [](IO &io,
                               const Interpretation &interpretation) -> Response {
            return { .showHelp = true };
        };
    };
}

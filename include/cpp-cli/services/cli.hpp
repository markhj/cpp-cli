#pragma once

#include "cpp-cli/contracts/helper.hpp"
#include "cpp-cli/utilities/interpretation.hpp"
#include "cpp-cli/utilities/std-helper.hpp"
#include "cpp-cli/utilities/subcommand.hpp"
#include <iostream>
#include <memory>

using CppCLI::Response;
using CppCLI::StdHelper;
using CppCLI::Subcommand;

namespace CppCLI {
    /**
     * CLI Service
     *
     * The primary service for handling the entire CLI flow from interpretation
     * through handling, and finally managing error and success responses.
     */
    class CLI {
    public:
        /**
         * Create a new instance with app name, version and a ConsoleIO.
         *
         * @param appName
         * @param appVersion
         * @param io
         */
        CLI(std::string appName, std::string appVersion, std::shared_ptr<ConsoleIO> io);

        /**
         * Define a new Subcommand.
         * This includes the subcommand at the root of the application.
         *
         * @ref subcommand-structure
         * @param subcommand
         */
        void define(const Subcommand &subcommand) noexcept;

        /**
         * Run the application.
         *
         * This method handles interpretation, error handling and executing
         * the handles associated with each subcommand.
         *
         * @param argc
         * @param argv
         * @return
         */
        Response run(int argc, char *argv[]) noexcept(false);

        /**
         * Replace the error handler.
         *
         * @param errorHandler
         */
        void setErrorHandler(const std::function<Response(std::shared_ptr<ConsoleIO>,
                                                          std::runtime_error &)> &errorHandler);

        /**
         * Replace the helper
         *
         * @ref helpers
         * @param helper
         */
        void setHelper(std::shared_ptr<Helper> helper);

        /**
         * Retrieve a subcommand.
         * Empty ``std::option`` returned, if no command matches
         *
         * @param cmd
         * @return
         */
        [[nodiscard]] std::optional<Subcommand> findSubcommand(const std::optional<std::string> &cmd) const noexcept;

    private:
        std::string m_appName, m_appVersion;

        std::shared_ptr<ConsoleIO> m_io;

        std::vector<Subcommand> m_subcommands;

        std::shared_ptr<Helper> m_helper;

        void validate(const Subcommand &subcommand, const Interpretation &interpretation) noexcept(false);

        [[nodiscard]] Response err(const std::string &msg) const;

        std::function<Response(std::shared_ptr<ConsoleIO>,
                               std::runtime_error &)>
                m_errorHandler = [](std::shared_ptr<ConsoleIO> io,
                                    std::runtime_error &e) {
                    io->error(e.what());
                    return Response();
                };

        /**
         *
         * @param main
         * @return
         */
        std::optional<Subcommand> traceSubcommand(const Interpretation &interpretation) const;
    };
}

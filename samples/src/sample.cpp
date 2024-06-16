#include "cpp-cli/cpp-cli.hpp"
#include <format>
#include <iostream>

const char *APP_VERSION = "v0.1.0";

using CppCLI::CLI;
using CppCLI::ConsoleIO;
using CppCLI::Interpretation;
using CppCLI::IO;
using CppCLI::OptionDataType;
using CppCLI::Subcommand;

int main(int argc, char *argv[]) {
    std::shared_ptr<IO> io = std::make_shared<IO>(IO());
    CLI cli("Sample CLI", APP_VERSION, io);

    cli.define(
            Subcommand()
                    .addOption({.id = "show-help",
                                .short_name = 'h',
                                .long_name = "help",
                                .description = "Learn which commands and options are available"})
                    .addOption({.id = "show-version",
                                .short_name = 'v',
                                .long_name = "version",
                                .description = "Display the current version"})
                    .handle([](ConsoleIO &io, const Interpretation &interpretation) {
                        if (interpretation.hasFlag("show-version")) {
                            io.emit(APP_VERSION);
                        }
                        Response r = Response();
                        if (interpretation.hasFlag("show-help")) {
                            r.showHelp = true;
                        }
                        return r;
                    }));

    cli.define(
            Subcommand("greet", "Greets the user with a warm welcome.")
                    .addOption({.id = "name",
                                .short_name = 'n',
                                .long_name = "name",
                                .required = true,
                                .dataType = OptionDataType::String,
                                .description = "Name of the person to be greeted"})
                    .handle([](ConsoleIO &io, const Interpretation &interpretation) {
                        io.emit(std::format("Hello, {}!",
                                            interpretation.getOption("name").value().value.getAsString()));
                        return Response();
                    }));

    cli.setErrorHandler([](std::shared_ptr<ConsoleIO> io, std::runtime_error &e) {
        io->error(std::format("Oh no!\n{}", e.what()));
        return Response();
    });

    cli.run(argc, argv);

    return 0;
}

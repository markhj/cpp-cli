#include "cpp-cli/cpp-cli.hpp"

using CppCLI::CLI, CppCLI::ConsoleIO, CppCLI::Interpretation, CppCLI::IO, CppCLI::Subcommand;

int main(int argc, char *argv[]) {
    // Initialize an instance of ``IO``.
    // This class is responsible for printing information to the console.
    std::shared_ptr<IO> io = std::make_shared<IO>(IO());

    // Create a CLI app called "Hello World".
    CLI cli("Hello World", "v1.0.0", io);

    // Create a new subcommand (when it's not given a name, it's the universal/top-level command)
    Subcommand subcommand = Subcommand();

    // Define a handler for the subcommand, which prints "Hello world"
    // to the console
    subcommand.handle([](ConsoleIO &io, const Interpretation &interpretation) {
        io.emit("Hello, world!");
        return Response();
    });

    // Add the subcommand to the CLI
    cli.define(subcommand);

    // Run the CLI with argc (argument count) and argv (list of arguments) as provided
    // by C++
    cli.run(argc, argv);

    return 0;
}

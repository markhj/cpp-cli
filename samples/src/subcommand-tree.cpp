#include "cpp-cli/cpp-cli.hpp"

#include <format>
#include <memory>

using CppCLI::IO, CppCLI::CLI, CppCLI::ConsoleIO, CppCLI::Interpretation, CppCLI::OptionDataType;

int main(int argc, char *argv[]) {
    std::shared_ptr<IO> io = std::make_shared<IO>(IO());
    CLI cli("Subtree CLI", "v0.1.0", io);

    // First, we define the universal command.
    // If called, it will display the help (which contains the list of subcommands)
    cli.define(Subcommand());

    // At the top-layer, we create a command alled "project"
    Subcommand project = Subcommand("project", "Create, delete and manage projects");

    // Next, we create another subcommand, called "create", which we intend
    // to nest under the "project" command, such that the end-user can type
    // "project create".
    Subcommand create_project = Subcommand("create", "Create a new project");

    create_project.addOption({
            .id = "name",
            .long_name = "name",
            .required = true,
            .dataType = OptionDataType::String,
    });

    create_project.handle([](ConsoleIO &io, const Interpretation &interpretation) -> Response {
        io.emit(std::format("Creating project: {}",
                            interpretation.getOption("name").value().value.getAsString()));
        return {};
    });

    // We also create a "delete" command.
    // We leave out implementation details, as this is just to show how it works.
    Subcommand delete_project = Subcommand("delete", "Delete a project");

    // Add the two sub-subcommands to the "project" command
    project.addSubcommand(create_project);
    project.addSubcommand(delete_project);

    // Add the "project" command
    cli.define(project);

    // Run the CLI app
    cli.run(argc, argv);

    return 0;
}
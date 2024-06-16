#include "base-test.hpp"
#include "cpp-cli/cpp-cli.hpp"

using CppCLI::CLI;
using CppCLI::Interpretation;
using CppCLI::Response;
using CppCLI::ResponseState;
using CppCLI::Subcommand;
using CppCLI::Value;

class SubcommandTreeTest : public BaseTestCase {
public:
    SubcommandTreeTest() : BaseTestCase() {}

    void configure(CLI &cli) override {
        cli.define(Subcommand()
                           .handle([](ConsoleIO &io, const Interpretation &interpretation) -> Response {
                               return {
                                       .showHelp = true,
                               };
                           }));

        Subcommand project = Subcommand("project", "Create, delete and manage projects");

        Subcommand create_project = Subcommand("create", "Create a new project");
        Subcommand delete_project = Subcommand("delete", "Delete a project");

        create_project.handle([](ConsoleIO &io, const Interpretation &interpretation) -> Response {
            return { .messages = { "Create" } };
        });

        delete_project.handle([](ConsoleIO &io, const Interpretation &interpretation) -> Response {
            return {.messages = {"Delete"}};
        });

        project.addSubcommand(create_project);
        project.addSubcommand(delete_project);

        cli.define(project);
    }

    void run() override {
        testCmd("", [&](const Response& response) {
            assertEquals(ResponseState::Success, response.state);
            assertTrue(response.showHelp);
        });

        testCmd("project", [&](const Response& response) {
            assertEquals(ResponseState::Success, response.state);
            assertTrue(response.showHelp);
        });

        testCmd("project create", [&](const Response& response) {
            assertEquals(ResponseState::Success, response.state);
            assertFalse(response.showHelp);
            assertCount(1, response.messages);
        });

        testCmd("project delete", [&](const Response& response) {
            assertEquals(ResponseState::Success, response.state);
            assertFalse(response.showHelp);
            assertCount(1, response.messages);
        });

        testCmd("unknown", [&](const Response& response) {
            assertEquals(ResponseState::Error, response.state);
            assertEquals("Unknown command.", response.error.value());
        });

        testCmd("project unknown", [&](const Response& response) {
            assertEquals(ResponseState::Error, response.state);
            assertEquals("Unknown command.", response.error.value());
        });
    }
};
